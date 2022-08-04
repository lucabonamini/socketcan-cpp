#include "socketcan/socketcan.h"

#include <iostream>
#include <thread>

int main() {
  ::transport::SocketCan s_can("vcan0");
  while (true) {
    s_can.Read();
  }
  return 0;
}