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
};


#endif // SCHEDULER_H
