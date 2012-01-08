#pragma once

//////////////////////////////////////////////////////////////////////////
// container.h

// (C) Copyright 2011-2012 Guardian. 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://code.google.com/p/iocplusplus/ for updates, documentation, and revision history.

#include <boost/mpl/range_c.hpp>
#include <boost/any.hpp>
#include <boost/function.hpp>
#include <boost/unordered_map.hpp>

#include "generators.h"
#include "dependency.h"

namespace ioc
{

//////////////////////////////////////////////////////////////////////////
// container

class any_map
{
public:
	void insert(const char* name, boost::any resolver)
	{
		container.insert(std::make_pair(name, resolver));
	}

	boost::any get(const char* name) const
	{
		boost::unordered_map<std::string, boost::any>::const_iterator it = container.find(name);
		if(it != container.end())
			return it->second;
		return boost::any();
	}
private:
	boost::unordered_map<std::string, boost::any> container;
};

class container
{
public:
	template<typename descriptor, typename register_type, int placeholder_count, typename signature>
	void registerType()
	{
		typedef boost::mpl::range_c<int, 1, placeholder_count + 1>::type placeholders;
		enum { dependencies_count = boost::mpl::size<typename descriptor::dependencies>::value };
		typedef typename detail::make_dependency<descriptor, placeholders>::type d;
		typedef detail::bind_type_resolver<
			typename descriptor::interface,
			typename d,
			placeholders,
			false,
			dependencies_count
		>::type bind_type;

		typedef detail::generate_resolver<
			typename d,
			bind_type,
			placeholders,
			dependencies_count
		> resolver_type;

		boost::function<signature> resolver =
			resolver_type::invoke();
		m_resolvers.insert(typeid(register_type).name(), resolver);
	}

	template<typename descriptor, int placeholder_count, typename signature>
	void registerType()
	{
		registerType<descriptor, descriptor::type, placeholder_count, signature>();
	}

	template <typename T, typename signature>
	void registerFactory(const boost::function<signature>& binded_factory)
	{
		m_resolvers.insert(typeid(T).name(), binded_factory);
	}

	// TODO: add macro IOC_NO_EXCEPTIONS
	// TODO: catch bad_any_cast and throw invalid_argument_type
	// TODO: throw unregistred_type when resolver is empty
	template<typename R>
	R* resolve() const
	{
		boost::any resolver = m_resolvers.get(typeid(R).name());
		if(!resolver.empty())
			return boost::any_cast< boost::function<R* ()> >(resolver)();
		return 0;
	}

	template<typename R, typename A0>
	R* resolve(A0 a0) const
	{
		boost::any resolver = m_resolvers.get(typeid(R).name());
		if(!resolver.empty())
			return boost::any_cast< boost::function<R* (A0)> >(resolver)(a0);
		return 0;
	}

	template<typename R, typename A0, typename A1>
	R* resolve(A0 a0, A1 a1) const
	{
		boost::any resolver = m_resolvers.get(typeid(R).name());
		if(!resolver.empty())
			return boost::any_cast< boost::function<R* (A0, A1)> >(resolver)(a0, a1);
		return 0;
	}

