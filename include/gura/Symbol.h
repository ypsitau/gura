#ifndef __GURA_SYMBOL_H__
#define __GURA_SYMBOL_H__

#include "Common.h"

#define Gura_Symbol(name) (SymbolPool::GetInstance()->_pSymbol_##name)

#define Gura_DeclareSymbol(name) \
const Symbol *_pSymbol_##name

#define Gura_RealizeSymbol(name) \
_pSymbol_##name = Symbol::Add(#name);

#define Gura_RealizeSymbolAlias(name, str) \
_pSymbol_##name = Symbol::Add(str);

#define Gura_UserSymbol(name) (_pUserSymbol_##name)

#if defined(GURA_MODULE_MAIN)
#define Gura_DeclareUserSymbol(name) \
const Symbol *_pUserSymbol_##name = NULL;
#else
#define Gura_DeclareUserSymbol(name) \
extern const Symbol *_pUserSymbol_##name;
#endif

#define Gura_DeclarePrivUserSymbol(name) \
static const Symbol *_pUserSymbol_##name = NULL;

#define Gura_RealizeUserSymbol(name) \
_pUserSymbol_##name = Symbol::Add(#name);

#define Gura_RealizeUserSymbolAlias(name, str) \
_pUserSymbol_##name = Symbol::Add(str);

