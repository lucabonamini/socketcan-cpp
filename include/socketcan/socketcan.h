#pragma once

#include <optional>
#include <string>

#include <linux/can.h>

namespace transport {
class SocketCan {
public:
  SocketCan() = delete;
  explicit SocketCan(const std::string &interface);
  SocketCan(const SocketCan &) = delete;
  SocketCan(SocketCan &&) = delete;
  virtual ~SocketCan() noexcept = default;
  std::optional<can_frame> Read() const;
  bool Write(const can_frame &frame) const;

private:
  int socket_descriptor_;
};
} // namespace transport