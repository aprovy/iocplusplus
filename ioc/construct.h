#pragma once

//////////////////////////////////////////////////////////////////////////
// construct.h

// (C) Copyright 2011-2012 Guardian. 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://code.google.com/p/iocplusplus/ for updates, documentation, and revision history.

namespace ioc
{
namespace detail
{
//////////////////////////////////////////////////////////////////////////
// constructors
template<typename I, typename T>
struct construct0
{
	static I invoke() { return I(new T()); }
};

template<typename I, typename T, typename A0>
struct construct1
{
	static I invoke(A0 a0) { return I(new T(a0)); }
};

template<typename I, typename T, typename A0, typename A1>
struct construct2
{
	static I invoke(A0 a0, A1 a1) { return I(new T(a0, a1)); }
};

template<typename I, typename T, typename A0, typename A1, typename A2>
struct construct3
{
	static I invoke(A0 a0, A1 a1, A2 a2) { return I(new T(a0, a1, a2)); }
};

template<typename I, typename T, typename A0, typename A1, typename A2, typename A3>
struct construct4
{
	static I invoke(A0 a0, A1 a1, A2 a2, A3 a3) { return I(new T(a0, a1, a2, a3)); }
};

template<typename I, typename T, typename A0, typename A1, typename A2, typename A3, typename A4>
struct construct5
{
	static I invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4) { return I(new T(a0, a1, a2, a3, a4)); }
};

template<typename I, typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
struct construct6
{
	static I invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) { return I(new T(a0, a1, a2, a3, a4, a5)); }
};

template<typename I, typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
struct construct7
{
	static I invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) { return I(new T(a0, a1, a2, a3, a4, a5, a6)); }
};

template<typename I, typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
struct construct8
{
	static I invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) { return I(new T(a0, a1, a2, a3, a4, a5, a6, a7)); }
};

template<typename I, typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
struct construct9
{
	static I invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) { return I(new T(a0, a1, a2, a3, a4, a5, a6, a7, a8)); }
};

}
}