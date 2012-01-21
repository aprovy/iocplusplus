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
#include "signature.h"

namespace ioc
{
//////////////////////////////////////////////////////////////////////////
// exceptions
class unregistred_descriptor : public std::exception
{
public:
	unregistred_descriptor(std::string name) : m_what("ioc++: no descriptor is registred for a type " + name) {}
	virtual const char * what() const { return m_what.c_str(); }
private:
	std::string m_what;
};

class invalid_signature : public std::exception
{
public:
	invalid_signature(std::string name) : m_what("ioc++: signature mismatch for a type " + name) {}
	virtual const char * what() const { return m_what.c_str(); }
private:
	std::string m_what;
};

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
	template<typename descriptor, typename register_type>
	void registerType()
	{
		enum { placeholder_count = detail::get_placeholder_count<descriptor>::value };
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

		typedef detail::signature_maker<
			typename descriptor::interface,
			typename resolver_type::signature_placeholders
		>::type signature;

		boost::function<signature> resolver =
			resolver_type::invoke();
		m_resolvers.insert(typeid(register_type).name(), resolver);
	}

	template<typename descriptor>
	void registerType()
	{
		registerType<descriptor, descriptor::type>();
	}

	template <typename T, typename signature>
	void registerFactory(const boost::function<signature>& binded_factory)
	{
		m_resolvers.insert(typeid(T).name(), binded_factory);
	}

	template<typename R>
	R* resolve() const
	{
		std::string name = typeid(R).name();
		boost::any resolver = m_resolvers.get(name.c_str());
		if(!resolver.empty())
		{
			try { return boost::any_cast< boost::function<R* ()> >(resolver)(); }
			catch(boost::bad_any_cast&)
			{
#ifndef IOC_NO_EXCEPTIONS
				throw invalid_signature(name);
#endif
			}
		}

#ifndef IOC_NO_EXCEPTIONS
		throw unregistred_descriptor(name);
#endif
		return 0;
	}

	template<typename R, typename A0>
	R* resolve(A0 a0) const
	{
		std::string name = typeid(R).name();
		boost::any resolver = m_resolvers.get(name.c_str());
		if(!resolver.empty())
		{
			try { return boost::any_cast< boost::function<R* (A0)> >(resolver)(a0); }
			catch(boost::bad_any_cast&)
			{
#ifndef IOC_NO_EXCEPTIONS
				throw invalid_signature(name);
#endif
			}
		}

#ifndef IOC_NO_EXCEPTIONS
		throw unregistred_descriptor(name);
#endif
		return 0;
	}

	template<typename R, typename A0, typename A1>
	R* resolve(A0 a0, A1 a1) const
	{
		std::string name = typeid(R).name();
		boost::any resolver = m_resolvers.get(name.c_str());
		if(!resolver.empty())
		{
			try { return boost::any_cast< boost::function<R* (A0, A1)> >(resolver)(a0, a1); }
			catch(boost::bad_any_cast&)
			{
#ifndef IOC_NO_EXCEPTIONS
				throw invalid_signature(name);
#endif
			}
		}

#ifndef IOC_NO_EXCEPTIONS
		throw unregistred_descriptor(name);
#endif
		return 0;
	}

