
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

tMeasurementTime getCurrentTime()
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

bool compareTimeInMsRange(tMeasurementTime compareTime, tMeasurementTime range)
{
    const tMeasurementTime nsToMsDivisor = 1000000;
    tMeasurementTime now = getCurrentTime() / nsToMsDivisor;
    tMeasurementTime compMs = compareTime / nsToMsDivisor;
    if ((compMs - range <= now) && (compMs + range >= now))
    {
        return true;
    } else {
        return false;
    }
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
    tMeasurementTime interval = getCurrentTime() + newSensor->getPollingInterval();
    mNextPolls.insert(std::pair<tMeasurementTime, Sensor*>(interval, newSensor));
}

int Scheduler::pollTimedSensors()
{
    // Get Current time
    int64_t now = getCurrentTime();
    int elapsedSensors = 0;
    const int64_t nsToUsDivisor = 1000;

    // prints current map
    cout << "Positive times are timed to be run.\n";
    for (std::multimap<tMeasurementTime,Sensor*>::iterator it= mNextPolls.begin();
         it != mNextPolls.end(); ++it)
    {
        cout << "Sensor " << it->second->getName() << " " << (it->first - now)/nsToUsDivisor << endl;
    }
    cout << "Polling\n";
    cout << "Now " << now << " First diff " << mNextPolls.begin()->first - now << endl;
    if (now < mNextPolls.begin()->first)
    {
        cout << "wait more " << mNextPolls.begin()->first - now << endl;
        return 0;
    }

    std::multimap<tMeasurementTime,Sensor*>::iterator it= mNextPolls.begin();
    while (now > it->first)
    {
        Sensor *p_sensor = it->second;
        std::cout << "Elapsed Sensor " << p_sensor->getName() <<" " << (now - it->first)/nsToUsDivisor << "\t" << endl;
        // Start query process
        // Later this will set task on queue. I2C devices will have own thread for separate HW drivers
        p_sensor->executeSensorValueRead();
        //std::cout << it->first << "\t" << it->second << std::endl ;
        //
        tMeasurementTime nextPoll = it->second->getPollingInterval() + it->first;
        if (nextPoll < now)
        {
            nextPoll = now + it->second->getPollingInterval();
        }
        cout << "Next for " << it->second->getName() <<" is " << nextPoll << " Forward time " << nextPoll-now << endl;
        mNextPolls.insert(std::pair<tMeasurementTime, Sensor*>(nextPoll, it->second));
        mNextPolls.erase(it);
        it = mNextPolls.begin();
        elapsedSensors++;
    }
    return elapsedSensors;
}

int Scheduler::collectCurrentValues()
{
    int count = 0;
    // std::pair<char, int> elem : mmapOfPos
    for (std::pair<tMeasurementTime,Sensor*> elem : mNextPolls)
    {
        // fill measurement struct from sensor
        cout << "CV Sensor " << elem.second->getName() << " ValueType " << elem.second->getMeasurement()->mMeas.mType;
        switch (elem.second->getMeasurement()->mMeas.mType )
        {
            case tDOUDBLE:
                cout << " double: ";
                cout << elem.second->getMeasurement()->mMeas.dValue;
                break;
            case tINT:
                cout << " int: ";
                cout << elem.second->getMeasurement()->mMeas.iValue;
                break;
            default:
                break;
        }
        cout << endl;
        count++;
    }
    return count;
}
