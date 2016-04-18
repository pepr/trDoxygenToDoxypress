// There is the file of the same name in Doxygen. Here it is specific for the converter.
#ifndef CLASSDEF_H
#define CLASSDEF_H

#include <string>
#include "qcstring.h"

/** Stub for the converter.
*/
class ClassDef
{
public:
    /** The various compound types */
    enum CompoundType {
        Class,     //=Entry::CLASS_SEC, 
        Struct,    //=Entry::STRUCT_SEC, 
        Union,     //=Entry::UNION_SEC,
        Interface, //=Entry::INTERFACE_SEC,
        Protocol,  //=Entry::PROTOCOL_SEC,
        Category,  //=Entry::CATEGORY_SEC,
        Exception, //=Entry::EXCEPTION_SEC
        Service,   //=Entry::CLASS_SEC
        Singleton, //=Entry::CLASS_SEC
    };
};

#endif
