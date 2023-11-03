
#ifndef SENSOR_H
#define SENSOR_H

#include <string>

#include "Measurement.h"

/**
  * class Sensor
  * 
  */

/******************************* Abstract Class ****************************
Sensor does not have any pure virtual methods, but its author
  defined it as an abstract class, so you should not use it directly.
  Inherit from it instead and create only objects from the derived classes
*****************************************************************************/

class Sensor
{
private:
  Measurement mMeasurement;

public:
  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  Sensor();

  /**
   * Empty Destructor
   */
  virtual ~Sensor();

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  

  tMeasurementTime getPollingInterval();

  // Public attribute accessor methods
  //

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

  std::string name;
  // I2C device number
  int dev;

  // Private attribute accessor methods
  //  


  // Private attribute accessor methods
  //  


  /**
   * Set the value of name
   * @param value the new value of name
   */
  void setName(std::string value)
  {
    name = value;
  }

  /**
   * Get the value of name
   * @return the value of name
   */
  std::string getName()
  {
    return name;
  }

  /**
   * Set the value of dev
   * I2C device number
   * @param value the new value of dev
   */
  void setDev(int value)
  {
    dev = value;
  }

  /**
   * Get the value of dev
   * I2C device number
   * @return the value of dev
   */
  int getDev()
  {
    return dev;
  }

  void initAttributes();

};

#endif // SENSOR_H
