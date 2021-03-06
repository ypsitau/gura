//=============================================================================
// String
//=============================================================================
#include "stdafx.h"

namespace Gura {

//-----------------------------------------------------------------------------
// String
//-----------------------------------------------------------------------------
const StringList StringList::Empty;

static const UInt32 __ctypeTbl[] = {
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000060, 0x00000040, 0x00000000,
	0x00000000, 0x00000040, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000060, 0x00004000, 0x00000000, 0x00000000,
	0x00004800, 0x00000000, 0x00004000, 0x00004000,
	0x00004000, 0x00004000, 0x00004000, 0x00004000,
	0x00004000, 0x00004000, 0x00004000, 0x00004000,
	0x0000401e, 0x0000401e, 0x0000400e, 0x0000400e,
	0x0000400e, 0x0000400e, 0x0000400e, 0x0000400e,
	0x00004006, 0x00004006, 0x00004000, 0x00004000,
	0x00000000, 0x00004000, 0x00000000, 0x00004000,
	0x00004900, 0x00006105, 0x00006105, 0x00006105,
	0x00006105, 0x00006105, 0x00006105, 0x00006101,
	0x00006101, 0x00006101, 0x00006101, 0x00006101,
	0x00006101, 0x00006101, 0x00006101, 0x00006101,
	0x00006101, 0x00006101, 0x00006101, 0x00006101,
	0x00006101, 0x00006101, 0x00006101, 0x00006101,
	0x00006101, 0x00006101, 0x00006101, 0x00000100,
	0x00000100, 0x00000100, 0x00000100, 0x00004900,
	0x00000100, 0x00005105, 0x00005105, 0x00005105,
	0x00005105, 0x00005105, 0x00005105, 0x00005101,
	0x00005101, 0x00005101, 0x00005101, 0x00005101,
	0x00005101, 0x00005101, 0x00005101, 0x00005101,
	0x00005101, 0x00005101, 0x00005101, 0x00005101,
	0x00005101, 0x00005101, 0x00005101, 0x00005101,
	0x00005101, 0x00005101, 0x00005101, 0x00000100,
	0x00000100, 0x00000100, 0x00004100, 0x00000000,
	0x00000500, 0x00000580, 0x00000580, 0x00000580,
	0x00000580, 0x00000580, 0x00000580, 0x00000580,
	0x00000580, 0x00000580, 0x00000580, 0x00000580,
	0x00000580, 0x00000580, 0x00000580, 0x00000580,
	0x00000580, 0x00000580, 0x00000580, 0x00000580,
	0x00000580, 0x00000580, 0x00000580, 0x00000580,
	0x00000580, 0x00000580, 0x00000580, 0x00000580,
	0x00000580, 0x00000580, 0x00000580, 0x00000580,
	0x00000500, 0x00000500, 0x00000500, 0x00000500,
	0x00000500, 0x00000500, 0x00000500, 0x00000500,
	0x00000500, 0x00000500, 0x00000500, 0x00000500,
	0x00000500, 0x00000500, 0x00000500, 0x00000500,
	0x00000500, 0x00000500, 0x00000500, 0x00000500,
	0x00000500, 0x00000500, 0x00000500, 0x00000500,
	0x00000500, 0x00000500, 0x00000500, 0x00000500,
	0x00000500, 0x00000500, 0x00000500, 0x00000500,
	0x00000300, 0x00000300, 0x00000300, 0x00000300,
	0x00000300, 0x00000300, 0x00000300, 0x00000300,
	0x00000300, 0x00000300, 0x00000300, 0x00000300,
	0x00000300, 0x00000300, 0x00000300, 0x00000300,
	0x00000300, 0x00000300, 0x00000300, 0x00000300,
	0x00000300, 0x00000300, 0x00000300, 0x00000300,
	0x00000300, 0x00000300, 0x00000300, 0x00000300,
	0x00000300, 0x00000300, 0x00000300, 0x00000300,
	0x00000380, 0x00000380, 0x00000380, 0x00000380,
	0x00000380, 0x00000380, 0x00000380, 0x00000380,
	0x00000380, 0x00000380, 0x00000380, 0x00000380,
	0x00000380, 0x00000380, 0x00000380, 0x00000380,
	0x00000300, 0x00000300, 0x00000300, 0x00000300,
	0x00000300, 0x00000300, 0x00000300, 0x00000300,
	0x00000300, 0x00000300, 0x00000380, 0x00000380,
	0x00000380, 0x00000200, 0x00000200, 0x00000200,
};

UInt32 GetCType(char ch)
{
	return __ctypeTbl[static_cast<UChar>(ch)];
}

Number ToNumber(const char *str, bool *pSuccessFlag)
{
	Number num;
	char *next = nullptr;
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X' || IsOctDigit(str[1]))) {
		num = static_cast<Number>(::strtoull(str, &next, 0));
	} else if (str[0] == '0' && (str[1] == 'b' || str[1] == 'B')) {
		num = static_cast<Number>(::strtoull(str + 2, &next, 2));
	} else {
		num = ::strtod(str, &next);
	}
	if (pSuccessFlag != nullptr) *pSuccessFlag = (*next == '\0');
	return num;
}

char GetEscaped(char ch)
{
	static const struct {
		char ch;
		char chConv;
	} tbl[] = {
		{ 'a',	'\a'	},
		{ 'b',	'\b'	},
		{ 'f',	'\f'	},
		{ 'n',	'\n'	},
		{ 'r',	'\r'	},
		{ 't',	'\t'	},
		{ 'v',	'\v'	},
		{ '\\',	'\\'	},
		{ '\'',	'\''	},
		{ '"',	'"'		},
	};
	for (size_t i = 0; i < ArraySizeOf(tbl); i++) {
		if (tbl[i].ch == ch) return tbl[i].chConv;
	}
	return ch;
}

