#pragma once

//////////////////////////////////////////////////////////////////////////
// construct.h

// (C) Copyright 2011-2012 Guardian. 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://code.google.com/p/iocplusplus/ for updates, documentation, and revision history.

#include <string>
#include <boost/mpl/range_c.hpp>
#include <boost/function.hpp>
#include <boost/unordered_map.hpp>

#include "signature.h"
#include "generators.h"
#include "dependency.h"

namespace ioc
{

//////////////////////////////////////////////////////////////////////////
// exceptions
class unregistred_type : public std::exception
{
public:
	unregistred_type(std::string name) : m_what("ioc++: no factory is registred for a type " + name) {}
	virtual const char * what() const { return m_what.c_str(); }
private:
	std::string m_what;
};

template<
	typename interface_type,
	typename A0 = boost::mpl::void_,
	typename A1 = boost::mpl::void_,
	typename A2 = boost::mpl::void_,
	typename A3 = boost::mpl::void_,
	typename A4 = boost::mpl::void_,
	typename A5 = boost::mpl::void_,
	typename A6 = boost::mpl::void_,
	typename A7 = boost::mpl::void_,
	typename A8 = boost::mpl::void_
	>
class factory
{
private:
	typedef typename detail::pack_args<boost::mpl::void_, A0, A1, A2, A3, A4, A5, A6, A7, A8>::output_args parameters;
	enum { placeholder_count = boost::mpl::size<parameters>::value };
	typedef typename boost::mpl::range_c<int, 1, placeholder_count + 1>::type placeholders;
	typedef typename boost::mpl::copy<placeholders, boost::mpl::back_inserter<boost::mpl::vector<>>>::type placeholders_repacked;
	typedef typename boost::mpl::transform<placeholders_repacked, detail::create_placeholder<parameters, boost::mpl::_1> >::type common_descriptors;
	typedef typename detail::signature_maker<interface_type, common_descriptors>::type signature;
	typedef typename boost::mpl::transform<common_descriptors, detail::create_placeholder_dependency<boost::mpl::_1> >::type common_dependencies;

public:
	template<typename T>
	void registerType(const std::string& name)
	{
		struct descriptor
		{
			typedef T type;
			typedef interface_type interface;
			typedef common_dependencies dependencies;
		};

		typedef typename detail::make_dependency<descriptor, placeholders_repacked>::type d;
		typedef detail::bind_type_resolver<
			typename descriptor::interface,
			typename d,
			placeholders_repacked,
			false,
			placeholder_count
		>::type bind_type;

		typedef detail::generate_resolver<
			typename d,
			bind_type,
			placeholders_repacked,
			placeholder_count
		> resolver_type;

		boost::function<signature> resolver = resolver_type::invoke();
		m_registry.insert(std::make_pair(name, resolver));
	}

	template<typename R>
	R resolve(const std::string& name) const
	{
		registry::const_iterator it = m_registry.find(name);
		if(it != m_registry.end())
			return it->second();

#ifndef IOC_NO_EXCEPTIONS
		throw unregistred_type(name);
#endif
		return 0;
	}

	template<typename R, typename A0>
	R resolve(const std::string& name, A0 a0) const
	{
		registry::const_iterator it = m_registry.find(name);
		if(it != m_registry.end())
			return it->second(a0);

#ifndef IOC_NO_EXCEPTIONS
		throw unregistred_type(name);
#endif
		return 0;
	}

	template<typename R, typename A0, typename A1>
	R resolve(const std::string& name, A0 a0, A1 a1) const
	{
		registry::const_iterator it = m_registry.find(name);
		if(it != m_registry.end())
			return it->second(a0, a1);

#ifndef IOC_NO_EXCEPTIONS
		throw unregistred_type(name);
#endif
		return 0;
	}

	template<typename R, typename A0, typename A1, typename A2>
	R resolve(const std::string& name, A0 a0, A1 a1, A2 a2) const
	{
		registry::const_iterator it = m_registry.find(name);
		if(it != m_registry.end())
			return it->second(a0, a1, a2);

#ifndef IOC_NO_EXCEPTIONS
		throw unregistred_type(name);
#endif
		return 0;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3>
	R resolve(const std::string& name, A0 a0, A1 a1, A2 a2, A3 a3) const
	{
		registry::const_iterator it = m_registry.find(name);
		if(it != m_registry.end())
			return it->second(a0, a1, a2, a3);

#ifndef IOC_NO_EXCEPTIONS
		throw unregistred_type(name);
#endif
		return 0;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4>
	R resolve(const std::string& name, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4) const
	{
		registry::const_iterator it = m_registry.find(name);
		if(it != m_registry.end())
			return it->second(a0, a1, a2, a3, a4);

#ifndef IOC_NO_EXCEPTIONS
		throw unregistred_type(name);
#endif
		return 0;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
	R resolve(const std::string& name, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
	{
		registry::const_iterator it = m_registry.find(name);
		if(it != m_registry.end())
			return it->second(a0, a1, a2, a3, a4, a5);

#ifndef IOC_NO_EXCEPTIONS
		throw unregistred_type(name);
#endif
		return 0;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
	R resolve(const std::string& name, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
	{
		registry::const_iterator it = m_registry.find(name);
		if(it != m_registry.end())
			return it->second(a0, a1, a2, a3, a4, a5, a6);

#ifndef IOC_NO_EXCEPTIONS
		throw unregistred_type(name);
#endif
		return 0;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
	R resolve(const std::string& name, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
	{
		registry::const_iterator it = m_registry.find(name);
		if(it != m_registry.end())
			return it->second(a0, a1, a2, a3, a4, a5, a6, a7);

#ifndef IOC_NO_EXCEPTIONS
		throw unregistred_type(name);
#endif
		return 0;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
	R resolve(const std::string& name, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
	{
		registry::const_iterator it = m_registry.find(name);
		if(it != m_registry.end())
			return it->second(a0, a1, a2, a3, a4, a5, a6, a7, a8);

#ifndef IOC_NO_EXCEPTIONS
		throw unregistred_type(name);
#endif
		return 0;
	}


private:
	typedef boost::function<signature> type_factory;
	typedef boost::unordered_map<std::string, type_factory> registry;
	registry m_registry;
};

}