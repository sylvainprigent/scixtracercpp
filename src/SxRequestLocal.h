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
class SCIXTRACER_EXPORT SxRequestLocal : public SxRequest{

public:
    /// \brief Constructor
    SxRequestLocal();
    /// \brief Destructor
    virtual ~SxRequestLocal();

public:
    /// \brief Create a new experiment
    /// \param[in] name Name of the experiment
    /// \param[in] author Username of the experiment author
    /// \param[in] date Creation date of the experiment
    /// \param[in] tag_keys List of keys used for the experiment vocabulary
    /// \param[in] destination Destination where the experiment is created. It is a the path of the directory where the experiment will be created for local use case
    /// \returns Experiment container with the experiment metadata
    virtual SxExperiment* create_experiment(const QString& name, const QString &author, SxDate* date= new SxDate("now"), const QStringList& tag_keys = {}, const QString& destination=".");

    /// \brief Read an experiment from the database
    /// \param[in] uri URI of the experiment. For local use case, the URI is either the path of the experiment directory, or the path of the experiment.md.json file
    /// \return Experiment container with the experiment metadata
    virtual SxExperiment* get_experiment(const QString uri);

    /// \brief Write an experiment to the database
    /// \param[in] experiment Container of the experiment metadata
    virtual void update_experiment(SxExperiment* experiment);

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
    virtual SxRawData* import_data(SxExperiment* experiment, const QString& data_path, const QString& name, const QString& author, SxFormat* format, SxDate* date = new SxDate("now"), SxTags* tags = new SxTags(), bool copy = true);

    /// \brief Read a raw data from the database
    /// \param[in] uri URI if the rawdata
    /// \returns RawData object containing the raw data metadata
    virtual SxRawData* get_rawdata(const QString&  uri);

    /// \brief Read a raw data from the database
    /// \param[in] rawdata Container with the rawdata metadata
    virtual void update_rawdata(SxRawData* rawdata);

    /// \brief Read a processed data from the database
    /// \param[in] uri URI if the processeddata
    /// \return ProcessedData object containing the raw data metadata
    virtual SxProcessedData* get_processeddata(const QString& uri);

    /// \brief Read a processed data from the database
    /// \param[in] processeddata Container with the processeddata metadata
    virtual void update_processeddata(SxProcessedData* processeddata);

    /// \brief Read a dataset from the database using it URI
    /// \param[in] uri URI if the dataset
    /// \return Dataset object containing the dataset metadata
    virtual SxDataset* get_dataset(const QString& uri);

    /// \brief Read a processed data from the database
    /// \param[in] dataset Container with the dataset metadata
    virtual void update_dataset(SxDataset* dataset);

    /// \brief Create a processed dataset in an experiment
    /// \param[in] experiment Object containing the experiment metadata
    /// \param[in] dataset_name Name of the dataset
    /// \return Dataset object containing the new dataset metadata
    virtual SxDataset* create_dataset(SxExperiment* experiment, const QString& dataset_name);

    /// \brief Create a new run metadata
    /// \param[in] dataset Object of the dataset metadata
    /// \param[in] run_info Object containing the metadata of the run. md_uri is ignored and created automatically by this method
    /// \return Run object with the metadata and the new created md_uri
    virtual SxRun* create_run(SxDataset* dataset, SxRun* run_info);

    /// \brief Read a run metadata from the data base
    /// \param[in] uri URI of the run entry in the database
    /// \return Run: object containing the run metadata
    virtual SxRun* get_run(const QString& uri);

    /// \brief Create a new processed data for a given dataset
    /// \param[in] dataset Object of the dataset metadata
    /// \param[in] run Metadata of the run
    /// \param[in] processed_data Object containing the new processed data. md_uri is ignored and created automatically by this method
    virtual SxProcessedData* create_data(SxDataset* dataset, SxRun* run, SxProcessedData* processed_data);

private:
    /// \brief Write a run metadata in the database
    /// \param[in] run Metadata container
    void _write_run(SxRun* run);
    /// \brief Generate a new random UUID
    /// \return String continaing the UUID
    QString _generate_uuid();
    /// \brief Read the metadata from the a JSON file
    /// \param[in] filename URI of the JSON file
    /// \return Object containing the JSON data
    QJsonObject _read_json(const QString& filename);
    /// \brief Write the metadata to the a json file
    /// \param[in] metadata Metadata in a JSON object
    /// \param[in] md_uri URI of the destination file
    void _write_json(const QJsonObject& metadata, const QString& filename);
    /// \brief get metadata file directory path
    /// \param[in] md_uri URI of the metadata file
    /// \return The metadata file directory path
    QString md_file_path(const QString& md_uri);
    /// \brief Convert file absolute path to a relative path wrt reference_file
    /// \param[in] reference_file Reference file path
    /// \param[in] file File to get absolute path
    /// \return relative path of file wrt reference_file
    QString relative_path(const QString& file, const QString& reference_file);
    /// \brief Convert file relative to reference_file into an absolute path
    /// \param[in] reference_file Reference file
    /// \param[in] file File to get absolute path
    /// \return absolute path of file
    QString absolute_path(const QString& file, const QString& reference_file);
    /// \brief Simplify a path by removing ../
    /// \param[in] path Path to simplify
    /// \return Simplified path
    QString simplify_path(const QString& path);
    /// \brief Normalize the separators of a path
    /// \param[in] path Path to normalize
    /// \return path normalized
    QString normalize_path_sep(const QString& path);
    /// \brief Transform a path to unix path
    /// \param[in] path Path to unixify
    /// \return Path with unix separator
    QString to_unix_path(const QString& path);
    /// \brief Create a path by joining two part of path
    /// \param[in] path1 First path of the path
    /// \param[in] path2 Second part of the path
    /// \return the constructed path
    QString path_join(QString path1, QString path2);
    /// \brief get the absolut file path
    /// \param[in] path Relative path
    /// \return the absoute path
    QString abspath(const QString& path);

};
