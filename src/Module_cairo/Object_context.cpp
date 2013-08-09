#include "stdafx.h"

Gura_BeginModule(cairo)

//-----------------------------------------------------------------------------
// Object_context implementation
//-----------------------------------------------------------------------------
Object_context::~Object_context()
{
	Destroy();
}

Object *Object_context::Clone() const
{
	return NULL;
}

bool Object_context::DoDirProp(Environment &env, Signal sig, SymbolSet &symbols)
{
	if (!Object::DoDirProp(env, sig, symbols)) return false;
	symbols.insert(Gura_UserSymbol(surface));
	symbols.insert(Gura_UserSymbol(width));
	symbols.insert(Gura_UserSymbol(height));
	return true;
}

Value Object_context::DoGetProp(Environment &env, Signal sig, const Symbol *pSymbol,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(surface))) {
		return Value(Object_surface::Reference(_pObjSurface.get()));
	}
	evaluatedFlag = false;
	return Value::Null;
}

String Object_context::ToString(Signal sig, bool exprFlag)
{
	String str;
	str += "<cairo.context:";
	if (_cr == NULL) {
		str += "invalid";
	} else {
		cairo_surface_t *surface = ::cairo_get_target(_cr);
		cairo_surface_type_t surface_type = ::cairo_surface_get_type(surface);
		str += SurfaceTypeToName(surface_type);
		if (surface_type == CAIRO_SURFACE_TYPE_IMAGE) {
			str += ":";
			str += NumberToString(::cairo_image_surface_get_width(surface));
			str += "x";
			str += NumberToString(::cairo_image_surface_get_height(surface));
		}
	}
	str += ">";
	return str;
}

void Object_context::Destroy()
{
	if (_cr != NULL) {
		::cairo_destroy(_cr);
		_cr = NULL;
		_pObjSurface.reset(NULL);
	}
}

//-----------------------------------------------------------------------------
// Gura interfaces for context
// context operations
//-----------------------------------------------------------------------------
//#cairo_t *cairo_reference(cairo_t *cr);
//#void cairo_destroy(cairo_t *cr);

// cairo.context#status()
Gura_DeclareMethod(context, status)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	AddHelp(Gura_Symbol(en),
	"Checks whether an error has previously occurred for this context."
	);
}

Gura_ImplementMethod(context, status)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *context = pThis->GetEntity();
	cairo_status_t rtn = ::cairo_status(context);
	return Value(rtn);
}

// cairo.context#destroy():reduce
Gura_DeclareMethod(context, destroy)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	AddHelp(Gura_Symbol(en),
	"Decreases the reference count on cr by one.\n"
	"If the result is zero, then cr and all associated resources are freed.\n"
	"See cairo.context#reference()."
	);
}

Gura_ImplementMethod(context, destroy)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	pThis->Destroy();
	return Value::Null;
}

// cairo.context#save():reduce {block?}
Gura_DeclareMethod(context, save)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(Gura_Symbol(en),
	"Makes a copy of the current state of cr and saves it on an internal stack of saved states for cr.\n"
	"When cairo.context#restore() is called, cr will be restored to the saved state.\n"
	"Multiple calls to cairo.context#save() and cairo.context#restore() can be nested;\n"
	"each call to cairo.context#restore() restores the state from the matching paired cairo.context#save().\n"
	"\n"
	"It isn't necessary to clear all saved states before a cairo_t is freed.\n"
	"If the reference count of a cairo_t drops to zero in response to a call to cairo.context#destroy(),\n"
	"any saved states will be freed along with the cairo_t.\n"
	);
}

Gura_ImplementMethod(context, save)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_save(cr);
	if (IsError(sig, cr)) return Value::Null;
	if (args.IsBlockSpecified()) {
		const Expr_Block *pExprBlock = args.GetBlock(env, sig);
		if (sig.IsSignalled()) return Value::Null;
		pExprBlock->Exec(env, sig);
		::cairo_restore(cr);
		if (IsError(sig, cr)) return Value::Null;
	}
	return args.GetThis();
}

// cairo.context#restore():reduce
Gura_DeclareMethod(context, restore)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	AddHelp(Gura_Symbol(en),
	"Restores cr to the state saved by a preceding call to cairo.context#save()\n"
	"and removes that state from the stack of saved states."
	);
}

Gura_ImplementMethod(context, restore)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_restore(cr);
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#get_target()
Gura_DeclareMethod(context, get_target)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	AddHelp(Gura_Symbol(en),
	"Gets the target surface for the cairo context as passed to cairo.context constructor.\n"
	);
}

Gura_ImplementMethod(context, get_target)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	cairo_surface_t *surface = ::cairo_get_target(cr);
	if (IsError(sig, cr)) return Value::Null;
	return Value(Object_surface::Reference(pThis->GetSurfaceObj()));
}

// cairo.context#push_group():reduce
Gura_DeclareMethod(context, push_group)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	AddHelp(Gura_Symbol(en),
	"Temporarily redirects drawing to an intermediate surface known as a group.\n"
	"The redirection lasts until the group is completed by a call to cairo.context#pop_group() or cairo.context#pop_group_to_source().\n"
	"These calls provide the result of any drawing to the group as a pattern,\n"
	"(either as an explicit object, or set as the source pattern).\n"
	"\n"
	"This group functionality can be convenient for performing intermediate compositing.\n"
	"One common use of a group is to render objects as opaque within the group,\n"
	"(so that they occlude each other), and then blend the result with translucence onto the destination.\n"
	"\n"
	"Groups can be nested arbitrarily deep by making balanced calls to cairo.context#push_group()/cairo.context#pop_group().\n"
	"Each call pushes/pops the new target group onto/from a stack.\n"
	"\n"
	"The cairo.context#push_group() function calls cairo_save()\n"
	"so that any changes to the graphics state will not be visible outside the group,\n"
	"(the pop_group functions call cairo_restore()).\n"
	"\n"
	"By default the intermediate group will have a content type of cairo.CONTENT_COLOR_ALPHA.\n"
	"Other content types can be chosen for the group by using cairo.context#push_group_with_content() instead.\n"
	"\n"
	"As an example, here is how one might fill and stroke a path with translucence,\n"
	"but without any portion of the fill being visible under the stroke:\n"
	);
}

Gura_ImplementMethod(context, push_group)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_push_group(cr);
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#push_group_with_content(content:number):reduce
Gura_DeclareMethod(context, push_group_with_content)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "content", VTYPE_number);
	AddHelp(Gura_Symbol(en),
	"Temporarily redirects drawing to an intermediate surface known as a group.\n"
	"The redirection lasts until the group is completed by a call to cairo.context#pop_group() or cairo.context#pop_group_to_source().\n"
	"These calls provide the result of any drawing to the group as a pattern,\n"
	"(either as an explicit object, or set as the source pattern).\n"
	"\n"
	"The group will have a content type of content.\n"
	"The ability to control this content type is the only distinction between this function and cairo.context#push_group()\n"
	"which you should see for a more detailed description of group rendering.\n"
	);
}

Gura_ImplementMethod(context, push_group_with_content)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	cairo_content_t content = static_cast<cairo_content_t>(args.GetInt(0));
	if (sig.IsSignalled()) return Value::Null;
	::cairo_push_group_with_content(cr, content);
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#pop_group()
Gura_DeclareMethod(context, pop_group)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	AddHelp(Gura_Symbol(en),
	"Terminates the redirection begun by a call to cairo.context#push_group() or cairo.context#push_group_with_content()\n"
	"and returns a new pattern containing the results of all drawing operations performed to the group.\n"
	"\n"
	"The cairo.context#pop_group() function calls cairo_restore(),\n"
	"(balancing a call to cairo_save() by the push_group function),\n"
	"so that any changes to the graphics state will not be visible outside the group.\n"
	);
}

Gura_ImplementMethod(context, pop_group)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	cairo_pattern_t *pattern = ::cairo_pop_group(cr);
	if (IsError(sig, cr)) return Value::Null;
	Object_pattern *pObjPattern = new Object_pattern(pattern);
	return Value(pObjPattern);
}

