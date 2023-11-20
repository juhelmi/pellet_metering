#include "Humidity.h"

#include <iostream>
#include <typeinfo>

using namespace std;

// Constructors/Destructors
//

Humidity::Humidity(I2C_sensor* hwSensor, int pollingInterval, int bus, int address) :
Sensor(pollingInterval),
I2C_Logical_Sensor(hwSensor, pollingInterval, bus, address)
{
  this->mTag = "Humidity";
}

Humidity::~Humidity()
{
}

void Humidity::executeSensorValueRead()
{
  cout << "Humidity read for " << mTag << " Bus " << mBus << " Location " << mLocation << " Value " << getValue() << endl;
}

double Humidity::getValue()
{
  if (typeid(*mHWSensor) == typeid(BME280_sensor))
  {
    BME280_sensor* pBME = dynamic_cast<BME280_sensor*>(mHWSensor);
    if (pBME->getLastBmeErrorCode() != 0)
    {
      mConfigurationOk = false;
    }
    if (mConfigurationOk)
    {
        return pBME->getHumidity();
    }
  }
  return 0;
}
