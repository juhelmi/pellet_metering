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
//#include <boost/test/included/unit_test.hpp>
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
namespace utf = boost::unit_test;
namespace tt = boost::test_tools;


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
        if (mNextPolls.size() == 0)
        {
            return nullptr;
        }
        auto it= mNextPolls.begin();
        return it->second;
    }
    tMeasurementTime getNextLaunchTime()
    {
        auto it= mNextPolls.begin();
        return it->first;
    }
};

BOOST_AUTO_TEST_SUITE(testScheduler)

BOOST_AUTO_TEST_CASE(Simple)
{
#if SIMULATE_HW == false
    cout << "GPIO setup" << endl;
    setup();
#endif
    BOOST_TEST(true, "Simple tests for Scheduler.");
    Scheduler_test *p_sch = new Scheduler_test;
    BOOST_TEST(p_sch->getPollingListSize() == 0);
    delete p_sch;
    std::shared_ptr<Scheduler_test> sp_sch = std::make_shared<Scheduler_test>();
    BOOST_TEST(sp_sch->getPollingListSize() == 0, "List is expected to be empty");
    BOOST_TEST(sp_sch->getNextTimedSensor() == nullptr);
#if SIMULATE_HW == false
    //cout << "GPIO cleanup" << endl;
    //cleanup();
#endif
}

BOOST_AUTO_TEST_CASE(Scheduler_test_Test)
{
	Scheduler_test readTimer ;

#if SIMULATE_HW == false
    cout << "GPIO setup" << endl;
    setup(); // duplicate call do not reinitialize
#endif
    int check_interval = 50;
    int intervalX = check_interval*1000*1000;

    tMeasurementTime now = getCurrentTime();

    BOOST_CHECK_EQUAL(readTimer.getSensorCount(), 0);
    BOOST_CHECK_EQUAL(readTimer.getPollingListSize(), 0);

    BME280_sensor bmeHw1(intervalX, 1, 0x76);
    BME280_sensor bmeHw2(intervalX, 1, 0x77);

    Temperature_room dummyTemp(&bmeHw1, intervalX/5, 2, 3);
    dummyTemp.setLocation("Out door");
    Air_pressure dummyPressure(&bmeHw1, 9*intervalX/4, 2,3);
    dummyPressure.setLocation("Out door");
    BME280_sensor dummyBME(4+4*intervalX, 4,0x77);

    Temperature_room temp2(&bmeHw2, 3*intervalX/2, 1, 0x77);
    temp2.setLocation("Storage");
    Air_pressure press2(&bmeHw2, 2*intervalX, 3, 3);
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
    BOOST_TEST(dummyPin.getName() == "GPIO_read");

    Sensor *p_sens = readTimer.getNextTimedSensor();
    cout << "First name in list " << p_sens->getName() << endl;
    BOOST_CHECK_EQUAL(p_sens->getName(), "Temperature_room");

    // Not so usefull to test these time independent routines, but this could be used later.
    BOOST_TEST((double)(getCurrentTime() - now) <= 1e6, tt::tolerance(1.0));
    tMeasurementTime nextHit = readTimer.getNextLaunchTime();
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

BOOST_AUTO_TEST_SUITE_END() // testScheduler

