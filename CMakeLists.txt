cmake_minimum_required(VERSION 3.22)

project(mc_revo2 VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

find_package(mc_rtc REQUIRED)
find_description_package(revo2_description)

message("-- REVO2_DESCRIPTION_PATH: ${REVO2_DESCRIPTION_PATH}")
configure_file(src/config.h.in "${CMAKE_CURRENT_BINARY_DIR}/include/config.h")

macro(add_module NAME)
  add_robot(${NAME} src/${NAME}.cpp src/${NAME}.h)
  target_include_directories(${NAME}
                             PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/include")
endmacro()

add_module(revo2)

option(DISABLE_TESTS "Disable unit tests" OFF)
if(NOT ${DISABLE_TESTS})
  enable_testing()
  add_subdirectory(tests)
endif()
