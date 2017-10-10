//=============================================================================
// Gura class: filter
//=============================================================================
#ifndef __GURA_CLASS_FILTER_H__
#define __GURA_CLASS_FILTER_H__

#include "Class.h"

namespace Gura {

//-----------------------------------------------------------------------------
// Filter
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Filter {
public:
	enum PaddingType {
		PADDINGTYPE_None,
		PADDINGTYPE_Valid,
		PADDINGTYPE_Same,
	};
	enum ChannelAt {
		CHANNELAT_None,
		CHANNELAT_Last,
		CHANNELAT_First,
	};
protected:
	int _cntRef;
public:
	Gura_DeclareReferenceAccessor(Filter);
public:
	inline Filter() : _cntRef(1) {}
protected:
	virtual ~Filter();
public:
	virtual bool Apply(Signal &sig, AutoPtr<Array> &pArrayRtn, const Array *pArray) const = 0;
	virtual String ToString() const = 0;
public:
	static void CalcPadding(size_t sizeIn, size_t sizeKernel, size_t strides, PaddingType paddingType,
							size_t *pSizeOut, size_t *pSizePad);
	static void CalcPadding(size_t sizeIn, size_t sizeKernel, size_t strides, PaddingType paddingType,
							size_t *pSizeOut, size_t *pSizePadHead, size_t *pSizePadTail);
	static PaddingType SymbolToPaddingType(Signal &sig, const Symbol *pSymbol);
	static PaddingType SymbolToPaddingType(const Symbol *pSymbol);
	static const Symbol *PaddingTypeToSymbol(PaddingType paddingType);
	static ChannelAt SymbolToChannelAt(Signal &sig, const Symbol *pSymbol);
	static ChannelAt SymbolToChannelAt(const Symbol *pSymbol);
	static const Symbol *ChannelAtToSymbol(ChannelAt channelAt);
};

//-----------------------------------------------------------------------------
// Class_filter
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Class_filter : public ClassFundamental {
public:
	Class_filter(Environment *pEnvOuter);
	virtual void DoPrepare(Environment &env);
	virtual Object *CreateDescendant(Environment &env, Class *pClass);
};

//-----------------------------------------------------------------------------
// Object_filter
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Object_filter : public Object {
protected:
	AutoPtr<Filter> _pFilter;
public:
	Gura_DeclareObjectAccessor(filter)
public:
	Object_filter(Environment &env, Filter *pFilter);
	Object_filter(Class *pClass, Filter *pFilter);
	virtual String ToString(bool exprFlag);
	inline Filter *GetFilter() { return _pFilter.get(); }
	inline const Filter *GetFilter() const { return _pFilter.get(); }
};

}

#endif
