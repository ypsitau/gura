//=============================================================================
// Gura class: memory
//=============================================================================
#ifndef __GURA_CLASS_MEMORY_H__
#define __GURA_CLASS_MEMORY_H__

#include "Class.h"

namespace Gura {

//-----------------------------------------------------------------------------
// Class_memory
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Class_memory : public Class {
public:
	Class_memory(Environment *pEnvOuter);
	virtual void Prepare(Environment &env);
	virtual bool CastFrom(Environment &env, Value &value, const Declaration *pDecl);
};

//-----------------------------------------------------------------------------
// Object_memory
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Object_memory : public Object {
public:
	class GURA_DLLDECLARE IteratorUnpack : public Iterator {
	private:
		AutoPtr<Object_memory> _pObj;
		String _format;
		ValueList _valListArg;
		size_t _offset;
	public:
		IteratorUnpack(Object_memory *pObj, const char *format,
					   const ValueList &valListArg, size_t offset);
		virtual Iterator *GetSource();
		virtual bool DoNext(Environment &env, Value &value);
		virtual String ToString() const;
		virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
	};
	class GURA_DLLDECLARE PointerEx : public Pointer {
	protected:
		AutoPtr<Object_memory> _pObjMemory;
	public:
		PointerEx(size_t offset, Object_memory *pObjMemory);
		PointerEx(const PointerEx &ptr);
		inline Object_memory *GetMemoryObj() { return _pObjMemory.get(); }
		inline const Object_memory *GetMemoryObj() const { return _pObjMemory.get(); }
		inline Memory &GetMemory() { return _pObjMemory->GetMemory(); }
		inline const Memory &GetMemory() const { return _pObjMemory->GetMemory(); }
	public:
		virtual Pointer *Clone() const;
		virtual Object *GetTarget() const;
		virtual size_t GetSize() const;
		virtual bool IsWritable() const;
		virtual bool Pack(Environment &env, bool forwardFlag,
						  const char *format, const ValueList &valListArg);
		virtual Value Unpack(Environment &env, bool forwardFlag,
							 const char *format, const ValueList &valListArg, bool exeedErrorFlag);
		virtual Iterator *CreateUnpackIterator(const char *format, const ValueList &valList);
	};
public:
	Gura_DeclareObjectAccessor(memory)
private:
	AutoPtr<Memory> _pMemory;
public:
	Object_memory(Environment &env, Memory *pMemory);
	Object_memory(Class *pClass, Memory *pMemory);
	inline Memory &GetMemory() { return *_pMemory; }
	inline const Memory &GetMemory() const { return *_pMemory; }
	virtual Object *Clone() const;
	virtual bool DoDirProp(Environment &env, SymbolSet &symbols);
	virtual Value DoGetProp(Environment &env, const Symbol *pSymbol,
						const SymbolSet &attrs, bool &evaluatedFlag);
	virtual Value DoSetProp(Environment &env, const Symbol *pSymbol, const Value &value,
						const SymbolSet &attrs, bool &evaluatedFlag);
	virtual String ToString(bool exprFlag);
};

}

#endif