/* 
 * File CapabilityModel.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "SAFplusAmfCommon.hxx"

#include "MgtEnumType.hxx"
#include <iostream>
#include "CapabilityModel.hxx"

using namespace SAFplusAmf;

namespace SAFplusAmf
  {

    /*
     * Provide an implementation of the en2str_map lookup table.
     */
    const CapabilityModelManager::map_t CapabilityModelManager::en2str_map = {
            pair_t(CapabilityModel::x_active_and_y_standby, "x_active_and_y_standby"),
            pair_t(CapabilityModel::x_active_or_y_standby, "x_active_or_y_standby"),
            pair_t(CapabilityModel::not_preinstantiable, "not_preinstantiable")
    }; // uses c++11 initializer lists 

    const char* c_str(const SAFplusAmf::CapabilityModel &capabilityModel)
    {
        return CapabilityModelManager::c_str(capabilityModel);
    };

    std::ostream& operator<<(std::ostream &os, const SAFplusAmf::CapabilityModel &capabilityModel)
    {
        return os << CapabilityModelManager::toString(capabilityModel);
    };

    std::istream& operator>>(std::istream &is, SAFplusAmf::CapabilityModel &capabilityModel)
    {
        std::string buf;
        is >> buf;
        capabilityModel = CapabilityModelManager::toEnum(buf);
        return is;
    };

}
/* namespace ::SAFplusAmf */