// cairo.context#pop_group_to_source():reduce
Gura_DeclareMethod(context, pop_group_to_source)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	AddHelp(Gura_Symbol(en),
	"Terminates the redirection begun by a call to cairo.context#push_group() or cairo.context#push_group_with_content()\n"
	"and installs the resulting pattern as the source pattern in the given cairo context.\n"
	"\n"
	"The cairo.context#pop_group() function calls cairo_restore(),\n"
	"(balancing a call to cairo_save() by the push_group function),\n"
	"so that any changes to the graphics state will not be visible outside the group.\n"
	);
}

Gura_ImplementMethod(context, pop_group_to_source)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_pop_group_to_source(cr);
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#get_group_target()
Gura_DeclareMethod(context, get_group_target)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	AddHelp(Gura_Symbol(en),
	"Gets the current destination surface for the context.\n"
	"This is either the original target surface as passed to cairo.context constructor\n"
	"or the target surface for the current group as started\n"
	"by the most recent call to cairo.context#push_group() or cairo.context#push_group_with_content().\n"
	);
}

Gura_ImplementMethod(context, get_group_target)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	cairo_surface_t *surface = ::cairo_get_group_target(cr);
	if (IsError(sig, cr)) return Value::Null;
	Object_surface *pObjSurface =
			new Object_surface(::cairo_surface_reference(surface));
	return Value(pObjSurface);
}

// cairo.context#set_source_rgb(red:number, green:number, blue:number):reduce
Gura_DeclareMethod(context, set_source_rgb)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "red", VTYPE_number);
	DeclareArg(env, "green", VTYPE_number);
	DeclareArg(env, "blue", VTYPE_number);
	AddHelp(Gura_Symbol(en),
	"Sets the source pattern within cr to an opaque color.\n"
	"This opaque color will then be used for any subsequent drawing operation until a new source pattern is set.\n"
	"\n"
	"The color components are floating point numbers in the range 0 to 1.\n"
	"If the values passed in are outside that range, they will be clamped.\n"
	"\n"
	"The default source pattern is opaque black, (that is, it is equivalent to cr.set_source_rgb(0.0, 0.0, 0.0)).\n"
	);
}

Gura_ImplementMethod(context, set_source_rgb)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_set_source_rgb(cr, args.GetDouble(0), args.GetDouble(1), args.GetDouble(2));
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#set_source_rgba(red:number, green:number, blue:number, alpha:number):reduce
Gura_DeclareMethod(context, set_source_rgba)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "red", VTYPE_number);
	DeclareArg(env, "green", VTYPE_number);
	DeclareArg(env, "blue", VTYPE_number);
	DeclareArg(env, "alpha", VTYPE_number);
	AddHelp(Gura_Symbol(en),
	"Sets the source pattern within cr to a translucent color.\n"
	"This color will then be used for any subsequent drawing operation until a new source pattern is set.\n"
	"\n"
	"The color and alpha components are floating point numbers in the range 0 to 1.\n"
	"If the values passed in are outside that range, they will be clamped.\n"
	"\n"
	"The default source pattern is opaque black, (that is, it is equivalent to cr.set_source_rgba(0.0, 0.0, 0.0, 1.0)).\n"
	);
}

Gura_ImplementMethod(context, set_source_rgba)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_set_source_rgba(cr, args.GetDouble(0), args.GetDouble(1),
									args.GetDouble(2), args.GetDouble(3));
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#set_source_color(color:color, alpha?:number):reduce
Gura_DeclareMethod(context, set_source_color)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "color", VTYPE_color);
	DeclareArg(env, "alpha", VTYPE_number, OCCUR_ZeroOrOnce);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, set_source_color)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	const Color &color = Object_color::GetObject(args, 0)->GetColor();
	double red = static_cast<double>(color.GetRed()) / 255;
	double green = static_cast<double>(color.GetGreen()) / 255;
	double blue = static_cast<double>(color.GetBlue()) / 255;
	if (args.IsNumber(1)) {
		double alpha = args.GetDouble(1);
		::cairo_set_source_rgba(cr, red, green, blue, alpha);
	} else {
		::cairo_set_source_rgb(cr, red, green, blue);
	}
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#set_source(source:cairo.pattern):reduce
Gura_DeclareMethod(context, set_source)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "source", VTYPE_pattern);
	AddHelp(Gura_Symbol(en),
	"Sets the source pattern within cr to source.\n"
	"This pattern will then be used for any subsequent drawing operation until a new source pattern is set.\n"
	"\n"
	"Note: The pattern's transformation matrix will be locked to the user space in effect at the time of cairo.context#set_source().\n"
	"This means that further modifications of the current transformation matrix will not affect the source pattern. See cairo.pattern#set_matrix().\n"
	"\n"
	"The default source pattern is a solid pattern that is opaque black,\n"
	"(that is, it is equivalent to cr.set_source_rgb(0.0, 0.0, 0.0)).\n"
	);
}

Gura_ImplementMethod(context, set_source)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	cairo_pattern_t *source = Object_pattern::GetObject(args, 0)->GetEntity();
	::cairo_set_source(cr, source);
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#set_source_surface(surface:cairo.surface, x:number, y:number):reduce
Gura_DeclareMethod(context, set_source_surface)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "surface", VTYPE_surface);
	DeclareArg(env, "x", VTYPE_number);
	DeclareArg(env, "y", VTYPE_number);
	AddHelp(Gura_Symbol(en),
	"This is a convenience function for creating a pattern from surface\n"
	"and setting it as the source in cr with cairo.context#set_source().\n"
	"\n"
	"The x and y parameters give the user-space coordinate at which the surface origin should appear.\n"
	"(The surface origin is its upper-left corner before any transformation has been applied.)\n"
	"The x and y parameters are negated and then set as translation values in the pattern matrix.\n"
	"\n"
	"Other than the initial translation pattern matrix, as described above,\n"
	"all other pattern attributes, (such as its extend mode), are set to the default values as in cairo.pattern.create_for_surface().\n"
	"The resulting pattern can be queried with cairo.context#get_source() so that these attributes can be modified if desired,\n"
	"(eg. to create a repeating pattern with cairo.pattern#set_extend()).\n"
	);
}

Gura_ImplementMethod(context, set_source_surface)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	cairo_surface_t *surface = Object_surface::GetObject(args, 0)->GetEntity();
	double x = args.GetDouble(1);
	double y = args.GetDouble(2);
	::cairo_set_source_surface(cr, surface, x, y);
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#get_source()
Gura_DeclareMethod(context, get_source)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	AddHelp(Gura_Symbol(en),
	"Gets the current source pattern for cr.\n"
	);
}

Gura_ImplementMethod(context, get_source)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	cairo_pattern_t *pattern = ::cairo_get_source(cr);
	if (IsError(sig, cr)) return Value::Null;
	Object_pattern *pObjPattern =
				new Object_pattern(::cairo_pattern_reference(pattern));
	return Value(pObjPattern);
}

// cairo.context#set_antialias(antialias:number):reduce
Gura_DeclareMethod(context, set_antialias)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "antialias", VTYPE_number);
	AddHelp(Gura_Symbol(en),
	"Set the antialiasing mode of the rasterizer used for drawing shapes.\n"
	"This value is a hint, and a particular backend may or may not support a particular value.\n"
	"At the current time, no backend supports cairo.ANTIALIAS_SUBPIXEL when drawing shapes.\n"
	"\n"
	"Note that this option does not affect text rendering, instead see cairo.font_options#set_antialias().\n"
	);
}

Gura_ImplementMethod(context, set_antialias)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	cairo_antialias_t antialias = static_cast<cairo_antialias_t>(args.GetInt(0));
	if (sig.IsSignalled()) return Value::Null;
	::cairo_set_antialias(cr, antialias);
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#get_antialias()
Gura_DeclareMethod(context, get_antialias)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	AddHelp(Gura_Symbol(en),
	"Gets the current shape antialiasing mode, as set by cairo.context#set_antialias().\n"
	);
}

