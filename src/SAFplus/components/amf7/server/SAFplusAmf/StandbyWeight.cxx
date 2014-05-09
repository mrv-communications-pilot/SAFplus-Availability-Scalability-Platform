/* 
 * File StandbyWeight.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "SAFplusAmfCommon.hxx"

#include <vector>
#include "MgtFactory.hxx"
#include <string>
#include "Capacity.hxx"
#include "StandbyWeight.hxx"


namespace SAFplusAmf
  {

    /* Apply MGT object factory */
    MGT_REGISTER_IMPL(StandbyWeight, /SAFplusAmf/ServiceInstance/standbyWeight)

    StandbyWeight::StandbyWeight()
    {
        this->name.assign("standbyWeight");
    };

    StandbyWeight::StandbyWeight(std::string resourceValue)
    {
        this->resource.value =  resourceValue;
        this->name.assign("standbyWeight");
    };

    void StandbyWeight::toString(std::stringstream &xmlString)
    {
        /* TODO:  */
    };

    std::vector<std::string> StandbyWeight::getKeys()
    {
        std::string keyNames[] = { "resource" };
        return std::vector<std::string> (keyNames, keyNames + sizeof(keyNames) / sizeof(keyNames[0]));
    };

    std::vector<std::string>* StandbyWeight::getChildNames()
    {
        std::string childNames[] = { "resource", "value" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    StandbyWeight::~StandbyWeight()
    {
    };

}
/* namespace SAFplusAmf */
