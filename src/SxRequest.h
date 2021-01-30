/// \file SxRequest.h
/// \brief SxRequest class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include <QString>
#include "scixtracerExport.h"

/// \class SxRequest
/// \brief Abstract class that define the metadata request interface
class SCIXTRACER_EXPORT SxRequest{

public:
    SxRequest();
    virtual ~SxRequest();

public:
    //virtual SxExperiment* get_experiment(QString uri) = 0;
};