Gura_ImplementMethod(context, get_antialias)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	cairo_antialias_t antialias = ::cairo_get_antialias(cr);
	if (IsError(sig, cr)) return Value::Null;
	return Value(antialias);
}

// cairo.context#set_dash(dashes[]:number, offset:number):reduce
Gura_DeclareMethod(context, set_dash)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "dashes", VTYPE_number, OCCUR_Once, FLAG_List);
	DeclareArg(env, "offset", VTYPE_number);
	AddHelp(Gura_Symbol(en),
	"Sets the dash pattern to be used by cairo.context#stroke().\n"
	"A dash pattern is specified by dashes, an array of positive values.\n"
	"Each value provides the length of alternate \"on\" and \"off\" portions of the stroke.\n"
	"The offset specifies an offset into the pattern at which the stroke begins.\n"
	"\n"
	"Each \"on\" segment will have caps applied as if the segment were a separate sub-path.\n"
	"In particular, it is valid to use an \"on\" length of 0.0 with cairo.LINE_CAP_ROUND or cairo.LINE_CAP_SQUARE\n"
	"in order to distributed dots or squares along a path.\n"
	"\n"
	"Note: The length values are in user-space units as evaluated at the time of stroking.\n"
	"This is not necessarily the same as the user space at the time of cairo.context#set_dash().\n"
	"\n"
	"If length of dashes is 0 dashing is disabled.\n"
	"\n"
	"If length of dashes is 1 a symmetric pattern is assumed\n"
	"with alternating on and off portions of the size specified by the single value in dashes.\n"
	"\n"
	"If any value in dashes is negative, or if all values are 0,\n"
	"then cr will be put into an error state with a status of cairo.STATUS_INVALID_DASH.\n"
	);
}

Gura_ImplementMethod(context, set_dash)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	int num_dashes = static_cast<int>(args.GetList(0).size());
	double *dashes = new double [num_dashes];
	int i = 0;
	foreach_const (ValueList, pValue, args.GetList(0)) {
		dashes[i++] = pValue->GetDouble();
	}
	double offset = args.GetDouble(1);
	::cairo_set_dash(cr, dashes, num_dashes, offset);
	delete[] dashes;
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#get_dash()
Gura_DeclareMethod(context, get_dash)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	AddHelp(Gura_Symbol(en),
	"Gets the current dash array."
	);
}

Gura_ImplementMethod(context, get_dash)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	int num_dashes = ::cairo_get_dash_count(cr);
	double *dashes = new double [num_dashes];
	double offset = 0;
	::cairo_get_dash(cr, dashes, &offset);
	if (IsError(sig, cr)) {
		delete[] dashes;
		return Value::Null;
	}
	Value rtn;
	ValueList &valList = rtn.InitAsList(env);
	valList.reserve(num_dashes);
	for (int i = 0; i < num_dashes; i++) {
		valList.push_back(Value(dashes[num_dashes]));
	}
	delete[] dashes;
	return Value::CreateAsList(env, rtn, Value(offset));
}

// cairo.context#set_fill_rule(fill_rule:number):reduce
Gura_DeclareMethod(context, set_fill_rule)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "fill_rule", VTYPE_number);
	AddHelp(Gura_Symbol(en),
	"Set the current fill rule within the cairo context.\n"
	"The fill rule is used to determine which regions are inside or outside a complex\n"
	"(potentially self-intersecting) path. The current fill rule affects both cairo.context#fill() and cairo.context#clip().\n"
	"See cairo_fill_rule_t for details on the semantics of each available fill rule.\n"
	"\n"
	"The default fill rule is cairo.FILL_RULE_WINDING.\n"
	);
}

Gura_ImplementMethod(context, set_fill_rule)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	cairo_fill_rule_t fill_rule = static_cast<cairo_fill_rule_t>(args.GetInt(0));
	if (sig.IsSignalled()) return Value::Null;
	::cairo_set_fill_rule(cr, fill_rule);
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#get_fill_rule()
Gura_DeclareMethod(context, get_fill_rule)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	AddHelp(Gura_Symbol(en),
	"Gets the current fill rule, as set by cairo.context#set_fill_rule().\n"
	);
}

Gura_ImplementMethod(context, get_fill_rule)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	cairo_fill_rule_t fill_rule = ::cairo_get_fill_rule(cr);
	if (IsError(sig, cr)) return Value::Null;
	return Value(fill_rule);
}

// cairo.context#set_line_cap(line_cap:number):reduce
Gura_DeclareMethod(context, set_line_cap)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "line_cap", VTYPE_number);
	AddHelp(Gura_Symbol(en),
	"Sets the current line cap style within the cairo context.\n"
	"See cairo_line_cap_t for details about how the available line cap styles are drawn.\n"
	"\n"
	"As with the other stroke parameters, the current line cap style is examined by cairo.context#stroke(), cairo.context#stroke_extents(),\n"
	"and cairo.context#stroke_to_path(), but does not have any effect during path construction.\n"
	"\n"
	"The default line cap style is cairo.LINE_CAP_BUTT.\n"
	);
}

Gura_ImplementMethod(context, set_line_cap)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	cairo_line_cap_t line_cap = static_cast<cairo_line_cap_t>(args.GetInt(0));
	if (sig.IsSignalled()) return Value::Null;
	::cairo_set_line_cap(cr, line_cap);
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#get_line_cap()
Gura_DeclareMethod(context, get_line_cap)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	AddHelp(Gura_Symbol(en),
	"Gets the current line cap style, as set by cairo.context#set_line_cap()."
	);
}

Gura_ImplementMethod(context, get_line_cap)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	cairo_line_cap_t line_cap = ::cairo_get_line_cap(cr);
	if (IsError(sig, cr)) return Value::Null;
	return Value(line_cap);
}

// cairo.context#set_line_join(line_join:number):reduce
Gura_DeclareMethod(context, set_line_join)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "line_join", VTYPE_number);
	AddHelp(Gura_Symbol(en),
	"Sets the current line join style within the cairo context.\n"
	"See cairo_line_join_t for details about how the available line join styles are drawn.\n"
	"\n"
	"As with the other stroke parameters, the current line join style is examined by cairo.context#stroke(), cairo.context#stroke_extents(),\n"
	"and cairo.context#stroke_to_path(), but does not have any effect during path construction.\n"
	"\n"
	"The default line join style is cairo.LINE_JOIN_MITER.\n"
	);
}

Gura_ImplementMethod(context, set_line_join)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	cairo_line_join_t line_join = static_cast<cairo_line_join_t>(args.GetInt(0));
	if (sig.IsSignalled()) return Value::Null;
	::cairo_set_line_join(cr, line_join);
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#get_line_join()
Gura_DeclareMethod(context, get_line_join)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	AddHelp(Gura_Symbol(en),
	"Gets the current line join style, as set by cairo.context#set_line_join().\n"
	);
}

Gura_ImplementMethod(context, get_line_join)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	cairo_line_join_t line_join = ::cairo_get_line_join(cr);
	if (IsError(sig, cr)) return Value::Null;
	return Value(line_join);
}

// cairo.context#set_line_width(width:number):reduce
Gura_DeclareMethod(context, set_line_width)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "width", VTYPE_number);
	AddHelp(Gura_Symbol(en),
	"Sets the current line width within the cairo context.\n"
	"The line width value specifies the diameter of a pen that is circular in user space,\n"
	"(though device-space pen may be an ellipse in general due to scaling/shear/rotation of the CTM).\n"
	"\n"
	"Note: When the description above refers to user space and CTM\n"
	"it refers to the user space and CTM in effect at the time of the stroking operation,\n"
	"not the user space and CTM in effect at the time of the call to cairo.context#set_line_width().\n"
	"The simplest usage makes both of these spaces identical.\n"
	"That is, if there is no change to the CTM between a call to cairo.context#set_line_width() and the stroking operation,\n"
	"then one can just pass user-space values to cairo.context#set_line_width() and ignore this note.\n"
	"\n"
	"As with the other stroke parameters, the current line width is examined by cairo.context#stroke(), cairo.context#stroke_extents(),\n"
	"and cairo.context#stroke_to_path(), but does not have any effect during path construction.\n"
	"\n"
	"The default line width value is 2.0.\n"
	);
}

