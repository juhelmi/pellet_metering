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
#include "bme280.h"

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

// Copied routine, to be removed when not needed
void print_sensor_data(struct bme280_data *comp_data)
{
    float temp, press, hum;

#ifdef BME280_DOUBLE_ENABLE
    temp = comp_data->temperature;
    press = 0.01 * comp_data->pressure;
    hum = comp_data->humidity;
#else
#ifdef BME280_64BIT_ENABLE
    temp = 0.01f * comp_data->temperature;
    press = 0.0001f * comp_data->pressure;
    hum = 1.0f / 1024.0f * comp_data->humidity;
#else
    temp = 0.01f * comp_data->temperature;
    press = 0.01f * comp_data->pressure;
    hum = 1.0f / 1024.0f * comp_data->humidity;
#endif
#endif
    printf("%0.2lf deg C, %0.2lf hPa, %0.2lf%%\n", temp, press, hum);
}

// Constructors/Destructors
//  

bool BME280_sensor::mHwDriverInitialized = false;

BME280_sensor::BME280_sensor(int pollingInterval, int bus, int address) : Sensor(pollingInterval), I2C_sensor(pollingInterval, bus, address)
{
  mTag = "BME280_sensor";
  mSensor_use = eBME_not_set;
  mRslt = BME280_OK;
  mComp_data = {0};
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
    mRslt = BME280_OK;
    char buf[50];

    snprintf(buf, sizeof(buf)-1, "/dev/i2c-%d", mBus);
    if ((mId.fd = open(buf, O_RDWR)) < 0)
    {
        fprintf(stderr, "Failed to open the i2c bus %s\n", buf);
        mRslt = BME280_E_DEV_OPEN_FAIL;
        return false;
    }
    /* Make sure to select BME280_I2C_ADDR_PRIM or BME280_I2C_ADDR_SEC as needed */
    mId.dev_addr = mAddress;
    if (ioctl(mId.fd, I2C_SLAVE, mId.dev_addr) < 0)
    {
        fprintf(stderr, "Failed to acquire bus access void executeSensorValueRead() override;and/or talk to slave.\n");
        mRslt = BME280_E_DEV_ID_ADDR_FAIL;
        return false;
    }
    mDev.intf = BME280_I2C_INTF;
    mDev.read = user_i2c_read;
    mDev.write = user_i2c_write;
    mDev.delay_us = user_delay_us;

    /* Update interface pointer with the structure that contains both device address and file descriptor */
    mDev.intf_ptr = &mId;

    /* Initialize the bme280 */
    mRslt = bme280_init(&mDev);
    if (mRslt != BME280_OK)
    {
        fprintf(stderr, "Failed to initialize the device (code %+d). Device do not respond.\n", mRslt);
        return false;
    }
    // Stream mode initialization, example function stream_sensor_data_forced_mode in linux_userspace.c

   /* Structure to store the settings */
    struct bme280_settings settings = {0};

    /* Variable to store minimum wait time between consecutive measurement in force mode */
    //uint32_t req_delay;

    /* Structure to get the pressure, temperature and humidity values */
    // struct bme280_data comp_data;

    /* Get the current sensor settings */
    mRslt = bme280_get_sensor_settings(&settings, &mDev);
    if (mRslt != BME280_OK)
    {
        fprintf(stderr, "Failed to get sensor settings (code %+d).", mRslt);

        return false;
    }

    /* Recommended mode of operation: Indoor navigation */
    settings.filter = BME280_FILTER_COEFF_16;
    settings.osr_h = BME280_OVERSAMPLING_1X;
    settings.osr_p = BME280_OVERSAMPLING_16X;
    settings.osr_t = BME280_OVERSAMPLING_4X;

    /* Set the sensor settings */
    mRslt = bme280_set_sensor_settings(BME280_SEL_ALL_SETTINGS, &settings, &mDev);
    if (mRslt != BME280_OK)
    {
        fprintf(stderr, "Failed to set sensor settings (code %+d).", mRslt);

        return false;
    }

    /*Calculate the minimum delay required between consecutive measurement based upon the sensor enabled
     *  and the oversampling configuration. */
    bme280_cal_meas_delay(&mReq_delay, &settings);

  }
  return true;
}


void BME280_sensor::executeSensorValueRead()
{
  cout << ("Temperature, Pressure, Humidity\n");
    /* Set the sensor to forced mode */
  mRslt = bme280_set_sensor_mode(BME280_POWERMODE_FORCED, &mDev);
  if (mRslt != BME280_OK)
  {
      fprintf(stderr, "Failed to set sensor mode (code %+d).", mRslt);
      return;
  }

#ifdef SIMULATE_HW
  mComp_data.humidity = 45.6789;
  mComp_data.pressure = 987.6543;
  mComp_data.temperature = 23.456;
#else
  /* Wait for the measurement to complete and print data */
  mDev.delay_us(mReq_delay, mDev.intf_ptr);
  mRslt = bme280_get_sensor_data(BME280_ALL, &mComp_data, &mDev);
  if (mRslt != BME280_OK)
  {
      fprintf(stderr, "Failed to get sensor data (code %+d).", mRslt);
      return;
  }
#endif

#if 0
  #ifdef BME280_DOUBLE_ENABLE
    temp = comp_data->temperature;
    press = 0.01 * comp_data->pressure;
    hum = comp_data->humidity;
#else
#ifdef BME280_64BIT_ENABLE
    temp = 0.01f * comp_data->temperature;
    press = 0.0001f * comp_data->pressure;
    hum = 1.0f / 1024.0f * comp_data->humidity;
#else
    temp = 0.01f * comp_data->temperature;
    press = 0.01f * comp_data->pressure;
    hum = 1.0f / 1024.0f * comp_data->humidity;
#endif
#endif
#endif
  print_sensor_data(&mComp_data);
}

bool BME280_sensor::setWorkingMode(sensor_use_type wanted_use)
{
  mSensor_use = wanted_use;
  if (wanted_use != eBME_not_set)
  {
    if (!initAttributes())
    {
      mSensor_use = eBME_not_set;
    }
  }
  return mSensor_use != eBME_not_set;
}

int BME280_sensor::getLastBmeErrorCode()
{
  return (int)mRslt;
}


double BME280_sensor::getTemperature()
{
  #ifdef BME280_DOUBLE_ENABLE
    return mComp_data.temperature;
#else
#ifdef BME280_64BIT_ENABLE
    temp = 0.01f * comp_data->temperature;
    press = 0.0001f * comp_data->pressure;
    hum = 1.0f / 1024.0f * comp_data->humidity;
#else
    temp = 0.01f * comp_data->temperature;
    press = 0.01f * comp_data->pressure;
    hum = 1.0f / 1024.0f * comp_data->humidity;
#endif
#endif
}

double BME280_sensor::getPressure()
{
    return 0.01 * mComp_data.pressure;
}

double BME280_sensor::getHumidity()
{
  cout << "Humidity value is " << mComp_data.humidity << " mode " << mSensor_use << endl;
  switch (mSensor_use )
  {
    default:
    case eBME_not_set:
      return 0;
    case eBME_tph:
      return mComp_data.humidity;
    case eBMP_tp:
      // not available on this chip
      return 0;
  }
  return 0;
}

