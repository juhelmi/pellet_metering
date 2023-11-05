
#ifndef AIR_PRESSURE_H
#define AIR_PRESSURE_H

#include "I2C_sensor.h"


/**
  * class Air_pressure
  * 
  */

class Air_pressure : virtual public I2C_sensor
{
public:
  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  Air_pressure(int bus, int address);

  /**
   * Empty Destructor
   */
  virtual ~Air_pressure();

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  



  /**
   * @return double
   */
  double getPressure()
  {
    return 0;
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

  int repeatedHwRead;

  // Private attribute accessor methods
  //  


  // Private attribute accessor methods
  //  


  /**
   * Set the value of repeatedHwRead
   * @param value the new value of repeatedHwRead
   */
  void setRepeatedHwRead(int value)
  {
    repeatedHwRead = value;
  }

  /**
   * Get the value of repeatedHwRead
   * @return the value of repeatedHwRead
   */
  int getRepeatedHwRead()
  {
    return repeatedHwRead;
  }

  void initAttributes();

};

#endif // AIR_PRESSURE_H
