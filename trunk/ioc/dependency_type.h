#pragma once

//////////////////////////////////////////////////////////////////////////
// dependency_type.h

// (C) Copyright 2011-2012 Guardian. 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://code.google.com/p/iocplusplus/ for updates, documentation, and revision history.

#include <boost/mpl/vector.hpp>
#include <boost/mpl/size.hpp>

#include <boost/bind.hpp>

#include "placeholders.h"

namespace ioc
{
namespace detail
{
//forward declaration
template <typename return_type, typename dependency, typename placeholders, bool is_placeholder, int dependency_count>
struct bind_type_resolver;
//////////////////////////////////////////////////////////////////////////
// helper
template<typename parent_dependency, int index>
struct unpack_dependency_type
{
	typedef typename parent_dependency::descriptor parent_descriptor;
	typedef typename boost::mpl::at_c<typename parent_descriptor::dependencies, index>::type dependency;
	typedef typename dependency::descriptor::interface interface_type;
	typedef typename dependency::placeholders used_placeholders;
	enum {is_placeholder = boost::is_placeholder<typename dependency::descriptor::type>::value };
};

//////////////////////////////////////////////////////////////////////////
// dependency type resolver

// select between binded type and placeholder value type
template <typename dependency, typename placeholders, typename used_placeholders, bool is_placeholder>
struct dependency_type_resolver
{
	enum { dependency_count = boost::mpl::size<typename dependency::descriptor::dependencies>::value };
	typedef typename remap_placeholders<placeholders, used_placeholders, boost::mpl::size<used_placeholders>::value == 0>::type dependency_placeholders;
	typedef typename bind_type_resolver<typename dependency::descriptor::interface, dependency, dependency_placeholders, false, dependency_count>::type type;
};

template <typename dependency, typename placeholders, typename used_placeholders>
struct dependency_type_resolver<dependency, placeholders, used_placeholders, true>
{
	typedef typename get_placeholder_type<placeholders, typename dependency::descriptor::type>::type type; // special case for a placeholder [used from bind_type_resolver]
};
//////////////////////////////////////////////////////////////////////////
// bind_type_resolver
template <typename return_type, typename dependency, typename placeholders>
struct bind_type_resolver<return_type, dependency, placeholders, true, 0>
{
	// can't use get_placeholder_type because placeholders is for the dependency, not for a parent
	typedef return_type type; // special case for a placeholder [used from generate_resolver()]
};

template <typename return_type, typename dependency, typename placeholders>
struct bind_type_resolver<return_type, dependency, placeholders, false, 0>
{
	typedef return_type (signature)();
	typedef
		boost::_bi::bind_t<
			return_type,
			signature*,
			boost::_bi::list0
		> type;
};

template <typename return_type, typename dependency, typename placeholders>
struct bind_type_resolver<return_type, dependency, placeholders, false, 1>
{
	typedef unpack_dependency_type<dependency, 0> d0;
	typedef return_type (signature)(typename d0::interface_type);
	typedef
		boost::_bi::bind_t<
			return_type,
			signature*,
			boost::_bi::list1<
				typename dependency_type_resolver<typename d0::dependency, placeholders, typename d0::used_placeholders, d0::is_placeholder != 0>::type
			>
		> type;
};

template <typename return_type, typename dependency, typename placeholders>
struct bind_type_resolver<return_type, dependency, placeholders, false, 2>
{
	typedef unpack_dependency_type<dependency, 0> d0;
	typedef unpack_dependency_type<dependency, 1> d1;
	typedef return_type (signature)(typename d0::interface_type, typename d1::interface_type);
	typedef
		boost::_bi::bind_t<
			return_type,
			signature*,
			boost::_bi::list2<
				typename dependency_type_resolver<typename d0::dependency, placeholders, typename d0::used_placeholders, d0::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d1::dependency, placeholders, typename d1::used_placeholders, d1::is_placeholder != 0>::type
			>
		> type;
};

template <typename return_type, typename dependency, typename placeholders>
struct bind_type_resolver<return_type, dependency, placeholders, false, 3>
{
	typedef unpack_dependency_type<dependency, 0> d0;
	typedef unpack_dependency_type<dependency, 1> d1;
	typedef unpack_dependency_type<dependency, 2> d2;
	typedef return_type (signature)(typename d0::interface_type, typename d1::interface_type, typename d2::interface_type);
	typedef
		boost::_bi::bind_t<
			return_type,
			signature*,
			boost::_bi::list3<
				typename dependency_type_resolver<typename d0::dependency, placeholders, typename d0::used_placeholders, d0::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d1::dependency, placeholders, typename d1::used_placeholders, d1::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d2::dependency, placeholders, typename d2::used_placeholders, d2::is_placeholder != 0>::type
			>
		> type;
};

template <typename return_type, typename dependency, typename placeholders>
struct bind_type_resolver<return_type, dependency, placeholders, false, 4>
{
	typedef unpack_dependency_type<dependency, 0> d0;
	typedef unpack_dependency_type<dependency, 1> d1;
	typedef unpack_dependency_type<dependency, 2> d2;
	typedef unpack_dependency_type<dependency, 3> d3;
	typedef return_type (signature)(typename d0::interface_type, typename d1::interface_type, typename d2::interface_type, typename d3::interface_type);
	typedef
		boost::_bi::bind_t<
			return_type,
			signature*,
			boost::_bi::list4<
				typename dependency_type_resolver<typename d0::dependency, placeholders, typename d0::used_placeholders, d0::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d1::dependency, placeholders, typename d1::used_placeholders, d1::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d2::dependency, placeholders, typename d2::used_placeholders, d2::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d3::dependency, placeholders, typename d3::used_placeholders, d3::is_placeholder != 0>::type
			>
		> type;
};

template <typename return_type, typename dependency, typename placeholders>
struct bind_type_resolver<return_type, dependency, placeholders, false, 5>
{
	typedef unpack_dependency_type<dependency, 0> d0;
	typedef unpack_dependency_type<dependency, 1> d1;
	typedef unpack_dependency_type<dependency, 2> d2;
	typedef unpack_dependency_type<dependency, 3> d3;
	typedef unpack_dependency_type<dependency, 4> d4;
	typedef return_type (signature)(typename d0::interface_type, typename d1::interface_type, typename d2::interface_type, typename d3::interface_type, typename d4::interface_type);
	typedef
		boost::_bi::bind_t<
			return_type,
			signature*,
			boost::_bi::list5<
				typename dependency_type_resolver<typename d0::dependency, placeholders, typename d0::used_placeholders, d0::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d1::dependency, placeholders, typename d1::used_placeholders, d1::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d2::dependency, placeholders, typename d2::used_placeholders, d2::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d3::dependency, placeholders, typename d3::used_placeholders, d3::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d4::dependency, placeholders, typename d4::used_placeholders, d4::is_placeholder != 0>::type
			>
		> type;
};

template <typename return_type, typename dependency, typename placeholders>
struct bind_type_resolver<return_type, dependency, placeholders, false, 6>
{
	typedef unpack_dependency_type<dependency, 0> d0;
	typedef unpack_dependency_type<dependency, 1> d1;
	typedef unpack_dependency_type<dependency, 2> d2;
	typedef unpack_dependency_type<dependency, 3> d3;
	typedef unpack_dependency_type<dependency, 4> d4;
	typedef unpack_dependency_type<dependency, 5> d5;
	typedef return_type (signature)(typename d0::interface_type, typename d1::interface_type, typename d2::interface_type, typename d3::interface_type, typename d4::interface_type, typename d5::interface_type);
	typedef
			boost::_bi::bind_t<
			return_type,
			signature*,
			boost::_bi::list6<
				typename dependency_type_resolver<typename d0::dependency, placeholders, typename d0::used_placeholders, d0::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d1::dependency, placeholders, typename d1::used_placeholders, d1::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d2::dependency, placeholders, typename d2::used_placeholders, d2::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d3::dependency, placeholders, typename d3::used_placeholders, d3::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d4::dependency, placeholders, typename d4::used_placeholders, d4::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d5::dependency, placeholders, typename d5::used_placeholders, d5::is_placeholder != 0>::type
			>
		> type;
};

template <typename return_type, typename dependency, typename placeholders>
struct bind_type_resolver<return_type, dependency, placeholders, false, 7>
{
	typedef unpack_dependency_type<dependency, 0> d0;
	typedef unpack_dependency_type<dependency, 1> d1;
	typedef unpack_dependency_type<dependency, 2> d2;
	typedef unpack_dependency_type<dependency, 3> d3;
	typedef unpack_dependency_type<dependency, 4> d4;
	typedef unpack_dependency_type<dependency, 5> d5;
	typedef unpack_dependency_type<dependency, 6> d6;
	typedef return_type (signature)(typename d0::interface_type, typename d1::interface_type, typename d2::interface_type, typename d3::interface_type, typename d4::interface_type, typename d5::interface_type, typename d6::interface_type);
	typedef
		boost::_bi::bind_t<
			return_type,
			signature*,
			boost::_bi::list7<
				typename dependency_type_resolver<typename d0::dependency, placeholders, typename d0::used_placeholders, d0::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d1::dependency, placeholders, typename d1::used_placeholders, d1::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d2::dependency, placeholders, typename d2::used_placeholders, d2::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d3::dependency, placeholders, typename d3::used_placeholders, d3::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d4::dependency, placeholders, typename d4::used_placeholders, d4::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d5::dependency, placeholders, typename d5::used_placeholders, d5::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d6::dependency, placeholders, typename d6::used_placeholders, d6::is_placeholder != 0>::type
			>
		> type;
};

template <typename return_type, typename dependency, typename placeholders>
struct bind_type_resolver<return_type, dependency, placeholders, false, 8>
{
	typedef unpack_dependency_type<dependency, 0> d0;
	typedef unpack_dependency_type<dependency, 1> d1;
	typedef unpack_dependency_type<dependency, 2> d2;
	typedef unpack_dependency_type<dependency, 3> d3;
	typedef unpack_dependency_type<dependency, 4> d4;
	typedef unpack_dependency_type<dependency, 5> d5;
	typedef unpack_dependency_type<dependency, 6> d6;
	typedef unpack_dependency_type<dependency, 7> d7;
	typedef return_type (signature)(typename d0::interface_type, typename d1::interface_type, typename d2::interface_type, typename d3::interface_type, typename d4::interface_type, typename d5::interface_type, typename d6::interface_type, typename d7::interface_type);
	typedef
		boost::_bi::bind_t<
			return_type,
			signature*,
			boost::_bi::list8<
				typename dependency_type_resolver<typename d0::dependency, placeholders, typename d0::used_placeholders, d0::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d1::dependency, placeholders, typename d1::used_placeholders, d1::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d2::dependency, placeholders, typename d2::used_placeholders, d2::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d3::dependency, placeholders, typename d3::used_placeholders, d3::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d4::dependency, placeholders, typename d4::used_placeholders, d4::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d5::dependency, placeholders, typename d5::used_placeholders, d5::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d6::dependency, placeholders, typename d6::used_placeholders, d6::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d7::dependency, placeholders, typename d7::used_placeholders, d7::is_placeholder != 0>::type
			>
		> type;
};

template <typename return_type, typename dependency, typename placeholders>
struct bind_type_resolver<return_type, dependency, placeholders, false, 9>
{
	typedef unpack_dependency_type<dependency, 0> d0;
	typedef unpack_dependency_type<dependency, 1> d1;
	typedef unpack_dependency_type<dependency, 2> d2;
	typedef unpack_dependency_type<dependency, 3> d3;
	typedef unpack_dependency_type<dependency, 4> d4;
	typedef unpack_dependency_type<dependency, 5> d5;
	typedef unpack_dependency_type<dependency, 6> d6;
	typedef unpack_dependency_type<dependency, 7> d7;
	typedef unpack_dependency_type<dependency, 8> d8;
	typedef return_type (signature)(typename d0::interface_type, typename d1::interface_type, typename d2::interface_type, typename d3::interface_type, typename d4::interface_type, typename d5::interface_type, typename d6::interface_type, typename d7::interface_type, typename d8::interface_type);
	typedef
		boost::_bi::bind_t<
			return_type,
			signature*,
			boost::_bi::list9<
				typename dependency_type_resolver<typename d0::dependency, placeholders, typename d0::used_placeholders, d0::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d1::dependency, placeholders, typename d1::used_placeholders, d1::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d2::dependency, placeholders, typename d2::used_placeholders, d2::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d3::dependency, placeholders, typename d3::used_placeholders, d3::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d4::dependency, placeholders, typename d4::used_placeholders, d4::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d5::dependency, placeholders, typename d5::used_placeholders, d5::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d6::dependency, placeholders, typename d6::used_placeholders, d6::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d7::dependency, placeholders, typename d7::used_placeholders, d7::is_placeholder != 0>::type,
				typename dependency_type_resolver<typename d8::dependency, placeholders, typename d8::used_placeholders, d8::is_placeholder != 0>::type
			>
		> type;
};
}
}