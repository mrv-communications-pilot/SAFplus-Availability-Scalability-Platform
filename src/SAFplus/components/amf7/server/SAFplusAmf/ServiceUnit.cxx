/* 
 * File ServiceUnit.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#include "RestartCount.hxx"
#include "StandbyServiceInstances.hxx"
#include <string>
#include "RestartCount.hxx"
#include "StandbyServiceInstances.hxx"
#include "MgtFactory.hxx"
#include "AdministrativeState.hxx"
#include "ActiveServiceInstances.hxx"
#include "ActiveServiceInstances.hxx"
#include "ReadinessState.hxx"
#include "clMgtObject.hxx"
#include "clMgtProv.hxx"
#include "HighAvailabilityReadinessState.hxx"
#include <vector>
#include "HighAvailabilityState.hxx"
#include "PresenceState.hxx"
#include "clMgtProvList.hxx"
#include "ServiceUnit.hxx"


namespace SAFplusAmf {

    /* Apply MGT object factory */
    REGISTERIMPL(ServiceUnit, /SAFplusAmf/ServiceUnit)

     ServiceUnit::ServiceUnit(): ClMgtObject("ServiceUnit"), name("name"), id("id"), adminState("adminState"), rank("rank"), failover("failover"), preInstantiable("preInstantiable"), saAmfSUHostNodeOrNodeGroup("saAmfSUHostNodeOrNodeGroup"), presenceState("presenceState"), readinessState("readinessState"), haReadinessState("haReadinessState"), haState("haState"), operState("operState"), assignedServiceInstances("assignedServiceInstances") {
        this->addChildObject(&name, "name");
        this->addChildObject(&id, "id");
        this->addChildObject(&adminState, "adminState");
        this->addChildObject(&rank, "rank");
        this->addChildObject(&failover, "failover");
        this->addChildObject(&preInstantiable, "preInstantiable");
        this->addChildObject(&saAmfSUHostNodeOrNodeGroup, "saAmfSUHostNodeOrNodeGroup");
        this->addChildObject(&presenceState, "presenceState");
        this->addChildObject(&readinessState, "readinessState");
        this->addChildObject(&haReadinessState, "haReadinessState");
        this->addChildObject(&haState, "haState");
        this->addChildObject(&operState, "operState");
        this->addChildObject(&assignedServiceInstances, "assignedServiceInstances");
        this->addKey("name");
    };

     ServiceUnit::ServiceUnit(std::string nameValue): ClMgtObject("ServiceUnit"), name("name"), id("id"), adminState("adminState"), rank("rank"), failover("failover"), preInstantiable("preInstantiable"), saAmfSUHostNodeOrNodeGroup("saAmfSUHostNodeOrNodeGroup"), presenceState("presenceState"), readinessState("readinessState"), haReadinessState("haReadinessState"), haState("haState"), operState("operState"), assignedServiceInstances("assignedServiceInstances") {
        this->name.Value =  nameValue;
        this->addKey("name");
        this->addChildObject(&name, "name");
        this->addChildObject(&id, "id");
        this->addChildObject(&adminState, "adminState");
        this->addChildObject(&rank, "rank");
        this->addChildObject(&failover, "failover");
        this->addChildObject(&preInstantiable, "preInstantiable");
        this->addChildObject(&saAmfSUHostNodeOrNodeGroup, "saAmfSUHostNodeOrNodeGroup");
        this->addChildObject(&presenceState, "presenceState");
        this->addChildObject(&readinessState, "readinessState");
        this->addChildObject(&haReadinessState, "haReadinessState");
        this->addChildObject(&haState, "haState");
        this->addChildObject(&operState, "operState");
        this->addChildObject(&assignedServiceInstances, "assignedServiceInstances");
    };

    std::vector<std::string> ServiceUnit::getKeys() {
        std::string keyNames[] = { "name" };
        return std::vector<std::string> (keyNames, keyNames + sizeof(keyNames) / sizeof(keyNames[0]));
    };

    std::vector<std::string>* ServiceUnit::getChildNames() {
        std::string childNames[] = { "name", "id", "adminState", "rank", "failover", "preInstantiable", "saAmfSUHostNodeOrNodeGroup", "presenceState", "readinessState", "haReadinessState", "haState", "operState", "assignedServiceInstances", "activeServiceInstances", "standbyServiceInstances", "restartCount" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/name
     */
    std::string ServiceUnit::getName() {
        return this->name.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/name
     */
    void ServiceUnit::setName(std::string nameValue) {
        this->name.Value = nameValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/id
     */
    unsigned short int ServiceUnit::getId() {
        return this->id.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/id
     */
    void ServiceUnit::setId(unsigned short int idValue) {
        this->id.Value = idValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/adminState
     */
    SAFplusAmf::AdministrativeState ServiceUnit::getAdminState() {
        return this->adminState.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/adminState
     */
    void ServiceUnit::setAdminState(SAFplusAmf::AdministrativeState adminStateValue) {
        this->adminState.Value = adminStateValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/rank
     */
    unsigned int ServiceUnit::getRank() {
        return this->rank.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/rank
     */
    void ServiceUnit::setRank(unsigned int rankValue) {
        this->rank.Value = rankValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/failover
     */
    bool ServiceUnit::getFailover() {
        return this->failover.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/failover
     */
    void ServiceUnit::setFailover(bool failoverValue) {
        this->failover.Value = failoverValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/preInstantiable
     */
    bool ServiceUnit::getPreInstantiable() {
        return this->preInstantiable.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/preInstantiable
     */
    void ServiceUnit::setPreInstantiable(bool preInstantiableValue) {
        this->preInstantiable.Value = preInstantiableValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/saAmfSUHostNodeOrNodeGroup
     */
    std::string ServiceUnit::getSaAmfSUHostNodeOrNodeGroup() {
        return this->saAmfSUHostNodeOrNodeGroup.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/saAmfSUHostNodeOrNodeGroup
     */
    void ServiceUnit::setSaAmfSUHostNodeOrNodeGroup(std::string saAmfSUHostNodeOrNodeGroupValue) {
        this->saAmfSUHostNodeOrNodeGroup.Value = saAmfSUHostNodeOrNodeGroupValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/presenceState
     */
    SAFplusAmf::PresenceState ServiceUnit::getPresenceState() {
        return this->presenceState.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/presenceState
     */
    void ServiceUnit::setPresenceState(SAFplusAmf::PresenceState presenceStateValue) {
        this->presenceState.Value = presenceStateValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/readinessState
     */
    SAFplusAmf::ReadinessState ServiceUnit::getReadinessState() {
        return this->readinessState.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/readinessState
     */
    void ServiceUnit::setReadinessState(SAFplusAmf::ReadinessState readinessStateValue) {
        this->readinessState.Value = readinessStateValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/haReadinessState
     */
    SAFplusAmf::HighAvailabilityReadinessState ServiceUnit::getHaReadinessState() {
        return this->haReadinessState.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/haReadinessState
     */
    void ServiceUnit::setHaReadinessState(SAFplusAmf::HighAvailabilityReadinessState haReadinessStateValue) {
        this->haReadinessState.Value = haReadinessStateValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/haState
     */
    SAFplusAmf::HighAvailabilityState ServiceUnit::getHaState() {
        return this->haState.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/haState
     */
    void ServiceUnit::setHaState(SAFplusAmf::HighAvailabilityState haStateValue) {
        this->haState.Value = haStateValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/operState
     */
    bool ServiceUnit::getOperState() {
        return this->operState.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/operState
     */
    void ServiceUnit::setOperState(bool operStateValue) {
        this->operState.Value = operStateValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/assignedServiceInstances
     */
    std::vector<std::string> ServiceUnit::getAssignedServiceInstances() {
        return this->assignedServiceInstances.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/assignedServiceInstances
     */
    void ServiceUnit::setAssignedServiceInstances(std::string assignedServiceInstancesValue) {
        this->assignedServiceInstances.Value.push_back(assignedServiceInstancesValue);
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/activeServiceInstances
     */
    SAFplusAmf::ActiveServiceInstances* ServiceUnit::getActiveServiceInstances() {
        return (ActiveServiceInstances*)this->getChildObject("activeServiceInstances");
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/activeServiceInstances
     */
    void ServiceUnit::addActiveServiceInstances(SAFplusAmf::ActiveServiceInstances *activeServiceInstancesValue) {
        this->addChildObject(activeServiceInstancesValue, "activeServiceInstances");
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/standbyServiceInstances
     */
    SAFplusAmf::StandbyServiceInstances* ServiceUnit::getStandbyServiceInstances() {
        return (StandbyServiceInstances*)this->getChildObject("standbyServiceInstances");
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/standbyServiceInstances
     */
    void ServiceUnit::addStandbyServiceInstances(SAFplusAmf::StandbyServiceInstances *standbyServiceInstancesValue) {
        this->addChildObject(standbyServiceInstancesValue, "standbyServiceInstances");
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/restartCount
     */
    SAFplusAmf::RestartCount* ServiceUnit::getRestartCount() {
        return (RestartCount*)this->getChildObject("restartCount");
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/restartCount
     */
    void ServiceUnit::addRestartCount(SAFplusAmf::RestartCount *restartCountValue) {
        this->addChildObject(restartCountValue, "restartCount");
    };

     ServiceUnit::~ServiceUnit() {
    };

}
/* namespace SAFplusAmf */
