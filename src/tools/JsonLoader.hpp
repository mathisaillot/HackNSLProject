#pragma once

// lib std
#include <iostream>
#include <string>
#include <sstream>
// lib extern
#ifdef __APPLE__
    #include <json/json.h>
#else
    #include <jsoncpp/json/json.h>
#endif
// lib perso
#include "Outils.hpp"

/**
 *  role :  cette class permet d'utiliser la lib jsoncpp
 *          plus facilement dans notre utilisation afin
 *          de charger les configurations 
 */
class JsonLoader {
private:
    /*****************************************
     *                 fields                *
     *****************************************/
    Json::Value m_data;
public:
    /*****************************************
     *              constr/destr             *
     *****************************************/
    // constr
    JsonLoader(const std::string & destfile);
    // destr
    virtual ~JsonLoader();
    /*****************************************
     *             getter/setter             *
     *****************************************/
    const Json::Value & getData() const { return m_data; }
};