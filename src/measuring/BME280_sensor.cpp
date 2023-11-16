#include "BME280_sensor.h"
#include <iostream>

#include "config.hpp"

#include <linux/i2c-dev.h>
#include <sys/ioctl.h>

/******************************************************************************/
/*!                         System header files                               */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
using namespace std;

//
/*!
 * @brief This function reading the sensor's registers through I2C bus.
 */
int8_t user_i2c_read(uint8_t reg_addr, uint8_t *data, uint32_t len, void *intf_ptr)
{
    struct identifier id;

    id = *((struct identifier *)intf_ptr);
    write(id.fd, &reg_addr, 1);
    if (read(id.fd, data, len) != len) {
        return -1;
    }

    return 0;
}

/*!
 * @brief This function provides the delay for required time (Microseconds) as per the input provided in some of the
 * APIs
 */
void user_delay_us(uint32_t period, void *intf_ptr)
{
    usleep(period);
}

/*!
 * @brief This function for writing the sensor's registers through I2C bus.
 */
int8_t user_i2c_write(uint8_t reg_addr, const uint8_t *data, uint32_t len, void *intf_ptr)
{
    uint8_t *buf;
    struct identifier id;

    id = *((struct identifier *)intf_ptr);

    buf = (uint8_t*)malloc(len + 1);
    buf[0] = reg_addr;
    memcpy(buf + 1, data, len);
    if (write(id.fd, buf, len + 1) < (uint16_t)len)
    {
        return BME280_E_COMM_FAIL;
    }

    free(buf);

    return BME280_OK;
}



// Constructors/Destructors
//  

bool BME280_sensor::mHwDriverInitialized = false;

BME280_sensor::BME280_sensor(int pollingInterval, int bus, int address) : Sensor(pollingInterval), I2C_sensor(pollingInterval, bus, address)
{
  this->mTag = "BME280_sensor";
  this->mSensor_use = eBME_not_set;
  // Initialize HW driver later as it might fail.
}

BME280_sensor::~BME280_sensor()
{
}

//  
// Methods
//  


// Accessor methods
//  


// Other methods
//  

bool BME280_sensor::initAttributes()
{
  if (mSensor_use == eBME_not_set)
  {
    return false;
  }
  if (!mHwDriverInitialized)
  {
    /* Variable to define the result */
    int8_t rslt = BME280_OK;
    char buf[50];

    snprintf(buf, sizeof(buf)-1, "/dev/i2c-%d", mBus);
    if ((mId.fd = open(buf, O_RDWR)) < 0)
    {
        fprintf(stderr, "Failed to open the i2c bus %s\n", buf);
        return false;
    }
    /* Make sure to select BME280_I2C_ADDR_PRIM or BME280_I2C_ADDR_SEC as needed */
    mId.dev_addr = mAddress;
    if (ioctl(mId.fd, I2C_SLAVE, mId.dev_addr) < 0)
    {
        fprintf(stderr, "Failed to acquire bus access and/or talk to slave.\n");
        return false;
    }
    mDev.intf = BME280_I2C_INTF;
    mDev.read = user_i2c_read;
    mDev.write = user_i2c_write;
    mDev.delay_us = user_delay_us;

    /* Update interface pointer with the structure that contains both device address and file descriptor */
    mDev.intf_ptr = &mId;

    /* Initialize the bme280 */
    rslt = bme280_init(&mDev);
    if (rslt != BME280_OK)
    {
        fprintf(stderr, "Failed to initialize the device (code %+d).\n", rslt);
        return false;
    }

  }
  return false;
}

bool BME280_sensor::setWorkingMode(sensor_use_type wanted_use)
{
  mSensor_use = wanted_use;
  return mSensor_use != eBME_not_set;
}

double BME280_sensor::getTemperature()
{
  if (simulate_hw)
  {
    cout << "Simulation coming" << endl;
  } else {
  }
  return 0;
}

double BME280_sensor::getPressure()
{
  return 0;
}

double BME280_sensor::getHumidity()
{
  switch (mSensor_use )
  {
    default:
    case eBME_not_set:
      return 0;
    case eBME_tph:
      return 0;
    case eBMP_tp:
      // not available on this chip
      return 0;
  }
  return 0;
}

