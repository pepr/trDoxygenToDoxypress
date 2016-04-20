// stub to simulate Doxygen settings + auxiliary...
#ifndef XXX_H
#define XXX_H

#include <string>

std::string generateMarker(int id);
std::string getDotImageExtension();

// The stub uses the following only for the call 
//      Config_getBool(OPTIMIZE_OUTPUT_FOR_C)

#define OPTIMIZE_OUTPUT_FOR_C "whatever string for the stub"
#define OPTIMIZE_OUTPUT_JAVA "whatever string for the stub"

bool Config_getBool(const std::string & s);
void Config_setBool(bool bValue);


#endif // XXX_H