/* 
 * File Component.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#ifndef COMPONENT_HXX_
#define COMPONENT_HXX_

#include "RestartCount.hxx"
#include <string>
#include "Timeouts.hxx"
#include "StandbyAssignments.hxx"
#include "Instantiate.hxx"
#include "RestartCount.hxx"
#include "Terminate.hxx"
#include "Cleanup.hxx"
#include "MgtFactory.hxx"
#include "ActiveAssignments.hxx"
#include "Cleanup.hxx"
#include "ReadinessState.hxx"
#include "Timeouts.hxx"
#include "clMgtObject.hxx"
#include "Instantiate.hxx"
#include "clMgtProv.hxx"
#include "StandbyAssignments.hxx"
#include "HighAvailabilityReadinessState.hxx"
#include <vector>
#include "ActiveAssignments.hxx"
#include "HighAvailabilityState.hxx"
#include "PresenceState.hxx"
#include "Terminate.hxx"
#include "clMgtProvList.hxx"

namespace SAFplusAmf {

    enum CapabilityModelOption { x_active_and_y_standby, x_active_or_y_standby, one_active_or_y_standby, one_active_or_one_standby, x_active, one_active, nonPreInstantiable };
    enum RecoveryOption { NoRecommendation, Restart, Failover, NodeSwitchover, NodeFailover, NodeFailfast, ClusterReset, ApplicationRestart, ContainerRestart };

    class Component : public ClMgtObject {

        /* Apply MGT object factory */
        REGISTER(Component);

    public:

        /*
         * Unique name of this entity
         */
        ClMgtProv<std::string> name;

        /*
         * Each SAFplus AMF entity gets a unique numerical identifier
         */
        ClMgtProv<unsigned short int> id;
        ClMgtProv<SAFplusAmf::PresenceState> presence;

        /*
         * This is defined by the SA-Forum AMF specificaion but is read-only because it is an emergent property based on values in saAmfCompNumMaxActiveCSIs and saAmfCompNumMaxStandbyCSIs.
         */
        ClMgtProv<int> capabilityModel;

        /*
         * Maximum number of active work assignments this component can handle.
         */
        ClMgtProv<unsigned int> maxActiveAssignments;

        /*
         * Maximum number of standby work assignments this component can handle.
         */
        ClMgtProv<unsigned int> maxStandbyAssignments;

        /*
         * Currently assigned work.
         */
        ClMgtProvList<std::string> assignedWork;

        /*
         * True is enabled, False is disabled.  To move from False to True a 'repair' action must occur.
         */
        ClMgtProv<bool> operState;
        ClMgtProv<SAFplusAmf::ReadinessState> readinessState;

        /*
         * This state field covers ALL work assignments...
         */
        ClMgtProv<SAFplusAmf::HighAvailabilityReadinessState> haReadinessState;
        ClMgtProv<SAFplusAmf::HighAvailabilityState> haState;

        /*
         * Compatible SA-Forum API version
         */
        ClMgtProv<std::string> safVersion;
        ClMgtProv<unsigned int> compCategory;

        /*
         * What software installation bundle does this component come from
         */
        ClMgtProv<std::string> swBundle;

        /*
         * List of environment variables in the form '<VARIABLE>=<VALUE>' the form the environment in which this component should be started
         */
        ClMgtProvList<std::string> commandEnvironment;

        /*
         * How many times to attempt to instantiate this entity without delay.  If the number of instantiation attempts exceeds both this and the max delayed instantiations field, the fault will be elevated to the Service Unit level.
         */
        ClMgtProv<unsigned int> maxInstantInstantiations;

        /*
         * How many times to attempt to instantiate this entity after an initial delay.  If the number of instantiation attempts exceeds both this and the max instant instantiations field, the fault will be elevated to the Service Unit level.
         */
        ClMgtProv<unsigned int> maxDelayedInstantiations;

        /*
         * How long to delay between instantiation attempts
         */
        ClMgtProv<unsigned int> delayBetweenInstantiation;
        ClMgtProv<int> recovery;

        /*
         * Set to true if this component can be restarted on failure, without this event registering as a fault
         */
        ClMgtProv<bool> restartable;

        /*
         * The component listed here is this component's proxy.
         */
        ClMgtProv<std::string> proxy;

        /*
         * This component is the proxy for the components listed here.
         */
        ClMgtProvList<std::string> proxied;

    public:
         Component();
         Component(std::string nameValue);
        std::vector<std::string> getKeys();
        std::vector<std::string>* getChildNames();

        /*
         * XPATH: /SAFplusAmf/Component/name
         */
        std::string getName();

        /*
         * XPATH: /SAFplusAmf/Component/name
         */
        void setName(std::string nameValue);

        /*
         * XPATH: /SAFplusAmf/Component/id
         */
        unsigned short int getId();

        /*
         * XPATH: /SAFplusAmf/Component/id
         */
        void setId(unsigned short int idValue);

        /*
         * XPATH: /SAFplusAmf/Component/presence
         */
        SAFplusAmf::PresenceState getPresence();

        /*
         * XPATH: /SAFplusAmf/Component/presence
         */
        void setPresence(SAFplusAmf::PresenceState presenceValue);

        /*
         * XPATH: /SAFplusAmf/Component/capabilityModel
         */
        CapabilityModelOption getCapabilityModel();

        /*
         * XPATH: /SAFplusAmf/Component/capabilityModel
         */
        void setCapabilityModel(CapabilityModelOption capabilityModelValue);

        /*
         * XPATH: /SAFplusAmf/Component/maxActiveAssignments
         */
        unsigned int getMaxActiveAssignments();

        /*
         * XPATH: /SAFplusAmf/Component/maxActiveAssignments
         */
        void setMaxActiveAssignments(unsigned int maxActiveAssignmentsValue);

        /*
         * XPATH: /SAFplusAmf/Component/maxStandbyAssignments
         */
        unsigned int getMaxStandbyAssignments();

        /*
         * XPATH: /SAFplusAmf/Component/maxStandbyAssignments
         */
        void setMaxStandbyAssignments(unsigned int maxStandbyAssignmentsValue);

        /*
         * XPATH: /SAFplusAmf/Component/assignedWork
         */
        std::vector<std::string> getAssignedWork();

        /*
         * XPATH: /SAFplusAmf/Component/assignedWork
         */
        void setAssignedWork(std::string assignedWorkValue);

        /*
         * XPATH: /SAFplusAmf/Component/operState
         */
        bool getOperState();

        /*
         * XPATH: /SAFplusAmf/Component/operState
         */
        void setOperState(bool operStateValue);

        /*
         * XPATH: /SAFplusAmf/Component/readinessState
         */
        SAFplusAmf::ReadinessState getReadinessState();

        /*
         * XPATH: /SAFplusAmf/Component/readinessState
         */
        void setReadinessState(SAFplusAmf::ReadinessState readinessStateValue);

        /*
         * XPATH: /SAFplusAmf/Component/haReadinessState
         */
        SAFplusAmf::HighAvailabilityReadinessState getHaReadinessState();

        /*
         * XPATH: /SAFplusAmf/Component/haReadinessState
         */
        void setHaReadinessState(SAFplusAmf::HighAvailabilityReadinessState haReadinessStateValue);

        /*
         * XPATH: /SAFplusAmf/Component/haState
         */
        SAFplusAmf::HighAvailabilityState getHaState();

        /*
         * XPATH: /SAFplusAmf/Component/haState
         */
        void setHaState(SAFplusAmf::HighAvailabilityState haStateValue);

        /*
         * XPATH: /SAFplusAmf/Component/safVersion
         */
        std::string getSafVersion();

        /*
         * XPATH: /SAFplusAmf/Component/safVersion
         */
        void setSafVersion(std::string safVersionValue);

        /*
         * XPATH: /SAFplusAmf/Component/compCategory
         */
        unsigned int getCompCategory();

        /*
         * XPATH: /SAFplusAmf/Component/compCategory
         */
        void setCompCategory(unsigned int compCategoryValue);

        /*
         * XPATH: /SAFplusAmf/Component/swBundle
         */
        std::string getSwBundle();

        /*
         * XPATH: /SAFplusAmf/Component/swBundle
         */
        void setSwBundle(std::string swBundleValue);

        /*
         * XPATH: /SAFplusAmf/Component/commandEnvironment
         */
        std::vector<std::string> getCommandEnvironment();

        /*
         * XPATH: /SAFplusAmf/Component/commandEnvironment
         */
        void setCommandEnvironment(std::string commandEnvironmentValue);

        /*
         * XPATH: /SAFplusAmf/Component/maxInstantInstantiations
         */
        unsigned int getMaxInstantInstantiations();

        /*
         * XPATH: /SAFplusAmf/Component/maxInstantInstantiations
         */
        void setMaxInstantInstantiations(unsigned int maxInstantInstantiationsValue);

        /*
         * XPATH: /SAFplusAmf/Component/maxDelayedInstantiations
         */
        unsigned int getMaxDelayedInstantiations();

        /*
         * XPATH: /SAFplusAmf/Component/maxDelayedInstantiations
         */
        void setMaxDelayedInstantiations(unsigned int maxDelayedInstantiationsValue);

        /*
         * XPATH: /SAFplusAmf/Component/delayBetweenInstantiation
         */
        unsigned int getDelayBetweenInstantiation();

        /*
         * XPATH: /SAFplusAmf/Component/delayBetweenInstantiation
         */
        void setDelayBetweenInstantiation(unsigned int delayBetweenInstantiationValue);

        /*
         * XPATH: /SAFplusAmf/Component/recovery
         */
        RecoveryOption getRecovery();

        /*
         * XPATH: /SAFplusAmf/Component/recovery
         */
        void setRecovery(RecoveryOption recoveryValue);

        /*
         * XPATH: /SAFplusAmf/Component/restartable
         */
        bool getRestartable();

        /*
         * XPATH: /SAFplusAmf/Component/restartable
         */
        void setRestartable(bool restartableValue);

        /*
         * XPATH: /SAFplusAmf/Component/proxy
         */
        std::string getProxy();

        /*
         * XPATH: /SAFplusAmf/Component/proxy
         */
        void setProxy(std::string proxyValue);

        /*
         * XPATH: /SAFplusAmf/Component/proxied
         */
        std::vector<std::string> getProxied();

        /*
         * XPATH: /SAFplusAmf/Component/proxied
         */
        void setProxied(std::string proxiedValue);

        /*
         * XPATH: /SAFplusAmf/Component/activeAssignments
         */
        SAFplusAmf::ActiveAssignments* getActiveAssignments();

        /*
         * XPATH: /SAFplusAmf/Component/activeAssignments
         */
        void addActiveAssignments(SAFplusAmf::ActiveAssignments *activeAssignmentsValue);

        /*
         * XPATH: /SAFplusAmf/Component/standbyAssignments
         */
        SAFplusAmf::StandbyAssignments* getStandbyAssignments();

        /*
         * XPATH: /SAFplusAmf/Component/standbyAssignments
         */
        void addStandbyAssignments(SAFplusAmf::StandbyAssignments *standbyAssignmentsValue);

        /*
         * XPATH: /SAFplusAmf/Component/instantiate
         */
        SAFplusAmf::Instantiate* getInstantiate();

        /*
         * XPATH: /SAFplusAmf/Component/instantiate
         */
        void addInstantiate(SAFplusAmf::Instantiate *instantiateValue);

        /*
         * XPATH: /SAFplusAmf/Component/terminate
         */
        SAFplusAmf::Terminate* getTerminate();

        /*
         * XPATH: /SAFplusAmf/Component/terminate
         */
        void addTerminate(SAFplusAmf::Terminate *terminateValue);

        /*
         * XPATH: /SAFplusAmf/Component/cleanup
         */
        SAFplusAmf::Cleanup* getCleanup();

        /*
         * XPATH: /SAFplusAmf/Component/cleanup
         */
        void addCleanup(SAFplusAmf::Cleanup *cleanupValue);

        /*
         * XPATH: /SAFplusAmf/Component/timeouts
         */
        SAFplusAmf::Timeouts* getTimeouts();

        /*
         * XPATH: /SAFplusAmf/Component/timeouts
         */
        void addTimeouts(SAFplusAmf::Timeouts *timeoutsValue);

        /*
         * XPATH: /SAFplusAmf/Component/restartCount
         */
        SAFplusAmf::RestartCount* getRestartCount();

        /*
         * XPATH: /SAFplusAmf/Component/restartCount
         */
        void addRestartCount(SAFplusAmf::RestartCount *restartCountValue);
         ~Component();

    };
}
/* namespace SAFplusAmf */
#endif /* COMPONENT_HXX_ */
