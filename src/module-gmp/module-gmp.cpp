//=============================================================================
// Gura module: gmp
//=============================================================================
#include "stdafx.h"

Gura_BeginModuleBody(gmp)

//-----------------------------------------------------------------------------
// Module functions
//-----------------------------------------------------------------------------
// gmp.gcd(num1:gmp.mpz, num2:gmp.mpz)
Gura_DeclareFunction(gcd)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "num1", VTYPE_mpz);
	DeclareArg(env, "num2", VTYPE_mpz);
	AddHelp(Gura_Symbol(en), Help::FMT_markdown,
	""
	);
}

Gura_ImplementFunction(gcd)
{
	const mpz_class &num1 = Object_mpz::GetEntity(args, 0);
	const mpz_class &num2 = Object_mpz::GetEntity(args, 1);
	mpz_t num;
	::mpz_init(num);
	::mpz_gcd(num, num1.get_mpz_t(), num2.get_mpz_t());
	return Value(new Object_mpz(num));
}

// gmp.lcm(num1:gmp.mpz, num2:gmp.mpz)
Gura_DeclareFunction(lcm)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "num1", VTYPE_mpz);
	DeclareArg(env, "num2", VTYPE_mpz);
	AddHelp(Gura_Symbol(en), Help::FMT_markdown,
	""
	);
}

Gura_ImplementFunction(lcm)
{
	const mpz_class &num1 = Object_mpz::GetEntity(args, 0);
	const mpz_class &num2 = Object_mpz::GetEntity(args, 1);
	mpz_t num;
	::mpz_init(num);
	::mpz_lcm(num, num1.get_mpz_t(), num2.get_mpz_t());
	return Value(new Object_mpz(num));
}

// gmp.sqrt(num)
Gura_DeclareFunction(sqrt)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "num", VTYPE_any);
	AddHelp(Gura_Symbol(en), Help::FMT_markdown,
	""
	);
}

Gura_ImplementFunction(sqrt)
{
	if (args.IsType(0, VTYPE_mpz)) {
		const mpz_class &num = Object_mpz::GetEntity(args, 0);
		mpz_class result = ::sqrt(num);
		return Value(new Object_mpz(result.get_mpz_t()));
	} else if (args.IsType(0, VTYPE_mpf)) {
		const mpf_class &num = Object_mpf::GetEntity(args, 0);
		mpf_class result = ::sqrt(num);
		return Value(new Object_mpf(result.get_mpf_t()));
	}
	
	
	
	return Value::Null;
}

//-----------------------------------------------------------------------------
// Suffix handlers
//-----------------------------------------------------------------------------
Gura_ImplementSuffixMgrForNumber(L)
{
	if (::strchr(body, '.') != NULL || ::strchr(body, 'e') != NULL || ::strchr(body, 'E') != NULL) {
		mpf_t numf;
		::mpf_init(numf);
		if (::mpf_set_str(numf, body, 0) == 0) return Value(new Object_mpf(numf));
		::mpf_clear(numf);
	} else {
		mpz_t numz;
		::mpz_init(numz);
		if (::mpz_set_str(numz, body, 0) == 0) return Value(new Object_mpz(numz));
		::mpz_clear(numz);
	}
	sig.SetError(ERR_ValueError, "invalid string format for gmp number");
	return false;
}

Gura_ImplementSuffixMgrForNumber(Lr)
{
	mpq_t numq;
	::mpq_init(numq);
	if (::mpq_set_str(numq, body, 0) == 0) return Value(new Object_mpq(numq));
	::mpq_clear(numq);
	sig.SetError(ERR_ValueError, "invalid string format for gmp number");
	return false;
}

//-----------------------------------------------------------------------------
// Module entry
//-----------------------------------------------------------------------------
Gura_ModuleEntry()
{
	// realization of classes
	Gura_RealizeUserClass(mpz, env.LookupClass(VTYPE_object));
	Gura_RealizeUserClass(mpq, env.LookupClass(VTYPE_object));
	Gura_RealizeUserClass(mpf, env.LookupClass(VTYPE_object));
	// assignment of functions
	Gura_AssignFunction(gcd);
	Gura_AssignFunction(lcm);
	Gura_AssignFunction(sqrt);
	// assignment of operators
	AssignOperators(env);
	// assignment of suffix managers
	Gura_AssignSuffixMgrForNumber(L);
	Gura_AssignSuffixMgrForNumber(Lr);
}

Gura_ModuleTerminate()
{
}

//-----------------------------------------------------------------------------
// utility functions
//-----------------------------------------------------------------------------
String ComposeFormat(const Formatter::Flags &flags, char *qualifier)
{
	String fmt = "%";
	if (flags.leftAlignFlag) fmt += "-";
	if (flags.sharpFlag) fmt += "#";
	if (flags.charPadding == '0') fmt += '0';
	if (flags.plusMode == Formatter::PLUSMODE_Space) {
		fmt += " ";
	} else if (flags.plusMode == Formatter::PLUSMODE_Plus) {
		fmt += "+";
	}
	if (flags.fieldMinWidth > 0) {
		char buff[64];
		::sprintf(buff, "%d", flags.fieldMinWidth);
		fmt += buff;
	}
	if (flags.precision >= 0) {
		char buff[64];
		::sprintf(buff, ".%d", flags.precision);
		fmt += buff;
	}
	fmt += qualifier;
	return fmt;
}

