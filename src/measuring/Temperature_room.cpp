#include "Temperature_room.h"

// Constructors/Destructors
//  

Temperature_room::Temperature_room(int bus, int address) : I2C_sensor(bus,address)
{
  initAttributes();
}

Temperature_room::~Temperature_room()
{
}

//  
// Methods
//  


// Accessor methods
//  


// Other methods
//  

void Temperature_room::initAttributes()
{
  minTemp = -10;
  maxTemp = 60;
}

