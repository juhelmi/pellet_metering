
#ifndef ADC_SENSOR_H
#define ADC_SENSOR_H

#include "I2C_sensor.h"


/**
  * class ADC_sensor
  * 
  */

class ADC_sensor : virtual public I2C_sensor
{
public:
  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  ADC_sensor(int bus, int address);

  /**
   * Empty Destructor
   */
  virtual ~ADC_sensor();

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  



  /**
   * @return int
   */
  int getValue()
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


  // Private attribute accessor methods
  //  


  // Private attribute accessor methods
  //

};

#endif // ADC_SENSOR_H
