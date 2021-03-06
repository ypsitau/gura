//-----------------------------------------------------------------------------
// Gura module: base64
//-----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleBody(base64)

//-----------------------------------------------------------------------------
// Gura module functions: base64
//-----------------------------------------------------------------------------
// base64.decode(stream:stream:r) {block?}
Gura_DeclareFunction(decode)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "stream", VTYPE_stream, OCCUR_Once, FLAG_Read);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Reads text stream that is formatted in base64 and returns the decoded result in binary.\n"
		"\n"
		GURA_HELPTEXT_BLOCK_en("data", "binary"));
}

Gura_ImplementFunction(decode)
{
	AutoPtr<Object_binary> pObjBinary(new Object_binary(env));
	AutoPtr<Stream> pStreamSrc(new Stream_Base64Reader(env, arg.GetStream(0).Reference()));
	AutoPtr<Stream> pStreamDst(
		new Pointer::StreamEx(
			env, new Object_binary::PointerEx(
				pObjBinary->GetBinary().size(), pObjBinary->Reference())));
	if (!pStreamSrc->ReadToStream(env, *pStreamDst)) return Value::Nil;
	return ReturnValue(env, arg, Value(pObjBinary.release()));
}

// base64.encode(stream:stream:r, linelen:number => 76) {block?}
Gura_DeclareFunction(encode)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "stream", VTYPE_stream, OCCUR_Once, FLAG_Read);
	DeclareArg(env, "linelen", VTYPE_number, OCCUR_Once, FLAG_Nil, 0, new Expr_Value(76));
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Encodes content of the stream into base64 format and returns the result in binary.\n"
		"\n"
		GURA_HELPTEXT_BLOCK_en("data", "binary"));
}

Gura_ImplementFunction(encode)
{
	int nCharsPerLine = arg.Is_number(1)? arg.GetInt(1) : -1;
	AutoPtr<Object_binary> pObjBinary(new Object_binary(env));
	Stream &streamSrc = arg.GetStream(0);
	AutoPtr<Stream> pStreamDst(
		new Stream_Base64Writer(
			env,
			new Pointer::StreamEx(
				env, new Object_binary::PointerEx(
					pObjBinary->GetBinary().size(), pObjBinary->Reference())),
			nCharsPerLine));
	if (!streamSrc.ReadToStream(env, *pStreamDst)) return Value::Nil;
	return ReturnValue(env, arg, Value(pObjBinary.release()));
}

// base64.reader(stream:stream:r) {block?}
Gura_DeclareFunction(reader)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "stream", VTYPE_stream, OCCUR_Once, FLAG_Read);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Creates a stream instance that reads data formatted in base64 from `stream`.\n"
		"\n"
		GURA_HELPTEXT_BLOCK_en("s", "stream"));
}

Gura_ImplementFunction(reader)
{
	Stream &stream = arg.GetStream(0);
	AutoPtr<Stream> pStream(new Stream_Base64Reader(env, stream.Reference()));
	return ReturnValue(env, arg, Value(new Object_stream(env, pStream.release())));
}

// base64.writer(stream:stream:w, linelen:number => 76) {block?}
Gura_DeclareFunction(writer)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "stream", VTYPE_stream, OCCUR_Once, FLAG_Write);
	DeclareArg(env, "linelen", VTYPE_number, OCCUR_Once, FLAG_Nil, 0, new Expr_Value(76));
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Creates a stream instance that encodes data to base64 format and writes it to the `stream`.\n"
		"\n"
		"The number of characters per line is specified by an argument `linelen`.\n"
		"If omitted, that is 76.\n"
		"\n"
		GURA_HELPTEXT_BLOCK_en("s", "stream"));
}

Gura_ImplementFunction(writer)
{
	Stream &stream = arg.GetStream(0);
	int nCharsPerLine = arg.Is_number(1)? arg.GetInt(1) : -1;
	AutoPtr<Stream> pStream(new Stream_Base64Writer(env,
								stream.Reference(), nCharsPerLine));
	return ReturnValue(env, arg, Value(new Object_stream(env, pStream.release())));
}

//-----------------------------------------------------------------------------
// Gura interfaces for stream class
//-----------------------------------------------------------------------------
// stream#reader@base64() {block?}
Gura_DeclareMethodAlias(stream, reader_base64, "reader@base64")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Creates a stream instance that reads data formatted in base64 from the target stream instance.\n"
		"\n"
		GURA_HELPTEXT_BLOCK_en("s", "stream"));
}

Gura_ImplementMethod(stream, reader_base64)
{
	Stream &stream = Object_stream::GetObjectThis(arg)->GetStream();
	AutoPtr<Stream> pStream(new Stream_Base64Reader(env, stream.Reference()));
	return ReturnValue(env, arg, Value(new Object_stream(env, pStream.release())));
}

// stream#writer@base64(linelen:number => 76) {block?}
Gura_DeclareMethodAlias(stream, writer_base64, "writer@base64")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "linelen", VTYPE_number, OCCUR_Once, FLAG_Nil, 0, new Expr_Value(76));
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Creates a stream instance that encodes data to base64 format and writes it to the target stream instance.\n"
		"\n"
		"The number of characters per line is specified by an argument `linelen`.\n"
		"If omitted, that is 76.\n"
		"\n"
		GURA_HELPTEXT_BLOCK_en("s", "stream"));
}

Gura_ImplementMethod(stream, writer_base64)
{
	int nCharsPerLine = arg.Is_number(0)? arg.GetInt(0) : -1;
	Stream &stream = Object_stream::GetObjectThis(arg)->GetStream();
	AutoPtr<Stream> pStream(new Stream_Base64Writer(env,
								stream.Reference(), nCharsPerLine));
	return ReturnValue(env, arg, Value(new Object_stream(env, pStream.release())));
}

//-----------------------------------------------------------------------------
// Module Entries
//-----------------------------------------------------------------------------
Gura_ModuleValidate()
{
	return Version::CheckCoreVersion(GURA_VERSION, nullptr);
}

Gura_ModuleEntry()
{
	// function assignment
	Gura_AssignFunction(decode);
	Gura_AssignFunction(encode);
	Gura_AssignFunction(reader);
	Gura_AssignFunction(writer);
	// method assignment to stream type
	Gura_AssignMethodTo(VTYPE_stream, stream, reader_base64);
	Gura_AssignMethodTo(VTYPE_stream, stream, writer_base64);
	return true;
}

Gura_ModuleTerminate()
{
}

Gura_EndModuleBody(base64, base64)

Gura_RegisterModule(base64)
