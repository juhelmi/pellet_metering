
#ifndef GPIO_CONTROL_H
#define GPIO_CONTROL_H

#include <string>


/**
  * class GPIO_control
  * 
  */

class GPIO_control
{
public:
  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  GPIO_control();

  /**
   * Empty Destructor
   */
  virtual ~GPIO_control();

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
   */
  bool read()
  {
    return false;
  }


  /**
   */
  void write()
  {
  }


  /**
   * @param  port_index
   */
  void soft_pwm(int port_index)
  {
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

  std::string use_type;

  // Private attribute accessor methods
  //  


  // Private attribute accessor methods
  //  


  /**
   * Set the value of use_type
   * @param value the new value of use_type
   */
  void setUse_type(std::string value)
  {
    use_type = value;
  }

  /**
   * Get the value of use_type
   * @return the value of use_type
   */
  std::string getUse_type()
  {
    return use_type;
  }

  void initAttributes();

};

#endif // GPIO_CONTROL_H
