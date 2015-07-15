/* 
 * File ServiceGroup.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "unitTestCommon.hxx"

#include <string>
#include "clTransaction.hxx"
#include "clMgtProv.hxx"
#include <vector>
#include "MgtFactory.hxx"
#include "clMgtContainer.hxx"
#include "ServiceGroup.hxx"


namespace unitTest
  {

    /* Apply MGT object factory */
    MGT_REGISTER_IMPL(ServiceGroup, /unitTest/ServiceGroup)

    ServiceGroup::ServiceGroup(): SAFplus::MgtContainer("ServiceGroup"), name("name"), id("id"), data("data"), key("key")
    {
        this->addChildObject(&name, "name");
        this->addChildObject(&id, "id");
        this->addChildObject(&data, "data");
        this->addChildObject(&key, "key");
    };

    ServiceGroup::ServiceGroup(std::string nameValue): SAFplus::MgtContainer("ServiceGroup"), name("name"), id("id"), data("data"), key("key")
    {
        this->name.value =  nameValue;
        this->addChildObject(&name, "name");
        this->addChildObject(&id, "id");
        this->addChildObject(&data, "data");
        this->addChildObject(&key, "key");
    };

    std::vector<std::string> ServiceGroup::getKeys()
    {
        std::string keyNames[] = { "name" };
        return std::vector<std::string> (keyNames, keyNames + sizeof(keyNames) / sizeof(keyNames[0]));
    };

    std::vector<std::string>* ServiceGroup::getChildNames()
    {
        std::string childNames[] = { "name", "id", "data", "key" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    /*
     * XPATH: /unitTest/ServiceGroup/name
     */
    std::string ServiceGroup::getName()
    {
        return this->name.value;
    };

    /*
     * XPATH: /unitTest/ServiceGroup/name
     */
    void ServiceGroup::setName(std::string nameValue, SAFplus::Transaction &t)
    {
        if(&t == &SAFplus::NO_TXN) this->name.value = nameValue;
        else
        {
            SAFplus::SimpleTxnOperation<std::string> *opt = new SAFplus::SimpleTxnOperation<std::string>(&(name.value),nameValue);
            t.addOperation(opt);
        }
    };

    /*
     * XPATH: /unitTest/ServiceGroup/id
     */
    unsigned int ServiceGroup::getId()
    {
        return this->id.value;
    };

    /*
     * XPATH: /unitTest/ServiceGroup/id
     */
    void ServiceGroup::setId(unsigned int idValue, SAFplus::Transaction &t)
    {
        if(&t == &SAFplus::NO_TXN) this->id.value = idValue;
        else
        {
            SAFplus::SimpleTxnOperation<unsigned int> *opt = new SAFplus::SimpleTxnOperation<unsigned int>(&(id.value),idValue);
            t.addOperation(opt);
        }
    };

    /*
     * XPATH: /unitTest/ServiceGroup/data
     */
    long int ServiceGroup::getData()
    {
        return this->data.value;
    };

    /*
     * XPATH: /unitTest/ServiceGroup/data
     */
    void ServiceGroup::setData(long int dataValue, SAFplus::Transaction &t)
    {
        if(&t == &SAFplus::NO_TXN) this->data.value = dataValue;
        else
        {
            SAFplus::SimpleTxnOperation<long int> *opt = new SAFplus::SimpleTxnOperation<long int>(&(data.value),dataValue);
            t.addOperation(opt);
        }
    };

    /*
     * XPATH: /unitTest/ServiceGroup/key
     */
    unsigned int ServiceGroup::getKey()
    {
        return this->key.value;
    };

    /*
     * XPATH: /unitTest/ServiceGroup/key
     */
    void ServiceGroup::setKey(unsigned int keyValue, SAFplus::Transaction &t)
    {
        if(&t == &SAFplus::NO_TXN) this->key.value = keyValue;
        else
        {
            SAFplus::SimpleTxnOperation<unsigned int> *opt = new SAFplus::SimpleTxnOperation<unsigned int>(&(key.value),keyValue);
            t.addOperation(opt);
        }
    };

    ServiceGroup::~ServiceGroup()
    {
    };

}
/* namespace unitTest */