mpq_class MpqFromRational(const Rational &ratio)
{
	mpq_t num;
	::mpq_init(num);
	::mpz_set_si(mpq_numref(num), ratio.numer);
	::mpz_set_si(mpq_denref(num), ratio.denom);
	return mpq_class(num);
}

bool _Format_d(Signal sig, Formatter *pFormatter,
					const Formatter::Flags &flags, const mpz_class &num)
{
	char *str = NULL;
	::gmp_asprintf(&str, ComposeFormat(flags, "Zd").c_str(), num.get_mpz_t());
	bool rtn = pFormatter->PutString(sig, str);
	::free(str);
	return rtn;
}

bool _Format_u(Signal sig, Formatter *pFormatter,
					const Formatter::Flags &flags, const mpz_class &num)
{
	char *str = NULL;
	::gmp_asprintf(&str, ComposeFormat(flags, "Zu").c_str(), num.get_mpz_t());
	bool rtn = pFormatter->PutString(sig, str);
	::free(str);
	return rtn;
}

bool _Format_b(Signal sig, Formatter *pFormatter,
					const Formatter::Flags &flags, const mpz_class &num)
{
	char *str = NULL;
	::gmp_asprintf(&str, ComposeFormat(flags, "Zb").c_str(), num.get_mpz_t());
	bool rtn = pFormatter->PutString(sig, str);
	::free(str);
	return rtn;
}

bool _Format_o(Signal sig, Formatter *pFormatter,
					const Formatter::Flags &flags, const mpz_class &num)
{
	char *str = NULL;
	::gmp_asprintf(&str, ComposeFormat(flags, "Zo").c_str(), num.get_mpz_t());
	bool rtn = pFormatter->PutString(sig, str);
	::free(str);
	return rtn;
}

bool _Format_x(Signal sig, Formatter *pFormatter,
					const Formatter::Flags &flags, const mpz_class &num)
{
	char *str = NULL;
	::gmp_asprintf(&str, ComposeFormat(flags,
				flags.upperCaseFlag? "ZX" : "Zx").c_str(), num.get_mpz_t());
	bool rtn = pFormatter->PutString(sig, str);
	::free(str);
	return rtn;
}

bool _Format_e(Signal sig, Formatter *pFormatter,
					const Formatter::Flags &flags, const mpf_class &num)
{
	char *str = NULL;
	::gmp_asprintf(&str, ComposeFormat(flags,
				flags.upperCaseFlag? "Fe" : "FE").c_str(), num.get_mpf_t());
	bool rtn = pFormatter->PutString(sig, str);
	::free(str);
	return rtn;
}

bool _Format_f(Signal sig, Formatter *pFormatter,
					const Formatter::Flags &flags, const mpf_class &num)
{
	char *str = NULL;
	::gmp_asprintf(&str, ComposeFormat(flags, "Ff").c_str(), num.get_mpf_t());
	bool rtn = pFormatter->PutString(sig, str);
	::free(str);
	return rtn;
}

bool _Format_g(Signal sig, Formatter *pFormatter,
					const Formatter::Flags &flags, const mpf_class &num)
{
	char *str = NULL;
	::gmp_asprintf(&str, ComposeFormat(flags,
				flags.upperCaseFlag? "Fg" : "FG").c_str(), num.get_mpf_t());
	bool rtn = pFormatter->PutString(sig, str);
	::free(str);
	return rtn;
}

bool _Format_d(Signal sig, Formatter *pFormatter,
					const Formatter::Flags &flags, const mpq_class &num)
{
	char *str = NULL;
	::gmp_asprintf(&str, ComposeFormat(flags, "Qd").c_str(), num.get_mpq_t());
	bool rtn = pFormatter->PutString(sig, str);
	::free(str);
	return rtn;
}

bool _Format_b(Signal sig, Formatter *pFormatter,
					const Formatter::Flags &flags, const mpq_class &num)
{
	char *str = NULL;
	::gmp_asprintf(&str, ComposeFormat(flags, "Qb").c_str(), num.get_mpq_t());
	bool rtn = pFormatter->PutString(sig, str);
	::free(str);
	return rtn;
}

bool _Format_o(Signal sig, Formatter *pFormatter,
					const Formatter::Flags &flags, const mpq_class &num)
{
	char *str = NULL;
	::gmp_asprintf(&str, ComposeFormat(flags, "Qo").c_str(), num.get_mpq_t());
	bool rtn = pFormatter->PutString(sig, str);
	::free(str);
	return rtn;
}

bool _Format_x(Signal sig, Formatter *pFormatter,
					const Formatter::Flags &flags, const mpq_class &num)
{
	char *str = NULL;
	::gmp_asprintf(&str, ComposeFormat(flags,
				flags.upperCaseFlag? "QX" : "Qx").c_str(), num.get_mpq_t());
	bool rtn = pFormatter->PutString(sig, str);
	::free(str);
	return rtn;
}

Gura_EndModuleBody(gmp, gmp)

Gura_RegisterModule(gmp)
