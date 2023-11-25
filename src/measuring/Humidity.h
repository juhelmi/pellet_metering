
#ifndef HUMIDITY_H
#define HUMIDITY_H

#include "I2C_sensor.h"
#include "BME280_sensor.h"

// There will be imlementation for BME280 but BMP280 should raise some error. Exception is not nice but some assert is OK.
class Humidity : virtual public I2C_Logical_Sensor
{
public:
  Humidity(I2C_sensor* hwSensor);
  Humidity(I2C_sensor* hwSensor, int pollingInterval, int bus, int address);
  /**
   * Empty Destructor
   */
  virtual ~Humidity();

  // Static Public attributes
  //

  // Public attributes
  //


  // Public attribute accessor methods
  //
  double getValue();

  // Public attribute accessor methods
  //

  std::string getFullId() override;
  void executeSensorValueRead() override;
  std::shared_ptr<Measurement> getMeasurement() override;

  /**
   * @return double
   */
  double getHumidity()
  {
    return 0;
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

#endif  // HUMIDITY_H
