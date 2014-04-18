/* 
 * File EntityByName.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#ifndef ENTITYBYNAME_HXX_
#define ENTITYBYNAME_HXX_

#include "clMgtObject.hxx"
#include "clMgtProv.hxx"
#include <vector>
#include "MgtFactory.hxx"
#include <string>

namespace SAFplusAmf {

    class EntityByName : public ClMgtObject {

        /* Apply MGT object factory */
        REGISTER(EntityByName);

    public:
        ClMgtProv<std::string> name;
        ClMgtProv<std::string> entity;

    public:
         EntityByName();
        std::vector<std::string>* getChildNames();

        /*
         * XPATH: /SAFplusAmf/EntityByName/name
         */
        std::string getName();

        /*
         * XPATH: /SAFplusAmf/EntityByName/name
         */
        void setName(std::string nameValue);

        /*
         * XPATH: /SAFplusAmf/EntityByName/entity
         */
        std::string getEntity();

        /*
         * XPATH: /SAFplusAmf/EntityByName/entity
         */
        void setEntity(std::string entityValue);
         ~EntityByName();

    };
}
/* namespace SAFplusAmf */
#endif /* ENTITYBYNAME_HXX_ */
