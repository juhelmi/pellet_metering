
#ifndef I2C_SENSOR_H
#define I2C_SENSOR_H

#include "Sensor.h"

#include <string>
#include <map>
#include <memory>
#include <boost/ref.hpp>
#include <list>

/**
  * class I2C_sensor
  * 
  */

/******************************* Abstract Class ****************************
I2C_sensor does not have any pure virtual methods, but its author
  defined it as an abstract class, so you should not use it directly.
  Inherit from it instead and create only objects from the derived classes
*****************************************************************************/

class I2C_sensor : virtual public Sensor
{
protected:
  int mBus;
  int mAddress;
  std::string   mDevName;
  static const int mMaxBus = 5;

public:
  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  I2C_sensor();
  I2C_sensor(int pollingInterval, int bus, int address);
  I2C_sensor(I2C_sensor &t);
  I2C_sensor& operator=(const I2C_sensor& t);
  // Move
  I2C_sensor(const I2C_sensor& t);
  I2C_sensor& operator=(I2C_sensor&& t);

  /**
   * Empty Destructor
   */
  virtual ~I2C_sensor();

  // Static Public attributes
  //  

  // Public attributes
  //  
  int getBus() { return mBus;}
  int getAddress() {return mAddress; }


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  

  void executeSensorValueRead() override;


  /**
   * I2C luku
   */
  void read()
  {
  }


  /**
   * I2C kirjoitus
   */
  void write()
  {
  }

protected:
  // Static Protected attributes
  //  
  // Collects list of initialized devices
  // One I2C devices shares multiple functions but there will be objects for handling only one function from real device.
  static int mAllSensorCount;
  // Typically Sensor objects are not created with new. No shared_ptr is needed and no delete is need to call directly.
  //static std::map<std::pair<int,int>, std::shared_ptr<I2C_sensor> > mMapOfActiveSensors;
  static std::map<std::pair<int,int>, I2C_sensor*> mMapOfActiveSensors;
  // Sensor knows it's own childs for pair<bus, address>
  std::list<Sensor*> mSensorsAtSameAddress;

  // Protected attributes
  //  

  bool isSensorUsed(int port, int address);
  I2C_sensor* getDevice(int port, int address);
  bool addThisSensor(int port, int address);
  void removeThisSensor(int port, int address);

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


  /**
   * Set the value of address
   * @param value the new value of address
   */
  void setAddress(int value);

  /**
   * Set the value of dev_nr
   * @param value the new value of dev_nr
   */
  void setDev_nr(int value);

  /**
   * Get the value of dev_nr
   * @return the value of dev_nr
   */
  int getDev_nr();

  void initAttributes();

};

class I2C_Logical_Sensor : virtual public Sensor
{
public:
  I2C_Logical_Sensor(I2C_sensor* hwSensor);
  I2C_Logical_Sensor(I2C_sensor* hwSensor, int pollingInterval, int bus, int address);
  virtual ~I2C_Logical_Sensor();

  bool isConfigurationOK();

  // Value reading operation is overriden in next level where actual sensor type is known.
  // void executeSensorValueRead() override;

protected:
  I2C_sensor* mHWSensor;    // Actual sensor that has multiple parameters to read.
  bool mConfigurationOk;
  int mBus;
  int mAddress;

  virtual void raiseConfigurationError();
};

#endif // I2C_SENSOR_H
