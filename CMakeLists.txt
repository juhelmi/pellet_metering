cmake_minimum_required(VERSION 3.0)

project(pellet_metering VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

#set(SIMULATION  true)
# set(SIMULATION  false)

set(LIBRARY_NAME Library)
set(MEASURING_NAME Measuring)
set(EXECUTABLE_NAME pellets)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
include(AddGitSubmodule)

# Debug in KDevelop
set(CMAKE_BUILD_TYPE Debug)


add_git_submodule(external/json)
add_git_submodule(external/BME280_driver)

# https://cmake.org/cmake/help/git-master/module/FindBoost.html
# Use following lines when boost is OS library
# Compile Boost from source. Compile notes on doc directory
FIND_PACKAGE( Boost 1.83 COMPONENTS program_options REQUIRED )
# Ubuntu 22.04 has 1.74
# FIND_PACKAGE( Boost 1.74 COMPONENTS program_options REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

# https://github.com/joan2937/pigpio/blob/master/util/Findpigpio.cmake
set(LINUX_USR_LIB_PATH "/usr/lib")  # ${LINUX_USR_LIB_PATH}
set(PI-GPIO_NAME libpi-gpio.so)
#find_library(PIGPIO_LIBRARY NAMES libpi-gpio.so HINTS /usr/local/lib)
find_library(PIGPIO_LIBRARY PATHS ${PI-GPIO_NAME} HINTS /usr/local/lib)
if(PIGPIO_LIBRARY)
    message("Pi-gpio ${PI-GPIO_NAME} found, cmake running in Raspberry Pi with needed library")
    set(SIMULATION  false)
else()
    message("HW library ${PI-GPIO_NAME} not found libpi-gpio and simulation for HW will be option.")
    set(SIMULATION  true)
endif()

add_subdirectory(configured)
add_subdirectory(external)
add_subdirectory(src)
add_subdirectory(app)
#Unit testing
add_subdirectory(test)


