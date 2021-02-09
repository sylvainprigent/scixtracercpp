/// \file SxRequestLocal.h
/// \brief SxRequestLocal class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include "scixtracerExport.h"
#include "SxRequest.h"

#include <QJsonObject>

/// \class SxRequestLocal
/// \brief Implementation if SxRequest for a local file systeme
class SCIXTRACER_EXPORT SxRequestLocal{

public:
    /// \brief Constructor
    SxRequestLocal();
    /// \brief Destructor
    virtual ~SxRequestLocal();

public:
    /// \brief Read a raw data metadata from the database
    /// \param[in] md_uri URI of the data
    /// \return a RawDataContainer that stores the raw data metadata
    SxRawData* read_rawdata(const QString& md_uri);
    /// \brief Write a raw data metadata to the database
    /// \param[in] container Object that contains the raw data metadata to write
    /// \param[in] md_uri URI of the data
    void write_rawdata(SxRawData* container, const QString& md_uri);
    /// \brief Read a processed data metadata from the database
    /// \param[in] URI of the data
    /// \return ProcessedDataContainer: object that contains the read processed data metadata
    SxProcessedData* read_processeddata(const QString& md_uri);
    /// \brief Write a processed data metadata to the database
    /// \param[in] container Object that contains the processed data metadata to write
    /// \param[in] md_uri URI of the data
    void write_processeddata(SxProcessedData* container, const QString& md_uri);
    /// \brief Read a raw dataset metadata from the database
    /// \param[in] md_uri URI of the dataset
    /// \return Object that contains the read dataset metadata
    SxDataset* read_rawdataset(const QString& md_uri);
    /// \brief Write a raw dataset metadata to the database
    /// \param[in] container object that contains the raw dataset metadata to write
    /// \param[in] md_uri URI of the dataset
    void write_rawdataset(SxDataset* container, const QString& md_uri);
    /// \brief Read a processed dataset metadata from the database
    /// \param[in] md_uri URI of the dataset
    /// \return Object that contains the read dataset metadata
    SxDataset* read_processeddataset(const QString& md_uri);
    /// \brief Write a processed dataset metadata to the database
    /// \param[in] container Object that contains the processed dataset metadata to write
    /// \param[in] md_uri URI of the dataset
    void write_processeddataset(SxDataset* container, const QString& md_uri);
    /// \brief Add a run to a processed dataset
    /// \param[in] run Container of the Run metadata
    /// \param[in] dataset_md_uri URI of the ProcessedDataset
    /// \return URI of the run metadata info
    QString add_run_processeddataset(SxRun* run, const QString& dataset_md_uri);
    /// \brief Create a new processed dataset
    /// \param[in] name Name of the processed dataset
    /// \param[in] experiment_md_uri URI of the experiment that contains the dataset
    /// \return Reference to the newly created dataset
    SxDataset *create_processed_dataset(const QString& name, const QString& experiment_md_uri);
    /// \brief Create a new data metadata in the dataset
    ///  The input data object must contain only the metadata (ie no uri and no md_uri).
    ///  This method generate the uri and the md_uri and save all the metadata
    /// \param[in] container Metadata of the processed data to create
    /// \param[in] md_uri URI of the processed dataset
    void create_data_processeddataset(SxProcessedData* container, const QString& md_uri);
    /// \brief Read an experiment metadata
    /// \param[in] md_uri URI of the experiment in the database
    /// \return object that contains an experiment metadata
    SxExperiment* read_experiment(const QString& md_uri);
    /// \brief Write an experiment metadata to the database
    /// \param[in] container Object that contains an experiment metadata
    /// \param[in] md_uri URI of the experiment in the database
    void write_experiment(SxExperiment* container, const QString& md_uri);
    /// \brief Create a new experiment metadata to the database
    /// \param[in] container Object that contains an experiment metadata
    /// \param[in] uri URI of the experiment in the database
    void create_experiment(SxExperiment* container, const QString& uri);
    /// \brief Import a data to a raw dataset
    /// \param[in] data_path local path of the data to import
    /// \param[in] rawdataset_uri URI of the raw dataset where the data will be imported
    /// \param[in] metadata Metadata of the data to import
    /// \param[in] copy True if the data is copied to the Experiment database, false otherwise
    /// \return the URI of the imported data
    QString import_data(const QString& data_path, const QString& rawdataset_uri, SxRawData* metadata, bool copy);
    /// \brief Read a run metadata from the data base
    /// \param[in] md_uri URI of the run entry in the database
    /// \return Object containing the run metadata
    SxRun* read_run(const QString& md_uri);
    /// \brief Write a run metadata to the data base
    /// \param[in] container Object containing the run metadata
    /// \param[in] md_uri URI of the run entry in the database
    void write_run(SxRun* container, const QString& md_uri);
    /// \brief Query files in a repository
    /// \param[in] repository_uri URI of the repository
    /// \param[in] filter_ Regular expression to select a subset of file base on their names
    /// \return The list of selected files
    QStringList query_rep(const QString& repository_uri, const QString& filter_);
    /// \brief Create the URI of an run output data file
    /// \param[in] output_rep_uri Output directory of the run
    /// \param[in] output_name Output filename
    /// \param[in] format_ Output file format
    /// \param[in] corresponding_input_uri URI of the origin input data
    /// \return The created URI
    QString create_output_uri(const QString& output_rep_uri, const QString& output_name, const QString& format_, const QString& corresponding_input_uri);

private:
    /// \brief Read the content of a json file
    /// \param[in] filename Path of the json file
    /// \return a QJsonObject containing the json data
    QJsonObject read_json(const QString& filename);
    /// \brief Write json object to file
    /// \param[in] object Json Object to write
    /// \param[in] filename Path of the file for writing
    void write_json(QJsonObject object, const QString& filename);

private:
    /// \brief Join two path, and add separator if necessary
    /// \param[in] path1 Start string of the path
    /// \param[in] path2 End string of the path
    /// \return the join path
    static QString path_join(QString path1, QString path2);
    /// \brief get metadata file directory path
    /// \param[in] md_uri md file uri
    /// \return The name of the metadata file directory path
    static QString md_file_path(const QString& md_uri);
    /// \brief Convert file absolute path to a relative path wrt reference_file
    /// \param[in] file File to get the relative path
    /// \param[in] reference_file Reference file
    /// \return Relative path of uri wrt md_uri
    static QString relative_path(const QString& file, const QString& reference_file);
    /// \brief Convert file relative to reference_file into an absolute path
    /// \param[in] file
    /// \param[in] reference_file Reference file
    /// \return Absolute path of uri wrt md_uri
    static QString absolute_path(const QString& file, const QString& reference_file);
    /// \brief Simplify a path by removing ../
    /// \param[in] path Path to simplify
    /// \return Simplified path
    static QString simplify_path(const QString& path);
    /// \brief Normalize the separators of a path (/ vs \)
    /// \param[in] path Path to normalize
    /// \return path normalized
    static QString normalize_path_sep(const QString& path);
    /// \brief Transforms a path to unix path
    /// \param[in] path Path to unixify
    /// \return Path with unix separator
    static QString to_unix_path(const QString& path);
};
