#include "Sensor.h"

#include <iostream>
using namespace std;

// Constructors/Destructors
//  

Sensor::Sensor() : mTag(""), mPollingInterval(1000)
{
  cout << "Default not wanted\n";
}

Sensor::Sensor(int pollingInterval) : mValueType(NO_VALUE), mTag(""), mPollingInterval(pollingInterval)
{
  //mTag = "";
  initAttributes();
  if (mPollingInterval == 999)
  {
    cout << "Check this\n";
  }
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

void Sensor::setPollingInterval(tMeasurementTime value)
{
  mPollingInterval = value;
}


tMeasurementTime Sensor::getPollingInterval()
{
  if (mPollingInterval != 0)
  {
    return mPollingInterval;
  }
  return 10000;
}

std::string Sensor::getName()
{
  return mTag;
}

void Sensor::setName(std::string value)
{
  mTag = value;
}

std::string Sensor::getFullId()
{
  return mTag + " Generic";
}


void Sensor::setLocation(std::string value)
{
  mLocation = value;
}

std::string Sensor::getLocation()
{
  return mLocation;
}

void Sensor::executeSensorValueRead()
{
  cout << "Reads value for " << mTag << " Location " << mLocation << endl;
}

Sensor::eValueType Sensor::getValueType()
{
  return mValueType;
}


int Sensor::getIntValue()
{
  return 0;
}

double Sensor::getDoubleValue()
{
  return 0;
}

std::shared_ptr<Measurement> Sensor::getMeasurement()
{
 std::shared_ptr<Measurement> meas = std::make_shared<Measurement>();
 // Identity for measurement
 meas->mName = getFullId();
 // Value for measurement
 meas->mMeas.mType = MeasurementType::tNONE;
 meas->mMeas.dValue = getDoubleValue();
  return meas;
}


