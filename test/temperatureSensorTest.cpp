
#include <cstdlib>
#include <iostream>
#include <list>

#include "Scheduler.h"
#include "Sensor.h"
#include "I2C_sensor.h"
#include "ADC_sensor.h"
#include "Air_pressure.h"
#include "Temperature_room.h"
#include "BME280_sensor.h"

using namespace std;

#define BOOST_TEST_MODULE i2c check Test
//#include <boost/test/included/unit_test.hpp>
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
namespace utf = boost::unit_test;
namespace tt = boost::test_tools;

// https://www.boost.org/doc/libs/1_83_0/libs/test/doc/html/boost_test/utf_reference.html

class I2C_sensor_test : public I2C_sensor
{
public:
    I2C_sensor_test(int pollingInterval, int bus, int address) : Sensor(pollingInterval), I2C_sensor(pollingInterval, bus, address)
    {
    };
    int isUsed(int port, int address)
    {
        return this->isSensorUsed(port, address);
    }
    int getAllUsedCount()
    {
        return mAllSensorCount;
    }
    int getMapSize()
    {
        return mMapOfActiveSensors.size();
    }
};

#if 1
BOOST_AUTO_TEST_CASE(i2c_check_test)
{
	Scheduler readTimer ;

        int intervalX = 100*1000;
        I2C_sensor_test statusCheck(intervalX, 0,0);

        BOOST_CHECK_EQUAL(statusCheck.getAllUsedCount(), 1);
        BOOST_CHECK_EQUAL(statusCheck.isUsed(2,3), false);
        Temperature_room dummyTemp(1*intervalX, 2, 3);
        BOOST_CHECK_EQUAL(statusCheck.getAllUsedCount(), 2);
        BOOST_CHECK_EQUAL(statusCheck.isUsed(2,3), true);
        Air_pressure dummyPressure(2*intervalX, 2,3);
        BME280_sensor dummyBME(4+1*intervalX, 4,0x77);
        BOOST_CHECK_EQUAL(statusCheck.getAllUsedCount(), 4);

        Temperature_room temp2(intervalX, 3, 3);
        Air_pressure press2(2*intervalX, 3, 3);
        BOOST_CHECK_EQUAL(statusCheck.getAllUsedCount(), 6);
        BOOST_CHECK_EQUAL(statusCheck.getMapSize(), 4);

        readTimer.addSensor(&dummyTemp);
        readTimer.addSensor(&dummyPressure);
        readTimer.addSensor(&dummyBME);

        for (int i=0; i<2; i++)
        {
            readTimer.pollTimedSensors();
            //usleep(1*1000);
            usleep(10);
        }
}
#else
BOOST_AUTO_TEST_CASE(i2c_check_test)
{
	list<int> i_list;
	cout << "Boost test study i2c" << endl;
	i_list.push_back(1);
    BOOST_CHECK_EQUAL(i_list.size(), 1);
	i_list.push_back(2);
    BOOST_CHECK_EQUAL(i_list.back(), 2);
	i_list.push_front(3);
	BOOST_REQUIRE(i_list.front() == 3);
	BOOST_REQUIRE(i_list.back() == 2);
	BOOST_REQUIRE(i_list.size() > 2);
}
#endif

