project(socketcan_tests)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(test_socketcan test_socketcan.cpp)
target_compile_options(test_socketcan PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-std=c++17>)
target_link_libraries(test_socketcan PRIVATE
  PRIVATE
    SocketCan
    gtest_main
)
add_test(NAME test_socketcan COMMAND test_socketcan)

add_executable(receive receive.cpp)
target_compile_options(receive PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-std=c++17>)
target_link_libraries(receive
  PRIVATE
    SocketCan
    pthread
)

add_executable(transmit transmit.cpp)
target_compile_options(transmit PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-std=c++17>)
target_link_libraries(transmit
  PRIVATE
    SocketCan
    pthread
)
