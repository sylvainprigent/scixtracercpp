/// \file SxRequest.h
/// \brief SxRequest class
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

/// \class SxRequest
/// \brief Abstract class that define the metadata request interface
class SCIXTRACER_EXPORT SxRequest{

public:
    /// \brief Constructor
    SxRequest();
    /// \brief Destructor
    virtual ~SxRequest();

public:
    /// \brief Read a raw data metadata from the database
    /// \param[in] md_uri URI of the data
    /// \return a RawDataContainer that stores the raw data metadata
    virtual SxRawData* read_rawdata(const QString& md_uri) = 0;
    /// \brief Write a raw data metadata to the database
    /// \param[in] container Object that contains the raw data metadata to write
    /// \param[in] md_uri URI of the data
    virtual void write_rawdata(SxRawData* container, const QString& md_uri) = 0;
    /// \brief Read a processed data metadata from the database
    /// \param[in] URI of the data
    /// \return ProcessedDataContainer: object that contains the read processed data metadata
    virtual SxProcessedData* read_processeddata(const QString& md_uri) = 0;
    /// \brief Write a processed data metadata to the database
    /// \param[in] container Object that contains the processed data metadata to write
    /// \param[in] md_uri URI of the data
    virtual void write_processeddata(SxProcessedData* container, const QString& md_uri) = 0;
    /// \brief Read a raw dataset metadata from the database
    /// \param[in] md_uri URI of the dataset
    /// \return Object that contains the read dataset metadata
    virtual SxDataset* read_rawdataset(const QString& md_uri) = 0;
    /// \brief Write a raw dataset metadata to the database
    /// \param[in] container object that contains the raw dataset metadata to write
    /// \param[in] md_uri URI of the dataset
    virtual void write_rawdataset(SxDataset* container, const QString& md_uri) = 0;
    /// \brief Read a processed dataset metadata from the database
    /// \param[in] md_uri URI of the dataset
    /// \return Object that contains the read dataset metadata
    virtual SxDataset* read_processeddataset(const QString& md_uri) = 0;
    /// \brief Write a processed dataset metadata to the database
    /// \param[in] container Object that contains the processed dataset metadata to write
    /// \param[in] md_uri URI of the dataset
    virtual void write_processeddataset(SxDataset* container, const QString& md_uri) = 0;
    /// \brief Add a run to a processed dataset
    /// \param[in] run Container of the Run metadata
    /// \param[in] dataset_md_uri URI of the ProcessedDataset
    /// \return URI of the run metadata info
    virtual QString add_run_processeddataset(SxRun* run, const QString& dataset_md_uri) = 0;
    /// \brief Create a new processed dataset
    /// \param[in] name Name of the processed dataset
    /// \param[in] experiment_md_uri URI of the experiment that contains the dataset
    /// \return Reference to the newly created dataset
    virtual SxDataset *create_processed_dataset(const QString& name, const QString& experiment_md_uri) = 0;
    /// \brief Create a new data metadata in the dataset
    ///  The input data object must contain only the metadata (ie no uri and no md_uri).
    ///  This method generate the uri and the md_uri and save all the metadata
    /// \param[in] container Metadata of the processed data to create
    /// \param[in] md_uri URI of the processed dataset
    virtual void create_data_processeddataset(SxProcessedData* container, const QString& md_uri) = 0;
    /// \brief Read an experiment metadata
    /// \param[in] md_uri URI of the experiment in the database
    /// \return object that contains an experiment metadata
    virtual SxExperiment* read_experiment(const QString& md_uri) = 0;
    /// \brief Write an experiment metadata to the database
    /// \param[in] container Object that contains an experiment metadata
    /// \param[in] md_uri URI of the experiment in the database
    virtual void write_experiment(SxExperiment* container, const QString& md_uri) = 0;
    /// \brief Create a new experiment metadata to the database
    /// \param[in] container Object that contains an experiment metadata
    /// \param[in] uri URI of the experiment in the database
    virtual void create_experiment(SxExperiment* container, const QString& uri) = 0;
    /// \brief Import a data to a raw dataset
    /// \param[in] data_path local path of the data to import
    /// \param[in] rawdataset_uri URI of the raw dataset where the data will be imported
    /// \param[in] metadata Metadata of the data to import
    /// \param[in] copy True if the data is copied to the Experiment database, false otherwise
    virtual void import_data(const QString& data_path, const QString& rawdataset_uri, SxRawData* metadata, bool copy) = 0;
    /// \brief Read a run metadata from the data base
    /// \param[in] md_uri URI of the run entry in the database
    /// \return Object containing the run metadata
    virtual SxRun* read_run(const QString& md_uri) = 0;
    /// \brief Write a run metadata to the data base
    /// \param[in] container Object containing the run metadata
    /// \param[in] md_uri URI of the run entry in the database
    virtual void write_run(SxRun* container, const QString& md_uri) = 0;
    /// \brief Query files in a repository
    /// \param[in] repository_uri URI of the repository
    /// \param[in] filter_ Regular expression to select a subset of file base on their names
    /// \return The list of selected files
    virtual QStringList query_rep(const QString& repository_uri, const QString& filter_) = 0;
    /// \brief Create the URI of an run output data file
    /// \param[in] output_rep_uri Output directory of the run
    /// \param[in] output_name Output filename
    /// \param[in] format_ Output file format
    /// \param[in] corresponding_input_uri URI of the origin input data
    /// \return The created URI
    virtual QString create_output_uri(const QString& output_rep_uri, const QString& output_name, const QString& format_, const QString& corresponding_input_uri) = 0;

};
