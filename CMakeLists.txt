cmake_minimum_required(VERSION 2.8)
project(swarm)

set(CMAKE_C_STANDARD 99)

#platform information
set(DEVICE_TYPE_x86 "1")

#select platform
set(DEVICE_TYPE ${DEVICE_TYPE_x86})
set(TEST_MODE ON)

#test mode specific configurations
if (${TEST_MODE})
 add_definitions(-DDEVICE_TEST_MODE)
endif ()

set(EXECUTABLES src/main.c src/common.c src/xbee.c)

#x86 specific configurations
if(${DEVICE_TYPE} MATCHES ${DEVICE_TYPE_x86})
 list(APPEND EXECUTABLES src/device_x86.c)
endif()

include_directories(include)
add_executable(swarm ${EXECUTABLES})
