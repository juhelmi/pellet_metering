
#ifndef SENSOR_H
#define SENSOR_H

#include <string>
#include <memory>

#include "Measurement.h"
#include "config.hpp"

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
public:
  enum eValueType {NO_VALUE, INT_VALUE, DOUBLE_VALUE, BOOLEAN_VALUE, STRING_VALUE};   // bool and string are optional

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  Sensor();
  Sensor(int pollingInterval);

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
  virtual void executeSensorValueRead();  // will be overriden

  tMeasurementTime getPollingInterval();
  void setPollingInterval(tMeasurementTime value);

  // Public attribute accessor methods
  //

  /**
   * Get the value of name
   * @return the value of name
   */
  std::string getName();
  void setLocation(std::string value);
  std::string getLocation();
  eValueType getValueType();
  virtual int getIntValue();
  virtual double getDoubleValue();
  virtual std::shared_ptr<Measurement> getMeasurement();


protected:
  // Static Protected attributes
  //  
  eValueType mValueType;
  std::string mTag;           // at start this contains object type name
  std::string mLocation;  // For user documentation

  // Protected attributes
  //  
  int mPollingInterval;

    /**
   * Set the value of name
   * @param value the new value of name
   */
  void setName(std::string value);


  // Protected attribute accessor methods
  //  


  // Protected attribute accessor methods
  //

private:
  // Static Private attributes
  //  

  // Private attributes
  //  
  Measurement mMeasurement;

  // I2C device number
  int dev;

  // Private attribute accessor methods
  //  


  // Private attribute accessor methods
  //  



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
