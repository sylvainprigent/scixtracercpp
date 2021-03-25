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
#include "SxSearchContainer.h"

/// \class SxRequest
/// \brief Abstract class that define the metadata request interface
class SCIXTRACER_EXPORT SxRequest{

public:
    /// \brief Constructor
    SxRequest();
    /// \brief Destructor
    virtual ~SxRequest();

public:
    /// \brief Create a new experiment
    /// \param[in] name Name of the experiment
    /// \param[in] author Username of the experiment author
    /// \param[in] date Creation date of the experiment
    /// \param[in] tag_keys List of keys used for the experiment vocabulary
    /// \param[in] destination Destination where the experiment is created. It is a the path of the directory where the experiment will be created for local use case
    /// \returns Experiment container with the experiment metadata
    virtual SxExperiment* create_experiment(const QString& name, const QString &author, SxDate* date= new SxDate("now"), const QStringList& tag_keys = {}, const QString& destination=".") = 0;

    /// \brief Read an experiment from the database
    /// \param[in] uri URI of the experiment. For local use case, the URI is either the path of the experiment directory, or the path of the experiment.md.json file
    /// \return Experiment container with the experiment metadata
    virtual SxExperiment* get_experiment(const QString uri) = 0;

    /// \brief Write an experiment to the database
    /// \param[in] experiment Container of the experiment metadata
    virtual void update_experiment(SxExperiment* experiment) = 0;

    /// \brief import one data to the experiment.
    /// The data is imported to the rawdataset
    /// \param[in] experiment Container of the experiment metadata
    /// \param[in] data_path Path of the accessible data on your local computer
    /// \param[in] name Name of the data
    /// \param[in] author Person who created the data
    /// \param[in] format Format of the data (ex: tif)
    /// \param[in] date Date when the data where created
    /// \param[in] tags Tags to identify the data
    /// \param[in] copy True to copy the data to the Experiment database False otherwise
    /// \returns a RawData containing the metadata
    virtual SxRawData* import_data(SxExperiment* experiment, const QString& data_path, const QString& name, const QString& author, SxFormat* format, SxDate* date = new SxDate("now"), SxTags* tags = new SxTags(), bool copy = true) = 0;

    /// \brief Read a raw data from the database
    /// \param[in] uri URI if the rawdata
    /// \returns RawData object containing the raw data metadata
    virtual SxRawData* get_rawdata(const QString&  uri) = 0;

    /// \brief Read a raw data from the database
    /// \param[in] rawdata Container with the rawdata metadata
    virtual void update_rawdata(SxRawData* rawdata) = 0;

    /// \brief Read a processed data from the database
    /// \param[in] uri URI if the processeddata
    /// \return ProcessedData object containing the raw data metadata
    virtual SxProcessedData* get_processeddata(const QString& uri) = 0;

    /// \brief Read a processed data from the database
    /// \param[in] processeddata Container with the processeddata metadata
    virtual void update_processeddata(SxProcessedData* processeddata) = 0;

    /// \brief Read a dataset from the database using it URI
    /// \param[in] uri URI if the dataset
    /// \return Dataset object containing the dataset metadata
    virtual SxDataset* get_dataset_from_uri(const QString& uri) = 0;

    /// \brief Read a processed data from the database
    /// \param[in] dataset Container with the dataset metadata
    virtual void update_dataset(SxDataset* dataset) = 0;

    /// \brief Create a processed dataset in an experiment
    /// \param[in] experiment Object containing the experiment metadata
    /// \param[in] dataset_name Name of the dataset
    /// \return Dataset object containing the new dataset metadata
    virtual SxDataset* create_dataset(SxExperiment* experiment, const QString& dataset_name) = 0;

    /// \brief Create a new run metadata
    /// \param[in] dataset Object of the dataset metadata
    /// \param[in] run_info Object containing the metadata of the run. md_uri is ignored and created automatically by this method
    /// \return Run object with the metadata and the new created md_uri
    virtual SxRun* create_run(SxDataset* dataset, SxRun* run_info) = 0;

    /// \brief Read a run metadata from the data base
    /// \param[in] uri URI of the run entry in the database
    /// \return Run: object containing the run metadata
    virtual SxRun* get_run(const QString& uri) = 0;

