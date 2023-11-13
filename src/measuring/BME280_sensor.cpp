#include "BME280_sensor.h"
#include <iostream>

using namespace std;

// Constructors/Destructors
//  

BME280_sensor::BME280_sensor(int pollingInterval, int bus, int address) : Sensor(pollingInterval), I2C_sensor(pollingInterval, bus, address)
{
  this->mTag = "BME280_sensor";
  initAttributes();
}

BME280_sensor::~BME280_sensor()
{
}

//  
// Methods
//  


// Accessor methods
//  


// Other methods
//  

void BME280_sensor::initAttributes()
{
}

void BME280_sensor::setWorkingMode()
{
}

double BME280_sensor::getTemperature()
{
  if (simulate_hw)
  {
    cout << "Simulation coming" << endl;
  } else {
  }
  return 0;
}

double BME280_sensor::getPressure()
{
  return 0;
}

double BME280_sensor::getHumidity()
{
  return 0;
}


