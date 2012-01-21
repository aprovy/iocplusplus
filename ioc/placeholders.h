#pragma once

//////////////////////////////////////////////////////////////////////////
// placeholders.h

// (C) Copyright 2011-2012 Guardian. 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://code.google.com/p/iocplusplus/ for updates, documentation, and revision history.

#include <boost/mpl/vector.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/sort.hpp>
#include <boost/mpl/unique.hpp>
#include <boost/mpl/less.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/comparison.hpp>
#include <boost/static_assert.hpp>

namespace ioc
{
namespace detail
{
//////////////////////////////////////////////////////////////////////////
// placeholder descriptor
template<int I, typename T>
struct placeholder
{
	typedef boost::arg<I> type;
	typedef T interface;
	typedef boost::mpl::vector0<> dependencies;
};

template<typename placeholder_types, typename placeholder_index>
struct create_placeholder
{
	typedef placeholder<
		placeholder_index::value,
		typename boost::mpl::at_c<placeholder_types, placeholder_index::value - 1>::type
	> type;
};

template<typename placeholder_descriptor>
struct create_placeholder_dependency
{
	typedef struct
	{
		typedef placeholder_descriptor descriptor;
		typedef boost::mpl::vector0<> placeholders;
	} type;
};

//////////////////////////////////////////////////////////////////////////
// placeholders helpers
// inspired by the boost...
template<class T>
struct get_placeholder_index
{
	enum _vt { index = 0 };
};

template<int I>
struct get_placeholder_index<boost::arg<I>>
{
	enum _vt { index = I - 1 }; // mpl::vector is used a zero-based index, but a placeholder index starts from 1
};

// transform one placeholder to another stored in vector
template<typename placeholders, typename construct_type>
struct get_placeholder_type
{
	typedef boost::arg<boost::mpl::at_c<placeholders, get_placeholder_index<construct_type>::index>::type::value> type;
};

// gets the placeholder with remapped index
template<typename placeholders, typename descriptor>
struct get_actual_placeholder
{
	typedef typename descriptor::type construct_type;
	typedef typename descriptor::interface interface_type;
	typedef placeholder<boost::mpl::at_c<placeholders, get_placeholder_index<construct_type>::index>::type::value, interface_type> type;
};

struct placeholder_less
{
	template<typename Left, typename Right>
	struct apply
	{
		enum { left_index = get_placeholder_index<typename Left::type>::index };
		enum { right_index = get_placeholder_index<typename Right::type>::index };
		typedef typename boost::mpl::less<boost::mpl::int_<left_index>, boost::mpl::int_<right_index>>::type type;
	};
};

//////////////////////////////////////////////////////////////////////////
// merge placeholders
template<
	typename A0 = boost::mpl::vector0<>,
	typename A1 = boost::mpl::vector0<>,
	typename A2 = boost::mpl::vector0<>,
	typename A3 = boost::mpl::vector0<>,
	typename A4 = boost::mpl::vector0<>,
	typename A5 = boost::mpl::vector0<>,
	typename A6 = boost::mpl::vector0<>,
	typename A7 = boost::mpl::vector0<>,
	typename A8 = boost::mpl::vector0<>
>
struct merge_placeholders
{
	typedef typename boost::mpl::copy<A0, boost::mpl::back_inserter<boost::mpl::vector0<>> >::type merged_a0;
	typedef typename boost::mpl::copy<A1, boost::mpl::back_inserter<merged_a0> >::type merged_a1;
	typedef typename boost::mpl::copy<A2, boost::mpl::back_inserter<merged_a1> >::type merged_a2;
	typedef typename boost::mpl::copy<A3, boost::mpl::back_inserter<merged_a2> >::type merged_a3;
	typedef typename boost::mpl::copy<A4, boost::mpl::back_inserter<merged_a3> >::type merged_a4;
	typedef typename boost::mpl::copy<A5, boost::mpl::back_inserter<merged_a4> >::type merged_a5;
	typedef typename boost::mpl::copy<A6, boost::mpl::back_inserter<merged_a5> >::type merged_a6;
	typedef typename boost::mpl::copy<A7, boost::mpl::back_inserter<merged_a6> >::type merged_a7;
	typedef typename boost::mpl::copy<A8, boost::mpl::back_inserter<merged_a7> >::type merged_a8;
	typedef typename boost::mpl::sort<
		merged_a8,
		typename boost::mpl::bind<
			placeholder_less,
			boost::mpl::_1,
			boost::mpl::_2
			>
	>::type sorted;
	typedef typename boost::mpl::unique<
		sorted,
		boost::is_same<boost::mpl::_1,boost::mpl::_2>
	>::type result;
};

//////////////////////////////////////////////////////////////////////////
// remap
template<typename from_placeholders, typename to_placeholders, bool empty>
struct remap_placeholders
{
	// from_placeholders - input vector, actual placeholders
	// to_placeholders - placeholders in the dependency,
	BOOST_STATIC_ASSERT((boost::mpl::greater_equal<boost::mpl::size<from_placeholders>, boost::mpl::size<to_placeholders>>::value));
	// once again, we must correct an index of a placeholder while we using it in the mpl::vector
	typedef typename boost::mpl::transform<typename to_placeholders,
		boost::mpl::at<typename from_placeholders, boost::mpl::minus<boost::mpl::_1, boost::mpl::int_<1>>> >::type type;
};

template<typename from_placeholders, typename to_placeholders>
struct remap_placeholders<from_placeholders, to_placeholders, true>
{
	typedef boost::mpl::vector<> type;
};

}
}