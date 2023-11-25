#include "Air_pressure.h"
#include <iostream>
#include <sstream>

using namespace std;

// Constructors/Destructors
//  

Air_pressure::Air_pressure(I2C_sensor* hwSensor) :
Sensor(-3),
I2C_Logical_Sensor(hwSensor)
{
  initAttributes();
  mTag = "Air_pressure";
}


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

double Air_pressure::getPressure()
{
  if (typeid(*mHWSensor) == typeid(BME280_sensor))
  {
    BME280_sensor* pBME = dynamic_cast<BME280_sensor*>(mHWSensor);
    if (pBME->getLastBmeErrorCode() != 0)
    {
      // cout << "BME Error\n";
      mConfigurationOk = false;
    }
    if (mConfigurationOk)
    {
      return pBME->getPressure();
    }
  } else {
  }
  return 0;
}


std::shared_ptr<Measurement> Air_pressure::getMeasurement()
{
  std::shared_ptr<Measurement> meas = std::make_shared<Measurement>();
  meas->mName = getFullId();
  meas->mMeas.mType = MeasurementType::tDOUDBLE;
  meas->mMeas.dValue = getValue();
  return meas;
}
