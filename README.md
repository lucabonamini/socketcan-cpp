# SocketCAN-cpp
A simple library for CAN communication, written in C++

## Dependencies

To install dependencies, just run `./install_dependencies.sh`

## Build

`mkdir build && cd build && cmake .. && make -j`

## Run examples

* Setup a virtual CAN interface using `vcan.sh` script
* Compile with `BUILD_TESTS` flag set to `ON`
* In a terminal, launch `./build/receiver`
* In another terminal, launch `./build/transmit`
