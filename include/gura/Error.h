#ifndef __GURA_ERROR_H__
#define __GURA_ERROR_H__

#include "Common.h"

namespace Gura {

class Expr;
class ExprOwner;
class Environment;

//-----------------------------------------------------------------------------
// ErrorType
//-----------------------------------------------------------------------------
enum ErrorType {
	ERR_None,
	ERR_SyntaxError,
	ERR_ArithmeticError,
	ERR_TypeError,
	ERR_ZeroDivisionError,
	ERR_ValueError,
	ERR_DeclarationError,
	ERR_SystemError,
	ERR_IOError,
	ERR_OutOfRangeError,
	ERR_IndexError,
	ERR_KeyError,
	ERR_ImportError,
	ERR_AttributeError,
	ERR_RuntimeError,
	ERR_NameError,
	ERR_NotImplementedError,
	ERR_IteratorError,
	ERR_CodecError,
	ERR_CommandError,
	ERR_ArgumentError,
	ERR_MemoryError,
	ERR_FormatError,
	ERR_ResourceError,
	ERR_MemberAccessError,
};

//-----------------------------------------------------------------------------
// Error
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Error {
public:
	struct TypeInfo {
		ErrorType errType;
		const char *name;
	};
private:
	ErrorType _errType;
	String _text;
	std::auto_ptr<ExprOwner> _pExprCauseOwner;
	static const TypeInfo _typeInfoTbl[];
public:
	Error(ErrorType errType = ERR_None);
	Error(const Error &err);
	void Clear();
	void Set(ErrorType errType, const String &text);
	String MakeText(bool lineInfoFlag = true) const;
	String MakeTrace() const;
	inline ErrorType GetType() const { return _errType; }
	inline const char *GetTypeName() const { return GetTypeName(_errType); }
	inline ExprOwner &GetExprCauseOwner() { return *_pExprCauseOwner; }
	inline const ExprOwner &GetExprCauseOwner() const { return *_pExprCauseOwner; }
	static const char *GetTypeName(ErrorType errType);
	static void AssignErrorTypes(Environment &env);
};

}

#endif