namespace Gura {

//-----------------------------------------------------------------------------
// Symbol
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Symbol {
public:
	typedef unsigned int UniqNumber;
	struct KeyCompare_UniqNumber {
		inline bool operator()(const Symbol *pSymbol1, const Symbol *pSymbol2) const {
			return pSymbol1->GetUniqNum() < pSymbol2->GetUniqNum();
		}
	};
	struct KeyCompare_Name {
		inline bool operator()(const Symbol *pSymbol1, const Symbol *pSymbol2) const {
			return ::strcmp(pSymbol1->GetName(), pSymbol2->GetName()) < 0;
		}
	};
private:
	UniqNumber _uniqNum;
	char *_name;
public:
	Symbol(UniqNumber uniqNum, const char *name);
	~Symbol();
	bool IsFlowControlSymbol() const;
	inline static void Delete(Symbol *pSymbol) { delete pSymbol; }
	inline UniqNumber GetUniqNum() const { return _uniqNum; }
	inline const char *GetName() const { return _name; }
	inline bool IsIdentical(const Symbol *pSymbol) const {
		return GetUniqNum() == pSymbol->GetUniqNum();
	}
	inline bool IsNone() const { return _name[0] == '\0'; }
	inline bool IsPrivateName() const { return _name[0] == '_' && _name[1] == '_'; }
	static const Symbol *Add(const char *name);
};

//-----------------------------------------------------------------------------
// SymbolList
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE SymbolList : public std::vector<const Symbol *> {
public:
	String Join(const char *sep) const;
	String Join(const char sepChar) const;
	static String Join(SymbolList::const_iterator ppSymbol,
				SymbolList::const_iterator ppSymbolEnd, const char *sep);
	static String Join(SymbolList::const_iterator ppSymbol,
				SymbolList::const_iterator ppSymbolEnd, const char sepChar);
	void SortByName();
};

//-----------------------------------------------------------------------------
// SymbolSet
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE SymbolSet : public std::set<const Symbol *, Symbol::KeyCompare_UniqNumber> {
public:
	static const SymbolSet Null;
public:
	inline SymbolSet() {}
	SymbolSet(const SymbolSet &symbolSet);
	~SymbolSet();
	void operator=(const SymbolSet &symbolSet);
	inline bool IsSet(const Symbol *pSymbol) const {
		return find(pSymbol) != const_cast<SymbolSet *>(this)->end();
	}
	inline void Insert(const Symbol *pSymbol) {
		insert(pSymbol);
	}
};

//-----------------------------------------------------------------------------
// SymbolPool
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE SymbolPool {
public:
	Gura_DeclareSymbol(Str_Empty);
	Gura_DeclareSymbol(Char_Add);
	Gura_DeclareSymbol(Char_Mul);
	Gura_DeclareSymbol(Char_Question);
	Gura_DeclareSymbol(Char_Mod);
	Gura_DeclareSymbol(Char_ModMod);
	Gura_DeclareSymbol(Char_And);
	Gura_DeclareSymbol(boolean);
	Gura_DeclareSymbol(number);
	Gura_DeclareSymbol(string);
	Gura_DeclareSymbol(ps1);
	Gura_DeclareSymbol(ps2);
	Gura_DeclareSymbol(stdin);
	Gura_DeclareSymbol(stdout);
	Gura_DeclareSymbol(stderr);
	Gura_DeclareSymbol(e);
	Gura_DeclareSymbol(pi);
	Gura_DeclareSymbol(nil);
	Gura_DeclareSymbol(zero);
	Gura_DeclareSymbol(raise);
	Gura_DeclareSymbol(true_);
	Gura_DeclareSymbol(false_);
	Gura_DeclareSymbol(j);
	Gura_DeclareSymbol(if_);
	Gura_DeclareSymbol(elsif);
	Gura_DeclareSymbol(else_);
	Gura_DeclareSymbol(repeat);
	Gura_DeclareSymbol(while_);
	Gura_DeclareSymbol(for_);
	Gura_DeclareSymbol(cross);
	Gura_DeclareSymbol(break_);
	Gura_DeclareSymbol(continue_);
	Gura_DeclareSymbol(except_);
	Gura_DeclareSymbol(text);
	Gura_DeclareSymbol(binary);
	Gura_DeclareSymbol(unary);
	Gura_DeclareSymbol(message);
	Gura_DeclareSymbol(value);
	Gura_DeclareSymbol(__init__);
	Gura_DeclareSymbol(__del__);
	Gura_DeclareSymbol(__str__);
	Gura_DeclareSymbol(__setprop__);
	Gura_DeclareSymbol(__getprop__);
	Gura_DeclareSymbol(__setitem__);
	Gura_DeclareSymbol(__setitemx__);
	Gura_DeclareSymbol(__getitem__);
	Gura_DeclareSymbol(__getitemx__);
	Gura_DeclareSymbol(__name__);
	Gura_DeclareSymbol(__symbol__);
	Gura_DeclareSymbol(__source__);
	Gura_DeclareSymbol(__doc__);
	Gura_DeclareSymbol(__args__);
	Gura_DeclareSymbol(super);
	Gura_DeclareSymbol(this);
	Gura_DeclareSymbol(static_);
	Gura_DeclareSymbol(const_);
	Gura_DeclareSymbol(_anonymous_);
	Gura_DeclareSymbol(public_);
	Gura_DeclareSymbol(private_);
	Gura_DeclareSymbol(protected_);
	Gura_DeclareSymbol(default_);
	Gura_DeclareSymbol(privileged);
	Gura_DeclareSymbol(dynamic_scope);
	Gura_DeclareSymbol(inside_scope);
	Gura_DeclareSymbol(func_scope);
	Gura_DeclareSymbol(symbol_func);
	Gura_DeclareSymbol(force);
	Gura_DeclareSymbol(overwrite);
	Gura_DeclareSymbol(mixin_type);
	Gura_DeclareSymbol(raw);
	Gura_DeclareSymbol(stat);
	Gura_DeclareSymbol(map);
	Gura_DeclareSymbol(nomap);
	Gura_DeclareSymbol(nocast);
	Gura_DeclareSymbol(noesc);
	Gura_DeclareSymbol(leader);
	Gura_DeclareSymbol(trailer);
	Gura_DeclareSymbol(end_marker);
	Gura_DeclareSymbol(fork);
	Gura_DeclareSymbol(strict);
	Gura_DeclareSymbol(loose);
	Gura_DeclareSymbol(block);
	Gura_DeclareSymbol(list);
	Gura_DeclareSymbol(xlist);
	Gura_DeclareSymbol(set);
	Gura_DeclareSymbol(xset);
	Gura_DeclareSymbol(iter);
	Gura_DeclareSymbol(xiter);
	Gura_DeclareSymbol(iteritem);
	Gura_DeclareSymbol(xiteritem);
	Gura_DeclareSymbol(listitem);
	Gura_DeclareSymbol(xlistitem);
	Gura_DeclareSymbol(rev);
	Gura_DeclareSymbol(and);
	Gura_DeclareSymbol(or);
	Gura_DeclareSymbol(xor);
	Gura_DeclareSymbol(root);
	Gura_DeclareSymbol(void_);
	Gura_DeclareSymbol(extern_);
	Gura_DeclareSymbol(reduce);
	Gura_DeclareSymbol(xreduce);
	Gura_DeclareSymbol(local);
	Gura_DeclareSymbol(flat);
	Gura_DeclareSymbol(noflat);
	Gura_DeclareSymbol(rest);
	Gura_DeclareSymbol(icase);
	Gura_DeclareSymbol(chop);
	Gura_DeclareSymbol(align);
	Gura_DeclareSymbol(upper);
	Gura_DeclareSymbol(lower);
	Gura_DeclareSymbol(index);
	Gura_DeclareSymbol(last_index);
	Gura_DeclareSymbol(indices);
	Gura_DeclareSymbol(transpose);
	Gura_DeclareSymbol(ascend);
	Gura_DeclareSymbol(descend);
	Gura_DeclareSymbol(stable);
	Gura_DeclareSymbol(up);
	Gura_DeclareSymbol(down);
	Gura_DeclareSymbol(center);
	Gura_DeclareSymbol(both);
	Gura_DeclareSymbol(left);
	Gura_DeclareSymbol(right);
	Gura_DeclareSymbol(begin);
	Gura_DeclareSymbol(end);
	Gura_DeclareSymbol(cur);
	Gura_DeclareSymbol(prev);
	Gura_DeclareSymbol(next);
	Gura_DeclareSymbol(stay);
	Gura_DeclareSymbol(forward);
	Gura_DeclareSymbol(backward);
	Gura_DeclareSymbol(help);
	Gura_DeclareSymbol(symbol);
	Gura_DeclareSymbol(name);
	Gura_DeclareSymbol(fullname);
	Gura_DeclareSymbol(identifier);
	Gura_DeclareSymbol(args);
	Gura_DeclareSymbol(readable);
	Gura_DeclareSymbol(writable);
	Gura_DeclareSymbol(codec);
	Gura_DeclareSymbol(argsymbols);
	Gura_DeclareSymbol(expr);
	Gura_DeclareSymbol(parent);
	Gura_DeclareSymbol(parents);
	Gura_DeclareSymbol(sibling);
	Gura_DeclareSymbol(siblings);
	Gura_DeclareSymbol(child);
	Gura_DeclareSymbol(children);
	Gura_DeclareSymbol(path);
	Gura_DeclareSymbol(shrink);
	Gura_DeclareSymbol(shrinkable);
	Gura_DeclareSymbol(r);
	Gura_DeclareSymbol(w);
	Gura_DeclareSymbol(x);
	Gura_DeclareSymbol(y);
	Gura_DeclareSymbol(z);
	Gura_DeclareSymbol(deg);
	Gura_DeclareSymbol(box);
	Gura_DeclareSymbol(imagetype);
	Gura_DeclareSymbol(audiotype);
	Gura_DeclareSymbol(format);
	Gura_DeclareSymbol(stream);
	Gura_DeclareSymbol(color);
	Gura_DeclareSymbol(width);
	Gura_DeclareSymbol(height);
	Gura_DeclareSymbol(palette);
	Gura_DeclareSymbol(rgb);
	Gura_DeclareSymbol(rgba);
	Gura_DeclareSymbol(rgbq);
	Gura_DeclareSymbol(bgr);
	Gura_DeclareSymbol(bgra);
	Gura_DeclareSymbol(bitmap);
	Gura_DeclareSymbol(black);
	Gura_DeclareSymbol(blue);
	Gura_DeclareSymbol(green);
	Gura_DeclareSymbol(aqua);
	Gura_DeclareSymbol(cyan);
	Gura_DeclareSymbol(red);
	Gura_DeclareSymbol(purple);
	Gura_DeclareSymbol(magenta);
	Gura_DeclareSymbol(yellow);
	Gura_DeclareSymbol(white);
	Gura_DeclareSymbol(gray);
	Gura_DeclareSymbol(bright_blue);
	Gura_DeclareSymbol(bright_green);
	Gura_DeclareSymbol(bright_aqua);
	Gura_DeclareSymbol(bright_cyan);
	Gura_DeclareSymbol(bright_red);
	Gura_DeclareSymbol(bright_purple);
	Gura_DeclareSymbol(bright_magenta);
	Gura_DeclareSymbol(bright_yellow);
	Gura_DeclareSymbol(bright_white);
	Gura_DeclareSymbol(alpha);
	Gura_DeclareSymbol(u8);
	Gura_DeclareSymbol(s8);
	Gura_DeclareSymbol(u16le);
	Gura_DeclareSymbol(s16le);
	Gura_DeclareSymbol(u16be);
	Gura_DeclareSymbol(s16be);
	Gura_DeclareSymbol(u32le);
	Gura_DeclareSymbol(s32le);
	Gura_DeclareSymbol(u32be);
	Gura_DeclareSymbol(s32be);
	Gura_DeclareSymbol(u64le);
	Gura_DeclareSymbol(s64le);
	Gura_DeclareSymbol(u64be);
	Gura_DeclareSymbol(s64be);
	Gura_DeclareSymbol(channels);
	Gura_DeclareSymbol(len);
	Gura_DeclareSymbol(open);
	Gura_DeclareSymbol(open_l);
	Gura_DeclareSymbol(open_r);
	Gura_DeclareSymbol(sticky);
	Gura_DeclareSymbol(sticky_l);
	Gura_DeclareSymbol(sticky_r);
	Gura_DeclareSymbol(horz);
	Gura_DeclareSymbol(vert);
	Gura_DeclareSymbol(mono);
	Gura_DeclareSymbol(basic);
	Gura_DeclareSymbol(win256);
	Gura_DeclareSymbol(websafe);
	Gura_DeclareSymbol(uri);
	Gura_DeclareSymbol(http);
	Gura_DeclareSymbol(ftp);
	Gura_DeclareSymbol(year);
	Gura_DeclareSymbol(month);
	Gura_DeclareSymbol(day);
	Gura_DeclareSymbol(hour);
	Gura_DeclareSymbol(min);
	Gura_DeclareSymbol(sec);
	Gura_DeclareSymbol(msec);
	Gura_DeclareSymbol(usec);
	Gura_DeclareSymbol(nsec);
	Gura_DeclareSymbol(wday);
	Gura_DeclareSymbol(week);
	Gura_DeclareSymbol(yday);
	Gura_DeclareSymbol(days);
	Gura_DeclareSymbol(secs);
	Gura_DeclareSymbol(msecs);
	Gura_DeclareSymbol(usecs);
	Gura_DeclareSymbol(nsecs);
	Gura_DeclareSymbol(sunday);
	Gura_DeclareSymbol(monday);
	Gura_DeclareSymbol(tuesday);
	Gura_DeclareSymbol(wednesday);
	Gura_DeclareSymbol(thursday);
	Gura_DeclareSymbol(friday);
	Gura_DeclareSymbol(saturday);
	Gura_DeclareSymbol(single);
	Gura_DeclareSymbol(multi);
	Gura_DeclareSymbol(w3c);
	Gura_DeclareSymbol(asctime);
	Gura_DeclareSymbol(unixtime);
	Gura_DeclareSymbol(ascii);
	Gura_DeclareSymbol(utf8);
	Gura_DeclareSymbol(utf16);
	Gura_DeclareSymbol(utf32);
	Gura_DeclareSymbol(msc);
	Gura_DeclareSymbol(bcc);
	Gura_DeclareSymbol(gnuc);
	Gura_DeclareSymbol(file);
	Gura_DeclareSymbol(dir);
	Gura_DeclareSymbol(mswin);
	Gura_DeclareSymbol(linux);
	Gura_DeclareSymbol(top);
	Gura_DeclareSymbol(bottom);
	Gura_DeclareSymbol(eol);
	Gura_DeclareSymbol(eof);
	Gura_DeclareSymbol(firsteol);
	Gura_DeclareSymbol(lasteol);
	Gura_DeclareSymbol(cstr);
	Gura_DeclareSymbol(carray);
	Gura_DeclareSymbol(indent);
	Gura_DeclareSymbol(noindent);
	Gura_DeclareSymbol(autoindent);
	Gura_DeclareSymbol(en);
	Gura_DeclareSymbol(ar);
	Gura_DeclareSymbol(bg);
	Gura_DeclareSymbol(cs);
	Gura_DeclareSymbol(de);
	Gura_DeclareSymbol(fr);
	Gura_DeclareSymbol(ja);
	Gura_DeclareSymbol(ka);
	Gura_DeclareSymbol(pl);
	Gura_DeclareSymbol(sv);
	Gura_DeclareSymbol(scheme);
	Gura_DeclareSymbol(user);
	Gura_DeclareSymbol(password);
	Gura_DeclareSymbol(host);
	Gura_DeclareSymbol(port);
	Gura_DeclareSymbol(urlpath);
	Gura_DeclareSymbol(misc);
	Gura_DeclareSymbol(line);
private:
	typedef std::set<Symbol *, Symbol::KeyCompare_Name> Content;
private:
	static SymbolPool *_pInst;
	Symbol::UniqNumber _uniqNum;
	Content _content;
private:
	inline SymbolPool() {}
public:
	~SymbolPool();
	static void Initialize();
	static SymbolPool *GetInstance();
	const Symbol *Add(const char *name);
private:
	void _Initialize();
private:
	inline SymbolPool(const SymbolPool &symbolPool) {}
	inline void operator=(const SymbolPool &symbolPool) {}
};

//-----------------------------------------------------------------------------
// utilities
//-----------------------------------------------------------------------------
const Symbol *GetOccurPatternSymbol(OccurPattern occurPattern);

}

#endif
