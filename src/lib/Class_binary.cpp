// -*- coding: utf-8 -*-
//=============================================================================
// Gura class: binary
//=============================================================================
#include "stdafx.h"

namespace Gura {

static const char *helpDoc_en = R"**(
# Overview

The `binary` class provides measures to work on binary data
that is a byte sequence without any format.

You can create a `binary` instance by calling `binary()` function.

You can also create the instance by specifying `b` prefix before a string literal.
For example, the code below creates a `binary` instance that contains a sequence
`0x41, 0x42, 0xfe, 0x03, 0x43, 0x44`.

    b'AB\xfe\x03CD'


# Property

A `binary` instance has the following properties:

${markdown.makedoc@property(`en, binary)}


# Constructor

${markdown.makedoc@function(`en
binary
)}


# Method

${markdown.makedoc@function(`en
binary.alloc
binary.dump
binary.pointer
binary.reader
binary.writer
)}
)**";

//-----------------------------------------------------------------------------
// Object_binary
//-----------------------------------------------------------------------------
Object_binary::Object_binary(const Object_binary &obj) :
		Object(obj), _binary(obj._binary), _writableFlag(obj._writableFlag)
{
}

Object_binary::~Object_binary()
{
}

Object *Object_binary::Clone() const
{
	return new Object_binary(*this);
}

Value Object_binary::IndexGet(Environment &env, const Value &valueIdx)
{
	if (!valueIdx.Is_number()) {
		env.SetError(ERR_IndexError, "index must be a number for binary");
		return Value::Nil;
	}
	int idx = valueIdx.GetInt();
	int len = static_cast<int>(_binary.size());
	if (idx >= 0) {
		if (idx >= len) {
			env.SetError(ERR_IndexError, "index is out of range");
			return Value::Nil;
		}
		return Value(static_cast<UChar>(_binary[idx]));
	} else {
		if (-idx > len) {
			env.SetError(ERR_IndexError, "index is out of range");
			return Value::Nil;
		}
		return Value(static_cast<UChar>(_binary[len + idx]));
	}
}

void Object_binary::IndexSet(Environment &env, const Value &valueIdx, const Value &value)
{
	if (!IsWritable()) {
		env.SetError(ERR_ValueError, "not a writable binary");
		return;
	}
	if (!valueIdx.Is_number()) {
		env.SetError(ERR_IndexError, "index must be a number for binary");
		return;
	}
	if (!value.Is_number()) {
		env.SetError(ERR_IndexError, "value must be a number for binary");
		return;
	}
	int idx = valueIdx.GetInt();
	long data = value.GetLong();
	if (data < 0 || data > 255) {
		env.SetError(ERR_IndexError, "value must be between 0 and 255");
		return;
	}
	int len = static_cast<int>(_binary.size());
	if (idx >= 0) {
		if (idx >= len) {
			env.SetError(ERR_IndexError, "index is out of range");
			return;
		}
		_binary[idx] = static_cast<UChar>(data);
	} else {
		if (-idx > len) {
			env.SetError(ERR_IndexError, "index is out of range");
			return;
		}
		_binary[len + idx] = static_cast<UChar>(data);
	}
}

Iterator *Object_binary::CreateIterator(Signal &sig)
{
	return new Pointer::IteratorEach<UChar>(new PointerEx(0, Reference()), false);
}

String Object_binary::ToString(bool exprFlag)
{
	String str;
	char buff[64];
	::sprintf(buff, "<binary:%s:%dbyte",
				IsWritable()? "RW" : "R", static_cast<int>(_binary.size()));
	str += buff;
	if (!_binary.empty() && _binary.size() < 32) {
		str += ":'";
		foreach (Binary, p, _binary) {
			char ch = *p;
			if (ch == '\'' || ch == '\\') {
				str += '\\';
				str += ch;
			} else if (0x20 < ch && ch < 0x7f) {
				str += ch;
			} else {
				::sprintf(buff, "\\x%02x", static_cast<UChar>(ch));
				str += buff;
			}
		}
		str += "'";
	}
	str += ">";
	return str;
}

//-----------------------------------------------------------------------------
// Object_binary::PointerEx
//-----------------------------------------------------------------------------
Object_binary::PointerEx::PointerEx(size_t offset, Object_binary *pObjBinary) :
	Pointer(offset), _pObjBinary(pObjBinary)
{
}

Object_binary::PointerEx::PointerEx(const PointerEx &ptr) :
	Pointer(ptr), _pObjBinary(dynamic_cast<Object_binary *>(ptr._pObjBinary->Reference()))
{
}

bool Object_binary::PointerEx::StorePrepare(Signal &sig, size_t bytes)
{
	if (!_pObjBinary->IsWritable()) {
		sig.SetError(ERR_ValueError, "not a writable binary");
		return false;
	}
	return true;
}

void Object_binary::PointerEx::StoreBuffer(const void *buff, size_t bytes)
{
	size_t offsetNext = _offset + bytes;
	if (buff != nullptr) {
		Binary &binary = _pObjBinary->GetBinary();
		const UChar *buffp = reinterpret_cast<const UChar *>(buff);
		if (_offset < binary.size()) {
			size_t bytesToCopy = ChooseMin(binary.size() - _offset, bytes);
			std::copy(buffp, buffp + bytesToCopy, binary.begin() + _offset);
			buffp += bytesToCopy;
			bytes -= bytesToCopy;
		} else if (_offset > binary.size()) {
			binary.append(_offset - binary.size(), '\0');
		}
		binary.append(buffp, buffp + bytes);
	}
	_offset = offsetNext;
}

const UChar *Object_binary::PointerEx::ExtractPrepare(
	Signal &sig, size_t bytes, bool exceedErrorFlag)
{
	Binary &binary = _pObjBinary->GetBinary();
	if (_offset + bytes <= binary.size()) {
		const UChar *p = reinterpret_cast<const UChar *>(binary.data() + _offset);
		_offset += bytes;
		return p;
	}
	if (exceedErrorFlag) {
		sig.SetError(ERR_IndexError, "pointer exceeds the range of binary");
	}
	return nullptr;
}

Pointer *Object_binary::PointerEx::Clone() const
{
	return new PointerEx(*this);
}

Object *Object_binary::PointerEx::GetTarget() const
{
	return _pObjBinary.get();
}

const UChar *Object_binary::PointerEx::GetPointerC() const
{
	return reinterpret_cast<const UChar *>(_pObjBinary->GetBinary().data() + _offset);
}

UChar *Object_binary::PointerEx::GetWritablePointerC() const
{
	return nullptr;
}

size_t Object_binary::PointerEx::GetEntireSize() const
{
	return _pObjBinary->GetBinary().size();
}

bool Object_binary::PointerEx::IsWritable() const
{
	return _pObjBinary->IsWritable();
}

//-----------------------------------------------------------------------------
// Implementation of functions
//-----------------------------------------------------------------------------
// binary(buff*) {block?}
Gura_DeclareFunction(binary)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "buff", VTYPE_any, OCCUR_ZeroOrMore);
	SetClassToConstruct(env.LookupClass(VTYPE_binary));
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Creates a `binary` instance after combining `string` or `binary` specified by the arguments `buff`.\n"
		"If no argument is specified for `buff`, an empty `binary` instance would be created.\n"
		"\n"
		GURA_HELPTEXT_BLOCK_en("bin", "binary"));
}

Gura_ImplementFunction(binary)
{
	AutoPtr<Object_binary> pObjBinary(new Object_binary(env));
	Binary &binary = pObjBinary->GetBinary();
	foreach_const (ValueList, pValue, arg.GetList(0)) {
		if (pValue->Is_string()) {
			binary += pValue->GetString();
		} else if (pValue->Is_binary()) {
			binary += pValue->GetBinary();
		} else {
			env.SetError(ERR_ValueError, "string or binary is expected");
			return Value::Nil;
		}
	}
	return ReturnValue(env, arg, Value(pObjBinary.release()));
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------
// binary#p
Gura_DeclareProperty_R(binary, p)
{
	SetPropAttr(VTYPE_pointer);
	AddHelp(
		Gura_Symbol(en),
		"Returns a `pointer` instance that accesses the binary.\n"
		"This result is equivalent to that of calling the method `binary#pointer()`");
}

Gura_ImplementPropertyGetter(binary, p)
{
	Object_binary *pObj = Object_binary::GetObject(valueThis);
	Pointer *pPointer = new Object_binary::PointerEx(0, pObj->Reference());
	return Value(new Object_pointer(env, pPointer));
}

// binary#size
Gura_DeclareProperty_R(binary, size)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		"Returns the binary size in bytes."
		);
}

