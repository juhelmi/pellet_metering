#include "Air_pressure.h"

// Constructors/Destructors
//  

Air_pressure::Air_pressure(int bus, int address) : I2C_sensor(bus,address)
{
  initAttributes();
}

Air_pressure::~Air_pressure()
{
}

//  
// Methods
//  


// Accessor methods
//  


// Other methods
//  

void Air_pressure::initAttributes()
{
  repeatedHwRead = 0;
}

