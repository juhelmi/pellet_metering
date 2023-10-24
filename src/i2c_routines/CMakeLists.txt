set(LIBRARY_SOURCES
    "i2c_routines.cc"
    )
set(LIBRARY_HEADERS
    "i2c_routines.h"
    )

add_library(${LIBRARY_NAME} STATIC
    ${LIBRARY_SOURCES}
    ${LIBRARY_HEADERS})
target_include_directories(${LIBRARY_NAME} PUBLIC
    "./"
    "${CMAKE_BINARY_DIR}/configured_files/include")

# Taglib include directories
include_directories("${CMAKE_SOURCE_DIR}/external/taglib/taglib"
  "${CMAKE_SOURCE_DIR}/external/taglib/taglib/toolkit"
  "${CMAKE_SOURCE_DIR}/build/external/taglib"
  )

# Pointer to json include also
include_directories(  "${CMAKE_SOURCE_DIR}/external/json/include")
