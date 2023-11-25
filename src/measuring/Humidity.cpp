#include "Humidity.h"

#include <iostream>
#include <sstream>
#include <typeinfo>

using namespace std;

// Constructors/Destructors
//

Humidity::Humidity(I2C_sensor* hwSensor) :
Sensor(-2),
I2C_Logical_Sensor(hwSensor)
{
  // init attributes
  mTag = "Humidity";
  mPollingInterval = hwSensor->getPollingInterval();
}


Humidity::Humidity(I2C_sensor* hwSensor, int pollingInterval, int bus, int address) :
Sensor(pollingInterval),
I2C_Logical_Sensor(hwSensor, pollingInterval, bus, address)
{
  this->mTag = "Humidity";
}

Humidity::~Humidity()
{
}

std::string Humidity::getFullId()
{
  stringstream ss;
  ss << mTag <<" "<< mBus << " " << mAddress << " unit: %";;
  return ss.str();
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
  } else {
    cout << __FILE__ << " " << __LINE__ << endl;
  }
  return 0;
}

std::shared_ptr<Measurement> Humidity::getMeasurement()
{
  std::shared_ptr<Measurement> meas = std::make_shared<Measurement>();
  meas->mName = getFullId();
  meas->mMeas.mType = MeasurementType::tDOUDBLE;
  meas->mMeas.dValue = getValue();
  return meas;
}
