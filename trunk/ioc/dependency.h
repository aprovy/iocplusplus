#pragma once

//////////////////////////////////////////////////////////////////////////
// dependency.h

// (C) Copyright 2011-2012 Guardian. 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://code.google.com/p/iocplusplus/ for updates, documentation, and revision history.

#include <boost/shared_ptr.hpp>
#include <boost/mpl/copy_if.hpp>
#include <boost/mpl/always.hpp>
#include <boost/type_traits/is_same.hpp>

namespace ioc
{
namespace detail
{
template<typename T, typename P>
struct make_dependency
{
	typedef struct type{
		typedef T descriptor;
		typedef P placeholders;
	};
};

template<typename invalid_type, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
struct pack_args
{
	typedef typename boost::mpl::copy_if<
		boost::mpl::vector<A0, A1, A2, A3, A4, A5, A6, A7, A8>,
		boost::mpl::not_equal_to<boost::is_same<boost::mpl::_1, invalid_type>, boost::mpl::true_>,
		boost::mpl::back_inserter<boost::mpl::vector<>>
	>::type output_args; 
};

template<int invalid_value, int A0, int A1, int A2, int A3, int A4, int A5, int A6, int A7, int A8>
struct pack_int_args
{
	typedef typename boost::mpl::copy_if<
		boost::mpl::vector<
			boost::mpl::int_<A0>,
			boost::mpl::int_<A1>,
			boost::mpl::int_<A2>,
			boost::mpl::int_<A3>,
			boost::mpl::int_<A4>,
			boost::mpl::int_<A5>,
			boost::mpl::int_<A6>,
			boost::mpl::int_<A7>,
			boost::mpl::int_<A8>
		>,
		boost::mpl::not_equal_to<boost::mpl::_1, boost::mpl::int_<invalid_value>>
		>::type output_args; 
};
}

enum { invalid_placeholder_index = 0 };

template<
	typename desc,
	int A0 = invalid_placeholder_index,
	int A1 = invalid_placeholder_index,
	int A2 = invalid_placeholder_index,
	int A3 = invalid_placeholder_index,
	int A4 = invalid_placeholder_index,
	int A5 = invalid_placeholder_index,
	int A6 = invalid_placeholder_index,
	int A7 = invalid_placeholder_index,
	int A8 = invalid_placeholder_index
>
struct dependency_t
{
	typedef desc descriptor;
	typedef typename typename detail::pack_int_args<
		invalid_placeholder_index, A0, A1, A2, A3, A4, A5, A6, A7, A8
	>::output_args placeholders;
};

template<int I, typename T>
struct placeholder_dependency_t
{
	typedef detail::placeholder<I, T> descriptor;
	typedef boost::mpl::vector<> placeholders;
};

struct empty_dependency_t { typedef int dummy_; };
template<
	typename T,
	typename A0 = empty_dependency_t,
	typename A1 = empty_dependency_t,
	typename A2 = empty_dependency_t,
	typename A3 = empty_dependency_t,
	typename A4 = empty_dependency_t,
	typename A5 = empty_dependency_t,
	typename A6 = empty_dependency_t,
	typename A7 = empty_dependency_t,
	typename A8 = empty_dependency_t
>
struct descriptor_t
{
	typedef T type;
	typedef T* interface;
	typedef typename detail::pack_args<empty_dependency_t, A0, A1, A2, A3, A4, A5, A6, A7, A8>::output_args dependencies;
};

template<
	typename T,
	typename A0 = empty_dependency_t,
	typename A1 = empty_dependency_t,
	typename A2 = empty_dependency_t,
	typename A3 = empty_dependency_t,
	typename A4 = empty_dependency_t,
	typename A5 = empty_dependency_t,
	typename A6 = empty_dependency_t,
	typename A7 = empty_dependency_t,
	typename A8 = empty_dependency_t
>
struct descriptor_shared_t
{
	typedef T type;
	typedef boost::shared_ptr<T> interface;
	typedef typename detail::pack_args<empty_dependency_t, A0, A1, A2, A3, A4, A5, A6, A7, A8>::output_args dependencies;
};

}