//=============================================================================
// Complex
//=============================================================================
#ifndef __GURA_COMPLEX_H__
#define __GURA_COMPLEX_H__

namespace Gura {

//-----------------------------------------------------------------------------
// Complex
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Complex : public std::complex<double> {
public:
	static const Complex Zero;
public:
	inline static void *operator new(size_t size) {
		return MemoryPool::Allocate(size, "Complex");
	}
	inline static void operator delete(void *pv) {
		MemoryPool::Deallocate(pv);
	}
public:
	inline Complex() : std::complex<double>(0.) {}
	inline Complex(const Complex &comp) : std::complex<double>(comp) {}
	inline Complex(const std::complex<double> &comp) : std::complex<double>(comp) {}
	inline Complex(double real) : std::complex<double>(real) {}
	inline Complex(double real, double imag) : std::complex<double>(real, imag) {}
	inline bool IsZero() const { return real() == 0 && imag() == 0; }
	inline static Complex Polar(double abs, double arg) {
		return Complex(abs * ::cos(arg), abs * ::sin(arg));
	}
	inline explicit operator Boolean() const noexcept { return !IsZero(); }
};

typedef std::vector<Complex> ComplexList;
typedef std::deque<Complex> ComplexDeque;

}

#endif