    /// \brief Create a new processed data for a given dataset
    /// \param[in] dataset Object of the dataset metadata
    /// \param[in] run Metadata of the run
    /// \param[in] processed_data Object containing the new processed data. md_uri is ignored and created automatically by this method
    virtual SxProcessedData* create_data(SxDataset* dataset, SxRun* run, SxProcessedData* processed_data) = 0;



public:
    /// \brief Import data from a directory to the experiment
    /// This method import with or without copy data contained
    /// in a local folder into an experiment. Imported data are
    /// considered as RawData for the experiment
    /// \param[in] experiment Container of the experiment metadata
    /// \param[in] dir_uri URI of the directory containing the data to be imported
    /// \param[in] filter Regular expression to filter which files in the folder to import
    /// \param[in] author Name of the person who created the data
    /// \param[in] format Format of the image (ex: tif)
    /// \param[in] date Date when the data where created
    /// \param[in] copy_data True to copy the data to the experiment, false otherwise. If the data are not copied, an absolute link to dir_uri is kept in the experiment metadata. The original data directory must then not be changed for the experiment to find the data.
    void import_dir(SxExperiment* experiment, const QString& dir_uri, const QString& filter, const QString& author, SxFormat* format, SxDate* date, bool copy_data);

    /// \brief Tag an experiment raw data using raw data file names
    /// \param[in] experiment Container of the experiment metadata
    /// \param[in] tag The name (or key) of the tag to add to the data
    /// \param[in] values List of possible values (str) for the tag to find in the filename
    void tag_from_name(SxExperiment* experiment, const QString& tag, const QStringList& values);

    /// \brief Tag an experiment raw data using file name and separator
    /// \param[in] experiment Container of the experiment metadata
    /// \param[in] tag The name (or key) of the tag to add to the data
    /// \param[in] separator The character used as a separator in the filename (ex: _)
    /// \param[in] value_position Position of the value to extract with respect to the separators
    void tag_using_separator(SxExperiment* experiment, const QString& tag, const QString& separator, const qint16& value_position);

    /// \brief Get the metadata of the parent data
    /// The parent data can be a RawData or a ProcessedData
    /// depending on the process chain
    /// \param[in] processed_data Container of the processed data URI
    /// \return Parent data (RawData or ProcessedData)
    SxData* get_parent(SxProcessedData* processed_data);

    /// \brief Get the first metadata of the parent data
    /// The origin data is a RawData. It is the first data that have
    /// been seen in the raw dataset
    /// \param[in] processeddata Container of the processed data URI
    /// \return  the origin data in a RawData object
    SxRawData* get_origin(SxProcessedData* processed_data);

    /// \brief Read the raw dataset from the database
    /// \param[in] experiment Container of the experiment metadata
    /// \return Dataset object containing the dataset metadata
    SxDataset* get_rawdataset(SxExperiment* experiment);

    /// \brief Query a dataset from it name
    /// \param[in] experiment Object containing the experiment metadata
    /// \param[in] name Name of the dataset to query
    /// \return a Dataset containing the dataset metadata. None is return if the dataset is not found
    SxDataset* get_dataset(SxExperiment* experiment, const QString &name);

    /// \brief Query data from a dataset
    /// \param[in] dataset Object containing the dataset metadata
    /// \param[in] query String query with the key=value format
    /// \param[in] origin_output_name Name of the output origin (ex: -o) in the case of ProcessedDataset search
    /// \return List of selected data (list of RawData or ProcessedData objects)
    QList<SxData*> get_data(SxDataset* dataset, const QString& query="", const QString& origin_output_name="");

    /// \brief convert a RawData to SearchContainer
    /// \param[in] rawdata Object containing the rawdata
    /// \return SearchContainer object
    SxSearchContainer* _rawdata_to_search_container(SxRawData* rawdata);

    /// \brief convert a ProcessedData to SearchContainer
    /// \param[in] processeddata Object containing the processeddata
    /// \return SearchContainer object
    SxSearchContainer* _processed_data_to_search_container(SxProcessedData* processeddata);

};
