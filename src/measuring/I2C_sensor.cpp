#include "I2C_sensor.h"

// Constructors/Destructors
//  

I2C_sensor::I2C_sensor()
{
  initAttributes();
}

I2C_sensor::~I2C_sensor()
{
}

//  
// Methods
//  


// Accessor methods
//  


// Other methods
//  

void I2C_sensor::initAttributes()
{
  address = 0;
}

void I2C_sensor::setAddress(int value)
  {
    address = value;
  }

int I2C_sensor::getAddress()
  {
    return address;
  }

  void I2C_sensor::setDev_nr(int value)
  {
    dev_nr = value;
  }

  /**
   * Get the value of dev_nr
   * @return the value of dev_nr
   */
  int I2C_sensor::getDev_nr()
  {
    return dev_nr;
  }