	template<typename R, typename A0, typename A1, typename A2>
	R* resolve(A0 a0, A1 a1, A2 a2) const
	{
		boost::any resolver = m_resolvers.get(typeid(R).name());
		if(!resolver.empty())
			return boost::any_cast< boost::function<R* (A0, A1, A2)> >(resolver)(a0, a1, a2);
		return 0;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3>
	R* resolve(A0 a0, A1 a1, A2 a2, A3 a3) const
	{
		boost::any resolver = m_resolvers.get(typeid(R).name());
		if(!resolver.empty())
			return boost::any_cast< boost::function<R* (A0, A1, A2, A3)> >(resolver)(a0, a1, a2, a3);
		return 0;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4>
	R* resolve(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4) const
	{
		boost::any resolver = m_resolvers.get(typeid(R).name());
		if(!resolver.empty())
			return boost::any_cast< boost::function<R* (A0, A1, A2, A3, A4)> >(resolver)(a0, a1, a2, a3, a4);
		return 0;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
	R* resolve(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
	{
		boost::any resolver = m_resolvers.get(typeid(R).name());
		if(!resolver.empty())
			return boost::any_cast< boost::function<R* (A0, A1, A2, A3, A4, A5)> >(resolver)(a0, a1, a2, a3, a4, a5);
		return 0;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
	R* resolve(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
	{
		boost::any resolver = m_resolvers.get(typeid(R).name());
		if(!resolver.empty())
			return boost::any_cast< boost::function<R* (A0, A1, A2, A3, A4, A5, A6)> >(resolver)(a0, a1, a2, a3, a4, a5, a6);
		return 0;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
	R* resolve(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
	{
		boost::any resolver = m_resolvers.get(typeid(R).name());
		if(!resolver.empty())
			return boost::any_cast< boost::function<R* (A0, A1, A2, A3, A4, A5, A6, A7)> >(resolver)(a0, a1, a2, a3, a4, a5, a6, a7);
		return 0;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
	R* resolve(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
	{
		boost::any resolver = m_resolvers.get(typeid(R).name());
		if(!resolver.empty())
			return boost::any_cast< boost::function<R* (A0, A1, A2, A3, A4, A5, A6, A7, A8)> >(resolver)(a0, a1, a2, a3, a4, a5, a6, a7, a8);
		return 0;
	}

	template<typename R>
	boost::shared_ptr<R> resolve_shared() const
	{
		boost::any resolver = m_resolvers.get(typeid(R).name());
		if(!resolver.empty())
			return boost::any_cast< boost::function<boost::shared_ptr<R> ()> >(resolver)();
		return boost::shared_ptr<R>();
	}

	template<typename R, typename A0>
	boost::shared_ptr<R> resolve_shared(A0 a0) const
	{
		boost::any resolver = m_resolvers.get(typeid(R).name());
		if(!resolver.empty())
			return boost::any_cast< boost::function<boost::shared_ptr<R> (A0)> >(resolver)(a0);
		return boost::shared_ptr<R>();
	}

	template<typename R, typename A0, typename A1>
	boost::shared_ptr<R> resolve_shared(A0 a0, A1 a1) const
	{
		boost::any resolver = m_resolvers.get(typeid(R).name());
		if(!resolver.empty())
			return boost::any_cast< boost::function<boost::shared_ptr<R> (A0, A1)> >(resolver)(a0, a1);
		return boost::shared_ptr<R>();
	}

	template<typename R, typename A0, typename A1, typename A2>
	boost::shared_ptr<R> resolve_shared(A0 a0, A1 a1, A2 a2) const
	{
		boost::any resolver = m_resolvers.get(typeid(R).name());
		if(!resolver.empty())
			return boost::any_cast< boost::function<boost::shared_ptr<R> (A0, A1, A2)> >(resolver)(a0, a1, a2);
		return boost::shared_ptr<R>();
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3>
	boost::shared_ptr<R> resolve_shared(A0 a0, A1 a1, A2 a2, A3 a3) const
	{
		boost::any resolver = m_resolvers.get(typeid(R).name());
		if(!resolver.empty())
			return boost::any_cast< boost::function<boost::shared_ptr<R> (A0, A1, A2, A3)> >(resolver)(a0, a1, a2, a3);
		return boost::shared_ptr<R>();
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4>
	boost::shared_ptr<R> resolve_shared(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4) const
	{
		boost::any resolver = m_resolvers.get(typeid(R).name());
		if(!resolver.empty())
			return boost::any_cast< boost::function<boost::shared_ptr<R> (A0, A1, A2, A3, A4)> >(resolver)(a0, a1, a2, a3, a4);
		return boost::shared_ptr<R>();
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
	boost::shared_ptr<R> resolve_shared(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
	{
		boost::any resolver = m_resolvers.get(typeid(R).name());
		if(!resolver.empty())
			return boost::any_cast< boost::function<boost::shared_ptr<R> (A0, A1, A2, A3, A4, A5)> >(resolver)(a0, a1, a2, a3, a4, a5);
		return boost::shared_ptr<R>();
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
	boost::shared_ptr<R> resolve_shared(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
	{
		boost::any resolver = m_resolvers.get(typeid(R).name());
		if(!resolver.empty())
			return boost::any_cast< boost::function<boost::shared_ptr<R> (A0, A1, A2, A3, A4, A5, A6)> >(resolver)(a0, a1, a2, a3, a4, a5, a6);
		return boost::shared_ptr<R>();
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
	boost::shared_ptr<R> resolve_shared(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
	{
		boost::any resolver = m_resolvers.get(typeid(R).name());
		if(!resolver.empty())
			return boost::any_cast< boost::function<boost::shared_ptr<R> (A0, A1, A2, A3, A4, A5, A6, A7)> >(resolver)(a0, a1, a2, a3, a4, a5, a6, a7);
		return boost::shared_ptr<R>();
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
	boost::shared_ptr<R> resolve_shared(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
	{
		boost::any resolver = m_resolvers.get(typeid(R).name());
		if(!resolver.empty())
			return boost::any_cast< boost::function<boost::shared_ptr<R> (A0, A1, A2, A3, A4, A5, A6, A7, A8)> >(resolver)(a0, a1, a2, a3, a4, a5, a6, a7, a8);
		return boost::shared_ptr<R>();
	}

private:
	any_map m_resolvers;
};

}