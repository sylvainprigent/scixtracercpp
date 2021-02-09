/// \file SxSerializeJson.h
/// \brief SxSerializeJson class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include "scixtracerExport.h"
#include "SxSerialize.h"

/// \class SxSerializeJson
/// \brief Serialize containers to json string
class SCIXTRACER_EXPORT SxSerializeJson : public SxSerialize{

public:
    /// \brief Constructor
    SxSerializeJson();
    /// \brief Destructor
    virtual ~SxSerializeJson();

public:
    /// \brief Serialize a raw data to a string
    /// \param[in] container Pointer to the container
    /// \return string that represent the container content
    QString serialize_rawdata(SxRawData* container);
    /// \brief Serialize a processed data to a string
    /// \param[in] container Pointer to the container
    /// \return string that represent the container content
    QString serialize_processeddata(SxProcessedData* container);
    /// \brief Serialize a dataset to a string
    /// \param[in] container Pointer to the container
    /// \return string that represent the container content
    QString serialize_dataset(SxDataset* container);
    /// \brief Serialize a run to a string
    /// \param[in] container Pointer to the container
    /// \return string that represent the container content
    QString serialize_run(SxRun* container);
    /// \brief Serialize an axperiment to a string
    /// \param[in] container Pointer to the container
    /// \return string that represent the container content
    QString serialize_experiment(SxExperiment* container);

};
