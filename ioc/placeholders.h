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
	typedef boost::mpl::vector<> dependencies;
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