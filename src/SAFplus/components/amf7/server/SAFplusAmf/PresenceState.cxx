/* 
 * File PresenceState.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#include <iostream>
#include "PresenceState.hxx"


namespace SAFplusAmf {

     PresenceState::PresenceState() {
    };

    int PresenceState::getValue() {
        return this->Value;
    };

    void PresenceState::setValue(int value) {
        this->Value = value;
    };

    SAFplusAmf::PresenceState& PresenceState::operator=(SAFplusAmf::PresenceState& PresenceState) {
        Value = PresenceState.Value;
        return *this;
    };

     PresenceState::~PresenceState() {
    };

    std::ostream& operator<<(std::ostream& os, const SAFplusAmf::PresenceState& PresenceState) {
        return os << PresenceState.Value;
    };

    std::istream& operator>>(std::istream& in, SAFplusAmf::PresenceState& PresenceState) {
        return in >> PresenceState.Value;
    };

}
/* namespace SAFplusAmf */
