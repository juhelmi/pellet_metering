
#ifndef BME280_SENSOR_H
#define BME280_SENSOR_H

#include "I2C_sensor.h"

#include <string>


/**
  * class BME280_sensor
  * 
  */

class BME280_sensor : virtual public I2C_sensor
{
public:
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


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  



  /**
   */
  void setWorkingMode();


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

  /**
   * Get the value of mAddress
   * @return the value of mAddress
   */
  int getMAddress()
  {
    return 0;
  }

  void initAttributes();

};

#endif // BME280_SENSOR_H
