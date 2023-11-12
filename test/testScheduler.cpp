#include <cstdlib>
#include <iostream>
#include <list>

#include "Measurement.h"
#include "Scheduler.h"
#include "Sensor.h"
#include "I2C_sensor.h"
#include "ADC_sensor.h"
#include "Air_pressure.h"
#include "Temperature_room.h"
#include "BME280_sensor.h"

using namespace std;

#define BOOST_TEST_MODULE Scheduler_test Test
#include <boost/test/included/unit_test.hpp>

class Scheduler_test : public Scheduler
{
public:
    int getSensorCount()
    {
        return mSensors.size();
    }
    int getPollingListSize()
    {
        return mNextPolls.size();
    }
    Sensor* getNextTimedSensor()
    {
        auto it= mNextPolls.begin();
        return it->second;
    }
    tMeasurementTime getNextLaunchTime()
    {
        auto it= mNextPolls.begin();
        return it->first;
    }
};

BOOST_AUTO_TEST_CASE(Scheduler_test_Test)
{
	Scheduler_test readTimer ;

    int check_interval = 50;
    int intervalX = check_interval*1000*1000;

    BOOST_CHECK_EQUAL(readTimer.getSensorCount(), 0);
    BOOST_CHECK_EQUAL(readTimer.getPollingListSize(), 0);
    Temperature_room dummyTemp(1*intervalX, 2, 3);
    Air_pressure dummyPressure(2*intervalX, 2,3);
    BME280_sensor dummyBME(4+1*intervalX, 4,0x77);

    Temperature_room temp2(intervalX, 3, 3);
    Air_pressure press2(2*intervalX, 3, 3);

    BOOST_CHECK_EQUAL(readTimer.getSensorCount(), 0);
    BOOST_CHECK_EQUAL(readTimer.getPollingListSize(), 0);

    readTimer.addSensor(&dummyTemp);
    readTimer.addSensor(&dummyPressure);
    readTimer.addSensor(&dummyBME);

    BOOST_CHECK_EQUAL(readTimer.getSensorCount(), 3);
    BOOST_CHECK_EQUAL(readTimer.getPollingListSize(), 3);

    Sensor *p_sens = readTimer.getNextTimedSensor();
    cout << "First name in list " << p_sens->getName() << endl;
    BOOST_CHECK_EQUAL(p_sens->getName(), "Temperature_room");
    tMeasurementTime nextHit = readTimer.getNextLaunchTime();
    tMeasurementTime now = getCurrentTime();
    cout << "Now " << now << " next " << nextHit << " Diff: " << nextHit - now << endl;
    BOOST_CHECK_EQUAL(compareTimeInMsRange(nextHit, check_interval), true);

    for (int i=0; i<5; i++)
    {
        readTimer.pollTimedSensors();
        usleep(50*1000);
    }
}

