/* 
 * File StreamStatistics.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef STREAMSTATISTICS_HXX_
#define STREAMSTATISTICS_HXX_
#include "SAFplusLogCommon.hxx"

#include "NumLogs.hxx"
#include <vector>
#include "MgtFactory.hxx"
#include "NumLogs.hxx"
#include "clMgtContainer.hxx"

namespace SAFplusLog
  {

    class StreamStatistics : public SAFplus::MgtContainer {

        /* Apply MGT object factory */
        MGT_REGISTER(StreamStatistics);

    public:
        StreamStatistics();
        std::vector<std::string>* getChildNames();

        /*
         * XPATH: /SAFplusLog/StreamConfig/stream/StreamStatistics/numLogs
         */
        SAFplusLog::NumLogs* getNumLogs();

        /*
         * XPATH: /SAFplusLog/StreamConfig/stream/StreamStatistics/numLogs
         */
        void addNumLogs(SAFplusLog::NumLogs *numLogsValue);
        ~StreamStatistics();

    };
}
/* namespace SAFplusLog */
#endif /* STREAMSTATISTICS_HXX_ */