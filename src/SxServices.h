/// \file SxServices.h
/// \brief SxServices class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include <QString>
#include "scixtracerExport.h"

#include "SxSettings.h"
#include "SxRequest.h"

/// \class SxServices
/// \brief Main class to serve services to the API
class SCIXTRACER_EXPORT SxServices{

private:
    static SxSettings *m_settings; ///< Unique instance of the settings service
    static SxRequest *m_request; ///< Unique instance of the serializer service

public:
    /// \brief Constructor
    /// \param[in] serializer Name of the serializer
    SxServices();
    ~SxServices();

public:
    static SxSettings* settings();
    static SxRequest* request();

private:
    void set_settings_file(QString filename);
    void set_request_engine(QString engine_name);
};
