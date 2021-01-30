/// \file SxServices.h
/// \brief SxServices class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include <QString>
#include "scixtracerExport.h"

#include "SxSerialize.h"
#include "SxRequest.h"

/// \class SxServices
/// \brief Main class to serve services to the API
class SCIXTRACER_EXPORT SxServices{

private:
    static SxSerialize *m_serializer; ///< Unique instance of the serializer service
    static SxRequest *m_request; ///< Unique instance of the serializer service

public:
    /// \brief Constructor
    /// \param[in] serializer Name of the serializer
    SxServices();
    ~SxServices();

public:
    static SxSerialize* serializer();
    static SxRequest* request();

private:
    void set_serializer(QString serializer_name);
    void set_request_engine(QString engine_name);
};
