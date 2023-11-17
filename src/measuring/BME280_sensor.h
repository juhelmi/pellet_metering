
#ifndef BME280_SENSOR_H
#define BME280_SENSOR_H

#include "I2C_sensor.h"
extern "C" {
#include "bme280.h"
}

#include <string>

struct identifier
{
    /* Variable to hold device address */
    uint8_t dev_addr;

    /* Variable that contains file descriptor */
    int8_t fd;
};


/**
  * class BME280_sensor
  * Uses BMP280 also with BME280 communication protocol. Requires modifications to bme280 driver.
  */

class BME280_sensor : virtual public I2C_sensor
{
public:
  enum sensor_use_type{eBME_not_set = 0, eBME_tph, eBMP_tp, eBME_tp};
  enum chip_ids_supported{eBME280_CHIP_ID=BME280_CHIP_ID, eBMP280_CHIP_ID=BMP280_CHIP_ID};

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  BME280_sensor(int pollingInterval, int bus, int address);

  /**
   * Empty Destructor
   */
  virtual ~BME280_sensor();

  // Static Public attributes
  //  


  // Public attributes
  //  
  bool initAttributes();  // This might fail when no permission to open driver or other reason.
  void executeSensorValueRead() override;

  // Public attribute accessor methods
  //  


  // Public attribute accessor methodssensor_use_type wanted_use
  //  



  /**
   */
  bool setWorkingMode(sensor_use_type wanted_use);
  int getLastBmeErrorCode();


  /**
   * @return double
   */
  double getTemperature();


  /**
   * @return double
   */
  double getPressure();


  /**
   * @return double
   */
  double getHumidity();


protected:
  // Static Protected attributes
  //  
  static bool mHwDriverInitialized;
  sensor_use_type mSensor_use;
  struct bme280_dev mDev;
  struct identifier mId;
  int8_t mRslt;   // last result in BME280 operation
  uint32_t mReq_delay;
  struct bme280_data mComp_data;

  // Protected attributes
  //  


  // Protected attribute accessor methods
  //  


  // Protected attribute accessor methods
  //

private:
  // Static Private attributes
  //  

  // Private attributes
  //  


  // Private attribute accessor methods
  //  


  // Private attribute accessor methods
  //  


  /**
   * Set the value of mDev
   * @param value the new value of mDev
   */
  void setMDev(int value)
  {
  }

  /**
   * Get the value of mDev
   * @return the value of mDev
   */
  int getMDev()
  {
    return 0;
  }

  /**
   * Set the value of mAddress
   * @param value the new value of mAddress
   */
  void setMAddress(int value)
  {
  }
virtual
  /**
   * Get the value of mAddress
   * @return the value of mAddress
   */
  int getMAddress()
  {
    return 0;
  }

};

#endif // BME280_SENSOR_H
