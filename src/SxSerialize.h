/// \file SxSerialize.h
/// \brief SxSerialize class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include <QString>
#include "scixtracerExport.h"

#include "SxRawData.h"
#include "SxProcessedData.h"
#include "SxDataset.h"
#include "SxRun.h"
#include "SxExperiment.h"

/// \class SxSerialize
/// \brief Interface for metadata container serializer
class SCIXTRACER_EXPORT SxSerialize{

public:
    /// \brief Constructor
    SxSerialize();
    /// \brief Destructor
    virtual ~SxSerialize();

public:
    /// \brief Serialize a metadata to a string
    /// \param[in] container Pointer to the container
    /// \return string that represent the container content
    QString serialize(SxMetadata* container);
    /// \brief Serialize a raw data to a string
    /// \param[in] container Pointer to the container
    /// \return string that represent the container content
    virtual QString serialize_rawdata(SxRawData* container) = 0;
    /// \brief Serialize a processed data to a string
    /// \param[in] container Pointer to the container
    /// \return string that represent the container content
    virtual QString serialize_processeddata(SxProcessedData* container) = 0;
    /// \brief Serialize a dataset to a string
    /// \param[in] container Pointer to the container
    /// \return string that represent the container content
    virtual QString serialize_dataset(SxDataset* container) = 0;
    /// \brief Serialize a run to a string
    /// \param[in] container Pointer to the container
    /// \return string that represent the container content
    virtual QString serialize_run(SxRun* container) = 0;
    /// \brief Serialize an axperiment to a string
    /// \param[in] container Pointer to the container
    /// \return string that represent the container content
    virtual QString serialize_experiment(SxExperiment* container) = 0;


};