Gura_ImplementMethod(context, set_line_width)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_set_line_width(cr, args.GetDouble(0));
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#get_line_width()
Gura_DeclareMethod(context, get_line_width)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	AddHelp(Gura_Symbol(en),
	"This function returns the current line width value exactly as set by cairo.context#set_line_width().\n"
	"Note that the value is unchanged even if the CTM has changed between the calls to cairo.context#set_line_width()\n"
	"and cairo.context#get_line_width().\n"
	);
}

Gura_ImplementMethod(context, get_line_width)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	double width = ::cairo_get_line_width(cr);
	if (IsError(sig, cr)) return Value::Null;
	return Value(width);
}

// cairo.context#set_miter_limit(limit:number):reduce
Gura_DeclareMethod(context, set_miter_limit)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "limit", VTYPE_number);
	AddHelp(Gura_Symbol(en),
	"Sets the current miter limit within the cairo context.\n"
	"\n"
	"If the current line join style is set to cairo.LINE_JOIN_MITER\n"
	"(see cairo_set_line_join()), the miter limit is used to determine whether the lines should be joined with a bevel instead of a miter.\n"
	"Cairo divides the length of the miter by the line width.\n"
	"If the result is greater than the miter limit, the style is converted to a bevel.\n"
	"\n"
	"As with the other stroke parameters, the current line miter limit is examined by cairo.context#stroke(), cairo.context#stroke_extents(),\n"
	"and cairo.context#stroke_to_path(), but does not have any effect during path construction.\n"
	"\n"
	"The default miter limit value is 10.0, which will convert joins with interior angles less than 11 degrees to bevels instead of miters.\n"
	"For reference, a miter limit of 2.0 makes the miter cutoff at 60 degrees, and a miter limit of 1.414 makes the cutoff at 90 degrees.\n"
	"\n"
	"A miter limit for a desired angle can be computed as: miter limit = 1/sin(angle/2)\n"
	);
}

Gura_ImplementMethod(context, set_miter_limit)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_set_miter_limit(cr, args.GetDouble(0));
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#get_miter_limit()
Gura_DeclareMethod(context, get_miter_limit)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	AddHelp(Gura_Symbol(en),
	"Gets the current miter limit, as set by cairo.context#set_miter_limit().\n"
	);
}

Gura_ImplementMethod(context, get_miter_limit)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	double limit = ::cairo_get_miter_limit(cr);
	if (IsError(sig, cr)) return Value::Null;
	return Value(limit);
}

// cairo.context#set_operator(op:number):reduce
Gura_DeclareMethod(context, set_operator)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "op", VTYPE_number);
	AddHelp(Gura_Symbol(en),
	"Sets the compositing operator to be used for all drawing operations.\n"
	"See cairo_operator_t for details on the semantics of each available compositing operator.\n"
	"\n"
	"The default operator is cairo.OPERATOR_OVER.\n"
	);
}

Gura_ImplementMethod(context, set_operator)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	cairo_operator_t operator_ = static_cast<cairo_operator_t>(args.GetInt(0));
	if (sig.IsSignalled()) return Value::Null;
	::cairo_set_operator(cr, operator_);
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#get_operator()
Gura_DeclareMethod(context, get_operator)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	AddHelp(Gura_Symbol(en),
	"Gets the current compositing operator for a cairo context.\n"
	);
}

Gura_ImplementMethod(context, get_operator)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	cairo_operator_t operator_ = ::cairo_get_operator(cr);
	if (IsError(sig, cr)) return Value::Null;
	return Value(operator_);
}

// cairo.context#set_tolerance(tolerance:number):reduce
Gura_DeclareMethod(context, set_tolerance)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "tolerance", VTYPE_number);
	AddHelp(Gura_Symbol(en),
	"Sets the tolerance used when converting paths into trapezoids.\n"
	"Curved segments of the path will be subdivided until the maximum deviation\n"
	"between the original path and the polygonal approximation is less than tolerance.\n"
	"The default value is 0.1. A larger value will give better performance,\n"
	"a smaller value, better appearance.\n"
	"(Reducing the value from the default value of 0.1 is unlikely to improve appearance significantly.)\n"
	"The accuracy of paths within Cairo is limited by the precision of its internal arithmetic,\n"
	"and the prescribed tolerance is restricted to the smallest representable internal value.\n"
	);
}

Gura_ImplementMethod(context, set_tolerance)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_set_tolerance(cr, args.GetDouble(0));
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#get_tolerance()
Gura_DeclareMethod(context, get_tolerance)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	AddHelp(Gura_Symbol(en),
	"Gets the current tolerance value, as set by cairo.context#set_tolerance()."
	);
}

Gura_ImplementMethod(context, get_tolerance)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	double tolerance = ::cairo_get_tolerance(cr);
	if (IsError(sig, cr)) return Value::Null;
	return Value(tolerance);
}

// cairo.context#clip():reduce
Gura_DeclareMethod(context, clip)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	AddHelp(Gura_Symbol(en),
	"Establishes a new clip region by intersecting the current clip region\n"
	"with the current path as it would be filled by cairo.context#fill()\n"
	"and according to the current fill rule (see cairo.context#set_fill_rule()).\n"
	"\n"
	"After cairo.context#clip(), the current path will be cleared from the cairo context.\n"
	"\n"
	"The current clip region affects all drawing operations\n"
	"by effectively masking out any changes to the surface that are outside the current clip region.\n"
	"\n"
	"Calling cairo.context#clip() can only make the clip region smaller, never larger.\n"
	"But the current clip is part of the graphics state,\n"
	"so a temporary restriction of the clip region can be achieved by calling cairo.context#clip()\n"
	"within a cairo.context#save()/cairo.context#restore() pair.\n"
	"The only other means of increasing the size of the clip region is cairo.context#reset_clip().\n"
	);
}

Gura_ImplementMethod(context, clip)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_clip(cr);
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#clip_preserve():reduce
Gura_DeclareMethod(context, clip_preserve)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	AddHelp(Gura_Symbol(en),
	"Establishes a new clip region by intersecting the current clip region\n"
	"with the current path as it would be filled by cairo.context#fill()\n"
	"and according to the current fill rule (see cairo.context#set_fill_rule())."
	"\n"
	"Unlike cairo.context#clip(), cairo.context#clip_preserve() preserves the path within the cairo context.\n"
	"\n"
	"The current clip region affects all drawing operations\n"
	"by effectively masking out any changes to the surface that are outside the current clip region.\n"
	"\n"
	"Calling cairo.context#clip_preserve() can only make the clip region smaller, never larger.\n"
	"But the current clip is part of the graphics state,\n"
	"so a temporary restriction of the clip region can be achieved by calling cairo.context#clip_preserve()\n"
	"within a cairo.context#save()/cairo.context#restore() pair.\n"
	"The only other means of increasing the size of the clip region is cairo.context#reset_clip().\n"
	);
}

Gura_ImplementMethod(context, clip_preserve)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_clip_preserve(cr);
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#clip_extents()
Gura_DeclareMethod(context, clip_extents)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	AddHelp(Gura_Symbol(en),
	"Computes a bounding box in user coordinates covering the area inside the current clip.\n"
	);
}

Gura_ImplementMethod(context, clip_extents)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	double x1, y1, x2, y2;
	::cairo_clip_extents(cr, &x1, &y1, &x2, &y2);
	if (IsError(sig, cr)) return Value::Null;
	return CreateValueList(env, x1, y1, x2, y2);
}

