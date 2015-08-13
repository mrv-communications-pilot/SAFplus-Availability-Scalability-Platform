/* 
 * File SAFplusAmfModule.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "SAFplusAmfCommon.hxx"

#include "clMgtModule.hxx"
#include "EntityByName.hxx"
#include "Application.hxx"
#include "EntityById.hxx"
#include "MgtFactory.hxx"
#include "SafplusAmf.hxx"
#include "Node.hxx"
#include "ServiceGroup.hxx"
#include "ComponentServiceInstance.hxx"
#include "Component.hxx"
#include "Cluster.hxx"
#include <vector>
#include "ServiceUnit.hxx"
#include "ServiceInstance.hxx"
#include "SAFplusAmfModule.hxx"


namespace SAFplusAmf
  {

    /* Apply MGT object factory */
    MGT_REGISTER_IMPL(SAFplusAmfModule, /)

    SAFplusAmfModule::SAFplusAmfModule(): SAFplus::MgtModule("")
    {
        this->addChildObject(&safplusAmf, "safplusAmf");
    };

    std::vector<std::string>* SAFplusAmfModule::getChildNames()
    {
        std::string childNames[] = { "safplusAmf" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    SAFplusAmfModule::~SAFplusAmfModule()
    {
    };

}
/* namespace ::SAFplusAmf */
