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
  if (name.empty())
  {
    return mTag;
  }
  return name;
}

void Sensor::setName(std::string value)
{
  name = value;
}
