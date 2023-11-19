
#ifndef TEMPERATURE_ROOM_H
#define TEMPERATURE_ROOM_H

#include "I2C_sensor.h"
#include "I2C_sensor.h"
#include "BME280_sensor.h"

#include <string>


/**
  * class Temperature_room
  * 
  */

class Temperature_room : virtual public I2C_Logical_Sensor
{
protected:
  //BME280_sensor *mRealSensor;

public:
  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  Temperature_room(I2C_sensor* hwSensor, int pollingInterval, int bus, int address);

  /**
   * Empty Destructor
   */
  virtual ~Temperature_room();

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  

  void executeSensorValueRead() override;

  /**
   * @return double
   */
  double getTemperature()
  {
    return 0;
  }


  /**
   * @return string
   */
  std::string getErrors()
  {
    return "";
  }

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

  float minTemp;
  float maxTemp;

  // Private attribute accessor methods
  //  


  // Private attribute accessor methods
  //  


  /**
   * Set the value of minTemp
   * @param value the new value of minTemp
   */
  void setMinTemp(float value)
  {
    minTemp = value;
  }

  /**
   * Get the value of minTemp
   * @return the value of minTemp
   */
  float getMinTemp()
  {
    return minTemp;
  }

  /**
   * Set the value of maxTemp
   * @param value the new value of maxTemp
   */
  void setMaxTemp(float value)
  {
    maxTemp = value;
  }

  /**
   * Get the value of maxTemp
   * @return the value of maxTemp
   */
  float getMaxTemp()
  {
    return maxTemp;
  }

  void initAttributes();

};

#endif // TEMPERATURE_ROOM_H
