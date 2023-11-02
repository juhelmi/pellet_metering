
#ifndef GPIO_READ_H
#define GPIO_READ_H

#include "GPIO_control.h"
#include "Sensor.h"

#include <string>


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



  /**
   * @return bool
   * @param  port_index
   */
  bool read(int port_index)
  {
    return false;
  }

protected:
  // Static Protected attributes
  //  

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
