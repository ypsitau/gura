#ifndef __GMP_CLASS_MPQ_H__
#define __GMP_CLASS_MPQ_H__

Gura_BeginModuleScope(gmp)

//-----------------------------------------------------------------------------
// Object_mpq declaration
//-----------------------------------------------------------------------------
Gura_DeclareUserClassBegin(mpq)
public:
	virtual bool Format_d(Formatter *pFormatter, Formatter::Flags &flags, const Value &value) const;
	virtual bool Format_b(Formatter *pFormatter, Formatter::Flags &flags, const Value &value) const;
	virtual bool Format_o(Formatter *pFormatter, Formatter::Flags &flags, const Value &value) const;
	virtual bool Format_x(Formatter *pFormatter, Formatter::Flags &flags, const Value &value) const;
Gura_DeclareUserClassEnd(mpq)

class Object_mpq : public Object {
private:
	mpq_class _num;
public:
	Gura_DeclareObjectAccessor(mpq)
public:
	Object_mpq(mpq_t num);
	Object_mpq(const mpq_class &num);
	virtual String ToString(bool exprFlag);
	inline mpq_class &GetEntity() { return _num; }
	inline const mpq_class &GetEntity() const { return _num; }
	inline static const mpq_class &GetEntity(const Value &value) {
		return GetObject(value)->GetEntity();
	}
	inline static const mpq_class &GetEntity(Argument &arg, size_t idx) {
		return GetObject(arg, idx)->GetEntity();
	}
	inline static const mpq_class &GetThisEntity(Argument &arg) {
		return GetObjectThis(arg)->GetEntity();
	}
};

Gura_EndModuleScope(gmp)

#endif
