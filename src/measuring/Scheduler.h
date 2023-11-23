#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <string>
#include <map>
#include <list>

#include "Measurement.h"
#include "Sensor.h"

tMeasurementTime getCurrentTime();
bool compareTimeInMsRange(tMeasurementTime compareTime, tMeasurementTime range);

class Scheduler {
private:
protected:
    std::list<Sensor*> mSensors;
    std::multimap<tMeasurementTime, Sensor*> mNextPolls;
    /**
     * Current measurements are in List according to sample interval.
     * List contains only last meaningful length of measurements.
     * If history is needed then there could be virtual sensors where value is calculated according to other sensors.
     */
    std::list<std::list<Measurement>> mMeasurements;

public:
  // Constructors/Destructors
  //


  /**
   * Empty Constructor
   */
  Scheduler();

    /**
   * Empty Destructor
   */
  virtual ~Scheduler();

  // Public attribute accessor methods
  //

  void addSensor(Sensor *newSensor);

  int pollTimedSensors();

  int collectCurrentValues();
};


#endif // SCHEDULER_H
