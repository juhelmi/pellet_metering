#include "Air_pressure.h"
#include <iostream>
#include <sstream>

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

std::string Air_pressure::getFullId()
{
  stringstream ss;
  // Get type name and address
  ss << mTag << " " << mBus << " " << mAddress << " unit: hPa";
  return ss.str();
}


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