String ZenToHan(const char *str)
{
	String rtn;
	while (*str != '\0') {
		const char *next = nullptr;
		char ch = ZenToHanChar(str, &next);
		if (ch == '\0') {
			for ( ; str != next; str++) rtn += *str;
		} else {
			rtn += ch;
			str = next;
		}
	}
	return rtn;
}

char ZenToHanChar(const char *str, const char **next)
{
	struct Convert {
		const char *zenkaku;
		int len;
		char hankaku;
	};
	static const Convert convTbl[] = {
		{ "\xef\xbc\x81", 3, 0x21 }, // !
		{ "\xe2\x80\x9c", 3, 0x22 }, // "
		{ "\xe2\x80\x9d", 3, 0x22 }, // "
		{ "\xe3\x82\x9b", 3, 0x22 }, // "
		{ "\xe2\x80\xb3", 3, 0x22 }, // "
		{ "\xef\xbc\x83", 3, 0x23 }, // #
		{ "\xef\xbc\x84", 3, 0x24 }, // $
		{ "\xef\xbc\x85", 3, 0x25 }, // %
		{ "\xef\xbc\x86", 3, 0x26 }, // &
		{ "\xe2\x80\x99", 3, 0x27 }, // '
		{ "\xc2\xb4",     2, 0x27 }, // '
		{ "\xe2\x80\xb2", 3, 0x27 }, // '
		{ "\xef\xbc\x88", 3, 0x28 }, // (
		{ "\xef\xbc\x89", 3, 0x29 }, // )
		{ "\xef\xbc\x8a", 3, 0x2a }, // *
		{ "\xc3\x97",     2, 0x2a }, // *
		{ "\xef\xbc\x8b", 3, 0x2b }, // +
		{ "\xe3\x80\x81", 3, 0x2c }, // ,
		{ "\xef\xbc\x8c", 3, 0x2c }, // ,
		{ "\xe3\x83\xbc", 3, 0x2d }, // -
		{ "\xef\xbc\x8d", 3, 0x2d }, // -
		{ "\xe2\x94\x80", 3, 0x2d }, // -
		{ "\xe3\x80\x82", 3, 0x2e }, // .
		{ "\xef\xbc\x8e", 3, 0x2e }, // .
		{ "\xef\xbc\x8f", 3, 0x2f }, // /
		{ "\xef\xbc\x90", 3, 0x30 }, // 0
		{ "\xef\xbc\x91", 3, 0x31 }, // 1
		{ "\xef\xbc\x92", 3, 0x32 }, // 2
		{ "\xef\xbc\x93", 3, 0x33 }, // 3
		{ "\xef\xbc\x94", 3, 0x34 }, // 4
		{ "\xef\xbc\x95", 3, 0x35 }, // 5
		{ "\xef\xbc\x96", 3, 0x36 }, // 6
		{ "\xef\xbc\x97", 3, 0x37 }, // 7
		{ "\xef\xbc\x98", 3, 0x38 }, // 8
		{ "\xef\xbc\x99", 3, 0x39 }, // 9
		{ "\xef\xbc\x9a", 3, 0x3a }, // :
		{ "\xef\xbc\x9b", 3, 0x3b }, // ;
		{ "\xef\xbc\x9c", 3, 0x3c }, // <
		{ "\xe3\x80\x88", 3, 0x3c }, // <
		{ "\xef\xbc\x9d", 3, 0x3d }, // =
		{ "\xef\xbc\x9e", 3, 0x3e }, // >
		{ "\xe3\x80\x89", 3, 0x3e }, // >
		{ "\xef\xbc\x9f", 3, 0x3f }, // ?
		{ "\xef\xbc\xa0", 3, 0x40 }, // @
		{ "\xef\xbc\xa1", 3, 0x41 }, // A
		{ "\xef\xbc\xa2", 3, 0x42 }, // B
		{ "\xef\xbc\xa3", 3, 0x43 }, // C
		{ "\xef\xbc\xa4", 3, 0x44 }, // D
		{ "\xef\xbc\xa5", 3, 0x45 }, // E
		{ "\xef\xbc\xa6", 3, 0x46 }, // F
		{ "\xef\xbc\xa7", 3, 0x47 }, // G
		{ "\xef\xbc\xa8", 3, 0x48 }, // H
		{ "\xef\xbc\xa9", 3, 0x49 }, // I
		{ "\xef\xbc\xaa", 3, 0x4a }, // J
		{ "\xef\xbc\xab", 3, 0x4b }, // K
		{ "\xef\xbc\xac", 3, 0x4c }, // L
		{ "\xef\xbc\xad", 3, 0x4d }, // M
		{ "\xef\xbc\xae", 3, 0x4e }, // N
		{ "\xef\xbc\xaf", 3, 0x4f }, // O
		{ "\xef\xbc\xb0", 3, 0x50 }, // P
		{ "\xef\xbc\xb1", 3, 0x51 }, // Q
		{ "\xef\xbc\xb2", 3, 0x52 }, // R
		{ "\xef\xbc\xb3", 3, 0x53 }, // S
		{ "\xef\xbc\xb4", 3, 0x54 }, // T
		{ "\xef\xbc\xb5", 3, 0x55 }, // U
		{ "\xef\xbc\xb6", 3, 0x56 }, // V
		{ "\xef\xbc\xb7", 3, 0x57 }, // W
		{ "\xef\xbc\xb8", 3, 0x58 }, // X
		{ "\xef\xbc\xb9", 3, 0x59 }, // Y
		{ "\xef\xbc\xba", 3, 0x5a }, // Z
		{ "\xef\xbc\xbb", 3, 0x5b }, // [
		{ "\xe3\x80\x94", 3, 0x5b }, // [
		{ "\xef\xbf\xa5", 3, 0x5c }, // yen
		{ "\xef\xbc\xbd", 3, 0x5d }, // ]
		{ "\xe3\x80\x95", 3, 0x5d }, // ]
		{ "\xef\xbc\xbe", 3, 0x5e }, // ^
		{ "\xef\xbc\xbf", 3, 0x5f }, // _
		{ "\xe2\x80\x98", 3, 0x60 }, // `
		{ "\xef\xbd\x80", 3, 0x60 }, // `
		{ "\xef\xbd\x81", 3, 0x61 }, // a
		{ "\xef\xbd\x82", 3, 0x62 }, // b
		{ "\xef\xbd\x83", 3, 0x63 }, // c
		{ "\xef\xbd\x84", 3, 0x64 }, // d
		{ "\xef\xbd\x85", 3, 0x65 }, // e
		{ "\xef\xbd\x86", 3, 0x66 }, // f
		{ "\xef\xbd\x87", 3, 0x67 }, // g
		{ "\xef\xbd\x88", 3, 0x68 }, // h
		{ "\xef\xbd\x89", 3, 0x69 }, // i
		{ "\xef\xbd\x8a", 3, 0x6a }, // j
		{ "\xef\xbd\x8b", 3, 0x6b }, // k
		{ "\xef\xbd\x8c", 3, 0x6c }, // l
		{ "\xef\xbd\x8d", 3, 0x6d }, // m
		{ "\xef\xbd\x8e", 3, 0x6e }, // n
		{ "\xef\xbd\x8f", 3, 0x6f }, // o
		{ "\xef\xbd\x90", 3, 0x70 }, // p
		{ "\xef\xbd\x91", 3, 0x71 }, // q
		{ "\xef\xbd\x92", 3, 0x72 }, // r
		{ "\xef\xbd\x93", 3, 0x73 }, // s
		{ "\xef\xbd\x94", 3, 0x74 }, // t
		{ "\xef\xbd\x95", 3, 0x75 }, // u
		{ "\xef\xbd\x96", 3, 0x76 }, // v
		{ "\xef\xbd\x97", 3, 0x77 }, // w
		{ "\xef\xbd\x98", 3, 0x78 }, // x
		{ "\xef\xbd\x99", 3, 0x79 }, // y
		{ "\xef\xbd\x9a", 3, 0x7a }, // z
		{ "\xef\xbd\x9b", 3, 0x7b }, // {
		{ "\xef\xbd\x9c", 3, 0x7c }, // |
		{ "\xef\xbd\x9d", 3, 0x7d }, // }
		{ "\xef\xbd\x9e", 3, 0x7e }, // ~
		{ "\xef\xbf\xa3", 3, 0x7e }, // ~
	};
	for (size_t i = 0; i < ArraySizeOf(convTbl); i++) {
		const Convert &conv = convTbl[i];
		if (::strncmp(str, conv.zenkaku, conv.len) == 0) {
			if (next != nullptr) *next = str + conv.len;
			return conv.hankaku;
		}
	}
	if (IsUTF8First(*str)) {
		str++;
		while (IsUTF8Follower(*str)) str++;
	} else if (*str != '\0') {
		str++;
	}
	if (next != nullptr) *next = str;
	return '\0';
}

