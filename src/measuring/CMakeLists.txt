set(MEASURING_SOURCES
    "ADC_sensor.cpp"
    "Air_pressure.cpp"
    "GPIO_control.cpp"
    "GPIO_read.cpp"
    "I2C_sensor.cpp"
    "K_TypeTemperature.cpp"
    "Measurement.cpp"
    "Scheduler.cpp"
    "Sensor.cpp"
    "Temperature_room.cpp"
    )
set(MEASURING_HEADERS
    "ADC_sensor.h"
    "Air_pressure.h"
    "GPIO_control.h"
    "GPIO_read.h"
    "I2C_sensor.h"
    "K_TypeTemperature.h"
    "Measurement.h"
    "Scheduler.h"
    "Sensor.h"
    "Temperature_room.h"
    )

add_library(${MEASURING_NAME} STATIC
    ${MEASURING_SOURCES}
    ${MEASURING_HEADERS} )
target_include_directories(${MEASURING_NAME} PUBLIC
    "./"
    "${CMAKE_BINARY_DIR}/configured_files/include")

# Taglib include directories
include_directories("${CMAKE_SOURCE_DIR}/external/taglib/taglib"
  "${CMAKE_SOURCE_DIR}/external/taglib/taglib/toolkit"
  "${CMAKE_SOURCE_DIR}/build/external/taglib"
  )

# Pointer to json include also
include_directories(  "${CMAKE_SOURCE_DIR}/external/json/include")
