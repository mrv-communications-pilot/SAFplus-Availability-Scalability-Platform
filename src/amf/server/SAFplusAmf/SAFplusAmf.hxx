/* 
 * File SAFplusAmf.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef SAFPLUSAMFROOT_HXX_
#define SAFPLUSAMFROOT_HXX_
#include "SAFplusAmfCommon.hxx"

#include "clTransaction.hxx"
#include "clMgtProv.hxx"
#include "clMgtList.hxx"
#include <vector>
#include "MgtFactory.hxx"
#include "clMgtContainer.hxx"
#include "EntityByIdKey.hxx"

namespace SAFplusAmf
  {

    class SAFplusAmfRoot : public SAFplus::MgtContainer {

        /* Apply MGT object factory */
        MGT_REGISTER(SAFplusAmfRoot);

    public:

        /*
         * This attribute indicates the interval at which the corresponding healthcheck should be initiated (in milliseconds).
         */
        SAFplus::MgtProv<SaTimeT> healthCheckPeriod;

        /*
         * This attribute indicates the maximum time allowable for components to not reply to the health check (in milliseconds).  After this time passes with no response from the component, it will be faulted
         */
        SAFplus::MgtProv<SaTimeT> healthCheckMaxSilence;

        /*
         * 
         */
        SAFplus::MgtList<std::string> clusterList;

        /*
         * Represents a node.  A node is generally a physical instance of running software, such as a rack server or a blade in the chassis.  But more formally, it is a separately running instance of SAFplus which communicates to other instances via messaging.
         */
        SAFplus::MgtList<std::string> nodeList;

        /*
         * A Service Group is a Service Availability Forum defined concept that corresponds to a group of redundant processes that should fail over as a unit.
         */
        SAFplus::MgtList<std::string> serviceGroupList;

        /*
         * 
         */
        SAFplus::MgtList<std::string> componentList;

        /*
         * 
         */
        SAFplus::MgtList<std::string> componentServiceInstanceList;

        /*
         * 
         */
        SAFplus::MgtList<std::string> serviceInstanceList;

        /*
         * A Service Unit is a group of processes that all fail over together.  All service unit members must be run on the same node.
         */
        SAFplus::MgtList<std::string> serviceUnitList;

        /*
         * 
         */
        SAFplus::MgtList<std::string> applicationList;

        /*
         * Look up any entity by its string name
         */
        SAFplus::MgtList<std::string> entityByNameList;

        /*
         * Look up any entity by its identifier
         */
        SAFplus::MgtList<SAFplusAmf::EntityByIdKey> entityByIdList;

    public:
        SAFplusAmfRoot();
        std::vector<std::string>* getChildNames();

        /*
         * XPATH: /SAFplusAmf/healthCheckPeriod
         */
        SaTimeT getHealthCheckPeriod();

        /*
         * XPATH: /SAFplusAmf/healthCheckPeriod
         */
        void setHealthCheckPeriod(SaTimeT &healthCheckPeriodValue, SAFplus::Transaction &txn=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/healthCheckMaxSilence
         */
        SaTimeT getHealthCheckMaxSilence();

        /*
         * XPATH: /SAFplusAmf/healthCheckMaxSilence
         */
        void setHealthCheckMaxSilence(SaTimeT &healthCheckMaxSilenceValue, SAFplus::Transaction &txn=SAFplus::NO_TXN);
        ~SAFplusAmfRoot();

    };
}
/* namespace SAFplusAmf */
#endif /* SAFPLUSAMFROOT_HXX_ */