String MakeQuotedString(const char *str, bool surroundFlag)
{
	String strDst;
	char chQuote = '\'';
	if (::strchr(str, '\'') != nullptr && ::strchr(str, '"') == nullptr) {
		chQuote = '"';
	}
	if (surroundFlag) strDst += chQuote;
	for (const char *p = str; *p != '\0'; p++) {
		char ch = *p;
		if (ch == '\a') {
			strDst += "\\a";
		} else if (ch == '\b') {
			strDst += "\\b";
		} else if (ch == '\f') {
			strDst += "\\f";
		} else if (ch == '\n') {
			strDst += "\\n";
		} else if (ch == '\r') {
			strDst += "\\r";
		} else if (ch == '\t') {
			strDst += "\\t";
		} else if (ch == '\v') {
			strDst += "\\v";
		} else if (ch == chQuote) {
			strDst += '\\';
			strDst += chQuote;
		} else if (ch == '\\') {
			strDst += "\\\\";
		} else if (IsUTF8First(ch) || IsUTF8Follower(ch)) {
			strDst += ch;
		} else if (ch < 0x20 || ch >= 0x7f) {
			char tmp[16];
			::sprintf(tmp, "\\x%02x", static_cast<UChar>(ch));
			strDst += tmp;
		} else {
			strDst += ch;
		}
	}
	if (surroundFlag) strDst += chQuote;
	return strDst;
}

void EncodeURI(String &strDst, const char *str)
{
	for (const char *p = str; *p != '\0'; p++) {
		char ch = *p;
		if (IsURIC(ch)) {
			strDst += ch;
		} else {
			char buff[8];
			::sprintf(buff, "%%%02X", static_cast<UChar>(ch));
			strDst += buff;
		}
	}
}

String EncodeURI(const char *str)
{
	String rtn;
	EncodeURI(rtn, str);
	return rtn;
}

void EncodeURI(String &strDst, const char *str, size_t len)
{
	for (const char *p = str; len > 0; p++, len--) {
		char ch = *p;
		if (IsURIC(ch)) {
			strDst += ch;
		} else {
			char buff[8];
			::sprintf(buff, "%%%02X", static_cast<UChar>(ch));
			strDst += buff;
		}
	}
}

