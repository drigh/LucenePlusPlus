#pragma once

#include <typeinfo>
#include <string>
#include <iostream>
#include <sstream>
#include <boost/smart_ptr/detail/atomic_count.hpp>

namespace Lucene
{

template <class T>
class TypedCounter
{
public:
	TypedCounter(const std::string& name): m_counter(0), m_nullCounter(0)
	{
		std::stringstream builder;
		builder << typeid(T*).name() << "::" << name;
		m_countername = builder.str();
	}

	void Increment(const T* ptr)
	{
		if (ptr) ++m_counter;
		else ++m_nullCounter;
	}

	~TypedCounter()
	{
		long count = m_counter;
		long nullCount = m_nullCounter;
		if (count || nullCount)
			std::cerr << "Counter " << m_countername << " value: " << count << " (" << nullCount << ")" << std::endl;
	}

private:
	std::string m_countername;
	boost::detail::atomic_count m_counter;
	boost::detail::atomic_count m_nullCounter;
};

}
