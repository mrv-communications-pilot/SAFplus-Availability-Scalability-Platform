/* 
 * File Replicate.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef REPLICATE_HXX_
#define REPLICATE_HXX_
#include "SAFplusLogCommon.hxx"

#include "MgtEnumType.hxx"
#include <iostream>

namespace SAFplusLog
  {

    enum class Replicate
      {
        NONE=0, SYSTEM_CONTROLLERS=1, APPLICATIONS=2, ANY=3
      };
    std::ostream& operator<<(std::ostream& os, const Replicate& e);
    std::istream& operator>>(std::istream& is, Replicate& e);
    const char* c_str(const Replicate& e);

    /*
     * This is the class that will handle the conversion for us.
     */
    class ReplicateManager : public SAFplus::MgtEnumType<ReplicateManager, Replicate> {
        ReplicateManager();  // private to prevent instantiation
    public:
        static const map_t en2str_map;  // This is the lookup table.
    };
}
/* namespace ::SAFplusLog */
#endif /* REPLICATE_HXX_ */
