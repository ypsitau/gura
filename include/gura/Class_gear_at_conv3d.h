//=============================================================================
// Gura class: gear@conv3d
//=============================================================================
#ifndef __GURA_CLASS_GEAR_AT_CONV3D_H__
#define __GURA_CLASS_GEAR_AT_CONV3D_H__

#include "Class_gear.h"

namespace Gura {

//-----------------------------------------------------------------------------
// Gear_Conv3d
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Gear_Conv3d : public Gear {
public:
	typedef bool (*GearFuncT)(Signal &sig, AutoPtr<Array> &pArrayRtn,
								  const Array *pArray, const Gear_Conv3d *pGear);
	struct GearFuncTable {
		GearFuncT funcs[Array::ETYPE_Max][Array::ETYPE_Max];
	};
public:
	static GearFuncTable gearFuncTable;
public:
	Gura_DeclareReferenceAccessor(Gear_Conv3d);
public:
	inline Gear_Conv3d() {}
public:
	virtual bool Apply(Signal &sig, AutoPtr<Array> &pArrayRtn, const Array *pArray) const;
	virtual String ToString() const;
};

//-----------------------------------------------------------------------------
// Class_gear_at_conv3d
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Class_gear_at_conv3d : public ClassFundamental {
public:
	Class_gear_at_conv3d(Environment *pEnvOuter);
	virtual void DoPrepare(Environment &env);
	virtual Object *CreateDescendant(Environment &env, Class *pClass);
};

//-----------------------------------------------------------------------------
// Object_gear_at_conv3d
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Object_gear_at_conv3d : public Object_gear {
public:
	Gura_DeclareObjectAccessor(gear_at_conv3d)
public:
	Object_gear_at_conv3d(Environment &env, Gear_Conv3d *pGear);
	virtual Object *Clone() const;
	inline Gear_Conv3d *GetGear() { return dynamic_cast<Gear_Conv3d *>(_pGear.get()); }
	inline const Gear_Conv3d *GetGear() const { return dynamic_cast<const Gear_Conv3d *>(_pGear.get()); }
};

}

#endif
