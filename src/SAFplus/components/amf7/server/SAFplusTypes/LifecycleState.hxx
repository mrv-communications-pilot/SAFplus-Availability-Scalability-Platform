/* 
 * File LifecycleState.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#ifndef LIFECYCLESTATE_HXX_
#define LIFECYCLESTATE_HXX_

#include <iostream>

namespace SAFplusTypes {

    class LifecycleState {
    public:
        int Value;

    public:
         LifecycleState();
        int getValue();
        void setValue(int value);
        SAFplusTypes::LifecycleState& operator=(SAFplusTypes::LifecycleState& lifecycleState);
        friend std::ostream& operator<<(std::ostream& os, const SAFplusTypes::LifecycleState& lifecycleState);
        friend std::istream& operator>>(std::istream& in, SAFplusTypes::LifecycleState& lifecycleState);
         ~LifecycleState();

    };
}
/* namespace SAFplusTypes */
#endif /* LIFECYCLESTATE_HXX_ */
