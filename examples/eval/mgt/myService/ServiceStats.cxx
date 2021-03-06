/* 
 * File ServiceStats.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#include "MgtFactory.hxx"
#include "clMgtContainer.hxx"
#include "myServiceCommon.hxx"
#include "clMgtHistoryStat.hxx"
#include <vector>
#include "ServiceStats.hxx"


namespace myService
  {

    /* Apply MGT object factory */
    MGT_REGISTER_IMPL(ServiceStats, /myService/serviceStats)

    ServiceStats::ServiceStats(): SAFplus::MgtContainer("serviceStats")
    {
        this->addChildObject(&accessCounts, "accessCounts");
        accessCounts.config = false;
        this->addChildObject(&bytesTransmitted, "bytesTransmitted");
        bytesTransmitted.config = false;
    };

    std::vector<std::string>* ServiceStats::getChildNames()
    {
        std::string childNames[] = { "accessCounts", "bytesTransmitted" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    /*
     * XPATH: /myService/serviceStats/accessCounts
     */
    SAFplus::MgtHistoryStat<int>* ServiceStats::getAccessCounts()
    {
        return dynamic_cast<SAFplus::MgtHistoryStat<int>*>(this->getChildObject("accessCounts"));
    };

    /*
     * XPATH: /myService/serviceStats/accessCounts
     */
    void ServiceStats::addAccessCounts(SAFplus::MgtHistoryStat<int> *accessCountsValue)
    {
        this->addChildObject(accessCountsValue, "accessCounts");
    };

    /*
     * XPATH: /myService/serviceStats/bytesTransmitted
     */
    SAFplus::MgtHistoryStat<int>* ServiceStats::getBytesTransmitted()
    {
        return dynamic_cast<SAFplus::MgtHistoryStat<int>*>(this->getChildObject("bytesTransmitted"));
    };

    /*
     * XPATH: /myService/serviceStats/bytesTransmitted
     */
    void ServiceStats::addBytesTransmitted(SAFplus::MgtHistoryStat<int> *bytesTransmittedValue)
    {
        this->addChildObject(bytesTransmittedValue, "bytesTransmitted");
    };

    ServiceStats::~ServiceStats()
    {
    };

}
/* namespace ::myService */
