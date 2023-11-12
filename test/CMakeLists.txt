message("Test definitions are under study")

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

set(UNIT_TEST MyTestTargetName)
# https://cmake.org/cmake/help/latest/command/add_test.html#command:add_test
add_test(NAME ${UNIT_TEST} COMMAND ${UNIT_TEST})
#add_custom_target(run_unit_test ALL COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure     DEPENDS ${UNIT_TEST})

add_executable(test_unit
    boostTester.cpp
    #tests/test_one.cpp
    #tests/test_two.cpp
)
add_executable(test_unit2
    temperatureSensorTest.cpp
)

add_executable(test_unit3
    testScheduler.cpp
)

target_link_libraries(test_unit Boost::unit_test_framework ${LIBRARY_NAME} ${MEASURING_NAME} )
target_link_libraries(test_unit2 Boost::unit_test_framework ${LIBRARY_NAME} ${MEASURING_NAME} )
target_link_libraries(test_unit3 Boost::unit_test_framework ${LIBRARY_NAME} ${MEASURING_NAME} )

add_test(
  NAME
    test_unit
  COMMAND
    $<TARGET_FILE:test_unit>
  )

if(false)
target_link_libraries(testTheTester
  PRIVATE
  Boost::filesystem
  Boost::system
  Boost::unit_test_framework
  )
endif()

message("End of test part")
