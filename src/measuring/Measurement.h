
#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <string>

enum MeasurementType {tNONE, tDOUDBLE, tINT};

typedef int64_t tMeasurementTime;


struct SingleMeasurement {
  tMeasurementTime  mMeasureTime;
  MeasurementType    mType;
  union {
    double dValue;
    int        iValue;    // GPIO value goes here. 1 for hight and 0 for low.
  };
};

/**
  * class Measurement
  * 
  */

class Measurement
{
//private:
public:
  std::string mName;
  SingleMeasurement mMeas;

public:
  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  Measurement();
  Measurement(MeasurementType type, std::string);

  /**
   * Empty Destructor
   */
  virtual ~Measurement();

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  

  void setMeasurement(struct SingleMeasurement value);

  /**
   * @return MeasurementType
   */
  MeasurementType getResultType();


  /**
   * @return double
   */
  double getDouble();


  /**
   * @return int
   */
  int getInt();


  /**
   * @return string
   */
  std::string getSourceName();


  /**
   * Time in seconds since start
   * @return long int
   */
  unsigned int getMeasureTime();

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

#endif // MEASUREMENT_H
