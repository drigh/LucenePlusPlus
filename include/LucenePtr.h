#ifndef LUCENEPTR_H
#define LUCENEPTR_H

#include <boost/shared_ptr.hpp>

namespace Lucene
{

template <class T>
class my_ptr
{
public:
	my_ptr(): m_t(NULL)
	{
	}

	explicit my_ptr(T* t): m_t(t)
	{}

    template<class Y>
    my_ptr( my_ptr<Y> const & r, typename boost::detail::sp_enable_if_convertible<Y,T>::type = boost::detail::sp_empty() )
    : m_t( r.m_t )
    {
    }

	template <class T1>
	my_ptr(const my_ptr<T1>& other,boost::detail::dynamic_cast_tag): m_t(dynamic_cast<T*>(other.m_t))
	{

	}

	template <class T1>
	my_ptr(const my_ptr<T1>& other,boost::detail::static_cast_tag): m_t(static_cast<T*>(other.m_t))
	{

	}

	bool expired() const
	{
		return false;
	}

	my_ptr lock() const
	{
		return *this;
	}

	T* get() const
	{
		return m_t;
	}

	T* operator->() const
	{
		return m_t;
	}

	T& operator*()
	{
		return *m_t;
	}

	const T& operator*() const
	{
		return *m_t;
	}

	void reset(T* newT = NULL)
	{
		m_t = newT;
	}

	my_ptr& operator=(const my_ptr& other)
	{
		m_t = other.m_t;
		return *this;
	}

	template <class T1>
	my_ptr& operator=(const my_ptr<T1>& other)
	{
		m_t = other.m_t;
		return *this;
	}

    template<class Y> bool _internal_less(my_ptr<Y> const & rhs) const
    {
        return m_t < rhs.m_t;
    }

private:
	T* m_t;

	template <class Y> friend class my_ptr;

private:

  struct Tester
  {
    Tester(int) {}  // No default constructor
    void dummy() {}
  };

  typedef void (Tester::*unspecified_bool_type)();

public:

  operator unspecified_bool_type() const
  {
    return !m_t? 0 : &Tester::dummy;
  }
};

template<class T, class U> inline bool operator<(my_ptr<T> const & a, my_ptr<U> const & b)
{
    return a._internal_less(b);
}

template<class T, class U> inline bool operator==(my_ptr<T> const & a, my_ptr<U> const & b)
{
    return a.get() == b.get();
}

template<class T, class U> inline bool operator!=(my_ptr<T> const & a, my_ptr<U> const & b)
{
    return a.get() != b.get();
}

template<class T> inline T * get_pointer(my_ptr<T> const & p)
{
    return p.get();
}


}

namespace boost
{

template <class T1, class T2>
Lucene::my_ptr<T1> dynamic_pointer_cast(const Lucene::my_ptr<T2>& a)
{
	return Lucene::my_ptr<T1>(a, boost::detail::dynamic_cast_tag());
}
template <class T1, class T2>
Lucene::my_ptr<T1> static_pointer_cast(const Lucene::my_ptr<T2>& a)
{
	return Lucene::my_ptr<T1>(a, boost::detail::static_cast_tag());
}

}

#endif

