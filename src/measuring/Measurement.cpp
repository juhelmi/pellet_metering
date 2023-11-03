#include "Measurement.h"

// Constructors/Destructors
//  

Measurement::Measurement()
{
}

Measurement::~Measurement()
{
}

//  
// Methods
//  

std::string Measurement::getSourceName()
{
    return mName;
}

unsigned int Measurement::getMeasureTime()
{
    return mMeas.mMeasureTime;
}

MeasurementType Measurement::getResultType()
{
    return mMeas.mType;
}

double Measurement::getDouble()
{
    if (mMeas.mType != tDOUDBLE)
    {
        return 0;
    } else {
        return mMeas.dValue;
    }
}

int Measurement::getInt()
{
    if (mMeas.mType != tINT)
    {
        return 0;
    } else {
        return mMeas.iValue;
    }
}

// Accessor methods
//  


// Other methods
//  