	template<typename R, typename A0, typename A1, typename A2>
	R* resolve(A0 a0, A1 a1, A2 a2) const
	{
		std::string name = typeid(R).name();
		boost::any resolver = m_resolvers.get(name.c_str());
		if(!resolver.empty())
		{
			try { return boost::any_cast< boost::function<R* (A0, A1, A2)> >(resolver)(a0, a1, a2); }
			catch(boost::bad_any_cast&)
			{
#ifndef IOC_NO_EXCEPTIONS
				throw invalid_signature(name);
#endif
			}
		}

#ifndef IOC_NO_EXCEPTIONS
		throw unregistred_descriptor(name);
#endif
		return 0;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3>
	R* resolve(A0 a0, A1 a1, A2 a2, A3 a3) const
	{
		std::string name = typeid(R).name();
		boost::any resolver = m_resolvers.get(name.c_str());
		if(!resolver.empty())
		{
			try { return boost::any_cast< boost::function<R* (A0, A1, A2, A3)> >(resolver)(a0, a1, a2, a3); }
			catch(boost::bad_any_cast&)
			{
#ifndef IOC_NO_EXCEPTIONS
				throw invalid_signature(name);
#endif
			}
		}

#ifndef IOC_NO_EXCEPTIONS
		throw unregistred_descriptor(name);
#endif
		return 0;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4>
	R* resolve(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4) const
	{
		std::string name = typeid(R).name();
		boost::any resolver = m_resolvers.get(name.c_str());
		if(!resolver.empty())
		{
			try { return boost::any_cast< boost::function<R* (A0, A1, A2, A3, A4)> >(resolver)(a0, a1, a2, a3, a4); }
			catch(boost::bad_any_cast&)
			{
#ifndef IOC_NO_EXCEPTIONS
				throw invalid_signature(name);
#endif
			}
		}

#ifndef IOC_NO_EXCEPTIONS
		throw unregistred_descriptor(name);
#endif
		return 0;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
	R* resolve(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
	{
		std::string name = typeid(R).name();
		boost::any resolver = m_resolvers.get(name.c_str());
		if(!resolver.empty())
		{
			try { return boost::any_cast< boost::function<R* (A0, A1, A2, A3, A4, A5)> >(resolver)(a0, a1, a2, a3, a4, a5); }
			catch(boost::bad_any_cast&)
			{
#ifndef IOC_NO_EXCEPTIONS
				throw invalid_signature(name);
#endif
			}
		}

#ifndef IOC_NO_EXCEPTIONS
		throw unregistred_descriptor(name);
#endif
		return 0;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
	R* resolve(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
	{
		std::string name = typeid(R).name();
		boost::any resolver = m_resolvers.get(name.c_str());
		if(!resolver.empty())
		{
			try { return boost::any_cast< boost::function<R* (A0, A1, A2, A3, A4, A5, A6)> >(resolver)(a0, a1, a2, a3, a4, a5, a6); }
			catch(boost::bad_any_cast&)
			{
#ifndef IOC_NO_EXCEPTIONS
				throw invalid_signature(name);
#endif
			}
		}

#ifndef IOC_NO_EXCEPTIONS
		throw unregistred_descriptor(name);
#endif
		return 0;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
	R* resolve(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
	{
		std::string name = typeid(R).name();
		boost::any resolver = m_resolvers.get(name.c_str());
		if(!resolver.empty())
		{
			try { return boost::any_cast< boost::function<R* (A0, A1, A2, A3, A4, A5, A6, A7)> >(resolver)(a0, a1, a2, a3, a4, a5, a6, a7); }
			catch(boost::bad_any_cast&)
			{
#ifndef IOC_NO_EXCEPTIONS
				throw invalid_signature(name);
#endif
			}
		}

#ifndef IOC_NO_EXCEPTIONS
		throw unregistred_descriptor(name);
#endif
		return 0;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
	R* resolve(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
	{
		std::string name = typeid(R).name();
		boost::any resolver = m_resolvers.get(name.c_str());
		if(!resolver.empty())
		{
			try { return boost::any_cast< boost::function<R* (A0, A1, A2, A3, A4, A5, A6, A7, A8)> >(resolver)(a0, a1, a2, a3, a4, a5, a6, a7, a8); }
			catch(boost::bad_any_cast&)
			{
#ifndef IOC_NO_EXCEPTIONS
				throw invalid_signature(name);
#endif
			}
		}

#ifndef IOC_NO_EXCEPTIONS
		throw unregistred_descriptor(name);
#endif
		return 0;
	}

	template<typename R>
	boost::shared_ptr<R> resolve_shared() const
	{
		std::string name = typeid(R).name();
		boost::any resolver = m_resolvers.get(name.c_str());
		if(!resolver.empty())
		{
			try { return boost::any_cast< boost::function<boost::shared_ptr<R> ()> >(resolver)(); }
			catch(boost::bad_any_cast&)
			{
#ifndef IOC_NO_EXCEPTIONS
				throw invalid_signature(name);
#endif
			}
		}

#ifndef IOC_NO_EXCEPTIONS
		throw unregistred_descriptor(name);
#endif
		return boost::shared_ptr<R>();
	}

	template<typename R, typename A0>
	boost::shared_ptr<R> resolve_shared(A0 a0) const
	{
		std::string name = typeid(R).name();
		boost::any resolver = m_resolvers.get(name.c_str());
		if(!resolver.empty())
		{
			try { return boost::any_cast< boost::function<boost::shared_ptr<R> (A0)> >(resolver)(a0); }
			catch(boost::bad_any_cast&)
			{
#ifndef IOC_NO_EXCEPTIONS
				throw invalid_signature(name);
#endif
			}
		}

#ifndef IOC_NO_EXCEPTIONS
		throw unregistred_descriptor(name);
#endif
		return boost::shared_ptr<R>();
	}

	template<typename R, typename A0, typename A1>
	boost::shared_ptr<R> resolve_shared(A0 a0, A1 a1) const
	{
		std::string name = typeid(R).name();
		boost::any resolver = m_resolvers.get(name.c_str());
		if(!resolver.empty())
		{
			try { return boost::any_cast< boost::function<boost::shared_ptr<R> (A0, A1)> >(resolver)(a0, a1); }
			catch(boost::bad_any_cast&)
			{
#ifndef IOC_NO_EXCEPTIONS
				throw invalid_signature(name);
#endif
			}
		}

#ifndef IOC_NO_EXCEPTIONS
		throw unregistred_descriptor(name);
#endif
		return boost::shared_ptr<R>();
	}

	template<typename R, typename A0, typename A1, typename A2>
	boost::shared_ptr<R> resolve_shared(A0 a0, A1 a1, A2 a2) const
	{
		std::string name = typeid(R).name();
		boost::any resolver = m_resolvers.get(name.c_str());
		if(!resolver.empty())
		{
			try { return boost::any_cast< boost::function<boost::shared_ptr<R> (A0, A1, A2)> >(resolver)(a0, a1, a2); }
			catch(boost::bad_any_cast&)
			{
#ifndef IOC_NO_EXCEPTIONS
				throw invalid_signature(name);
#endif
			}
		}

#ifndef IOC_NO_EXCEPTIONS
		throw unregistred_descriptor(name);
#endif
		return boost::shared_ptr<R>();
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3>
	boost::shared_ptr<R> resolve_shared(A0 a0, A1 a1, A2 a2, A3 a3) const
	{
		std::string name = typeid(R).name();
		boost::any resolver = m_resolvers.get(name.c_str());
		if(!resolver.empty())
		{
			try { return boost::any_cast< boost::function<boost::shared_ptr<R> (A0, A1, A2, A3)> >(resolver)(a0, a1, a2, a3); }
			catch(boost::bad_any_cast&)
			{
#ifndef IOC_NO_EXCEPTIONS
				throw invalid_signature(name);
#endif
			}
		}

#ifndef IOC_NO_EXCEPTIONS
		throw unregistred_descriptor(name);
#endif
		return boost::shared_ptr<R>();
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4>
	boost::shared_ptr<R> resolve_shared(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4) const
	{
		std::string name = typeid(R).name();
		boost::any resolver = m_resolvers.get(name.c_str());
		if(!resolver.empty())
		{
			try { return boost::any_cast< boost::function<boost::shared_ptr<R> (A0, A1, A2, A3, A4)> >(resolver)(a0, a1, a2, a3, a4); }
			catch(boost::bad_any_cast&)
			{
#ifndef IOC_NO_EXCEPTIONS
				throw invalid_signature(name);
#endif
			}
		}

#ifndef IOC_NO_EXCEPTIONS
		throw unregistred_descriptor(name);
#endif
		return boost::shared_ptr<R>();
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
	boost::shared_ptr<R> resolve_shared(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
	{
		std::string name = typeid(R).name();
		boost::any resolver = m_resolvers.get(name.c_str());
		if(!resolver.empty())
		{
			try { return boost::any_cast< boost::function<boost::shared_ptr<R> (A0, A1, A2, A3, A4, A5)> >(resolver)(a0, a1, a2, a3, a4, a5); }
			catch(boost::bad_any_cast&)
			{
#ifndef IOC_NO_EXCEPTIONS
				throw invalid_signature(name);
#endif
			}
		}

#ifndef IOC_NO_EXCEPTIONS
		throw unregistred_descriptor(name);
#endif
		return boost::shared_ptr<R>();
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
	boost::shared_ptr<R> resolve_shared(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
	{
		std::string name = typeid(R).name();
		boost::any resolver = m_resolvers.get(name.c_str());
		if(!resolver.empty())
		{
			try { return boost::any_cast< boost::function<boost::shared_ptr<R> (A0, A1, A2, A3, A4, A5, A6)> >(resolver)(a0, a1, a2, a3, a4, a5, a6); }
			catch(boost::bad_any_cast&)
			{
#ifndef IOC_NO_EXCEPTIONS
				throw invalid_signature(name);
#endif
			}
		}

#ifndef IOC_NO_EXCEPTIONS
		throw unregistred_descriptor(name);
#endif
		return boost::shared_ptr<R>();
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
	boost::shared_ptr<R> resolve_shared(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
	{
		std::string name = typeid(R).name();
		boost::any resolver = m_resolvers.get(name.c_str());
		if(!resolver.empty())
		{
			try { return boost::any_cast< boost::function<boost::shared_ptr<R> (A0, A1, A2, A3, A4, A5, A6, A7)> >(resolver)(a0, a1, a2, a3, a4, a5, a6, a7); }
			catch(boost::bad_any_cast&)
			{
#ifndef IOC_NO_EXCEPTIONS
				throw invalid_signature(name);
#endif
			}
		}

#ifndef IOC_NO_EXCEPTIONS
		throw unregistred_descriptor(name);
#endif
		return boost::shared_ptr<R>();
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
	boost::shared_ptr<R> resolve_shared(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
	{
		std::string name = typeid(R).name();
		boost::any resolver = m_resolvers.get(name.c_str());
		if(!resolver.empty())
		{
			try { return boost::any_cast< boost::function<boost::shared_ptr<R> (A0, A1, A2, A3, A4, A5, A6, A7, A8)> >(resolver)(a0, a1, a2, a3, a4, a5, a6, a7, a8); }
			catch(boost::bad_any_cast&)
			{
#ifndef IOC_NO_EXCEPTIONS
				throw invalid_signature(name);
#endif
			}
		}

#ifndef IOC_NO_EXCEPTIONS
		throw unregistred_descriptor(name);
#endif
		return boost::shared_ptr<R>();
	}

private:
	any_map m_resolvers;
};

}