//=============================================================================
// Gura class: gear
//=============================================================================
#ifndef __GURA_CLASS_GEAR_H__
#define __GURA_CLASS_GEAR_H__

#include "Class.h"

namespace Gura {

//-----------------------------------------------------------------------------
// Gear
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Gear {
public:
	enum PaddingType {
		PADDINGTYPE_Invalid,
		PADDINGTYPE_Valid,
		PADDINGTYPE_Same,
	};
protected:
	int _cntRef;
public:
	Gura_DeclareReferenceAccessor(Gear);
public:
	inline Gear() : _cntRef(1) {}
protected:
	virtual ~Gear();
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
	template<typename T_Gear>
	static void CalcPadding1d(const T_Gear *pGear, const Array::Dimensions &dims,
							  size_t *pSizePad);
	template<typename T_Gear>
	static void CalcPadding2d(const T_Gear *pGear, const Array::Dimensions &dims,
							  size_t *pSizePadRow, size_t *pSizePadCol);
	template<typename T_Gear>
	static void CalcPadding3d(const T_Gear *pGear, const Array::Dimensions &dims,
							  size_t *pSizePadPlane, size_t *pSizePadRow, size_t *pSizePadCol);
};

template<typename T_Gear>
void Gear::CalcPadding1d(const T_Gear *pGear, const Array::Dimensions &dims,
						  size_t *pSizePad)
{
	size_t sizeOut = 0;
	bool chLastFlag = (pGear->GetChannelPos() == Array::CHANNELPOS_Last);
	CalcPadding(dims.GetBack(chLastFlag? 1 : 0).GetSize(),
				pGear->GetSize(), pGear->GetStrides(), pGear->GetPaddingType(),
				&sizeOut, pSizePad);
}

template<typename T_Gear>
void Gear::CalcPadding2d(const T_Gear *pGear, const Array::Dimensions &dims,
						   size_t *pSizePadRow, size_t *pSizePadCol)
{
	size_t sizeOutRow = 0;
	size_t sizeOutCol = 0;
	bool chLastFlag = (pGear->GetChannelPos() == Array::CHANNELPOS_Last);
	CalcPadding(dims.GetBack(chLastFlag? 2 : 1).GetSize(),
				pGear->GetSizeRow(), pGear->GetStridesRow(), pGear->GetPaddingType(),
				&sizeOutRow, pSizePadRow);
	CalcPadding(dims.GetBack(chLastFlag? 1 : 0).GetSize(),
				pGear->GetSizeCol(), pGear->GetStridesCol(), pGear->GetPaddingType(),
				&sizeOutCol, pSizePadCol);
}

template<typename T_Gear>
void Gear::CalcPadding3d(const T_Gear *pGear, const Array::Dimensions &dims,
						   size_t *pSizePadPlane, size_t *pSizePadRow, size_t *pSizePadCol)
{
	size_t sizeOutPlane = 0;
	size_t sizeOutRow = 0;
	size_t sizeOutCol = 0;
	bool chLastFlag = (pGear->GetChannelPos() == Array::CHANNELPOS_Last);
	CalcPadding(dims.GetBack(chLastFlag? 3 : 2).GetSize(),
				pGear->GetSizePlane(), pGear->GetStridesPlane(), pGear->GetPaddingType(),
				&sizeOutPlane, pSizePadPlane);
	CalcPadding(dims.GetBack(chLastFlag? 2 : 1).GetSize(),
				pGear->GetSizeRow(), pGear->GetStridesRow(), pGear->GetPaddingType(),
				&sizeOutRow, pSizePadRow);
	CalcPadding(dims.GetBack(chLastFlag? 1 : 0).GetSize(),
				pGear->GetSizeCol(), pGear->GetStridesCol(), pGear->GetPaddingType(),
				&sizeOutCol, pSizePadCol);
}

//-----------------------------------------------------------------------------
// Class_gear
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Class_gear : public ClassFundamental {
public:
	Class_gear(Environment *pEnvOuter);
	virtual void DoPrepare(Environment &env);
	virtual Object *CreateDescendant(Environment &env, Class *pClass);
};

//-----------------------------------------------------------------------------
// Object_gear
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Object_gear : public Object {
protected:
	AutoPtr<Gear> _pGear;
public:
	Gura_DeclareObjectAccessor(gear)
public:
	Object_gear(Environment &env, Gear *pGear);
	Object_gear(Class *pClass, Gear *pGear);
	virtual String ToString(bool exprFlag);
	inline Gear *GetGear() { return _pGear.get(); }
	inline const Gear *GetGear() const { return _pGear.get(); }
};

}

#endif
