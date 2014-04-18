/* 
 * File Application.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#include "NumServiceGroups.hxx"
#include "clMgtObject.hxx"
#include "clMgtProv.hxx"
#include <vector>
#include "MgtFactory.hxx"
#include "NumServiceGroups.hxx"
#include "AdministrativeState.hxx"
#include <string>
#include "Application.hxx"


namespace SAFplusAmf {

    /* Apply MGT object factory */
    REGISTERIMPL(Application, /SAFplusAmf/Application)

     Application::Application(): ClMgtObject("Application"), name("name"), id("id"), adminState("adminState") {
        this->addChildObject(&name, "name");
        this->addChildObject(&id, "id");
        this->addChildObject(&adminState, "adminState");
        this->addKey("name");
    };

     Application::Application(std::string nameValue): ClMgtObject("Application"), name("name"), id("id"), adminState("adminState") {
        this->name.Value =  nameValue;
        this->addKey("name");
        this->addChildObject(&name, "name");
        this->addChildObject(&id, "id");
        this->addChildObject(&adminState, "adminState");
    };

    std::vector<std::string> Application::getKeys() {
        std::string keyNames[] = { "name" };
        return std::vector<std::string> (keyNames, keyNames + sizeof(keyNames) / sizeof(keyNames[0]));
    };

    std::vector<std::string>* Application::getChildNames() {
        std::string childNames[] = { "name", "id", "adminState", "NumServiceGroups" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    /*
     * XPATH: /SAFplusAmf/Application/name
     */
    std::string Application::getName() {
        return this->name.Value;
    };

    /*
     * XPATH: /SAFplusAmf/Application/name
     */
    void Application::setName(std::string nameValue) {
        this->name.Value = nameValue;
    };

    /*
     * XPATH: /SAFplusAmf/Application/id
     */
    unsigned short int Application::getId() {
        return this->id.Value;
    };

    /*
     * XPATH: /SAFplusAmf/Application/id
     */
    void Application::setId(unsigned short int idValue) {
        this->id.Value = idValue;
    };

    /*
     * XPATH: /SAFplusAmf/Application/adminState
     */
    SAFplusAmf::AdministrativeState Application::getAdminState() {
        return this->adminState.Value;
    };

    /*
     * XPATH: /SAFplusAmf/Application/adminState
     */
    void Application::setAdminState(SAFplusAmf::AdministrativeState adminStateValue) {
        this->adminState.Value = adminStateValue;
    };

    /*
     * XPATH: /SAFplusAmf/Application/NumServiceGroups
     */
    SAFplusAmf::NumServiceGroups* Application::getNumServiceGroups() {
        return (NumServiceGroups*)this->getChildObject("NumServiceGroups");
    };

    /*
     * XPATH: /SAFplusAmf/Application/NumServiceGroups
     */
    void Application::addNumServiceGroups(SAFplusAmf::NumServiceGroups *NumServiceGroupsValue) {
        this->addChildObject(NumServiceGroupsValue, "NumServiceGroups");
    };

     Application::~Application() {
    };

}
/* namespace SAFplusAmf */
