/* 
 * File ServiceInstance.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "SAFplusAmfCommon.hxx"

#include "AssignmentState.hxx"
#include "clMgtIdentifier.hxx"
#include "clTransaction.hxx"
#include "clMgtProv.hxx"
#include "clMgtIdentifierList.hxx"
#include "ComponentServiceInstance.hxx"
#include "ServiceGroup.hxx"
#include "clMgtList.hxx"
#include <vector>
#include "MgtFactory.hxx"
#include <cstdint>
#include "AdministrativeState.hxx"
#include "EntityId.hxx"
#include <string>
#include "ServiceUnit.hxx"
#include "ServiceInstance.hxx"

using namespace SAFplusAmf;

namespace SAFplusAmf
  {

    /* Apply MGT object factory */
    MGT_REGISTER_IMPL(ServiceInstance, /SAFplusAmf/safplusAmf/ServiceInstance)

    ServiceInstance::ServiceInstance(): adminState("adminState"), assignmentState("assignmentState"), preferredActiveAssignments("preferredActiveAssignments"), preferredStandbyAssignments("preferredStandbyAssignments"), rank("rank"), activeAssignments("activeAssignments"), standbyAssignments("standbyAssignments"), componentServiceInstances("componentServiceInstances"), serviceGroup("serviceGroup"), activeWeightList("activeWeight"), standbyWeightList("standbyWeight")
    {
        this->addChildObject(&adminState, "adminState");
        this->addChildObject(&assignmentState, "assignmentState");
        this->addChildObject(&preferredActiveAssignments, "preferredActiveAssignments");
        this->addChildObject(&preferredStandbyAssignments, "preferredStandbyAssignments");
        this->addChildObject(&rank, "rank");
        this->addChildObject(&activeAssignments, "activeAssignments");
        activeAssignments.config = false;
        this->addChildObject(&standbyAssignments, "standbyAssignments");
        standbyAssignments.config = false;
        this->addChildObject(&componentServiceInstances, "componentServiceInstances");
        this->addChildObject(&serviceGroup, "serviceGroup");
        this->addChildObject(&numActiveAssignments, "numActiveAssignments");
        numActiveAssignments.config = false;
        this->addChildObject(&numStandbyAssignments, "numStandbyAssignments");
        numStandbyAssignments.config = false;
        this->addChildObject(&activeWeightList, "activeWeight");
        this->addChildObject(&standbyWeightList, "standbyWeight");
        activeWeightList.childXpath="/SAFplusAmf/safplusAmf/ServiceInstance/activeWeight";
        activeWeightList.setListKey("resource");
        standbyWeightList.childXpath="/SAFplusAmf/safplusAmf/ServiceInstance/standbyWeight";
        standbyWeightList.setListKey("resource");
        this->tag.assign("ServiceInstance");
    };

    ServiceInstance::ServiceInstance(std::string nameValue): adminState("adminState"), assignmentState("assignmentState"), preferredActiveAssignments("preferredActiveAssignments"), preferredStandbyAssignments("preferredStandbyAssignments"), rank("rank"), activeAssignments("activeAssignments"), standbyAssignments("standbyAssignments"), componentServiceInstances("componentServiceInstances"), serviceGroup("serviceGroup"), activeWeightList("activeWeight"), standbyWeightList("standbyWeight")
    {
        this->name.value =  nameValue;
        this->addChildObject(&adminState, "adminState");
        this->addChildObject(&assignmentState, "assignmentState");
        this->addChildObject(&preferredActiveAssignments, "preferredActiveAssignments");
        this->addChildObject(&preferredStandbyAssignments, "preferredStandbyAssignments");
        this->addChildObject(&rank, "rank");
        this->addChildObject(&activeAssignments, "activeAssignments");
        activeAssignments.config = false;
        this->addChildObject(&standbyAssignments, "standbyAssignments");
        standbyAssignments.config = false;
        this->addChildObject(&componentServiceInstances, "componentServiceInstances");
        this->addChildObject(&serviceGroup, "serviceGroup");
        this->addChildObject(&numActiveAssignments, "numActiveAssignments");
        numActiveAssignments.config = false;
        this->addChildObject(&numStandbyAssignments, "numStandbyAssignments");
        numStandbyAssignments.config = false;
        this->addChildObject(&activeWeightList, "activeWeight");
        this->addChildObject(&standbyWeightList, "standbyWeight");
        activeWeightList.childXpath="/SAFplusAmf/safplusAmf/ServiceInstance/activeWeight";
        activeWeightList.setListKey("resource");
        standbyWeightList.childXpath="/SAFplusAmf/safplusAmf/ServiceInstance/standbyWeight";
        standbyWeightList.setListKey("resource");
        this->tag.assign("ServiceInstance");
    };

    std::vector<std::string> ServiceInstance::getKeys()
    {
        std::string keyNames[] = { "name" };
        return std::vector<std::string> (keyNames, keyNames + sizeof(keyNames) / sizeof(keyNames[0]));
    };

    std::vector<std::string>* ServiceInstance::getChildNames()
    {
        std::string childNames[] = { "name", "id", "adminState", "assignmentState", "preferredActiveAssignments", "preferredStandbyAssignments", "rank", "activeWeight", "standbyWeight", "activeAssignments", "standbyAssignments", "numActiveAssignments", "numStandbyAssignments", "componentServiceInstances", "serviceGroup" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    /*
     * XPATH: /SAFplusAmf/safplusAmf/ServiceInstance/adminState
     */
    ::SAFplusAmf::AdministrativeState ServiceInstance::getAdminState()
    {
        return this->adminState.value;
    };

    /*
     * XPATH: /SAFplusAmf/safplusAmf/ServiceInstance/adminState
     */
    void ServiceInstance::setAdminState(::SAFplusAmf::AdministrativeState &adminStateValue, SAFplus::Transaction &t)
    {
        if(&t == &SAFplus::NO_TXN) this->adminState.value = adminStateValue;
        else
        {
            SAFplus::SimpleTxnOperation<::SAFplusAmf::AdministrativeState> *opt = new SAFplus::SimpleTxnOperation<::SAFplusAmf::AdministrativeState>(&(adminState.value),adminStateValue);
            t.addOperation(opt);
        }
    };

    /*
     * XPATH: /SAFplusAmf/safplusAmf/ServiceInstance/assignmentState
     */
    ::SAFplusAmf::AssignmentState ServiceInstance::getAssignmentState()
    {
        return this->assignmentState.value;
    };

    /*
     * XPATH: /SAFplusAmf/safplusAmf/ServiceInstance/assignmentState
     */
    void ServiceInstance::setAssignmentState(::SAFplusAmf::AssignmentState &assignmentStateValue, SAFplus::Transaction &t)
    {
        if(&t == &SAFplus::NO_TXN) this->assignmentState.value = assignmentStateValue;
        else
        {
            SAFplus::SimpleTxnOperation<::SAFplusAmf::AssignmentState> *opt = new SAFplus::SimpleTxnOperation<::SAFplusAmf::AssignmentState>(&(assignmentState.value),assignmentStateValue);
            t.addOperation(opt);
        }
    };

    /*
     * XPATH: /SAFplusAmf/safplusAmf/ServiceInstance/preferredActiveAssignments
     */
    ::uint32_t ServiceInstance::getPreferredActiveAssignments()
    {
        return this->preferredActiveAssignments.value;
    };

    /*
     * XPATH: /SAFplusAmf/safplusAmf/ServiceInstance/preferredActiveAssignments
     */
    void ServiceInstance::setPreferredActiveAssignments(::uint32_t preferredActiveAssignmentsValue, SAFplus::Transaction &t)
    {
        if(&t == &SAFplus::NO_TXN) this->preferredActiveAssignments.value = preferredActiveAssignmentsValue;
        else
        {
            SAFplus::SimpleTxnOperation<::uint32_t> *opt = new SAFplus::SimpleTxnOperation<::uint32_t>(&(preferredActiveAssignments.value),preferredActiveAssignmentsValue);
            t.addOperation(opt);
        }
    };

    /*
     * XPATH: /SAFplusAmf/safplusAmf/ServiceInstance/preferredStandbyAssignments
     */
    ::uint32_t ServiceInstance::getPreferredStandbyAssignments()
    {
        return this->preferredStandbyAssignments.value;
    };

    /*
     * XPATH: /SAFplusAmf/safplusAmf/ServiceInstance/preferredStandbyAssignments
     */
    void ServiceInstance::setPreferredStandbyAssignments(::uint32_t preferredStandbyAssignmentsValue, SAFplus::Transaction &t)
    {
        if(&t == &SAFplus::NO_TXN) this->preferredStandbyAssignments.value = preferredStandbyAssignmentsValue;
        else
        {
            SAFplus::SimpleTxnOperation<::uint32_t> *opt = new SAFplus::SimpleTxnOperation<::uint32_t>(&(preferredStandbyAssignments.value),preferredStandbyAssignmentsValue);
            t.addOperation(opt);
        }
    };

    /*
     * XPATH: /SAFplusAmf/safplusAmf/ServiceInstance/rank
     */
    ::uint32_t ServiceInstance::getRank()
    {
        return this->rank.value;
    };

    /*
     * XPATH: /SAFplusAmf/safplusAmf/ServiceInstance/rank
     */
    void ServiceInstance::setRank(::uint32_t rankValue, SAFplus::Transaction &t)
    {
        if(&t == &SAFplus::NO_TXN) this->rank.value = rankValue;
        else
        {
            SAFplus::SimpleTxnOperation<::uint32_t> *opt = new SAFplus::SimpleTxnOperation<::uint32_t>(&(rank.value),rankValue);
            t.addOperation(opt);
        }
    };

    /*
     * XPATH: /SAFplusAmf/safplusAmf/ServiceInstance/activeAssignments
     */
    std::vector<::SAFplusAmf::ServiceUnit*> ServiceInstance::getActiveAssignments()
    {
        return this->activeAssignments.value;
    };

    /*
     * XPATH: /SAFplusAmf/safplusAmf/ServiceInstance/activeAssignments
     */
    void ServiceInstance::setActiveAssignments(::SAFplusAmf::ServiceUnit* activeAssignmentsValue)
    {
        this->activeAssignments.value.push_back(activeAssignmentsValue);
    };

    /*
     * XPATH: /SAFplusAmf/safplusAmf/ServiceInstance/standbyAssignments
     */
    std::vector<::SAFplusAmf::ServiceUnit*> ServiceInstance::getStandbyAssignments()
    {
        return this->standbyAssignments.value;
    };

    /*
     * XPATH: /SAFplusAmf/safplusAmf/ServiceInstance/standbyAssignments
     */
    void ServiceInstance::setStandbyAssignments(::SAFplusAmf::ServiceUnit* standbyAssignmentsValue)
    {
        this->standbyAssignments.value.push_back(standbyAssignmentsValue);
    };

    /*
     * XPATH: /SAFplusAmf/safplusAmf/ServiceInstance/componentServiceInstances
     */
    std::vector<::SAFplusAmf::ComponentServiceInstance*> ServiceInstance::getComponentServiceInstances()
    {
        return this->componentServiceInstances.value;
    };

    /*
     * XPATH: /SAFplusAmf/safplusAmf/ServiceInstance/componentServiceInstances
     */
    void ServiceInstance::setComponentServiceInstances(::SAFplusAmf::ComponentServiceInstance* componentServiceInstancesValue)
    {
        this->componentServiceInstances.value.push_back(componentServiceInstancesValue);
    };

    /*
     * XPATH: /SAFplusAmf/safplusAmf/ServiceInstance/serviceGroup
     */
    SAFplusAmf::ServiceGroup* ServiceInstance::getServiceGroup()
    {
        return this->serviceGroup.value;
    };

    /*
     * XPATH: /SAFplusAmf/safplusAmf/ServiceInstance/serviceGroup
     */
    void ServiceInstance::setServiceGroup(SAFplusAmf::ServiceGroup* serviceGroupValue, SAFplus::Transaction &t)
    {
        if(&t == &SAFplus::NO_TXN) this->serviceGroup.value = serviceGroupValue;
        else
        {
            SAFplus::SimpleTxnOperation<SAFplusAmf::ServiceGroup*> *opt = new SAFplus::SimpleTxnOperation<SAFplusAmf::ServiceGroup*>(&(serviceGroup.value),serviceGroupValue);
            t.addOperation(opt);
        }
    };

    /*
     * XPATH: /SAFplusAmf/safplusAmf/ServiceInstance/numActiveAssignments
     */
    SAFplus::MgtHistoryStat<int>* ServiceInstance::getNumActiveAssignments()
    {
        return dynamic_cast<SAFplus::MgtHistoryStat<int>*>(this->getChildObject("numActiveAssignments"));
    };

    /*
     * XPATH: /SAFplusAmf/safplusAmf/ServiceInstance/numActiveAssignments
     */
    void ServiceInstance::addNumActiveAssignments(SAFplus::MgtHistoryStat<int> *numActiveAssignmentsValue)
    {
        this->addChildObject(numActiveAssignmentsValue, "numActiveAssignments");
    };

    /*
     * XPATH: /SAFplusAmf/safplusAmf/ServiceInstance/numStandbyAssignments
     */
    SAFplus::MgtHistoryStat<int>* ServiceInstance::getNumStandbyAssignments()
    {
        return dynamic_cast<SAFplus::MgtHistoryStat<int>*>(this->getChildObject("numStandbyAssignments"));
    };

    /*
     * XPATH: /SAFplusAmf/safplusAmf/ServiceInstance/numStandbyAssignments
     */
    void ServiceInstance::addNumStandbyAssignments(SAFplus::MgtHistoryStat<int> *numStandbyAssignmentsValue)
    {
        this->addChildObject(numStandbyAssignmentsValue, "numStandbyAssignments");
    };

    ServiceInstance::~ServiceInstance()
    {
    };

}
/* namespace ::SAFplusAmf */
