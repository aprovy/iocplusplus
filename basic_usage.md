# Basic usage #

## Example 1. ##
### Hello world ###
```
#include <ioc/container.h>

struct a{};
typedef ioc::descriptor_t<a> descriptor_a;

main()
{
	ioc::container ioc;
	ioc.registerType<descriptor_a>();
	a* a_ptr = ioc.resolve<a>(); // -> a* a_ptr = new a();
}
```
The lifetime tracking of the object is a caller responsability.

## Example 2. ##

### Constructor arguments. ###

Let's see another example. We are using a constructor with argument:
```
struct a{ a(int value) {} };
typedef ioc::descriptor_t<a, ioc::placeholder_dependency_t<1, int> > descriptor_a;

main()
{
	ioc::container ioc;
	ioc.registerType<descriptor_a>();
	a* a_ptr = ioc.resolve<a>(5); // -> a* a_ptr = new a(5);
}
```

## Example 3. ##

### Smart pointers. ###

You can handle objects with smart pointer `shared_ptr<T>`, instead of raw pointer `T*` with another version of template:
```
struct a{ a(int value) {} };
typedef ioc::descriptor_shared_t<a, ioc::placeholder_dependency_t<1, int> > descriptor_a;

main()
{
	ioc::container ioc;
	ioc.registerType<descriptor_a>();
	boost::shared_ptr<a> a_ptr = ioc.resolve_shared<a>(5); // -> a* a_ptr = boost::shared_ptr<a>(new a(5));
}
```
But you still can do:
```
boost::shared_ptr<a> a_ptr(ioc.resolve<a>(5));
```
to create an object. But you can't do it when "a" is dependency for another type that can be resolved. You should use descriptor\_shared\_t instead (see example 4)

## Example 4. ##

### Dependend object with smart pointer. ###
```
struct a{};
typedef ioc::descriptor_shared_t<a> desc_a;

struct b
{
	b(const boost::shared_ptr<a>& aaa) : m_a(aaa) {}
	boost::shared_ptr<a> m_a;
};
typedef ioc::descriptor_t<b, ioc::dependency_t<desc_a>> desc_b;

ioc.registerType<desc_b>();
b* obj1 = ioc.resolve<b>();
```
Please, pay attention that there is no dependency\_shared\_t, only descriptor\_shared\_t.

## Example 5. ##

### Dependend objects with placeholders. ###
```
struct pl_inner
{
	pl_inner(char a){}
};
typedef ioc::descriptor_t<pl_inner, ioc::placeholder_dependency_t<1, char>> desc_pl_inner;

struct pl_middle
{
	pl_middle(pl_inner* i, float t){}
};
typedef ioc::descriptor_t<pl_middle, ioc::dependency_t<desc_pl_inner, 2>, ioc::placeholder_dependency_t<1, float>> desc_pl_middle;

struct pl_left
{
	pl_left(int a, float b)	{}
};
typedef ioc::descriptor_t<pl_left, ioc::placeholder_dependency_t<1, int>, ioc::placeholder_dependency_t<2, float>> desc_pl_left;

struct pl
{
	pl(pl_left* left, pl_middle* middle) {}
};
typedef ioc::descriptor_t<pl, ioc::dependency_t<desc_pl_left, 1, 2>, ioc::dependency_t<desc_pl_middle, 2, 3>> desc_pl;

ioc.registerType<desc_pl>();

pl* obj = ioc.resolve<pl>(1, 2.f, (char)3);
delete obj;
```
A few words about placeholders (for details see. dependency\_t, placeholder\_dependency\_t) Placeholders must be passed along to the final consumer types. For example, struct pl doesn't take any placeholder directly, but must provide it to the dependencies. It looks like `[`pseudocode`]`:
```
function<pl* (int, float, char)> f =
	bind(&new pl,
		bind(&new pl_left, _1, _2),
		bind(&new pl_middle, bind(&new pl_inner, _3), _2)
		);
```
As you can see there is no placeholder 2 in the desc\_pl\_left. Each descriptor has its own list of a placeholders, numbered from 1. But each descriptor has access to the actual parent placeholders using placeholder remap, wiht the indecies passed to dependency\_t.  This is done to allow descriptors to be independent and reusable.
Note, that you don't need to register the all dependend descriptors in the container in order to create an object. You have to register descriptor for this object only.


---

[Home](documentation_root.md) [Prev (Concepts)](contents.md) [Next (Preferences)](preferences.md)