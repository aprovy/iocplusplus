# Factory method design pattern implementation. #

## Example. ##

Assume what we have some hierarchy of classes:

```
struct ICar
{
	virtual void test() const = 0;
};

struct Car : ICar
{
	Car(int i, float f) {};
	void test() const { std::cout << "Car::test()"; }
};

struct Bus : ICar
{
	Bus(int i, float f) {};
	void test() const { std::cout << "Bus::test()"; }
};

struct Truck : ICar
{
	Truck(int i, float f) {};
	void test() const { std::cout << "Truck::test()"; }
};
```

Now, we can declare a factory type for it
```
#include <ioc/include/factory.h>

typedef ioc::factory<ICar*, int, float> car_factory_type;
```

This factory can include up to 9 constructor arguments. Here is two for example: int and float. Every type registered in a factory must accept same parameters in their constructor arguments.

Usage of a car factory is very simple:
```
int main()
{
...
// instantiate the factory: 
car_factory_type the_factory; 
// register some implementation classes:
the_factory.registerType<Car>("car"); 
the_factory.registerType<Bus>("bus");
the_factory.registerType<Truck>("truck");

// resolve a car by it's name "car"
ICar* ptr = the_factory.resolve<ICar*>("car", 0, 0.f);
ptr->test();
delete ptr;
...
}
```

There is no `_shared` version of interface since you can do like this:
```
boost::shared_ptr<ICar> ptr = the_factory.resolve<ICar*>("car", 0, 0.f);
```

This is all about ioc++ factory container.