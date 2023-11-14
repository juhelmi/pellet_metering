#include "GPIO_read.h"
#include "config.hpp"


#include <iostream>

using namespace std;

// Constructors/Destructors
//  

struct GPIOvalue {
	int value;
	int function;
	int pull;
};

struct GPIOvalue getGPIO(int g)
{
	GPIOvalue gp;
	gp.value = input_gpio(g);
	gp.function = gpio_function(g);
	gp.pull = (gp.function==0) ? get_pullupdn(g) : 0;	// only input
	return gp;
}


GPIO_read::GPIO_read() : Sensor(998)
{
    mPinIndex = 0;
}

GPIO_read::GPIO_read(int pollingInterval, int pinIndex) : Sensor(pollingInterval), mPinIndex(pinIndex)
{
    const int pullDirection = PUD_UP;
    mTag = "GPIO_read";
    cout << "GPIO set pin " << mPinIndex << " as INPUT" << endl;
    setup_gpio(mPinIndex, INPUT, pullDirection);
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
    if (simulate_hw)
    {
        // Read from file?
        cout << "Simulation coming" << endl;
    } else {
        cout << "Raspberry Pi HW read coming" << endl;
#if 1
        mPinValue = input_gpio(mPinIndex);
        mLastReadFunction = gpio_function(mPinIndex);
        mPullUpDn = (mLastReadFunction == 0) ? get_pullupdn(mPinIndex) : 0;
#else
        struct GPIOvalue gp;
        gp = getGPIO(mPinIndex);
        mPinValue = gp.value;
        mLastReadFunction = gp.function;
        mPullUpDn = gp.pull;
#endif
        cout << "GPIO " << mPinIndex << " Value " << mPinValue << " Function " << mLastReadFunction << " Pull " << mPullUpDn << endl;

    }
}


// Accessor methods
//  


// Other methods
//  


