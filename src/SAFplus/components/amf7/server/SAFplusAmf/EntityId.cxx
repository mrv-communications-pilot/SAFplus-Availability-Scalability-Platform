/* 
 * File EntityId.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "SAFplusAmfCommon.hxx"

#include <vector>
#include <string>
#include "clMgtContainer.hxx"
#include "clMgtProv.hxx"
#include "EntityId.hxx"


namespace SAFplusAmf
  {

    EntityId::EntityId(): SAFplus::MgtContainer("EntityId"), myName("myName"), id("id")
    {
        this->addChildObject(&myName, "myName");
        this->addChildObject(&id, "id");
    };

    void EntityId::toString(std::stringstream &xmlString)
    {
        /* TODO:  */
    };

    std::vector<std::string>* EntityId::getChildNames()
    {
        std::string childNames[] = { "myName", "id" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    /*
     * XPATH: /SAFplusAmf/EntityId/myName
     */
    std::string EntityId::getMyName()
    {
        return this->myName.value;
    };

    /*
     * XPATH: /SAFplusAmf/EntityId/myName
     */
    void EntityId::setMyName(std::string myNameValue)
    {
        this->myName.value = myNameValue;
    };

    /*
     * XPATH: /SAFplusAmf/EntityId/id
     */
    unsigned short int EntityId::getId()
    {
        return this->id.value;
    };

    /*
     * XPATH: /SAFplusAmf/EntityId/id
     */
    void EntityId::setId(unsigned short int idValue)
    {
        this->id.value = idValue;
    };

    EntityId::~EntityId()
    {
    };

}
/* namespace SAFplusAmf */