// cairo.context#in_clip(x:number, y:number)
Gura_DeclareMethod(context, in_clip)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "x", VTYPE_number);
	DeclareArg(env, "y", VTYPE_number);
	AddHelp(Gura_Symbol(en),
	"Tests whether the given point is inside the area that would be visible through the current clip,\n"
	"i.e. the area that would be filled by a cairo.context#paint() operation.\n"
	"\n"
	"See cairo.context#clip(), and cairo.context#clip_preserve().\n"
	);
}

Gura_ImplementMethod(context, in_clip)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	bool rtn = ::cairo_in_clip(cr, args.GetDouble(0), args.GetDouble(1))? true : false;
	if (IsError(sig, cr)) return Value::Null;
	return Value(rtn);
}

// cairo.context#reset_clip():reduce
Gura_DeclareMethod(context, reset_clip)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	AddHelp(Gura_Symbol(en),
	"Reset the current clip region to its original, unrestricted state.\n"
	"That is, set the clip region to an infinitely large shape containing the target surface.\n"
	"Equivalently, if infinity is too hard to grasp,\n"
	"one can imagine the clip region being reset to the exact bounds of the target surface.\n"
	"\n"
	"Note that code meant to be reusable should not call cairo_reset_clip()\n"
	"as it will cause results unexpected by higher-level code which calls cairo.context#clip().\n"
	"Consider using cairo.context#save() and cairo.context#restore() around cairo.context#clip()\n"
	"as a more robust means of temporarily restricting the clip region.\n"
	);
}

Gura_ImplementMethod(context, reset_clip)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_reset_clip(cr);
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

//#void cairo_rectangle_list_destroy(cairo_rectangle_list_t *rectangle_list);

// cairo.context#copy_clip_rectangle_list()
Gura_DeclareMethod(context, copy_clip_rectangle_list)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	AddHelp(Gura_Symbol(en),
	"Gets the current clip region as a list of rectangles in user coordinates.\n"
	"\n"
	"The status in the list may be cairo.STATUS_CLIP_NOT_REPRESENTABLE\n"
	"to indicate that the clip region cannot be represented as a list of user-space rectangles.\n"
	"The status may have other values to indicate other errors.\n"
	);
}

Gura_ImplementMethod(context, copy_clip_rectangle_list)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	cairo_rectangle_list_t *rectangle_list = ::cairo_copy_clip_rectangle_list(cr);
	if (IsError(sig, cr)) {
		::cairo_rectangle_list_destroy(rectangle_list);
		return Value::Null;
	}
	Value result;
	ValueList &valList = result.InitAsList(env);
	valList.reserve(rectangle_list->num_rectangles);
	for (int i = 0; i < rectangle_list->num_rectangles; i++) {
		cairo_rectangle_t &rectangle = rectangle_list->rectangles[i];
		valList.push_back(RectangleToValue(env, rectangle));
	}
	::cairo_rectangle_list_destroy(rectangle_list);
	return result;
}

// cairo.context#fill():reduce
Gura_DeclareMethod(context, fill)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	AddHelp(Gura_Symbol(en),
	"A drawing operator that fills the current path according to the current fill rule,\n"
	"(each sub-path is implicitly closed before being filled).\n"
	"After cairo.context#fill(), the current path will be cleared from the cairo context.\n"
	"See cairo.context#set_fill_rule() and cairo.context#fill_preserve().\n"
	);
}

Gura_ImplementMethod(context, fill)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_fill(cr);
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#fill_preserve():reduce
Gura_DeclareMethod(context, fill_preserve)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	AddHelp(Gura_Symbol(en),
	"A drawing operator that fills the current path according to the current fill rule,\n"
	"(each sub-path is implicitly closed before being filled).\n"
	"Unlike cairo.context#fill(), cairo.context#fill_preserve() preserves the path within the cairo context.\n"
	"\n"
	"See cairo.context#set_fill_rule() and cairo.context#fill().\n"
	);
}

Gura_ImplementMethod(context, fill_preserve)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_fill_preserve(cr);
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#fill_extents():reduce
Gura_DeclareMethod(context, fill_extents)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, fill_extents)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	double x1, y1, x2, y2;
	::cairo_fill_extents(cr, &x1, &y1, &x2, &y2);
	if (IsError(sig, cr)) return Value::Null;
	return CreateValueList(env, x1, y1, x2, y2);
}

// cairo.context#in_fill(x:number, y:number)
Gura_DeclareMethod(context, in_fill)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "x", VTYPE_number);
	DeclareArg(env, "y", VTYPE_number);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, in_fill)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	bool rtn = ::cairo_in_fill(cr, args.GetDouble(0), args.GetDouble(1))? true : false;
	if (IsError(sig, cr)) return Value::Null;
	return Value(rtn);
}

// cairo.context#mask(pattern:cairo.pattern):reduce
Gura_DeclareMethod(context, mask)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "pattern", VTYPE_pattern);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, mask)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	cairo_pattern_t *pattern = Object_pattern::GetObject(args, 0)->GetEntity();
	::cairo_mask(cr, pattern);
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#mask_surface(surface:cairo.surface, surface_x:number, surface_y:number):reduce
Gura_DeclareMethod(context, mask_surface)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "surface", VTYPE_surface);
	DeclareArg(env, "surface_x", VTYPE_number);
	DeclareArg(env, "surface_y", VTYPE_number);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, mask_surface)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	cairo_surface_t *surface = Object_surface::GetObject(args, 0)->GetEntity();
	double surface_x = args.GetDouble(1);
	double surface_y = args.GetDouble(2);
	::cairo_mask_surface(cr, surface, surface_x, surface_y);
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#paint():reduce
Gura_DeclareMethod(context, paint)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, paint)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_paint(cr);
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#paint_with_alpha(alpha:number):reduce
Gura_DeclareMethod(context, paint_with_alpha)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "alpha", VTYPE_number);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, paint_with_alpha)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_paint_with_alpha(cr, args.GetDouble(0));
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#stroke():reduce
Gura_DeclareMethod(context, stroke)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, stroke)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_stroke(cr);
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#stroke_preserve():reduce
Gura_DeclareMethod(context, stroke_preserve)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, stroke_preserve)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_stroke_preserve(cr);
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#stroke_extents()
Gura_DeclareMethod(context, stroke_extents)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, stroke_extents)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	double x1, y1, x2, y2;
	::cairo_stroke_extents(cr, &x1, &y1, &x2, &y2);
	if (IsError(sig, cr)) return Value::Null;
	return CreateValueList(env, x1, y1, x2, y2);
}

// cairo.context#in_stroke(x:number, y:number)
Gura_DeclareMethod(context, in_stroke)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "x", VTYPE_number);
	DeclareArg(env, "y", VTYPE_number);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, in_stroke)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	bool rtn = ::cairo_in_stroke(cr, args.GetDouble(0), args.GetDouble(1))? true : false;
	if (IsError(sig, cr)) return Value::Null;
	return Value(rtn);
}

// cairo.context#copy_page():reduce
Gura_DeclareMethod(context, copy_page)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, copy_page)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_copy_page(cr);
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#show_page():reduce
Gura_DeclareMethod(context, show_page)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, show_page)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_show_page(cr);
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

//#unsigned int cairo_get_reference_count(cairo_t *cr);
//#cairo_status_t cairo_set_user_data(cairo_t *cr, const cairo_user_data_key_t *key, void *user_data, cairo_destroy_func_t destroy);
//#void *cairo_get_user_data(cairo_t *cr, const cairo_user_data_key_t *key);

//-----------------------------------------------------------------------------
// Gura interfaces for context
// Paths - Creating paths and manipulating path data
//-----------------------------------------------------------------------------
// cairo.context#copy_path()
Gura_DeclareMethod(context, copy_path)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, copy_path)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	cairo_path_t *path = ::cairo_copy_path(cr);
	if (IsError(sig, cr)) return Value::Null;
	Value result(new Object_path(path));
	return result;
}

// cairo.context#copy_path_flat()
Gura_DeclareMethod(context, copy_path_flat)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, copy_path_flat)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	cairo_path_t *path = ::cairo_copy_path_flat(cr);
	if (IsError(sig, cr)) return Value::Null;
	Value result(new Object_path(path));
	return result;
}

