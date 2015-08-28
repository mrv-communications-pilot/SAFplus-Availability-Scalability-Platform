/* 
 * File Xpath10.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "ietfYangTypesCommon.hxx"

#include <iostream>
#include <string>
#include "clTransaction.hxx"
#include "Xpath10.hxx"


namespace ietfYangTypes
  {

    Xpath10::Xpath10()
    {
    };

    std::string Xpath10::getValue()
    {
        return this->value;
    };

    void Xpath10::setValue(std::string value, SAFplus::Transaction &t)
    {
        if(&t == &SAFplus::NO_TXN) this->value = value;
        else
        {
            SAFplus::SimpleTxnOperation<std::string> *opt = new SAFplus::SimpleTxnOperation<std::string>(&this->value,value);
            t.addOperation(opt);
        }
    };

    ::ietfYangTypes::Xpath10& Xpath10::operator=(const ::ietfYangTypes::Xpath10 &xpath10)
    {
        value = xpath10.value;
        return *this;
    };

    Xpath10::~Xpath10()
    {
    };

    std::ostream& operator<<(std::ostream &os, const ::ietfYangTypes::Xpath10 &xpath10)
    {
        return os << xpath10.value;
    };

    std::istream& operator>>(std::istream &is, ::ietfYangTypes::Xpath10 &xpath10)
    {
        return is >> xpath10.value;
    };

}
/* namespace ::ietfYangTypes */