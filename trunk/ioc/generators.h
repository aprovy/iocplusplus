#pragma once

//////////////////////////////////////////////////////////////////////////
// generators.h

// (C) Copyright 2011-2012 Guardian. 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://code.google.com/p/iocplusplus/ for updates, documentation, and revision history.

#include <boost/mpl/comparison.hpp>

#include "construct.h"
#include "dependency_type.h"
#include "bind_or_call.h"

namespace ioc
{
namespace detail
{
// forward declaration
template<typename dependency, typename bind_type, typename placeholders, int dependency_count>
struct generate_resolver;

//////////////////////////////////////////////////////////////////////////
// helper

template <typename parent_dependency, int index, typename placeholders>
struct unpack_dependency
{
	// get parent descriptor
	typedef typename parent_dependency::descriptor parent_descriptor;
	// extract dependency
	typedef typename boost::mpl::at_c<typename parent_descriptor::dependencies, index>::type dependency;
	// get a placeholders that are used in the dependency
	typedef typename dependency::placeholders used_placeholders;
	// extract descriptor
	typedef typename dependency::descriptor dependency_descriptor;
	// get dependency children count
	enum { dependency_count = boost::mpl::size<typename dependency_descriptor::dependencies>::value };
	// get the dependency construct type
	typedef typename dependency_descriptor::type construct_type;
	typedef typename dependency_descriptor::interface interface_type;
	// test if the dependency construct type is a placeholder
	enum { is_placeholder = boost::is_placeholder<construct_type>::value };

