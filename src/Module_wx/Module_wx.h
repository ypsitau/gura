#ifndef __MODULE_WX_H__
#define __MODULE_WX_H__

//-----------------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------------
#if defined(__WXMSW__)
#define _MS(x) x
#else
#define _MS(x)
#endif

#define Gura_AssignWxValue(name) \
Gura_AssignValue(name, Value(static_cast<double>(wx##name)))

#define Gura_AssignWxStringValue(name) \
Gura_AssignValue(name, Value(env, wxString(wx##name).ToUTF8()))

#define Gura_AssignWxObject(name, className) \
Gura_AssignValue(name, Value(new Object_wx_##className(const_cast<wx##className *>(wx##name), NULL, false)));

#define Gura_AssignWxObjectEx(name, className, value) \
Gura_AssignValue(name, Value(new Object_wx_##className(const_cast<wx##className *>(value), NULL, false)));

#define Gura_AssignMacroValue(name) \
Gura_AssignValue(name, Value(name))

Gura_BeginModule(wx)

extern const bool OwnerFalse;
extern const bool OwnerTrue;

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------
void InitializeObjects(Environment &env);
void SetError_NotImplemented(Signal sig);
void SetError_MSWOnly(Signal sig);
void SetError_InvalidWxObject(Signal sig, const char *name);
void SetLogError(const Signal &sig);
wxArrayString *CreateArrayString(const ValueList &valList);
wxArrayInt *CreateArrayInt(const ValueList &valList);
Value ArrayIntToValue(Environment &env, const wxArrayInt &array);
Value ArrayStringToValue(Environment &env, const wxArrayString &array);
Value ArrayStringToValue(Environment &env, const wxString *array, int n);
void AddToArrayString(wxArrayString &array, const ValueList &valList);
void AddToArrayInt(wxArrayInt &array, const ValueList &valList);
void ConvertToWxImage(Object_image *pObjImage, wxImage *pImage);
bool CheckMethodResult(Signal sig);
bool CheckMethodResult(Signal sig, const Value &rtn,
					ValueType valueType, bool invalidAcceptableFlag = false);

//-----------------------------------------------------------------------------
// GuraObjectObserver
//-----------------------------------------------------------------------------
class GuraObjectObserver {
public:
	virtual void GuraObjectDeleted() = 0;
};

//-----------------------------------------------------------------------------
// ClientData
//-----------------------------------------------------------------------------
class ClientData : public wxClientData {
private:
	Value _value;
public:
	inline ClientData(const Value &value) : _value(value) {}
	inline Value &GetValue() { return _value; }
};

//-----------------------------------------------------------------------------
// ObjectWithValue
//-----------------------------------------------------------------------------
class ObjectWithValue : public wxObject {
private:
	Value _value;
public:
	inline ObjectWithValue(const Value &value) : _value(value) {}
	inline Value &GetValue() { return _value; }
};

//-----------------------------------------------------------------------------
// Iterator_NewIds
//-----------------------------------------------------------------------------
class Iterator_NewIds : public Iterator {
public:
	inline Iterator_NewIds() : Iterator(true) {}
	virtual ~Iterator_NewIds();
	virtual Iterator *Clone() const;
	virtual bool DoNext(Environment &env, Signal sig, Value &value);
	virtual String ToString(Signal sig) const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

}}

#endif
