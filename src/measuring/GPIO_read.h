
#ifndef GPIO_READ_H
#define GPIO_READ_H

#if SIMULATE_HW == false

#include <pi-gpio.h>

#else

#endif

#include "GPIO_control.h"
#include "Sensor.h"

#include <string>

// HW example is pi-gpio and examples/getGPIO.c

/**
  * class GPIO_read
  * 
  */

class GPIO_read : public GPIO_control, virtual public Sensor
{
public:
  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  GPIO_read();
  GPIO_read(int pollingInterval, int pinIndex);

  /**
   * Empty Destructor
   */
  virtual ~GPIO_read();

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  

  void executeSensorValueRead() override;

  /**
   * @return int
   * @param  pinIndex
   */
  int read(int pinIndex)
  {
    return 0;
  }

protected:
  // Static Protected attributes
  //  
  int mPinIndex;  // Raspberry Pi 4B values in range 0..27
  std::string mPinName;
  int mPinValue;
  int mLastReadFunction;
  int mPullUpDn;

  // Protected attributes
  //  


  // Protected attribute accessor methods
  //  


  // Protected attribute accessor methods
  //

private:
  // Static Private attributes
  //  

  // Private attributes
  //  


  // Private attribute accessor methods
  //  


  // Private attribute accessor methods
  //

};

#endif // GPIO_READ_H