Gura_ImplementPropertyGetter(binary, size)
{
	Object_binary *pObj = Object_binary::GetObject(valueThis);
	return Value(pObj->GetBinary().size());
}

// binary#writable
Gura_DeclareProperty_R(binary, writable)
{
	SetPropAttr(VTYPE_boolean);
	AddHelp(
		Gura_Symbol(en),
		"Indicates if the content of the binary object is writable."
		);
}

Gura_ImplementPropertyGetter(binary, writable)
{
	Object_binary *pObj = Object_binary::GetObject(valueThis);
	return Value(pObj->IsWritable());
}

//-----------------------------------------------------------------------------
// Implementation of methods
//-----------------------------------------------------------------------------
// binary.alloc(bytes:number, data?:number):map {block?}
Gura_DeclareClassMethod(binary, alloc)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "bytes", VTYPE_number);
	DeclareArg(env, "data", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Creates a `binary` instance that has the specified size of buffer.\n"
		"If the argument `data`, which should have a number between 0 and 255, is specified,\n"
		"the buffer would be initialized with the value.\n"
		"\n"
		GURA_HELPTEXT_BLOCK_en("bin", "binary"));
}

Gura_ImplementClassMethod(binary, alloc)
{
	AutoPtr<Object_binary> pObjBinary(new Object_binary(env));
	Binary &buff = pObjBinary->GetBinary();
	size_t bytes = arg.GetSizeT(0);
	UChar data = arg.IsValid(1)? arg.GetUChar(1) : 0;
	buff.reserve(bytes);
	buff.insert(0, bytes, static_cast<char>(data));
	return ReturnValue(env, arg, Value(pObjBinary.release()));
}

