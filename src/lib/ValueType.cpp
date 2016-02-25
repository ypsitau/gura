//=============================================================================
// ValueType
//=============================================================================
#include "stdafx.h"

namespace Gura {

//-----------------------------------------------------------------------------
// Built-in Value Types
//-----------------------------------------------------------------------------
// invalid types
ValueType VTYPE_undefined		= static_cast<ValueType>(0);	// dumb copiable
ValueType VTYPE_nil				= static_cast<ValueType>(1);	// dumb copiable
// pseudo types
ValueType VTYPE_quote			= static_cast<ValueType>(2);	// dumb copiable
ValueType VTYPE_any				= static_cast<ValueType>(3);	// dumb copiable
// primitive types
ValueType VTYPE_boolean			= static_cast<ValueType>(4);	// dumb copiable
ValueType VTYPE_number			= static_cast<ValueType>(5);	// dumb copiable
ValueType VTYPE_symbol			= static_cast<ValueType>(6);	// dumb copiable
ValueType VTYPE_string			= static_cast<ValueType>(7);
ValueType VTYPE_complex			= static_cast<ValueType>(8);
ValueType VTYPE_rational		= static_cast<ValueType>(9);
// container types
ValueType VTYPE_Module			= static_cast<ValueType>(0);
ValueType VTYPE_Class			= static_cast<ValueType>(0);
ValueType VTYPE_Struct			= static_cast<ValueType>(0);
// object types
ValueType VTYPE_object			= static_cast<ValueType>(0);
ValueType VTYPE_argument		= static_cast<ValueType>(0);
ValueType VTYPE_array_char		= static_cast<ValueType>(0);
ValueType VTYPE_array_uchar		= static_cast<ValueType>(0);
ValueType VTYPE_array_short		= static_cast<ValueType>(0);
ValueType VTYPE_array_ushort	= static_cast<ValueType>(0);
ValueType VTYPE_array_int		= static_cast<ValueType>(0);
ValueType VTYPE_array_uint		= static_cast<ValueType>(0);
ValueType VTYPE_array_int32		= static_cast<ValueType>(0);
ValueType VTYPE_array_uint32	= static_cast<ValueType>(0);
ValueType VTYPE_array_int64		= static_cast<ValueType>(0);
ValueType VTYPE_array_uint64	= static_cast<ValueType>(0);
ValueType VTYPE_array_float		= static_cast<ValueType>(0);
ValueType VTYPE_array_double	= static_cast<ValueType>(0);
ValueType VTYPE_audio			= static_cast<ValueType>(0);
ValueType VTYPE_binary			= static_cast<ValueType>(0);
ValueType VTYPE_codec			= static_cast<ValueType>(0);
ValueType VTYPE_color			= static_cast<ValueType>(0);
ValueType VTYPE_datetime		= static_cast<ValueType>(0);
ValueType VTYPE_declaration		= static_cast<ValueType>(0);
ValueType VTYPE_dict			= static_cast<ValueType>(0);
ValueType VTYPE_directory		= static_cast<ValueType>(0);
ValueType VTYPE_environment		= static_cast<ValueType>(0);
ValueType VTYPE_error			= static_cast<ValueType>(0);
ValueType VTYPE_expr			= static_cast<ValueType>(0);
ValueType VTYPE_formatter		= static_cast<ValueType>(0);
ValueType VTYPE_function		= static_cast<ValueType>(0);
ValueType VTYPE_help			= static_cast<ValueType>(0);
ValueType VTYPE_image			= static_cast<ValueType>(0);
ValueType VTYPE_iterator		= static_cast<ValueType>(0);
ValueType VTYPE_list			= static_cast<ValueType>(0);
ValueType VTYPE_matrix			= static_cast<ValueType>(0);
ValueType VTYPE_memory			= static_cast<ValueType>(0);
ValueType VTYPE_monitor			= static_cast<ValueType>(0);
ValueType VTYPE_operator		= static_cast<ValueType>(0);
ValueType VTYPE_palette			= static_cast<ValueType>(0);
ValueType VTYPE_pointer			= static_cast<ValueType>(0);
ValueType VTYPE_semaphore		= static_cast<ValueType>(0);
ValueType VTYPE_stream			= static_cast<ValueType>(0);
ValueType VTYPE_suffixmgr		= static_cast<ValueType>(0);
ValueType VTYPE_template		= static_cast<ValueType>(0);
ValueType VTYPE_timedelta		= static_cast<ValueType>(0);
ValueType VTYPE_uri				= static_cast<ValueType>(0);
ValueType VTYPE_vertex			= static_cast<ValueType>(0);

//-----------------------------------------------------------------------------
// ValueTypeInfo
//-----------------------------------------------------------------------------
ValueTypeInfo::~ValueTypeInfo()
{
	Class::Delete(_pClass);
}

void ValueTypeInfo::SetClass(Class *pClass)
{
	_pClass = pClass;
	pClass->SetSymbol(_pSymbol);
	pClass->SetValueType(_valType);
}

String ValueTypeInfo::MakeFullName() const
{
	String rtn;
	if (_pModule != nullptr) {
		rtn += _pModule->GetName();
		rtn += ".";
	}
	rtn += _pSymbol->GetName();
	return rtn;
}

Expr *ValueTypeInfo::MakeExpr() const
{
	if (_pModule == nullptr) {
		return new Expr_Identifier(_pSymbol);
	}
	return new Expr_Member(_pModule->MakeExpr(), new Expr_Identifier(_pSymbol));
}

//-----------------------------------------------------------------------------
// ValueTypeMap
//-----------------------------------------------------------------------------
const ValueTypeMap ValueTypeMap::Empty;

//-----------------------------------------------------------------------------
// ValueTypePool
//-----------------------------------------------------------------------------
ValueTypePool *ValueTypePool::_pInst = nullptr;

ValueTypePool::~ValueTypePool()
{
	foreach (ValueTypeList, ppValueTypeInfo, _valueTypeList) {
		ValueTypeInfo::Delete(*ppValueTypeInfo);
	}
}

void ValueTypePool::Initialize(Environment &env)
{
	if (_pInst == nullptr) {
		_pInst = new ValueTypePool();
		_pInst->_Initialize(env);
	}
}

void ValueTypePool::_Initialize(Environment &env)
{
	// primitive types. This order is significant for the following methods:
	// - Value::IsInvalid()
	// - Value::IsValid()
	// - Value::IsPrimitive()
	// - Value::IsFundamental()
	// - Value::IsObject()
	// invalid types
	Gura_RealizeVTYPE(undefined);							// must be at 1st
	Gura_RealizeVTYPE(nil);									// must be at 2nd
	// pseudo types
	Gura_RealizeVTYPE(quote);								// must be at 3rd
	Gura_RealizeVTYPE(any);									// must be at 4th
	// primitive types
	Gura_RealizeVTYPE(boolean);								// must be at 5th
	Gura_RealizeVTYPE(number);								// must be at 6th
	Gura_RealizeVTYPE(symbol);								// must be at 7th
	Gura_RealizeVTYPE(string);								// must be at 8th
	Gura_RealizeVTYPE(complex);								// must be at 9th
	Gura_RealizeVTYPE(rational);							// must be at 10th
	// container types
	Gura_RealizeVTYPEAlias(Module,			"module");		// must be at 11th
	Gura_RealizeVTYPEAlias(Class,			"class");		// must be at 12th
	// object types
	Gura_RealizeVTYPE(object);								// must be at 13th
	Gura_RealizeVTYPEAlias(Struct,			"struct");
	Gura_RealizeVTYPE(argument);
	Gura_RealizeVTYPEAlias(array_char,		"array@char");
	Gura_RealizeVTYPEAlias(array_uchar,		"array@uchar");
	Gura_RealizeVTYPEAlias(array_short,		"array@short");
	Gura_RealizeVTYPEAlias(array_ushort,	"array@ushort");
	Gura_RealizeVTYPEAlias(array_int,		"array@int");
	Gura_RealizeVTYPEAlias(array_uint,		"array@uint");
	Gura_RealizeVTYPEAlias(array_int32,		"array@int32");
	Gura_RealizeVTYPEAlias(array_uint32,	"array@uint32");
	Gura_RealizeVTYPEAlias(array_int64,		"array@int64");
	Gura_RealizeVTYPEAlias(array_uint64,	"array@uint64");
	Gura_RealizeVTYPEAlias(array_float,		"array@float");
   	Gura_RealizeVTYPEAlias(array_double,	"array@double");
	Gura_RealizeVTYPE(audio);
	Gura_RealizeVTYPE(binary);
	Gura_RealizeVTYPE(codec);
	Gura_RealizeVTYPE(color);
	Gura_RealizeVTYPE(datetime);
	Gura_RealizeVTYPE(declaration);
	Gura_RealizeVTYPE(dict);
	Gura_RealizeVTYPE(directory);
	Gura_RealizeVTYPE(environment);
	Gura_RealizeVTYPE(error);
	Gura_RealizeVTYPE(expr);
	Gura_RealizeVTYPE(formatter);
	Gura_RealizeVTYPE(function);
	Gura_RealizeVTYPE(help);
	Gura_RealizeVTYPE(image);
	Gura_RealizeVTYPE(iterator);
	Gura_RealizeVTYPE(list);
	Gura_RealizeVTYPE(matrix);
	Gura_RealizeVTYPE(memory);
	Gura_RealizeVTYPE(monitor);
	Gura_RealizeVTYPE(operator);
	Gura_RealizeVTYPE(palette);
	Gura_RealizeVTYPE(pointer);
	Gura_RealizeVTYPE(semaphore);
	Gura_RealizeVTYPE(stream);
	Gura_RealizeVTYPE(suffixmgr);
	Gura_RealizeVTYPE(template);
	Gura_RealizeVTYPE(timedelta);
	Gura_RealizeVTYPE(uri);
	Gura_RealizeVTYPE(vertex);
	Class *pClass = new Class(&env, VTYPE_object);
	Gura_VTYPEInfo(object		)->SetClass(pClass);
	// invalid types
	Gura_VTYPEInfo(undefined	)->SetClass(new Class_undefined(pClass));
	Gura_VTYPEInfo(nil			)->SetClass(new Class_nil(pClass));
	// pseudo types
	Gura_VTYPEInfo(quote		)->SetClass(new Class_quote(pClass));
	Gura_VTYPEInfo(any			)->SetClass(new Class_any(pClass));
	// primitive types
	Gura_VTYPEInfo(boolean		)->SetClass(new Class_boolean(pClass));
	Gura_VTYPEInfo(number		)->SetClass(new Class_number(pClass));
	Gura_VTYPEInfo(symbol		)->SetClass(new Class_symbol(pClass));
	Gura_VTYPEInfo(string		)->SetClass(new Class_string(pClass));
	Gura_VTYPEInfo(complex		)->SetClass(new Class_complex(pClass));
	Gura_VTYPEInfo(rational		)->SetClass(new Class_rational(pClass));
	// container types
	Gura_VTYPEInfo(Module		)->SetClass(new Class_Module(pClass));
	Gura_VTYPEInfo(Class		)->SetClass(new Class_Class(pClass));
	// object types
	Gura_VTYPEInfo(Struct		)->SetClass(new Class_Struct(pClass));
	Gura_VTYPEInfo(argument		)->SetClass(new Class_argument(pClass));
	Gura_VTYPEInfo(array_char	)->SetClass(
		new Class_array<Char>(pClass, VTYPE_array_char, "char"));
	Gura_VTYPEInfo(array_uchar	)->SetClass(
		new Class_array<UChar>(pClass, VTYPE_array_uchar, "uchar"));
	Gura_VTYPEInfo(array_short	)->SetClass(
		new Class_array<Short>(pClass, VTYPE_array_short, "short"));
	Gura_VTYPEInfo(array_ushort	)->SetClass(
		new Class_array<UShort>(pClass, VTYPE_array_ushort, "ushort"));
	Gura_VTYPEInfo(array_int	)->SetClass(
		new Class_array<Int>(pClass, VTYPE_array_int, "int"));
	Gura_VTYPEInfo(array_uint	)->SetClass(
		new Class_array<UInt>(pClass, VTYPE_array_uint, "uint"));
	Gura_VTYPEInfo(array_uint32	)->SetClass(
		new Class_array<UInt32>(pClass, VTYPE_array_uint32, "uint32"));
	Gura_VTYPEInfo(array_int32	)->SetClass(
		new Class_array<Int32>(pClass, VTYPE_array_int32, "int32"));
	Gura_VTYPEInfo(array_uint32	)->SetClass(
		new Class_array<UInt32>(pClass, VTYPE_array_uint32, "uint32"));
	Gura_VTYPEInfo(array_int64	)->SetClass(
		new Class_array<Int64>(pClass, VTYPE_array_int64, "int64"));
	Gura_VTYPEInfo(array_uint64	)->SetClass(
		new Class_array<UInt64>(pClass, VTYPE_array_uint64, "uint64"));
	Gura_VTYPEInfo(array_float	)->SetClass(
		new Class_array<float>(pClass, VTYPE_array_float, "float"));
	Gura_VTYPEInfo(array_double	)->SetClass(
		new Class_array<double>(pClass, VTYPE_array_double, "double"));
	Gura_VTYPEInfo(audio		)->SetClass(new Class_audio(pClass));
	Gura_VTYPEInfo(binary		)->SetClass(new Class_binary(pClass));
	Gura_VTYPEInfo(codec		)->SetClass(new Class_codec(pClass));
	Gura_VTYPEInfo(color		)->SetClass(new Class_color(pClass));
	Gura_VTYPEInfo(datetime		)->SetClass(new Class_datetime(pClass));
	Gura_VTYPEInfo(declaration	)->SetClass(new Class_declaration(pClass));
	Gura_VTYPEInfo(dict			)->SetClass(new Class_dict(pClass));
	Gura_VTYPEInfo(directory	)->SetClass(new Class_directory(pClass));
	Gura_VTYPEInfo(environment	)->SetClass(new Class_environment(pClass));
	Gura_VTYPEInfo(error		)->SetClass(new Class_error(pClass));
	Gura_VTYPEInfo(expr			)->SetClass(new Class_expr(pClass));
	Gura_VTYPEInfo(formatter	)->SetClass(new Class_formatter(pClass));
	Gura_VTYPEInfo(function		)->SetClass(new Class_function(pClass));
	Gura_VTYPEInfo(help			)->SetClass(new Class_help(pClass));
	Gura_VTYPEInfo(image		)->SetClass(new Class_image(pClass));
	Gura_VTYPEInfo(iterator		)->SetClass(new Class_iterator(pClass));
	Gura_VTYPEInfo(list			)->SetClass(new Class_list(pClass));
	Gura_VTYPEInfo(matrix		)->SetClass(new Class_matrix(pClass));
	Gura_VTYPEInfo(memory		)->SetClass(new Class_memory(pClass));
	Gura_VTYPEInfo(monitor		)->SetClass(new Class_monitor(pClass));
	Gura_VTYPEInfo(operator		)->SetClass(new Class_operator(pClass));
	Gura_VTYPEInfo(palette		)->SetClass(new Class_palette(pClass));
	Gura_VTYPEInfo(pointer		)->SetClass(new Class_pointer(pClass));
	Gura_VTYPEInfo(semaphore	)->SetClass(new Class_semaphore(pClass));
	Gura_VTYPEInfo(stream		)->SetClass(new Class_stream(pClass));
	Gura_VTYPEInfo(suffixmgr	)->SetClass(new Class_suffixmgr(pClass));
	Gura_VTYPEInfo(template		)->SetClass(new Class_template(pClass));
	Gura_VTYPEInfo(timedelta	)->SetClass(new Class_timedelta(pClass));
	Gura_VTYPEInfo(uri			)->SetClass(new Class_uri(pClass));
	Gura_VTYPEInfo(vertex		)->SetClass(new Class_vertex(pClass));
	pClass->Prepare(env); // methods of Object can only be initialized here
}

void ValueTypePool::DoPrepareClass(Environment &env)
{
	// invalid types
	env.LookupClass(VTYPE_undefined		)->Prepare(env);
	env.LookupClass(VTYPE_nil			)->Prepare(env);
	// pseudo types
	env.LookupClass(VTYPE_quote			)->Prepare(env);
	env.LookupClass(VTYPE_any			)->Prepare(env);
	// primitive types
	env.LookupClass(VTYPE_boolean		)->Prepare(env);
	env.LookupClass(VTYPE_number		)->Prepare(env);
	env.LookupClass(VTYPE_symbol		)->Prepare(env);
	env.LookupClass(VTYPE_string		)->Prepare(env);
	env.LookupClass(VTYPE_complex		)->Prepare(env);
	env.LookupClass(VTYPE_rational		)->Prepare(env);
	// container types
	env.LookupClass(VTYPE_Module		)->Prepare(env);
	env.LookupClass(VTYPE_Class			)->Prepare(env);
	env.LookupClass(VTYPE_Struct		)->Prepare(env);
	// object types
	env.LookupClass(VTYPE_argument		)->Prepare(env);
	env.LookupClass(VTYPE_array_char	)->Prepare(env);
	env.LookupClass(VTYPE_array_uchar	)->Prepare(env);
	env.LookupClass(VTYPE_array_short	)->Prepare(env);
	env.LookupClass(VTYPE_array_ushort	)->Prepare(env);
	env.LookupClass(VTYPE_array_int		)->Prepare(env);
	env.LookupClass(VTYPE_array_uint	)->Prepare(env);
	env.LookupClass(VTYPE_array_int32	)->Prepare(env);
	env.LookupClass(VTYPE_array_uint32	)->Prepare(env);
	env.LookupClass(VTYPE_array_int64	)->Prepare(env);
	env.LookupClass(VTYPE_array_uint64	)->Prepare(env);
	env.LookupClass(VTYPE_array_float	)->Prepare(env);
	env.LookupClass(VTYPE_array_double	)->Prepare(env);
	env.LookupClass(VTYPE_audio			)->Prepare(env);
	env.LookupClass(VTYPE_binary		)->Prepare(env);
	env.LookupClass(VTYPE_codec			)->Prepare(env);
	env.LookupClass(VTYPE_color			)->Prepare(env);
	env.LookupClass(VTYPE_datetime		)->Prepare(env);
	env.LookupClass(VTYPE_declaration	)->Prepare(env);
	env.LookupClass(VTYPE_dict			)->Prepare(env);
	env.LookupClass(VTYPE_directory		)->Prepare(env);
	env.LookupClass(VTYPE_environment	)->Prepare(env);
	env.LookupClass(VTYPE_error			)->Prepare(env);
	env.LookupClass(VTYPE_expr			)->Prepare(env);
	env.LookupClass(VTYPE_formatter		)->Prepare(env);
	env.LookupClass(VTYPE_function		)->Prepare(env);
	env.LookupClass(VTYPE_help			)->Prepare(env);
	env.LookupClass(VTYPE_image			)->Prepare(env);
	env.LookupClass(VTYPE_iterator		)->Prepare(env);
	env.LookupClass(VTYPE_list			)->Prepare(env);
	env.LookupClass(VTYPE_matrix		)->Prepare(env);
	env.LookupClass(VTYPE_memory		)->Prepare(env);
	env.LookupClass(VTYPE_monitor		)->Prepare(env);
	env.LookupClass(VTYPE_operator		)->Prepare(env);
	env.LookupClass(VTYPE_palette		)->Prepare(env);
	env.LookupClass(VTYPE_pointer		)->Prepare(env);
	env.LookupClass(VTYPE_semaphore		)->Prepare(env);
	env.LookupClass(VTYPE_stream		)->Prepare(env);
	env.LookupClass(VTYPE_suffixmgr		)->Prepare(env);
	env.LookupClass(VTYPE_template		)->Prepare(env);
	env.LookupClass(VTYPE_timedelta		)->Prepare(env);
	env.LookupClass(VTYPE_uri			)->Prepare(env);
	env.LookupClass(VTYPE_vertex		)->Prepare(env);
}

ValueTypeInfo *ValueTypePool::Add(const Symbol *pSymbol)
{
	ValueType valType = static_cast<ValueType>(_valueTypeList.size());
	ValueTypeInfo *pValTypeInfo = new ValueTypeInfo(valType, pSymbol, nullptr);
	_valueTypeList.push_back(pValTypeInfo);
	return pValTypeInfo;
}

ValueTypeInfo *ValueTypePool::Lookup(ValueType valType)
{
	return _valueTypeList[valType];
}

ValueTypeInfo *ValueTypePool::LookupWithCheck(ValueType valType)
{
	if (valType >= _valueTypeList.size()) return nullptr;
	return _valueTypeList[valType];
}

ValueTypePool *ValueTypePool::GetInstance()
{
	return _pInst;
}

}
