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
#include <boost/mpl/size.hpp>
#include <boost/mpl/at.hpp>

namespace ioc
{
namespace detail
{

//////////////////////////////////////////////////////////////////////////
// placeholder count

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

//////////////////////////////////////////////////////////////////////////
// signature

template<typename R, typename A, int argument_count>
struct make_signature {};

template<typename R, typename A>
struct make_signature<R, A, 0>
{
	typedef R (type)();
};

template<typename R, typename A>
struct make_signature<R, A, 1>
{
	typedef R (type)(
		typename boost::mpl::at_c<A, 0>::type
		);
};

template<typename R, typename A>
struct make_signature<R, A, 2>
{
	typedef R (type)(
		typename boost::mpl::at_c<A, 0>::type,
		typename boost::mpl::at_c<A, 1>::type
		);
};

template<typename R, typename A>
struct make_signature<R, A, 3>
{
	typedef R (type)(
		typename boost::mpl::at_c<A, 0>::type,
		typename boost::mpl::at_c<A, 1>::type,
		typename boost::mpl::at_c<A, 2>::type
		);
};

template<typename R, typename A>
struct make_signature<R, A, 4>
{
	typedef R (type)(
		typename boost::mpl::at_c<A, 0>::type,
		typename boost::mpl::at_c<A, 1>::type,
		typename boost::mpl::at_c<A, 2>::type,
		typename boost::mpl::at_c<A, 3>::type
		);
};

template<typename R, typename A>
struct make_signature<R, A, 5>
{
	typedef R (type)(
		typename boost::mpl::at_c<A, 0>::type,
		typename boost::mpl::at_c<A, 1>::type,
		typename boost::mpl::at_c<A, 2>::type,
		typename boost::mpl::at_c<A, 3>::type,
		typename boost::mpl::at_c<A, 4>::type
		);
};

template<typename R, typename A>
struct make_signature<R, A, 6>
{
	typedef R (type)(
		typename boost::mpl::at_c<A, 0>::type,
		typename boost::mpl::at_c<A, 1>::type,
		typename boost::mpl::at_c<A, 2>::type,
		typename boost::mpl::at_c<A, 3>::type,
		typename boost::mpl::at_c<A, 4>::type,
		typename boost::mpl::at_c<A, 5>::type
		);
};

template<typename R, typename A>
struct make_signature<R, A, 7>
{
	typedef R (type)(
		typename boost::mpl::at_c<A, 0>::type,
		typename boost::mpl::at_c<A, 1>::type,
		typename boost::mpl::at_c<A, 2>::type,
		typename boost::mpl::at_c<A, 3>::type,
		typename boost::mpl::at_c<A, 4>::type,
		typename boost::mpl::at_c<A, 5>::type,
		typename boost::mpl::at_c<A, 6>::type
		);
};

template<typename R, typename A>
struct make_signature<R, A, 8>
{
	typedef R (type)(
		typename boost::mpl::at_c<A, 0>::type,
		typename boost::mpl::at_c<A, 1>::type,
		typename boost::mpl::at_c<A, 2>::type,
		typename boost::mpl::at_c<A, 3>::type,
		typename boost::mpl::at_c<A, 4>::type,
		typename boost::mpl::at_c<A, 5>::type,
		typename boost::mpl::at_c<A, 6>::type,
		typename boost::mpl::at_c<A, 7>::type
		);
};

template<typename R, typename A>
struct make_signature<R, A, 9>
{
	typedef R (type)(
		typename boost::mpl::at_c<A, 0>::type,
		typename boost::mpl::at_c<A, 1>::type,
		typename boost::mpl::at_c<A, 2>::type,
		typename boost::mpl::at_c<A, 3>::type,
		typename boost::mpl::at_c<A, 4>::type,
		typename boost::mpl::at_c<A, 5>::type,
		typename boost::mpl::at_c<A, 6>::type,
		typename boost::mpl::at_c<A, 7>::type,
		typename boost::mpl::at_c<A, 8>::type
		);
};

template<typename placeholder>
struct get_placeholder_interface
{
	typedef typename placeholder::interface type;
};

template<typename R, typename A>
struct signature_maker
{
	typedef typename boost::mpl::transform<A, get_placeholder_interface<boost::mpl::_1> >::type params;
	typedef typename make_signature<R, params, boost::mpl::size<params>::value>::type type;
};

}
}