/* 
 * File ZeroBasedCounter32.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef ZEROBASEDCOUNTER32_HXX_
#define ZEROBASEDCOUNTER32_HXX_
#include "ietfYangTypesCommon.hxx"

#include <iostream>
#include "clTransaction.hxx"
#include <cstdint>

namespace ietfYangTypes
  {

    class ZeroBasedCounter32 {
    public:
        ::uint32_t value;

    public:
        ZeroBasedCounter32();
        ::uint32_t getValue();
        void setValue(::uint32_t value, SAFplus::Transaction &t=SAFplus::NO_TXN);
        ::ietfYangTypes::ZeroBasedCounter32& operator=(const ::ietfYangTypes::ZeroBasedCounter32 &zeroBasedCounter32);
        friend std::ostream& operator<<(std::ostream &os, const ::ietfYangTypes::ZeroBasedCounter32 &zeroBasedCounter32);
        friend std::istream& operator>>(std::istream &is, ::ietfYangTypes::ZeroBasedCounter32 &zeroBasedCounter32);
        ~ZeroBasedCounter32();

    };
}
/* namespace ::ietfYangTypes */
#endif /* ZEROBASEDCOUNTER32_HXX_ */