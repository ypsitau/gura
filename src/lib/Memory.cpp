//=============================================================================
// Memory
//=============================================================================
#include "stdafx.h"

namespace Gura {

//-----------------------------------------------------------------------------
// Memory
//-----------------------------------------------------------------------------
Memory::~Memory()
{
	// virtual destructor
}

Memory *Memory::Clone() const
{
	return nullptr;
}

String Memory::MakeId() const
{
	char str[128];
	::sprintf(str, "%p", _buff);
	return str;
}

//-----------------------------------------------------------------------------
// MemoryOwner
//-----------------------------------------------------------------------------
MemoryOwner::~MemoryOwner()
{
	Clear();
}

void MemoryOwner::Clear()
{
	foreach (MemoryOwner, ppMemory, *this) {
		Memory *pMemory = *ppMemory;
		Memory::Delete(pMemory);
	}
	clear();
}

#if defined(GURA_ON_MSWIN)

//-----------------------------------------------------------------------------
// MemoryHeap
//-----------------------------------------------------------------------------
MemoryHeap::MemoryHeap(size_t bytes)
{
	_bytes = bytes;
	_buff = reinterpret_cast<char *>(::LocalAlloc(LMEM_FIXED, _bytes));
}

MemoryHeap::~MemoryHeap()
{
	::LocalFree(_buff);
}

Memory *MemoryHeap::Clone() const
{
	void *buff = ::LocalAlloc(LMEM_FIXED, _bytes);
	if (buff == nullptr) return nullptr;
	::memcpy(buff, _buff, _bytes);
	return new MemoryHeap(_bytes, buff);
}

//-----------------------------------------------------------------------------
// MemoryDIB
//-----------------------------------------------------------------------------
MemoryDIB::MemoryDIB() : _hBitmap(nullptr)
{
}

MemoryDIB::~MemoryDIB()
{
	if (_hBitmap != nullptr) ::DeleteObject(_hBitmap);
}

bool MemoryDIB::AllocBuffer(size_t width, size_t height, size_t bitsPerPixel)
{
	BITMAPINFO bmi;
	BITMAPINFOHEADER &hdr = bmi.bmiHeader;
	::memset(&bmi, 0, sizeof(BITMAPINFO));
	hdr.biSize = sizeof(BITMAPINFOHEADER);
	hdr.biWidth = static_cast<int>(width);
	hdr.biHeight = -static_cast<int>(height);
	hdr.biPlanes = 1;
	hdr.biBitCount = static_cast<WORD>(bitsPerPixel);
	hdr.biCompression = BI_RGB;
	hdr.biSizeImage = 0;
	hdr.biXPelsPerMeter = 0;
	hdr.biYPelsPerMeter = 0;
	hdr.biClrUsed = 0;
	hdr.biClrImportant = 0;
	void *buff = nullptr;
	_hBitmap = ::CreateDIBSection(nullptr, &bmi, DIB_RGB_COLORS, &buff, nullptr, 0);
	_buff = reinterpret_cast<char *>(buff);
	_bytes = ((bitsPerPixel + 7) / 8 * width + 3) / 4 * 4;
	return _hBitmap != nullptr && _buff != nullptr;
}

Memory *MemoryDIB::Clone() const
{
	return nullptr;
}

#else

//-----------------------------------------------------------------------------
// MemoryHeap
//-----------------------------------------------------------------------------
MemoryHeap::MemoryHeap(size_t bytes)
{
	_bytes = bytes;
	_buff = reinterpret_cast<char *>(::malloc(_bytes));
}

MemoryHeap::~MemoryHeap()
{
	::free(_buff);
}

Memory *MemoryHeap::Clone() const
{
	void *buff = ::malloc(_bytes);
	if (buff == nullptr) return nullptr;
	::memcpy(buff, _buff, _bytes);
	return new MemoryHeap(_bytes, buff);
}

#endif

}
