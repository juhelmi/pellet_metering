#include "K_TypeTemperature.h"

// Constructors/Destructors
//  

K_TypeTemperature::K_TypeTemperature(int pollingInterval, int bus, int address) :
Sensor(pollingInterval), ADC_sensor(pollingInterval, bus, address)
,I2C_sensor(pollingInterval, bus, address)
{
}

K_TypeTemperature::~K_TypeTemperature()
{
}

//  
// Methods
//  


// Accessor methods
//  


// Other methods
//  