// cairo.context#append_path(path:path):reduce
Gura_DeclareMethod(context, append_path)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "path", VTYPE_path);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, append_path)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	cairo_path_t *path = Object_path::GetObject(args, 0)->GetEntity();
	::cairo_append_path(cr, path);
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#has_current_point()
Gura_DeclareMethod(context, has_current_point)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, has_current_point)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	bool rtn = ::cairo_has_current_point(cr)? true : false;
	if (IsError(sig, cr)) return Value::Null;
	return Value(rtn);
}

// cairo.context#get_current_point()
Gura_DeclareMethod(context, get_current_point)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, get_current_point)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	double x, y;
	::cairo_get_current_point(cr, &x, &y);
	if (IsError(sig, cr)) return Value::Null;
	return CreateValueList(env, x, y);
}

// cairo.context#new_path():reduce
Gura_DeclareMethod(context, new_path)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, new_path)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_new_path(cr);
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#new_sub_path():reduce
Gura_DeclareMethod(context, new_sub_path)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, new_sub_path)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_new_sub_path(cr);
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#close_path():reduce
Gura_DeclareMethod(context, close_path)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, close_path)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_close_path(cr);
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#arc(xc:number, yc:number, radius:number,
//                   angle1?:number, angle2?:number):map:reduce
Gura_DeclareMethod(context, arc)
{
	SetMode(RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "xc", VTYPE_number);
	DeclareArg(env, "yc", VTYPE_number);
	DeclareArg(env, "radius", VTYPE_number);
	DeclareArg(env, "angle1", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "angle2", VTYPE_number, OCCUR_ZeroOrOnce);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, arc)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	double angle1 = args.IsNumber(3)? args.GetDouble(3) : 0;
	double angle2 = args.IsNumber(4)? args.GetDouble(4) : 2 * NUM_PI;
	::cairo_arc(cr, args.GetDouble(0), args.GetDouble(1),
										args.GetDouble(2), angle1, angle2);
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#arc_negative(xc:number, yc:number, radius:number,
//                            angle1?:number, angle2?:number):map:reduce
Gura_DeclareMethod(context, arc_negative)
{
	SetMode(RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "xc", VTYPE_number);
	DeclareArg(env, "yc", VTYPE_number);
	DeclareArg(env, "radius", VTYPE_number);
	DeclareArg(env, "angle1", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "angle2", VTYPE_number, OCCUR_ZeroOrOnce);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, arc_negative)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	double angle1 = args.IsNumber(3)? args.GetDouble(3) : 0;
	double angle2 = args.IsNumber(4)? args.GetDouble(4) : 2 * NUM_PI;
	::cairo_arc_negative(cr, args.GetDouble(0), args.GetDouble(1),
										args.GetDouble(2), angle1, angle2);
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#curve_to(x1:number, y1:number, x2:number, y2:number, x3:number, y3:number):map:reduce
Gura_DeclareMethod(context, curve_to)
{
	SetMode(RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "x1", VTYPE_number);
	DeclareArg(env, "y1", VTYPE_number);
	DeclareArg(env, "x2", VTYPE_number);
	DeclareArg(env, "y2", VTYPE_number);
	DeclareArg(env, "x3", VTYPE_number);
	DeclareArg(env, "y3", VTYPE_number);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, curve_to)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_curve_to(cr,
			args.GetDouble(0), args.GetDouble(1),
			args.GetDouble(2), args.GetDouble(3),
			args.GetDouble(4), args.GetDouble(5));
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#line_to(x:number, y:number):map:reduce
Gura_DeclareMethod(context, line_to)
{
	SetMode(RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "x", VTYPE_number);
	DeclareArg(env, "y", VTYPE_number);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, line_to)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_line_to(cr, args.GetDouble(0), args.GetDouble(1));
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#move_to(x:number, y:number):map:reduce
Gura_DeclareMethod(context, move_to)
{
	SetMode(RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "x", VTYPE_number);
	DeclareArg(env, "y", VTYPE_number);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, move_to)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_move_to(cr, args.GetDouble(0), args.GetDouble(1));
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#rectangle(x:number, y:number, width:number, height:number):map:reduce
Gura_DeclareMethod(context, rectangle)
{
	SetMode(RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "x", VTYPE_number);
	DeclareArg(env, "y", VTYPE_number);
	DeclareArg(env, "width", VTYPE_number);
	DeclareArg(env, "height", VTYPE_number);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, rectangle)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_rectangle(cr,
			args.GetDouble(0), args.GetDouble(1),
			args.GetDouble(2), args.GetDouble(3));
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#glyph_path(glyphs:cairo.glyph):reduce
Gura_DeclareMethod(context, glyph_path)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "glyphs", VTYPE_glyph);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, glyph_path)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	Object_glyph *pObjGlyph = Object_glyph::GetObject(args, 0);
	::cairo_glyph_path(cr, pObjGlyph->GetGlyphs(), pObjGlyph->GetNumGlyphs());
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#text_path(text:string):map:reduce
Gura_DeclareMethod(context, text_path)
{
	SetMode(RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "text", VTYPE_string);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, text_path)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_text_path(cr, args.GetString(0));
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#rel_curve_to(dx1:number, dy1:number, dx2:number, dy2:number, dx3:number, dy3:number):map:reduce
Gura_DeclareMethod(context, rel_curve_to)
{
	SetMode(RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "dx1", VTYPE_number);
	DeclareArg(env, "dy1", VTYPE_number);
	DeclareArg(env, "dx2", VTYPE_number);
	DeclareArg(env, "dy2", VTYPE_number);
	DeclareArg(env, "dx3", VTYPE_number);
	DeclareArg(env, "dy3", VTYPE_number);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, rel_curve_to)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_rel_curve_to(cr,
			args.GetDouble(0), args.GetDouble(1),
			args.GetDouble(2), args.GetDouble(3),
			args.GetDouble(4), args.GetDouble(5));
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#rel_line_to(dx:number, dy:number):map:reduce
Gura_DeclareMethod(context, rel_line_to)
{
	SetMode(RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "dx", VTYPE_number);
	DeclareArg(env, "dy", VTYPE_number);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, rel_line_to)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_rel_line_to(cr, args.GetDouble(0), args.GetDouble(1));
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#rel_move_to(dx:number, dy:number):map:reduce
Gura_DeclareMethod(context, rel_move_to)
{
	SetMode(RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "dx", VTYPE_number);
	DeclareArg(env, "dy", VTYPE_number);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, rel_move_to)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_rel_move_to(cr, args.GetDouble(0), args.GetDouble(1));
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#path_extents()
Gura_DeclareMethod(context, path_extents)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, path_extents)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	double x1, y1, x2, y2;
	::cairo_path_extents(cr, &x1, &y1, &x2, &y2);
	if (IsError(sig, cr)) return Value::Null;
	return CreateValueList(env, x1, y1, x2, y2);
}

//-----------------------------------------------------------------------------
// Gura interfaces for context
// Transformations - Manipulating the current transformation matrix
//-----------------------------------------------------------------------------
// cairo.context#translate(tx:number, ty:number):reduce
Gura_DeclareMethod(context, translate)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "tx", VTYPE_number);
	DeclareArg(env, "ty", VTYPE_number);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, translate)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_translate(cr, args.GetDouble(0), args.GetDouble(1));
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#scale(sx:number, sy:number):reduce
Gura_DeclareMethod(context, scale)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "sx", VTYPE_number);
	DeclareArg(env, "sy", VTYPE_number);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, scale)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_scale(cr, args.GetDouble(0), args.GetDouble(1));
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#rotate(angle:number):reduce
Gura_DeclareMethod(context, rotate)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "angle", VTYPE_number);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, rotate)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_rotate(cr, args.GetDouble(0));
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#transform(matrix:matrix):reduce
Gura_DeclareMethod(context, transform)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "matrix", VTYPE_matrix);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, transform)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	Object_matrix *pObjMatrix = Object_matrix::GetObject(args, 0);
	cairo_matrix_t matrix;
	if (!MatrixToCairo(sig, matrix, pObjMatrix->GetMatrix())) return Value::Null;
	::cairo_transform(cr, &matrix);
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#set_matrix(matrix:matrix):reduce
Gura_DeclareMethod(context, set_matrix)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "matrix", VTYPE_matrix);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, set_matrix)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	Object_matrix *pObjMatrix = Object_matrix::GetObject(args, 0);
	cairo_matrix_t matrix;
	if (!MatrixToCairo(sig, matrix, pObjMatrix->GetMatrix())) return Value::Null;
	::cairo_set_matrix(cr, &matrix);
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#get_matrix()
Gura_DeclareMethod(context, get_matrix)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, get_matrix)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	cairo_matrix_t matrix;
	::cairo_get_matrix(cr, &matrix);
	if (IsError(sig, cr)) return Value::Null;
	AutoPtr<Matrix> pMat(CairoToMatrix(env, matrix));
	return Value(new Object_matrix(env, pMat.release()));
}

