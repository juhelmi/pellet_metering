#include "Sensor.h"

#include <iostream>
using namespace std;

// Constructors/Destructors
//  

Sensor::Sensor() : mTag(""), mPollingInterval(1000)
{
  cout << "Default not wanted\n";
}

Sensor::Sensor(int pollingInterval) : mTag(""), mPollingInterval(pollingInterval)
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


