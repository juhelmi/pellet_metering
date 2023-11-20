#include "Air_pressure.h"
#include <iostream>

using namespace std;

// Constructors/Destructors
//  

Air_pressure::Air_pressure(I2C_sensor* hwSensor, int pollingInterval, int bus, int address) :
Sensor(pollingInterval),
I2C_Logical_Sensor(hwSensor, pollingInterval, bus, address)
{
  initAttributes();
  this->mTag = "Air_pressure";
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

void Air_pressure::executeSensorValueRead()
{
  cout << "Air pressure read for " << mTag << " Bus " << mBus << " Location " << mLocation << " Value " << getValue() << endl;
}