// cairo.context#identity_matrix():reduce
Gura_DeclareMethod(context, identity_matrix)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, identity_matrix)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_identity_matrix(cr);
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#user_to_device(x:number, y:number)
Gura_DeclareMethod(context, user_to_device)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "x", VTYPE_number);
	DeclareArg(env, "y", VTYPE_number);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, user_to_device)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	double x = args.GetDouble(0);
	double y = args.GetDouble(1);
	::cairo_user_to_device(cr, &x, &y);
	if (IsError(sig, cr)) return Value::Null;
	return CreateValueList(env, x, y);
}

// cairo.context#user_to_device_distance(dx:number, dy:number)
Gura_DeclareMethod(context, user_to_device_distance)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "dx", VTYPE_number);
	DeclareArg(env, "dy", VTYPE_number);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, user_to_device_distance)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	double dx = args.GetDouble(0);
	double dy = args.GetDouble(1);
	::cairo_user_to_device_distance(cr, &dx, &dy);
	if (IsError(sig, cr)) return Value::Null;
	return CreateValueList(env, dx, dy);
}

// cairo.context#device_to_user(x:number, y:number)
Gura_DeclareMethod(context, device_to_user)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "x", VTYPE_number);
	DeclareArg(env, "y", VTYPE_number);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, device_to_user)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	double x = args.GetDouble(0);
	double y = args.GetDouble(1);
	::cairo_device_to_user(cr, &x, &y);
	if (IsError(sig, cr)) return Value::Null;
	return CreateValueList(env, x, y);
}

// cairo.context#device_to_user_distance(dx:number, dy:number)
Gura_DeclareMethod(context, device_to_user_distance)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "dx", VTYPE_number);
	DeclareArg(env, "dy", VTYPE_number);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, device_to_user_distance)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	double dx = args.GetDouble(0);
	double dy = args.GetDouble(1);
	::cairo_device_to_user_distance(cr, &dx, &dy);
	if (IsError(sig, cr)) return Value::Null;
	return CreateValueList(env, dx, dy);
}

//-----------------------------------------------------------------------------
// Gura interfaces for context
// text - Rendering text and glyphs
//-----------------------------------------------------------------------------
// cairo.context#select_font_face(family:string, slant:number, weight:number):reduce
Gura_DeclareMethod(context, select_font_face)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "family", VTYPE_string);
	DeclareArg(env, "slant", VTYPE_number);
	DeclareArg(env, "weight", VTYPE_number);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, select_font_face)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	const char *family = args.GetString(0);
	cairo_font_slant_t slant = static_cast<cairo_font_slant_t>(args.GetInt(1));
	if (sig.IsSignalled()) return Value::Null;
	cairo_font_weight_t weight = static_cast<cairo_font_weight_t>(args.GetInt(2));
	if (sig.IsSignalled()) return Value::Null;
	::cairo_select_font_face(cr, family, slant, weight);
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#set_font_size(size:number):reduce
Gura_DeclareMethod(context, set_font_size)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "size", VTYPE_number);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, set_font_size)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_set_font_size(cr, args.GetDouble(0));
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#set_font_matrix(matrix:matrix):reduce
Gura_DeclareMethod(context, set_font_matrix)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "matrix", VTYPE_matrix);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, set_font_matrix)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	Object_matrix *pObjMatrix = Object_matrix::GetObject(args, 0);
	cairo_matrix_t matrix;
	if (!MatrixToCairo(sig, matrix, pObjMatrix->GetMatrix())) return Value::Null;
	::cairo_set_font_matrix(cr, &matrix);
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#get_font_matrix()
Gura_DeclareMethod(context, get_font_matrix)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, get_font_matrix)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	cairo_matrix_t matrix;
	::cairo_get_font_matrix(cr, &matrix);
	if (IsError(sig, cr)) return Value::Null;
	AutoPtr<Matrix> pMat(CairoToMatrix(env, matrix));
	return Value(new Object_matrix(env, pMat.release()));
}

// cairo.context#set_font_options(options:cairo.font_options):reduce
Gura_DeclareMethod(context, set_font_options)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "options", VTYPE_font_options);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, set_font_options)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_set_font_options(cr,
				Object_font_options::GetObject(args, 0)->GetEntity());
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#get_font_options()
Gura_DeclareMethod(context, get_font_options)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, get_font_options)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	cairo_font_options_t *options = ::cairo_font_options_create();
	::cairo_get_font_options(cr, options);
	if (IsError(sig, cr)) {
		::cairo_font_options_destroy(options);
		return Value::Null;
	}
	Object_font_options *pObjFontOptions = new Object_font_options(options);
	return Value(pObjFontOptions);
}

// cairo.context#set_font_face(font_face:cairo.font_face):reduce
Gura_DeclareMethod(context, set_font_face)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "font_face", VTYPE_font_face);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, set_font_face)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_set_font_face(cr,
				Object_font_face::GetObject(args, 0)->GetEntity());
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#get_font_face()
Gura_DeclareMethod(context, get_font_face)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, get_font_face)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	cairo_font_face_t *font_face = ::cairo_get_font_face(cr);
	if (IsError(sig, cr)) {
		return Value::Null;
	}
	Object_font_face *pObjFontFace = new Object_font_face(::cairo_font_face_reference(font_face));
	return Value(pObjFontFace);
}

// cairo.context#set_scaled_font(scaled_font:cairo.scaled_font):reduce
Gura_DeclareMethod(context, set_scaled_font)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "scaled_font", VTYPE_scaled_font);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, set_scaled_font)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_set_scaled_font(cr,
				Object_scaled_font::GetObject(args, 0)->GetEntity());
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#get_scaled_font()
Gura_DeclareMethod(context, get_scaled_font)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, get_scaled_font)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	cairo_scaled_font_t *scaled_font = ::cairo_get_scaled_font(cr);
	if (IsError(sig, cr)) {
		return Value::Null;
	}
	Object_scaled_font *pObjFontFace = new Object_scaled_font(::cairo_scaled_font_reference(scaled_font));
	return Value(pObjFontFace);
}

// cairo.context#show_text(text:string):reduce
Gura_DeclareMethod(context, show_text)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "text", VTYPE_string);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, show_text)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	::cairo_show_text(cr, args.GetString(0));
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#show_glyphs(glyphs:cairo.glyph):reduce
Gura_DeclareMethod(context, show_glyphs)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "glyphs", VTYPE_glyph);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, show_glyphs)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	Object_glyph *pObjGlyph = Object_glyph::GetObject(args, 0);
	::cairo_show_glyphs(cr, pObjGlyph->GetGlyphs(), pObjGlyph->GetNumGlyphs());
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#show_text_glyphs(text:string, glyphs:cairo.glyphs,
//              clusters:cairo.text_cluster, cluster_flags:number):reduce
Gura_DeclareMethod(context, show_text_glyphs)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "text", VTYPE_string);
	DeclareArg(env, "glyphs", VTYPE_glyph);
	DeclareArg(env, "clusters", VTYPE_text_cluster);
	DeclareArg(env, "cluster_flags", VTYPE_number);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, show_text_glyphs)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	String text = args.GetStringSTL(0);
	Object_glyph *pObjGlyph = Object_glyph::GetObject(args, 1);
	Object_text_cluster *pObjCluster = Object_text_cluster::GetObject(args, 2);
	cairo_text_cluster_flags_t cluster_flags =
					static_cast<cairo_text_cluster_flags_t>(args.GetInt(3));
	::cairo_show_text_glyphs(cr, text.c_str(), static_cast<int>(text.size()),
		pObjGlyph->GetGlyphs(), pObjGlyph->GetNumGlyphs(),
		pObjCluster->GetClusters(), pObjCluster->GetNumClusters(), cluster_flags);
	if (IsError(sig, cr)) return Value::Null;
	return args.GetThis();
}

