#pragma once

template<typename Derived, template<typename> class CRTPClass>
class CRTPHelper
{
public:
	virtual ~CRTPHelper() {}
protected:
	Derived& Underlying() { return static_cast<Derived&>(*this); }
	Derived const& Underlying() const { return static_cast<Derived const&>(*this); }
private:
	CRTPHelper() {}
	friend CRTPClass<Derived>;
};
