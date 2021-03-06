//-----------------------------------------------------------------------------
// Gura module: http
//-----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleBody(http)

static Environment *_pEnvThis = nullptr;

static const char *HTTP_VERSION = "HTTP/1.1";

//-----------------------------------------------------------------------------
// utilities
//-----------------------------------------------------------------------------
bool SendStreamBody(Signal &sig, int sock, Stream &stream)
{
	const size_t bytesBuff = 32768;
	AutoPtr<Memory> pMemory(new MemoryHeap(bytesBuff));
	char *buff = reinterpret_cast<char *>(pMemory->GetPointer());
	size_t bytesRead;
	while ((bytesRead = stream.Read(sig, buff, bytesBuff)) > 0) {
		::send(sock, buff, static_cast<int>(bytesRead), 0);
	}
	return !sig.IsSignalled();
}

// RFC 3986 3.1. Scheme
String ExtractURIScheme(Signal &sig, const char *uri, const char **next)
{
	if (next != nullptr) *next = uri;
	const char *p = uri;
	for ( ; *p != '\0' && *p != '?' && *p != '#' && *p != ':'; p++) ;
	if (*p != ':') return String("");
	String rtn = String(uri, p - uri);
	if (next != nullptr) *next = p + 1;
	return rtn;
}

// RFC 3986 3.2. Authority
String ExtractURIAuthority(Signal &sig, const char *uri, const char **next)
{
	if (next != nullptr) *next = uri;
	const char *p = uri;
	String scheme = ExtractURIScheme(sig, uri, &p);
	if (sig.IsSignalled()) return String("");
	if (scheme.empty()) return String(""); // scheme has not been found
	if (*p != '/') return String("");
	while (*p == '/') p++;
	const char *top = p;
	for ( ; *p != '\0' && *p != '?' && *p != '#' && *p != '/'; p++) ;
	String rtn = String(top, p - top);
	if (next != nullptr) *next = p;
	return rtn;
}

// RFC 3986 3.3. Path
String ExtractURIPath(Signal &sig, const char *uri)
{
	const char *p = uri;
	ExtractURIScheme(sig, p, &p);
	if (sig.IsSignalled()) return String("");
	ExtractURIAuthority(sig, p, &p);
	if (sig.IsSignalled()) return String("");
	const char *top = p;
	for ( ; *p != '\0' && *p != '?' && *p != '#'; p++) ;
	return String(top, p - top);
}

// RFC 3986 3.4. Query
String ExtractURIQuery(Signal &sig, const char *uri)
{
	const char *p = uri;
	for ( ; *p != '\0' && *p != '?' && *p != '#'; p++) ;
	if (*p != '?') return String("");
	p++;
	const char *top = p;
	for ( ; *p != '\0' && *p != '#'; p++) ;
	return String(top, p - top);
}

String ExtractURIFragment(Signal &sig, const char *uri)
{
	const char *p = uri;
	for ( ; *p != '\0' && *p != '#'; p++) ;
	if (*p == '\0') return String("");
	return String(p + 1);
}

String QuoteURI(const char *str)
{
	String rtn;
	for (const char *p = str; *p != '\0'; p++) {
		char ch = *p;
		// tentative condition
		if (IsAlpha(ch) || IsDigit(ch) ||
						ch == '-' || ch == '/' || ch == '.' || ch == '@') {
			rtn += ch;
		} else {
			char buff[32];
			::sprintf(buff, "%%%02X", ch);
			rtn += buff;
		}
	}
	return rtn;
}

String UnquoteURI(Signal &sig, const char *str)
{
	enum {
		STAT_Start, STAT_Hex1, STAT_Hex2,
	} stat = STAT_Start;
	UChar chHex = 0x00;
	String rtn;
	for (const char *p = str; *p != '\0'; p++) {
		char ch = *p;
		switch (stat) {
		case STAT_Start: {
			if (ch == '+') {
				rtn += ' ';
			} else if (ch == '%') {
				stat = STAT_Hex1;
			} else {
				rtn += ch;
			}
			break;
		}
		case STAT_Hex1: {
			if (IsHexDigit(ch)) {
				chHex = ConvHexDigit(ch);
				stat = STAT_Hex2;
			} else {
				goto error_done;
			}
			break;
		}
		case STAT_Hex2: {
			if (IsHexDigit(ch)) {
				chHex = (chHex << 4) + ConvHexDigit(ch);
				rtn += static_cast<char>(chHex);
				stat = STAT_Start;
			} else {
				goto error_done;
			}
			break;
		}
		}
	}
	return rtn;
error_done:
	sig.SetError(ERR_FormatError, "invalid format of URI");
	return String("");
}

//-----------------------------------------------------------------------------
// Chunk implementation
//-----------------------------------------------------------------------------
Chunk::~Chunk()
{
}

bool Chunk::ParseChar(Signal &sig, char ch)
{
	if (ch == '\r') return true;	// just skip CR code
	Gura_BeginPushbackRegion();
	switch (_stat) {
	case STAT_Start: {
		if (IsSpace(ch)) {
			// nothing to do
		} else {
			_stat = STAT_Size;
			Gura_Pushback();
		}
		break;
	}
	case STAT_Size: {
		if (ch == '\n') {
			_stat = STAT_Complete;
		} else if (ch == ';') {
			_extName.clear(), _extValue.clear();
			_stat = STAT_ExtName;
		} else if (IsHexDigit(ch)) {
			_size = (_size << 4) + ConvHexDigit(ch);
		} else {
			sig.SetError(ERR_FormatError, "invalid character in chunk information");
			return false;
		}
		break;
	}
	case STAT_ExtName: {
		if (ch == '\n') {
			_stat = STAT_Complete;
		} else if (ch == '=') {
			_stat = STAT_ExtValue;
		} else {
			_extName += ch;
		}
		break;
	}
	case STAT_ExtValue: {
		if (ch == '\n') {
			_stat = STAT_Complete;
		} else {
			_extValue += ch;
		}
		break;
	}
	case STAT_Complete: {
		break;
	}
	}
	Gura_EndPushbackRegion();
	return true;
}

//-----------------------------------------------------------------------------
// SimpleHTMLParser implementation
// This is a very simple HTTP parser to detect the following patterns.
// - <?xml .. encoding="xxxxxxxx"?>
// - <meta http-equiv="Content-Type" content="..; charset=xxxxxxxx />
//-----------------------------------------------------------------------------
bool SimpleHTMLParser::ParseChar(Signal &sig, char ch)
{
	if (ch == '\r') return true;	// just skip CR code
	Gura_BeginPushbackRegion();
	switch (_stat) {
	case STAT_Init: {
		if (ch == '<') {
			_tagPrefix = '\0';
			_tagName.clear();
			_attrName.clear();
			_attrValue.clear();
			_attrs.clear();
			_stat = STAT_Tag1stChar;
		} else {
			// nothing to do
		}
		break;
	}
	case STAT_Tag1stChar: {
		if (ch == '?') {
			_tagPrefix = '?';
			_stat = STAT_TagName;
		} else if (ch == '!') {
			_stat = STAT_SeekTagClose;
		} else if (ch == '/') {
			_tagPrefix = '/';
			_stat = STAT_TagName;
		} else {
			Gura_Pushback();
			_stat = STAT_TagName;
		}
		break;
	}
	case STAT_SeekTagClose: {
		if (ch == '>') {
			_stat = STAT_Init;
		} else {
			// nothing to do
		}
		break;
	}
	case STAT_TagName: {
		if (ch == '?') {
			// just ignore it
		} else if (ch == '>') {
			if (!AcceptTag(sig, _tagPrefix, _tagName.c_str(), _attrs)) return false;
			if (!IsComplete()) _stat = STAT_Init;
		} else if (IsSpace(ch)) {
			_stat = STAT_SkipSpace;
			_statNext = STAT_AttrName;
		} else if (0x20 < ch && ch < 0x7f) {
			_tagName += ToLower(ch);
		} else {
			_stat = STAT_Error;
		}
		break;
	}
	case STAT_AttrName: {
		if (ch == '?') {
			// just ignore it
		} else if (ch == '>') {
			if (!AcceptTag(sig, _tagPrefix, _tagName.c_str(), _attrs)) return false;
			if (!IsComplete()) _stat = STAT_Init;
		} else if (IsSpace(ch)) {
			_stat = STAT_SeekEqual;
		} else if (ch == '=') {
			_stat = STAT_SkipSpace;
			_statNext = STAT_AttrValue;
		} else if (0x20 < ch && ch < 0x7f) {
			_attrName += ToLower(ch);
		} else {
			_stat = STAT_Error;
		}
		break;
	}
	case STAT_AttrValue: {
		if (ch == '\'') {
			_stat = STAT_AttrValueQuotedS;
		} else if (ch == '"') {
			_stat = STAT_AttrValueQuotedD;
		} else {
			Gura_Pushback();
			_stat = STAT_AttrValueNaked;
		}
		break;
	}
	case STAT_AttrValueQuotedS: {
		if (ch == '>') {
			_attrs[_attrName] = _attrValue;
			if (!AcceptTag(sig, _tagPrefix, _tagName.c_str(), _attrs)) return false;
			if (!IsComplete()) _stat = STAT_Init;
		} else if (ch == '\'') {
			_attrs[_attrName] = _attrValue;
			_attrName.clear(), _attrValue.clear();
			_stat = STAT_SkipSpace;
			_statNext = STAT_AttrName;
		} else {
			_attrValue += ch;
		}
		break;
	}
	case STAT_AttrValueQuotedD: {
		if (ch == '>') {
			_attrs[_attrName] = _attrValue;
			if (!AcceptTag(sig, _tagPrefix, _tagName.c_str(), _attrs)) return false;
			if (!IsComplete()) _stat = STAT_Init;
		} else if (ch == '"') {
			_attrs[_attrName] = _attrValue;
			_attrName.clear(), _attrValue.clear();
			_stat = STAT_SkipSpace;
			_statNext = STAT_AttrName;
		} else {
			_attrValue += ch;
		}
		break;
	}
	case STAT_AttrValueNaked: {
		if (ch == '>') {
			_attrs[_attrName] = _attrValue;
			if (!AcceptTag(sig, _tagPrefix, _tagName.c_str(), _attrs)) return false;
			if (!IsComplete()) _stat = STAT_Init;
		} else if (IsSpace(ch)) {
			_attrs[_attrName] = _attrValue;
			_attrName.clear(), _attrValue.clear();
			_stat = STAT_SkipSpace;
			_statNext = STAT_AttrName;
		} else {
			_attrValue += ch;
		}
		break;
	}
	case STAT_SeekEqual: {
		if (ch == '=') {
			_stat = STAT_SkipSpace;
			_statNext = STAT_AttrValue;
		} else if (IsSpace(ch)) {
			// nothing to do
		} else {
			_stat = STAT_Error;
		}
		break;
	}
	case STAT_Comment: {
		if (ch == '-') {
			_stat = STAT_Comment1stChar;
		} else {
			// nothing to do
		}
		break;
	}
	case STAT_Comment1stChar: {
		if (ch == '-') {
			_stat = STAT_Comment2ndChar;
		} else {
			_stat = STAT_Comment;
		}
		break;
	}
	case STAT_Comment2ndChar: {
		if (ch == '>') {
			_stat = STAT_Init;
		} else {
			_stat = STAT_Comment;
		}
		break;
	}
	case STAT_SkipSpace: {
		if (IsSpace(ch)) {
			// nothing to do
		} else {
			Gura_Pushback();
			_stat = _statNext;
		}
		break;
	}
	case STAT_Error: {
		break;
	}
	case STAT_Complete: {
		break;
	}
	}
	Gura_EndPushbackRegion();
	return true;
}

