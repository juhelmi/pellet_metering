#include "GPIO_read.h"

#include <iostream>

using namespace std;

// Constructors/Destructors
//  

GPIO_read::GPIO_read() : Sensor(998)
{
    mPinIndex = 0;
}

GPIO_read::GPIO_read(int pollingInterval, int pinIndex) : Sensor(pollingInterval), mPinIndex(pinIndex)
{
    mTag = "GPIO_read";
}


GPIO_read::~GPIO_read()
{
}

//  
// Methods
//  

void GPIO_read::executeSensorValueRead()
{
    cout << "IO read value for " << mTag << " Location " << mLocation << " Pin " << mPinIndex << " PinName " << mPinName << endl;
}


// Accessor methods
//  


// Other methods
//  


