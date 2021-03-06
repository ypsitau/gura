//=============================================================================
// MemoryPool
//=============================================================================
#ifndef __GURA_MEMORYPOOL_H__
#define __GURA_MEMORYPOOL_H__
#include "Common.h"

namespace Gura {

//-----------------------------------------------------------------------------
// MemoryPool
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE MemoryPool {
public:
	class Chunk {
	public:
		virtual void Deallocate(void *p) = 0;
	};
	struct Pool {
		Pool *pPoolPrev;
		char buff[1];
	};
	struct Header {
		union {
			Chunk *pChunk;
			Header *pHeaderVacantNext;
		} u;
		const char *ownerName;
	};
	class ChunkFixed : public Chunk {
	private:
		size_t _bytesBlock;
		size_t _nBlocks;
		size_t _iBlockNext;
		Pool *_pPool;
		Header *_pHeaderVacantHead;
	public:
		inline ChunkFixed(size_t bytesBlock, size_t nBlocks) :
			_bytesBlock(bytesBlock), _nBlocks(nBlocks), _iBlockNext(nBlocks),
			_pPool(nullptr), _pHeaderVacantHead(nullptr) {}
		inline size_t GetBytesBlock() const { return _bytesBlock; }
		void Print() const;
		void *Allocate(const char *ownerName);
		virtual void Deallocate(void *p);
	};
	class ChunkVariable : public Chunk {
	public:
		inline ChunkVariable() {}
		void *Allocate(size_t bytes, const char *ownerName);
		virtual void Deallocate(void *p);
	};
private:
	static MemoryPool _inst;
private:
	ChunkFixed _chunkFixed1;
	ChunkFixed _chunkFixed2;
	ChunkVariable _chunkVariable;
public:
	MemoryPool();
	inline static void *Allocate(size_t bytes, const char *ownerName = "") {
		return _inst.DoAllocate(bytes, ownerName);
	}
	inline static void Deallocate(void *p) { _inst.DoDeallocate(p); }
	inline static void Print() { _inst.DoPrint(); }
private:
	void *DoAllocate(size_t bytes, const char *ownerName);
	void DoDeallocate(void *p);
	void DoPrint() const;
};

//-----------------------------------------------------------------------------
// Allocator
//-----------------------------------------------------------------------------
template<typename _Tp> class Allocator : public std::allocator<_Tp> {
public:
	inline Allocator() {}
	inline Allocator(const Allocator &a) throw() {}
	template<typename _Tp1> inline Allocator(const Allocator<_Tp1> &a) throw() {}
	template<typename _Tp1> struct rebind {
		typedef Allocator<_Tp1> other;
	};
	inline _Tp *allocate(size_t num, std::allocator<void>::const_pointer hint = nullptr) {
		return reinterpret_cast<_Tp *>(MemoryPool::Allocate(num * sizeof(_Tp), "Allocator"));
	}
	inline void deallocate(_Tp *p, size_t num) {
		MemoryPool::Deallocate(p);
	}
};

}

#endif
