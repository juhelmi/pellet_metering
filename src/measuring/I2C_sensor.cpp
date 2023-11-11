#include "I2C_sensor.h"

#include <boost/format.hpp>
#include <iostream>

#include <stdexcept>
using namespace std;

// remove
#include <cstdio>
#include <string>
#include <cassert>
template< typename... Args >
std::string string_sprintf( const char* format, Args... args ) {
  int length = std::snprintf( nullptr, 0, format, args... );
  assert( length >= 0 );

  char* buf = new char[length + 1];
  std::snprintf( buf, length + 1, format, args... );

  std::string str( buf );
  delete[] buf;
  return str;
}
//


// Constructors/Destructors
//  

int I2C_sensor::mAllSensorCount = 0;
//std::map<std::pair<int,int>, std::shared_ptr<I2C_sensor>> I2C_sensor::mMapOfActiveSensors;
std::map<std::pair<int,int>, I2C_sensor*> I2C_sensor::mMapOfActiveSensors;

#if 1
I2C_sensor::I2C_sensor() : Sensor(999)
{
  cout << "I2C Default " << __FUNCTION__ << __LINE__ << endl;
}
#endif

I2C_sensor::I2C_sensor(int pollingInterval, int bus, int address) : Sensor(pollingInterval), mBus(bus), mAddress(address)
{
  addThisSensor(bus, address);
  // mDevName = boost::format("/dev/i2c-%1%" % bus);
  //cout << boost::format("/dev/i2c-%1%" % bus);
  cout << string_sprintf("/dev/i2c-%d \n", bus);
  initAttributes();
}

#if 1
I2C_sensor::I2C_sensor(I2C_sensor& t)
{
  mBus = t.mBus;
  mAddress = t.mAddress;
  mDevName = t.mDevName;
  cout << "Copy contructor " << __FUNCTION__ << __LINE__ << endl;
}
#endif

I2C_sensor & I2C_sensor::operator=(const I2C_sensor& t)
{
  mBus = t.mBus;
  mAddress = t.mAddress;
  mDevName = t.mDevName;
  cout << "Assignment " << __FUNCTION__ << __LINE__ << endl;
  return *this;
}


I2C_sensor::I2C_sensor(const I2C_sensor& t)
{
  mBus = t.mBus;
  mAddress = t.mAddress;
  mDevName = t.mDevName;
  cout << "Nearly move " << __FUNCTION__ << __LINE__ << endl;
}

I2C_sensor & I2C_sensor::operator=(I2C_sensor && t)
{
  mBus = t.mBus;
  mAddress = t.mAddress;
  mDevName = t.mDevName;
  cout << "Nearly move = " << __FUNCTION__ << __LINE__ << endl;
  return *this;
}


I2C_sensor::~I2C_sensor()
{
}

//  
// Methods
//  


// Accessor methods
//  std::shared_ptr<


// Other methods
//  
void I2C_sensor::initAttributes()
{
}

void I2C_sensor::setAddress(int value)
  {
    mAddress = value;
  }

int I2C_sensor::getAddress()
  {
    return mAddress;
  }

  void I2C_sensor::setDev_nr(int value)
  {
    mBus = value;
  }

  /**
   * Get the value of dev_nr
   * @return the value of dev_nr
   */
  int I2C_sensor::getDev_nr()
  {
    return mBus;
  }

  bool I2C_sensor::isSensorUsed(int port, int address)
  {
    std::pair<int, int> key(port, address);
    return mMapOfActiveSensors.count(key) > 0;
  }

  I2C_sensor* I2C_sensor::getDevice(int port, int address)
  {
    return 0;
  }

  bool I2C_sensor::addThisSensor(int port, int address)
  {
    std::pair<int, int> key(port, address);
    mAllSensorCount++;
    if (mMapOfActiveSensors.count(key) <= 0)
    {
      //mMapOfActiveSensors[key] = std::make_shared<I2C_sensor>(this);
      mMapOfActiveSensors[key] = this;
      return true;
    }
    return false;
  }

void I2C_sensor::removeThisSensor(int port, int address)
{
  mAllSensorCount--;
}
