/* 
 * File NumLogs.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "SAFplusLogCommon.hxx"

#include <vector>
#include "MgtFactory.hxx"
#include "IntStatistic.hxx"
#include "NumLogs.hxx"


namespace SAFplusLog
  {

    /* Apply MGT object factory */
    MGT_REGISTER_IMPL(NumLogs, /SAFplusLog/StreamStatistics/numLogs)

    NumLogs::NumLogs()
    {
        this->name.assign("numLogs");
    };

    void NumLogs::toString(std::stringstream &xmlString)
    {
        /* TODO:  */
    };

    std::vector<std::string>* NumLogs::getChildNames()
    {
        std::string childNames[] = { "current", "history10sec", "history1min", "history10min", "history1hour", "history12hour", "history1day", "history1week", "history1month" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    NumLogs::~NumLogs()
    {
    };

}
/* namespace SAFplusLog */
