#include "socketcan/socketcan.h"

#include <chrono>
#include <iostream>
#include <thread>

#include <cstring>

int main() {
    transport::SocketCan s_can("vcan0");
    while(true) {
        can_frame frame;
        frame.can_id = 0x555;
        frame.can_dlc = 5;
        memcpy(frame.data, "Hello", frame.can_dlc);
        s_can.Write(frame);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    return 0;
}