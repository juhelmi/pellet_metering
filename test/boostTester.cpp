
#include <cstdlib>
#include <iostream>
#include <list>

#include "Scheduler.h"
#include "Sensor.h"
#include "ADC_sensor.h"
#include "Air_pressure.h"
#include "BME280_sensor.h"

using namespace std;

#define BOOST_TEST_MODULE scheduling basics
// Header only
//#include <boost/test/included/unit_test.hpp>
// Shared library requires
#define BOOST_TEST_DYN_LINK
// statically linked
#include <boost/test/unit_test.hpp>
namespace utf = boost::unit_test;
namespace tt = boost::test_tools;

// https://www.boost.org/doc/libs/1_83_0/libs/test/doc/html/boost_test/utf_reference.html

BOOST_AUTO_TEST_CASE(scheduling_basics)
{
	Scheduler readTimer ;

        int intervalX = 10000;
        BME280_sensor bmeHw(intervalX, 1, 0x76);

        ADC_sensor dummyADC(1*intervalX, 1,2);
        Air_pressure dummyPressure(&bmeHw, 4*intervalX, 2,3);
        BME280_sensor dummyBME(4+1*intervalX, 4,0x77);

        readTimer.addSensor(&dummyADC);
        readTimer.addSensor(&dummyPressure);
        readTimer.addSensor(&dummyBME);

        for (int i=0; i<6; i++)
        {
            readTimer.pollTimedSensors();
            usleep(1);
        }
}