String EncodeURI(const char *str, size_t len)
{
	String rtn;
	EncodeURI(rtn, str, len);
	return rtn;
}

void DecodeURI(String &strDst, const char *str)
{
	enum {
		STAT_Normal, STAT_Percent,
	} stat = STAT_Normal;
	int nNibbles = 0;
	UChar data = 0x00;
	for (const char *p = str; *p != '\0'; p++) {
		char ch = *p;
		if (stat == STAT_Normal) {
			if (ch == '%') {
				nNibbles = 0;
				data = 0x00;
				stat = STAT_Percent;
			} else {
				strDst += ch;
			}
		} else if (stat == STAT_Percent) {
			if ('0' <= ch && ch <= '9') {
				data = (data << 4) + (ch - '0');
			} else if ('A' <= ch && ch <= 'F') {
				data = (data << 4) + (ch - 'A' + 10);
			} else if ('a' <= ch && ch <= 'f') {
				data = (data << 4) + (ch - 'a' + 10);
			}
			nNibbles++;
			if (nNibbles == 2) {
				strDst += static_cast<char>(data);
				stat = STAT_Normal;
			}
		}
	}
}

String DecodeURI(const char *str)
{
	String rtn;
	DecodeURI(rtn, str);
	return rtn;
}

void EscapeHtml(String &strDst, const char *str, bool quoteFlag)
{
	for (const char *p = str; *p != '\0'; p++) {
		char ch = *p;
		if (ch == '&') {
			strDst += "&amp;";
		} else if (ch == '>') {
			strDst += "&gt;";
		} else if (ch == '<') {
			strDst += "&lt;";
		} else if (quoteFlag && ch == '"') {
			strDst += "&quot;";
		} else {
			strDst += ch;
		}
	}
}

String EscapeHtml(const char *str, bool quoteFlag)
{
	String rtn;
	EscapeHtml(rtn, str, quoteFlag);
	return rtn;
}

void UnescapeHtml(String &strDst, const char *str)
{
	enum {
		STAT_Normal, STAT_Escape,
	} stat = STAT_Normal;
	String field;
	for (const char *p = str; *p != '\0'; p++) {
		char ch = *p;
		if (stat == STAT_Normal) {
			if (ch == '&') {
				field.clear();
				stat = STAT_Escape;
			} else {
				strDst += ch;
			}
		} else if (stat == STAT_Escape) {
			if (ch == ';') {
				if (field == "amp") {
					strDst += '&';
				} else if (field == "gt") {
					strDst += '>';
				} else if (field == "lt") {
					strDst += '<';
				} else if (field == "quot") {
					strDst += '"';
				}
				stat = STAT_Normal;
			} else {
				field += ch;
			}
		}
	}
}

String UnescapeHtml(const char *str)
{
	String rtn;
	UnescapeHtml(rtn, str);
	return rtn;
}

String NumberToString(Number num)
{
	char buff[32];
	if (-2147483647. <= num && num < 2147483648. &&
					static_cast<Number>(static_cast<int>(num)) == num) {
		::sprintf(buff, "%d", static_cast<int>(num));
	} else if (0 <= num && num <= 4294967295. &&
			static_cast<Number>(static_cast<UInt>(num)) == num) {
		::sprintf(buff, "%u", static_cast<UInt>(num));
	} else {
		::sprintf(buff, GetNumberFormat(), num);
	}
	return String(buff);
}

const char *FindString(const char *str, const char *sub, bool ignoreCaseFlag)
{
	for ( ; *str != '\0'; str++) {
		const char *p1 = str, *p2 = sub;
		for ( ; *p2 != '\0'; p1++, p2++) {
			if (CompareChar(*p1, *p2, ignoreCaseFlag) != 0) break;
		}
		if (*p2 == '\0') return str;
	}
	return nullptr;
}

String::const_iterator FindString(String::const_iterator str,
		String::const_iterator strEnd, const String &sub, bool ignoreCaseFlag)
{
	for ( ; str != strEnd; str++) {
		String::const_iterator p1 = str;
		String::const_iterator p2 = sub.begin();
		for ( ; p2 != sub.end(); p1++, p2++) {
			if (CompareChar(*p1, *p2, ignoreCaseFlag) != 0) break;
		}
		if (p2 == sub.end()) return str;
	}
	return strEnd;
}

Value FindString(Environment &env, const char *str, const char *sub, int start,
				 bool ignoreCaseFlag, bool reverseFlag, bool listFlag)
{
	do {
		int len = static_cast<int>(::strlen(str));
		if (start < 0) {
			start += len;
			if (start < 0) start = 0;
		}
		if (start > len) return Value::Nil;
	} while (0);
	if (reverseFlag) {
		const char *p = FindString(str + start, sub, ignoreCaseFlag);
		if (listFlag) {
			ValueList valListOrg;
			for ( ; p != nullptr; p = FindString(p + 1, sub, ignoreCaseFlag)) {
				valListOrg.push_back(Value(static_cast<Number>(p - str)));
			}
			Value result;
			Object_list *pObjList = result.InitAsList(env);
			pObjList->Reserve(valListOrg.size());
			foreach_reverse (ValueList, pValue, valListOrg) {
				pObjList->AddFast(*pValue);
			}
			pObjList->SetValueType(VTYPE_number);
			return result;
		} else {
			const char *pLast = nullptr;
			for ( ; p != nullptr; p = FindString(p + 1, sub, ignoreCaseFlag)) {
				pLast = p;
			}
			return (pLast == nullptr)? Value::Nil :
							Value(static_cast<Number>(pLast - str));
		}
	} else {
		const char *p = FindString(str + start, sub, ignoreCaseFlag);
		if (listFlag) {
			Value result;
			Object_list *pObjList = result.InitAsList(env);
			for ( ; p != nullptr; p = FindString(p + 1, sub, ignoreCaseFlag)) {
				pObjList->AddFast(Value(static_cast<Number>(p - str)));
			}
			pObjList->SetValueType(VTYPE_number);
			return result;
		} else {
			return (p == nullptr)? Value::Nil :
							Value(static_cast<Number>(p - str));
		}
	}
}