//-----------------------------------------------------------------------------
// EncodingDetector implementation
// This class detects the following patterns in HTML text.
// - <?xml .. encoding="xxxxxxxx"?>
// - <meta http-equiv="Content-Type" content="..; charset=xxxxxxxx />
//-----------------------------------------------------------------------------
bool EncodingDetector::AcceptTag(Signal &sig,
					char tagPrefix, const char *tagName, const Attrs &attrs)
{
	if (tagPrefix == '?' && ::strcasecmp(tagName, "xml") == 0) {
		Attrs::const_iterator iter = attrs.find("encoding");
		if (iter != attrs.end()) {
			_encoding = iter->second;
			_stat = STAT_Complete;
		}
	} else if (tagPrefix == '\0' && ::strcasecmp(tagName, "meta") == 0) {
		Attrs::const_iterator iter = attrs.find("http-equiv");
		if (iter != attrs.end() &&
				::strcasecmp(iter->second.c_str(), "Content-Type") == 0) {
			Attrs::const_iterator iter = attrs.find("content");
			if (iter != attrs.end()) {
				ContentType contentType;
				if (!contentType.Parse(sig, iter->second.c_str())) {
					return false;
				}
				_encoding = contentType.GetCharset();
			}
			_stat = STAT_Complete;
		}
	} else if (_tagPrefix == '/' && ::strcasecmp(tagName, "head") == 0) {
		_stat = STAT_Complete;
	}
	return true;
}

//-----------------------------------------------------------------------------
// LinkDetector implementation
//-----------------------------------------------------------------------------
bool LinkDetector::AcceptTag(Signal &sig,
					char tagPrefix, const char *tagName, const Attrs &attrs)
{
	return true;
}

//-----------------------------------------------------------------------------
// ContentType implementation
//-----------------------------------------------------------------------------
bool ContentType::Parse(Signal &sig, const char *str)
{
	const char *p = ::strchr(str, ';');
	if (p == nullptr) {
		_type = str;
		return true;
	}
	_type = String(str, p - str);
	//p++;
	//while (IsSpace(*p)) p++;
	// too-easy parsing
	for ( ; *p != '=' && *p != '\0'; p++) ;
	if (*p == '=') _charset = p + 1;
	return true;
}

//-----------------------------------------------------------------------------
// Header implementation
//-----------------------------------------------------------------------------
Header::Header(const Header &header) : _stat(STAT_Complete)
{
	foreach_const (Dict, iter, header._dict) {
		StringList *pStringList = iter->second;
		_dict[iter->first] = new StringList(*pStringList);
	}
}

Header::~Header()
{
	foreach (Dict, iter, _dict) {
		StringList *pStringList = iter->second;
		delete pStringList;
	}
}

void Header::Reset()
{
	_stat = STAT_LineTop;
	foreach (Dict, iter, _dict) {
		StringList *pStringList = iter->second;
		delete pStringList;
	}
	_dict.clear();
}

bool Header::ParseChar(Signal &sig, char ch)
{
	if (ch == '\r') return true;	// just skip CR code
	Gura_BeginPushbackRegion();
	switch (_stat) {
	case STAT_LineTop: {
		if (ch == '\n') {
			_stat = STAT_Complete;
		} else {
			_fieldName.clear();
			_fieldValue.clear();
			Gura_Pushback();
			_stat = STAT_FieldName;
		}
		break;
	}
	case STAT_FieldName: {
		if (ch == ':') {
			_fieldName = Strip(_fieldName.c_str());
			if (_fieldName.empty()) {
				SetError_InvalidFormat(sig);
				return false;
			}
			_stat = STAT_FieldValue;
		} else if (ch == '\n') {
			SetError_InvalidFormat(sig);
			return false;
		} else {
			_fieldName += ch;
		}
		break;
	}
	case STAT_FieldValue: {
		if (ch == '\n') {
			_fieldValue = Strip(_fieldValue.c_str());
			_stat = STAT_LineFolded;
		} else {
			_fieldValue += ch;
		}
		break;
	}
	case STAT_LineFolded: {
		if (ch == ' ' || ch == '\t') {
			_fieldValue += ' ';
			_stat = STAT_SkipWhiteSpace;
		} else {
			SetField(_fieldName.c_str(), _fieldValue.c_str());
			Gura_Pushback();
			_stat = STAT_LineTop;
		}
		break;
	}
	case STAT_SkipWhiteSpace: {
		if (ch == ' ' || ch == '\t') {
			// nothing to do
		} else {
			Gura_Pushback();
			_stat = STAT_FieldValue;
		}
		break;
	}
	case STAT_Complete: {
		break;
	}
	}
	Gura_EndPushbackRegion();
	return true;
}

void Header::SetField(const char *fieldName, const char *fieldValue)
{
	Dict::iterator iter = _dict.find(fieldName);
	StringList *pStringList = nullptr;
	if (iter == _dict.end()) {
		pStringList = new StringList();
		_dict[fieldName] = pStringList;
	} else {
		pStringList = iter->second;
	}
	pStringList->push_back(fieldValue);
}

bool Header::GetField(const char *fieldName, StringList **ppStringList) const
{
	Dict::const_iterator iter = _dict.find(fieldName);
	if (iter == _dict.end()) return false;
	if (ppStringList != nullptr) *ppStringList = iter->second;
	return true;
}

Value Header::GetField(Environment &env,
					Signal &sig, const char *fieldName, bool signalFlag) const
{
	StringList *pStringList = nullptr;
	Value value;
	Object_list *pObjList = value.InitAsList(env);
	if (GetField(fieldName, &pStringList)) {
		pObjList->Reserve(pStringList->size());
		foreach_const (StringList, pStr, *pStringList) {
			Value valueItem(*pStr);
			pObjList->Add(valueItem);
		}
	} else if (signalFlag) {
		sig.SetError(ERR_KeyError, "no field name %s", fieldName);
		return Value::Nil;
	}
	return value;
}

Value Header::GetFieldNames(Environment &env, Signal &sig) const
{
	Value valueRtn;
	Object_list *pObjListRtn = valueRtn.InitAsList(env);
	pObjListRtn->Reserve(_dict.size());
	foreach_const(Dict, iter, _dict) {
		const String &fieldName = iter->first;
		pObjListRtn->Add(Value(fieldName));
	}
	return valueRtn;
}

Value Header::IndexGet(Environment &env, const Value &valueIdx) const
{
	Signal &sig = env.GetSignal();
	if (!valueIdx.Is_string()) {
		sig.SetError(ERR_KeyError, "index must be a string");
		return Value::Nil;
	}
	const char *fieldName = valueIdx.GetString();
	StringList *pStringList = nullptr;
	if (GetField(fieldName, &pStringList)) {
		return Value(pStringList->back());
	} else {
		return Value::Nil;
	}
}

bool Header::GetTimeField(Environment &env, Signal &sig, const Symbol *pSymbol, Value &value) const
{
	StringList *pStringList = nullptr;
	if (pSymbol->IsIdentical(Gura_UserSymbol(date))) {
		// 14.18 Date
		if (GetField("Date", &pStringList)) {
			DateTime dt;
			if (!dt.Parse(pStringList->back().c_str())) {
				sig.SetError(ERR_FormatError, "invalid format of Date");
				return false;
			}
			value = Value(new Object_datetime(env, dt));
		}
		return true;
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(expires))) {
		// 14.21 Expires
		if (GetField("Expires", &pStringList)) {
			DateTime dt;
			if (!dt.Parse(pStringList->back().c_str())) {
				sig.SetError(ERR_FormatError, "invalid format of Expires");
				return false;
			}
			value = Value(new Object_datetime(env, dt));
		}
		return true;
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(last_modified))) {
		// 14.29 Last-Modified
		if (GetField("Last-Modified", &pStringList)) {
			DateTime dt;
			if (!dt.Parse(pStringList->back().c_str())) {
				sig.SetError(ERR_FormatError, "invalid format of Last-Modified");
				return false;
			}
			value = Value(new Object_datetime(env, dt));
		}
		return true;
	}
	return false;
}

bool Header::IsField(const char *fieldName, const char *value, bool *pFoundFlag) const
{
	StringList *pStringList;
	if (!GetField(fieldName, &pStringList)) {
		if (pFoundFlag != nullptr) *pFoundFlag = false;
		return false;
	}
	if (pFoundFlag != nullptr) *pFoundFlag = true;
	return ::strcasecmp(pStringList->back().c_str(), value) == 0;
}

bool Header::SetFields(Signal &sig, const ValueDict &valueDict, Stream *pStreamBody)
{
	foreach_const (ValueDict, iter, valueDict) {
		String fieldName = iter->first.ToString(false);
		if (sig.IsSignalled()) return false;
		String fieldValue = iter->second.ToString(false);
		if (sig.IsSignalled()) return false;
		SetField(fieldName.c_str(), fieldValue.c_str());
	}
	if (pStreamBody == nullptr) {
		SetField("Content-Length", "0");
	} else {
		size_t bytes = pStreamBody->GetSize();
		if (bytes != InvalidSize) {
			bytes -= pStreamBody->Tell();
			SetField("Content-Length", NumberToString(bytes).c_str());
		}
	}
	return true;
}

String Header::GetString() const
{
	String str;
	foreach_const (Dict, iter, _dict) {
		StringList *pStringList = iter->second;
		foreach_const (StringList, pStr, *pStringList) {
			str += iter->first;
			str += ": ";
			str += *pStr;
			str += "\r\n";
		}
	}
	return str;
}

Stream_Http *Header::GenerateDownStream(Environment &env, Signal &sig,
						Object *pObjOwner, int sock, const char *name) const
{
	bool chunkedFlag = false;
	bool gzipFlag = false;
	size_t bytes = InvalidSize;
	StringList *pStringList = nullptr;
	// RFC 2616 4.4 Message Length
	if (GetField("Transfer-Encoding", &pStringList)) {
		// RFC 2616 3.6 Transfer Codings
		// RFC 2616 14.41 Transfer-Encoding
		const char *fieldValue = pStringList->back().c_str();
		if (::strcasecmp(fieldValue, "chunked") == 0) {
			chunkedFlag = true;
			bytes = InvalidSize;
		}
	}
	if (GetField("Content-Length", &pStringList)) {
		// RFC 2616 14.13 Content-Length
		const char *fieldValue = pStringList->back().c_str();
		if (!chunkedFlag) {
			bytes = ::strtoul(fieldValue, nullptr, 0);
		}
	}
	ContentType contentType;
	if (GetField("Content-Type", &pStringList)) {
		// RFC 2616 14.17 Content-Type
		if (!contentType.Parse(sig, pStringList->back().c_str())) return nullptr;
	}
	if (GetField("Content-Encoding", &pStringList)) {
		// RFC 2616 14.11 Content-Encoding
		const char *fieldValue = pStringList->back().c_str();
		if (::strcasecmp(fieldValue, "gzip") == 0) {
			bytes = InvalidSize;
			gzipFlag = true;
		}
	}
	Stream *pStream = new Stream_Socket(env, Object::Reference(pObjOwner), sock);
	if (chunkedFlag) {
		Stream_Chunked *pStreamChunked =
						new Stream_Chunked(env, pStream, Stream::ATTR_Readable);
		pStream = pStreamChunked;
	}
	if (gzipFlag) {
		// Specifying 31 to windowBits doesn't work correctly here.
		ZLib::GZHeader hdr;
		hdr.Read(sig, *pStream);	// skip gz header
		ZLib::Stream_Inflater *pStreamInflater =
							new ZLib::Stream_Inflater(env, pStream, InvalidSize);
		pStreamInflater->Initialize(sig, -15);
		pStream = pStreamInflater;
	}
	AutoPtr<Stream_Http> pStreamHttp(new Stream_Http(env, pStream,
								Stream::ATTR_Readable, name, bytes, *this));
	const char *type = contentType.GetType();
	if (::strcasecmp(type, "text/html") == 0 || ::strcasecmp(type, "text/xml") == 0) {
		pStreamHttp->ActivateEncodingDetector();
	}
	if (contentType.IsValidCharset()) {
		AutoPtr<Codec> pCodec(Codec::CreateCodec(sig, contentType.GetCharset(), true, false));
		if (sig.IsSignalled()) return nullptr;
		pStreamHttp->SetCodec(pCodec.release());
	}
	return pStreamHttp.release();
}

