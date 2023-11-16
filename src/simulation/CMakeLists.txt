
message("Simulates Raspberry Pi HW. Used library is ${SIMLIBRARY_NAME}.")

set(SIMLIBRARY_SOURCES
    "bme280.c"
    "sim_gpio.c")
set(SIMLIBRARY_HEADERS
    "bme280.h"
    "pi-gpio.h")

add_library(${SIMLIBRARY_NAME}  STATIC
    ${SIMLIBRARY_SOURCES}
    ${SIMLIBRARY_HEADERS})
target_include_directories(${SIMLIBRARY_NAME} PUBLIC
    "./"
    #"${CMAKE_BINARY_DIR}/configured_files/include"
    )