const char *StartsWith(const char *str, const char *prefix, size_t pos, bool ignoreCaseFlag)
{
	str = Forward(str, pos);
	const char *p1 = str, *p2 = prefix;
	for ( ; *p2 != '\0'; p1++, p2++) {
		if (CompareChar(*p1, *p2, ignoreCaseFlag) != 0) return nullptr;
	}
	return p1;
}

const char *EndsWith(const char *str, const char *suffix, bool ignoreCaseFlag)
{
	size_t len = ::strlen(suffix);
	const char *p = str + ::strlen(str);
	if (str + len > p) return nullptr;
	const char *p1 = p - len, *p2 = suffix;
	for ( ; *p2 != '\0'; p1++, p2++) {
		if (CompareChar(*p1, *p2, ignoreCaseFlag) != 0) return nullptr;
	}
	return p - len;
}

const char *EndsWith(const char *str, const char *suffix, size_t posEnd, bool ignoreCaseFlag)
{
	size_t len = ::strlen(suffix);
	const char *p = Forward(str, posEnd);
	if (str + len > p) return nullptr;
	const char *p1 = p - len, *p2 = suffix;
	for ( ; *p2 != '\0'; p1++, p2++) {
		if (CompareChar(*p1, *p2, ignoreCaseFlag) != 0) return nullptr;
	}
	return p - len;
}

String Capitalize(const char *str)
{
	String rtn;
	const char *p = str;
	if (*p != '\0') {
		rtn += ('a' <= *p && *p <= 'z')? *p - 'a' + 'A' : *p;
		p++;
	}
	rtn += p;
	return rtn;
}

String Lower(const char *str)
{
	String rtn;
	for (const char *p = str; *p != '\0'; ) {
		UChar ch = static_cast<UChar>(*p);
		if (ch == 0xef) {
			p++;
			UChar ch = static_cast<UChar>(*p);
			if (ch == 0xbc) {
				p++;
				UChar ch = static_cast<UChar>(*p);
				if (0xa1 <= ch && ch <= 0xba) {
					// Zenkaku alphabet characters in Japanese code set
					rtn += '\xef';
					rtn += '\xbd';
					rtn += static_cast<char>(ch - 0xa1 + 0x81);
					p++;
				} else if (*p == '\0') {
					rtn += '\xef';
					rtn += '\xbc';
				} else {
					rtn += '\xef';
					rtn += '\xbc';
					rtn += *p;
					p++;
				}
			} else if (*p == '\0') {
				rtn += '\xef';
			} else {
				rtn += '\xef';
				rtn += *p;
				p++;
			}
		} else if ('A' <= *p && *p <= 'Z') {
			rtn += *p - 'A' + 'a';
			p++;
		} else {
			rtn += *p;
			p++;
		}
	}
	return rtn;
}

String Upper(const char *str)
{
	String rtn;
	for (const char *p = str; *p != '\0'; ) {
		UChar ch = static_cast<UChar>(*p);
		if (ch == 0xef) {
			p++;
			UChar ch = static_cast<UChar>(*p);
			if (ch == 0xbd) {
				p++;
				UChar ch = static_cast<UChar>(*p);
				if (0x81 <= ch && ch <= 0x9a) {
					// Zenkaku alphabet characters in Japanese code set
					rtn += '\xef';
					rtn += '\xbc';
					rtn += static_cast<char>(ch - 0x81 + 0xa1);
					p++;
				} else if (*p == '\0') {
					rtn += '\xef';
					rtn += '\xbd';
				} else {
					rtn += '\xef';
					rtn += '\xbd';
					rtn += *p;
					p++;
				}
			} else if (*p == '\0') {
				rtn += '\xef';
			} else {
				rtn += '\xef';
				rtn += *p;
				p++;
			}
		} else if ('a' <= *p && *p <= 'z') {
			rtn += *p - 'a' + 'A';
			p++;
		} else {
			rtn += *p;
			p++;
		}
	}
	return rtn;
}

String Strip(const char *str, bool stripLeftFlag, bool stripRightFlag)
{
	size_t len = ::strlen(str);
	if (len == 0) return String("");
	const char *p1 = str;
	const char *p2 = str + len - 1;
	if (stripLeftFlag) {
		for ( ; IsSpace(*p1); p1++) ;
	}
	if (stripRightFlag) {
		for ( ; p2 > p1 && IsSpace(*p2); p2--) ;
		if (IsSpace(*p2)) return String("");
	}
	return String(p1, p2 - p1 + 1);
}

String Chop(const char *str, bool eolOnlyFlag)
{
	size_t len = ::strlen(str);
	if (len == 0) return String("");
	const char *p = str + len;
	if (*(p - 1) == '\n') {
		p--;
		if (p > str && *(p - 1) == '\r') p--;
	} else if (eolOnlyFlag) {
		// nothing to do
	} else if (IsUTF8Follower(*(p - 1))) {
		p--;
		if (p > str) p--;
		while (p > str && !IsUTF8First(*p)) p--;
	} else {
		p--;
	}
	return String(str, p);
}

