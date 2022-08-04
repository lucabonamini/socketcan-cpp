#include "socketcan/socketcan.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;

TEST(SocketCAN, CreateSocketCanObject) {
  EXPECT_NO_THROW(::transport::SocketCan socket("vcan0"));
}

int main(int argc, char *argv[0]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}