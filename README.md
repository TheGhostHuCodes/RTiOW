# Ray Tracing in a Weekend

This repository contains code and exercises from my workthrough of [Ray Tracing
in a
Weekend](https://www.amazon.com/Ray-Tracing-Weekend-Minibooks-Book-ebook/dp/B01B5AODD8)
by Peter Shirley.

This project uses [CMake](https://cmake.org/) as a build system and
[Conan](https://conan.io/) to manage packages. To be able to build this
project, you will need these tools installed.

Build steps within a directory that contains a `CMakeList.txt` and
`conanfile.txt` on Linux:

```shell
mkdir build && cd build
conan install ..
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build .
```
