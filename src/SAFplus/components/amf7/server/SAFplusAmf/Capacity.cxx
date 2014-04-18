/* 
 * File Capacity.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#include "clMgtObject.hxx"
#include "clMgtProv.hxx"
#include <vector>
#include "MgtFactory.hxx"
#include <string>
#include "Capacity.hxx"


namespace SAFplusAmf {

    /* Apply MGT object factory */
    REGISTERIMPL(Capacity, /SAFplusAmf/Node/capacity)

     Capacity::Capacity(): ClMgtObject("capacity"), resource("resource"), value("value") {
        this->addChildObject(&resource, "resource");
        this->addChildObject(&value, "value");
        this->addKey("resource");
    };

     Capacity::Capacity(std::string resourceValue): ClMgtObject("capacity"), resource("resource"), value("value") {
        this->resource.Value =  resourceValue;
        this->addKey("resource");
        this->addChildObject(&resource, "resource");
        this->addChildObject(&value, "value");
    };

    std::vector<std::string> Capacity::getKeys() {
        std::string keyNames[] = { "resource" };
        return std::vector<std::string> (keyNames, keyNames + sizeof(keyNames) / sizeof(keyNames[0]));
    };

    std::vector<std::string>* Capacity::getChildNames() {
        std::string childNames[] = { "resource", "value" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    /*
     * XPATH: /SAFplusAmf/Node/capacity/resource
     */
    std::string Capacity::getResource() {
        return this->resource.Value;
    };

    /*
     * XPATH: /SAFplusAmf/Node/capacity/resource
     */
    void Capacity::setResource(std::string resourceValue) {
        this->resource.Value = resourceValue;
    };

    /*
     * XPATH: /SAFplusAmf/Node/capacity/value
     */
    long int Capacity::getValue() {
        return this->value.Value;
    };

    /*
     * XPATH: /SAFplusAmf/Node/capacity/value
     */
    void Capacity::setValue(long int valueValue) {
        this->value.Value = valueValue;
    };

     Capacity::~Capacity() {
    };

}
/* namespace SAFplusAmf */
