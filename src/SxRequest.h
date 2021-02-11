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
    /// \brief Get the parent data of a data
    /// \param[in] data_md_uri URI of the data to query
    /// \return a pointer to the parent data
    SxData* get_parent(const QString& data_md_uri);
    /// \brief Get the first metadata of the parent data.
    /// The origin data is a RawData. It is the first data that have
    /// been seen by scixtracer
    /// \param[in] data_md_uri URI of the data to query
    /// \return  a pointer to the origin data
    SxRawData* get_origin(const QString& data_md_uri);

    /// \brief import data to an experiment
    /// \param[in] data_path Path of the accessible data on your local computer
    /// \param[in] name Name of the data
    /// \param[in] author Person who created the data
    /// \param[in] format_ Format of the data (ex: tif)
    /// \param[in] date Date when the data where created
    /// \param[in] tags List of tags to identify the data
    /// \param[in] copy  True to copy the data to the Experiment database, false otherwise
    /// \return a pointer to the created metadata
    SxRawData* import_data_experiment(SxExperiment* experiment, const QString& data_path, const QString& name,
                                      SxUser* author, SxFormat* format, SxDate *date,
                                      SxTags* tags, bool copy);

    /// \brief Import data from a directory to the experiment
    /// This method import with or without copy data contained
    /// in a local folder into an experiment. Imported data are
    /// considered as RawData for the experiment
    /// \param[in] experiment Experiment container
    /// \param[in] dir_uri URI of the directory containing the data to be imported
    /// \param[in] filter_ Regular expression to filter which files in the folder to import
    /// \param[in] author Name of the person who created the data
    /// \param[in] format_ Format of the image (ex: tif)
    /// \param[in] date Date when the data where created
    /// \param[in] copy True to copy the data to the experiment, false otherwise.
    /// If the data are not copied, an absolute link to dir_uri is kept in the
    /// experiment metadata. The original data directory must then not be
    /// changed for the experiment to find the data.
    void import_dir_experiment(SxExperiment* experiment, const QString& dir_uri,
                               const QString& filter_, SxUser* author,
                               SxFormat* format, SxDate *date, bool copy);
    /// \brief Tag an experiment raw data using file name
    /// \param[in] experiment Pointer to the experiment
    /// \param[in] tag The name (or key) of the tag to add to the data
    /// \param[in] values List of possible values for the tag to find in the filename
    void tag_from_name(SxExperiment* experiment, const QString& tag, const QStringList& values);
    /// \brief Tag an experiment raw data using file name and separator
    /// \param[in] experiment Pointer to the experiment
    /// \param[in] tag The name (or key) of the tag to add to the data
    /// \param[in] separator The character used as a separator in the filename (ex: _)
    /// \param[in] value_position Position of the value to extract with respect to the separators
    void tag_using_seperator(SxExperiment* experiment, const QString& tag, const QString& separator, const qint16& value_position);

    /// \brief query a specific dataset of an experiment
    /// In this version only AND queries are supported (ex: tag1=value1 AND tag2=value2)
    /// and performed on the data set named dataset
    /// \param[in] experiment Pointer to the experiment
    /// \param[in] dataset_name Name of the dataset to query
    /// \param[in] query String query with the key=value format
    /// \param[in] origin_output_name Name of the ouput origin (ex: -o) in the case of ProcessedDataset search
    /// \return The list of data metadata URIs
    QStringList get_data(SxExperiment* experiment, const QString& dataset_name, const QString& query, const QString& origin_output_name="");

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
    /// \return the URI of the imported data
    virtual QString import_data(const QString& data_path, const QString& rawdataset_uri, SxRawData* metadata, bool copy) = 0;
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

protected:
    /// \brief Query a raw dataset using tags
    /// In this verion only AND queries are supported (ex: tag1=value1 AND tag2=value2)
    /// and performed on the RawData set
    /// \param[in] raw_dataset Pointer to the raw dataset
    /// \param[in] query String query with the key=value format
    /// \return List of selected data (md.json files urls are returned)
    QStringList query_rawdataset(SxDataset* raw_dataset, const QString& query);

    QStringList query_processeddataset(SxDataset* processed_dataset, const QString& query, const QString &origin_output_name);

    SxSearchContainer* raw_data_to_search_container(SxRawData* raw_data);
    SxSearchContainer* processed_data_to_search_container(SxProcessedData* processed_data);
    QList<SxSearchContainer*> raw_dataset_to_search_containers(SxDataset* raw_dataset);
    QList<SxSearchContainer*> processed_dataset_to_search_containers(SxDataset* processed_dataset);
    QStringList serach_container_list_to_uri_list(QList<SxSearchContainer*>& containers);

};
