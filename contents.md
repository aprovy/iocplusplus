# Concepts #

Concept of the ioc++ can be described in example below. Let we have few classes, such:

```
struct a{};
struct b{};
struct c{};
struct d{};
struct e{ e(a* a_ptr, b* b_ptr) {} };
struct f{ f(c* c_ptr, d* d_ptr) {} };
struct g{ g(e* e_ptr, f* f_ptr) {} };
```
when the creation of a functor(or factory) can be described as`[`pseudocode`]`:

```
function<g* ()> f =
	bind(&new g,
		bind(&new e, bind(&new a), bind(&new b)),
		bind(&new f, bind(&new c), bind(&new d))
		);
```

ioc++ does the same thing and creates factories recursively for all dependencies, saving a result into a boost::function object. Also, ioc++ can handle placeholders. The ioc++ placeholders have the same limitations as the boost.bind placeholders do.


---

[Home](documentation_root.md) [Next (Basic usage)](basic_usage.md)