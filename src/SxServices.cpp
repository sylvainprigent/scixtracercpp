/// \file SxServices.cpp
/// \brief SxServices class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include "SxServices.h"
#include "SxException.h"

#include <QFile>

SxServices::SxServices()
{

}

SxServices::~SxServices()
{
    if (m_settings){
        delete m_settings;
    }
    if (m_request){
        delete m_request;
    }
}

SxSettings* SxServices::settings()
{
    if (m_settings){
        return m_settings;
    }
    else{
        throw SxException("SxServices: settings not initilized. Please use the 'set_settings_file(filename) method'");
    }
}

SxRequest* SxServices::request()
{
    if (m_request){
        return m_request;
    }
    else{
        throw SxException("SxServices: request engine not initilized. Please use the 'set_request_engine(name) method'");
    }
}

void SxServices::set_settings_file(QString filename)
{
    if (QFile::exists(filename)){
        m_settings = new SxSettings(filename);
    }
    else{
        throw SxException(("Cannot find the settings file " + filename.toStdString()).c_str());
    }
}

void SxServices::set_request_engine(QString engine_name)
{
    if (engine_name == "local"){
       // m_request = new SxRequestLocal();
    }
    else{
        throw SxException(("Cannot find the request engine " + engine_name.toStdString()).c_str());
    }
}
