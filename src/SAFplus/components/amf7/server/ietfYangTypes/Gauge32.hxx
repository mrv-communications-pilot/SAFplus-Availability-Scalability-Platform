/* 
 * File Gauge32.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#ifndef GAUGE32_HXX_
#define GAUGE32_HXX_

#include <iostream>

namespace ietfYangTypes {

    class Gauge32 {
    public:
        unsigned int Value;

    public:
         Gauge32();
        unsigned int getValue();
        void setValue(unsigned int value);
        ietfYangTypes::Gauge32& operator=(ietfYangTypes::Gauge32& gauge32);
        friend std::ostream& operator<<(std::ostream& os, const ietfYangTypes::Gauge32& gauge32);
        friend std::istream& operator>>(std::istream& in, ietfYangTypes::Gauge32& gauge32);
         ~Gauge32();

    };
}
/* namespace ietfYangTypes */
#endif /* GAUGE32_HXX_ */