size_t Length(const char *str)
{
	size_t len = 0;
	for ( ; *str != '\0'; len++) {
		int ch = static_cast<UChar>(*str);
		str++;
		if (IsUTF8First(ch)) {
			while (IsUTF8Follower(*str)) str++;
		}
	}
	return len;
}

size_t Width(const char *str)
{
	size_t width = 0;
	UInt32 codeUTF32 = 0;
	for (const char *p = str; *p != '\0'; ) {
		p = NextUTF32(p, codeUTF32);
		Codec::WidthProp widthProp = Codec::GetWidthProp(codeUTF32);
		if (widthProp == Codec::WIDTHPROP_A ||
			widthProp == Codec::WIDTHPROP_W ||
			widthProp == Codec::WIDTHPROP_F) {
			width += 2;
		} else {
			width += 1;
		}
	}
	return width;
}

bool CheckCType(const char *str, UInt32 type)
{
	if (*str == '\0') return false;
	UInt32 codeUTF32 = 0;
	for (const char *p = str; *p != '\0'; ) {
		p = NextUTF32(p, codeUTF32);
		if (codeUTF32 > 0x7f) return false;
		if ((GetCType(static_cast<char>(codeUTF32)) & type) == 0) return false;
	}
	return true;
}

size_t CalcCharPos(const char *str, size_t idx)
{
	size_t len = 0;
	const char *strEnd = str + idx;
	for ( ; *str != '\0' && str < strEnd; len++) {
		int ch = static_cast<UChar>(*str);
		str++;
		if (IsUTF8First(ch)) {
			while (IsUTF8Follower(*str)) str++;
		}
	}
	return len;
}

String PickChar(const String &str, size_t idx)
{
	String::const_iterator p = str.begin();
	for ( ; p != str.end() && idx > 0; p = NextChar(str, p), idx--) ;
	String::const_iterator pEnd = NextChar(str, p);
	String rtn;
	for ( ; p != pEnd; p++) rtn.push_back(*p);
	return rtn;
}

String::const_iterator NextChar(const String &str, String::const_iterator p)
{
	if (p != str.end()) {
		int ch = static_cast<UChar>(*p);
		p++;
		if (IsUTF8First(ch)) {
			while (p != str.end() && IsUTF8Follower(*p)) p++;
		}
	}
	return p;
}

String::const_iterator NextUTF8(const String &str, String::const_iterator p, UInt64 &codeUTF8)
{
	codeUTF8 = 0x000000000000;
	if (p != str.end()) {
		int ch = static_cast<UChar>(*p);
		codeUTF8 = ch;
		p++;
		if (IsUTF8First(ch)) {
			while (p != str.end() && IsUTF8Follower(*p)) {
				codeUTF8 = (codeUTF8 << 8) | static_cast<UChar>(*p);
				p++;
			}
		}
	}
	return p;
}

const char *NextUTF8(const char *p, UInt64 &codeUTF8)
{
	codeUTF8 = 0x000000000000;
	if (*p != '\0') {
		int ch = static_cast<UChar>(*p);
		codeUTF8 = ch;
		p++;
		if (IsUTF8First(ch)) {
			while (IsUTF8Follower(*p)) {
				codeUTF8 = (codeUTF8 << 8) | static_cast<UChar>(*p);
				p++;
			}
		}
	}
	return p;
}

String::const_iterator NextUTF32(const String &str, String::const_iterator p, UInt32 &codeUTF32)
{
	codeUTF32 = 0x00000000;
	if (p == str.end()) {
		// nothing to do
	} else if ((*p & 0x80) == 0x00) {
		codeUTF32 = static_cast<UChar>(*p);
		p++;
	} else {
		int cntChars = 0;
		if ((*p & 0xe0) == 0xc0) {
			codeUTF32 = static_cast<UChar>(*p) & 0x1f;
			cntChars = 1;
		} else if ((*p & 0xf0) == 0xe0) {
			codeUTF32 = static_cast<UChar>(*p) & 0x0f;
			cntChars = 2;
		} else if ((*p & 0xf8) == 0xf0) {
			codeUTF32 = static_cast<UChar>(*p) & 0x07;
			cntChars = 3;
		} else if ((*p & 0xfc) == 0xf8) {
			codeUTF32 = static_cast<UChar>(*p) & 0x03;
			cntChars = 4;
		} else {
			codeUTF32 = static_cast<UChar>(*p) & 0x01;
			cntChars = 5;
		}
		p++;
		for (int i = 0; p != str.end() && i < cntChars &&
				 		(static_cast<UChar>(*p) & 0xc0) == 0x80; i++, p++) {
			codeUTF32 = (codeUTF32 << 6) | (static_cast<UChar>(*p) & 0x3f);
		}
	}
	return p;
}

const char *NextUTF32(const char *p, UInt32 &codeUTF32)
{
	codeUTF32 = 0x00000000;
	if (*p == '\0') {
		// nothing to do
	} else if ((*p & 0x80) == 0x00) {
		codeUTF32 = static_cast<UChar>(*p);
		p++;
	} else {
		int cntChars = 0;
		if ((*p & 0xe0) == 0xc0) {
			codeUTF32 = static_cast<UChar>(*p) & 0x1f;
			cntChars = 1;
		} else if ((*p & 0xf0) == 0xe0) {
			codeUTF32 = static_cast<UChar>(*p) & 0x0f;
			cntChars = 2;
		} else if ((*p & 0xf8) == 0xf0) {
			codeUTF32 = static_cast<UChar>(*p) & 0x07;
			cntChars = 3;
		} else if ((*p & 0xfc) == 0xf8) {
			codeUTF32 = static_cast<UChar>(*p) & 0x03;
			cntChars = 4;
		} else {
			codeUTF32 = static_cast<UChar>(*p) & 0x01;
			cntChars = 5;
		}
		p++;
		for (int i = 0; i < cntChars && (static_cast<UChar>(*p) & 0xc0) == 0x80; i++, p++) {
			codeUTF32 = (codeUTF32 << 6) | (static_cast<UChar>(*p) & 0x3f);
		}
	}
	return p;
}

