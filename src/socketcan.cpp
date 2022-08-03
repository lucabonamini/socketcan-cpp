#include "socketcan/socketcan.h"

#include <stdexcept>

#include <cstring>

#include <linux/can/raw.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

namespace transport {
SocketCan::SocketCan(const std::string &interface) {
  socket_descriptor_ = socket(PF_CAN, SOCK_RAW, CAN_RAW);
  if (socket_descriptor_ < 0) {
    throw std::runtime_error("Error in create socket.");
  }
  struct sockaddr_can can_address {};
  struct ifreq network_device {};
  strcpy(network_device.ifr_ifrn.ifrn_name, interface.c_str());
  ioctl(socket_descriptor_, SIOCGIFINDEX, &network_device);

  can_address.can_family = AF_CAN;
  can_address.can_ifindex = network_device.ifr_ifru.ifru_ivalue;

  if (bind(socket_descriptor_,
           reinterpret_cast<struct sockaddr *>(&can_address),
           sizeof(can_address)) < 0) {
    throw std::runtime_error("Error in bind socket.");
  }
}
std::optional<can_frame> SocketCan::Read() const {
  can_frame frame{};
  auto nbytes = ::read(socket_descriptor_, &frame, sizeof(struct can_frame));
  if (nbytes < 0) {
    return {};
  }
  #ifdef NDEBUG
  printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
  for (auto i = 0; i < frame.can_dlc; i++) {
    printf("%02X ", frame.data[i]);
  }
  printf("\r\n");
  #endif
  return std::make_optional<can_frame>(frame);
}
bool SocketCan::Write(const can_frame& frame) const {
  if (write(socket_descriptor_, &frame, sizeof(struct can_frame)) < 0) {
    return false;
  }
  return true;
}
} // namespace transport