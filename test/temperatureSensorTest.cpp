
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
// Instruction to run tests by name
// https://www.boost.org/doc/libs/1_83_0/libs/test/doc/html/boost_test/runtime_config/test_unit_filtering.html

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

BOOST_AUTO_TEST_CASE(i2c_check_test)
{
	Scheduler readTimer ;

        int intervalX = 1*1000*1000;
        I2C_sensor_test statusCheck(intervalX, 0,0);

        BOOST_CHECK_EQUAL(statusCheck.getAllUsedCount(), 1);
        BOOST_CHECK_EQUAL(statusCheck.isUsed(2,3), false);
        BME280_sensor devBME(4+1*intervalX, 1, 0x76);
        BME280_sensor devBMP(4+1*intervalX, 1, 0x77);
        BOOST_CHECK_EQUAL(statusCheck.getAllUsedCount(), 3);

        BOOST_CHECK_EQUAL(statusCheck.getMapSize(), 3);

        // Set extra settings for BME280
        devBME.setWorkingMode(BME280_sensor::eBME_tph);
        devBMP.setWorkingMode(BME280_sensor::eBMP_tp);
        BOOST_CHECK_EQUAL(devBME.getLastBmeErrorCode(), BME280_OK);
        BOOST_CHECK_EQUAL(devBMP.getLastBmeErrorCode(), BME280_OK);

        readTimer.addSensor(&devBME);
        readTimer.addSensor(&devBMP);

        for (int i=0; i<2; i++)
        {
            readTimer.pollTimedSensors();
            BOOST_CHECK_EQUAL(devBME.getLastBmeErrorCode(), BME280_OK);
            //usleep(1*1000);
            usleep(intervalX/2);
        }
        // Some value should be received
        BOOST_CHECK_NE(devBME.getTemperature(), 0);
        BOOST_CHECK_NE(devBME.getPressure(), 0);
        BOOST_CHECK_NE(devBME.getHumidity(), 0);
        BOOST_CHECK_NE(devBMP.getTemperature(), 0);
        BOOST_CHECK_NE(devBMP.getPressure(), 0);
        BOOST_CHECK_EQUAL(devBMP.getHumidity(), 0);
}

BOOST_AUTO_TEST_CASE(device_share_test)
{
    Scheduler readTimer ;
    int intervalX = 1*1000*1000;

    I2C_sensor_test statusCheck(intervalX, 0,0);
    BOOST_CHECK_EQUAL(statusCheck.getAllUsedCount(), 1);
    BME280_sensor *p_bme = new BME280_sensor(intervalX, 2, 0x78);
    BOOST_CHECK_EQUAL(statusCheck.getAllUsedCount(), 2);
    delete p_bme;
    BOOST_CHECK_EQUAL(statusCheck.getAllUsedCount(), 1);

    BME280_sensor bme1(intervalX, 1, 0x76);
    bme1.setWorkingMode(BME280_sensor::eBME_tph);

    Air_pressure devAP(&bme1, intervalX, 1, 0x76);
    Temperature_room devTemp(&bme1, intervalX, 1, 0x76);
    BOOST_CHECK_EQUAL(statusCheck.getAllUsedCount(), 2);

    readTimer.addSensor(&devAP);
    readTimer.addSensor(&devTemp);

    cout << "Loop\n";
    for (int i=0; i<2; i++)
    {
        readTimer.pollTimedSensors();
        BOOST_CHECK_EQUAL(bme1.getLastBmeErrorCode(), BME280_OK);
        //usleep(1*1000);
        usleep(intervalX/2);
    }
    cout << "Air_pressure " << devAP.getPressure() << endl;
    cout << "Temperature " << devTemp.getTemperature() << endl;
}
