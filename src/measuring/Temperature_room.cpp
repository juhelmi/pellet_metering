#include "Temperature_room.h"

// Constructors/Destructors
//  

Temperature_room::Temperature_room(int pollingInterval, int bus, int address) : Sensor(pollingInterval), I2C_sensor(pollingInterval, bus, address)
{
  mRealSensor = 0;
  initAttributes();
  mTag = "Temperature_room";
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

