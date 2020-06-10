# Soto

A library of common algorithms and data structures.

## Building

``` shell
cmake . -Bbuild
cmake --build build
```

## Testing

To compile tests, you need to have [Check](https://libcheck.github.io/check/) framework installed and build Soto with `BUILD_TESTING` variable set to `ON`. You may also need to specify Check installation directory by setting `CHECK_INSTALL_DIR`. For example:

``` shell
cmake . -Bbuild -DBUILD_TESTING=ON -DCHECK_INSTALL_DIR='C:\Program Files (x86)\Check'
cmake --build build
```

Now, run `ctest` from the `build` directory like this:

``` shell
ctest -C Debug
```

You can also directly execute the test files for better output. For example, to run sort test compiled using [Visual Studio](https://visualstudio.microsoft.com/), enter the following:

``` shell
./build/test/Debug/test_sort.exe
```

## Installing

First, you need to build Soto using Release configuration:

``` shell
cmake --build build --config Release
```

Then, enter the following:

``` shell
cmake -P build/cmake_install.cmake
```

## Usage

To use Soto with a project that uses [CMake](https://cmake.org/) itself, add the following to your top-level `CMakeLists.txt` file:

``` cmake
find_package(soto REQUIRED)
```

Then, use `target_link_libraries` to add it to your project:

``` cmake
target_link_libraries(${PROJECT_NAME} soto)
```

## License

[MIT](https://github.com/wadiim/soto/blob/master/LICENSE)
