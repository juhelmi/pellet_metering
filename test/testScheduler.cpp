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

#include "GPIO_read.h"

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
    Temperature_room dummyTemp(9*intervalX/5, 2, 3);
    dummyTemp.setLocation("Out door");
    Air_pressure dummyPressure(9*intervalX/4, 2,3);
    dummyPressure.setLocation("Out door");
    BME280_sensor dummyBME(4+4*intervalX, 4,0x77);

    Temperature_room temp2(3*intervalX/2, 3, 3);
    temp2.setLocation("Storage");
    Air_pressure press2(2*intervalX, 3, 3);
    press2.setLocation("Storage");

    BOOST_CHECK_EQUAL(readTimer.getSensorCount(), 0);
    BOOST_CHECK_EQUAL(readTimer.getPollingListSize(), 0);

    readTimer.addSensor(&dummyTemp);
    readTimer.addSensor(&dummyPressure);
    readTimer.addSensor(&dummyBME);
    readTimer.addSensor(&temp2);
    readTimer.addSensor(&press2);

    BOOST_CHECK_EQUAL(readTimer.getSensorCount(), 5);
    BOOST_CHECK_EQUAL(readTimer.getPollingListSize(), 5);

    GPIO_read dummyPin(2*intervalX-5, 7);
    dummyPin.setLocation("Just IO read");
    readTimer.addSensor(&dummyPin);
    BOOST_CHECK_EQUAL(readTimer.getSensorCount(), 6);

    Sensor *p_sens = readTimer.getNextTimedSensor();
    cout << "First name in list " << p_sens->getName() << endl;
    BOOST_CHECK_EQUAL(p_sens->getName(), "Temperature_room");
    tMeasurementTime nextHit = readTimer.getNextLaunchTime();
    tMeasurementTime now = getCurrentTime();
    cout << "Now " << now << " next " << nextHit << " Diff: " << nextHit - now << endl;
    BOOST_CHECK_EQUAL(compareTimeInMsRange(nextHit, check_interval*1.5), true);

    for (int i=0; i<10; i++)
    {
        p_sens = readTimer.getNextTimedSensor();
        cout << "First name in list " << p_sens->getName() << " Location: " << p_sens->getLocation() << endl;
        readTimer.pollTimedSensors();
        usleep(check_interval/2*1000);
    }
}