void AppendUTF8(String &str, UInt64 codeUTF8)
{
	if (codeUTF8 == 0) {
		str.push_back('\0');
		return;
	}
	size_t i = 0;
	char buff[8];
	for ( ; codeUTF8 != 0 && i < 8; codeUTF8 >>= 8, i++) {
		buff[i] = static_cast<char>(static_cast<UChar>(codeUTF8 & 0xff));
	}
	while (i > 0) {
		i--;
		str.push_back(buff[i]);
	}
}

void AppendUTF32(String &str, UInt32 codeUTF32)
{
	int i = 0;
	char buff[8];
	if ((codeUTF32 & ~0x7f) == 0) {
		buff[i++] = static_cast<char>(codeUTF32);
	} else {
		buff[i++] = 0x80 | static_cast<char>(codeUTF32 & 0x3f);
		codeUTF32 >>= 6;
		if ((codeUTF32 & ~0x1f) == 0) {
			buff[i++] = 0xc0 | static_cast<char>(codeUTF32);
		} else {
			buff[i++] = 0x80 | static_cast<char>(codeUTF32 & 0x3f);
			codeUTF32 >>= 6;
			if ((codeUTF32 & ~0x0f) == 0) {
				buff[i++] = 0xe0 | static_cast<char>(codeUTF32);
			} else {
				buff[i++] = 0x80 | static_cast<char>(codeUTF32 & 0x3f);
				codeUTF32 >>= 6;
				if ((codeUTF32 & ~0x07) == 0) {
					buff[i++] = 0xf0 | static_cast<char>(codeUTF32);
				} else {
					buff[i++] = 0x80 | static_cast<char>(codeUTF32 & 0x3f);
					codeUTF32 >>= 6;
					if ((codeUTF32 & ~0x03) == 0) {
						buff[i++] = 0xf8 | static_cast<char>(codeUTF32);
					} else {
						buff[i++] = 0x80 | static_cast<char>(codeUTF32 & 0x3f);
						codeUTF32 >>= 6;
						buff[i++] = 0xfc | static_cast<char>(codeUTF32);
					}
				}
			}
		}
	}
	while (i > 0) {
		str.push_back(buff[--i]);
	}
}

void _Copy(String &rtn, const char *str, size_t len)
{
	for ( ; *str != '\0' && len > 0; len--) {
		int ch = static_cast<UChar>(*str);
		rtn += *str;
		str++;
		if (IsUTF8First(ch)) {
			while (IsUTF8Follower(*str)) {
				rtn += *str;
				str++;
			}
		}
	}
}

const char *Forward(const char *str, size_t len, size_t *pLenForward)
{
	size_t lenForward = 0;
	for ( ; *str != '\0' && lenForward < len; lenForward++) {
		int ch = static_cast<UChar>(*str);
		str++;
		if (IsUTF8First(ch)) {
			while (IsUTF8Follower(*str)) str++;
		}
	}
	if (pLenForward != nullptr) *pLenForward = lenForward;
	return str;
}

String::const_iterator Forward(String::const_iterator str,
			String::const_iterator strEnd, size_t len, size_t *pLenForward)
{
	size_t lenForward = 0;
	for ( ; str != strEnd && lenForward < len; lenForward++) {
		int ch = static_cast<UChar>(*str);
		str++;
		if (IsUTF8First(ch)) {
			while (IsUTF8Follower(*str)) str++;
		}
	}
	if (pLenForward != nullptr) *pLenForward = lenForward;
	return str;
}

String Center(const char *str, size_t width, const char *padding)
{
	size_t widthBody = Width(str);
	if (width <= widthBody) return String(str);
	String rtn;
	size_t widthRight = (width - widthBody) / 2;
	size_t widthLeft = width - widthBody - widthRight;
	while (widthLeft-- > 0) rtn += padding;
	rtn += str;
	while (widthRight-- > 0) rtn += padding;
	return rtn;
}

String LJust(const char *str, size_t width, const char *padding)
{
	size_t widthBody = Width(str);
	if (width <= widthBody) return String(str);
	String rtn;
	size_t widthRight = width - widthBody;
	rtn += str;
	while (widthRight-- > 0) rtn += padding;
	return rtn;
}

String RJust(const char *str, size_t width, const char *padding)
{
	size_t widthBody = Width(str);
	if (width <= widthBody) return String(str);
	String rtn;
	size_t widthLeft = width - widthBody;
	while (widthLeft-- > 0) rtn += padding;
	rtn += str;
	return rtn;
}

String Left(const char *str, size_t len)
{
	String rtn;
	_Copy(rtn, str, len);
	return rtn;
}

String Right(const char *str, size_t len)
{
	size_t lenSrc = Length(str);
	if (lenSrc > len) {
		str = Forward(str, lenSrc - len);
	}
	return String(str);
}

String Middle(const char *str, int start, int len)
{
	int lenSrc = static_cast<int>(Length(str));
	if (start < 0) {
		start += lenSrc;
		if (start < 0) start = 0;
	}
	if (start >= lenSrc || len == 0) {
		return String("");
	} else if (len > 0 && start + len < lenSrc) {
		str = Forward(str, start);
		String rtn;
		_Copy(rtn, str, len);
		return rtn;
	} else {
		str = Forward(str, start);
		return String(str);
	}
}

