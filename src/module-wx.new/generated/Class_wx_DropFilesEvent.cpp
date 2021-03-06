//----------------------------------------------------------------------------
// wxDropFilesEvent
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxDropFilesEvent
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxDropFilesEvent
//----------------------------------------------------------------------------
Object_wx_DropFilesEvent::~Object_wx_DropFilesEvent()
{
}

Object *Object_wx_DropFilesEvent::Clone() const
{
	return nullptr;
}

String Object_wx_DropFilesEvent::ToString(bool exprFlag)
{
	String rtn("<wx.DropFilesEvent:");
	if (GetEntity() == nullptr) {
		rtn += "invalid>";
	} else {
		char buff[64];
		::sprintf(buff, "%p>", GetEntity());
		rtn += buff;
	}
	return rtn;
}

//----------------------------------------------------------------------------
// Constructor implementation
//----------------------------------------------------------------------------
Gura_DeclareFunctionAlias(__DropFilesEvent, "DropFilesEvent")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "noFiles", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "files", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_DropFilesEvent));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__DropFilesEvent)
{
	//wxEventType id = arg.GetNumber(0)
	//int noFiles = arg.GetNumber(1)
	//wxString* files = arg.GetNumber(2)
	//wxDropFilesEvent(id, noFiles, files);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_DropFilesEvent, __GetFiles, "GetFiles")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_DropFilesEvent, __GetFiles)
{
	Object_wx_DropFilesEvent *pThis = Object_wx_DropFilesEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxString* _rtn = pThis->GetEntity()->GetFiles();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_DropFilesEvent, __GetNumberOfFiles, "GetNumberOfFiles")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_DropFilesEvent, __GetNumberOfFiles)
{
	Object_wx_DropFilesEvent *pThis = Object_wx_DropFilesEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetNumberOfFiles();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_DropFilesEvent, __GetPosition, "GetPosition")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_DropFilesEvent, __GetPosition)
{
	Object_wx_DropFilesEvent *pThis = Object_wx_DropFilesEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxPoint _rtn = pThis->GetEntity()->GetPosition();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxDropFilesEvent
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_DropFilesEvent)
{
	// Constructor assignment
	Gura_AssignFunction(__DropFilesEvent);
	// Method assignment
	Gura_AssignMethod(wx_DropFilesEvent, __GetFiles);
	Gura_AssignMethod(wx_DropFilesEvent, __GetNumberOfFiles);
	Gura_AssignMethod(wx_DropFilesEvent, __GetPosition);
}

Gura_ImplementDescendantCreator(wx_DropFilesEvent)
{
	return new Object_wx_DropFilesEvent((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
