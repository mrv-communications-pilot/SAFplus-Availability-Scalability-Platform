/* 
 * File EntityStandbyStatus.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#include <iostream>
#include "EntityStandbyStatus.hxx"


namespace ENTITYSTATETCMIB {

     EntityStandbyStatus::EntityStandbyStatus() {
    };

    int EntityStandbyStatus::getValue() {
        return this->Value;
    };

    void EntityStandbyStatus::setValue(int value) {
        this->Value = value;
    };

    ENTITYSTATETCMIB::EntityStandbyStatus& EntityStandbyStatus::operator=(ENTITYSTATETCMIB::EntityStandbyStatus& EntityStandbyStatus) {
        Value = EntityStandbyStatus.Value;
        return *this;
    };

     EntityStandbyStatus::~EntityStandbyStatus() {
    };

    std::ostream& operator<<(std::ostream& os, const ENTITYSTATETCMIB::EntityStandbyStatus& EntityStandbyStatus) {
        return os << EntityStandbyStatus.Value;
    };

    std::istream& operator>>(std::istream& in, ENTITYSTATETCMIB::EntityStandbyStatus& EntityStandbyStatus) {
        return in >> EntityStandbyStatus.Value;
    };

}
/* namespace ENTITYSTATETCMIB */
