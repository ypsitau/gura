//=============================================================================
// Color
//=============================================================================
#ifndef __GURA_COLOR_H__
#define __GURA_COLOR_H__

namespace Gura {

class Symbol;
class ColorMap;

//-----------------------------------------------------------------------------
// Color
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Color {
public:
	struct ElementEntry {
		const char *name;
		UChar r, g, b;
	};
private:
	UChar _r, _g, _b, _a;
	static ColorMap *_pColorMap;
	static const ElementEntry _elementEntries[];
public:
	static const Color zero;
	static const Color black;
	static const Color maroon;
	static const Color green;
	static const Color olive;
	static const Color navy;
	static const Color purple;
	static const Color teal;
	static const Color gray;
	static const Color silver;
	static const Color red;
	static const Color lime;
	static const Color yellow;
	static const Color blue;
	static const Color fuchsia;
	static const Color aqua;
	static const Color white;
public:
	inline Color() : _r(0), _g(0), _b(0), _a(0) {}
	inline Color(const Color &color) : _r(color._r), _g(color._g), _b(color._b), _a(color._a) {}
	inline Color(UChar r, UChar g, UChar b) : _r(r), _g(g), _b(b), _a(0) {}
	inline Color(UChar r, UChar g, UChar b, UChar a) : _r(r), _g(g), _b(b), _a(a) {}
	inline UChar GetR() const { return _r; }
	inline UChar GetG() const { return _g; }
	inline UChar GetB() const { return _b; }
	inline UChar GetA() const { return _a; }
	inline void SetR(UChar r) { _r = r; }
	inline void SetG(UChar g) { _g = g; }
	inline void SetB(UChar b) { _b = b; }
	inline void SetA(UChar a) { _a = a; }
	inline UChar GetGray() const { return CalcGray(GetR(), GetG(), GetB()); }
	inline ULong GetARGB() const {
		return
			(static_cast<ULong>(GetA()) << 24) +
			(static_cast<ULong>(GetR()) << 16) +
			(static_cast<ULong>(GetG()) << 8) +
			(static_cast<ULong>(GetB()) << 0);
	}
	inline ULong GetABGR() const {
		return
			(static_cast<ULong>(GetA()) << 24) +
			(static_cast<ULong>(GetB()) << 16) +
			(static_cast<ULong>(GetG()) << 8) +
			(static_cast<ULong>(GetR()) << 0);
	}
	inline ULong GetRGB() const {
		return
			(static_cast<ULong>(GetR()) << 16) +
			(static_cast<ULong>(GetG()) << 8) +
			(static_cast<ULong>(GetB()) << 0);
	}
	inline ULong GetBGR() const {
		return
			(static_cast<ULong>(GetB()) << 16) +
			(static_cast<ULong>(GetG()) << 8) +
			(static_cast<ULong>(GetR()) << 0);
	}
	inline bool operator<(const Color &c) const { return GetRGB() < c.GetRGB(); }
	inline size_t CalcDistSqu(UChar r, UChar g, UChar b) const {
		return CalcDistSqu(GetR(), GetG(), GetB(), r, g, b);
	}
	inline size_t CalcDistSqu(const Color &c) const {
		return CalcDistSqu(GetR(), GetG(), GetB(), c.GetR(), c.GetG(), c.GetB());
	}
	inline String GetHTML() const {
		char buff[32];
		::sprintf(buff, "#%06lx", GetRGB());
		return String(buff);
	}
	static inline size_t CalcDistSqu(
				UChar r1, UChar g1, UChar b1, UChar r2, UChar g2, UChar b2) {
		Long distR = static_cast<Long>(r1) - static_cast<Long>(r2);
		Long distG = static_cast<Long>(g1) - static_cast<Long>(g2);
		Long distB = static_cast<Long>(b1) - static_cast<Long>(b2);
		return distR * distR + distG * distG + distB * distB;
	}
	// revise this equation to convert a color into gray scale.
	static inline UChar CalcGray(UChar r, UChar g, UChar b) {
		return static_cast<UChar>(
			(static_cast<ULong>(r) * 299 +
			 static_cast<ULong>(g) * 587 +
			 static_cast<ULong>(b) * 114) / 1000);
	}
	static Color CreateFromValues(Environment &env, const ValueList &valList);
	static Color CreateNamedColor(Environment &env, const char *name, UChar a);
	static const ElementEntry *GetElementEntries(size_t *pCnt);
};

class ColorMap : public std::unordered_map<const Symbol *, Color, Symbol::Hasher, Symbol::EqualTo> {
};

typedef std::vector<Color, Allocator<Color> > ColorList;
typedef std::deque<Color, Allocator<Color> > ColorDeque;
typedef std::set<Color> ColorSet;

}

#endif
