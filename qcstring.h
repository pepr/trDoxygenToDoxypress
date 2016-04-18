// stub for the converter
#ifndef QCSTRING_H
#define QCSTRING_H

#include <string>

class QCString : public std::string
{
public:
    QCString(const char * c) : std::string(c) {}
    QCString(std::string & s) : std::string(s) {}
    QCString() : std::string("") {}
    QCString &QCString::sprintf( const char *format, ... )
    {
      return *this;
    } 
};

#endif // QCSTRING_H
