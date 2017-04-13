//=============================================================================
// ArrayT
//=============================================================================
#ifndef __GURA_ARRAYT_H__
#define __GURA_ARRAYT_H__

#include "Array.h"

namespace Gura {

//-----------------------------------------------------------------------------
// ArrayT
//-----------------------------------------------------------------------------
template<typename T_Elem>
class GURA_DLLDECLARE ArrayT : public Array {
public:
	Gura_DeclareReferenceAccessor(ArrayT);
public:
	ArrayT();
	ArrayT(const ArrayT &src);
	ArrayT(Memory *pMemory, size_t offsetBase);
	ArrayT(size_t size);
	ArrayT(size_t sizeRow, size_t sizeCol);
	inline void AllocMemory() {
		_pMemory.reset(new MemoryHeap(sizeof(T_Elem) * GetElemNum()));
	}
	inline T_Elem *GetPointer() {
		return reinterpret_cast<T_Elem *>(_pMemory->GetPointer()) + GetOffsetBase();
	}
	inline const T_Elem *GetPointer() const {
		return reinterpret_cast<T_Elem *>(_pMemory->GetPointer()) + GetOffsetBase();
	}
	inline operator T_Elem *() { return GetPointer(); }
	inline operator const T_Elem *() const { return GetPointer(); }
	virtual String ToString(bool exprFlag) const;
	virtual bool DoesContainZero() const;
	virtual bool DoesContainMinus() const;
	virtual bool DoesContainZeroOrMinus() const;
	static ElemType ElemTypeThis;
	static size_t ElemBytes;
	static const char *ElemTypeName;
	static const char *ConstructorName;
	void Fill(const T_Elem &num);
	void FillZero();
	void FillRand(UInt range);
	void FillRandNormal(double mu, double sigma);
	bool Paste(Signal &sig, size_t offset, const ArrayT *pArrayTSrc);
	void Dump(Signal &sig, Stream &stream, bool upperFlag) const;
	void CopyToList(ValueList &valList) const;
	ArrayT *Flatten() const;
	ArrayT *Reshape(Signal &sig, const ValueList &valList) const;
	ArrayT *Transpose(Signal &sig, const ValueList &valList) const;
	ArrayT *Transpose(const SizeTList &axes) const;
	ArrayT *Transpose() const;
	ArrayT *Head(Signal &sig, size_t n) const;
	ArrayT *Tail(Signal &sig, size_t n) const;
	ArrayT *Offset(Signal &sig, size_t n) const;
	ArrayT *RoundOff(double threshold) const;
	// functions to create an ArrayT instance
	static ArrayT *Create(const Dimension &dim);
	static ArrayT *Create(const Array::Dimensions &dims);
	static ArrayT *Create(Dimensions::const_iterator pDim, Dimensions::const_iterator pDimEnd);
	static ArrayT *Create(Dimensions::const_iterator pDim,
						  Dimensions::const_iterator pDimEnd, const Dimension &dim);
	static ArrayT *Create(
		Dimensions::const_iterator pDim1, Dimensions::const_iterator pDim1End,
		Dimensions::const_iterator pDim2, Dimensions::const_iterator pDim2End);
	static ArrayT *CreateFromValue(Environment &env, const Value &value);
	static ArrayT *CreateFromList(const ValueList &valList);
	static ArrayT *CreateFromList(Signal &sig, const ValueList &valList);
	static ArrayT *CreateFromIterator(Environment &env, Iterator *pIterator);
	static ArrayT *CreateFromExpr(Environment &env, const Expr *pExpr);
	static ArrayT *CreateIdentity(size_t n);
	static ArrayT *CreateRange(Double numBegin, Double numEnd, Double numStep);
	static ArrayT *CreateInterval(
		Double numBegin, Double numEnd, int numSamples, Double numDenom, int iFactor);
	static ArrayT *CreateOnes(const ValueList &valList);
	static ArrayT *CreateZeros(const ValueList &valList);
	static ArrayT *CreateRands(const ValueList &valList, UInt range);
	static ArrayT *CreateRandsNormal(const ValueList &valList, double mu, double sigma);
	static ArrayT *CreateRotation(double rad, bool transFlag, T_Elem xTrans, T_Elem yTrans);
	static ArrayT *CreateRotationX(double rad, bool transFlag, T_Elem xTrans, T_Elem yTrans, T_Elem zTrans);
	static ArrayT *CreateRotationY(double rad, bool transFlag, T_Elem xTrans, T_Elem yTrans, T_Elem zTrans);
	static ArrayT *CreateRotationZ(double rad, bool transFlag, T_Elem xTrans, T_Elem yTrans, T_Elem zTrans);
	static ArrayT *CreateScale2D(T_Elem xScale, T_Elem yScale);
	static ArrayT *CreateScale3D(T_Elem xScale, T_Elem yScale, T_Elem zScale);
	static ArrayT *CreateTranslate2D(T_Elem xTrans, T_Elem yTrans);
	static ArrayT *CreateTranslate3D(T_Elem xTrans, T_Elem yTrans, T_Elem zTrans);
private:
	inline ~ArrayT() {}
};

//-----------------------------------------------------------------------------
// Iterator_ArrayT_Each
//-----------------------------------------------------------------------------
template<typename T_Elem>
class GURA_DLLDECLARE Iterator_ArrayT_Each : public Iterator {
private:
	AutoPtr<ArrayT<T_Elem> > _pArrayT;
	bool _flatFlag;
	size_t _idx;
public:
	inline Iterator_ArrayT_Each(ArrayT<T_Elem> *pArrayT, bool flatFlag) :
		Iterator(FinitePredictable), _pArrayT(pArrayT), _flatFlag(flatFlag), _idx(0) {}
	virtual size_t GetLength() const;
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

}

#endif
