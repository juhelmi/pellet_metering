 
#include <iostream>
#include <fstream>
#include <filesystem>
//#include <format>
#include <boost/format.hpp>




#include <nlohmann/json.hpp>

#include "config.hpp"
#include "i2c_routines.h"

#include "Scheduler.h"
#include "Sensor.h"
#include "ADC_sensor.h"
#include "Air_pressure.h"
#include "BME280_sensor.h"

using namespace std;
namespace fs = std::filesystem;

bool debug_run = false;


int main(int argc, char *argv[])
{

    if (argc <= 1)
    {
        std::cout << project_name << '\n';
        std::cout << project_version << '\n';

        std::cout << "JSON Lib Version:" << NLOHMANN_JSON_VERSION_MAJOR << "."
                << NLOHMANN_JSON_VERSION_MINOR << "."
                << NLOHMANN_JSON_VERSION_PATCH << "\n";

    } else {
        setlocale(LC_ALL, "en_US.UTF-8");
        //setlocale(LC_ALL, "fi_FI.UTF-8");


    }

    // Simple demo
    {
        Scheduler readTimer ;

        int intervalX = 10000;

        I2C_sensor  dummyI2C(intervalX, 0, 0);
        ADC_sensor dummyADC(1*intervalX, 1,2);
        Air_pressure dummyPressure(2*intervalX, 2,3);
        BME280_sensor dummyBME(4+1*intervalX, 4,0x77);

        readTimer.addSensor(&dummyADC);
        readTimer.addSensor(&dummyPressure);
        readTimer.addSensor(&dummyBME);

        for (int i; i<1000; i++)
        {
            readTimer.pollTimedSensors();
            usleep(1000);
        }
    }

    return 0;
}
