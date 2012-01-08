#pragma once

//////////////////////////////////////////////////////////////////////////
// bind_or_call.h

// (C) Copyright 2011-2012 Guardian. 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://code.google.com/p/iocplusplus/ for updates, documentation, and revision history.

namespace ioc
{

//////////////////////////////////////////////////////////////////////////
// bind_or_call

template<typename return_type, typename resolver_type, bool is_placeholder>
struct bind_or_call
{
	static return_type resolve()
	{
		return resolver_type::invoke();
	}
};

template<typename return_type, typename resolver_type>
struct bind_or_call<return_type, resolver_type, true>
{
	static return_type resolve()
	{
		return return_type();
	}
};

}