String Replace(const char *str, const char *sub, const char *replace,
			   int nMaxReplace, bool ignoreCaseFlag)
{
	String result;
	int lenSub = static_cast<int>(::strlen(sub));
	if (lenSub == 0) {
		if (nMaxReplace != 0) {
			result += replace;
			nMaxReplace--;
		}
		const char *p = str;
		for ( ; *p != '\0' && nMaxReplace != 0; p++, nMaxReplace--) {
			result += *p;
			result += replace;
		}
		result += p;
	} else {
		const char *pLeft = str;
		const char *pRight = FindString(pLeft, sub, ignoreCaseFlag);
		for ( ; pRight != nullptr && nMaxReplace != 0;
					pRight = FindString(pLeft, sub, ignoreCaseFlag), nMaxReplace--) {
			result.append(pLeft, pRight - pLeft);
			result += replace;
			pLeft = pRight + lenSub;
		}
		result += pLeft;
	}
	return result;
}

GURA_DLLDECLARE String Replaces(const char *str, const ValueList &valList,
								int nMaxReplace, bool ignoreCaseFlag)
{
	String result;
	const char *p = str;
	for (int nReplace = 0; (nMaxReplace < 0 || nReplace < nMaxReplace) && *p != '\0'; ) {
		bool replacedFlag = false;
		foreach_const (ValueList, pValue, valList) {
			const char *sub = pValue->GetString();
			pValue++;
			if (pValue == valList.end()) break;
			if (*sub == '\0') continue;
			const char *p1 = p, *p2 = sub;
			for ( ; *p2 != '\0'; p1++, p2++) {
				if (CompareChar(*p1, *p2, ignoreCaseFlag) != 0) break;
			}
			if (*p2 == '\0') {
				const char *replace = pValue->GetString();
				p = p1;
				result += replace;
				replacedFlag = true;
				nReplace++;
				break;
			}
		}
		if (!replacedFlag) {
			result += *p++;
		}
	}
	result += p;
	return result;
}

void SplitPathList(const char *str, StringList &strList)
{
	enum {
		STAT_SkipSpace, STAT_Field,
	} stat = STAT_SkipSpace;
	char ch = '\0';
	String field;
	int cntSpace = 0;
	bool eatNextFlag = true;
	do {
		if (eatNextFlag) ch = *str++;
		eatNextFlag = true;
		if (stat == STAT_SkipSpace) {
			if (IsSpace(ch)) {
				// nothing to do
			} else {
				field.clear();
				cntSpace = 0;
				eatNextFlag = false;
				stat = STAT_Field;
			}
		} else if (stat == STAT_Field) {
			if (OAL::IsPathSeparator(ch) || ch == '\0') {
				strList.push_back(field);
				stat = STAT_SkipSpace;
			} else if (ch == ' ') {
				cntSpace++;
			} else {
				while (cntSpace-- > 0) field.push_back(' ');
				field.push_back(ch);
			}
		}
	} while (ch != '\0');
}

//-----------------------------------------------------------------------------
// StringList
//-----------------------------------------------------------------------------
StringList::StringList(const StringList &stringList)
{
	reserve(stringList.size());
	foreach_const (StringList, pStr, stringList) {
		push_back(*pStr);
	}
}

void StringList::operator=(const StringList &stringList)
{
	reserve(stringList.size());
	foreach_const (StringList, pStr, stringList) {
		push_back(*pStr);
	}
}

//-----------------------------------------------------------------------------
// StringSet
//-----------------------------------------------------------------------------
StringSet::StringSet(const StringSet &stringSet)
{
	foreach_const (StringSet, pStr, stringSet) {
		insert(*pStr);
	}
}

void StringSet::operator=(const StringSet &stringSet)
{
	foreach_const (StringSet, pStr, stringSet) {
		insert(*pStr);
	}
}

//-----------------------------------------------------------------------------
// CharConverter
//-----------------------------------------------------------------------------
CharConverter::CharConverter() :
	_chSuspend('\0'), _enableFlag(true), _readyFlag(false), _idxPut(0), _idxGet(0)
{
}

void CharConverter::Put(char ch)
{
	if (_idxPut >= ArraySizeOf(_buff) - 1) _idxPut = 0; // This case should not happen.
	if (!_enableFlag) {
		_buff[_idxPut++] = ch;
		_readyFlag = true;
	} else if (ch > 0) {
		char chConv = '\0';
		if (_idxPut > 0 && (chConv = ZenToHanChar(_buff, nullptr)) != '\0') {
			_idxGet = _idxPut - 1;
			_buff[_idxGet] = chConv;
		}
		_buff[_idxPut++] = ch;
		_readyFlag = true;
	} else if (_idxPut > 0 && IsUTF8First(ch)) {
		char chConv = '\0';
		if ((chConv = ZenToHanChar(_buff, nullptr)) != '\0') {
			_idxGet = _idxPut - 1;
			_buff[_idxGet] = chConv;
		}
		_chSuspend = ch;
		_readyFlag = true;
	} else {
		_buff[_idxPut++] = ch;
	}
}

bool CharConverter::Get(char *pch)
{
	if (!_readyFlag) return false;
	if (_idxGet < _idxPut) {
		*pch = _buff[_idxGet++];
		return true;
	}
	_idxPut = _idxGet = 0;
	if (_chSuspend != '\0') {
		_buff[_idxPut++] = _chSuspend;
		_chSuspend = '\0';
	}
	_readyFlag = false;
	return false;
}

}