// cairo.context#font_extents()
Gura_DeclareMethod(context, font_extents)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, font_extents)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	cairo_font_extents_t extents;
	::cairo_font_extents(cr, &extents);
	if (IsError(sig, cr)) return Value::Null;
	Object_font_extents *pObjFontExtents = new Object_font_extents(extents);
	return Value(pObjFontExtents);
}

// cairo.context#text_extents(text:string)
Gura_DeclareMethod(context, text_extents)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "text", VTYPE_string);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, text_extents)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	cairo_text_extents_t extents;
	::cairo_text_extents(cr, args.GetString(0), &extents);
	if (IsError(sig, cr)) return Value::Null;
	Object_text_extents *pObjTextExtents = new Object_text_extents(extents);
	return Value(pObjTextExtents);
}

// cairo.context#glyph_extents(glyphs:cairo.glyph)
Gura_DeclareMethod(context, glyph_extents)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "glyphs", VTYPE_glyph);
	AddHelp(Gura_Symbol(en),
	""
	);
}

Gura_ImplementMethod(context, glyph_extents)
{
	Object_context *pThis = Object_context::GetThisObj(args);
	cairo_t *cr = pThis->GetEntity();
	if (IsInvalid(sig, cr)) return Value::Null;
	Object_glyph *pObjGlyph = Object_glyph::GetObject(args, 0);
	cairo_text_extents_t extents;
	::cairo_glyph_extents(cr, pObjGlyph->GetGlyphs(), pObjGlyph->GetNumGlyphs(), &extents);
	if (IsError(sig, cr)) return Value::Null;
	Object_text_extents *pObjTextExtents = new Object_text_extents(extents);
	return Value(pObjTextExtents);
}

// implementation of class Context
Gura_ImplementUserClass(context)
{
	// Context operations
	Gura_AssignMethod(context, status);
	Gura_AssignMethod(context, destroy);
	Gura_AssignMethod(context, save);
	Gura_AssignMethod(context, restore);
	Gura_AssignMethod(context, get_target);
	Gura_AssignMethod(context, push_group);
	Gura_AssignMethod(context, push_group_with_content);
	Gura_AssignMethod(context, pop_group);
	Gura_AssignMethod(context, pop_group_to_source);
	Gura_AssignMethod(context, get_group_target);
	Gura_AssignMethod(context, set_source_rgb);
	Gura_AssignMethod(context, set_source_rgba);
	Gura_AssignMethod(context, set_source_color);
	Gura_AssignMethod(context, set_source);
	Gura_AssignMethod(context, set_source_surface);
	Gura_AssignMethod(context, get_source);
	Gura_AssignMethod(context, set_antialias);
	Gura_AssignMethod(context, get_antialias);
	Gura_AssignMethod(context, set_dash);
	Gura_AssignMethod(context, get_dash);
	Gura_AssignMethod(context, set_fill_rule);
	Gura_AssignMethod(context, get_fill_rule);
	Gura_AssignMethod(context, set_line_cap);
	Gura_AssignMethod(context, get_line_cap);
	Gura_AssignMethod(context, set_line_join);
	Gura_AssignMethod(context, get_line_join);
	Gura_AssignMethod(context, set_line_width);
	Gura_AssignMethod(context, get_line_width);
	Gura_AssignMethod(context, set_miter_limit);
	Gura_AssignMethod(context, get_miter_limit);
	Gura_AssignMethod(context, set_operator);
	Gura_AssignMethod(context, get_operator);
	Gura_AssignMethod(context, set_tolerance);
	Gura_AssignMethod(context, get_tolerance);
	Gura_AssignMethod(context, clip);
	Gura_AssignMethod(context, clip_preserve);
	Gura_AssignMethod(context, clip_extents);
	Gura_AssignMethod(context, in_clip);
	Gura_AssignMethod(context, reset_clip);
	Gura_AssignMethod(context, copy_clip_rectangle_list);
	Gura_AssignMethod(context, fill);
	Gura_AssignMethod(context, fill_preserve);
	Gura_AssignMethod(context, fill_extents);
	Gura_AssignMethod(context, in_fill);
	Gura_AssignMethod(context, mask);
	Gura_AssignMethod(context, mask_surface);
	Gura_AssignMethod(context, paint);
	Gura_AssignMethod(context, paint_with_alpha);
	Gura_AssignMethod(context, stroke);
	Gura_AssignMethod(context, stroke_preserve);
	Gura_AssignMethod(context, stroke_extents);
	Gura_AssignMethod(context, in_stroke);
	Gura_AssignMethod(context, copy_page);
	Gura_AssignMethod(context, show_page);
	// Paths - Creating paths and manipulating path data
	Gura_AssignMethod(context, copy_path);
	Gura_AssignMethod(context, copy_path_flat);
	Gura_AssignMethod(context, append_path);
	Gura_AssignMethod(context, has_current_point);
	Gura_AssignMethod(context, get_current_point);
	Gura_AssignMethod(context, new_path);
	Gura_AssignMethod(context, new_sub_path);
	Gura_AssignMethod(context, close_path);
	Gura_AssignMethod(context, arc);
	Gura_AssignMethod(context, arc_negative);
	Gura_AssignMethod(context, curve_to);
	Gura_AssignMethod(context, line_to);
	Gura_AssignMethod(context, move_to);
	Gura_AssignMethod(context, rectangle);
	Gura_AssignMethod(context, text_path);
	Gura_AssignMethod(context, rel_curve_to);
	Gura_AssignMethod(context, rel_line_to);
	Gura_AssignMethod(context, rel_move_to);
	Gura_AssignMethod(context, path_extents);
	// Transformations - Manipulating the current transformation matrix
	Gura_AssignMethod(context, translate);
	Gura_AssignMethod(context, scale);
	Gura_AssignMethod(context, rotate);
	Gura_AssignMethod(context, transform);
	Gura_AssignMethod(context, set_matrix);
	Gura_AssignMethod(context, get_matrix);
	Gura_AssignMethod(context, identity_matrix);
	Gura_AssignMethod(context, user_to_device);
	Gura_AssignMethod(context, user_to_device_distance);
	Gura_AssignMethod(context, device_to_user);
	Gura_AssignMethod(context, device_to_user_distance);
	// text - Rendering text and glyphs
	Gura_AssignMethod(context, select_font_face);
	Gura_AssignMethod(context, set_font_size);
	Gura_AssignMethod(context, set_font_matrix);
	Gura_AssignMethod(context, get_font_matrix);
	Gura_AssignMethod(context, set_font_options);
	Gura_AssignMethod(context, get_font_options);
	Gura_AssignMethod(context, set_font_face);
	Gura_AssignMethod(context, get_font_face);
	Gura_AssignMethod(context, set_scaled_font);
	Gura_AssignMethod(context, get_scaled_font);
	Gura_AssignMethod(context, show_text);
	Gura_AssignMethod(context, show_glyphs);
	Gura_AssignMethod(context, show_text_glyphs);
	Gura_AssignMethod(context, font_extents);
	Gura_AssignMethod(context, text_extents);
	Gura_AssignMethod(context, glyph_extents);
}

}}
