//----------------------------------------------------------------------------
// wxTreeItemData
// extracted from treedata.tex
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_TREEITEMDATA_H__
#define __CLASS_WX_TREEITEMDATA_H__

Gura_BeginModuleScope(wx)

class Object_wx_TreeItemData;

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_TreeItemData: public wxTreeItemData, public GuraObjectObserver {
private:
	Value _value;
	Object_wx_TreeItemData *_pObj;
public:
	inline wx_TreeItemData(const Value &value) : wxTreeItemData(),
						_value(value), _pObj(nullptr) {}
	inline wx_TreeItemData(const wx_TreeItemData &itemData) : wxTreeItemData(itemData),
						_value(itemData._value), _pObj(nullptr) {}
	~wx_TreeItemData();
	inline const Value &GetValue() { return _value; }
	inline void SetValue(const Value &value) { _value = value; }
	inline void AssocWithGura(Object_wx_TreeItemData *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

//----------------------------------------------------------------------------
// Class declaration for wxTreeItemData
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_TreeItemData);

//----------------------------------------------------------------------------
// Object declaration for wxTreeItemData
//----------------------------------------------------------------------------
class Object_wx_TreeItemData : public Object {
protected:
	wx_TreeItemData *_pEntity;
	GuraObjectObserver *_pObserver;
	bool _ownerFlag;
public:
	Gura_DeclareObjectAccessor(wx_TreeItemData)
public:
	inline Object_wx_TreeItemData(wx_TreeItemData *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object(Gura_UserClass(wx_TreeItemData)),
				_pEntity(pEntity), _pObserver(pObserver), _ownerFlag(ownerFlag) {}
	inline Object_wx_TreeItemData(Class *pClass, wx_TreeItemData *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object(pClass), _pEntity(pEntity), _pObserver(pObserver), _ownerFlag(ownerFlag) {}
	virtual ~Object_wx_TreeItemData();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline void SetEntity(wx_TreeItemData *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) {
		if (_ownerFlag) delete _pEntity;
		_pEntity = pEntity;
		_pObserver = pObserver;
		_ownerFlag = ownerFlag;
	}
	inline void InvalidateEntity() { _pEntity = nullptr, _pObserver = nullptr, _ownerFlag = false; }
	inline wx_TreeItemData *GetEntity() { return _pEntity; }
	inline wxTreeItemData *ReleaseEntity() {
		wxTreeItemData *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline void NotifyGuraObjectDeleted() {
		if (_pObserver != nullptr) _pObserver->GuraObjectDeleted();
	}
	inline bool IsInvalid(Signal &sig) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(sig, "wxTreeItemData");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
