#include <sstream>

#include "xxx.h"

std::string generateMarker(int id)
{
    std::ostringstream result;
    result << "@" << id;
    return result.str();
}


std::string getDotImageExtension()
{ 
    return "dot";
}


static bool ConfigBool = false;

bool Config_getBool(const std::string & s)
{
    return ConfigBool;
}


void Config_setBool(bool bValue)
{
    ConfigBool = bValue;
}
