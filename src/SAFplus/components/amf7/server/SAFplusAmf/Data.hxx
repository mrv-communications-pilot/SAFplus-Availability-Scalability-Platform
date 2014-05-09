/* 
 * File Data.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef DATA_HXX_
#define DATA_HXX_
#include "SAFplusAmfCommon.hxx"

#include <string>
#include "clMgtProv.hxx"
#include "clMgtList.hxx"
#include <vector>
#include "MgtFactory.hxx"

namespace SAFplusAmf
  {

    class Data : public SAFplus::MgtList {

        /* Apply MGT object factory */
        MGT_REGISTER(Data);

    public:
        SAFplus::MgtProv<std::string> myName;
        SAFplus::MgtProv<std::string> val;

    public:
        Data();
        Data(std::string myNameValue);
        void toString(std::stringstream &xmlString);
        std::vector<std::string> getKeys();
        std::vector<std::string>* getChildNames();

        /*
         * XPATH: /SAFplusAmf/ComponentServiceInstance/data/myName
         */
        std::string getMyName();

        /*
         * XPATH: /SAFplusAmf/ComponentServiceInstance/data/myName
         */
        void setMyName(std::string myNameValue);

        /*
         * XPATH: /SAFplusAmf/ComponentServiceInstance/data/val
         */
        std::string getVal();

        /*
         * XPATH: /SAFplusAmf/ComponentServiceInstance/data/val
         */
        void setVal(std::string valValue);
        ~Data();

    };
}
/* namespace SAFplusAmf */
#endif /* DATA_HXX_ */
