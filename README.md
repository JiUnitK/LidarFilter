## Prerequisites
- CMake version 3.14 or newer
- C++11 compiler or newer

Note: If you are building the unit tests for the first time, you will also need internet access to download the Google gtest framework into the build directory. This is automatically downloaded to the build directory by CMake. You do not need to install the gtest framework manually.

## How to Run Unit Tests
From the project root directory, run the following commands
```
cmake -S . -B build
cmake --build build
cd build && test_filter
```