/* 
 * File StreamScope.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "SAFplusLogCommon.hxx"

#include "MgtEnumType.hxx"
#include <iostream>
#include "StreamScope.hxx"


namespace SAFplusLog
  {

    /*
     * Provide an implementation of the en2str_vec lookup table.
     */
    const StreamScopeManager::vec_t StreamScopeManager::en2str_vec = {
            pair_t(StreamScope::GLOBAL, "GLOBAL"),
            pair_t(StreamScope::LOCAL, "LOCAL")
    }; // uses c++11 initializer lists 

    std::ostream& operator<<(std::ostream &os, const SAFplusLog::StreamScope &streamScope)
    {
        return os << StreamScopeManager::toString(streamScope);
    };

    std::istream& operator>>(std::istream &is, SAFplusLog::StreamScope &streamScope)
    {
        std::string buf;
        is >> buf;
        streamScope = StreamScopeManager::toEnum(buf);
        return is;
    };

}
/* namespace SAFplusLog */
