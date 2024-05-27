Creating a dynamic library in C++ and using it in a small C++ program with CMake involves several steps. Here's a step-by-step guide to help you accomplish this task.

### Step 1: Create the Dynamic Library

#### 1.1. Create the Library Source Files

First, create a directory for your library and add the source files. Let's call the directory `mylib`.

`mylib/mylib.h`:

```cpp
#ifndef MYLIB_H
#define MYLIB_H

#if defined(_WIN32) || defined(_WIN64)
    #ifdef MYLIB_EXPORTS
        #define MYLIB_API __declspec(dllexport)
    #else
        #define MYLIB_API __declspec(dllimport)
    #endif
#else
    #define MYLIB_API
#endif

MYLIB_API void hello();

#endif // MYLIB_H
```

`mylib/mylib.cpp`:

```cpp
#include "mylib.h"
#include <iostream>

void hello() {
    std::cout << "Hello, World!" << std::endl;
}
```

#### 1.2. Create the CMakeLists.txt for the Library

Create a `CMakeLists.txt` file in the `mylib` directory.

`mylib/CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.10)
project(mylib)

add_library(mylib SHARED mylib.cpp)

target_include_directories(mylib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
```

### Step 2: Create the Main Program

#### 2.1. Create the Main Program Source Files

Next, create a directory for your main program. Let's call this directory `main`.

`main/main.cpp`:

```cpp
#include <iostream>
#include "mylib.h"

int main() {
    hello();
    return 0;
}
```

#### 2.2. Create the CMakeLists.txt for the Main Program

Create a `CMakeLists.txt` file in the `main` directory.

`main/CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.10)
project(main)

add_subdirectory(../mylib ${CMAKE_BINARY_DIR}/mylib)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE mylib)
```

### Step 3: Build the Project

#### 3.1. Create the Top-Level CMakeLists.txt

Create a top-level `CMakeLists.txt` file in the root directory of your project.

`CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.10)

add_subdirectory(mylib)
add_subdirectory(main)
```

#### 3.2. Build the Project Using CMake

Open a terminal, navigate to the root directory of your project, and run the following commands:

```sh
mkdir build
cd build
cmake ..
cmake --build .
```

### Step 4: Run the Program

After building the project, you can run the main program. If you are on a Unix-like system (Linux, macOS), navigate to the `build/main` directory and run:

```sh
./main
```

On Windows, the executable will be in the `build\main\Debug` or `build\main\Release` directory, depending on the build type:

```sh
main.exe
```

You should see the output:

```
Hello, World!
```

This process creates a dynamic library (`mylib`) and a main program that uses this library, all managed with CMake.
