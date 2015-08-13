/* 
 * File ServiceUnit.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef SERVICEUNIT_HXX_
#define SERVICEUNIT_HXX_
#include "SAFplusAmfCommon.hxx"

#include "Node.hxx"
#include "clMgtIdentifier.hxx"
#include "clTransaction.hxx"
#include "Component.hxx"
#include "MgtFactory.hxx"
#include "AdministrativeState.hxx"
#include <string>
#include "ReadinessState.hxx"
#include "clMgtProv.hxx"
#include "ServiceInstance.hxx"
#include "HighAvailabilityReadinessState.hxx"
#include "ServiceGroup.hxx"
#include <vector>
#include "clMgtIdentifierList.hxx"
#include <cstdint>
#include "PresenceState.hxx"
#include "EntityId.hxx"
#include "HighAvailabilityState.hxx"

namespace SAFplusAmf
  {

    class ServiceUnit : public EntityId {

        /* Apply MGT object factory */
        MGT_REGISTER(ServiceUnit);

    public:

        /*
         * Does the operator want this entity to be off, idle, or in service?
         */
        SAFplus::MgtProv<::SAFplusAmf::AdministrativeState> adminState;

        /*
         * Lower rank is instantiated before higher; but rank 0 means 'don't care'.
         */
        SAFplus::MgtProv<::uint32_t> rank;

        /*
         * TODO
         */
        SAFplus::MgtProv<bool> failover;

        /*
         * Can this service unit be instantiated before being assigned active?  True if ALL components are preinstantiable.
         */
        SAFplus::MgtProv<bool> preinstantiable;

        /*
         * The service unit can only be instantiated on the node (if a node is specified) or on one of the nodes of the node group (if a node group is configured).
         */
        SAFplus::MgtProv<std::string> saAmfSUHostNodeOrNodeGroup;
        SAFplus::MgtProv<::SAFplusAmf::PresenceState> presenceState;
        SAFplus::MgtProv<::SAFplusAmf::ReadinessState> readinessState;

        /*
         * This state field covers ALL work assignments...
         */
        SAFplus::MgtProv<::SAFplusAmf::HighAvailabilityReadinessState> haReadinessState;
        SAFplus::MgtProv<::SAFplusAmf::HighAvailabilityState> haState;

        /*
         * True is enabled, False is disabled.  To move from False to True a 'repair' action must occur.
         */
        SAFplus::MgtProv<bool> operState;
        SAFplus::MgtIdentifierList<SAFplusAmf::ServiceInstance*> assignedServiceInstances;
        SAFplus::MgtIdentifierList<SAFplusAmf::Component*> components;
        SAFplus::MgtIdentifier<SAFplusAmf::Node*> node;
        SAFplus::MgtIdentifier<SAFplusAmf::ServiceGroup*> serviceGroup;

        /*
         * Once this Service Unit is instantiated, how long should I wait before assigning it?
         */
        SAFplus::MgtProv<::uint32_t> probationTime;
        SAFplus::MgtHistoryStat<int> numActiveServiceInstances;
        SAFplus::MgtHistoryStat<int> numStandbyServiceInstances;
        SAFplus::MgtHistoryStat<int> restartCount;

    public:
        ServiceUnit();
        ServiceUnit(std::string nameValue);
        std::vector<std::string> getKeys();
        std::vector<std::string>* getChildNames();

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/adminState
         */
        ::SAFplusAmf::AdministrativeState getAdminState();

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/adminState
         */
        void setAdminState(::SAFplusAmf::AdministrativeState &adminStateValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/rank
         */
        ::uint32_t getRank();

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/rank
         */
        void setRank(::uint32_t rankValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/failover
         */
        bool getFailover();

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/failover
         */
        void setFailover(bool failoverValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/preinstantiable
         */
        bool getPreinstantiable();

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/preinstantiable
         */
        void setPreinstantiable(bool preinstantiableValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/saAmfSUHostNodeOrNodeGroup
         */
        std::string getSaAmfSUHostNodeOrNodeGroup();

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/saAmfSUHostNodeOrNodeGroup
         */
        void setSaAmfSUHostNodeOrNodeGroup(std::string saAmfSUHostNodeOrNodeGroupValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/presenceState
         */
        ::SAFplusAmf::PresenceState getPresenceState();

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/presenceState
         */
        void setPresenceState(::SAFplusAmf::PresenceState &presenceStateValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/readinessState
         */
        ::SAFplusAmf::ReadinessState getReadinessState();

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/readinessState
         */
        void setReadinessState(::SAFplusAmf::ReadinessState &readinessStateValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/haReadinessState
         */
        ::SAFplusAmf::HighAvailabilityReadinessState getHaReadinessState();

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/haReadinessState
         */
        void setHaReadinessState(::SAFplusAmf::HighAvailabilityReadinessState &haReadinessStateValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/haState
         */
        ::SAFplusAmf::HighAvailabilityState getHaState();

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/haState
         */
        void setHaState(::SAFplusAmf::HighAvailabilityState &haStateValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/operState
         */
        bool getOperState();

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/operState
         */
        void setOperState(bool operStateValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/assignedServiceInstances
         */
        std::vector<SAFplusAmf::ServiceInstance*> getAssignedServiceInstances();

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/assignedServiceInstances
         */
        void setAssignedServiceInstances(SAFplusAmf::ServiceInstance* assignedServiceInstancesValue);

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/components
         */
        std::vector<SAFplusAmf::Component*> getComponents();

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/components
         */
        void setComponents(SAFplusAmf::Component* componentsValue);

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/node
         */
        SAFplusAmf::Node* getNode();

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/node
         */
        void setNode(SAFplusAmf::Node* nodeValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/serviceGroup
         */
        SAFplusAmf::ServiceGroup* getServiceGroup();

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/serviceGroup
         */
        void setServiceGroup(SAFplusAmf::ServiceGroup* serviceGroupValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/probationTime
         */
        ::uint32_t getProbationTime();

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/probationTime
         */
        void setProbationTime(::uint32_t probationTimeValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/numActiveServiceInstances
         */
        SAFplus::MgtHistoryStat<int>* getNumActiveServiceInstances();

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/numActiveServiceInstances
         */
        void addNumActiveServiceInstances(SAFplus::MgtHistoryStat<int> *numActiveServiceInstancesValue);

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/numStandbyServiceInstances
         */
        SAFplus::MgtHistoryStat<int>* getNumStandbyServiceInstances();

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/numStandbyServiceInstances
         */
        void addNumStandbyServiceInstances(SAFplus::MgtHistoryStat<int> *numStandbyServiceInstancesValue);

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/restartCount
         */
        SAFplus::MgtHistoryStat<int>* getRestartCount();

        /*
         * XPATH: /SAFplusAmf/safplusAmf/ServiceUnit/restartCount
         */
        void addRestartCount(SAFplus::MgtHistoryStat<int> *restartCountValue);
        ~ServiceUnit();

    };
}
/* namespace ::SAFplusAmf */
#endif /* SERVICEUNIT_HXX_ */
