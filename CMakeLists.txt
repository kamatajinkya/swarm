cmake_minimum_required(VERSION 2.8)
project(swarm)

set(CMAKE_C_STANDARD 99)

set(DEVICE_TYPE_x86 1)
set(DEVICE_TYPE_x86_TEST 2)
set(DEVICE_TYPE DEVICE_TYPE_x86)

include_directories(include)
add_executable(swarm src/main.c src/common.c src/xbee.c src/device.c)
