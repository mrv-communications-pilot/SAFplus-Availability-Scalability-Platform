/* 
 * File Sensor.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "SAFplusTypesCommon.hxx"

#include "Val.hxx"
#include <vector>
#include <string>
#include "clMgtContainer.hxx"
#include "clMgtProv.hxx"
#include "Val.hxx"
#include "Sensor.hxx"


namespace SAFplusTypes
  {

    Sensor::Sensor(): SAFplus::MgtContainer("sensor"), name("name"), desc("desc")
    {
        this->addChildObject(&name, "name");
        this->addChildObject(&desc, "desc");
    };

    void Sensor::toString(std::stringstream &xmlString)
    {
        /* TODO:  */
    };

    std::vector<std::string>* Sensor::getChildNames()
    {
        std::string childNames[] = { "name", "desc", "val" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    /*
     * XPATH: /SAFplusTypes/sensor/name
     */
    std::string Sensor::getName()
    {
        return this->name.value;
    };

    /*
     * XPATH: /SAFplusTypes/sensor/name
     */
    void Sensor::setName(std::string nameValue)
    {
        this->name.value = nameValue;
    };

    /*
     * XPATH: /SAFplusTypes/sensor/desc
     */
    std::string Sensor::getDesc()
    {
        return this->desc.value;
    };

    /*
     * XPATH: /SAFplusTypes/sensor/desc
     */
    void Sensor::setDesc(std::string descValue)
    {
        this->desc.value = descValue;
    };

    /*
     * XPATH: /SAFplusTypes/sensor/val
     */
    SAFplusTypes::Val* Sensor::getVal()
    {
        return dynamic_cast<Val*>(this->getChildObject("val"));
    };

    /*
     * XPATH: /SAFplusTypes/sensor/val
     */
    void Sensor::addVal(SAFplusTypes::Val *valValue)
    {
        this->addChildObject(valValue, "val");
    };

    Sensor::~Sensor()
    {
    };

}
/* namespace SAFplusTypes */
