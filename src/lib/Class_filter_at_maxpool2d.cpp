//=============================================================================
// Gura class: filter@maxpool2d
//=============================================================================
#include "stdafx.h"

namespace Gura {

static const char *helpDoc_en = R"**(
)**";

//-----------------------------------------------------------------------------
// Filter_MaxPool2d
//-----------------------------------------------------------------------------
Filter_MaxPool2d::FilterFuncTable Filter_MaxPool2d::filterFuncTable = {{nullptr}};

Array *Filter_MaxPool2d::Apply(Signal &sig, Array *pArrayResult, const Array *pArray)
{
	FilterFuncT filterFunc = filterFuncTable.funcs[pArray->GetElemType()];
	if (filterFunc == nullptr) {
		sig.SetError(ERR_TypeError, "can't apply 2-dimension max pool filter on array@%s",
					 pArray->GetElemTypeName());
		return nullptr;
	}
	return (*filterFunc)(sig, pArrayResult, pArray, *this);
}

//-----------------------------------------------------------------------------
// Object_filter_at_maxpool2d
//-----------------------------------------------------------------------------
Object_filter_at_maxpool2d::Object_filter_at_maxpool2d(Environment &env, Filter_MaxPool2d *pFilter) :
	Object_filter(env.LookupClass(VTYPE_filter_at_maxpool2d), pFilter)
{
}

Object *Object_filter_at_maxpool2d::Clone() const
{
	return nullptr;
}
	
String Object_filter_at_maxpool2d::ToString(bool exprFlag)
{
	String str;
	str += "<filter@maxpool2d:";
	str += ">";
	return str;
}

//-----------------------------------------------------------------------------
// Implementation of functions
//-----------------------------------------------------------------------------
// filter@maxpool2d(size[]:number, strides[]?:number, padding?:symbol, channel_at?:symbol):map {block?}
Gura_DeclareFunctionAlias(filter_at_maxpool2d, "filter@maxpool2d")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "size", VTYPE_number, OCCUR_Once, FLAG_ListVar);
	DeclareArg(env, "strides", VTYPE_number, OCCUR_ZeroOrOnce, FLAG_ListVar);
	DeclareArg(env, "padding", VTYPE_symbol, OCCUR_ZeroOrOnce);
	DeclareArg(env, "channel_at", VTYPE_symbol, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
	SetClassToConstruct(env.LookupClass(VTYPE_filter_at_maxpool2d));
	AddHelp(
		Gura_Symbol(en),
		"Creates a `filter@maxpool2d` instance.\n");
}

Gura_ImplementFunction(filter_at_maxpool2d)
{
	size_t sizeRow = 0;
	size_t sizeCol = 0;
	do {
		const ValueList &valList = arg.GetList(0);
		if (valList.size() != 2) {
			env.SetError(ERR_ValueError, "size must have two elements");
			return Value::Nil;
		}
		sizeRow = valList[0].GetSizeT();
		sizeCol = valList[1].GetSizeT();
	} while (0);
	size_t stridesRow = 1;
	size_t stridesCol = 1;
	if (arg.IsValid(1)) {
		const ValueList &valList = arg.GetList(1);
		if (valList.size() != 2) {
			env.SetError(ERR_ValueError, "strides must have two elements");
			return Value::Nil;
		}
		stridesRow = valList[0].GetSizeT();
		stridesCol = valList[1].GetSizeT();
	}
	Filter::PaddingType paddingType = Filter::PADDINGTYPE_Valid;
	if (arg.IsValid(2)) {
		Filter::SymbolToPaddingType(env, arg.GetSymbol(2));
		if (paddingType == Filter::PADDINGTYPE_None) return Value::Nil;
	}
	Filter::ChannelAt channelAt = Filter::CHANNELAT_Last;
	if (arg.IsValid(3)) {
		Filter::SymbolToChannelAt(env, arg.GetSymbol(3));
		if (channelAt == Filter::CHANNELAT_None) return Value::Nil;
	}
	Object_filter_at_maxpool2d *pObj = new Object_filter_at_maxpool2d(
		env, new Filter_MaxPool2d(sizeRow, sizeCol, stridesRow, stridesCol, paddingType, channelAt));
	return ReturnValue(env, arg, Value(pObj));
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------
// filter@maxpool2d#size
Gura_DeclareProperty_R(filter_at_maxpool2d, size)
{
	SetPropAttr(VTYPE_number, FLAG_ListVar);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementPropertyGetter(filter_at_maxpool2d, size)
{
	const Filter_MaxPool2d *pFilter = Object_filter_at_maxpool2d::GetObject(valueThis)->GetFilter();
	return Value::CreateList(env, Value(pFilter->GetSizeCol()), Value(pFilter->GetSizeRow()));
}

// filter@maxpool2d#strides
Gura_DeclareProperty_R(filter_at_maxpool2d, strides)
{
	SetPropAttr(VTYPE_number, FLAG_ListVar);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementPropertyGetter(filter_at_maxpool2d, strides)
{
	const Filter_MaxPool2d *pFilter = Object_filter_at_maxpool2d::GetObject(valueThis)->GetFilter();
	return Value::CreateList(env, Value(pFilter->GetStridesCol()), Value(pFilter->GetStridesRow()));
}

// filter@maxpool2d#padding
Gura_DeclareProperty_R(filter_at_maxpool2d, padding)
{
	SetPropAttr(VTYPE_symbol);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementPropertyGetter(filter_at_maxpool2d, padding)
{
	const Filter_MaxPool2d *pFilter = Object_filter_at_maxpool2d::GetObject(valueThis)->GetFilter();
	return Value(Filter::PaddingTypeToSymbol(pFilter->GetPaddingType()));
}

// filter@maxpool2d#channel_at
Gura_DeclareProperty_R(filter_at_maxpool2d, channel_at)
{
	SetPropAttr(VTYPE_symbol);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementPropertyGetter(filter_at_maxpool2d, channel_at)
{
	const Filter_MaxPool2d *pFilter = Object_filter_at_maxpool2d::GetObject(valueThis)->GetFilter();
	return Value(Filter::ChannelAtToSymbol(pFilter->GetChannelAt()));
}

//-----------------------------------------------------------------------------
// Implementation of class
//-----------------------------------------------------------------------------
Class_filter_at_maxpool2d::Class_filter_at_maxpool2d(Environment *pEnvOuter) :
	ClassFundamental(pEnvOuter, VTYPE_filter_at_maxpool2d)
{
}

void Class_filter_at_maxpool2d::DoPrepare(Environment &env)
{
	// Assignment of function
	Gura_AssignFunction(filter_at_maxpool2d);
	// help document
	AddHelpTemplate(env, Gura_Symbol(en), helpDoc_en);
}

Object *Class_filter_at_maxpool2d::CreateDescendant(Environment &env, Class *pClass)
{
	return nullptr;
}

}
