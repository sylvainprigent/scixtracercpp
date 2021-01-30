/// \file SxServices.cpp
/// \brief SxServices class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include "SxServices.h"
#include "SxException.h"

SxServices::SxServices()
{

}

SxServices::~SxServices()
{
    if (m_serializer){
        delete m_serializer;
    }
    if (m_request){
        delete m_request;
    }
}

SxSerialize* SxServices::serializer()
{
    if (m_serializer){
        return m_serializer;
    }
    else{
        throw SxException("SxServices: serializer not initilized. Please use 'set_serializer(name) method'");
    }
}

SxRequest* SxServices::request()
{
    if (m_request){
        return m_request;
    }
    else{
        throw SxException("SxServices: request engine not initilized. Please use 'set_request_engine(name) method'");
    }
}

void SxServices::set_serializer(QString serializer_name)
{
    if (serializer_name == "json"){
        //m_serializer = new SxSerializerJson();
    }
    else{
        throw SxException(("Cannot find the serializer " + serializer_name.toStdString()).c_str());
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
