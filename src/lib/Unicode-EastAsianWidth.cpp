//=============================================================================
// Unicode-EastAsianWidth
//=============================================================================
#include "stdafx.h"

namespace Gura {

const Codec::WidthInfo Codec::_widthInfoTbl[] = {
	{ 0x000020, WIDTHPROP_N  },
	{ 0x00007f, WIDTHPROP_Na },
	{ 0x0000a1, WIDTHPROP_N  },
	{ 0x0000a2, WIDTHPROP_A  },
	{ 0x0000a4, WIDTHPROP_Na },
	{ 0x0000a5, WIDTHPROP_A  },
	{ 0x0000a7, WIDTHPROP_Na },
	{ 0x0000a9, WIDTHPROP_A  },
	{ 0x0000aa, WIDTHPROP_N  },
	{ 0x0000ab, WIDTHPROP_A  },
	{ 0x0000ac, WIDTHPROP_N  },
	{ 0x0000ad, WIDTHPROP_Na },
	{ 0x0000af, WIDTHPROP_A  },
	{ 0x0000b0, WIDTHPROP_Na },
	{ 0x0000b5, WIDTHPROP_A  },
	{ 0x0000b6, WIDTHPROP_N  },
	{ 0x0000bb, WIDTHPROP_A  },
	{ 0x0000bc, WIDTHPROP_N  },
	{ 0x0000c0, WIDTHPROP_A  },
	{ 0x0000c6, WIDTHPROP_N  },
	{ 0x0000c7, WIDTHPROP_A  },
	{ 0x0000d0, WIDTHPROP_N  },
	{ 0x0000d1, WIDTHPROP_A  },
	{ 0x0000d7, WIDTHPROP_N  },
	{ 0x0000d9, WIDTHPROP_A  },
	{ 0x0000de, WIDTHPROP_N  },
	{ 0x0000e2, WIDTHPROP_A  },
	{ 0x0000e6, WIDTHPROP_N  },
	{ 0x0000e7, WIDTHPROP_A  },
	{ 0x0000e8, WIDTHPROP_N  },
	{ 0x0000eb, WIDTHPROP_A  },
	{ 0x0000ec, WIDTHPROP_N  },
	{ 0x0000ee, WIDTHPROP_A  },
	{ 0x0000f0, WIDTHPROP_N  },
	{ 0x0000f1, WIDTHPROP_A  },
	{ 0x0000f2, WIDTHPROP_N  },
	{ 0x0000f4, WIDTHPROP_A  },
	{ 0x0000f7, WIDTHPROP_N  },
	{ 0x0000fb, WIDTHPROP_A  },
	{ 0x0000fc, WIDTHPROP_N  },
	{ 0x0000fd, WIDTHPROP_A  },
	{ 0x0000fe, WIDTHPROP_N  },
	{ 0x0000ff, WIDTHPROP_A  },
	{ 0x000101, WIDTHPROP_N  },
	{ 0x000102, WIDTHPROP_A  },
	{ 0x000111, WIDTHPROP_N  },
	{ 0x000112, WIDTHPROP_A  },
	{ 0x000113, WIDTHPROP_N  },
	{ 0x000114, WIDTHPROP_A  },
	{ 0x00011b, WIDTHPROP_N  },
	{ 0x00011c, WIDTHPROP_A  },
	{ 0x000126, WIDTHPROP_N  },
	{ 0x000128, WIDTHPROP_A  },
	{ 0x00012b, WIDTHPROP_N  },
	{ 0x00012c, WIDTHPROP_A  },
	{ 0x000131, WIDTHPROP_N  },
	{ 0x000134, WIDTHPROP_A  },
	{ 0x000138, WIDTHPROP_N  },
	{ 0x000139, WIDTHPROP_A  },
	{ 0x00013f, WIDTHPROP_N  },
	{ 0x000143, WIDTHPROP_A  },
	{ 0x000144, WIDTHPROP_N  },
	{ 0x000145, WIDTHPROP_A  },
	{ 0x000148, WIDTHPROP_N  },
	{ 0x00014c, WIDTHPROP_A  },
	{ 0x00014d, WIDTHPROP_N  },
	{ 0x00014e, WIDTHPROP_A  },
	{ 0x000152, WIDTHPROP_N  },
	{ 0x000154, WIDTHPROP_A  },
	{ 0x000166, WIDTHPROP_N  },
	{ 0x000168, WIDTHPROP_A  },
	{ 0x00016b, WIDTHPROP_N  },
	{ 0x00016c, WIDTHPROP_A  },
	{ 0x0001ce, WIDTHPROP_N  },
	{ 0x0001cf, WIDTHPROP_A  },
	{ 0x0001d0, WIDTHPROP_N  },
	{ 0x0001d1, WIDTHPROP_A  },
	{ 0x0001d2, WIDTHPROP_N  },
	{ 0x0001d3, WIDTHPROP_A  },
	{ 0x0001d4, WIDTHPROP_N  },
	{ 0x0001d5, WIDTHPROP_A  },
	{ 0x0001d6, WIDTHPROP_N  },
	{ 0x0001d7, WIDTHPROP_A  },
	{ 0x0001d8, WIDTHPROP_N  },
	{ 0x0001d9, WIDTHPROP_A  },
	{ 0x0001da, WIDTHPROP_N  },
	{ 0x0001db, WIDTHPROP_A  },
	{ 0x0001dc, WIDTHPROP_N  },
	{ 0x0001dd, WIDTHPROP_A  },
	{ 0x000251, WIDTHPROP_N  },
	{ 0x000252, WIDTHPROP_A  },
	{ 0x000261, WIDTHPROP_N  },
	{ 0x000262, WIDTHPROP_A  },
	{ 0x0002c4, WIDTHPROP_N  },
	{ 0x0002c5, WIDTHPROP_A  },
	{ 0x0002c7, WIDTHPROP_N  },
	{ 0x0002c8, WIDTHPROP_A  },
	{ 0x0002c9, WIDTHPROP_N  },
	{ 0x0002cc, WIDTHPROP_A  },
	{ 0x0002cd, WIDTHPROP_N  },
	{ 0x0002ce, WIDTHPROP_A  },
	{ 0x0002d0, WIDTHPROP_N  },
	{ 0x0002d1, WIDTHPROP_A  },
	{ 0x0002d8, WIDTHPROP_N  },
	{ 0x0002dc, WIDTHPROP_A  },
	{ 0x0002dd, WIDTHPROP_N  },
	{ 0x0002de, WIDTHPROP_A  },
	{ 0x0002df, WIDTHPROP_N  },
	{ 0x0002e0, WIDTHPROP_A  },
	{ 0x000300, WIDTHPROP_N  },
	{ 0x000370, WIDTHPROP_A  },
	{ 0x000391, WIDTHPROP_N  },
	{ 0x0003aa, WIDTHPROP_A  },
	{ 0x0003b1, WIDTHPROP_N  },
	{ 0x0003c2, WIDTHPROP_A  },
	{ 0x0003c3, WIDTHPROP_N  },
	{ 0x0003ca, WIDTHPROP_A  },
	{ 0x000401, WIDTHPROP_N  },
	{ 0x000402, WIDTHPROP_A  },
	{ 0x000410, WIDTHPROP_N  },
	{ 0x000450, WIDTHPROP_A  },
	{ 0x000451, WIDTHPROP_N  },
	{ 0x000452, WIDTHPROP_A  },
	{ 0x001100, WIDTHPROP_N  },
	{ 0x001160, WIDTHPROP_W  },
	{ 0x002010, WIDTHPROP_N  },
	{ 0x002011, WIDTHPROP_A  },
	{ 0x002013, WIDTHPROP_N  },
	{ 0x002017, WIDTHPROP_A  },
	{ 0x002018, WIDTHPROP_N  },
	{ 0x00201a, WIDTHPROP_A  },
	{ 0x00201c, WIDTHPROP_N  },
	{ 0x00201e, WIDTHPROP_A  },
	{ 0x002020, WIDTHPROP_N  },
	{ 0x002023, WIDTHPROP_A  },
	{ 0x002024, WIDTHPROP_N  },
	{ 0x002028, WIDTHPROP_A  },
	{ 0x002030, WIDTHPROP_N  },
	{ 0x002031, WIDTHPROP_A  },
	{ 0x002032, WIDTHPROP_N  },
	{ 0x002034, WIDTHPROP_A  },
	{ 0x002035, WIDTHPROP_N  },
	{ 0x002036, WIDTHPROP_A  },
	{ 0x00203b, WIDTHPROP_N  },
	{ 0x00203c, WIDTHPROP_A  },
	{ 0x00203e, WIDTHPROP_N  },
	{ 0x00203f, WIDTHPROP_A  },
	{ 0x002074, WIDTHPROP_N  },
	{ 0x002075, WIDTHPROP_A  },
	{ 0x00207f, WIDTHPROP_N  },
	{ 0x002080, WIDTHPROP_A  },
	{ 0x002081, WIDTHPROP_N  },
	{ 0x002085, WIDTHPROP_A  },
	{ 0x0020a9, WIDTHPROP_N  },
	{ 0x0020aa, WIDTHPROP_H  },
	{ 0x0020ac, WIDTHPROP_N  },
	{ 0x0020ad, WIDTHPROP_A  },
	{ 0x002103, WIDTHPROP_N  },
	{ 0x002104, WIDTHPROP_A  },
	{ 0x002105, WIDTHPROP_N  },
	{ 0x002106, WIDTHPROP_A  },
	{ 0x002109, WIDTHPROP_N  },
	{ 0x00210a, WIDTHPROP_A  },
	{ 0x002113, WIDTHPROP_N  },
	{ 0x002114, WIDTHPROP_A  },
	{ 0x002116, WIDTHPROP_N  },
	{ 0x002117, WIDTHPROP_A  },
	{ 0x002121, WIDTHPROP_N  },
	{ 0x002123, WIDTHPROP_A  },
	{ 0x002126, WIDTHPROP_N  },
	{ 0x002127, WIDTHPROP_A  },
	{ 0x00212b, WIDTHPROP_N  },
	{ 0x00212c, WIDTHPROP_A  },
	{ 0x002153, WIDTHPROP_N  },
	{ 0x002155, WIDTHPROP_A  },
	{ 0x00215b, WIDTHPROP_N  },
	{ 0x00215f, WIDTHPROP_A  },
	{ 0x002160, WIDTHPROP_N  },
	{ 0x00216c, WIDTHPROP_A  },
	{ 0x002170, WIDTHPROP_N  },
	{ 0x00217a, WIDTHPROP_A  },
	{ 0x002189, WIDTHPROP_N  },
	{ 0x00219a, WIDTHPROP_A  },
	{ 0x0021b8, WIDTHPROP_N  },
	{ 0x0021ba, WIDTHPROP_A  },
	{ 0x0021d2, WIDTHPROP_N  },
	{ 0x0021d3, WIDTHPROP_A  },
	{ 0x0021d4, WIDTHPROP_N  },
	{ 0x0021d5, WIDTHPROP_A  },
	{ 0x0021e7, WIDTHPROP_N  },
	{ 0x0021e8, WIDTHPROP_A  },
	{ 0x002200, WIDTHPROP_N  },
	{ 0x002201, WIDTHPROP_A  },
	{ 0x002202, WIDTHPROP_N  },
	{ 0x002204, WIDTHPROP_A  },
	{ 0x002207, WIDTHPROP_N  },
	{ 0x002209, WIDTHPROP_A  },
	{ 0x00220b, WIDTHPROP_N  },
	{ 0x00220c, WIDTHPROP_A  },
	{ 0x00220f, WIDTHPROP_N  },
	{ 0x002210, WIDTHPROP_A  },
	{ 0x002211, WIDTHPROP_N  },
	{ 0x002212, WIDTHPROP_A  },
	{ 0x002215, WIDTHPROP_N  },
	{ 0x002216, WIDTHPROP_A  },
	{ 0x00221a, WIDTHPROP_N  },
	{ 0x00221b, WIDTHPROP_A  },
	{ 0x00221d, WIDTHPROP_N  },
	{ 0x002221, WIDTHPROP_A  },
	{ 0x002223, WIDTHPROP_N  },
	{ 0x002224, WIDTHPROP_A  },
	{ 0x002225, WIDTHPROP_N  },
	{ 0x002226, WIDTHPROP_A  },
	{ 0x002227, WIDTHPROP_N  },
	{ 0x00222d, WIDTHPROP_A  },
	{ 0x00222e, WIDTHPROP_N  },
	{ 0x00222f, WIDTHPROP_A  },
	{ 0x002234, WIDTHPROP_N  },
	{ 0x002238, WIDTHPROP_A  },
	{ 0x00223c, WIDTHPROP_N  },
	{ 0x00223e, WIDTHPROP_A  },
	{ 0x002248, WIDTHPROP_N  },
	{ 0x002249, WIDTHPROP_A  },
	{ 0x00224c, WIDTHPROP_N  },
	{ 0x00224d, WIDTHPROP_A  },
	{ 0x002252, WIDTHPROP_N  },
	{ 0x002253, WIDTHPROP_A  },
	{ 0x002260, WIDTHPROP_N  },
	{ 0x002262, WIDTHPROP_A  },
	{ 0x002264, WIDTHPROP_N  },
	{ 0x002268, WIDTHPROP_A  },
	{ 0x00226a, WIDTHPROP_N  },
	{ 0x00226c, WIDTHPROP_A  },
	{ 0x00226e, WIDTHPROP_N  },
	{ 0x002270, WIDTHPROP_A  },
	{ 0x002282, WIDTHPROP_N  },
	{ 0x002284, WIDTHPROP_A  },
	{ 0x002286, WIDTHPROP_N  },
	{ 0x002288, WIDTHPROP_A  },
	{ 0x002295, WIDTHPROP_N  },
	{ 0x002296, WIDTHPROP_A  },
	{ 0x002299, WIDTHPROP_N  },
	{ 0x00229a, WIDTHPROP_A  },
	{ 0x0022a5, WIDTHPROP_N  },
	{ 0x0022a6, WIDTHPROP_A  },
	{ 0x0022bf, WIDTHPROP_N  },
	{ 0x0022c0, WIDTHPROP_A  },
	{ 0x002312, WIDTHPROP_N  },
	{ 0x002313, WIDTHPROP_A  },
	{ 0x002329, WIDTHPROP_N  },
	{ 0x00232b, WIDTHPROP_W  },
	{ 0x002460, WIDTHPROP_N  },
	{ 0x0024ea, WIDTHPROP_A  },
	{ 0x0024eb, WIDTHPROP_N  },
	{ 0x00254c, WIDTHPROP_A  },
	{ 0x002550, WIDTHPROP_N  },
	{ 0x002574, WIDTHPROP_A  },
	{ 0x002580, WIDTHPROP_N  },
	{ 0x002590, WIDTHPROP_A  },
	{ 0x002592, WIDTHPROP_N  },
	{ 0x002596, WIDTHPROP_A  },
	{ 0x0025a0, WIDTHPROP_N  },
	{ 0x0025a2, WIDTHPROP_A  },
	{ 0x0025a3, WIDTHPROP_N  },
	{ 0x0025aa, WIDTHPROP_A  },
	{ 0x0025b2, WIDTHPROP_N  },
	{ 0x0025b4, WIDTHPROP_A  },
	{ 0x0025b6, WIDTHPROP_N  },
	{ 0x0025b8, WIDTHPROP_A  },
	{ 0x0025bc, WIDTHPROP_N  },
	{ 0x0025be, WIDTHPROP_A  },
	{ 0x0025c0, WIDTHPROP_N  },
	{ 0x0025c2, WIDTHPROP_A  },
	{ 0x0025c6, WIDTHPROP_N  },
	{ 0x0025c9, WIDTHPROP_A  },
	{ 0x0025cb, WIDTHPROP_N  },
	{ 0x0025cc, WIDTHPROP_A  },
	{ 0x0025ce, WIDTHPROP_N  },
	{ 0x0025d2, WIDTHPROP_A  },
	{ 0x0025e2, WIDTHPROP_N  },
	{ 0x0025e6, WIDTHPROP_A  },
	{ 0x0025ef, WIDTHPROP_N  },
	{ 0x0025f0, WIDTHPROP_A  },
	{ 0x002605, WIDTHPROP_N  },
	{ 0x002607, WIDTHPROP_A  },
	{ 0x002609, WIDTHPROP_N  },
	{ 0x00260a, WIDTHPROP_A  },
	{ 0x00260e, WIDTHPROP_N  },
	{ 0x002610, WIDTHPROP_A  },
	{ 0x002614, WIDTHPROP_N  },
	{ 0x002616, WIDTHPROP_A  },
	{ 0x00261c, WIDTHPROP_N  },
	{ 0x00261d, WIDTHPROP_A  },
	{ 0x00261e, WIDTHPROP_N  },
	{ 0x00261f, WIDTHPROP_A  },
	{ 0x002640, WIDTHPROP_N  },
	{ 0x002641, WIDTHPROP_A  },
	{ 0x002642, WIDTHPROP_N  },
	{ 0x002643, WIDTHPROP_A  },
	{ 0x002660, WIDTHPROP_N  },
	{ 0x002662, WIDTHPROP_A  },
	{ 0x002663, WIDTHPROP_N  },
	{ 0x002666, WIDTHPROP_A  },
	{ 0x002667, WIDTHPROP_N  },
	{ 0x00266b, WIDTHPROP_A  },
	{ 0x00266c, WIDTHPROP_N  },
	{ 0x00266e, WIDTHPROP_A  },
	{ 0x00266f, WIDTHPROP_N  },
	{ 0x002670, WIDTHPROP_A  },
	{ 0x00269e, WIDTHPROP_N  },
	{ 0x0026a0, WIDTHPROP_A  },
	{ 0x0026be, WIDTHPROP_N  },
	{ 0x0026c0, WIDTHPROP_A  },
	{ 0x0026c4, WIDTHPROP_N  },
	{ 0x0026ce, WIDTHPROP_A  },
	{ 0x0026cf, WIDTHPROP_N  },
	{ 0x0026e2, WIDTHPROP_A  },
	{ 0x0026e3, WIDTHPROP_N  },
	{ 0x0026e4, WIDTHPROP_A  },
	{ 0x0026e8, WIDTHPROP_N  },
	{ 0x002700, WIDTHPROP_A  },
	{ 0x00273d, WIDTHPROP_N  },
	{ 0x00273e, WIDTHPROP_A  },
	{ 0x002757, WIDTHPROP_N  },
	{ 0x002758, WIDTHPROP_A  },
	{ 0x002776, WIDTHPROP_N  },
	{ 0x002780, WIDTHPROP_A  },
	{ 0x0027e6, WIDTHPROP_N  },
	{ 0x0027ee, WIDTHPROP_Na },
	{ 0x002985, WIDTHPROP_N  },
	{ 0x002987, WIDTHPROP_Na },
	{ 0x002b55, WIDTHPROP_N  },
	{ 0x002b5a, WIDTHPROP_A  },
	{ 0x002e80, WIDTHPROP_N  },
	{ 0x003000, WIDTHPROP_W  },
	{ 0x003001, WIDTHPROP_F  },
	{ 0x00303f, WIDTHPROP_W  },
	{ 0x003041, WIDTHPROP_N  },
	{ 0x003248, WIDTHPROP_W  },
	{ 0x003250, WIDTHPROP_A  },
	{ 0x004dc0, WIDTHPROP_W  },
	{ 0x004e00, WIDTHPROP_N  },
	{ 0x00a4d0, WIDTHPROP_W  },
	{ 0x00a960, WIDTHPROP_N  },
	{ 0x00a980, WIDTHPROP_W  },
	{ 0x00ac00, WIDTHPROP_N  },
	{ 0x00d7b0, WIDTHPROP_W  },
	{ 0x00e000, WIDTHPROP_N  },
	{ 0x00f900, WIDTHPROP_A  },
	{ 0x00fb00, WIDTHPROP_W  },
	{ 0x00fe00, WIDTHPROP_N  },
	{ 0x00fe10, WIDTHPROP_A  },
	{ 0x00fe20, WIDTHPROP_W  },
	{ 0x00fe30, WIDTHPROP_N  },
	{ 0x00fe70, WIDTHPROP_W  },
	{ 0x00ff01, WIDTHPROP_N  },
	{ 0x00ff61, WIDTHPROP_F  },
	{ 0x00ffe0, WIDTHPROP_H  },
	{ 0x00ffe8, WIDTHPROP_F  },
	{ 0x00fff9, WIDTHPROP_H  },
	{ 0x00fffd, WIDTHPROP_N  },
	{ 0x010000, WIDTHPROP_A  },
	{ 0x01b000, WIDTHPROP_N  },
	{ 0x01bc00, WIDTHPROP_W  },
	{ 0x01f100, WIDTHPROP_N  },
	{ 0x01f10b, WIDTHPROP_A  },
	{ 0x01f110, WIDTHPROP_N  },
	{ 0x01f12e, WIDTHPROP_A  },
	{ 0x01f130, WIDTHPROP_N  },
	{ 0x01f16a, WIDTHPROP_A  },
	{ 0x01f170, WIDTHPROP_N  },
	{ 0x01f1e6, WIDTHPROP_A  },
	{ 0x01f200, WIDTHPROP_N  },
	{ 0x01f300, WIDTHPROP_W  },
	{ 0x020000, WIDTHPROP_N  },
	{ 0x0e0001, WIDTHPROP_W  },
	{ 0x0e0100, WIDTHPROP_N  },
	{ 0x10fffe, WIDTHPROP_A  },
	{ 0x000000, WIDTHPROP_N  },
	{ 0x000020, WIDTHPROP_N  },
	{ 0x00007f, WIDTHPROP_Na },
	{ 0x0000a1, WIDTHPROP_N  },
	{ 0x0000a2, WIDTHPROP_A  },
	{ 0x0000a4, WIDTHPROP_Na },
	{ 0x0000a5, WIDTHPROP_A  },
	{ 0x0000a7, WIDTHPROP_Na },
	{ 0x0000a9, WIDTHPROP_A  },
	{ 0x0000aa, WIDTHPROP_N  },
	{ 0x0000ab, WIDTHPROP_A  },
	{ 0x0000ac, WIDTHPROP_N  },
	{ 0x0000ad, WIDTHPROP_Na },
	{ 0x0000af, WIDTHPROP_A  },
	{ 0x0000b0, WIDTHPROP_Na },
	{ 0x0000b5, WIDTHPROP_A  },
	{ 0x0000b6, WIDTHPROP_N  },
	{ 0x0000bb, WIDTHPROP_A  },
	{ 0x0000bc, WIDTHPROP_N  },
	{ 0x0000c0, WIDTHPROP_A  },
	{ 0x0000c6, WIDTHPROP_N  },
	{ 0x0000c7, WIDTHPROP_A  },
	{ 0x0000d0, WIDTHPROP_N  },
	{ 0x0000d1, WIDTHPROP_A  },
	{ 0x0000d7, WIDTHPROP_N  },
	{ 0x0000d9, WIDTHPROP_A  },
	{ 0x0000de, WIDTHPROP_N  },
	{ 0x0000e2, WIDTHPROP_A  },
	{ 0x0000e6, WIDTHPROP_N  },
	{ 0x0000e7, WIDTHPROP_A  },
	{ 0x0000e8, WIDTHPROP_N  },
	{ 0x0000eb, WIDTHPROP_A  },
	{ 0x0000ec, WIDTHPROP_N  },
	{ 0x0000ee, WIDTHPROP_A  },
	{ 0x0000f0, WIDTHPROP_N  },
	{ 0x0000f1, WIDTHPROP_A  },
	{ 0x0000f2, WIDTHPROP_N  },
	{ 0x0000f4, WIDTHPROP_A  },
	{ 0x0000f7, WIDTHPROP_N  },
	{ 0x0000fb, WIDTHPROP_A  },
	{ 0x0000fc, WIDTHPROP_N  },
	{ 0x0000fd, WIDTHPROP_A  },
	{ 0x0000fe, WIDTHPROP_N  },
	{ 0x0000ff, WIDTHPROP_A  },
	{ 0x000101, WIDTHPROP_N  },
	{ 0x000102, WIDTHPROP_A  },
	{ 0x000111, WIDTHPROP_N  },
	{ 0x000112, WIDTHPROP_A  },
	{ 0x000113, WIDTHPROP_N  },
	{ 0x000114, WIDTHPROP_A  },
	{ 0x00011b, WIDTHPROP_N  },
	{ 0x00011c, WIDTHPROP_A  },
	{ 0x000126, WIDTHPROP_N  },
	{ 0x000128, WIDTHPROP_A  },
	{ 0x00012b, WIDTHPROP_N  },
	{ 0x00012c, WIDTHPROP_A  },
	{ 0x000131, WIDTHPROP_N  },
	{ 0x000134, WIDTHPROP_A  },
	{ 0x000138, WIDTHPROP_N  },
	{ 0x000139, WIDTHPROP_A  },
	{ 0x00013f, WIDTHPROP_N  },
	{ 0x000143, WIDTHPROP_A  },
	{ 0x000144, WIDTHPROP_N  },
	{ 0x000145, WIDTHPROP_A  },
	{ 0x000148, WIDTHPROP_N  },
	{ 0x00014c, WIDTHPROP_A  },
	{ 0x00014d, WIDTHPROP_N  },
	{ 0x00014e, WIDTHPROP_A  },
	{ 0x000152, WIDTHPROP_N  },
	{ 0x000154, WIDTHPROP_A  },
	{ 0x000166, WIDTHPROP_N  },
	{ 0x000168, WIDTHPROP_A  },
	{ 0x00016b, WIDTHPROP_N  },
	{ 0x00016c, WIDTHPROP_A  },
	{ 0x0001ce, WIDTHPROP_N  },
	{ 0x0001cf, WIDTHPROP_A  },
	{ 0x0001d0, WIDTHPROP_N  },
	{ 0x0001d1, WIDTHPROP_A  },
	{ 0x0001d2, WIDTHPROP_N  },
	{ 0x0001d3, WIDTHPROP_A  },
	{ 0x0001d4, WIDTHPROP_N  },
	{ 0x0001d5, WIDTHPROP_A  },
	{ 0x0001d6, WIDTHPROP_N  },
	{ 0x0001d7, WIDTHPROP_A  },
	{ 0x0001d8, WIDTHPROP_N  },
	{ 0x0001d9, WIDTHPROP_A  },
	{ 0x0001da, WIDTHPROP_N  },
	{ 0x0001db, WIDTHPROP_A  },
	{ 0x0001dc, WIDTHPROP_N  },
	{ 0x0001dd, WIDTHPROP_A  },
	{ 0x000251, WIDTHPROP_N  },
	{ 0x000252, WIDTHPROP_A  },
	{ 0x000261, WIDTHPROP_N  },
	{ 0x000262, WIDTHPROP_A  },
	{ 0x0002c4, WIDTHPROP_N  },
	{ 0x0002c5, WIDTHPROP_A  },
	{ 0x0002c7, WIDTHPROP_N  },
	{ 0x0002c8, WIDTHPROP_A  },
	{ 0x0002c9, WIDTHPROP_N  },
	{ 0x0002cc, WIDTHPROP_A  },
	{ 0x0002cd, WIDTHPROP_N  },
	{ 0x0002ce, WIDTHPROP_A  },
	{ 0x0002d0, WIDTHPROP_N  },
	{ 0x0002d1, WIDTHPROP_A  },
	{ 0x0002d8, WIDTHPROP_N  },
	{ 0x0002dc, WIDTHPROP_A  },
	{ 0x0002dd, WIDTHPROP_N  },
	{ 0x0002de, WIDTHPROP_A  },
	{ 0x0002df, WIDTHPROP_N  },
	{ 0x0002e0, WIDTHPROP_A  },
	{ 0x000300, WIDTHPROP_N  },
	{ 0x000370, WIDTHPROP_A  },
	{ 0x000391, WIDTHPROP_N  },
	{ 0x0003aa, WIDTHPROP_A  },
	{ 0x0003b1, WIDTHPROP_N  },
	{ 0x0003c2, WIDTHPROP_A  },
	{ 0x0003c3, WIDTHPROP_N  },
	{ 0x0003ca, WIDTHPROP_A  },
	{ 0x000401, WIDTHPROP_N  },
	{ 0x000402, WIDTHPROP_A  },
	{ 0x000410, WIDTHPROP_N  },
	{ 0x000450, WIDTHPROP_A  },
	{ 0x000451, WIDTHPROP_N  },
	{ 0x000452, WIDTHPROP_A  },
	{ 0x001100, WIDTHPROP_N  },
	{ 0x001160, WIDTHPROP_W  },
	{ 0x002010, WIDTHPROP_N  },
	{ 0x002011, WIDTHPROP_A  },
	{ 0x002013, WIDTHPROP_N  },
	{ 0x002017, WIDTHPROP_A  },
	{ 0x002018, WIDTHPROP_N  },
	{ 0x00201a, WIDTHPROP_A  },
	{ 0x00201c, WIDTHPROP_N  },
	{ 0x00201e, WIDTHPROP_A  },
	{ 0x002020, WIDTHPROP_N  },
	{ 0x002023, WIDTHPROP_A  },
	{ 0x002024, WIDTHPROP_N  },
	{ 0x002028, WIDTHPROP_A  },
	{ 0x002030, WIDTHPROP_N  },
	{ 0x002031, WIDTHPROP_A  },
	{ 0x002032, WIDTHPROP_N  },
	{ 0x002034, WIDTHPROP_A  },
	{ 0x002035, WIDTHPROP_N  },
	{ 0x002036, WIDTHPROP_A  },
	{ 0x00203b, WIDTHPROP_N  },
	{ 0x00203c, WIDTHPROP_A  },
	{ 0x00203e, WIDTHPROP_N  },
	{ 0x00203f, WIDTHPROP_A  },
	{ 0x002074, WIDTHPROP_N  },
	{ 0x002075, WIDTHPROP_A  },
	{ 0x00207f, WIDTHPROP_N  },
	{ 0x002080, WIDTHPROP_A  },
	{ 0x002081, WIDTHPROP_N  },
	{ 0x002085, WIDTHPROP_A  },
	{ 0x0020a9, WIDTHPROP_N  },
	{ 0x0020aa, WIDTHPROP_H  },
	{ 0x0020ac, WIDTHPROP_N  },
	{ 0x0020ad, WIDTHPROP_A  },
	{ 0x002103, WIDTHPROP_N  },
	{ 0x002104, WIDTHPROP_A  },
	{ 0x002105, WIDTHPROP_N  },
	{ 0x002106, WIDTHPROP_A  },
	{ 0x002109, WIDTHPROP_N  },
	{ 0x00210a, WIDTHPROP_A  },
	{ 0x002113, WIDTHPROP_N  },
	{ 0x002114, WIDTHPROP_A  },
	{ 0x002116, WIDTHPROP_N  },
	{ 0x002117, WIDTHPROP_A  },
	{ 0x002121, WIDTHPROP_N  },
	{ 0x002123, WIDTHPROP_A  },
	{ 0x002126, WIDTHPROP_N  },
	{ 0x002127, WIDTHPROP_A  },
	{ 0x00212b, WIDTHPROP_N  },
	{ 0x00212c, WIDTHPROP_A  },
	{ 0x002153, WIDTHPROP_N  },
	{ 0x002155, WIDTHPROP_A  },
	{ 0x00215b, WIDTHPROP_N  },
	{ 0x00215f, WIDTHPROP_A  },
	{ 0x002160, WIDTHPROP_N  },
	{ 0x00216c, WIDTHPROP_A  },
	{ 0x002170, WIDTHPROP_N  },
	{ 0x00217a, WIDTHPROP_A  },
	{ 0x002189, WIDTHPROP_N  },
	{ 0x00219a, WIDTHPROP_A  },
	{ 0x0021b8, WIDTHPROP_N  },
	{ 0x0021ba, WIDTHPROP_A  },
	{ 0x0021d2, WIDTHPROP_N  },
	{ 0x0021d3, WIDTHPROP_A  },
	{ 0x0021d4, WIDTHPROP_N  },
	{ 0x0021d5, WIDTHPROP_A  },
	{ 0x0021e7, WIDTHPROP_N  },
	{ 0x0021e8, WIDTHPROP_A  },
	{ 0x002200, WIDTHPROP_N  },
	{ 0x002201, WIDTHPROP_A  },
	{ 0x002202, WIDTHPROP_N  },
	{ 0x002204, WIDTHPROP_A  },
	{ 0x002207, WIDTHPROP_N  },
	{ 0x002209, WIDTHPROP_A  },
	{ 0x00220b, WIDTHPROP_N  },
	{ 0x00220c, WIDTHPROP_A  },
	{ 0x00220f, WIDTHPROP_N  },
	{ 0x002210, WIDTHPROP_A  },
	{ 0x002211, WIDTHPROP_N  },
	{ 0x002212, WIDTHPROP_A  },
	{ 0x002215, WIDTHPROP_N  },
	{ 0x002216, WIDTHPROP_A  },
	{ 0x00221a, WIDTHPROP_N  },
	{ 0x00221b, WIDTHPROP_A  },
	{ 0x00221d, WIDTHPROP_N  },
	{ 0x002221, WIDTHPROP_A  },
	{ 0x002223, WIDTHPROP_N  },
	{ 0x002224, WIDTHPROP_A  },
	{ 0x002225, WIDTHPROP_N  },
	{ 0x002226, WIDTHPROP_A  },
	{ 0x002227, WIDTHPROP_N  },
	{ 0x00222d, WIDTHPROP_A  },
	{ 0x00222e, WIDTHPROP_N  },
	{ 0x00222f, WIDTHPROP_A  },
	{ 0x002234, WIDTHPROP_N  },
	{ 0x002238, WIDTHPROP_A  },
	{ 0x00223c, WIDTHPROP_N  },
	{ 0x00223e, WIDTHPROP_A  },
	{ 0x002248, WIDTHPROP_N  },
	{ 0x002249, WIDTHPROP_A  },
	{ 0x00224c, WIDTHPROP_N  },
	{ 0x00224d, WIDTHPROP_A  },
	{ 0x002252, WIDTHPROP_N  },
	{ 0x002253, WIDTHPROP_A  },
	{ 0x002260, WIDTHPROP_N  },
	{ 0x002262, WIDTHPROP_A  },
	{ 0x002264, WIDTHPROP_N  },
	{ 0x002268, WIDTHPROP_A  },
	{ 0x00226a, WIDTHPROP_N  },
	{ 0x00226c, WIDTHPROP_A  },
	{ 0x00226e, WIDTHPROP_N  },
	{ 0x002270, WIDTHPROP_A  },
	{ 0x002282, WIDTHPROP_N  },
	{ 0x002284, WIDTHPROP_A  },
	{ 0x002286, WIDTHPROP_N  },
	{ 0x002288, WIDTHPROP_A  },
	{ 0x002295, WIDTHPROP_N  },
	{ 0x002296, WIDTHPROP_A  },
	{ 0x002299, WIDTHPROP_N  },
	{ 0x00229a, WIDTHPROP_A  },
	{ 0x0022a5, WIDTHPROP_N  },
	{ 0x0022a6, WIDTHPROP_A  },
	{ 0x0022bf, WIDTHPROP_N  },
	{ 0x0022c0, WIDTHPROP_A  },
	{ 0x002312, WIDTHPROP_N  },
	{ 0x002313, WIDTHPROP_A  },
	{ 0x002329, WIDTHPROP_N  },
	{ 0x00232b, WIDTHPROP_W  },
	{ 0x002460, WIDTHPROP_N  },
	{ 0x0024ea, WIDTHPROP_A  },
	{ 0x0024eb, WIDTHPROP_N  },
	{ 0x00254c, WIDTHPROP_A  },
	{ 0x002550, WIDTHPROP_N  },
	{ 0x002574, WIDTHPROP_A  },
	{ 0x002580, WIDTHPROP_N  },
	{ 0x002590, WIDTHPROP_A  },
	{ 0x002592, WIDTHPROP_N  },
	{ 0x002596, WIDTHPROP_A  },
	{ 0x0025a0, WIDTHPROP_N  },
	{ 0x0025a2, WIDTHPROP_A  },
	{ 0x0025a3, WIDTHPROP_N  },
	{ 0x0025aa, WIDTHPROP_A  },
	{ 0x0025b2, WIDTHPROP_N  },
	{ 0x0025b4, WIDTHPROP_A  },
	{ 0x0025b6, WIDTHPROP_N  },
	{ 0x0025b8, WIDTHPROP_A  },
	{ 0x0025bc, WIDTHPROP_N  },
	{ 0x0025be, WIDTHPROP_A  },
	{ 0x0025c0, WIDTHPROP_N  },
	{ 0x0025c2, WIDTHPROP_A  },
	{ 0x0025c6, WIDTHPROP_N  },
	{ 0x0025c9, WIDTHPROP_A  },
	{ 0x0025cb, WIDTHPROP_N  },
	{ 0x0025cc, WIDTHPROP_A  },
	{ 0x0025ce, WIDTHPROP_N  },
	{ 0x0025d2, WIDTHPROP_A  },
	{ 0x0025e2, WIDTHPROP_N  },
	{ 0x0025e6, WIDTHPROP_A  },
	{ 0x0025ef, WIDTHPROP_N  },
	{ 0x0025f0, WIDTHPROP_A  },
	{ 0x002605, WIDTHPROP_N  },
	{ 0x002607, WIDTHPROP_A  },
	{ 0x002609, WIDTHPROP_N  },
	{ 0x00260a, WIDTHPROP_A  },
	{ 0x00260e, WIDTHPROP_N  },
	{ 0x002610, WIDTHPROP_A  },
	{ 0x002614, WIDTHPROP_N  },
	{ 0x002616, WIDTHPROP_A  },
	{ 0x00261c, WIDTHPROP_N  },
	{ 0x00261d, WIDTHPROP_A  },
	{ 0x00261e, WIDTHPROP_N  },
	{ 0x00261f, WIDTHPROP_A  },
	{ 0x002640, WIDTHPROP_N  },
	{ 0x002641, WIDTHPROP_A  },
	{ 0x002642, WIDTHPROP_N  },
	{ 0x002643, WIDTHPROP_A  },
	{ 0x002660, WIDTHPROP_N  },
	{ 0x002662, WIDTHPROP_A  },
	{ 0x002663, WIDTHPROP_N  },
	{ 0x002666, WIDTHPROP_A  },
	{ 0x002667, WIDTHPROP_N  },
	{ 0x00266b, WIDTHPROP_A  },
	{ 0x00266c, WIDTHPROP_N  },
	{ 0x00266e, WIDTHPROP_A  },
	{ 0x00266f, WIDTHPROP_N  },
	{ 0x002670, WIDTHPROP_A  },
	{ 0x00269e, WIDTHPROP_N  },
	{ 0x0026a0, WIDTHPROP_A  },
	{ 0x0026be, WIDTHPROP_N  },
	{ 0x0026c0, WIDTHPROP_A  },
	{ 0x0026c4, WIDTHPROP_N  },
	{ 0x0026ce, WIDTHPROP_A  },
	{ 0x0026cf, WIDTHPROP_N  },
	{ 0x0026e2, WIDTHPROP_A  },
	{ 0x0026e3, WIDTHPROP_N  },
	{ 0x0026e4, WIDTHPROP_A  },
	{ 0x0026e8, WIDTHPROP_N  },
	{ 0x002700, WIDTHPROP_A  },
	{ 0x00273d, WIDTHPROP_N  },
	{ 0x00273e, WIDTHPROP_A  },
	{ 0x002757, WIDTHPROP_N  },
	{ 0x002758, WIDTHPROP_A  },
	{ 0x002776, WIDTHPROP_N  },
	{ 0x002780, WIDTHPROP_A  },
	{ 0x0027e6, WIDTHPROP_N  },
	{ 0x0027ee, WIDTHPROP_Na },
	{ 0x002985, WIDTHPROP_N  },
	{ 0x002987, WIDTHPROP_Na },
	{ 0x002b55, WIDTHPROP_N  },
	{ 0x002b5a, WIDTHPROP_A  },
	{ 0x002e80, WIDTHPROP_N  },
	{ 0x003000, WIDTHPROP_W  },
	{ 0x003001, WIDTHPROP_F  },
	{ 0x00303f, WIDTHPROP_W  },
	{ 0x003041, WIDTHPROP_N  },
	{ 0x003248, WIDTHPROP_W  },
	{ 0x003250, WIDTHPROP_A  },
	{ 0x004dc0, WIDTHPROP_W  },
	{ 0x004e00, WIDTHPROP_N  },
	{ 0x00a4d0, WIDTHPROP_W  },
	{ 0x00a960, WIDTHPROP_N  },
	{ 0x00a980, WIDTHPROP_W  },
	{ 0x00ac00, WIDTHPROP_N  },
	{ 0x00d7b0, WIDTHPROP_W  },
	{ 0x00e000, WIDTHPROP_N  },
	{ 0x00f900, WIDTHPROP_A  },
	{ 0x00fb00, WIDTHPROP_W  },
	{ 0x00fe00, WIDTHPROP_N  },
	{ 0x00fe10, WIDTHPROP_A  },
	{ 0x00fe20, WIDTHPROP_W  },
	{ 0x00fe30, WIDTHPROP_N  },
	{ 0x00fe70, WIDTHPROP_W  },
	{ 0x00ff01, WIDTHPROP_N  },
	{ 0x00ff61, WIDTHPROP_F  },
	{ 0x00ffe0, WIDTHPROP_H  },
	{ 0x00ffe8, WIDTHPROP_F  },
	{ 0x00fff9, WIDTHPROP_H  },
	{ 0x00fffd, WIDTHPROP_N  },
	{ 0x010000, WIDTHPROP_A  },
	{ 0x01b000, WIDTHPROP_N  },
	{ 0x01bc00, WIDTHPROP_W  },
	{ 0x01f100, WIDTHPROP_N  },
	{ 0x01f10b, WIDTHPROP_A  },
	{ 0x01f110, WIDTHPROP_N  },
	{ 0x01f12e, WIDTHPROP_A  },
	{ 0x01f130, WIDTHPROP_N  },
	{ 0x01f16a, WIDTHPROP_A  },
	{ 0x01f170, WIDTHPROP_N  },
	{ 0x01f1e6, WIDTHPROP_A  },
	{ 0x01f200, WIDTHPROP_N  },
	{ 0x01f300, WIDTHPROP_W  },
	{ 0x020000, WIDTHPROP_N  },
	{ 0x0e0001, WIDTHPROP_W  },
	{ 0x0e0100, WIDTHPROP_N  },
	{ 0x10fffe, WIDTHPROP_A  },
	{ 0x000000, WIDTHPROP_N  },
};

}