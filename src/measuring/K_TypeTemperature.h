
#ifndef K_TYPETEMPERATURE_H
#define K_TYPETEMPERATURE_H

#include "ADC_sensor.h"

#include <string>


/**
  * class K_TypeTemperature
  * 
  */

class K_TypeTemperature : public ADC_sensor
{
public:
  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  K_TypeTemperature(int bus, int address);

  /**
   * Empty Destructor
   */
  virtual ~K_TypeTemperature();

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
  double getTemperature()
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

#endif // K_TYPETEMPERATURE_H
