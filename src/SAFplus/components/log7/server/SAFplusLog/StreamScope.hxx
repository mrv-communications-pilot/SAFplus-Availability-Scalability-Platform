/* 
 * File StreamScope.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef STREAMSCOPE_HXX_
#define STREAMSCOPE_HXX_
#include "SAFplusLogCommon.hxx"

#include "MgtEnumType.hxx"
#include <iostream>

namespace SAFplusLog
  {

    enum class StreamScope
  {
        GLOBAL, LOCAL
      };
    std::ostream& operator<<(std::ostream& os, const StreamScope& e);
    std::istream& operator>>(std::istream& is, StreamScope& e);

    /*
     * This is the class that will handle the conversion for us.
     */
    class StreamScopeManager : public SAFplus::MgtEnumType<StreamScopeManager, StreamScope> {
        StreamScopeManager();  // private to prevent instantiation
    public:
        static const vec_t en2str_vec;  // This is the lookup table.
    };
}
/* namespace SAFplusLog */
#endif /* STREAMSCOPE_HXX_ */
