#pragma once

//////////////////////////////////////////////////////////////////////////
// generators.h

// (C) Copyright 2011-2012 Guardian. 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://code.google.com/p/iocplusplus/ for updates, documentation, and revision history.

#include <boost/mpl/max_element.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/transform.hpp>

namespace ioc
{

namespace detail
{

template<typename dependency>
struct get_max_placeholder
{
	typedef typename dependency::placeholders placeholders;

	typedef typename boost::mpl::if_c<
		boost::mpl::size<placeholders>::value != 0,
		typename boost::mpl::deref<typename boost::mpl::max_element<placeholders>::type>::type,
		boost::mpl::int_<0>
	>::type type;
};

template<typename descriptor>
struct get_placeholder_count
{
	typedef typename descriptor::dependencies dependencies;
	typedef typename boost::mpl::transform<dependencies, get_max_placeholder<boost::mpl::_1> >::type result;
	typedef typename boost::mpl::if_c<
		boost::mpl::size<result>::value != 0,
		typename boost::mpl::deref<typename boost::mpl::max_element<result>::type>::type,
		boost::mpl::int_<0>
	>::type type;
	enum { value = type::value };
};

}
}