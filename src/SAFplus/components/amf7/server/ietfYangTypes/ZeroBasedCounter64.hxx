/* 
 * File ZeroBasedCounter64.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#ifndef ZEROBASEDCOUNTER64_HXX_
#define ZEROBASEDCOUNTER64_HXX_

#include <iostream>

namespace ietfYangTypes {

    class ZeroBasedCounter64 {
    public:
        unsigned long int Value;

    public:
         ZeroBasedCounter64();
        unsigned long int getValue();
        void setValue(unsigned long int value);
        ietfYangTypes::ZeroBasedCounter64& operator=(ietfYangTypes::ZeroBasedCounter64& zeroBasedCounter64);
        friend std::ostream& operator<<(std::ostream& os, const ietfYangTypes::ZeroBasedCounter64& zeroBasedCounter64);
        friend std::istream& operator>>(std::istream& in, ietfYangTypes::ZeroBasedCounter64& zeroBasedCounter64);
         ~ZeroBasedCounter64();

    };
}
/* namespace ietfYangTypes */
#endif /* ZEROBASEDCOUNTER64_HXX_ */
