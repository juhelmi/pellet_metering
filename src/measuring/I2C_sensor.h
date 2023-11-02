
#ifndef I2C_SENSOR_H
#define I2C_SENSOR_H

#include "Sensor.h"

#include <string>


/**
  * class I2C_sensor
  * 
  */

/******************************* Abstract Class ****************************
I2C_sensor does not have any pure virtual methods, but its author
  defined it as an abstract class, so you should not use it directly.
  Inherit from it instead and create only objects from the derived classes
*****************************************************************************/

class I2C_sensor : virtual public Sensor
{
public:
  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  I2C_sensor();

  /**
   * Empty Destructor
   */
  virtual ~I2C_sensor();

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  



  /**
   * I2C luku
   */
  void read()
  {
  }


  /**
   * I2C kirjoitus
   */
  void write()
  {
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

  int address;
  int dev_nr;

  // Private attribute accessor methods
  //  


  // Private attribute accessor methods
  //  


  /**
   * Set the value of address
   * @param value the new value of address
   */
  void setAddress(int value);

  /**
   * Get the value of address
   * @return the value of address
   */
  int getAddress();

  /**
   * Set the value of dev_nr
   * @param value the new value of dev_nr
   */
  void setDev_nr(int value);

  /**
   * Get the value of dev_nr
   * @return the value of dev_nr
   */
  int getDev_nr();

  void initAttributes();

};

#endif // I2C_SENSOR_H
