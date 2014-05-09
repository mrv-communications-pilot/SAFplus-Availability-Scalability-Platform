/* 
 * File NumSpareServiceUnits.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "SAFplusAmfCommon.hxx"

#include <vector>
#include "MgtFactory.hxx"
#include "IntStatistic.hxx"
#include "NumSpareServiceUnits.hxx"


namespace SAFplusAmf
  {

    /* Apply MGT object factory */
    MGT_REGISTER_IMPL(NumSpareServiceUnits, /SAFplusAmf/ServiceGroup/numSpareServiceUnits)

    NumSpareServiceUnits::NumSpareServiceUnits()
    {
        this->name.assign("numSpareServiceUnits");
    };

    void NumSpareServiceUnits::toString(std::stringstream &xmlString)
    {
        /* TODO:  */
    };

    std::vector<std::string>* NumSpareServiceUnits::getChildNames()
    {
        std::string childNames[] = { "current", "history10sec", "history1min", "history10min", "history1hour", "history12hour", "history1day", "history1week", "history1month" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    NumSpareServiceUnits::~NumSpareServiceUnits()
    {
    };

}
/* namespace SAFplusAmf */
