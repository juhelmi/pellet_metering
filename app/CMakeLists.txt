 
set(EXE_SOURCES
    "main.cc")

add_executable(${EXECUTABLE_NAME} ${EXE_SOURCES})
target_link_libraries(${EXECUTABLE_NAME} PUBLIC
    ${LIBRARY_NAME}
    ${MEASURING_NAME}
    nlohmann_json
    ${Boost_LIBRARIES}
    ${PIGPIO_LIBRARY}
    ${BME280_LIBRARY_NAME}
    ${SIMLIBRARY_NAME}
    )

