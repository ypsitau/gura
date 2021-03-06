//=============================================================================
// Vertex
//=============================================================================
#ifndef __GURA_VERTEX_H__
#define __GURA_VERTEX_H__

namespace Gura {

//-----------------------------------------------------------------------------
// Vertex2
//-----------------------------------------------------------------------------
struct GURA_DLLDECLARE Vertex2 {
public:
	double x, y;
public:
	static const Vertex2 Zero;
public:
	inline static void *operator new(size_t size) {
		return MemoryPool::Allocate(size, "Vertex2");
	}
	inline static void operator delete(void *pv) {
		MemoryPool::Deallocate(pv);
	}
public:
	inline Vertex2() : x(0), y(0) {}
	inline Vertex2(double _x, double _y) : x(_x), y(_y) {}
	inline Vertex2(const Vertex2 &vertex) : x(vertex.x), y(vertex.y) {}
	String ToString() const;
};

//-----------------------------------------------------------------------------
// Vertex
//-----------------------------------------------------------------------------
struct GURA_DLLDECLARE Vertex {
public:
	double x, y, z;
public:
	static const Vertex Zero;
public:
	inline static void *operator new(size_t size) {
		return MemoryPool::Allocate(size, "Vertex");
	}
	inline static void operator delete(void *pv) {
		MemoryPool::Deallocate(pv);
	}
public:
	inline Vertex() : x(0), y(0), z(0) {}
	inline Vertex(double _x, double _y) : x(_x), y(_y), z(0) {}
	inline Vertex(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
	inline Vertex(double _x, double _y, double _z, double _w) : x(_x), y(_y), z(_z) {}
	inline Vertex(const Vertex2 &vertex) : x(vertex.x), y(vertex.y), z(0.) {}
	inline Vertex(const Vertex &vertex) : x(vertex.x), y(vertex.y), z(vertex.z) {}
	inline bool IsZero() const { return x == 0. && y == 0. && z == 0.; }
	Vertex Translate(double tx, double ty, double tz) const;
	Vertex RotateX(double rad) const;
	Vertex RotateY(double rad) const;
	Vertex RotateZ(double rad) const;
	static void Neg(Vertex &vRtn, const Vertex &v);
	static void Add(Vertex &vRtn, const Vertex &v1, const Vertex &v2);
	static void Sub(Vertex &vRtn, const Vertex &v1, const Vertex &v2);
	static void Mul(Vertex &vRtn, const Vertex &v, const double &num);
	static bool Div(Signal &sig, Vertex &vRtn, const Vertex &v, const double &num);
	static void Dot(double &rtn, const Vertex &v1, const Vertex &v2);
	static void Cross(Vertex &vRtn, const Vertex &v1, const Vertex &v2);
	static void Norm(double &rtn, const Vertex &v);
	static void Normal(Vertex &vRtn, const Vertex &v1, const Vertex &v2, const Vertex &v3, bool unitFlag);
	String ToString() const;
	static Vertex CreateFromValues(Environment &env, const ValueList &valList);
};

//-----------------------------------------------------------------------------
// VertexRef
//-----------------------------------------------------------------------------
struct GURA_DLLDECLARE VertexRef : public Vertex {
protected:
	int _cntRef;
public:
	inline static void *operator new(size_t size) {
		return MemoryPool::Allocate(size, "VertexRef");
	}
	inline static void operator delete(void *pv) {
		MemoryPool::Deallocate(pv);
	}
public:
	Gura_DeclareReferenceAccessor(VertexRef)
public:
	inline VertexRef() : _cntRef(1) {}
	inline VertexRef(double _x, double _y) : Vertex(_x, _y), _cntRef(1) {}
	inline VertexRef(double _x, double _y, double _z) :
		Vertex(_x, _y, _z), _cntRef(1) {}
	inline VertexRef(const Vertex2 &vertex) : Vertex(vertex), _cntRef(1) {}
	inline VertexRef(const Vertex &vertex) : Vertex(vertex), _cntRef(1) {}
protected:
	inline ~VertexRef() {}
};

}

#endif
