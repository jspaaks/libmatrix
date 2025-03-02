# Developer notes

## CMake

The project has been initialized with a [CMakeLists.txt](CMakeLists.txt)-based
configuration for building with CMake:

```console
# change into the build directory
$ cd build

# generate the build files
$ cmake ..

# build the project
$ cmake --build .

# install the project to <repo>/build/cmake/dist
$ cmake --install .

# matrix library also installs documentation as man pages
$ man -l ./dist/share/man/man3/matrix.3
```

The CMake variable `MATRIX_BUILD_TESTING` can be used to control whether the tests get built.
If this project is the top project, the default is to build it; conversely, if `libmatrix` is
used as a dependency of a different project, the default is to not build the tests. Either way,
building can be controlled by explicitly setting the beforementioned variable, e.g like so:

```console
cmake -DMATRIX_BUILD_TESTING=ON ..
```

## Testing

Building and running the tests require that [Criterion](https://github.com/Snaipe/Criterion) is installed on the system, e.g. with

```console
$ sudo apt install libcriterion-dev
```

Run the tests with

```console
$ ./dist/bin/test_matrix -j1 --verbose
```

Or simply,

```console
$ ctest
```

## `clang-format`

The file `.clang-format` contains an initial configuration for (automatic) formatting with [clang-format](https://clang.llvm.org/docs/ClangFormat.html). Run the formatter with e.g.:

```console
# dry run on main.c
$ clang-format -Werror --dry-run main.c

# format in place all *.c and *.h files under ./src
$ clang-format -i `find ./src -type f -name '*.[c|h]'`
```
