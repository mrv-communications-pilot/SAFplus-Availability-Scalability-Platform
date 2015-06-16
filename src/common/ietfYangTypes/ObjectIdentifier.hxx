/* 
 * File ObjectIdentifier.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef OBJECTIDENTIFIER_HXX_
#define OBJECTIDENTIFIER_HXX_
#include "ietfYangTypesCommon.hxx"

#include <iostream>
#include <string>
#include "clTransaction.hxx"

namespace ietfYangTypes
  {

    class ObjectIdentifier {
    public:
        std::string value;

    public:
        ObjectIdentifier();
        std::string getValue();
        void setValue(std::string value, SAFplus::Transaction &t=SAFplus::NO_TXN);
        ietfYangTypes::ObjectIdentifier& operator=(const ietfYangTypes::ObjectIdentifier &objectIdentifier);
        friend std::ostream& operator<<(std::ostream &os, const ietfYangTypes::ObjectIdentifier &objectIdentifier);
        friend std::istream& operator>>(std::istream &is, ietfYangTypes::ObjectIdentifier &objectIdentifier);
        ~ObjectIdentifier();

    };
}
/* namespace ietfYangTypes */
#endif /* OBJECTIDENTIFIER_HXX_ */