// binary#dump(stream?:stream:w):void:[upper]
Gura_DeclareMethod(binary, dump)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "stream", VTYPE_stream, OCCUR_ZeroOrOnce, FLAG_Write);
	DeclareAttr(Gura_Symbol(upper));
	AddHelp(
		Gura_Symbol(en),
		"Prints a hexadecimal dump from the content of the `binary` to the standard output.\n"
		"If the argument `stream` is specified, the result would be output to the stream.\n"
		"\n"
		"In default, hexadecimal digit are printed with lower-case characters.\n"
		"Specifying an attribute `:upper` would output them with upper-case characters instead.\n"
		"\n"
		"Example:\n"
		"    >>> b'A quick brown fox jumps over the lazy dog.'.dump():upper\n"
		"    41 20 71 75 69 63 6B 20 62 72 6F 77 6E 20 66 6F  A quick brown fo\n"
		"    78 20 6A 75 6D 70 73 20 6F 76 65 72 20 74 68 65  x jumps over the\n"
		"    20 6C 61 7A 79 20 64 6F 67 2E                     lazy dog.\n");
}

Gura_ImplementMethod(binary, dump)
{
	Signal &sig = env.GetSignal();
	Stream *pStream = arg.IsInstanceOf(0, VTYPE_stream)?
								&arg.GetStream(0) : env.GetConsole();
	Object_binary *pThis = Object_binary::GetObjectThis(arg);
	const Binary &buff = pThis->GetBinary();
	pStream->Dump(sig, buff.data(), buff.size(), arg.IsSet(Gura_Symbol(upper)));
	return Value::Nil;
}

// binary#pointer(offset?:number):map {block?}
Gura_DeclareMethod(binary, pointer)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "offset", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Returns a `pointer` instance that has an initial offset specified\n"
		"by the argument `offset`. If the argument is omitted, it would return a `pointer`\n"
		"instance that points to the top of the binary.\n"
		"\n"
		GURA_HELPTEXT_BLOCK_en("p", "pointer"));
}

