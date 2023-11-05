 
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

        std::cout << "Se toimii!\n";
        std::cout << "No files given as parameter\n";
    } else {
        setlocale(LC_ALL, "en_US.UTF-8");
        //setlocale(LC_ALL, "fi_FI.UTF-8");


    }

    // Simple demo
    {
        Scheduler readTimer ;

        ADC_sensor dummyADC(1,2);
    }

    return 0;
}
