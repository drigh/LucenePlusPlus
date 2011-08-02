/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2009-2011 Alan Wright. All rights reserved.
// Distributable under the terms of either the Apache License (Version 2.0)
// or the GNU Lesser General Public License.
/////////////////////////////////////////////////////////////////////////////

#ifndef LUCENEFACTORY_H
#define LUCENEFACTORY_H

//#include <boost/make_shared.hpp>
#include "LucenePtr.h"

namespace Lucene
{
    template <class T>
    my_ptr<T> newInstance()
    {
    	Allocator<T> a;
    	T* newT = a.allocate(1);
    	::new (newT)T();
    	return my_ptr<T>(newT);
    }
    
    template <class T, class A1>
    my_ptr<T> newInstance(A1 const& a1)
    {
    	Allocator<T> a;
    	T* newT = a.allocate(1);
    	::new (newT)T(a1);
    	return my_ptr<T>(newT);
    }
    
    template <class T, class A1, class A2>
    my_ptr<T> newInstance(A1 const& a1, A2 const& a2)
    {
    	Allocator<T> a;
    	T* newT = a.allocate(1);
    	::new (newT)T(a1, a2);
    	return my_ptr<T>(newT);
    }
    
    template <class T, class A1, class A2, class A3>
    my_ptr<T> newInstance(A1 const& a1, A2 const& a2, A3 const& a3)
    {
    	Allocator<T> a;
    	T* newT = a.allocate(1);
    	::new (newT)T(a1, a2, a3);
    	return my_ptr<T>(newT);
    }
    
    template <class T, class A1, class A2, class A3, class A4>
    my_ptr<T> newInstance(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4)
    {
    	Allocator<T> a;
    	T* newT = a.allocate(1);
    	::new (newT)T(a1, a2, a3, a4);
    	return my_ptr<T>(newT);
    }
    
    template <class T, class A1, class A2, class A3, class A4, class A5>
    my_ptr<T> newInstance(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5)
    {
    	Allocator<T> a;
    	T* newT = a.allocate(1);
    	::new (newT)T(a1, a2, a3, a4, a5);
    	return my_ptr<T>(newT);
    }
    
    template <class T, class A1, class A2, class A3, class A4, class A5, class A6>
    my_ptr<T> newInstance(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6)
    {
    	Allocator<T> a;
    	T* newT = a.allocate(1);
    	::new (newT)T(a1, a2, a3, a4, a5, a6);
    	return my_ptr<T>(newT);
    }
    
    template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    my_ptr<T> newInstance(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7)
    {
    	Allocator<T> a;
    	T* newT = a.allocate(1);
    	::new (newT)T(a1, a2, a3, a4, a5, a6, a7);
    	return my_ptr<T>(newT);
    }
    
    template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    my_ptr<T> newInstance(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7, A8 const& a8)
    {
    	Allocator<T> a;
    	T* newT = a.allocate(1);
    	::new (newT)T(a1, a2, a3, a4, a5, a6, a7, a8);
    	return my_ptr<T>(newT);
    }
    
    template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    my_ptr<T> newInstance(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7, A8 const& a8, A9 const& a9)
    {
    	Allocator<T> a;
    	T* newT = a.allocate(1);
    	::new (newT)T(a1, a2, a3, a4, a5, a6, a7, a8, a9);
    	return my_ptr<T>(newT);
    }
        
    template <class T>
    my_ptr<T> newLucene()
    {
        my_ptr<T> instance(newInstance<T>());
        instance->initialize();
        return instance;
    }
    
    template <class T, class A1>
    my_ptr<T> newLucene(A1 const& a1)
    {
        my_ptr<T> instance(newInstance<T>(a1));
        instance->initialize();
        return instance;
    }
    
    template <class T, class A1, class A2>
    my_ptr<T> newLucene(A1 const& a1, A2 const& a2)
    {
        my_ptr<T> instance(newInstance<T>(a1, a2));
        instance->initialize();
        return instance;
    }
    
    template <class T, class A1, class A2, class A3>
    my_ptr<T> newLucene(A1 const& a1, A2 const& a2, A3 const& a3)
    {
        my_ptr<T> instance(newInstance<T>(a1, a2, a3));
        instance->initialize();
        return instance;
    }
    
    template <class T, class A1, class A2, class A3, class A4>
    my_ptr<T> newLucene(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4)
    {
        my_ptr<T> instance(newInstance<T>(a1, a2, a3, a4));
        instance->initialize();
        return instance;
    }
    
    template <class T, class A1, class A2, class A3, class A4, class A5>
    my_ptr<T> newLucene(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5)
    {
        my_ptr<T> instance(newInstance<T>(a1, a2, a3, a4, a5));
        instance->initialize();
        return instance;
    }
    
    template <class T, class A1, class A2, class A3, class A4, class A5, class A6>
    my_ptr<T> newLucene(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6)
    {
        my_ptr<T> instance(newInstance<T>(a1, a2, a3, a4, a5, a6));
        instance->initialize();
        return instance;
    }
    
    template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    my_ptr<T> newLucene(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7)
    {
        my_ptr<T> instance(newInstance<T>(a1, a2, a3, a4, a5, a6, a7));
        instance->initialize();
        return instance;
    }
    
    template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    my_ptr<T> newLucene(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7, A8 const& a8)
    {
        my_ptr<T> instance(newInstance<T>(a1, a2, a3, a4, a5, a6, a7, a8));
        instance->initialize();
        return instance;
    }
    
    template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    my_ptr<T> newLucene(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7, A8 const& a8, A9 const& a9)
    {
        my_ptr<T> instance(newInstance<T>(a1, a2, a3, a4, a5, a6, a7, a8, a9));
        instance->initialize();
        return instance;
    }
}

#endif