Gura_ImplementMethod(binary, pointer)
{
	Object_binary *pThis = Object_binary::GetObjectThis(arg);
	size_t offset = arg.Is_number(0)? arg.GetSizeT(0) : 0;
	Pointer *pPointer = new Object_binary::PointerEx(offset, pThis->Reference());
	return ReturnValue(env, arg, Value(new Object_pointer(env, pPointer)));
}

// binary#reader() {block?}
Gura_DeclareMethod(binary, reader)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Creates a `stream` instance with which you can read data from the binary by `stream#read()` method."
		"\n"
		GURA_HELPTEXT_BLOCK_en("s", "stream"));
}

Gura_ImplementMethod(binary, reader)
{
	Object_binary *pThis = Object_binary::GetObjectThis(arg);
	Stream *pStream = new Pointer::StreamEx(
		env, new Object_binary::PointerEx(0, pThis->Reference()));
	return ReturnValue(env, arg, Value(new Object_stream(env, pStream)));
}

// binary#writer() {block?}
Gura_DeclareMethod(binary, writer)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Creates a `stream` instance with which you can append data to the binary by `stream#write()` method."
		"\n"
		GURA_HELPTEXT_BLOCK_en("s", "stream"));
}

Gura_ImplementMethod(binary, writer)
{
	Object_binary *pThis = Object_binary::GetObjectThis(arg);
	Stream *pStream = new Pointer::StreamEx(
		env, new Object_binary::PointerEx(pThis->GetBinary().size(), pThis->Reference()));
	return ReturnValue(env, arg, Value(new Object_stream(env, pStream)));
}

//-----------------------------------------------------------------------------
// Implementation of class
//-----------------------------------------------------------------------------
Class_binary::Class_binary(Environment *pEnvOuter) : ClassFundamental(pEnvOuter, VTYPE_binary)
{
}

void Class_binary::DoPrepare(Environment &env)
{
	Gura_AssignFunction(binary);
	// Assignment of properties
	Gura_AssignProperty(binary, p);
	Gura_AssignProperty(binary, size);
	Gura_AssignProperty(binary, writable);
	// Assignment of methods
	Gura_AssignMethod(binary, alloc);
	Gura_AssignMethod(binary, dump);
	Gura_AssignMethod(binary, pointer);
	Gura_AssignMethod(binary, reader);
	Gura_AssignMethod(binary, writer);
	// help document
	AddHelpTemplate(env, Gura_Symbol(en), helpDoc_en);
}

bool Class_binary::CastFrom(Environment &env, Value &value, ULong flags)
{
	if (value.Is_string()) {
		Object_binary *pObjBinary = new Object_binary(env, value.GetStringSTL(), true);
		value = Value(pObjBinary);
		return true;
	}
	return false;
}

Class::SerializeFmtVer Class_binary::GetSerializeFmtVer() const
{
	return SerializeFmtVer_1;
}

bool Class_binary::Serialize(Environment &env, Stream &stream, const Value &value) const
{
	Object_binary *pObj = Object_binary::GetObject(value);
	if (!stream.SerializeBoolean(env, pObj->IsWritable())) return false;
	if (!stream.SerializeBinary(env, pObj->GetBinary())) return false;
	return true;
}

bool Class_binary::Deserialize(Environment &env, Stream &stream, Value &value, SerializeFmtVer serializeFmtVer) const
{
	if (serializeFmtVer == SerializeFmtVer_1) {
		bool writableFlag = false;
		if (!stream.DeserializeBoolean(env, writableFlag)) return false;
		AutoPtr<Object_binary> pObj(new Object_binary(env, writableFlag));
		if (!stream.DeserializeBinary(env, pObj->GetBinary())) return false;
		value = Value(pObj.release());
		return true;
	}
	SetError_UnsupportedSerializeFmtVer(serializeFmtVer);
	return false;
}

Object *Class_binary::CreateDescendant(Environment &env, Class *pClass)
{
	return new Object_binary((pClass == nullptr)? this : pClass);
}

}
