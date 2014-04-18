/* 
 * File ComponentRestart.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#ifndef COMPONENTRESTART_HXX_
#define COMPONENTRESTART_HXX_

#include "clMgtObject.hxx"
#include "clMgtProv.hxx"
#include "SaTimeT.hxx"
#include <vector>
#include "MgtFactory.hxx"

namespace SAFplusAmf {

    class ComponentRestart : public ClMgtObject {

        /* Apply MGT object factory */
        REGISTER(ComponentRestart);

    public:

        /*
         * The maximum number of events that can occur within that time period before escalation occurs.
         */
        ClMgtProv<unsigned long int> maximum;

        /*
         * The time period (in milliseconds) involved.
         */
        ClMgtProv<SAFplusTypes::SaTimeT> duration;

    public:
         ComponentRestart();
        std::vector<std::string>* getChildNames();

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/ComponentRestart/maximum
         */
        unsigned long int getMaximum();

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/ComponentRestart/maximum
         */
        void setMaximum(unsigned long int maximumValue);

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/ComponentRestart/duration
         */
        SAFplusTypes::SaTimeT getDuration();

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/ComponentRestart/duration
         */
        void setDuration(SAFplusTypes::SaTimeT durationValue);
         ~ComponentRestart();

    };
}
/* namespace SAFplusAmf */
#endif /* COMPONENTRESTART_HXX_ */
