
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
#include <boost/test/included/unit_test.hpp>

// https://www.boost.org/doc/libs/1_83_0/libs/test/doc/html/boost_test/utf_reference.html

BOOST_AUTO_TEST_CASE(scheduling_basics)
{
	Scheduler readTimer ;

        int intervalX = 10000;

        ADC_sensor dummyADC(1*intervalX, 1,2);
        Air_pressure dummyPressure(2*intervalX, 2,3);
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

