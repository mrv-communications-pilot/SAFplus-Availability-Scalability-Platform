/* 
 * File NumServiceGroups.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef NUMSERVICEGROUPS_HXX_
#define NUMSERVICEGROUPS_HXX_
#include "SAFplusAmfCommon.hxx"

#include <vector>
#include "MgtFactory.hxx"
#include "IntStatistic.hxx"

namespace SAFplusAmf
  {

    class NumServiceGroups : public SAFplusTypes::IntStatistic {

        /* Apply MGT object factory */
        MGT_REGISTER(NumServiceGroups);

    public:
        NumServiceGroups();
        void toString(std::stringstream &xmlString);
        std::vector<std::string>* getChildNames();
        ~NumServiceGroups();

    };
}
/* namespace SAFplusAmf */
#endif /* NUMSERVICEGROUPS_HXX_ */
