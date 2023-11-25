#include "Measurement.h"

#include <sstream>

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

std::string Measurement::getResultAsString()
{
    std::stringstream ss;
    switch (mMeas.mType)
    {
        case tNONE:
            break;
        case tDOUDBLE:
            ss << mMeas.dValue;
            break;
        case tINT:
            ss << mMeas.iValue;
            break;
        default:
            ss << "Measurement undefined type";
            break;
    }
    return ss.str();
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


