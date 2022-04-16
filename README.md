## Prerequisites
- CMake version 3.14 or newer
- C++11 compiler or newer

Note: If you are building the unit tests for the first time, you will also need internet access to download the Google gtest framework into the build directory. This is automatically downloaded to the build directory by CMake. You do not need to install the gtest framework manually.

## Running the Unit Tests
If this is the first time you are building, run the following command from the project root to setup the initial build directory:
```
cmake -S . -B build
```

Build the test executable:
```
cmake --build build
```

And then run the test executable:
```
build/test_filters
```

