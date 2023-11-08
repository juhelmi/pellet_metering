
#include "Scheduler.h"

/**
 * Task is to add all sensors to list of used sensors.
 * Sensors have polling frequency. Scheduler makes value updates according to timed base.
 *
 * Decision making uses current values. It can calculate trends from history and create derived values also to be used.
 *
 * Scheduler puts all sensors to be updated after update interval. When time is elapsed same interval is
 * added again.
 *
 * I2C busses have separate threads as there are different HW busses for all of them. Scheduler adds update for used bus.
 *
 * GPIO reading is prompt and are checked from main thread. PWM controlling do not belong to scheduler but works also from main thread.
 *
 */

#include <iostream>

#include "Sensor.h"
#include <map>

// This line **must** come **before** including <time.h> in order to
// bring in the POSIX functions such as `clock_gettime() from <time.h>`!
//#define _POSIX_C_SOURCE 199309L

#include <errno.h>  // `errno`
#include <stdint.h> // `UINT64_MAX`
#include <stdio.h>  // `printf()`
#include <string.h> // `strerror(errno)`
#include <time.h>   // `clock_gettime()` and `timespec_get()`

using namespace std;

#define SEC_TO_NS(sec) ((sec)*1000000000)

tMeasurementTime getCurrnetTime()
{
    // https://stackoverflow.com/questions/5833094/get-a-timestamp-in-c-in-microseconds
    /// Convert seconds to nanoseconds

    uint64_t nanoseconds;
    struct timespec ts;
    int return_code = clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    if (return_code == -1)
    {
        printf("Failed to obtain timestamp. errno = %i: %s\n", errno,
            strerror(errno));
        nanoseconds = UINT64_MAX; // use this to indicate error
    }
    else
    {
        // `ts` now contains your timestamp in seconds and nanoseconds! To
        // convert the whole struct to nanoseconds, do this:
        nanoseconds = SEC_TO_NS((uint64_t)ts.tv_sec) + (uint64_t)ts.tv_nsec;
    }
    return nanoseconds;
}

Scheduler::Scheduler()
{
}

Scheduler::~Scheduler() noexcept
{
}



void Scheduler::addSensor(Sensor *newSensor)
{
    // to all sensors
    mSensors.push_back(newSensor);
    // also to scheduled list
    tMeasurementTime interval = getCurrnetTime() + newSensor->getPollingInterval();
    mNextPolls.insert(std::pair<tMeasurementTime, Sensor*>(interval, newSensor));
}

int Scheduler::pollTimedSensors()
{
    // Get Current time
    tMeasurementTime now = getCurrnetTime();
    int elapsedSensors = 0;

    // prints current map
    cout << "Positive times are timed to be run.\n";
    for (std::multimap<tMeasurementTime,Sensor*>::iterator it= mNextPolls.begin();
         it != mNextPolls.end(); ++it)
    {
        cout << "Sensor " << it->second->getName() << " " << now - it->first << endl;
    }
    cout << "Polling\n";
    cout << "Now " << now << " First diff " << now -  mNextPolls.begin()->first << endl;
    if (now < mNextPolls.begin()->first)
    {
        return 0;
    }

    std::multimap<tMeasurementTime,Sensor*>::iterator it= mNextPolls.begin();
    while (it->first > now)
    {
        std::cout << "Sensor " << it->second->getName() <<" " << now - it->first << "\t" << endl;
        //std::cout << it->first << "\t" << it->second << std::endl ;
        //
        tMeasurementTime nextPoll = it->second->getPollingInterval() + it->first;
        if (nextPoll < now)
        {
            nextPoll = now + it->second->getPollingInterval();
        }
        cout << "Next for " << it->second->getName() <<" is " << nextPoll << endl;
        mNextPolls.insert(std::pair<tMeasurementTime, Sensor*>(nextPoll, it->second));
        mNextPolls.erase(it);
        it = mNextPolls.begin();
        elapsedSensors++;
    }
    return elapsedSensors;
}

