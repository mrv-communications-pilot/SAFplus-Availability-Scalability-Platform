/* 
 * File Cluster.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#include "EntityId.hxx"
#include "MgtFactory.hxx"
#include "clTransaction.hxx"
#include <string>
#include "clMgtProv.hxx"
#include "SAFplusAmfCommon.hxx"
#include <vector>
#include "AdministrativeState.hxx"
#include "Cluster.hxx"


namespace SAFplusAmf
  {

    /* Apply MGT object factory */
    MGT_REGISTER_IMPL(Cluster, /SAFplusAmf/safplusAmf/Cluster)

    Cluster::Cluster(): adminState("adminState"), startupAssignmentDelay("startupAssignmentDelay")
    {
        this->addChildObject(&adminState, "adminState");
        this->addChildObject(&startupAssignmentDelay, "startupAssignmentDelay");
        this->tag.assign("Cluster");
    };

    Cluster::Cluster(std::string nameValue): adminState("adminState"), startupAssignmentDelay("startupAssignmentDelay")
    {
        this->name.value =  nameValue;
        this->addChildObject(&adminState, "adminState");
        this->addChildObject(&startupAssignmentDelay, "startupAssignmentDelay");
        this->tag.assign("Cluster");
    };

    std::vector<std::string> Cluster::getKeys()
    {
        std::string keyNames[] = { "name" };
        return std::vector<std::string> (keyNames, keyNames + sizeof(keyNames) / sizeof(keyNames[0]));
    };

    std::vector<std::string>* Cluster::getChildNames()
    {
        std::string childNames[] = { "name", "id", "adminState", "startupAssignmentDelay" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    /*
     * XPATH: /SAFplusAmf/safplusAmf/Cluster/adminState
     */
    ::SAFplusAmf::AdministrativeState Cluster::getAdminState()
    {
        return this->adminState.value;
    };

    /*
     * XPATH: /SAFplusAmf/safplusAmf/Cluster/adminState
     */
    void Cluster::setAdminState(::SAFplusAmf::AdministrativeState &adminStateValue, SAFplus::Transaction &t)
    {
        if(&t == &SAFplus::NO_TXN) this->adminState.value = adminStateValue;
        else
        {
            SAFplus::SimpleTxnOperation<::SAFplusAmf::AdministrativeState> *opt = new SAFplus::SimpleTxnOperation<::SAFplusAmf::AdministrativeState>(&(adminState.value),adminStateValue);
            t.addOperation(opt);
        }
    };

    /*
     * XPATH: /SAFplusAmf/safplusAmf/Cluster/startupAssignmentDelay
     */
    SaTimeT Cluster::getStartupAssignmentDelay()
    {
        return this->startupAssignmentDelay.value;
    };

    /*
     * XPATH: /SAFplusAmf/safplusAmf/Cluster/startupAssignmentDelay
     */
    void Cluster::setStartupAssignmentDelay(SaTimeT &startupAssignmentDelayValue, SAFplus::Transaction &t)
    {
        if(&t == &SAFplus::NO_TXN) this->startupAssignmentDelay.value = startupAssignmentDelayValue;
        else
        {
            SAFplus::SimpleTxnOperation<SaTimeT> *opt = new SAFplus::SimpleTxnOperation<SaTimeT>(&(startupAssignmentDelay.value),startupAssignmentDelayValue);
            t.addOperation(opt);
        }
    };

    Cluster::~Cluster()
    {
    };

}
/* namespace ::SAFplusAmf */
