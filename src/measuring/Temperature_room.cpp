#include "Temperature_room.h"
#include <iostream>

using namespace std;

// Constructors/Destructors
//  

Temperature_room::Temperature_room(I2C_sensor* hwSensor, int  pollingInterval, int bus, int address) :
Sensor(pollingInterval),
I2C_Logical_Sensor(hwSensor, pollingInterval, bus, address)
{
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

void Temperature_room::executeSensorValueRead()
{
  cout << "Room temperature read for " << mTag << " Bus " << mBus << " Location " << mLocation << " Value " << getValue() << endl;
}

double Temperature_room::getTemperature()
{
  if (typeid(*mHWSensor) == typeid(BME280_sensor))
  {
    BME280_sensor* pBME = dynamic_cast<BME280_sensor*>(mHWSensor);
    if (pBME->getLastBmeErrorCode() != 0)
    {
      cout << "Error\n";
      mConfigurationOk = false;
    }
    if (mConfigurationOk)
    {
      return pBME->getTemperature();
    }
  } else {
  }
  return 0;
}

std::shared_ptr<Measurement> Temperature_room::getMeasurement()
{
  auto pMeas = Sensor::getMeasurement();
  pMeas->mMeas.dValue = getTemperature();
  return pMeas;
}