void Header::DoDirProp(SymbolSet &symbols)
{
	symbols.insert(Gura_UserSymbol(date));
	symbols.insert(Gura_UserSymbol(expires));
	symbols.insert(Gura_UserSymbol(last_modified));
}

//-----------------------------------------------------------------------------
// Request implementation
//-----------------------------------------------------------------------------
bool Request::ParseChar(Signal &sig, char ch)
{
	if (ch == '\r') return true;	// just skip CR code
	Gura_BeginPushbackRegion();
	switch (_stat) {
	case STAT_Start: {
		if (IsSpace(ch)) {
			// nothing to do
		} else {
			_stat = STAT_Method;
			Gura_Pushback();
		}
		break;
	}
	case STAT_Method: {
		if (IsAlpha(ch)) {
			_method += ch;
		} else if (ch == ' ') {
			_stat = STAT_SkipSpace;
			_statNext = STAT_RequestURI;
		} else {
			SetError_InvalidFormat(sig);
			return false;
		}
		break;
	}
	case STAT_RequestURI: {
		if (ch == ' ') {
			_stat = STAT_SkipSpace;
			_statNext = STAT_HttpVersion;
		} else if (0x20 < ch && ch < 0x7f) {
			_requestURI += ch;
		} else {
			SetError_InvalidFormat(sig);
			return false;
		}
		break;
	}
	case STAT_HttpVersion: {
		if (ch == '\n') {
			_stat = STAT_Header;
		} else if (0x20 < ch && ch < 0x7f) {
			_httpVersion += ch;
		} else {
			SetError_InvalidFormat(sig);
			return false;
		}
		break;
	}
	case STAT_SkipSpace: {
		if (ch == ' ') {
			// nothing to do
		} else {
			Gura_Pushback();
			_stat = _statNext;
		}
		break;
	}
	case STAT_Header: {
		if (!_header.ParseChar(sig, ch)) return false;
		break;
	}
	}
	Gura_EndPushbackRegion();
	return true;
}

bool Request::Send(Signal &sig, int sock)
{
	String str;
	str += _method;
	str += " ";
	str += _requestURI;
	str += " ";
	str += _httpVersion;
	str += "\r\n";
	str += _header.GetString();
	str += "\r\n";
	::send(sock, str.data(), static_cast<int>(str.size()), 0);
	return true;
}

bool Request::Receive(Signal &sig, int sock)
{
	char ch;
	Reset();
	while (::recv(sock, &ch, 1, 0) > 0) {
		if (!ParseChar(sig, ch)) return false;
		if (IsComplete()) return true;
	}
	//sig.SetError(ERR_IOError, "connection closed while getting request");
	return true;
}

//-----------------------------------------------------------------------------
// Status implementation
//-----------------------------------------------------------------------------
const Status::CodePhrase Status::_codePhraseTbl[] = {
	// RFC 2616 10.1 Informational 1xx
	{ "100", "Continue",						CODE_Continue,						},
	{ "101", "Switching Protocols",				CODE_SwitchingProtocols,			},
	// RFC 2616 10.2 Successful 2xx
	{ "200", "OK",								CODE_OK,							},
	{ "201", "Created",							CODE_Created,						},
	{ "202", "Accepted",						CODE_Accepted,						},
	{ "203", "Non-Authoritative Information",	CODE_NonAuthoritativeInformation,	},
	{ "204", "No Content",						CODE_NoContent,						},
	{ "205", "Reset Content",					CODE_ResetContent,					},
	{ "206", "Partial content",					CODE_PartialContent,				},
	// RFC 2616 10.3 Redirection 3xx
	{ "300", "Multiple Choices",				CODE_MultipleChoices,				},
	{ "301", "Moved Permanently",				CODE_MovedPermanently,				},
	{ "302", "Found",							CODE_Found,							},
	{ "303", "See Other",						CODE_SeeOther,						},
	{ "304", "Not Modified",					CODE_NotModified,					},
	{ "305", "Use Proxy",						CODE_UseProxy,						},
	{ "307", "Temporary Redirect",				CODE_TemporaryRedirect,				},
	// RFC 2616 10.4 Client Error 4xx
	{ "400", "Bad Request",						CODE_BadRequest,					},
	{ "401", "Unauthorized",					CODE_Unauthorized,					},
	{ "402", "Payment Required",				CODE_PaymentRequired,				},
	{ "403", "Forbidden",						CODE_Forbidden,						},
	{ "404", "Not Found",						CODE_NotFound,						},
	{ "405", "Method Not Allowed",				CODE_MethodNotAllowed,				},
	{ "406", "Not Acceptable",					CODE_NotAcceptable,					},
	{ "407", "Proxy Authentication Required",	CODE_ProxyAuthenticationRequired,	},
	{ "408", "Request Time-out",				CODE_RequestTimeOut,				},
	{ "409", "Conflict",						CODE_Conflict,						},
	{ "410", "Gone",							CODE_Gone,							},
	{ "411", "Length Required",					CODE_LengthRequired,				},
	{ "412", "Precondition Failed",				CODE_PreconditionFailed,			},
	{ "413", "Request Entity Too Large",		CODE_RequestEntityTooLarge,			},
	{ "414", "Request-URI Too Large",			CODE_RequestURITooLarge,			},
	{ "415", "Unsupported Media Type",			CODE_UnsupportedMediaType,			},
	{ "416", "Requested range not satisfiable",	CODE_RequestedRangeNotSatisfiable,	},
	{ "417", "Expectation Failed",				CODE_ExpectationFailed,				},
	// RFC 2616 10.5 Server Error 5xx
	{ "500", "Internal Server Error",			CODE_InternalServerError,			},
	{ "501", "Not Implemented",					CODE_NotImplemented,				},
	{ "502", "Bad Gateway",						CODE_BadGateway,					},
	{ "503", "Service Unavailable",				CODE_ServiceUnavailable,			},
	{ "504", "Gateway Time-out",				CODE_GatewayTimeOut,				},
	{ "505", "HTTP Version not supported",		CODE_HTTPVersionNotSupported,		},
};

void Status::SetStatus(const char *httpVersion,
							const char *statusCode, const char *reasonPhrase)
{
	_httpVersion = httpVersion, _statusCode = statusCode;
	if (reasonPhrase == nullptr) {
		const CodePhrase *p = _codePhraseTbl;
		for (int i = 0; i < ArraySizeOf(_codePhraseTbl); i++, p++) {
			if (::strcasecmp(p->statusCode, statusCode) == 0) {
				reasonPhrase = p->reasonPhrase;
				break;
			}
		}
		if (reasonPhrase == nullptr) {
			reasonPhrase = "Unknown Status";
		}
	}
	_reasonPhrase = reasonPhrase;
	_header.Reset();
}

bool Status::ParseChar(Signal &sig, char ch)
{
	if (ch == '\r') return true;	// just skip CR code
	Gura_BeginPushbackRegion();
	switch (_stat) {
	case STAT_Start: {
		if (IsSpace(ch)) {
			// nothing to do
		} else {
			_stat = STAT_HttpVersion;
			Gura_Pushback();
		}
		break;
	}
	case STAT_HttpVersion: {
		if (ch == ' ') {
			_stat = STAT_SkipSpace;
			_statNext = STAT_StatusCode;
		} else if (0x20 < ch && ch < 0x7f) {
			_httpVersion += ch;
		} else {
			SetError_InvalidFormat(sig);
			return false;
		}
		break;
	}
	case STAT_StatusCode: {
		if (ch == ' ') {
			_stat = STAT_SkipSpace;
			_statNext = STAT_ReasonPhrase;
		} else if (0x20 < ch && ch < 0x7f) {
			_statusCode += ch;
		} else {
			SetError_InvalidFormat(sig);
			return false;
		}
		break;
	}
	case STAT_ReasonPhrase: {
		if (ch == '\n') {
			_stat = STAT_Header;
		} else if (0x20 <= ch && ch < 0x7f) {
			_reasonPhrase += ch;
		} else {
			SetError_InvalidFormat(sig);
			return false;
		}
		break;
	}
	case STAT_SkipSpace: {
		if (ch == ' ') {
			// nothing to do
		} else {
			Gura_Pushback();
			_stat = _statNext;
		}
		break;
	}
	case STAT_Header: {
		if (!_header.ParseChar(sig, ch)) return false;
		break;
	}
	}
	Gura_EndPushbackRegion();
	return true;
}

bool Status::Send(Signal &sig, int sock)
{
	String str;
	str += _httpVersion;
	str += " ";
	str += _statusCode;
	str += " ";
	str += _reasonPhrase;
	str += "\r\n";
	str += _header.GetString();
	str += "\r\n";
	::send(sock, str.data(), static_cast<int>(str.size()), 0);
	return true;
}

bool Status::Receive(Signal &sig, int sock)
{
	char ch;
	Reset();
	while (::recv(sock, &ch, 1, 0) > 0) {
		if (!ParseChar(sig, ch)) return false;
		if (IsComplete()) return true;
	}
	sig.SetError(ERR_IOError, "connection closed while getting status");
	return false;
}

//-----------------------------------------------------------------------------
// Stream_Socket implementation
//-----------------------------------------------------------------------------
Stream_Socket::Stream_Socket(Environment &env, Object *pObjOwner, int sock) :
		Stream(env, ATTR_Readable | ATTR_Writable), _pObjOwner(pObjOwner), _sock(sock)
{
}

Stream_Socket::~Stream_Socket()
{
}

const char *Stream_Socket::GetName() const
{
	return "socket";
}

const char *Stream_Socket::GetIdentifier() const
{
	return nullptr;
}

size_t Stream_Socket::DoRead(Signal &sig, void *buff, size_t bytes)
{
	int rtn = ::recv(_sock, reinterpret_cast<char *>(buff), static_cast<int>(bytes), 0);
	if (rtn < 0) {
		sig.SetError(ERR_IOError, "error while receiving from socket");
		return 0;
	}
	return rtn;
}

size_t Stream_Socket::DoWrite(Signal &sig, const void *buff, size_t bytes)
{
	int rtn = ::send(_sock, reinterpret_cast<const char *>(buff), static_cast<int>(bytes), 0);
	if (rtn < 0) {
		sig.SetError(ERR_IOError, "error while sending to socket");
		return 0;
	}
	return rtn;
}

bool Stream_Socket::DoSeek(Signal &sig, long offset, size_t offsetPrev, SeekMode seekMode)
{
	if (_sock < 0) return false;
	return false;
}

bool Stream_Socket::DoFlush(Signal &sig)
{
	if (_sock < 0) return false;
	return true;
}

bool Stream_Socket::DoClose(Signal &sig)
{
	return Stream::DoClose(sig);
}

size_t Stream_Socket::DoGetSize()
{
	return InvalidSize;
}

Object *Stream_Socket::DoGetStatObj(Signal &sig)
{
	sig.SetError(ERR_IOError, "can't retrieve stat object");
	return nullptr;
}

//-----------------------------------------------------------------------------
// Stream_Chunked implementation
//-----------------------------------------------------------------------------
Stream_Chunked::Stream_Chunked(Environment &env, Stream *pStream, UInt32 attr) :
		Stream(env, attr), _pStream(pStream), _bytesChunk(0), _doneFlag(false)
{
}

