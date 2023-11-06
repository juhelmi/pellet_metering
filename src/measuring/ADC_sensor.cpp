#include "ADC_sensor.h"

// Constructors/Destructors
//  

ADC_sensor::ADC_sensor(int pollingInterval, int bus, int address) : Sensor(pollingInterval), I2C_sensor(pollingInterval, bus, address)
{
    this->mTag = "ADC_sensor";
}

ADC_sensor::~ADC_sensor()
{
}

//  
// Methods
//  


// Accessor methods
//  


// Other methods
//  


