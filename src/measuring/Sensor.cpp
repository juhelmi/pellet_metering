#include "Sensor.h"

// Constructors/Destructors
//  

Sensor::Sensor()
{
  initAttributes();
}

Sensor::~Sensor()
{
}

//  
// Methods
//  


// Accessor methods
//  


// Other methods
//  

void Sensor::initAttributes()
{
}

tMeasurementTime Sensor::getPollingInterval()
{
  return 3;
}
