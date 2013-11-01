#ifndef __GURA_IMAGE_H__
#define __GURA_IMAGE_H__

#include "Memory.h"

namespace Gura {

class Matrix;
class Palette;

//-----------------------------------------------------------------------------
// Image
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Image {
public:
	enum {
		OffsetRed	= 2,
		OffsetGreen	= 1,
		OffsetBlue	= 0,
		OffsetAlpha	= 3,
	};
	enum Format {
		FORMAT_None,
		FORMAT_RGB, FORMAT_RGBA,
	};
	enum ScanDir {
		SCAN_LeftTopHorz, SCAN_LeftTopVert,
		SCAN_RightTopHorz, SCAN_RightTopVert,
		SCAN_LeftBottomHorz, SCAN_LeftBottomVert,
		SCAN_RightBottomHorz, SCAN_RightBottomVert,
	};
public:
	struct Accum {
		size_t red;
		size_t green;
		size_t blue;
		size_t alpha;
		size_t cnt;
		inline void AddRGB(const UChar *pPixel) {
			red   += Image::GetPixelR(pPixel);
			green += Image::GetPixelG(pPixel);
			blue  += Image::GetPixelB(pPixel);
			cnt++;
		}
		inline void AddRGBA(const UChar *pPixel) {
			red   += Image::GetPixelR(pPixel);
			green += Image::GetPixelG(pPixel);
			blue  += Image::GetPixelB(pPixel);
			alpha += Image::GetPixelA(pPixel);
			cnt++;
		}
		inline void StoreRGB(UChar *pPixel) {
			StorePixel(pPixel,
				static_cast<UChar>(red),
				static_cast<UChar>(green),
				static_cast<UChar>(blue));
		}
		inline void StoreRGBA(UChar *pPixel) {
			StorePixel(pPixel,
				static_cast<UChar>(red),
				static_cast<UChar>(green),
				static_cast<UChar>(blue),
				static_cast<UChar>(alpha));
		}
	};
	class GURA_DLLDECLARE Scanner {
	private:
		AutoPtr<Image> _pImage;
		UChar *_pPixel;
		size_t _iPixel, _iLine;
		size_t _nPixels, _nLines;
		int _pitchPixel;
		int _pitchLine;
	public:
		Scanner(Image *pImage, size_t x, size_t y,
								size_t width, size_t height, ScanDir scanDir);
		~Scanner();
		inline void SetPointer(UChar *pPixel) { _pPixel = pPixel; }
		inline void ResetIndex() { _iPixel = 0, _iLine = 0; }
		inline Image *GetImage() { return _pImage.get(); }
		inline UChar *GetPointer() { return _pPixel; }
		inline UChar GetRed() const { return _pPixel[OffsetRed]; }
		inline UChar GetGreen() const { return _pPixel[OffsetGreen]; }
		inline UChar GetBlue() const { return _pPixel[OffsetBlue]; }
		inline UChar GetAlpha() const { return _pPixel[OffsetAlpha]; }
		inline void FwdPixel() {
			_iPixel++;
			_pPixel += _pitchPixel;
		}
		inline void BwdPixel() {
			_iPixel--;
			_pPixel -= _pitchPixel;
		}
		inline void FwdLine() {
			_iLine++;
			_pPixel += _pitchLine;
		}
		inline void BwdLine() {
			_iLine--;
			_pPixel -= _pitchLine;
		}
		inline bool NextPixel() {
			_iPixel++;
			_pPixel += _pitchPixel;
			return _iPixel < _nPixels;
		}
		inline bool NextLine() {
			_iPixel = 0;
			_iLine++;
			if (_iLine >= _nLines) return false;
			_pPixel += _pitchLine;
			return true;
		}
		inline bool Next() {
			_iPixel++;
			_pPixel += _pitchPixel;
			if (_iPixel < _nPixels) return true;
			_iPixel = 0;
			_iLine++;
			if (_iLine >= _nLines) return false;
			_pPixel += _pitchLine;
			return true;
		}
		inline bool Next(Scanner &scannerSlave) {
			_iPixel++;
			_pPixel += _pitchPixel;
			scannerSlave._pPixel += scannerSlave._pitchPixel;
			if (_iPixel < _nPixels) return true;
			_iPixel = 0;
			_iLine++;
			if (_iLine >= _nLines) return false;
			_pPixel += _pitchLine;
			scannerSlave._pPixel += scannerSlave._pitchLine;
			return true;
		}
		inline size_t CountPixels() const { return _nPixels; }
		inline size_t CountLines() const { return _nLines; }
		inline size_t GetPixelIdx() const { return _iPixel; }
		inline size_t GetLineIdx() const { return _iLine; }
		inline void StorePixel(UChar red, UChar green, UChar blue) {
			_pPixel[OffsetRed] = red;
			_pPixel[OffsetGreen] = green;
			_pPixel[OffsetBlue] = blue;
		}
		inline void StorePixel(UChar red, UChar green, UChar blue, UChar alpha) {
			_pPixel[OffsetRed] = red;
			_pPixel[OffsetGreen] = green;
			_pPixel[OffsetBlue] = blue;
			_pPixel[OffsetAlpha] = alpha;
		}
	};
	class IteratorEach : public Iterator {
	private:
		Scanner _scanner;
		bool _doneFlag;
	public:
		inline IteratorEach(Image *pImage,
				size_t x, size_t y, size_t width, size_t height, ScanDir scanDir) :
			Iterator(false),
			_scanner(pImage, x, y, width, height, scanDir), _doneFlag(false) {}
		virtual Iterator *GetSource();
		virtual bool DoNext(Environment &env, Signal sig, Value &value);
		virtual String ToString() const;
		virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
	};
protected:
	int _cntRef;
	Format _format;
	size_t _width, _height;
	struct {
		size_t bitsPerPixel;
		size_t bytesPerPixel;
		size_t bytesPerLine;
	} _metrics;
	AutoPtr<Memory> _pMemory;
	AutoPtr<Palette> _pPalette;
public:
	Gura_DeclareReferenceAccessor(Image);
public:
	Image(Format format);
	Image(const Image &image);
protected:
	virtual ~Image();
public:
	Image *Clone() const;
	inline Memory *GetMemory() { return _pMemory.get(); }
	inline const Memory *GetMemory() const { return _pMemory.get(); }
	inline Format GetFormat() const { return _format; }
	inline size_t GetWidth() const { return _width; }
	inline size_t GetHeight() const { return _height; }
	inline UChar *GetBuffer() {
		return reinterpret_cast<UChar *>(_pMemory->GetPointer());
	}
	inline const UChar *GetBuffer() const {
		return reinterpret_cast<const UChar *>(_pMemory->GetPointer());
	}
	inline bool IsValid() const { return !_pMemory.IsNull(); }
	inline size_t GetBitsPerPixel() const { return _metrics.bitsPerPixel; }
	inline size_t GetBytesPerPixel() const { return _metrics.bytesPerPixel; }
	inline size_t GetBytesPerLine() const { return _metrics.bytesPerLine; }
	inline size_t GetBufferSize() const {
		return GetBytesPerLine() * _height;
	}
	inline UChar *GetPointer(size_t y) {
		return GetBuffer() + GetBytesPerLine() * y;
	}
	inline UChar *GetPointer(size_t x, size_t y) {
		return GetBuffer() + GetBytesPerLine() * y + GetBytesPerPixel() * x;
	}
	inline const UChar *GetPointer(size_t y) const {
		return GetBuffer() + GetBytesPerLine() * y;
	}
	inline const UChar *GetPointer(size_t x, size_t y) const {
		return GetBuffer() + GetBytesPerLine() * y + GetBytesPerPixel() * x;
	}
	inline Scanner *CreateScanner(size_t x, size_t y,
				size_t width, size_t height, ScanDir scanDir = SCAN_LeftTopHorz) {
		return new Scanner(Image::Reference(this), x, y, width, height, scanDir);
	}
	inline Scanner *CreateScanner(ScanDir scanDir = SCAN_LeftTopHorz) {
		return new Scanner(Image::Reference(this), 0, 0, _width, _height, scanDir);
	}
	bool CheckEmpty(Signal sig) const;
	bool CheckValid(Signal sig) const;
	bool AllocBuffer(size_t width, size_t height, UChar fillValue);
	bool AllocBuffer(Signal sig, size_t width, size_t height, UChar fillValue);
	void FreeBuffer();
	inline bool CheckCoord(int x, int y) const {
		return 0 <= x && x < static_cast<int>(_width) &&
				0 <= y && y < static_cast<int>(_height);
	}
	bool CheckCoord(Signal sig, size_t x, size_t y) const;
	bool AdjustCoord(int &x, int &y, int &width, int &height) const;
	void PutPixel(UChar *buff, const Color &color);
	void GetPixel(const UChar *buff, Color &color);
	bool Store(Signal sig, size_t x, size_t y, size_t width, size_t height,
						const Symbol *pSymbol, const Matrix *pMat);
	bool Store(Environment &env, Signal sig, size_t x, size_t y, size_t width, size_t height,
						const Symbol *pSymbol, Iterator *pIterator);
	bool Extract(Signal sig, size_t x, size_t y, size_t width, size_t height,
						const Symbol *pSymbol, Matrix *pMat);
	bool Extract(Signal sig, size_t x, size_t y, size_t width, size_t height,
						const Symbol *pSymbol, ValueList &valList);
	void ReplaceColorRect(size_t x, size_t y, size_t width, size_t height,
						const Color &colorOrg, const Color &color, double tolerance);
	inline void ReplaceColor(const Color &colorOrg, Color &color, double tolerance) {
		ReplaceColorRect(0, 0, _width, _height, colorOrg, color, tolerance);
	}
	void FillRect(size_t x, size_t y, size_t width, size_t height, const Color &color);
	inline void Fill(const Color &color) {
		FillRect(0, 0, _width, _height, color);
	}
	void FillRectAlpha(size_t x, size_t y,
			size_t width, size_t height, UChar alpha);
	void FillRectAlpha(size_t x, size_t y,
			size_t width, size_t height, UChar alpha, const Color &color, double tolerance);
	inline void FillAlpha(UChar alpha) {
		FillRectAlpha(0, 0, _width, _height, alpha);
	}
	inline void FillAlpha(UChar alpha, const Color &color, double tolerance) {
		FillRectAlpha(0, 0, _width, _height, alpha, color, tolerance);
	}
	const Palette *GetPalette() const { return _pPalette.get(); }
	Image *ReduceColor(Signal sig, const Palette *pPalette);
	Image *GrayScale(Signal sig);
	Image *Blur(Signal sig, int radius, Number sigma);
	Image *Flip(Signal sig, bool horzFlag, bool vertFlag);
	Image *Rotate90(Signal sig, bool clockwiseFlag);
	Image *Rotate(Signal sig, double angle, const Color &color);
	Image *Crop(Signal sig, size_t x, size_t y, size_t width, size_t height);
	Image *Resize(Signal sig, size_t width, size_t height);
	void Paste(size_t x, size_t y, Image *pImage,
		size_t width, size_t height, size_t xOffset, size_t yOffset, UChar alpha);
	Palette *CreateEmptyPalette(Environment &env, size_t nEntries);
	void SetPalette(Palette *pPalette);
	bool Read(Environment &env, Signal sig, Stream &stream, const char *imageType);
	bool Write(Environment &env, Signal sig, Stream &stream, const char *imageType);
	int CalcDIBBitCount() const;
	static inline size_t CalcDIBPaletteSize(int biBitCount) {
		return (biBitCount <= 8)? (1 << biBitCount) * 4 : 0;
	}
	size_t CalcDIBImageSize(int biBitCount, bool maskFlag) const;
	bool ReadDIBPalette(Environment &env, Signal sig, Stream &stream, int biBitCount);
	bool WriteDIBPalette(Environment &env, Signal sig, Stream &stream, int biBitCount);
	bool ReadDIB(Signal sig, Stream &stream,
				int biWidth, int biHeight, int biBitCount, bool maskFlag);
	bool WriteDIB(Signal sig, Stream &stream, int biBitCount, bool maskFlag);
	size_t SymbolToPixelOffset(Signal sig, const Symbol *pSymbol) const;
	static Format SymbolToFormat(Signal sig, const Symbol *pSymbol);
	static const Symbol *FormatToSymbol(Format format);
	static inline UChar GetPixelGray(UChar *buff) {
		return Color::CalcGray(GetPixelR(buff), GetPixelG(buff), GetPixelB(buff));
	}
	static inline void StorePixel(UChar *buff, UChar red, UChar green, UChar blue) {
		*(buff + OffsetRed) = red;
		*(buff + OffsetGreen) = green;
		*(buff + OffsetBlue) = blue;
	}
	static inline void StorePixel(UChar *buff, UChar red, UChar green, UChar blue, UChar alpha) {
		*(buff + OffsetRed) = red;
		*(buff + OffsetGreen) = green;
		*(buff + OffsetBlue) = blue;
		*(buff + OffsetAlpha) = alpha;
	}
	static inline void StorePixel(UChar *pPixelDst, const UChar *pPixelSrc, bool alphaFlag) {
		*pPixelDst++ = *pPixelSrc++;
		*pPixelDst++ = *pPixelSrc++;
		*pPixelDst++ = *pPixelSrc++;
		if (alphaFlag) *pPixelDst++ = *pPixelSrc++;
	}
	static inline void StorePixelRGB(UChar *pPixelDst, const UChar *pPixelSrc) {
		*pPixelDst++ = *pPixelSrc++;
		*pPixelDst++ = *pPixelSrc++;
		*pPixelDst++ = *pPixelSrc++;
	}
	static inline void StorePixelRGBA(UChar *pPixelDst, const UChar *pPixelSrc) {
		*pPixelDst++ = *pPixelSrc++;
		*pPixelDst++ = *pPixelSrc++;
		*pPixelDst++ = *pPixelSrc++;
		*pPixelDst++ = *pPixelSrc++;
	}
	static inline void StorePixelRGBA(UChar *pPixelDst, const UChar *pPixelSrc, UChar alpha) {
		*pPixelDst++ = *pPixelSrc++;
		*pPixelDst++ = *pPixelSrc++;
		*pPixelDst++ = *pPixelSrc++;
		*pPixelDst++ = alpha;
	}
	static inline UChar GetPixelR(const UChar *buff) {
		return *(buff + OffsetRed);
	}
	static inline UChar GetPixelG(const UChar *buff) {
		return *(buff + OffsetGreen);
	}
	static inline UChar GetPixelB(const UChar *buff) {
		return *(buff + OffsetBlue);
	}
	static inline UChar GetPixelA(const UChar *buff) {
		return *(buff + OffsetAlpha);
	}
	static inline void RotateCoord(int &xm, int &ym,
							int x, int y, int cos1024, int sin1024) {
		xm = (x * cos1024 - y * sin1024) >> 10;
		ym = (x * sin1024 + y * cos1024) >> 10;
	}
#if GURA_USE_MSWIN_DIB
public:
	inline HBITMAP GetHBITMAP() {
		return dynamic_cast<MemoryDIB *>(GetMemory())->GetHBITMAP();
	}
#endif
private:
	void InitMetrics();
	Image *CreateDerivation(Signal sig,
				size_t width, size_t height, Palette *pPalette = NULL);
};

//-----------------------------------------------------------------------------
// ImageStreamer
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE ImageStreamer {
public:
	typedef std::vector<ImageStreamer *> List;
private:
	const char *_imageType;
	static List *_pList;
public:
	inline ImageStreamer(const char *imageType) : _imageType(imageType) {}
	inline const char *GetImageType() const { return _imageType; }
	virtual bool IsResponsible(Signal sig, Stream &stream) = 0;
	virtual bool Read(Environment &env, Signal sig, Image *pImage, Stream &stream) = 0;
	virtual bool Write(Environment &env, Signal sig, Image *pImage, Stream &stream) = 0;
public:
	static void Register(ImageStreamer *pImageStreamer);
	static ImageStreamer *FindResponsible(Signal sig, Stream &stream, const char *imageType);
	static ImageStreamer *FindByImageType(const char *imageType);
};

}

#endif