	// transform from passed to used
	typedef typename remap_placeholders<
		placeholders,
		used_placeholders,
		boost::mpl::size<used_placeholders>::value == 0
	>::type dependency_placeholders;
	// dependency bind type
	typedef typename bind_type_resolver<
		typename boost::mpl::if_c<
			is_placeholder != 0,
			typename get_placeholder_type<placeholders, construct_type>::type,
			interface_type
		>::type,
		dependency,
		dependency_placeholders,
		is_placeholder != 0,
		dependency_count
	>::type bind_type_param;
	// the dependency resolver type
	typedef generate_resolver<dependency, bind_type_param, dependency_placeholders, dependency_count> generate_resolver_type;
};

//////////////////////////////////////////////////////////////////////////
// generators

template<typename dependency, typename bind_type, typename placeholders, int dependency_count>
struct generate_resolver
{
	static bind_type invoke();
};

template<typename dependency, typename bind_type, typename placeholders>
struct generate_resolver<dependency, bind_type, placeholders, 0>
{
	typedef typename dependency::descriptor::type construct_type;
	typedef typename dependency::descriptor::interface interface_type;
	static bind_type invoke() 
	{
		return boost::bind(&construct0<interface_type, construct_type>::invoke);
	}
};

template<typename dependency, typename bind_type, typename placeholders>
struct generate_resolver<dependency, bind_type, placeholders, 1>
{
	typedef typename dependency::descriptor::type construct_type;
	typedef typename dependency::descriptor::interface interface_type;
	static bind_type invoke() 
	{
		typedef unpack_dependency<dependency, 0, placeholders> d0;
		return boost::bind(
			&construct1<interface_type, construct_type, typename d0::interface_type>::invoke,
			bind_or_call<typename d0::bind_type_param, typename d0::generate_resolver_type, d0::is_placeholder != 0>::resolve()
			);
	}
};

template<typename dependency, typename bind_type, typename placeholders>
struct generate_resolver<dependency, bind_type, placeholders, 2>
{
	typedef typename dependency::descriptor::type construct_type;
	typedef typename dependency::descriptor::interface interface_type;
	static bind_type invoke() 
	{
		typedef unpack_dependency<dependency, 0, placeholders> d0;
		typedef unpack_dependency<dependency, 1, placeholders> d1;
		return boost::bind(
			&construct2<interface_type, construct_type, typename d0::interface_type, typename d1::interface_type>::invoke,
			bind_or_call<typename d0::bind_type_param, typename d0::generate_resolver_type, d0::is_placeholder != 0>::resolve(),
			bind_or_call<typename d1::bind_type_param, typename d1::generate_resolver_type, d1::is_placeholder != 0>::resolve()
			);
	}
};

template<typename dependency, typename bind_type, typename placeholders>
struct generate_resolver<dependency, bind_type, placeholders, 3>
{
	typedef typename dependency::descriptor::type construct_type;
	typedef typename dependency::descriptor::interface interface_type;
	static bind_type invoke() 
	{
		typedef unpack_dependency<dependency, 0, placeholders> d0;
		typedef unpack_dependency<dependency, 1, placeholders> d1;
		typedef unpack_dependency<dependency, 2, placeholders> d2;
		return boost::bind(
			&construct3<interface_type, construct_type, typename d0::interface_type, typename d1::interface_type, typename d2::interface_type>::invoke,
			bind_or_call<typename d0::bind_type_param, typename d0::generate_resolver_type, d0::is_placeholder != 0>::resolve(),
			bind_or_call<typename d1::bind_type_param, typename d1::generate_resolver_type, d1::is_placeholder != 0>::resolve(),
			bind_or_call<typename d2::bind_type_param, typename d2::generate_resolver_type, d2::is_placeholder != 0>::resolve()
			);
	}
};

template<typename dependency, typename bind_type, typename placeholders>
struct generate_resolver<dependency, bind_type, placeholders, 4>
{
	typedef typename dependency::descriptor::type construct_type;
	typedef typename dependency::descriptor::interface interface_type;
	static bind_type invoke() 
	{
		typedef unpack_dependency<dependency, 0, placeholders> d0;
		typedef unpack_dependency<dependency, 1, placeholders> d1;
		typedef unpack_dependency<dependency, 2, placeholders> d2;
		typedef unpack_dependency<dependency, 3, placeholders> d3;
		return boost::bind(
			&construct4<interface_type, construct_type, typename d0::interface_type, typename d1::interface_type, typename d2::interface_type, typename d3::interface_type>::invoke,
			bind_or_call<typename d0::bind_type_param, typename d0::generate_resolver_type, d0::is_placeholder != 0>::resolve(),
			bind_or_call<typename d1::bind_type_param, typename d1::generate_resolver_type, d1::is_placeholder != 0>::resolve(),
			bind_or_call<typename d2::bind_type_param, typename d2::generate_resolver_type, d2::is_placeholder != 0>::resolve(),
			bind_or_call<typename d3::bind_type_param, typename d3::generate_resolver_type, d3::is_placeholder != 0>::resolve()
			);
	}
};

template<typename dependency, typename bind_type, typename placeholders>
struct generate_resolver<dependency, bind_type, placeholders, 5>
{
	typedef typename dependency::descriptor::type construct_type;
	typedef typename dependency::descriptor::interface interface_type;
	static bind_type invoke() 
	{
		typedef unpack_dependency<dependency, 0, placeholders> d0;
		typedef unpack_dependency<dependency, 1, placeholders> d1;
		typedef unpack_dependency<dependency, 2, placeholders> d2;
		typedef unpack_dependency<dependency, 3, placeholders> d3;
		typedef unpack_dependency<dependency, 4, placeholders> d4;
		return boost::bind(
			&construct5<interface_type, construct_type, typename d0::interface_type, typename d1::interface_type, typename d2::interface_type, typename d3::interface_type, typename d4::interface_type>::invoke,
			bind_or_call<typename d0::bind_type_param, typename d0::generate_resolver_type, d0::is_placeholder != 0>::resolve(),
			bind_or_call<typename d1::bind_type_param, typename d1::generate_resolver_type, d1::is_placeholder != 0>::resolve(),
			bind_or_call<typename d2::bind_type_param, typename d2::generate_resolver_type, d2::is_placeholder != 0>::resolve(),
			bind_or_call<typename d3::bind_type_param, typename d3::generate_resolver_type, d3::is_placeholder != 0>::resolve(),
			bind_or_call<typename d4::bind_type_param, typename d4::generate_resolver_type, d4::is_placeholder != 0>::resolve()
			);
	}
};

template<typename dependency, typename bind_type, typename placeholders>
struct generate_resolver<dependency, bind_type, placeholders, 6>
{
	typedef typename dependency::descriptor::type construct_type;
	typedef typename dependency::descriptor::interface interface_type;
	static bind_type invoke() 
	{
		typedef unpack_dependency<dependency, 0, placeholders> d0;
		typedef unpack_dependency<dependency, 1, placeholders> d1;
		typedef unpack_dependency<dependency, 2, placeholders> d2;
		typedef unpack_dependency<dependency, 3, placeholders> d3;
		typedef unpack_dependency<dependency, 4, placeholders> d4;
		typedef unpack_dependency<dependency, 5, placeholders> d5;
		return boost::bind(
			&construct6<interface_type, construct_type, typename d0::interface_type, typename d1::interface_type, typename d2::interface_type, typename d3::interface_type, typename d4::interface_type, typename d5::interface_type>::invoke,
			bind_or_call<typename d0::bind_type_param, typename d0::generate_resolver_type, d0::is_placeholder != 0>::resolve(),
			bind_or_call<typename d1::bind_type_param, typename d1::generate_resolver_type, d1::is_placeholder != 0>::resolve(),
			bind_or_call<typename d2::bind_type_param, typename d2::generate_resolver_type, d2::is_placeholder != 0>::resolve(),
			bind_or_call<typename d3::bind_type_param, typename d3::generate_resolver_type, d3::is_placeholder != 0>::resolve(),
			bind_or_call<typename d4::bind_type_param, typename d4::generate_resolver_type, d4::is_placeholder != 0>::resolve(),
			bind_or_call<typename d5::bind_type_param, typename d5::generate_resolver_type, d5::is_placeholder != 0>::resolve()
			);
	}
};

template<typename dependency, typename bind_type, typename placeholders>
struct generate_resolver<dependency, bind_type, placeholders, 7>
{
	typedef typename dependency::descriptor::type construct_type;
	typedef typename dependency::descriptor::interface interface_type;
	static bind_type invoke() 
	{
		typedef unpack_dependency<dependency, 0, placeholders> d0;
		typedef unpack_dependency<dependency, 1, placeholders> d1;
		typedef unpack_dependency<dependency, 2, placeholders> d2;
		typedef unpack_dependency<dependency, 3, placeholders> d3;
		typedef unpack_dependency<dependency, 4, placeholders> d4;
		typedef unpack_dependency<dependency, 5, placeholders> d5;
		typedef unpack_dependency<dependency, 6, placeholders> d6;
		return boost::bind(
			&construct7<interface_type, construct_type, typename d0::interface_type, typename d1::interface_type, typename d2::interface_type, typename d3::interface_type, typename d4::interface_type, typename d5::interface_type, typename d6::interface_type>::invoke,
			bind_or_call<typename d0::bind_type_param, typename d0::generate_resolver_type, d0::is_placeholder != 0>::resolve(),
			bind_or_call<typename d1::bind_type_param, typename d1::generate_resolver_type, d1::is_placeholder != 0>::resolve(),
			bind_or_call<typename d2::bind_type_param, typename d2::generate_resolver_type, d2::is_placeholder != 0>::resolve(),
			bind_or_call<typename d3::bind_type_param, typename d3::generate_resolver_type, d3::is_placeholder != 0>::resolve(),
			bind_or_call<typename d4::bind_type_param, typename d4::generate_resolver_type, d4::is_placeholder != 0>::resolve(),
			bind_or_call<typename d5::bind_type_param, typename d5::generate_resolver_type, d5::is_placeholder != 0>::resolve(),
			bind_or_call<typename d6::bind_type_param, typename d6::generate_resolver_type, d6::is_placeholder != 0>::resolve()
			);
	}
};

template<typename dependency, typename bind_type, typename placeholders>
struct generate_resolver<dependency, bind_type, placeholders, 8>
{
	typedef typename dependency::descriptor::type construct_type;
	typedef typename dependency::descriptor::interface interface_type;
	static bind_type invoke() 
	{
		typedef unpack_dependency<dependency, 0, placeholders> d0;
		typedef unpack_dependency<dependency, 1, placeholders> d1;
		typedef unpack_dependency<dependency, 2, placeholders> d2;
		typedef unpack_dependency<dependency, 3, placeholders> d3;
		typedef unpack_dependency<dependency, 4, placeholders> d4;
		typedef unpack_dependency<dependency, 5, placeholders> d5;
		typedef unpack_dependency<dependency, 6, placeholders> d6;
		typedef unpack_dependency<dependency, 7, placeholders> d7;
		return boost::bind(
			&construct8<interface_type, construct_type, typename d0::interface_type, typename d1::interface_type, typename d2::interface_type, typename d3::interface_type, typename d4::interface_type, typename d5::interface_type, typename d6::interface_type, typename d7::interface_type>::invoke,
			bind_or_call<typename d0::bind_type_param, typename d0::generate_resolver_type, d0::is_placeholder != 0>::resolve(),
			bind_or_call<typename d1::bind_type_param, typename d1::generate_resolver_type, d1::is_placeholder != 0>::resolve(),
			bind_or_call<typename d2::bind_type_param, typename d2::generate_resolver_type, d2::is_placeholder != 0>::resolve(),
			bind_or_call<typename d3::bind_type_param, typename d3::generate_resolver_type, d3::is_placeholder != 0>::resolve(),
			bind_or_call<typename d4::bind_type_param, typename d4::generate_resolver_type, d4::is_placeholder != 0>::resolve(),
			bind_or_call<typename d5::bind_type_param, typename d5::generate_resolver_type, d5::is_placeholder != 0>::resolve(),
			bind_or_call<typename d6::bind_type_param, typename d6::generate_resolver_type, d6::is_placeholder != 0>::resolve(),
			bind_or_call<typename d7::bind_type_param, typename d7::generate_resolver_type, d7::is_placeholder != 0>::resolve()
			);
	}
};

template<typename dependency, typename bind_type, typename placeholders>
struct generate_resolver<dependency, bind_type, placeholders, 9>
{
	typedef typename dependency::descriptor::type construct_type;
	typedef typename dependency::descriptor::interface interface_type;
	static bind_type invoke() 
	{
		typedef unpack_dependency<dependency, 0, placeholders> d0;
		typedef unpack_dependency<dependency, 1, placeholders> d1;
		typedef unpack_dependency<dependency, 2, placeholders> d2;
		typedef unpack_dependency<dependency, 3, placeholders> d3;
		typedef unpack_dependency<dependency, 4, placeholders> d4;
		typedef unpack_dependency<dependency, 5, placeholders> d5;
		typedef unpack_dependency<dependency, 6, placeholders> d6;
		typedef unpack_dependency<dependency, 7, placeholders> d7;
		typedef unpack_dependency<dependency, 8, placeholders> d8;
		return boost::bind(
			&construct9<interface_type, construct_type, typename d0::interface_type, typename d1::interface_type, typename d2::interface_type, typename d3::interface_type, typename d4::interface_type, typename d5::interface_type, typename d6::interface_type, typename d7::interface_type, typename d8::interface_type>::invoke,
			bind_or_call<typename d0::bind_type_param, typename d0::generate_resolver_type, d0::is_placeholder != 0>::resolve(),
			bind_or_call<typename d1::bind_type_param, typename d1::generate_resolver_type, d1::is_placeholder != 0>::resolve(),
			bind_or_call<typename d2::bind_type_param, typename d2::generate_resolver_type, d2::is_placeholder != 0>::resolve(),
			bind_or_call<typename d3::bind_type_param, typename d3::generate_resolver_type, d3::is_placeholder != 0>::resolve(),
			bind_or_call<typename d4::bind_type_param, typename d4::generate_resolver_type, d4::is_placeholder != 0>::resolve(),
			bind_or_call<typename d5::bind_type_param, typename d5::generate_resolver_type, d5::is_placeholder != 0>::resolve(),
			bind_or_call<typename d6::bind_type_param, typename d6::generate_resolver_type, d6::is_placeholder != 0>::resolve(),
			bind_or_call<typename d7::bind_type_param, typename d7::generate_resolver_type, d7::is_placeholder != 0>::resolve(),
			bind_or_call<typename d8::bind_type_param, typename d8::generate_resolver_type, d8::is_placeholder != 0>::resolve()
			);
	}
};
}
}