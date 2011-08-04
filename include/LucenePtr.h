#ifndef LUCENEPTR_H
#define LUCENEPTR_H

#include <boost/shared_ptr.hpp>
#include "TypedCounter.h"

namespace Lucene
{

template<class T> class my_w_ptr;

template <class T>
class my_ptr: public boost::shared_ptr<T>
{
	typedef boost::shared_ptr<T> sptr;
public:
	~my_ptr()
	{
		DestroyCounter().Increment(sptr::get());
	}
	my_ptr()
	{
		CreateCounter().Increment(sptr::get());
	}

	explicit my_ptr(T* t): sptr(t)
	{
		CreateCounter().Increment(sptr::get());
	}

	explicit my_ptr(const sptr& other): sptr(other)
	{
		CreateCounter().Increment(sptr::get());
	}

	explicit my_ptr(const my_w_ptr<T>& other): sptr(other)
	{
		FromWeakCounter().Increment(sptr::get());
	}

	explicit my_ptr(const my_w_ptr<T>& other, boost::detail::sp_nothrow_tag t): sptr(other, t)
	{
		FromWeakCounter().Increment(sptr::get());
	}

    my_ptr( my_ptr const & r) : sptr(r)
    {
		CopyCounter().Increment(sptr::get());
    }

	template<class Y>
    my_ptr( my_ptr<Y> const & r, typename boost::detail::sp_enable_if_convertible<Y,T>::type d = boost::detail::sp_empty() )
    : sptr(r, d)
    {
		CopyCounter().Increment(sptr::get());
    }

	template <class T1>
	my_ptr(const my_ptr<T1>& other,boost::detail::dynamic_cast_tag t)
	:sptr(other, t)
	{
		DyncastCounter().Increment(sptr::get());
	}

	template <class T1>
	my_ptr(const my_ptr<T1>& other,boost::detail::static_cast_tag t)
	:sptr(other, t)
	{
		StaticCastCounter().Increment(sptr::get());
	}

	my_ptr& operator=(const my_ptr& other)
	{
		my_ptr& result = static_cast<my_ptr&>(sptr::operator=(other));
		AssignCounter().Increment(sptr::get());
		return result;
	}

	template <class T1>
	my_ptr& operator=(const my_ptr<T1>& other)
	{
		my_ptr& result = static_cast<my_ptr&>(sptr::operator=(other));
		AssignCounter().Increment(sptr::get());
		return result;
	}

	template <class T1>
	my_ptr& operator=(const my_w_ptr<T1>& other)
	{
		my_ptr& result = static_cast<my_ptr&>(sptr::operator=(other));
		AssignFromWeakCounter().Increment(sptr::get());
		return result;
	}

	void reset()
	{
		DestroyCounter().Increment(sptr::get());
		sptr::reset();
	}

    template<class Y> void reset(Y * p) // Y must be complete
    {
		DestroyCounter().Increment(sptr::get());
		sptr::reset(p);
		CreateCounter().Increment(sptr::get());
    }

private:
	template <class Y> friend class my_ptr;

	static TypedCounter<T>& CreateCounter()
	{
		static TypedCounter<T> s_createCounter("MyPtr::Create");
		return s_createCounter;
	}
	static TypedCounter<T>& DyncastCounter()
	{
		static TypedCounter<T> s_dyncastCounter("MyPtr::DynamicCast");
		return s_dyncastCounter;
	}
	static TypedCounter<T>& StaticCastCounter()
	{
		static TypedCounter<T> s_staticCastCounter("MyPtr::StaticCast");
		return s_staticCastCounter;
	}
	static TypedCounter<T>& DestroyCounter()
	{
		static TypedCounter<T> s_destroyCounter("MyPtr::Destroy");
		return s_destroyCounter;
	}
	static TypedCounter<T>& CopyCounter()
	{
		static TypedCounter<T> s_copyCounter("MyPtr::Copy");
		return s_copyCounter;
	}
	static TypedCounter<T>& FromWeakCounter()
	{
		static TypedCounter<T> s_fromWeakCounter("MyPtr::CreateFromWeak");
		return s_fromWeakCounter;
	}
	static TypedCounter<T>& AssignCounter()
	{
		static TypedCounter<T> s_assignCounter("MyPtr::Assign");
		return s_assignCounter;
	}
	static TypedCounter<T>& AssignFromWeakCounter()
	{
		static TypedCounter<T> s_assignFromWeakCounter("MyPtr::AssignFromWeak");
		return s_assignFromWeakCounter;
	}
};

template <class T>
class my_w_ptr: public boost::weak_ptr<T>
{
	typedef boost::weak_ptr<T> wptr;
public:
	my_w_ptr()
	{
		CreateCounter().Increment(getPtr());
	}

	template <class Y>
    my_w_ptr( my_w_ptr<Y> const & r, typename boost::detail::sp_enable_if_convertible<Y,T>::type d = boost::detail::sp_empty() )
    :wptr(r, d)
    {
    }

	template <class Y>
	my_w_ptr( my_ptr<Y> const & r, typename boost::detail::sp_enable_if_convertible<Y,T>::type d = boost::detail::sp_empty() )
    :wptr(r, d)
    {
		CreateCounter().Increment(getPtr());
    }

    template<class Y>
    my_w_ptr & operator=(my_w_ptr<Y> const & r) // never throws
    {
        my_w_ptr& result = static_cast<my_w_ptr&>(wptr::operator=(r));
        AssignCounter().Increment(getPtr());
        return result;
    }

    template<class Y>
    my_w_ptr& operator=(my_ptr<Y> const & r) // never throws
    {
        my_w_ptr& result = static_cast<my_w_ptr&>(wptr::operator=(r));
        AssignCounter().Increment(getPtr());
        return result;
    }

    my_ptr<T> lock() const // never throws
    {
        return my_ptr<T>( *this, boost::detail::sp_nothrow_tag() );
    }
private:
    T* getPtr()
    {
    	// hacky hacky
    	// pointer to "counted base" is stored here
    	// (it is counted_base* in fact, but TypedCounter needs T*)
    	// if pointer is NULL, operation is free
    	return reinterpret_cast<T**>(this)[1];
    }
	static TypedCounter<T>& CreateCounter()
	{
		static TypedCounter<T> s_createCounter("WeakPtr::Create");
		return s_createCounter;
	}
	static TypedCounter<T>& AssignCounter()
	{
		static TypedCounter<T> s_createCounter("WeakPtr::Assign");
		return s_createCounter;
	}
};

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

template <class T> inline void swap(Lucene::my_ptr<T>& a, Lucene::my_ptr<T>& b)
{
    a.swap(b);
}

}

#endif