Stream_Chunked::~Stream_Chunked()
{
}

const char *Stream_Chunked::GetName() const
{
	return _pStream->GetName();
}

const char *Stream_Chunked::GetIdentifier() const
{
	return _pStream->GetIdentifier();
}

size_t Stream_Chunked::DoRead(Signal &sig, void *buff, size_t bytes)
{
	char *buffp = reinterpret_cast<char *>(buff);
	size_t offset = 0;
	while (offset < bytes) {
		if (_bytesChunk == 0) {
			if (_doneFlag) break;
			Chunk chunk;
			while (!chunk.IsComplete()) {
				char ch;
				if (_pStream->Read(sig, &ch, 1) < 1) return 0;
				if (!chunk.ParseChar(sig, ch)) return 0;
			}
			_bytesChunk = chunk.GetSize();
			if (_bytesChunk == 0) {
				_doneFlag = true;	// chunk end
				break;
			}
		}
		size_t bytesToRecv = ChooseMin(bytes - offset, _bytesChunk);
		size_t bytesRecved = _pStream->Read(sig, buffp + offset, bytesToRecv);
		if (sig.IsSignalled()) return 0;
		if (bytesRecved == 0) {
			// session closed
			break;
		}
		_bytesChunk -= bytesRecved;
		offset += bytesRecved;
	}
	return offset;
}

size_t Stream_Chunked::DoWrite(Signal &sig, const void *buff, size_t bytes)
{
	char buffChunkSep[32];
	::sprintf(buffChunkSep, "%zx\r\n", bytes);
	_pStream->Write(sig, buffChunkSep, ::strlen(buffChunkSep));
	_pStream->Write(sig, buff, bytes);
	return bytes;
}

bool Stream_Chunked::DoSeek(Signal &sig, long offset, size_t offsetPrev, SeekMode seekMode)
{
	size_t bytesToSkip = 0;
	if (seekMode == SeekSet) {
		if (static_cast<size_t>(offset) > offsetPrev) {
			bytesToSkip = static_cast<size_t>(offset) - offsetPrev;
		}
	} else if (seekMode == SeekCur) {
		if (offset > 0) bytesToSkip = static_cast<size_t>(offset);
	}
	const size_t bytesBuff = 32768;
	_pMemory.reset(new MemoryHeap(bytesBuff));
	void *buff = _pMemory->GetPointer();
	while (bytesToSkip > 0) {
		size_t bytesToRead = ChooseMin(bytesToSkip, bytesBuff);
		size_t bytesRead = DoRead(sig, buff, bytesToRead);
		if (sig.IsSignalled()) return false;
		if (bytesRead == 0) {
			sig.SetError(ERR_IOError, "seek error");
			return false;
		}
		bytesToSkip -= bytesRead;
	}
	return true;
}

bool Stream_Chunked::DoFlush(Signal &sig)
{
	if (_attr & ATTR_Writable) {
		char buffChunkSep[32];
		::sprintf(buffChunkSep, "0\r\n\r\n");
		_pStream->Write(sig, buffChunkSep, ::strlen(buffChunkSep));
		if (sig.IsSignalled()) return false;
	}
	return true;
}

bool Stream_Chunked::DoClose(Signal &sig)
{
	if (!DoFlush(sig)) return false;
	return Stream::DoClose(sig);
}

size_t Stream_Chunked::DoGetSize()
{
	return InvalidSize;
}

//-----------------------------------------------------------------------------
// Stream_Http implementation
//-----------------------------------------------------------------------------
Stream_Http::Stream_Http(Environment &env, Stream *pStream, UInt32 attr,
					const char *name, size_t bytes, const Header &header) :
		Stream(env, attr), _pStream(pStream), _name(name),
		_bytesRead(bytes), _header(header)
{
}

Stream_Http::~Stream_Http()
{
}

const char *Stream_Http::GetName() const
{
	return _name.c_str();
}

const char *Stream_Http::GetIdentifier() const
{
	return _name.c_str();
}

size_t Stream_Http::DoRead(Signal &sig, void *buff, size_t bytes)
{
	char *buffp = reinterpret_cast<char *>(buff);
	size_t offset = 0;
	while (offset < bytes) {
		size_t bytesToRecv = ChooseMin(bytes - offset, _bytesRead);
		size_t bytesRecved = _pStream->Read(sig, buffp + offset, bytesToRecv);
		if (sig.IsSignalled()) return 0;
		if (bytesRecved == 0) {
			// session closed
			break;
		}
		if (_encodingDetector.IsActive()) {
			for (size_t i = 0; i < bytesRecved && _encodingDetector.IsActive(); i++) {
				char ch = *(buffp + offset + i);
				if (!_encodingDetector.ParseChar(sig, ch)) return 0;
			}
			if (_encodingDetector.IsValidEncoding()) {
				AutoPtr<Codec> pCodec(Codec::CreateCodec(sig, _encodingDetector.GetEncoding(), true, false));
				if (sig.IsSignalled()) return 0;
				SetCodec(pCodec.release());
			}
		}
		_bytesRead -= bytesRecved;
		offset += bytesRecved;
	}
	return offset;
}

size_t Stream_Http::DoWrite(Signal &sig, const void *buff, size_t bytes)
{
	const char *buffp = reinterpret_cast<const char *>(buff);
	size_t offset = 0;
	while (offset < bytes) {
		size_t bytesToSend = bytes - offset;
		size_t bytesSent = _pStream->Write(sig, buffp + offset, bytesToSend);
		if (sig.IsSignalled()) return 0;
		offset += bytesSent;
	}
	return offset;
}

bool Stream_Http::DoSeek(Signal &sig, long offset, size_t offsetPrev, SeekMode seekMode)
{
	size_t bytesToSkip = 0;
	if (seekMode == SeekSet) {
		if (static_cast<size_t>(offset) > offsetPrev) {
			bytesToSkip = static_cast<size_t>(offset) - offsetPrev;
		}
	} else if (seekMode == SeekCur) {
		if (offset > 0) bytesToSkip = static_cast<size_t>(offset);
	}
	const size_t bytesBuff = 32768;
	_pMemory.reset(new MemoryHeap(bytesBuff));
	void *buff = _pMemory->GetPointer();
	while (bytesToSkip > 0) {
		size_t bytesToRead = ChooseMin(bytesToSkip, bytesBuff);
		size_t bytesRead = DoRead(sig, buff, bytesToRead);
		if (sig.IsSignalled()) return false;
		if (bytesRead == 0) {
			sig.SetError(ERR_IOError, "seek error");
			return false;
		}
		bytesToSkip -= bytesRead;
	}
	return true;
}

bool Stream_Http::DoFlush(Signal &sig)
{
	return true;
}

bool Stream_Http::DoClose(Signal &sig)
{
	return Stream::DoClose(sig);
}

size_t Stream_Http::DoGetSize()
{
	return _bytesRead;
}

Object *Stream_Http::DoGetStatObj(Signal &sig)
{
	return new Object_stat(_header);
}

bool Stream_Http::Cleanup(Signal &sig)
{
	if (GetSize() == InvalidSize) return true;
	const size_t bytesBuff = 32768;
	_pMemory.reset(new MemoryHeap(bytesBuff));
	void *buff = _pMemory->GetPointer();
	for (;;) {
		size_t bytesRead = Read(sig, buff, bytesBuff);
		if (bytesRead == 0) break;
	}
	return !sig.IsSignalled();
}

//-----------------------------------------------------------------------------
// Object_stat
//-----------------------------------------------------------------------------
Object_stat::~Object_stat()
{
}

Object *Object_stat::Clone() const
{
	return new Object_stat(*this);
}

bool Object_stat::DoDirProp(Environment &env, SymbolSet &symbols)
{
	Header::DoDirProp(symbols);
	return true;
}

Value Object_stat::DoGetProp(Environment &env, const Symbol *pSymbol,
						const SymbolSet &attrs, bool &evaluatedFlag)
{
	Signal &sig = GetSignal();
	Value value;
	if (_header.GetTimeField(env, sig, pSymbol, value)) {
		evaluatedFlag = true;
		return value;
	}
	return Value::Nil;
}

Value Object_stat::IndexGet(Environment &env, const Value &valueIdx)
{
	Signal &sig = GetSignal();
	return _header.IndexGet(env, valueIdx);
}

String Object_stat::ToString(bool exprFlag)
{
	return String("<http.stat>");
}

//-----------------------------------------------------------------------------
// Gura interfaces for Object_stat
//-----------------------------------------------------------------------------
// http.stat#field(name:string):map:[raise]
Gura_DeclareMethod(stat, field)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "name", VTYPE_string);
	DeclareAttr(Gura_Symbol(raise));
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(stat, field)
{
	Signal &sig = env.GetSignal();
	Object_stat *pThis = Object_stat::GetObjectThis(arg);
	bool signalFlag = arg.IsSet(Gura_Symbol(raise));
	return pThis->GetHeader().GetField(env, sig, arg.GetString(0), signalFlag);
}

// implementation of class Stat
Gura_ImplementUserClass(stat)
{
	Gura_AssignMethod(stat, field);
}

//-----------------------------------------------------------------------------
// Object_session implementation
//-----------------------------------------------------------------------------
Object_session::~Object_session()
{
	if (_sock >= 0) ::closesocket(_sock);
}

Object *Object_session::Clone() const
{
	return new Object_session(*this);
}

String Object_session::ToString(bool exprFlag)
{
	String rtn = "<http.session";
	do {
		rtn += ":";
		rtn += _remoteIP;
	} while (0);
	do {
		rtn += ":";
		rtn += _localIP;
	} while (0);
	rtn += ">";
	return rtn;
}

bool Object_session::ReceiveRequest(Signal &sig)
{
	Environment &env = *this;
	if (!_request.Receive(sig, _sock)) return false;
	if (_request.HasBody()) {
		Header &header = _request.GetHeader();
		_pStreamHttp.reset(header.GenerateDownStream(env, sig, this, _sock, ""));
		if (sig.IsSignalled()) return false;
	}
	return true;
}

