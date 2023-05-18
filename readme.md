# Splay Trees
This is a simple Splay Tree implementation. The implementation is based on Sleator and Tarjans paper on Splay Trees.

The splay tree implementation is generic and can store any object, as long as they implement the comparison operators >, ==, <. Refer to ```test/test.cpp``` for usage examples.

The project uses make and cmake to compile.

## Building

To build and configure the project run
```
mkdir build
cd build
cmake ..
cmake --build .
```

## Demo
A small demo program is included. Execute 
```
./build/main
```
The following commands to stdin is supported:

Insert a node with integer key x.
```
insert x
```
Remove the node with integer key x.
```
delete x
```
Print the splay tree. 
```
print
```

## Benchmarks
The benchmarking code, can be executed using 
```
./build/test_runner
```


## Tests
A small set of tests is included, demonstrating basic functionality of the splay tree implementation. Catch2 is used as testing framework.

Run the tests by executing
```
cd build
ctest
```

