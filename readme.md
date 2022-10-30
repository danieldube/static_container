# Static Container

Static Container is a small library, which implements a `std::vector`
like class `StaticVector`. In contrast to `std::vector`, `StaticVector`
operates on a predefined block of memory. The use case are environments,
where the usage of dynamic memory allocation is not available during
run-time.

##  Build

```bash
meson setup build
cd build
meson compile
```


## Development State

Currently, the implementation is _far away_ from ready for production code.
It's basically just a tiny proof of concept.
