//=============================================================================
// OperatorBasic
//=============================================================================
#include "stdafx.h"
#include <math.h>

namespace Gura {

//-----------------------------------------------------------------------------
// [+A] ... UnaryOperator(Pos, A)
//-----------------------------------------------------------------------------
Gura_ImplementUnaryOperator(Pos, number)
{
	return value;
}

Gura_ImplementUnaryOperator(Pos, complex)
{
	return value;
}

Gura_ImplementUnaryOperator(Pos, rational)
{
	Signal &sig = env.GetSignal();
	const Rational &a = value.GetRational();
	if (a.denom == 0) {
		Rational::SetError_DenominatorZero(sig);
		return Value::Nil;
	}
	if (a.numer == 0) return Value::Zero;
	return Value(+a);
}

Gura_ImplementUnaryOperator(Pos, matrix)
{
	return value;
}

Gura_ImplementUnaryOperator(Pos, timedelta)
{
	return value;
}

Gura_ImplementUnaryOperator(Pos, array)
{
	return Array::ApplyUnaryFunc(env, Array::unaryFuncPack_Pos, value);
}

//-----------------------------------------------------------------------------
// [-A] ... UnaryOperator(Neg, A)
//-----------------------------------------------------------------------------
Gura_ImplementUnaryOperator(Neg, number)
{
	return Value(-value.GetNumber());
}

Gura_ImplementUnaryOperator(Neg, complex)
{
	return Value(-value.GetComplex());
}

Gura_ImplementUnaryOperator(Neg, rational)
{
	Signal &sig = env.GetSignal();
	const Rational &a = value.GetRational();
	if (a.denom == 0) {
		Rational::SetError_DenominatorZero(sig);
		return Value::Nil;
	}
	if (a.numer == 0) return Value::Zero;
	return Value(-a);
}

Gura_ImplementUnaryOperator(Neg, matrix)
{
	return Matrix::Neg(env, Object_matrix::GetObject(value)->GetMatrix());
}

Gura_ImplementUnaryOperator(Neg, timedelta)
{
	TimeDelta td = Object_timedelta::GetObject(value)->GetTimeDelta();
	return Value(new Object_timedelta(env, TimeDelta(-td.GetDays(), -td.GetSecsRaw(), -td.GetUSecs())));
}

Gura_ImplementUnaryOperator(Neg, vertex)
{
	const Vertex &vertex = Object_vertex::GetObject(value)->GetVertex();
	return Value(new Object_vertex(env, Vertex(-vertex.x, -vertex.y, -vertex.z)));
}

Gura_ImplementUnaryOperator(Neg, array)
{
	return Array::ApplyUnaryFunc(env, Array::unaryFuncPack_Neg, value);
}

//-----------------------------------------------------------------------------
// [~A] ... UnaryOperator(Invert, A)
//-----------------------------------------------------------------------------
Gura_ImplementUnaryOperator(Inv, number)
{
	ULong num = ~static_cast<ULong>(value.GetNumber());
	return Value(static_cast<Number>(num));
}

//-----------------------------------------------------------------------------
// [!A] ... UnaryOperator(Not, A)
//-----------------------------------------------------------------------------
Gura_ImplementUnaryOperator(Not, any)
{
	bool rtn = !value.GetBoolean();
	return Value(rtn);
}

//-----------------------------------------------------------------------------
// [A..] ... UnaryOperator(SeqInf, A)
//-----------------------------------------------------------------------------
Gura_ImplementUnaryOperatorSuffix(SeqInf, number)
{
	Number numBegin = value.GetNumber();
	return Value(new Object_iterator(env, new Iterator_SequenceInf(numBegin)));
}

//-----------------------------------------------------------------------------
// [A?] ... UnaryOperator(Question, A)
//-----------------------------------------------------------------------------
Gura_ImplementUnaryOperatorSuffix(Question, any)
{
	bool rtn = value.GetBoolean();
	return Value(rtn);
}

//-----------------------------------------------------------------------------
// [A*] ... UnaryOperator(Each, A)
//-----------------------------------------------------------------------------
Gura_ImplementUnaryOperatorSuffix(Each, any)
{
	Signal &sig = env.GetSignal();
	AutoPtr<Iterator> pIterator(value.CreateIterator(sig));
	if (pIterator.IsNull()) return Value::Nil;
	return Value(new Object_iterator(env, pIterator.release()));
}

//-----------------------------------------------------------------------------
// [A+] ... UnaryOperator(PostPos, A)
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// [A%] ... UnaryOperator(PostMod, A)
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// [A + B] ... BinaryOperator(Add, A, B)
//-----------------------------------------------------------------------------
Gura_ImplementBinaryOperator(Add, number, number)
{
	return Value(valueLeft.GetNumber() + valueRight.GetNumber());
}

Gura_ImplementBinaryOperator(Add, boolean, boolean)
{
	return Value(valueLeft.GetNumber() + valueRight.GetNumber());
}

Gura_ImplementBinaryOperator(Add, number, boolean)
{
	return Value(valueLeft.GetNumber() + valueRight.GetNumber());
}

Gura_ImplementBinaryOperator(Add, boolean, number)
{
	return Value(valueLeft.GetNumber() + valueRight.GetNumber());
}

Gura_ImplementBinaryOperator(Add, complex, complex)
{
	return Value(valueLeft.GetComplex() + valueRight.GetComplex());
}

Gura_ImplementBinaryOperator(Add, rational, rational)
{
	Signal &sig = env.GetSignal();
	const Rational &a = valueLeft.GetRational();
	const Rational &b = valueRight.GetRational();
	if (a.denom == 0 || b.denom == 0) {
		Rational::SetError_DenominatorZero(sig);
		return Value::Nil;
	}
	Rational c = a + b;
	if (c.numer == 0) return Value::Zero;
	return Value(c);
}

Gura_ImplementBinaryOperator(Add, rational, number)
{
	Signal &sig = env.GetSignal();
	const Rational &a = valueLeft.GetRational();
	const Rational b = Rational::FromNumber(valueRight.GetNumber());
	if (a.denom == 0 || b.denom == 0) {
		Rational::SetError_DenominatorZero(sig);
		return Value::Nil;
	}
	Rational c = a + b;
	if (c.numer == 0) return Value::Zero;
	return Value(c);
}

Gura_ImplementBinaryOperator(Add, number, rational)
{
	Signal &sig = env.GetSignal();
	const Rational a = Rational::FromNumber(valueLeft.GetNumber());
	const Rational &b = valueRight.GetRational();
	if (a.denom == 0 || b.denom == 0) {
		Rational::SetError_DenominatorZero(sig);
		return Value::Nil;
	}
	Rational c = a + b;
	if (c.numer == 0) return Value::Zero;
	return Value(c);
}

Gura_ImplementBinaryOperator(Add, number, complex)
{
	return Value(valueLeft.GetNumber() + valueRight.GetComplex());
}

Gura_ImplementBinaryOperator(Add, complex, number)
{
	return Value(valueLeft.GetComplex() + valueRight.GetNumber());
}

Gura_ImplementBinaryOperator(Add, matrix, matrix)
{
	return Matrix::AddSub(env, OPTYPE_Add,
		Object_matrix::GetObject(valueLeft)->GetMatrix(), Object_matrix::GetObject(valueRight)->GetMatrix());
}

Gura_ImplementBinaryOperator(Add, datetime, timedelta)
{
	DateTime dateTime = Object_datetime::GetObject(valueLeft)->GetDateTime();
	const TimeDelta &timeDelta = Object_timedelta::GetObject(valueRight)->GetTimeDelta();
	dateTime.Plus(timeDelta);
	return Value(new Object_datetime(env, dateTime));
}

Gura_ImplementBinaryOperator(Add, timedelta, datetime)
{
	const TimeDelta &timeDelta = Object_timedelta::GetObject(valueLeft)->GetTimeDelta();
	DateTime dateTime = Object_datetime::GetObject(valueRight)->GetDateTime();
	dateTime.Plus(timeDelta);
	return Value(new Object_datetime(env, dateTime));
}

Gura_ImplementBinaryOperator(Add, timedelta, timedelta)
{
	TimeDelta td1 = Object_timedelta::GetObject(valueLeft)->GetTimeDelta();
	TimeDelta td2 = Object_timedelta::GetObject(valueRight)->GetTimeDelta();
	return Value(new Object_timedelta(env, TimeDelta(
			td1.GetDays() + td2.GetDays(),
			td1.GetSecsRaw() + td2.GetSecsRaw(),
			td1.GetUSecs() + td2.GetUSecs())));
}

Gura_ImplementBinaryOperator(Add, string, string)
{
	String str(valueLeft.GetString());
	str += valueRight.GetString();
	return Value(str);
}

Gura_ImplementBinaryOperator(Add, binary, binary)
{
	Binary buff(valueLeft.GetBinary());
	buff += valueRight.GetBinary();
	return Value(new Object_binary(env, buff, true));
}

Gura_ImplementBinaryOperator(Add, binary, string)
{
	Binary buff(valueLeft.GetBinary());
	buff += valueRight.GetString();
	return Value(new Object_binary(env, buff, true));
}

Gura_ImplementBinaryOperator(Add, string, binary)
{
	Binary buff;
	buff += valueLeft.GetString();
	buff += valueRight.GetBinary();
	return Value(new Object_binary(env, buff, true));
}

Gura_ImplementBinaryOperator(Add, pointer, number)
{
	AutoPtr<Object_pointer> pObj(dynamic_cast<Object_pointer *>(
						Object_pointer::GetObject(valueLeft)->Clone()));
	if (!pObj->GetPointer()->Advance(env, valueRight.GetInt())) return Value::Nil;
	return Value(pObj.release());
}

Gura_ImplementBinaryOperator(Add, string, any)
{
	String str(valueLeft.GetString());
	str += valueRight.ToString();
	return Value(str);
}

Gura_ImplementBinaryOperator(Add, any, string)
{
	String str(valueLeft.ToString());
	str += valueRight.GetString();
	return Value(str);
}

Gura_ImplementBinaryOperator(Add, vertex, vertex)
{
	const Vertex &vertexL = Object_vertex::GetObject(valueLeft)->GetVertex();
	const Vertex &vertexR = Object_vertex::GetObject(valueRight)->GetVertex();
	return Value(new Object_vertex(env, Vertex(
									   vertexL.x + vertexR.x,
									   vertexL.y + vertexR.y,
									   vertexL.z + vertexR.z)));
}

Gura_ImplementBinaryOperator(Add, array, array)
{
	return Array::ApplyBinaryFunc_array_array(
		env, Array::binaryFuncPack_Add, valueLeft, valueRight);
}

Gura_ImplementBinaryOperator(Add, array, number)
{
	return Array::ApplyBinaryFunc_array_number(
		env, Array::binaryFuncPack_Add, valueLeft, valueRight);
}

Gura_ImplementBinaryOperator(Add, number, array)
{
	return Array::ApplyBinaryFunc_number_array(
		env, Array::binaryFuncPack_Add, valueLeft, valueRight);
}

//-----------------------------------------------------------------------------
// [A - B] ... BinaryOperator(Sub, A, B)
//-----------------------------------------------------------------------------
Gura_ImplementBinaryOperator(Sub, number, number)
{
	return Value(valueLeft.GetNumber() - valueRight.GetNumber());
}

Gura_ImplementBinaryOperator(Sub, boolean, boolean)
{
	return Value(valueLeft.GetNumber() - valueRight.GetNumber());
}

Gura_ImplementBinaryOperator(Sub, number, boolean)
{
	return Value(valueLeft.GetNumber() - valueRight.GetNumber());
}

Gura_ImplementBinaryOperator(Sub, boolean, number)
{
	return Value(valueLeft.GetNumber() - valueRight.GetNumber());
}

Gura_ImplementBinaryOperator(Sub, complex, complex)
{
	return Value(valueLeft.GetComplex() - valueRight.GetComplex());
}

Gura_ImplementBinaryOperator(Sub, rational, rational)
{
	Signal &sig = env.GetSignal();
	const Rational &a = valueLeft.GetRational();
	const Rational &b = valueRight.GetRational();
	if (a.denom == 0 || b.denom == 0) {
		Rational::SetError_DenominatorZero(sig);
		return Value::Nil;
	}
	Rational c = a - b;
	if (c.numer == 0) return Value::Zero;
	return Value(c);
}

Gura_ImplementBinaryOperator(Sub, rational, number)
{
	Signal &sig = env.GetSignal();
	const Rational &a = valueLeft.GetRational();
	const Rational b = Rational::FromNumber(valueRight.GetNumber());
	if (a.denom == 0 || b.denom == 0) {
		Rational::SetError_DenominatorZero(sig);
		return Value::Nil;
	}
	Rational c = a - b;
	if (c.numer == 0) return Value::Zero;
	return Value(c);
}

Gura_ImplementBinaryOperator(Sub, number, rational)
{
	Signal &sig = env.GetSignal();
	const Rational a = Rational::FromNumber(valueLeft.GetNumber());
	const Rational &b = valueRight.GetRational();
	if (a.denom == 0 || b.denom == 0) {
		Rational::SetError_DenominatorZero(sig);
		return Value::Nil;
	}
	Rational c = a - b;
	if (c.numer == 0) return Value::Zero;
	return Value(c);
}

Gura_ImplementBinaryOperator(Sub, number, complex)
{
	return Value(valueLeft.GetNumber() - valueRight.GetComplex());
}

Gura_ImplementBinaryOperator(Sub, complex, number)
{
	return Value(valueLeft.GetComplex() - valueRight.GetNumber());
}

Gura_ImplementBinaryOperator(Sub, matrix, matrix)
{
	return Matrix::AddSub(env, OPTYPE_Sub,
			Object_matrix::GetObject(valueLeft)->GetMatrix(), Object_matrix::GetObject(valueRight)->GetMatrix());
}

Gura_ImplementBinaryOperator(Sub, datetime, timedelta)
{
	DateTime dateTime = Object_datetime::GetObject(valueLeft)->GetDateTime();
	dateTime.Minus(Object_timedelta::GetObject(valueRight)->GetTimeDelta());
	return Value(new Object_datetime(env, dateTime));
}

Gura_ImplementBinaryOperator(Sub, datetime, datetime)
{
	Signal &sig = env.GetSignal();
	const DateTime &dt1 = Object_datetime::GetObject(valueLeft)->GetDateTime();
	const DateTime &dt2 = Object_datetime::GetObject(valueRight)->GetDateTime();
	if ((dt1.HasTZOffset() && !dt2.HasTZOffset()) ||
								(!dt1.HasTZOffset() && dt2.HasTZOffset())) {
		sig.SetError(ERR_ValueError, "failed to calculate datetime difference");
		return Value::Nil;
	}
	return Value(new Object_timedelta(env, dt1.Minus(dt2)));
}

Gura_ImplementBinaryOperator(Sub, timedelta, timedelta)
{
	TimeDelta td1 = Object_timedelta::GetObject(valueLeft)->GetTimeDelta();
	TimeDelta td2 = Object_timedelta::GetObject(valueRight)->GetTimeDelta();
	return Value(new Object_timedelta(env, TimeDelta(
			td1.GetDays() - td2.GetDays(),
			td1.GetSecsRaw() - td2.GetSecsRaw(),
			td1.GetUSecs() - td2.GetUSecs())));
}

Gura_ImplementBinaryOperator(Sub, color, color)
{
	const Color &color1 = Object_color::GetObject(valueLeft)->GetColor();
	const Color &color2 = Object_color::GetObject(valueRight)->GetColor();
	return Value(::sqrt(static_cast<double>(color1.CalcDistSqu(color2))));
}

Gura_ImplementBinaryOperator(Sub, pointer, number)
{
	AutoPtr<Object_pointer> pObj(dynamic_cast<Object_pointer *>(
						Object_pointer::GetObject(valueLeft)->Clone()));
	if (!pObj->GetPointer()->Advance(env, -valueRight.GetInt())) return Value::Nil;
	return Value(pObj.release());
}

Gura_ImplementBinaryOperator(Sub, pointer, pointer)
{
	const Pointer *pPtr1 = Object_pointer::GetObject(valueLeft)->GetPointer();
	const Pointer *pPtr2 = Object_pointer::GetObject(valueRight)->GetPointer();
	if (pPtr1->GetTarget() != pPtr2->GetTarget()) {
		env.SetError(ERR_ValueError,
			"cannot calculate difference between pointers of different binaries");
		return Value::Nil;
	}
	int offset1 = static_cast<int>(pPtr1->GetOffset());
	int offset2 = static_cast<int>(pPtr2->GetOffset());
	return Value(static_cast<Number>(offset1 - offset2));
}

Gura_ImplementBinaryOperator(Sub, vertex, vertex)
{
	const Vertex &vertexL = Object_vertex::GetObject(valueLeft)->GetVertex();
	const Vertex &vertexR = Object_vertex::GetObject(valueRight)->GetVertex();
	return Value(new Object_vertex(env, Vertex(
									   vertexL.x - vertexR.x,
									   vertexL.y - vertexR.y,
									   vertexL.z - vertexR.z)));
}

Gura_ImplementBinaryOperator(Sub, array, array)
{
	return Array::ApplyBinaryFunc_array_array(
		env, Array::binaryFuncPack_Sub, valueLeft, valueRight);
}

Gura_ImplementBinaryOperator(Sub, array, number)
{
	return Array::ApplyBinaryFunc_array_number(
		env, Array::binaryFuncPack_Sub, valueLeft, valueRight);
}

Gura_ImplementBinaryOperator(Sub, number, array)
{
	return Array::ApplyBinaryFunc_number_array(
		env, Array::binaryFuncPack_Sub, valueLeft, valueRight);
}

//-----------------------------------------------------------------------------
// [A * B] ... BinaryOperator(Mul, A, B)
//-----------------------------------------------------------------------------
Gura_ImplementBinaryOperator(Mul, number, number)
{
	return Value(valueLeft.GetNumber() * valueRight.GetNumber());
}

Gura_ImplementBinaryOperator(Mul, boolean, boolean)
{
	return Value(valueLeft.GetNumber() * valueRight.GetNumber());
}

Gura_ImplementBinaryOperator(Mul, number, boolean)
{
	return Value(valueLeft.GetNumber() * valueRight.GetNumber());
}

Gura_ImplementBinaryOperator(Mul, boolean, number)
{
	return Value(valueLeft.GetNumber() * valueRight.GetNumber());
}

Gura_ImplementBinaryOperator(Mul, complex, complex)
{
	return Value(valueLeft.GetComplex() * valueRight.GetComplex());
}

Gura_ImplementBinaryOperator(Mul, rational, rational)
{
	Signal &sig = env.GetSignal();
	const Rational &a = valueLeft.GetRational();
	const Rational &b = valueRight.GetRational();
	if (a.denom == 0 || b.denom == 0) {
		Rational::SetError_DenominatorZero(sig);
		return Value::Nil;
	}
	Rational c = a * b;
	if (c.numer == 0) return Value::Zero;
	return Value(c);
}

Gura_ImplementBinaryOperator(Mul, rational, number)
{
	Signal &sig = env.GetSignal();
	const Rational &a = valueLeft.GetRational();
	const Rational b = Rational::FromNumber(valueRight.GetNumber());
	if (a.denom == 0 || b.denom == 0) {
		Rational::SetError_DenominatorZero(sig);
		return Value::Nil;
	}
	Rational c = a * b;
	if (c.numer == 0) return Value::Zero;
	return Value(c);
}

Gura_ImplementBinaryOperator(Mul, number, rational)
{
	Signal &sig = env.GetSignal();
	const Rational a = Rational::FromNumber(valueLeft.GetNumber());
	const Rational &b = valueRight.GetRational();
	if (a.denom == 0 || b.denom == 0) {
		Rational::SetError_DenominatorZero(sig);
		return Value::Nil;
	}
	Rational c = a * b;
	if (c.numer == 0) return Value::Zero;
	return Value(c);
}

Gura_ImplementBinaryOperator(Mul, number, complex)
{
	return Value(valueLeft.GetNumber() * valueRight.GetComplex());
}

Gura_ImplementBinaryOperator(Mul, complex, number)
{
	return Value(valueLeft.GetComplex() * valueRight.GetNumber());
}

#if 0
Gura_ImplementBinaryOperator(Mul, matrix, matrix)
{
	return Matrix::Mul(env,
			Object_matrix::GetObject(valueLeft)->GetMatrix(), Object_matrix::GetObject(valueRight)->GetMatrix());
}

Gura_ImplementBinaryOperator(Mul, list, matrix)
{
	return Matrix::Mul(env,
			valueLeft.GetList(), Object_matrix::GetObject(valueRight)->GetMatrix());
}

Gura_ImplementBinaryOperator(Mul, matrix, list)
{
	return Matrix::Mul(env,
			Object_matrix::GetObject(valueLeft)->GetMatrix(), valueRight.GetList());
}
#endif

Gura_ImplementBinaryOperator(Mul, any, matrix)
{
	return Matrix::Mul(env,
			valueLeft, Object_matrix::GetObject(valueRight)->GetMatrix());
}

Gura_ImplementBinaryOperator(Mul, matrix, any)
{
	return Matrix::Mul(env,
			Object_matrix::GetObject(valueLeft)->GetMatrix(), valueRight);
}

Gura_ImplementBinaryOperator(Mul, timedelta, number)
{
	const TimeDelta &td = Object_timedelta::GetObject(valueLeft)->GetTimeDelta();
	long num = valueRight.GetLong();
	return Value(new Object_timedelta(env,
		TimeDelta(td.GetDays() * num, td.GetSecsRaw() * num, td.GetUSecs() * num)));
}

Gura_ImplementBinaryOperator(Mul, number, timedelta)
{
	const TimeDelta &td = Object_timedelta::GetObject(valueRight)->GetTimeDelta();
	long num = valueLeft.GetLong();
	return Value(new Object_timedelta(env,
		TimeDelta(td.GetDays() * num, td.GetSecsRaw() * num, td.GetUSecs() * num)));
}

Gura_ImplementBinaryOperator(Mul, function, any)
{
	Signal &sig = env.GetSignal();
	const Object_function *pObj = Object_function::GetObject(valueLeft);
	Value result = pObj->Eval(env, valueRight);
	if (sig.IsSignalled()) return Value::Nil;
	return result;
}

Gura_ImplementBinaryOperator(Mul, Class, any)
{
	const Class *pClass = valueLeft.GetClassItself();
	const Function *pConstructor = pClass->GetConstructor();
	if (pConstructor == nullptr) {
		pClass->SetError_NoConstructor();
		return Value::Nil;
	}
	AutoPtr<Argument> pArg(new Argument(pConstructor));
	if (pArg->StoreValue(env, valueRight) && pArg->Complete(env)) {
		return pConstructor->Eval(env, *pArg);
	}
	return Value::Nil;
}

Gura_ImplementBinaryOperator(Mul, string, number)
{
	String str;
	for (int cnt = static_cast<int>(valueRight.GetNumber()); cnt > 0; cnt--) {
		str += valueLeft.GetString();
	}
	return Value(str);
}

Gura_ImplementBinaryOperator(Mul, number, string)
{
	String str;
	for (int cnt = static_cast<int>(valueLeft.GetNumber()); cnt > 0; cnt--) {
		str += valueRight.GetString();
	}
	return Value(str);
}

Gura_ImplementBinaryOperator(Mul, binary, number)
{
	Binary buff;
	for (int cnt = static_cast<int>(valueRight.GetNumber()); cnt > 0; cnt--) {
		buff += valueLeft.GetBinary();
	}
	return Value(new Object_binary(env, buff, true));
}

Gura_ImplementBinaryOperator(Mul, number, binary)
{
	Binary buff;
	for (int cnt = static_cast<int>(valueLeft.GetNumber()); cnt > 0; cnt--) {
		buff += valueRight.GetBinary();
	}
	return Value(new Object_binary(env, buff, true));
}

Gura_ImplementBinaryOperator(Mul, vertex, number)
{
	const Vertex &vertex = Object_vertex::GetObject(valueLeft)->GetVertex();
	double num = valueRight.GetDouble();
	return Value(new Object_vertex(env, Vertex(
									   vertex.x * num,
									   vertex.y * num,
									   vertex.z * num)));
}

Gura_ImplementBinaryOperator(Mul, array, array)
{
	return Array::ApplyBinaryFunc_array_array(
		env, Array::binaryFuncPack_Mul, valueLeft, valueRight);
}

Gura_ImplementBinaryOperator(Mul, array, number)
{
	return Array::ApplyBinaryFunc_array_number(
		env, Array::binaryFuncPack_Mul, valueLeft, valueRight);
}

Gura_ImplementBinaryOperator(Mul, number, array)
{
	return Array::ApplyBinaryFunc_number_array(
		env, Array::binaryFuncPack_Mul, valueLeft, valueRight);
}

//-----------------------------------------------------------------------------
// [A / B] ... BinaryOperator(Div, A, B)
//-----------------------------------------------------------------------------
Gura_ImplementBinaryOperator(Div, number, number)
{
	Signal &sig = env.GetSignal();
	Number numRight = valueRight.GetNumber();
	if (numRight == 0) {
		Operator::SetError_DivideByZero(sig);
		return Value::Nil;
	}
	return Value(valueLeft.GetNumber() / numRight);
}

Gura_ImplementBinaryOperator(Div, complex, complex)
{
	Signal &sig = env.GetSignal();
	Complex numRight = valueRight.GetComplex();
	if (numRight == Complex(0.)) {
		Operator::SetError_DivideByZero(sig);
		return Value::Nil;
	}
	return Value(valueLeft.GetComplex() / valueRight.GetComplex());
}

Gura_ImplementBinaryOperator(Div, rational, rational)
{
	Signal &sig = env.GetSignal();
	const Rational &a = valueLeft.GetRational();
	const Rational &b = valueRight.GetRational();
	if (a.denom == 0 || b.numer == 0) {
		Rational::SetError_DenominatorZero(sig);
		return Value::Nil;
	}
	Rational c = a / b;
	if (c.numer == 0) return Value::Zero;
	return Value(c);
}

Gura_ImplementBinaryOperator(Div, rational, number)
{
	Signal &sig = env.GetSignal();
	const Rational &a = valueLeft.GetRational();
	const Rational b = Rational::FromNumber(valueRight.GetNumber());
	if (a.denom == 0 || b.numer == 0) {
		Rational::SetError_DenominatorZero(sig);
		return Value::Nil;
	}
	Rational c = a / b;
	if (c.numer == 0) return Value::Zero;
	return Value(c);
}

Gura_ImplementBinaryOperator(Div, number, rational)
{
	Signal &sig = env.GetSignal();
	const Rational a = Rational::FromNumber(valueLeft.GetNumber());
	const Rational &b = valueRight.GetRational();
	if (a.denom == 0 || b.numer == 0) {
		Rational::SetError_DenominatorZero(sig);
		return Value::Nil;
	}
	Rational c = a / b;
	if (c.numer == 0) return Value::Zero;
	return Value(c);
}

Gura_ImplementBinaryOperator(Div, number, complex)
{
	Signal &sig = env.GetSignal();
	Complex numRight = valueRight.GetComplex();
	if (numRight == Complex(0.)) {
		Operator::SetError_DivideByZero(sig);
		return Value::Nil;
	}
	return Value(valueLeft.GetNumber() / numRight);
}

Gura_ImplementBinaryOperator(Div, complex, number)
{
	Signal &sig = env.GetSignal();
	Number numRight = valueRight.GetNumber();
	if (numRight == 0) {
		Operator::SetError_DivideByZero(sig);
		return Value::Nil;
	}
	return Value(valueLeft.GetComplex() / numRight);
}

Gura_ImplementBinaryOperator(Div, matrix, any)
{
	return Matrix::Div(env,
					Object_matrix::GetObject(valueLeft)->GetMatrix(), valueRight);
}

Gura_ImplementBinaryOperator(Div, vertex, number)
{
	Signal &sig = env.GetSignal();
	const Vertex &vertex = Object_vertex::GetObject(valueLeft)->GetVertex();
	double numRight = valueRight.GetDouble();
	if (numRight == 0) {
		Operator::SetError_DivideByZero(sig);
		return Value::Nil;
	}
	return Value(new Object_vertex(env, Vertex(
									   vertex.x / numRight,
									   vertex.y / numRight,
									   vertex.z / numRight)));
}

Gura_ImplementBinaryOperator(Div, array, array)
{
	return Array::ApplyBinaryFunc_array_array(
		env, Array::binaryFuncPack_Div, valueLeft, valueRight);
}

Gura_ImplementBinaryOperator(Div, array, number)
{
	return Array::ApplyBinaryFunc_array_number(
		env, Array::binaryFuncPack_Div, valueLeft, valueRight);
}

Gura_ImplementBinaryOperator(Div, number, array)
{
	return Array::ApplyBinaryFunc_number_array(
		env, Array::binaryFuncPack_Div, valueLeft, valueRight);
}

//-----------------------------------------------------------------------------
// [A % B] ... BinaryOperator(Mod, A, B)
//-----------------------------------------------------------------------------
Gura_ImplementBinaryOperator(Mod, number, number)
{
	Signal &sig = env.GetSignal();
	Number numRight = valueRight.GetNumber();
	if (numRight == 0) {
		Operator::SetError_DivideByZero(sig);
		return Value::Nil;
	}
	return Value(::fmod(valueLeft.GetNumber(), numRight));
}

Gura_ImplementBinaryOperator(Mod, array, array)
{
	return Array::ApplyBinaryFunc_array_array(
		env, Array::binaryFuncPack_Mod, valueLeft, valueRight);
}

Gura_ImplementBinaryOperator(Mod, array, number)
{
	return Array::ApplyBinaryFunc_array_number(
		env, Array::binaryFuncPack_Mod, valueLeft, valueRight);
}

Gura_ImplementBinaryOperator(Mod, number, array)
{
	return Array::ApplyBinaryFunc_number_array(
		env, Array::binaryFuncPack_Mod, valueLeft, valueRight);
}

//-----------------------------------------------------------------------------
// [A %% B] ... BinaryOperator(ModMod, A, B)
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// [A ** B] ... BinaryOperator(Pow, A, B)
//-----------------------------------------------------------------------------
Gura_ImplementBinaryOperator(Pow, number, number)
{
	return Value(::pow(valueLeft.GetNumber(), valueRight.GetNumber()));
}

Gura_ImplementBinaryOperator(Pow, complex, complex)
{
#if defined(_MSC_VER) && _MSC_VER < 1900
	return Value(std::pow(valueLeft.GetComplex(), valueRight.GetComplex()));
#else
	return Value(std::pow<double, double>(valueLeft.GetComplex(), valueRight.GetComplex()));
#endif
}

Gura_ImplementBinaryOperator(Pow, number, complex)
{
	return Value(std::pow(valueLeft.GetNumber(), valueRight.GetComplex()));
}

Gura_ImplementBinaryOperator(Pow, complex, number)
{
	return Value(std::pow(valueLeft.GetComplex(), valueRight.GetNumber()));
}

Gura_ImplementBinaryOperator(Pow, array, array)
{
	return Array::ApplyBinaryFunc_array_array(
		env, Array::binaryFuncPack_Pow, valueLeft, valueRight);
}

Gura_ImplementBinaryOperator(Pow, array, number)
{
	return Array::ApplyBinaryFunc_array_number(
		env, Array::binaryFuncPack_Pow, valueLeft, valueRight);
}

Gura_ImplementBinaryOperator(Pow, number, array)
{
	return Array::ApplyBinaryFunc_number_array(
		env, Array::binaryFuncPack_Pow, valueLeft, valueRight);
}

//-----------------------------------------------------------------------------
// [A == B] ... BinaryOperator(Eq, A, B)
//-----------------------------------------------------------------------------
Gura_ImplementBinaryOperator(Eq, any, any)
{
	Signal &sig = env.GetSignal();
	int cmp = Value::Compare(env, valueLeft, valueRight);
	if (sig.IsSignalled()) return Value::Nil;
	return Value(cmp == 0);
}

//-----------------------------------------------------------------------------
// [A != B] ... BinaryOperator(Ne, A, B)
//-----------------------------------------------------------------------------
Gura_ImplementBinaryOperator(Ne, any, any)
{
	Signal &sig = env.GetSignal();
	int cmp = Value::Compare(env, valueLeft, valueRight);
	if (sig.IsSignalled()) return Value::Nil;
	return Value(cmp != 0);
}

//-----------------------------------------------------------------------------
// [A > B] ... BinaryOperator(Gt, A, B)
//-----------------------------------------------------------------------------
Gura_ImplementBinaryOperator(Gt, any, any)
{
	Signal &sig = env.GetSignal();
	int cmp = Value::Compare(env, valueLeft, valueRight);
	if (sig.IsSignalled()) return Value::Nil;
	return Value(cmp > 0);
}

//-----------------------------------------------------------------------------
// [A < B] ... BinaryOperator(Lt, A, B)
//-----------------------------------------------------------------------------
Gura_ImplementBinaryOperator(Lt, any, any)
{
	Signal &sig = env.GetSignal();
	int cmp = Value::Compare(env, valueLeft, valueRight);
	if (sig.IsSignalled()) return Value::Nil;
	return Value(cmp < 0);
}

//-----------------------------------------------------------------------------
// [A >= B] ... BinaryOperator(Ge, A, B)
//-----------------------------------------------------------------------------
Gura_ImplementBinaryOperator(Ge, any, any)
{
	Signal &sig = env.GetSignal();
	int cmp = Value::Compare(env, valueLeft, valueRight);
	if (sig.IsSignalled()) return Value::Nil;
	return Value(cmp >= 0);
}

//-----------------------------------------------------------------------------
// [A <= B] ... BinaryOperator(Le, A, B)
//-----------------------------------------------------------------------------
Gura_ImplementBinaryOperator(Le, any, any)
{
	Signal &sig = env.GetSignal();
	int cmp = Value::Compare(env, valueLeft, valueRight);
	if (sig.IsSignalled()) return Value::Nil;
	return Value(cmp <= 0);
}

//-----------------------------------------------------------------------------
// [A <=> B] BinaryOperator(Cmp, A, B)
//-----------------------------------------------------------------------------
Gura_ImplementBinaryOperator(Cmp, boolean, boolean)
{
	return Value(Value::CompareBoolean(valueLeft.GetBoolean(), valueRight.GetBoolean()));
}

Gura_ImplementBinaryOperator(Cmp, complex, complex)
{
	return Value(Value::CompareComplex(valueLeft.GetComplex(), valueRight.GetComplex()));
}

Gura_ImplementBinaryOperator(Cmp, number, number)
{
	return Value(Value::CompareNumber(valueLeft.GetNumber(), valueRight.GetNumber()));
}

Gura_ImplementBinaryOperator(Cmp, rational, rational)
{
	return Value(Value::CompareRational(valueLeft.GetRational(), valueRight.GetRational()));
}

Gura_ImplementBinaryOperator(Cmp, number, rational)
{
	Signal &sig = env.GetSignal();
	const Rational &ratio = valueRight.GetRational();
	if (ratio.denom == 0) {
		Operator::SetError_DivideByZero(sig);
		return Value::Nil;
	}
	return Value(Value::CompareNumber(valueLeft.GetNumber(), ratio.numer / ratio.denom));
}

Gura_ImplementBinaryOperator(Cmp, rational, number)
{
	Signal &sig = env.GetSignal();
	const Rational &ratio = valueLeft.GetRational();
	if (ratio.denom == 0) {
		Operator::SetError_DivideByZero(sig);
		return Value::Nil;
	}
	return Value(Value::CompareNumber(ratio.numer / ratio.denom, valueRight.GetNumber()));
}

Gura_ImplementBinaryOperator(Cmp, string, string)
{
	return Value(Value::CompareString(valueLeft.GetString(), valueRight.GetString(), false));
}

Gura_ImplementBinaryOperator(Cmp, symbol, symbol)
{
	return Value(Value::CompareSymbol(valueLeft.GetSymbol(), valueRight.GetSymbol()));
}

Gura_ImplementBinaryOperator(Cmp, binary, binary)
{
	const Binary &buff1 = valueLeft.GetBinary();
	const Binary &buff2 = valueRight.GetBinary();
	return
		(buff1.size() < buff2.size())? -1 :
		(buff1.size() > buff2.size())? +1 :
		::memcmp(buff1.data(), buff2.data(), buff1.size());
}

Gura_ImplementBinaryOperator(Cmp, datetime, datetime)
{
	const DateTime &dt1 = Object_datetime::GetObject(valueLeft)->GetDateTime();
	const DateTime &dt2 = Object_datetime::GetObject(valueRight)->GetDateTime();
	return DateTime::Compare(dt1, dt2);
}

Gura_ImplementBinaryOperator(Cmp, list, list)
{
	Signal &sig = env.GetSignal();
	const ValueList &valList1 = valueLeft.GetList();
	const ValueList &valList2 = valueRight.GetList();
	if (valList1.size() < valList2.size()) return Value(-1);
	if (valList1.size() > valList2.size()) return Value(+1);
	ValueList::const_iterator pValue1 = valList1.begin();
	ValueList::const_iterator pValue2 = valList2.begin();
	for ( ; pValue1 != valList1.end(); pValue1++, pValue2++) {
		int cmp = Value::Compare(env, *pValue1, *pValue2);
		if (sig.IsSignalled()) return Value::Nil;
		if (cmp < 0) return Value(-1);
		if (cmp > 0) return Value(+1);
	}
	return Value(0);
}

Gura_ImplementBinaryOperator(Cmp, timedelta, timedelta)
{
	const TimeDelta &td1 = Object_timedelta::GetObject(valueLeft)->GetTimeDelta();
	const TimeDelta &td2 = Object_timedelta::GetObject(valueRight)->GetTimeDelta();
	return TimeDelta::Compare(td1, td2);
}

//-----------------------------------------------------------------------------
// [A in B] ... BinaryOperator(Contains, A, B)
//-----------------------------------------------------------------------------
Gura_ImplementBinaryOperator(Contains, any, any)
{
	Signal &sig = env.GetSignal();
	if (valueLeft.Is_list() || valueLeft.Is_iterator()) {
		AutoPtr<Iterator_Contains> pIterator(new Iterator_Contains(valueLeft.CreateIterator(sig)));
		if (sig.IsSignalled()) return Value::Nil;
		ValueList &valListToFind = pIterator->GetValueListToFind();
		if (valueRight.Is_list()) {
			valListToFind.Append(valueRight.GetList());
		} else if (valueRight.Is_iterator()) {
			AutoPtr<Iterator> pIteratorToFind(valueRight.CreateIterator(sig));
			if (pIteratorToFind.IsNull()) return Value::Nil;
			valListToFind.Append(env, pIteratorToFind.get());
			if (sig.IsSignalled()) return Value::Nil;
		} else {
			valListToFind.push_back(valueRight);
		}
		if (valueLeft.Is_iterator()) {
			return Value(new Object_iterator(env, pIterator.release()));
		}
		return pIterator->ToList(env, true, false);
	} else if (valueRight.Is_list()) {
		bool foundFlag = valueRight.GetList().DoesContain(env, valueLeft);
		if (sig.IsSignalled()) return Value::Nil;
		return Value(foundFlag);
	} else if (valueRight.Is_iterator()) {
		AutoPtr<Iterator> pIteratorToFind(valueRight.CreateIterator(sig));
		if (pIteratorToFind.IsNull()) return Value::Nil;
		bool foundFlag = pIteratorToFind->DoesContain(env, valueLeft);
		if (sig.IsSignalled()) return Value::Nil;
		return Value(foundFlag);
	} else {
		int cmp = Value::Compare(env, valueLeft, valueRight);
		if (sig.IsSignalled()) return Value::Nil;
		return Value(cmp == 0);
	}
}

//-----------------------------------------------------------------------------
// [A & B] ... BinaryOperator(And, A, B)
//-----------------------------------------------------------------------------
Gura_ImplementBinaryOperator(And, number, number)
{
	return Value(static_cast<ULong>(valueLeft.GetNumber()) &
						static_cast<ULong>(valueRight.GetNumber()));
}

Gura_ImplementBinaryOperator(And, boolean, boolean)
{
	return Value(valueLeft.GetBoolean() && valueRight.GetBoolean());
}

Gura_ImplementBinaryOperator(And, nil, any)
{
	return Value::Nil;	// nil & any -> nil
}

Gura_ImplementBinaryOperator(And, any, nil)
{
	return Value::Nil;	// any & nil -> nil
}

Gura_ImplementBinaryOperator(And, array, array)
{
	return Array::ApplyBinaryFunc_array_array(
		env, Array::binaryFuncPack_And, valueLeft, valueRight);
}

Gura_ImplementBinaryOperator(And, array, number)
{
	return Array::ApplyBinaryFunc_array_number(
		env, Array::binaryFuncPack_And, valueLeft, valueRight);
}

Gura_ImplementBinaryOperator(And, number, array)
{
	return Array::ApplyBinaryFunc_number_array(
		env, Array::binaryFuncPack_And, valueLeft, valueRight);
}

//-----------------------------------------------------------------------------
// [A | B] ... BinaryOperator(Or, A, B)
//-----------------------------------------------------------------------------
Gura_ImplementBinaryOperator(Or, number, number)
{
	return Value(valueLeft.GetULong() | valueRight.GetULong());
}

Gura_ImplementBinaryOperator(Or, boolean, boolean)
{
	return Value(valueLeft.GetBoolean() || valueRight.GetBoolean());
}

Gura_ImplementBinaryOperator(Or, nil, any)
{
	return valueRight;	// nil | any -> any
}

Gura_ImplementBinaryOperator(Or, any, nil)
{
	return valueLeft;	// any | nil -> any
}

Gura_ImplementBinaryOperator(Or, array, array)
{
	return Array::ApplyBinaryFunc_array_array(
		env, Array::binaryFuncPack_Or, valueLeft, valueRight);
}

Gura_ImplementBinaryOperator(Or, array, number)
{
	return Array::ApplyBinaryFunc_array_number(
		env, Array::binaryFuncPack_Or, valueLeft, valueRight);
}

Gura_ImplementBinaryOperator(Or, number, array)
{
	return Array::ApplyBinaryFunc_number_array(
		env, Array::binaryFuncPack_Or, valueLeft, valueRight);
}

//-----------------------------------------------------------------------------
// [A ^ B] ... BinaryOperator(Xor, A, B)
//-----------------------------------------------------------------------------
Gura_ImplementBinaryOperator(Xor, number, number)
{
	return Value(static_cast<ULong>(valueLeft.GetNumber()) ^
						static_cast<ULong>(valueRight.GetNumber()));
}

Gura_ImplementBinaryOperator(Xor, boolean, boolean)
{
	bool flagLeft = valueLeft.GetBoolean();
	bool flagRight = valueRight.GetBoolean();
	return Value((flagLeft && !flagRight) || (!flagLeft && flagRight));
}

Gura_ImplementBinaryOperator(Xor, array, array)
{
	return Array::ApplyBinaryFunc_array_array(
		env, Array::binaryFuncPack_Xor, valueLeft, valueRight);
}

Gura_ImplementBinaryOperator(Xor, array, number)
{
	return Array::ApplyBinaryFunc_array_number(
		env, Array::binaryFuncPack_Xor, valueLeft, valueRight);
}

Gura_ImplementBinaryOperator(Xor, number, array)
{
	return Array::ApplyBinaryFunc_number_array(
		env, Array::binaryFuncPack_Xor, valueLeft, valueRight);
}

//-----------------------------------------------------------------------------
// [A << B] ... BinaryOperator(Shl, A, B)
//-----------------------------------------------------------------------------
Gura_ImplementBinaryOperator(Shl, number, number)
{
	return Value(static_cast<ULong>(valueLeft.GetNumber()) <<
							static_cast<ULong>(valueRight.GetNumber()));
}

Gura_ImplementBinaryOperator(Shl, stream, any)
{
	Signal &sig = env.GetSignal();
	Stream &stream = valueLeft.GetStream();
	if (!stream.CheckWritable(sig)) return Value::Nil;
	if (valueRight.Is_binary()) {
		const Binary &binary = valueRight.GetBinary();
		stream.Write(sig, binary.c_str(), binary.size());
		if (sig.IsSignalled()) return Value::Nil;
	} else {
		String str(valueRight.ToString(false));
		if (sig.IsSignalled()) return Value::Nil;
		stream.Print(sig, str.c_str());
		if (sig.IsSignalled()) return Value::Nil;
	}
	return valueLeft;
}

Gura_ImplementBinaryOperator(Shl, array, array)
{
	return Array::ApplyBinaryFunc_array_array(
		env, Array::binaryFuncPack_Shl, valueLeft, valueRight);
}

Gura_ImplementBinaryOperator(Shl, array, number)
{
	return Array::ApplyBinaryFunc_array_number(
		env, Array::binaryFuncPack_Shl, valueLeft, valueRight);
}

Gura_ImplementBinaryOperator(Shl, number, array)
{
	return Array::ApplyBinaryFunc_number_array(
		env, Array::binaryFuncPack_Shl, valueLeft, valueRight);
}

//-----------------------------------------------------------------------------
// [A >> B] ... BinaryOperator(Shr, A, B)
//-----------------------------------------------------------------------------
Gura_ImplementBinaryOperator(Shr, number, number)
{
	return Value(static_cast<ULong>(valueLeft.GetNumber()) >>
							static_cast<ULong>(valueRight.GetNumber()));
}

Gura_ImplementBinaryOperator(Shr, array, array)
{
	return Array::ApplyBinaryFunc_array_array(
		env, Array::binaryFuncPack_Shr, valueLeft, valueRight);
}

Gura_ImplementBinaryOperator(Shr, array, number)
{
	return Array::ApplyBinaryFunc_array_number(
		env, Array::binaryFuncPack_Shr, valueLeft, valueRight);
}

Gura_ImplementBinaryOperator(Shr, number, array)
{
	return Array::ApplyBinaryFunc_number_array(
		env, Array::binaryFuncPack_Shr, valueLeft, valueRight);
}

//-----------------------------------------------------------------------------
// [A || B] ... BinaryOperator(OrOr, A, B)
//-----------------------------------------------------------------------------
Gura_ImplementBinaryOperator(OrOr, any, any)
{
	if (valueLeft.GetBoolean()) return valueLeft;
	return valueRight;
}

//-----------------------------------------------------------------------------
// [A && B] ... BinaryOperator(AndAnd, A, B)
//-----------------------------------------------------------------------------
Gura_ImplementBinaryOperator(AndAnd, any, any)
{
	if (!valueLeft.GetBoolean()) return valueLeft;
	return valueRight;
}

//-----------------------------------------------------------------------------
// [A .. B] ... BinaryOperator(Seq, A, B)
//-----------------------------------------------------------------------------
Gura_ImplementBinaryOperator(Seq, number, number)
{
	Number numBegin = valueLeft.GetNumber();
	Number numEnd = valueRight.GetNumber();
	Number numStep = (numEnd >= numBegin)? +1 : -1;
	return Value(new Object_iterator(env, new Iterator_Sequence(numBegin, numEnd, numStep)));
}

//-----------------------------------------------------------------------------
// [A => B] ... BinaryOperator(Pair, A, B)
//-----------------------------------------------------------------------------
Gura_ImplementBinaryOperator(Pair, symbol, any)
{
	return Value::CreateList(env, valueLeft, valueRight);
}

Gura_ImplementBinaryOperator(Pair, string, any)
{
	return Value::CreateList(env, valueLeft, valueRight);
}

Gura_ImplementBinaryOperator(Pair, number, any)
{
	return Value::CreateList(env, valueLeft, valueRight);
}

//-----------------------------------------------------------------------------
// math.abs(A) ... UnaryOperator(Math_abs, A)
//-----------------------------------------------------------------------------
Gura_ImplementUnaryOperator(Math_abs, number)
{
	return Value(::fabs(value.GetNumber()));
}

Gura_ImplementUnaryOperator(Math_abs, complex)
{
	return Value(std::abs(value.GetComplex()));
}

//-----------------------------------------------------------------------------
// OperatorEntryCustom
//-----------------------------------------------------------------------------
Value OperatorEntryCustom::DoEval(Environment &env, const Value &value) const
{
	AutoPtr<Argument> pArg(new Argument(_pFunc.get()));
	if (!pArg->StoreValue(env, value)) return Value::Nil;
	return _pFunc->Eval(env, *pArg);
}

Value OperatorEntryCustom::DoEval(Environment &env,
					const Value &valueLeft, const Value &valueRight) const
{
	AutoPtr<Argument> pArg(new Argument(_pFunc.get()));
	if (!pArg->StoreValue(env, valueLeft, valueRight)) return Value::Nil;
	return _pFunc->Eval(env, *pArg);
}

//-----------------------------------------------------------------------------
// OperatorEntryDerived
//-----------------------------------------------------------------------------
Value OperatorEntryDerived::DoEval(Environment &env, const Value &value) const
{
	return _pOperatorEntryOrg->DoEval(env, value);
}

Value OperatorEntryDerived::DoEval(Environment &env,
					const Value &valueLeft, const Value &valueRight) const
{
	return _pOperatorEntryOrg->DoEval(env, valueLeft, valueRight);
}

//-----------------------------------------------------------------------------
// Operator assignment
//-----------------------------------------------------------------------------
void Operator::AssignOperatorBasic(Environment &env)
{
	// unary operators
	Gura_AssignUnaryOperator(Pos, number);
	Gura_AssignUnaryOperator(Pos, complex);
	Gura_AssignUnaryOperator(Pos, rational);
	Gura_AssignUnaryOperator(Pos, matrix);
	Gura_AssignUnaryOperator(Pos, timedelta);
	Gura_AssignUnaryOperator(Pos, array);
	Gura_AssignUnaryOperator(Neg, number);
	Gura_AssignUnaryOperator(Neg, complex);
	Gura_AssignUnaryOperator(Neg, rational);
	Gura_AssignUnaryOperator(Neg, matrix);
	Gura_AssignUnaryOperator(Neg, timedelta);
	Gura_AssignUnaryOperator(Neg, vertex);
	Gura_AssignUnaryOperator(Neg, array);
	Gura_AssignUnaryOperator(Inv, number);
	Gura_AssignUnaryOperator(Not, any);
	Gura_AssignUnaryOperatorSuffix(SeqInf, number);
	Gura_AssignUnaryOperatorSuffix(Question, any);
	Gura_AssignUnaryOperatorSuffix(Each, any);
	// binary operators
	Gura_AssignBinaryOperator(Add, number, number);
	Gura_AssignBinaryOperator(Add, boolean, boolean);
	Gura_AssignBinaryOperator(Add, number, boolean);
	Gura_AssignBinaryOperator(Add, boolean, number);
	Gura_AssignBinaryOperator(Add, number, complex);
	Gura_AssignBinaryOperator(Add, number, rational);
	Gura_AssignBinaryOperator(Add, complex, number);
	Gura_AssignBinaryOperator(Add, complex, complex);
	Gura_AssignBinaryOperator(Add, rational, number);
	Gura_AssignBinaryOperator(Add, rational, rational);
	Gura_AssignBinaryOperator(Add, matrix, matrix);
	Gura_AssignBinaryOperator(Add, datetime, timedelta);
	Gura_AssignBinaryOperator(Add, timedelta, datetime);
	Gura_AssignBinaryOperator(Add, timedelta, timedelta);
	Gura_AssignBinaryOperator(Add, string, string);
	Gura_AssignBinaryOperator(Add, binary, binary);
	Gura_AssignBinaryOperator(Add, binary, string);
	Gura_AssignBinaryOperator(Add, string, binary);
	Gura_AssignBinaryOperator(Add, pointer, number);
	Gura_AssignBinaryOperator(Add, string, any);
	Gura_AssignBinaryOperator(Add, any, string);
	Gura_AssignBinaryOperator(Add, vertex, vertex);
	Gura_AssignBinaryOperator(Add, array, array);
	Gura_AssignBinaryOperator(Add, array, number);
	Gura_AssignBinaryOperator(Add, number, array);
	Gura_AssignBinaryOperator(Sub, number, number);
	Gura_AssignBinaryOperator(Sub, boolean, boolean);
	Gura_AssignBinaryOperator(Sub, number, boolean);
	Gura_AssignBinaryOperator(Sub, boolean, number);
	Gura_AssignBinaryOperator(Sub, number, complex);
	Gura_AssignBinaryOperator(Sub, number, rational);
	Gura_AssignBinaryOperator(Sub, complex, number);
	Gura_AssignBinaryOperator(Sub, complex, complex);
	Gura_AssignBinaryOperator(Sub, rational, number);
	Gura_AssignBinaryOperator(Sub, rational, rational);
	Gura_AssignBinaryOperator(Sub, matrix, matrix);
	Gura_AssignBinaryOperator(Sub, datetime, timedelta);
	Gura_AssignBinaryOperator(Sub, datetime, datetime);
	Gura_AssignBinaryOperator(Sub, timedelta, timedelta);
	Gura_AssignBinaryOperator(Sub, color, color);
	Gura_AssignBinaryOperator(Sub, pointer, number);
	Gura_AssignBinaryOperator(Sub, pointer, pointer);
	Gura_AssignBinaryOperator(Sub, vertex, vertex);
	Gura_AssignBinaryOperator(Sub, array, array);
	Gura_AssignBinaryOperator(Sub, array, number);
	Gura_AssignBinaryOperator(Sub, number, array);
	Gura_AssignBinaryOperator(Mul, number, number);
	Gura_AssignBinaryOperator(Mul, boolean, boolean);
	Gura_AssignBinaryOperator(Mul, number, boolean);
	Gura_AssignBinaryOperator(Mul, boolean, number);
	Gura_AssignBinaryOperator(Mul, number, complex);
	Gura_AssignBinaryOperator(Mul, number, rational);
	Gura_AssignBinaryOperator(Mul, complex, number);
	Gura_AssignBinaryOperator(Mul, complex, complex);
	Gura_AssignBinaryOperator(Mul, rational, number);
	Gura_AssignBinaryOperator(Mul, rational, rational);
	Gura_AssignBinaryOperator(Mul, any, matrix);
	Gura_AssignBinaryOperator(Mul, matrix, any);
	Gura_AssignBinaryOperator(Mul, timedelta, number);
	Gura_AssignBinaryOperator(Mul, number, timedelta);
	Gura_AssignBinaryOperator(Mul, function, any);
	Gura_AssignBinaryOperator(Mul, Class, any);
	Gura_AssignBinaryOperator(Mul, string, number);
	Gura_AssignBinaryOperator(Mul, number, string);
	Gura_AssignBinaryOperator(Mul, binary, number);
	Gura_AssignBinaryOperator(Mul, number, binary);
	Gura_AssignBinaryOperator(Mul, vertex, number);
	Gura_AssignBinaryOperator(Mul, array, array);
	Gura_AssignBinaryOperator(Mul, array, number);
	Gura_AssignBinaryOperator(Mul, number, array);
	Gura_AssignBinaryOperator(Div, number, number);
	Gura_AssignBinaryOperator(Div, number, complex);
	Gura_AssignBinaryOperator(Div, number, rational);
	Gura_AssignBinaryOperator(Div, complex, number);
	Gura_AssignBinaryOperator(Div, complex, complex);
	Gura_AssignBinaryOperator(Div, rational, number);
	Gura_AssignBinaryOperator(Div, rational, rational);
	Gura_AssignBinaryOperator(Div, matrix, any);
	Gura_AssignBinaryOperator(Div, vertex, number);
	Gura_AssignBinaryOperator(Div, array, array);
	Gura_AssignBinaryOperator(Div, array, number);
	Gura_AssignBinaryOperator(Div, number, array);
	Gura_AssignBinaryOperator(Mod, number, number);
	Gura_AssignBinaryOperator(Mod, array, array);
	Gura_AssignBinaryOperator(Mod, array, number);
	Gura_AssignBinaryOperator(Mod, number, array);
	Gura_AssignBinaryOperator(Pow, number, number);
	Gura_AssignBinaryOperator(Pow, complex, complex);
	Gura_AssignBinaryOperator(Pow, number, complex);
	Gura_AssignBinaryOperator(Pow, complex, number);
	Gura_AssignBinaryOperator(Pow, array, array);
	Gura_AssignBinaryOperator(Pow, array, number);
	Gura_AssignBinaryOperator(Pow, number, array);
	Gura_AssignBinaryOperator(Eq, any, any);
	Gura_AssignBinaryOperator(Ne, any, any);
	Gura_AssignBinaryOperator(Gt, any, any);
	Gura_AssignBinaryOperator(Lt, any, any);
	Gura_AssignBinaryOperator(Ge, any, any);
	Gura_AssignBinaryOperator(Le, any, any);
	Gura_AssignBinaryOperator(Cmp, boolean, boolean);
	Gura_AssignBinaryOperator(Cmp, complex, complex);
	Gura_AssignBinaryOperator(Cmp, number, number);
	Gura_AssignBinaryOperator(Cmp, rational, rational);
	Gura_AssignBinaryOperator(Cmp, number, rational);
	Gura_AssignBinaryOperator(Cmp, rational, number);
	Gura_AssignBinaryOperator(Cmp, string, string);
	Gura_AssignBinaryOperator(Cmp, symbol, symbol);
	Gura_AssignBinaryOperator(Cmp, binary, binary);
	Gura_AssignBinaryOperator(Cmp, datetime, datetime);
	Gura_AssignBinaryOperator(Cmp, list, list);
	Gura_AssignBinaryOperator(Cmp, timedelta, timedelta);
	Gura_AssignBinaryOperator(Contains, any, any);
	Gura_AssignBinaryOperator(And, number, number);
	Gura_AssignBinaryOperator(And, boolean, boolean);
	Gura_AssignBinaryOperator(And, nil, any);
	Gura_AssignBinaryOperator(And, any, nil);
	Gura_AssignBinaryOperator(And, array, array);
	Gura_AssignBinaryOperator(And, array, number);
	Gura_AssignBinaryOperator(And, number, array);
	Gura_AssignBinaryOperator(Or, number, number);
	Gura_AssignBinaryOperator(Or, boolean, boolean);
	Gura_AssignBinaryOperator(Or, nil, any);
	Gura_AssignBinaryOperator(Or, any, nil);
	Gura_AssignBinaryOperator(Or, array, array);
	Gura_AssignBinaryOperator(Or, array, number);
	Gura_AssignBinaryOperator(Or, number, array);
	Gura_AssignBinaryOperator(Xor, number, number);
	Gura_AssignBinaryOperator(Xor, boolean, boolean);
	Gura_AssignBinaryOperator(Xor, array, array);
	Gura_AssignBinaryOperator(Xor, array, number);
	Gura_AssignBinaryOperator(Xor, number, array);
	Gura_AssignBinaryOperator(Shl, number, number);
	Gura_AssignBinaryOperator(Shl, stream, any);
	Gura_AssignBinaryOperator(Shl, array, array);
	Gura_AssignBinaryOperator(Shl, array, number);
	Gura_AssignBinaryOperator(Shl, number, array);
	Gura_AssignBinaryOperator(Shr, number, number);
	Gura_AssignBinaryOperator(Shr, array, array);
	Gura_AssignBinaryOperator(Shr, array, number);
	Gura_AssignBinaryOperator(Shr, number, array);
	Gura_AssignBinaryOperator(OrOr, any, any);
	Gura_AssignBinaryOperator(AndAnd, any, any);
	Gura_AssignBinaryOperator(Seq, number, number);
	Gura_AssignBinaryOperator(Pair, symbol, any);
	Gura_AssignBinaryOperator(Pair, string, any);
	Gura_AssignBinaryOperator(Pair, number, any);
	// mathematical functions
	Gura_AssignUnaryOperator(Math_abs, number);
	Gura_AssignUnaryOperator(Math_abs, complex);
}

}
