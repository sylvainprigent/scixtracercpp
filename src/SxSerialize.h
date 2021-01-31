/// \file SxSerialize.h
/// \brief SxSerialize class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include <QString>
#include "scixtracerExport.h"

#include "SxMetadata.h"

/// \class SxSerialize
/// \brief Abstract class that define the metadata serilizer interface
class SCIXTRACER_EXPORT SxSerialize{

public:
    SxSerialize();
    virtual ~SxSerialize();

public:
    QString serialize(SxMetadata* data);
    virtual QString serialize(SxRawData* data) = 0;
    virtual QString serialize(SxProcessedData* data) = 0;
    /// \todo add all the data types
};
