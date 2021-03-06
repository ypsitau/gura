//-----------------------------------------------------------------------------
// Gura module: gzip
//-----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleBody(gzip)

//-----------------------------------------------------------------------------
// Gura module functions: gzip
//-----------------------------------------------------------------------------
// gzip.reader(stream:stream:r) {block?}
Gura_DeclareFunction(reader)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "stream", VTYPE_stream, OCCUR_Once, FLAG_Read);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementFunction(reader)
{
	Signal &sig = env.GetSignal();
	Stream &stream = arg.GetStream(0);
	int windowBits = 31;
	Object_stream *pObjStream = GenerateDecompressor(env, stream.Reference(), windowBits);
	if (sig.IsSignalled()) return Value::Nil;
	return ReturnValue(env, arg, Value(pObjStream));
}

// gzip.writer(stream:stream:w, level?:number) {block?}
Gura_DeclareFunction(writer)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "stream", VTYPE_stream, OCCUR_Once, FLAG_Write);
	DeclareArg(env, "level", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementFunction(writer)
{
	Signal &sig = env.GetSignal();
	Stream &stream = arg.GetStream(0);
	int level = arg.Is_number(1)? arg.GetInt(1) : Z_DEFAULT_COMPRESSION;
	int windowBits = 31;
	Object_stream *pObjStream = GenerateCompressor(env, stream.Reference(), level, windowBits);
	if (sig.IsSignalled()) return Value::Nil;
	return ReturnValue(env, arg, Value(pObjStream));
}

//-----------------------------------------------------------------------------
// Gura interfaces for Object_stream
//-----------------------------------------------------------------------------
// stream#reader@gzip() {block?}
Gura_DeclareMethodAlias(stream, reader_gzip, "reader@gzip")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(stream, reader_gzip)
{
	Signal &sig = env.GetSignal();
	Stream &stream = Object_stream::GetObjectThis(arg)->GetStream();
	int windowBits = 31;
	Object_stream *pObjStream = GenerateDecompressor(env, stream.Reference(), windowBits);
	if (sig.IsSignalled()) return Value::Nil;
	return ReturnValue(env, arg, Value(pObjStream));
}

// stream#writer@gzip(level?:number) {block?}
Gura_DeclareMethodAlias(stream, writer_gzip, "writer@gzip")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "level", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(stream, writer_gzip)
{
	Signal &sig = env.GetSignal();
	Stream &stream = Object_stream::GetObjectThis(arg)->GetStream();
	int level = arg.Is_number(0)? arg.GetInt(0) : Z_DEFAULT_COMPRESSION;
	int windowBits = 31;
	Object_stream *pObjStream = GenerateCompressor(env, stream.Reference(), level, windowBits);
	if (sig.IsSignalled()) return Value::Nil;
	return ReturnValue(env, arg, Value(pObjStream));
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
	// value assignment
	Gura_AssignValue(NO_COMPRESSION,		Value(Z_NO_COMPRESSION));
	Gura_AssignValue(BEST_SPEED,			Value(Z_BEST_SPEED));
	Gura_AssignValue(BEST_COMPRESSION,		Value(Z_BEST_COMPRESSION));
	Gura_AssignValue(DEFAULT_COMPRESSION,	Value(Z_DEFAULT_COMPRESSION));
	// function assignment
	Gura_AssignFunction(reader);
	Gura_AssignFunction(writer);
	// method assignment to stream type
	Gura_AssignMethodTo(VTYPE_stream, stream, reader_gzip);
	Gura_AssignMethodTo(VTYPE_stream, stream, writer_gzip);
	return true;
}

Gura_ModuleTerminate()
{
}

//-----------------------------------------------------------------------------
// utilities
//-----------------------------------------------------------------------------
Object_stream *GenerateDecompressor(Environment &env, Stream *pStreamSrc, int windowBits)
{
	Signal &sig = env.GetSignal();
	AutoPtr<ZLib::Stream_Inflater> pStream(
		new ZLib::Stream_Inflater(env, pStreamSrc, InvalidSize));
	if (!pStream->Initialize(sig, windowBits)) return nullptr;
	return new Object_stream(env, pStream.release());
}

Object_stream *GenerateCompressor(Environment &env, Stream *pStreamDst, int level, int windowBits)
{
	Signal &sig = env.GetSignal();
	AutoPtr<ZLib::Stream_Deflater> pStream(
		new ZLib::Stream_Deflater(env, pStreamDst));
	if (!pStream->Initialize(sig, level,
					windowBits, 8, Z_DEFAULT_STRATEGY)) return nullptr;
	return new Object_stream(env, pStream.release());
}

Gura_EndModuleBody(gzip, gzip)

Gura_RegisterModule(gzip)
