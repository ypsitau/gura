#include "stdafx.h"

extern "C" {
#include "../dSFMT-src-2.2.1/dSFMT.h"
}

namespace Gura {

const int MAX_STACK_LEVEL = 20000;
const size_t InvalidSize = static_cast<size_t>(-1);

const Number RoundOffThreshold = 1e-10;

const Complex Complex::Zero;
const Fraction Fraction::Zero;

bool IsBigEndian()
{
	long num = 0x12345678;
	return *reinterpret_cast<char *>(&num) == 0x12;
}

const char *GetVersion()
{
	return GURA_VERSION;
}

const char *GetOpening()
{
	static char buff[256];
#if defined(_MSC_VER)
	::sprintf(buff, "Gura %s [MSC v.%d, %s] copyright (c) 2011- Y.Saito",
						GURA_VERSION, _MSC_VER, __DATE__);
#elif defined(__GNUC__) && defined(__GNUC_MINOR__)
	::sprintf(buff, "Gura %s [GNUC v.%d.%d, %s] copyright (c) 2011- Y.Saito",
						GURA_VERSION, __GNUC__, __GNUC_MINOR__, __DATE__);
#else
	::sprintf(buff, "Gura %s [%s] copyright (c) 2011- Y.Saito",
						GURA_VERSION, __DATE__);
#endif
	return buff;
}

//-----------------------------------------------------------------------------
// RandomGenerator
//-----------------------------------------------------------------------------
void RandomGenerator::Initialize(unsigned long seed)
{
	::dsfmt_gv_init_gen_rand(seed);	// initialize random generator dSFMT
}

double RandomGenerator::Real2()
{
	return ::dsfmt_gv_genrand_close_open();
}

int RandomGenerator::operator()(int n)
{
	return static_cast<int>(Real2() * n);
}

//-----------------------------------------------------------------------------
// Color
//-----------------------------------------------------------------------------
const Color Color::Zero;

const Color Color::Black(	  0,   0,   0, 255);
const Color Color::Maroon(	128,   0,   0, 255);
const Color Color::Green(	  0, 128,   0, 255);
const Color Color::Olive(	128, 128,   0, 255);
const Color Color::Navy(	  0,   0, 128, 255);
const Color Color::Purple(	128,   0, 128, 255);
const Color Color::Teal(	  0, 128, 128, 255);
const Color Color::Gray(	128, 128, 128, 255);
const Color Color::Silver(	192, 192, 192, 255);
const Color Color::Red(		255,   0,   0, 255);
const Color Color::Lime(	  0, 255,   0, 255);
const Color Color::Yellow(	255, 255,   0, 255);
const Color Color::Blue(	  0,   0, 255, 255);
const Color Color::Fuchsia(	255,   0, 255, 255);
const Color Color::Aqua(	  0, 255, 255, 255);
const Color Color::White(	255, 255, 255, 255);


}
