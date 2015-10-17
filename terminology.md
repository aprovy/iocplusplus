# Terminology #

The ioc++ needs information about object's type for correnct type resolving.
You can provide such information using descriptor and dependency templates.

**Descriptor** describes object type, object factory return type (raw or smart pointer for example) and 0 to 9 dependencies for each constructor's argument.

There are two descriptors in a library for now: raw pointer `descriptor_t` and smart pointer(shared\_ptr) `descriptor_shared_t`.

**Dependency** describes a constructor argument. It includes a descriptor of argument's type and 0 to 9 indices of placeholders that are used inside by it.

There are two dependency types: `dependency_t` (constructed) and `placeholder_dependency_t` (for providing resolve-time arguments)

Constructed dependency tells the library that object type in descriptor should be constructed by library and passed as an argument.

Placeholder dependency marks that this argument to be supplied at resolve time like placeholders `_N` in boost.bind.