bool Object_session::CleanupRequest(Signal &sig)
{
	if (_pStreamHttp.IsNull()) return true;
	bool rtn = _pStreamHttp->Cleanup(sig);
	_pStreamHttp.reset(nullptr);
	return rtn;
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------
// http.session#date
Gura_DeclareProperty_R(session, date)
{
	SetPropAttr(VTYPE_any);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(session, date)
{
	Object_session *pObjThis = Object_session::GetObject(valueThis);
	return Value(new Object_datetime(env, pObjThis->GetDateTime()));
}

// http.session#local_host
Gura_DeclareProperty_R(session, local_host)
{
	SetPropAttr(VTYPE_any);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(session, local_host)
{
	Object_session *pObjThis = Object_session::GetObject(valueThis);
	return Value(pObjThis->GetLocalHost());
}

// http.session#local_ip
Gura_DeclareProperty_R(session, local_ip)
{
	SetPropAttr(VTYPE_any);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(session, local_ip)
{
	Object_session *pObjThis = Object_session::GetObject(valueThis);
	return Value(pObjThis->GetLocalIP());
}

// http.session#remote_host
Gura_DeclareProperty_R(session, remote_host)
{
	SetPropAttr(VTYPE_any);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(session, remote_host)
{
	Object_session *pObjThis = Object_session::GetObject(valueThis);
	return Value(pObjThis->GetRemoteHost());
}

// http.session#remote_ip
Gura_DeclareProperty_R(session, remote_ip)
{
	SetPropAttr(VTYPE_any);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(session, remote_ip)
{
	Object_session *pObjThis = Object_session::GetObject(valueThis);
	return Value(pObjThis->GetRemoteIP());
}

// http.session#remote_logname
Gura_DeclareProperty_R(session, remote_logname)
{
	SetPropAttr(VTYPE_any);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(session, remote_logname)
{
	Object_session *pObjThis = Object_session::GetObject(valueThis);
	return Value(pObjThis->GetRemoteLogname());
}

// http.session#server
Gura_DeclareProperty_R(session, server)
{
	SetPropAttr(VTYPE_any);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(session, server)
{
	Object_session *pObjThis = Object_session::GetObject(valueThis);
	return Value(Object_server::Reference(pObjThis->GetObjServer()));
}

//-----------------------------------------------------------------------------
// Gura interfaces for Object_session
//-----------------------------------------------------------------------------
// implementation of class session
Gura_ImplementUserClass(session)
{
	// Assignment of properties
	Gura_AssignProperty(session, date);
	Gura_AssignProperty(session, local_host);
	Gura_AssignProperty(session, local_ip);
	Gura_AssignProperty(session, remote_host);
	Gura_AssignProperty(session, remote_ip);
	Gura_AssignProperty(session, remote_logname);
	Gura_AssignProperty(session, server);
}

//-----------------------------------------------------------------------------
// Object_request implementation
// for reference:
// http://httpd.apache.org/dev/apidoc/index.html
// http://www.temme.net/sander/api/httpd/httpd_8h-source.html
//-----------------------------------------------------------------------------
Object_request::~Object_request()
{
}

bool Object_request::DoDirProp(Environment &env, SymbolSet &symbols)
{
	Header::DoDirProp(symbols);
	return true;
}

Value Object_request::DoGetProp(Environment &env, const Symbol *pSymbol,
						const SymbolSet &attrs, bool &evaluatedFlag)
{
	Signal &sig = GetSignal();
	Request &request = _pObjSession->GetRequest();
	Header &header = request.GetHeader();
	Value value;
	if (header.GetTimeField(env, sig, pSymbol, value)) {
		evaluatedFlag = true;
		return value;
	}
	return Value::Nil;
}

Value Object_request::IndexGet(Environment &env, const Value &valueIdx)
{
	Signal &sig = GetSignal();
	Request &request = _pObjSession->GetRequest();
	return request.GetHeader().IndexGet(env, valueIdx);
}

Object *Object_request::Clone() const
{
	return nullptr;
}

String Object_request::ToString(bool exprFlag)
{
	Request &request = _pObjSession->GetRequest();
	String str = "<http.request:";
	str += request.GetMethod();
	str += " ";
	str += request.GetRequestURI();
	str += " ";
	str += request.GetHttpVersion();
	str += ">";
	return str;
}

bool Object_request::SendResponse(Signal &sig,
		const char *statusCode, const char *reasonPhrase, Stream *pStreamBody,
		const char *httpVersion, const ValueDict &valueDict)
{
	int sock = _pObjSession->GetSocket();
	Header &header = _status.GetHeader();
	_status.SetStatus(httpVersion, statusCode, reasonPhrase);
	if (!header.SetFields(sig, valueDict, pStreamBody)) return false;
	if (!_status.Send(sig, sock)) return false;
	if (pStreamBody != nullptr) {
		if (!SendStreamBody(sig, sock, *pStreamBody)) return false;
	}
	return true;
}

Stream *Object_request::SendRespChunk(Signal &sig,
		const char *statusCode, const char *reasonPhrase,
		const char *httpVersion, const ValueDict &valueDict)
{
	Environment &env = *this;
	int sock = _pObjSession->GetSocket();
	Header &header = _status.GetHeader();
	_status.SetStatus(httpVersion, statusCode, reasonPhrase);
	if (!header.SetFields(sig, valueDict, nullptr)) return nullptr;
	header.SetField("Transfer-Encoding", "chunked");
	if (!_status.Send(sig, sock)) return nullptr;
	AutoPtr<Stream> pStream(new Stream_Socket(env, Object::Reference(this), sock));
	if (sig.IsSignalled()) return nullptr;
	pStream.reset(new Stream_Chunked(env, pStream.release(), Stream::ATTR_Writable));
	if (sig.IsSignalled()) return nullptr;
	return pStream.release();
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------
// http.request#authority
Gura_DeclareProperty_R(request, authority)
{
	SetPropAttr(VTYPE_string);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(request, authority)
{
	Signal &sig = env.GetSignal();
	Object_request *pObjThis = Object_request::GetObject(valueThis);
	Request &request = pObjThis->GetObjSession()->GetRequest();
	String str = ExtractURIAuthority(sig, request.GetRequestURI(), nullptr);
	if (sig.IsSignalled()) return Value::Nil;
	String strUnquote = UnquoteURI(sig, str.c_str());
	if (sig.IsSignalled()) return Value::Nil;
	return Value(strUnquote);
}

// http.request#body
Gura_DeclareProperty_R(request, body)
{
	SetPropAttr(VTYPE_stream);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(request, body)
{
	Object_request *pObjThis = Object_request::GetObject(valueThis);
	Stream *pStream = pObjThis->GetObjSession()->GetStream();
	if (pStream == nullptr) return Value::Nil;
	return Value(new Object_stream(env, Stream::Reference(pStream)));
}

// http.request#fragment
Gura_DeclareProperty_R(request, fragment)
{
	SetPropAttr(VTYPE_string);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(request, fragment)
{
	Signal &sig = env.GetSignal();
	Object_request *pObjThis = Object_request::GetObject(valueThis);
	Request &request = pObjThis->GetObjSession()->GetRequest();
	String str = ExtractURIFragment(sig, request.GetRequestURI());
	if (sig.IsSignalled()) return Value::Nil;
	String strUnquote = UnquoteURI(sig, str.c_str());
	if (sig.IsSignalled()) return Value::Nil;
	return Value(strUnquote);
}

// http.request#method
Gura_DeclareProperty_R(request, method)
{
	SetPropAttr(VTYPE_any);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(request, method)
{
	Object_request *pObjThis = Object_request::GetObject(valueThis);
	Request &request = pObjThis->GetObjSession()->GetRequest();
	return Value(request.GetMethod());
}

// http.request#path
Gura_DeclareProperty_R(request, path)
{
	SetPropAttr(VTYPE_any);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(request, path)
{
	Signal &sig = env.GetSignal();
	Object_request *pObjThis = Object_request::GetObject(valueThis);
	Request &request = pObjThis->GetObjSession()->GetRequest();
	String str = ExtractURIPath(sig, request.GetRequestURI());
	if (sig.IsSignalled()) return Value::Nil;
	String strUnquote = UnquoteURI(sig, str.c_str());
	if (sig.IsSignalled()) return Value::Nil;
	return Value(strUnquote);
}

// http.request#query
Gura_DeclareProperty_R(request, query)
{
	SetPropAttr(VTYPE_any);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(request, query)
{
	Object_request *pObjThis = Object_request::GetObject(valueThis);
	Request &request = pObjThis->GetObjSession()->GetRequest();
	Value rtn;
	ValueDict &valDict = rtn.InitAsDict(env, true);
	Uri::ExtractQuery(request.GetRequestURI(), valDict);
	return rtn;
}

// http.request#scheme
Gura_DeclareProperty_R(request, scheme)
{
	SetPropAttr(VTYPE_any);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(request, scheme)
{
	Signal &sig = env.GetSignal();
	Object_request *pObjThis = Object_request::GetObject(valueThis);
	Request &request = pObjThis->GetObjSession()->GetRequest();
	String str = ExtractURIScheme(sig, request.GetRequestURI(), nullptr);
	if (sig.IsSignalled()) return Value::Nil;
	String strUnquote = UnquoteURI(sig, str.c_str());
	if (sig.IsSignalled()) return Value::Nil;
	return Value(strUnquote.c_str());
}

// http.request#session
Gura_DeclareProperty_R(request, session)
{
	SetPropAttr(VTYPE_any);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(request, session)
{
	Signal &sig = env.GetSignal();
	Object_request *pObjThis = Object_request::GetObject(valueThis);
	return Value(Object_session::Reference(pObjThis->GetObjSession()));
}

// http.request#uri
Gura_DeclareProperty_R(request, uri)
{
	SetPropAttr(VTYPE_any);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(request, uri)
{
	Object_request *pObjThis = Object_request::GetObject(valueThis);
	Request &request = pObjThis->GetObjSession()->GetRequest();
	return Value(request.GetRequestURI());
}

// http.request#version
Gura_DeclareProperty_R(request, version)
{
	SetPropAttr(VTYPE_any);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(request, version)
{
	Object_request *pObjThis = Object_request::GetObject(valueThis);
	Request &request = pObjThis->GetObjSession()->GetRequest();
	return Value(request.GetHttpVersion());
}

//-----------------------------------------------------------------------------
// Gura interfaces for Object_request
//-----------------------------------------------------------------------------
// http.request#field(name:string):map:[raise]
Gura_DeclareMethod(request, field)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "name", VTYPE_string);
	DeclareAttr(Gura_Symbol(raise));
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(request, field)
{
	Signal &sig = env.GetSignal();
	Object_request *pThis = Object_request::GetObjectThis(arg);
	bool signalFlag = arg.IsSet(Gura_Symbol(raise));
	return pThis->GetObjSession()->GetRequest().
				GetHeader().GetField(env, sig, arg.GetString(0), signalFlag);
}

// http.request#response(code:string, reason?:string, body?:stream:r,
//                       version:string => 'HTTP/1.1', header%):reduce
Gura_DeclareMethod(request, response)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "code", VTYPE_string);
	DeclareArg(env, "reason", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareArg(env, "body", VTYPE_stream, OCCUR_ZeroOrOnce, FLAG_Read);
	DeclareArg(env, "version", VTYPE_string,
			   OCCUR_Once, FLAG_None, 0, new Expr_Value(Value(HTTP_VERSION)));
	DeclareDictArg("header");
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(request, response)
{
	Signal &sig = env.GetSignal();
	Object_request *pThis = Object_request::GetObjectThis(arg);
	if (!pThis->SendResponse(sig,
			arg.GetString(0), arg.Is_string(1)? arg.GetString(1) : nullptr,
			arg.Is_stream(2)? &arg.GetStream(2) : nullptr, arg.GetString(3),
			arg.GetValueDictArg())) {
		return Value::Nil;
	}
	return arg.GetValueThis();
}

// http.request#respchunk(code:string, reason?:string,
//                        version:string => 'HTTP/1.1', header%) {block?}
Gura_DeclareMethod(request, respchunk)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "code", VTYPE_string);
	DeclareArg(env, "reason", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareArg(env, "version", VTYPE_string,
			   OCCUR_Once, FLAG_None, 0, new Expr_Value(Value(HTTP_VERSION)));
	DeclareDictArg("header");
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(request, respchunk)
{
	Signal &sig = env.GetSignal();
	Object_request *pThis = Object_request::GetObjectThis(arg);
	Stream *pStream = pThis->SendRespChunk(sig, arg.GetString(0),
			arg.Is_string(1)? arg.GetString(1) : nullptr, arg.GetString(2),
			arg.GetValueDictArg());
	if (sig.IsSignalled()) return Value::Nil;
	return ReturnValue(env, arg, Value(new Object_stream(env, pStream)));
}

// http.request#ismethod(method:string)
Gura_DeclareMethod(request, ismethod)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "method", VTYPE_string);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(request, ismethod)
{
	Object_request *pThis = Object_request::GetObjectThis(arg);
	const char *method = pThis->GetObjSession()->GetRequest().GetMethod();
	return Value(::strcasecmp(method, arg.GetString(0)) == 0);
}

// implementation of class Request
Gura_ImplementUserClass(request)
{
	// Assignment of properties
	Gura_AssignProperty(request, authority);
	Gura_AssignProperty(request, body);
	Gura_AssignProperty(request, fragment);
	Gura_AssignProperty(request, method);
	Gura_AssignProperty(request, path);
	Gura_AssignProperty(request, query);
	Gura_AssignProperty(request, scheme);
	Gura_AssignProperty(request, session);
	Gura_AssignProperty(request, uri);
	Gura_AssignProperty(request, version);
	// Assignment of methods
	Gura_AssignMethod(request, field);
	Gura_AssignMethod(request, response);
	Gura_AssignMethod(request, respchunk);
	Gura_AssignMethod(request, ismethod);
}

//-----------------------------------------------------------------------------
// Object_response implementation
//-----------------------------------------------------------------------------
Object_response::~Object_response()
{
}

bool Object_response::DoDirProp(Environment &env, SymbolSet &symbols)
{
	Header::DoDirProp(symbols);
	return true;
}

Value Object_response::DoGetProp(Environment &env, const Symbol *pSymbol,
						const SymbolSet &attrs, bool &evaluatedFlag)
{
	Signal &sig = GetSignal();
	Status &status = _pObjClient->GetStatus();
	Header &header = status.GetHeader();
	Value value;
	if (header.GetTimeField(env, sig, pSymbol, value)) {
		evaluatedFlag = true;
		return value;
	}
	return Value::Nil;
}

Value Object_response::IndexGet(Environment &env, const Value &valueIdx)
{
	Signal &sig = GetSignal();
	Status &status = _pObjClient->GetStatus();
	return status.GetHeader().IndexGet(env, valueIdx);
}

Object *Object_response::Clone() const
{
	return nullptr;
}

String Object_response::ToString(bool exprFlag)
{
	Status &status = _pObjClient->GetStatus();
	String str = "<http.response:";
	str += status.GetHttpVersion();
	str += " ";
	str += status.GetStatusCode();
	str += " ";
	str += status.GetReasonPhrase();
	str += ">";
	return str;
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------
// http.response#body
Gura_DeclareProperty_R(response, body)
{
	SetPropAttr(VTYPE_any);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(response, body)
{
	Object_response *pObjThis = Object_response::GetObject(valueThis);
	Stream *pStream = pObjThis->GetObjClient()->GetStream();
	if (pStream == nullptr) return Value::Nil;
	return Value(new Object_stream(env, Stream::Reference(pStream)));
}

// http.response#code
Gura_DeclareProperty_R(response, code)
{
	SetPropAttr(VTYPE_any);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(response, code)
{
	Object_response *pObjThis = Object_response::GetObject(valueThis);
	Status &status = pObjThis->GetObjClient()->GetStatus();
	return Value(status.GetStatusCode());
}

// http.response#field_names
Gura_DeclareProperty_R(response, field_names)
{
	SetPropAttr(VTYPE_any);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(response, field_names)
{
	Signal &sig = env.GetSignal();
	Object_response *pObjThis = Object_response::GetObject(valueThis);
	Status &status = pObjThis->GetObjClient()->GetStatus();
	Header &header = status.GetHeader();
	return header.GetFieldNames(env, sig);
}

// http.response#reason
Gura_DeclareProperty_R(response, reason)
{
	SetPropAttr(VTYPE_any);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(response, reason)
{
	Object_response *pObjThis = Object_response::GetObject(valueThis);
	Status &status = pObjThis->GetObjClient()->GetStatus();
	return Value(status.GetReasonPhrase());
}

// http.response#version
Gura_DeclareProperty_R(response, version)
{
	SetPropAttr(VTYPE_any);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(response, version)
{
	Object_response *pObjThis = Object_response::GetObject(valueThis);
	Status &status = pObjThis->GetObjClient()->GetStatus();
	return Value(status.GetHttpVersion());
}

//-----------------------------------------------------------------------------
// Gura interfaces for Object_response
//-----------------------------------------------------------------------------
// http.response#field(name:string):map:[raise]
Gura_DeclareMethod(response, field)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "name", VTYPE_string);
	DeclareAttr(Gura_Symbol(raise));
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(response, field)
{
	Signal &sig = env.GetSignal();
	Object_response *pThis = Object_response::GetObjectThis(arg);
	bool signalFlag = arg.IsSet(Gura_Symbol(raise));
	return pThis->GetObjClient()->GetStatus().
				GetHeader().GetField(env, sig, arg.GetString(0), signalFlag);
}

// implementation of class Response
Gura_ImplementUserClass(response)
{
	// Assignment of properties
	Gura_AssignProperty(response, body);
	Gura_AssignProperty(response, code);
	Gura_AssignProperty(response, field_names);
	Gura_AssignProperty(response, reason);
	Gura_AssignProperty(response, version);
	// Assignment of methods
	Gura_AssignMethod(request, field);
}

//-----------------------------------------------------------------------------
// Object_server implementation
//-----------------------------------------------------------------------------
Object_server::Object_server() :
		Object(Gura_UserClass(server)), _port(0), _sockListen(-1)
{
	FD_ZERO(&_fdsRead);
	::memset(&_saddrServer, 0x00, sizeof(_saddrServer));
}

Object_server::~Object_server()
{
	if (_sockListen >= 0) ::closesocket(_sockListen);
	foreach (SessionList, ppObjSession, _sessionList) {
		Object::Delete(*ppObjSession);
	}
}

Object *Object_server::Clone() const
{
	return nullptr; //new Object_server(*this);
}

String Object_server::ToString(bool exprFlag)
{
	String str;
	str += "<http.server:";
	if (_sockListen < 0) {
		str += "invalid";
	} else {
		str += _addr;
		str += ":";
		str += NumberToString(_port);
	}
	str += ">";
	return str;
}

bool Object_server::Prepare(Signal &sig, const char *addr, short port)
{
	_addr = (addr == nullptr)? "localhost" : addr;
	_port = port;
	_sockListen = static_cast<int>(::socket(AF_INET, SOCK_STREAM, 0));
	if (_sockListen < 0) {
		sig.SetError(ERR_IOError, "failed to create a socket");
		return false;
	}
	::memset(&_saddrServer, 0x00, sizeof(_saddrServer));
	UInt32 addrNum = htonl(INADDR_ANY);
	_saddrServer.sin_family = AF_INET;
	if (addr != nullptr) {
		addrNum = ::inet_addr(addr);
		if (addrNum == 0xffffffff) {
			hostent *pHostEnt = ::gethostbyname(addr);
			if (pHostEnt == nullptr) {
				sig.SetError(ERR_IOError, "binding address not found: %s", addr);
				return false;
			}
			_saddrServer.sin_family = pHostEnt->h_addrtype;
			addrNum = **reinterpret_cast<UInt32 **>(pHostEnt->h_addr_list);
		}
	}
	_saddrServer.sin_addr.s_addr = addrNum;
	_saddrServer.sin_port = htons(port);
	if (::bind(_sockListen, reinterpret_cast<sockaddr *>(&_saddrServer), sizeof(_saddrServer)) < 0) {
		sig.SetError(ERR_IOError, "failed to bind address to socket");
		return false;
	}
	if (::listen(_sockListen, 5) < 0) {
		sig.SetError(ERR_IOError, "failed to listen to port");
		return false;
	}
	return true;
}

Object_request *Object_server::Wait(Signal &sig)
{
	AutoPtr<Object_session> pObjSessionCur;
	for (SessionList::iterator ppObjSession = _sessionList.begin();
								ppObjSession != _sessionList.end(); ) {
		Object_session *pObjSession = *ppObjSession;
		Header &header = pObjSession->GetRequest().GetHeader();
		if (header.IsField("Connection", "keep-alive")) {
			ppObjSession++;
		} else {
			::closesocket(pObjSession->GetSocket());
			Object::Delete(pObjSession);
			ppObjSession = _sessionList.erase(ppObjSession);
		}
	}
	foreach (SessionList, ppObjSession, _sessionList) {
		Object_session *pObjSession = *ppObjSession;
		if (!pObjSession->CleanupRequest(sig)) return nullptr;
	}
	for (;;) {
		bool requestFlag = false;
		if (FD_ISSET(_sockListen, &_fdsRead)) {
			FD_CLR(static_cast<UInt>(_sockListen), &_fdsRead);
			sockaddr_in saddrClient;
			socklen_t bytesAddr = sizeof(saddrClient);
			int sockClient = static_cast<int>(::accept(_sockListen,
							reinterpret_cast<sockaddr *>(&saddrClient), &bytesAddr));
			if (sockClient < 0) {
				sig.SetError(ERR_IOError, "failed to accept connection request");
				return nullptr;
			}
			const hostent *pHostEnt = nullptr;
			String remoteIP = ::inet_ntoa(saddrClient.sin_addr);
			String remoteHost(remoteIP);
			pHostEnt = ::gethostbyaddr(
					reinterpret_cast<char *>(&saddrClient.sin_addr), 4, AF_INET);
			if (pHostEnt != nullptr) remoteHost = pHostEnt->h_name;
			const char *remoteLogname = "";
			String localIP = ::inet_ntoa(_saddrServer.sin_addr);
			String localHost(localIP);
			pHostEnt = ::gethostbyaddr(
					reinterpret_cast<char *>(&_saddrServer.sin_addr), 4, AF_INET);
			if (pHostEnt != nullptr) localHost = pHostEnt->h_name;
			DateTime dateTime = OAL::GetCurDateTime(false);
			AutoPtr<Object_session> pObjSession(new Object_session(
					Object_server::Reference(this), sockClient,
					remoteIP.c_str(), remoteHost.c_str(), remoteLogname,
					localIP.c_str(), localHost.c_str(), dateTime));
			_sessionList.push_back(pObjSession.get());
			pObjSessionCur.reset(Object_session::Reference(pObjSession.release()));
		} else {
			foreach (SessionList, ppObjSession, _sessionList) {
				Object_session *pObjSession = *ppObjSession;
				if (!pObjSession->IsValid()) continue;
				int sock = pObjSession->GetSocket();
				if (FD_ISSET(static_cast<UInt>(sock), &_fdsRead)) {
					FD_CLR(static_cast<UInt>(sock), &_fdsRead);
					requestFlag = true;
					pObjSessionCur.reset(Object_session::Reference(pObjSession));
					break;
				}
			}
		}
		if (requestFlag) {
			if (!pObjSessionCur->ReceiveRequest(sig)) return nullptr;
			if (pObjSessionCur->GetRequest().IsComplete()) break;
			SessionList::iterator ppObjSession = std::find(_sessionList.begin(),
										_sessionList.end(), pObjSessionCur.get());
			_sessionList.erase(ppObjSession);
			::closesocket(pObjSessionCur->GetSocket());
			pObjSessionCur.reset(nullptr);
		}
		FD_ZERO(&_fdsRead);
		FD_SET(static_cast<UInt>(_sockListen), &_fdsRead);
		int sockMax = _sockListen;
		foreach (SessionList, ppObjSession, _sessionList) {
			Object_session *pObjSession = *ppObjSession;
			if (pObjSession->IsValid()) {
				int sock = pObjSession->GetSocket();
				FD_SET(static_cast<UInt>(sock), &_fdsRead);
				if (sockMax < sock) sockMax = sock;
			}
		}
		::select(sockMax + 1, &_fdsRead, nullptr, nullptr, nullptr);
	}
	return new Object_request(pObjSessionCur.release());
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------
// http.server#sessions
Gura_DeclareProperty_R(server, sessions)
{
	SetPropAttr(VTYPE_any);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(server, sessions)
{
	Object_server *pObjThis = Object_server::GetObject(valueThis);
	Object_server::SessionList &sessionList = pObjThis->GetSessionList();
	Value rtn;
	Object_list *pObjList = rtn.InitAsList(env);
	pObjList->Reserve(sessionList.size());
	foreach (Object_server::SessionList, ppObjSession, sessionList) {
		Object_session *pObjSession = *ppObjSession;
		pObjList->Add(Value(Object_session::Reference(pObjSession)));
	}
	return rtn;
}

//-----------------------------------------------------------------------------
// Gura interfaces for Object_server
//-----------------------------------------------------------------------------
// http.server#wait() {block?}
Gura_DeclareMethod(server, wait)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(server, wait)
{
	Signal &sig = env.GetSignal();
	Object_server *pThis = Object_server::GetObjectThis(arg);
	if (!arg.IsBlockSpecified()) {
		Object_request *pObjRequest = pThis->Wait(sig);
		if (sig.IsSignalled()) return Value::Nil;
		return Value(pObjRequest);
	}
	AutoPtr<Environment> pEnvBlock(env.Derive(ENVTYPE_block));
	const Function *pFuncBlock =
					arg.GetBlockFunc(*pEnvBlock, GetSymbolForBlock());
	if (pFuncBlock == nullptr) return Value::Nil;
	for (;;) {
		Object_request *pObjRequest = pThis->Wait(sig);
		if (sig.IsSignalled()) return Value::Nil;
		AutoPtr<Argument> pArgSub(new Argument(pFuncBlock));
		if (!pArgSub->StoreValue(env, Value(pObjRequest))) return Value::Nil;
		pFuncBlock->Eval(env, *pArgSub);
		if (sig.IsBreak()) {
			sig.ClearSignal();
			break;
		} else if (sig.IsContinue()) {
			sig.ClearSignal();
		} else if (sig.IsSignalled()) {
			break;
		}
	}
	return Value::Nil;
}

// implementation of class Server
Gura_ImplementUserClass(server)
{
	// Assignment of properties
	Gura_AssignProperty(server, sessions);
	// Assignment of methods
	Gura_AssignMethod(server, wait);
}

//-----------------------------------------------------------------------------
// Object_client implementation
//-----------------------------------------------------------------------------
Object_client::~Object_client()
{
	if (_sock >= 0) ::closesocket(_sock);
}

Object *Object_client::Clone() const
{
	return nullptr; //new Object_client(*this);
}

String Object_client::ToString(bool exprFlag)
{
	String str;
	str += "<http.client:";
	str += _addr;
	str += ":";
	str += NumberToString(_port);
	if (IsViaProxy()) {
		str += " via ";
		str += _addrProxy;
		str += ":";
		str += NumberToString(_portProxy);
	}
	str += (_sock < 0)? ":closed" : ":connected";
	str += ">";
	return str;
}

bool Object_client::Prepare(Signal &sig, const char *addr, short port,
				const char *addrProxy, short portProxy,
				const char *userIdProxy, const char *passwordProxy)
{
	if (addrProxy == nullptr) {
		const Value *pValueOfList = _pEnvThis->LookupValue(Gura_UserSymbol(proxies), ENVREF_NoEscalate);
		if (pValueOfList != nullptr && pValueOfList->Is_list()) {
			foreach_const_reverse (ValueList, pValue, pValueOfList->GetList()) {
				if (!pValue->IsType(VTYPE_proxy)) continue;
				Object_proxy *pObjProxy = Object_proxy::GetObject(*pValue);
				Environment &env = *this;
				if (pObjProxy->IsResponsible(env, addr)) {
	Signal &sig = env.GetSignal();
					addrProxy = pObjProxy->GetAddr();
					portProxy = pObjProxy->GetPort();
					userIdProxy = pObjProxy->GetUserId();
					passwordProxy = pObjProxy->GetPassword();
					break;
				}
				if (sig.IsSignalled()) return false;
			}
		}
	}
	const char *addrToConnect = addr;
	short portToConnect = port;
	_addr = addr, _port = port;
	if (addrProxy != nullptr) {
		_addrProxy = addrProxy, _portProxy = portProxy;
		_userIdProxy = userIdProxy, _passwordProxy = passwordProxy;
		addrToConnect = addrProxy, portToConnect = portProxy;
	}
	_sock = static_cast<int>(::socket(AF_INET, SOCK_STREAM, 0)); //IPPROTO_TCP);
	if (_sock < 0) {
		sig.SetError(ERR_IOError, "failed to create a socket");
		return false;
	}
	sockaddr_in saddrServer;
	::memset(&saddrServer, 0x00, sizeof(saddrServer));
	UInt32 addrNum = ::inet_addr(addrToConnect);
	if (addrNum == 0xffffffff) {
		hostent *pHostEnt = ::gethostbyname(addrToConnect);
		if (pHostEnt == nullptr) {
			sig.SetError(ERR_IOError, "host not found: %s", addrToConnect);
			return false;
		}
		saddrServer.sin_family = pHostEnt->h_addrtype;
		addrNum = **reinterpret_cast<UInt32 **>(pHostEnt->h_addr_list);
	} else {
		saddrServer.sin_family = AF_INET;
	}
	saddrServer.sin_addr.s_addr = addrNum;
	saddrServer.sin_port = htons(portToConnect);
	if (::connect(_sock, reinterpret_cast<sockaddr *>(&saddrServer), sizeof(saddrServer)) < 0) {
		sig.SetError(ERR_IOError, "failed to connect to%s host %s",
							IsViaProxy()? " proxy" : "", addrToConnect);
		return false;
	}
	return true;
}

Object_response *Object_client::SendRequest(Signal &sig,
		const char *method, const char *uri, Stream *pStreamBody,
		const char *httpVersion, const ValueDict &valueDict)
{
	Environment &env = *this;
	if (!CleanupResponse(sig)) return nullptr;
	if (_sock < 0) {
		sig.SetError(ERR_IOError, "access to invalid socket");
		return nullptr;
	}
	String uriFull;
	uriFull = "http://";
	uriFull += _addr;
	uriFull += uri;
	_request.SetRequest(method, IsViaProxy()? uriFull.c_str() : uri, httpVersion);
	Header &header = _request.GetHeader();
	if (!header.SetFields(sig, valueDict, pStreamBody)) return nullptr;
	do {
		String str;
		str += _addr;
		str += ":";
		str += NumberToString(_port);
		header.SetField("Host", str.c_str());
	} while (0);
	if (!_userIdProxy.empty()) {
		String str;
		str = _userIdProxy;
		str += ":";
		str += _passwordProxy;
		Binary buff;
		buff = "Basic ";
		do {
			Environment &env = *this;
			Object_binary *pObjBinary = new Object_binary(env);
			Stream_Base64Writer stream(
				env, new Pointer::StreamEx(
					env, new Object_binary::PointerEx(0, pObjBinary)), 0);
			stream.Write(sig, str.data(), str.size());
			if (sig.IsSignalled()) return nullptr;
			buff += pObjBinary->GetBinary();
		} while (0);
		header.SetField("Proxy-Authorization", buff.c_str());
	}
	if (!_request.Send(sig, _sock)) return nullptr;
	if (pStreamBody != nullptr) {
		if (!SendStreamBody(sig, _sock, *pStreamBody)) return nullptr;
	}
	if (!_status.Receive(sig, _sock)) return nullptr;
	if (::strcasecmp(method, "HEAD") != 0 && _status.HasBody()) {
		Header &header = _status.GetHeader();
		_pStreamHttp.reset(header.GenerateDownStream(env, sig, this, _sock, uriFull.c_str()));
		if (sig.IsSignalled()) return nullptr;
	}
	return new Object_response(Object_client::Reference(this));
}

bool Object_client::CleanupResponse(Signal &sig)
{
	if (_pStreamHttp.IsNull()) return true;
	Header &header = _status.GetHeader();
	bool rtn = true;
	if (header.IsField("Connection", "close")) {
		::closesocket(_sock);
		_sock = -1;
	} else if (header.IsField("Proxy-Connection", "close")) {
		::closesocket(_sock);
		_sock = -1;
	} else {
		rtn = _pStreamHttp->Cleanup(sig);
	}
	_pStreamHttp.reset(nullptr);
	return rtn;
}

//-----------------------------------------------------------------------------
// Gura interfaces for Object_client
//-----------------------------------------------------------------------------
// http.client#request(method:string, uri:string, body?:stream:r,
//                     version:string => 'HTTP/1.1', header%) {block?}
Gura_DeclareMethod(client, request)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "method", VTYPE_string);
	DeclareArg(env, "uri", VTYPE_string);
	DeclareArg(env, "body", VTYPE_stream, OCCUR_ZeroOrOnce, FLAG_Read);
	DeclareArg(env, "version", VTYPE_string,
			   OCCUR_Once, FLAG_None, 0, new Expr_Value(Value(HTTP_VERSION)));
	DeclareDictArg("header");
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(client, request)
{
	Signal &sig = env.GetSignal();
	Object_client *pThis = Object_client::GetObjectThis(arg);
	Object_response *pObjResponse = pThis->SendRequest(sig,
			arg.GetString(0), arg.GetString(1),
			arg.Is_stream(2)? &arg.GetStream(2) : nullptr,
			arg.GetString(3), arg.GetValueDictArg());
	if (sig.IsSignalled()) return Value::Nil;
	return ReturnValue(env, arg, Value(pObjResponse));
}

// http.client#_request(uri:string, body?:stream:r,
//                     version:string => 'HTTP/1.1', header%) {block?}
Gura_DeclareMethod(client, _request)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "uri", VTYPE_string);
	DeclareArg(env, "body", VTYPE_stream, OCCUR_ZeroOrOnce, FLAG_Read);
	DeclareArg(env, "version", VTYPE_string,
			   OCCUR_Once, FLAG_None, 0, new Expr_Value(Value(HTTP_VERSION)));
	DeclareDictArg("header");
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(client, _request)
{
	Signal &sig = env.GetSignal();
	Object_client *pThis = Object_client::GetObjectThis(arg);
	Object_response *pObjResponse = pThis->SendRequest(sig,
			Upper(GetName()).c_str(), arg.GetString(0),
			arg.Is_stream(1)? &arg.GetStream(1) : nullptr,
			arg.GetString(2), arg.GetValueDictArg());
	if (sig.IsSignalled()) return Value::Nil;
	return ReturnValue(env, arg, Value(pObjResponse));
}

// http.client#cleanup()
Gura_DeclareMethod(client, cleanup)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_None);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(client, cleanup)
{
	Signal &sig = env.GetSignal();
	Object_client *pThis = Object_client::GetObjectThis(arg);
	if (!pThis->CleanupResponse(sig)) return Value::Nil;
	return arg.GetValueThis();
}

// implementation of class Client
Gura_ImplementUserClass(client)
{
	Gura_AssignMethod(client, request);
	Gura_AssignMethod(client, cleanup);
	Gura_AssignMethodEx(client, _request, "options");	// RFC 2616 9.2
	Gura_AssignMethodEx(client, _request, "get");		// RFC 2616 9.3
	Gura_AssignMethodEx(client, _request, "head");		// RFC 2616 9.4
	Gura_AssignMethodEx(client, _request, "post");		// RFC 2616 9.5
	Gura_AssignMethodEx(client, _request, "put");		// RFC 2616 9.6
	Gura_AssignMethodEx(client, _request, "delete");	// RFC 2616 9.7
	Gura_AssignMethodEx(client, _request, "trace");		// RFC 2616 9.8
	Gura_AssignMethodEx(client, _request, "connect");	// RFC 2616 9.9
}

//-----------------------------------------------------------------------------
// Object_proxy implementation
//-----------------------------------------------------------------------------
Object_proxy::~Object_proxy()
{
}

Object *Object_proxy::Clone() const
{
	return nullptr;
}

String Object_proxy::ToString(bool exprFlag)
{
	String str;
	str += "<http.proxy:";
	str += _addr;
	str += ":";
	str += NumberToString(_port);
	str += ">";
	return str;
}

bool Object_proxy::IsResponsible(Environment &env, const char *addr) const
{
	Signal &sig = env.GetSignal();
	if (_pFuncCriteria.IsNull()) return true;
	AutoPtr<Argument> pArg(new Argument(_pFuncCriteria.get()));
	if (!pArg->StoreValue(env, Value(addr))) return false;
	Value result = _pFuncCriteria->Eval(env, *pArg);
	if (sig.IsSignalled()) return false;
	return result.GetBoolean();
}

//-----------------------------------------------------------------------------
// Gura interfaces for Object_proxy
//-----------------------------------------------------------------------------
// implementation of class Proxy
Gura_ImplementUserClass(proxy)
{
}

//-----------------------------------------------------------------------------
// Gura module functions: http
//-----------------------------------------------------------------------------
// http.addproxy(addr:string, port:number, userid?:string, password?:string) {criteria?}
Gura_DeclareFunction(addproxy)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "addr", VTYPE_string);
	DeclareArg(env, "port", VTYPE_number);
	DeclareArg(env, "userid", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareArg(env, "password", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce, Symbol::Add("criteria"));
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementFunction(addproxy)
{
	Signal &sig = env.GetSignal();
	Object_list *pObjList = nullptr;
	Value *pValue = _pEnvThis->LookupValue(Gura_UserSymbol(proxies), ENVREF_NoEscalate);
	if (pValue == nullptr || !pValue->Is_list()) {
		Value value;
		pObjList = value.InitAsList(env);
		_pEnvThis->AssignValue(Gura_UserSymbol(proxies), value, EXTRA_Public);
	} else {
		pObjList = pValue->GetObjList();
	}
	const Function *pFuncCriteria = arg.GetBlockFunc(env, GetSymbolForBlock());
	Value value(new Object_proxy(arg.GetString(0), arg.GetShort(1),
				arg.Is_string(2)? arg.GetString(2) : "",
				arg.Is_string(3)? arg.GetString(3) : "",
				Function::Reference(pFuncCriteria)));
	pObjList->Add(value);
	return Value::Nil;
}

// http.server(addr?:string, port:number => 80) {block?}
Gura_DeclareFunction(server)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "addr", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareArg(env, "port", VTYPE_number,
			   OCCUR_Once, FLAG_None, 0, new Expr_Value(80));
	DeclareBlock(OCCUR_ZeroOrOnce);
	SetClassToConstruct(Gura_UserClass(server));
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementFunction(server)
{
	Signal &sig = env.GetSignal();
	AutoPtr<Object_server> pObjServer(new Object_server());
	if (!pObjServer->Prepare(sig,
				arg.Is_string(0)? arg.GetString(0) : nullptr, arg.GetShort(1))) {
		return Value::Nil;
	}
	return ReturnValue(env, arg, Value(pObjServer.release()));
}

// http.client(addr:string, port:number => 80,
//             addrProxy?:string, portProxy?:number,
//             useridProxy?:string, passwordProxy?:string) {block?}
Gura_DeclareFunction(client)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "addr", VTYPE_string);
	DeclareArg(env, "port", VTYPE_number,
			   OCCUR_Once, FLAG_None, 0, new Expr_Value(80));
	DeclareArg(env, "addrProxy", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareArg(env, "portProxy", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "useridProxy", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareArg(env, "passwordProxy", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
	SetClassToConstruct(Gura_UserClass(client));
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementFunction(client)
{
	Signal &sig = env.GetSignal();
	AutoPtr<Object_client> pObjClient(new Object_client());
	const char *addrProxy = nullptr;
	short portProxy = 0;
	const char *userIdProxy = "";
	const char *passwordProxy = "";
	if (arg.Is_string(2)) {
		if (!arg.Is_number(3)) {
			Declaration::SetError_NotEnoughArguments(env);
			return Value::Nil;
		}
		addrProxy = arg.GetString(2);
		portProxy = arg.GetShort(3);
		if (arg.Is_string(4)) userIdProxy = arg.GetString(4);
		if (arg.Is_string(5)) passwordProxy = arg.GetString(5);
	}
	if (!pObjClient->Prepare(sig, arg.GetString(0), arg.GetShort(1),
							addrProxy, portProxy, userIdProxy, passwordProxy)) {
		return Value::Nil;
	}
	return ReturnValue(env, arg, Value(pObjClient.release()));
}

//-----------------------------------------------------------------------------
// Directory_Http implementation
//-----------------------------------------------------------------------------
Directory_Http::Directory_Http(Directory *pParent, const char *name, Type type) :
	Directory(pParent, name, type, '/', false)
{
}

Directory_Http::~Directory_Http()
{
}

Directory *Directory_Http::DoNext(Environment &env)
{
	Signal &sig = env.GetSignal();
	sig.SetError(ERR_SystemError, "");
	return nullptr;
}

Stream *Directory_Http::DoOpenStream(Environment &env, UInt32 attr)
{
	Signal &sig = env.GetSignal();
	AutoPtr<Object_client> pObjClient(new Object_client());
	String pathName;
	Directory_Http *pDirectoryTop = nullptr;
	if (IsContainer()) pathName = "/";
	for (Directory_Http *pDirectory = this; pDirectory != nullptr;
		pDirectory = dynamic_cast<Directory_Http *>(pDirectory->GetParent())) {
		if (pDirectory->GetParent() == nullptr) {
			pDirectoryTop = pDirectory;
		} else {
			String str = "/";
			str += pDirectory->GetName();
			pathName = str + pathName;
		}
	}
	if (pathName.empty()) pathName = "/";
	do {
		const char *query = pDirectoryTop->GetQuery();
		if (*query != '\0') {
			pathName += "?";
			pathName += query;
		}
	} while (0);
	do {
		const char *fragment = pDirectoryTop->GetFragment();
		if (*fragment != '\0') {
			pathName += "#";
			pathName += fragment;
		}
	} while (0);
	//::printf("%s %s\n", pDirectoryTop->GetAuthority(), pathName.c_str());
	short port = 80;
	const char *addrProxy = nullptr;
	short portProxy = 0;
	const char *userIdProxy = "";
	const char *passwordProxy = "";
	if (!pObjClient->Prepare(sig, pDirectoryTop->GetAuthority(), port, nullptr, 0, "", "")) {
		return nullptr;
	}
	AutoPtr<Object_response> pObjResponse(pObjClient->SendRequest(sig,
				"GET", pathName.c_str(), nullptr, HTTP_VERSION, ValueDict::Empty));
	if (sig.IsSignalled()) return nullptr;
	Stream *pStream = pObjClient->GetStream();
	if (pStream == nullptr) {
		sig.SetError(ERR_IOError, "no body");
		return nullptr;
	}
	Status &status = pObjClient->GetStatus();
	if (::strcmp(status.GetStatusCode(), "200") != 0) {
		sig.SetError(ERR_IOError, "%s %s",
					status.GetStatusCode(), status.GetReasonPhrase());
		return nullptr;
	}
	return Stream::Reference(pStream);
}

//-----------------------------------------------------------------------------
// PathMgr_Http implementation
//-----------------------------------------------------------------------------
bool PathMgr_Http::IsResponsible(Environment &env,
						const Directory *pParent, const char *pathName)
{
	return pParent == nullptr &&
		(StartsWith(pathName, "http:", 0, false) ||
		 StartsWith(pathName, "https:", 0, false));
}

Directory *PathMgr_Http::DoOpenDirectory(Environment &env,
		Directory *pParent, const char **pPathName, NotFoundMode notFoundMode)
{
	Signal &sig = env.GetSignal();
	const char *uri = *pPathName;
	String scheme = ExtractURIScheme(sig, uri, nullptr);
	const char *p = uri;
	String authority = ExtractURIAuthority(sig, p, &p);
	String field;
	Directory_Http *pDirectoryTop, *pDirectory;
	do {
		String name = scheme;
		name += "://";
		name += authority;
		name += field;
		pDirectoryTop = pDirectory = new Directory_Http(
						nullptr, name.c_str(), Directory::TYPE_Container);
		pParent = pDirectory;
		for ( ; *p == '/'; p++) ;
	} while (0);
	for ( ; ; p++) {
		char ch = *p;
		if (ch == '/' || ch == '\0' || ch == '?' || ch == '#') {
			Directory::Type type = IsFileSeparator(ch)?
						Directory::TYPE_Container : Directory::TYPE_Item;
			pDirectory = new Directory_Http(
						Directory::Reference(pParent), field.c_str(), type);
			pParent = pDirectory;
			field.clear();
			if (!IsFileSeparator(ch)) break;
		} else {
			field += ch;
		}
	}
	pDirectoryTop->SetScheme(scheme.c_str());
	pDirectoryTop->SetAuthority(authority.c_str());
	pDirectoryTop->SetQuery(ExtractURIQuery(sig, p).c_str());
	if (sig.IsSignalled()) return nullptr;
	pDirectoryTop->SetFragment(ExtractURIFragment(sig, p).c_str());
	if (sig.IsSignalled()) return nullptr;
	*pPathName = uri + ::strlen(uri);
	return pDirectory;
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
	_pEnvThis = &env;
#if defined(GURA_ON_MSWIN)
	WSADATA wsaData;
	::WSAStartup(MAKEWORD(2, 0), &wsaData);
#endif
	// symbol realization
	Gura_RealizeUserSymbol(request);
	Gura_RealizeUserSymbol(status);
	Gura_RealizeUserSymbol(field_names);
	Gura_RealizeUserSymbol(method);
	Gura_RealizeUserSymbol(uri);
	Gura_RealizeUserSymbol(scheme);
	Gura_RealizeUserSymbol(authority);
	Gura_RealizeUserSymbol(path);
	Gura_RealizeUserSymbol(query);
	Gura_RealizeUserSymbol(fragment);
	Gura_RealizeUserSymbol(version);
	Gura_RealizeUserSymbol(code);
	Gura_RealizeUserSymbol(reason);
	Gura_RealizeUserSymbol(proxies);
	Gura_RealizeUserSymbol(body);
	Gura_RealizeUserSymbol(server);
	Gura_RealizeUserSymbol(session);
	Gura_RealizeUserSymbol(sessions);
	Gura_RealizeUserSymbol(remote_ip);
	Gura_RealizeUserSymbol(remote_host);
	Gura_RealizeUserSymbol(remote_logname);
	Gura_RealizeUserSymbol(local_ip);
	Gura_RealizeUserSymbol(local_host);
	Gura_RealizeUserSymbol(date);				// 14.18 Date
	Gura_RealizeUserSymbol(expires);			// 14.21 Expires
	Gura_RealizeUserSymbol(last_modified);		// 14.29 Last-Modified
	// class realization
	Gura_RealizeAndPrepareUserClassAlias(stat, "stat", env.LookupClass(VTYPE_object));
	Gura_RealizeAndPrepareUserClass(request, env.LookupClass(VTYPE_object));
	Gura_RealizeAndPrepareUserClass(response, env.LookupClass(VTYPE_object));
	Gura_RealizeAndPrepareUserClass(session, env.LookupClass(VTYPE_object));
	Gura_RealizeAndPrepareUserClass(server, env.LookupClass(VTYPE_object));
	Gura_RealizeAndPrepareUserClass(client, env.LookupClass(VTYPE_object));
	Gura_RealizeAndPrepareUserClass(proxy, env.LookupClass(VTYPE_object));
	// function assignment
	Gura_AssignFunction(addproxy);
	Gura_AssignFunction(server);
	Gura_AssignFunction(client);
	// registration of directory factory
	PathMgr::Register(env, new PathMgr_Http());
	return true;
}

Gura_ModuleTerminate()
{
}

Gura_EndModuleBody(http, http)

Gura_RegisterModule(http)
