/// \file SxExperiment.h
/// \brief SxExperiment class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include "scixtracerExport.h"
#include "SxMetadata.h"

#include "SxUser.h"
#include "SxDate.h"

/// \class SxExperiment
/// \brief Metadata container for an Experiment
class SCIXTRACER_EXPORT SxExperiment: public SxMetadata{

public:
    SxExperiment();
    ~SxExperiment();

public:
    // getters
    /// \brief Get the name of the Experiment
    /// \return Name of the Experiment
    QString get_name();
    /// \brief Get the author of the Experiment
    /// \return Reference to the Experiment author
    SxUser get_author();
    /// \brief Get the date of the Experiment
    /// \return Date of the Experiment
    SxDate get_date();
    /// \brief Get the URI of the raw dataset
    /// \return URI of the raw dataset
    QString get_raw_dataset();
    /// \brief Get the URI list of the processed dataset
    /// \return URI list of the processed dataset
    QStringList get_processed_datasets();
    /// \brief Get the number of processed dataset
    /// \return Number of processed dataset
    qint8 get_processed_datasets_count();
    /// \brief Get the URI of the processed dataset at index
    /// \param[in] index Index of the processed dataset
    /// \return URI of the processed dataset at index
    QString get_processed_dataset(qint8 index);
    /// \brief Get the list of tags keys used in the Experiment
    /// \return List of tags keys used in the Experiment
    QStringList get_tags_keys();
    /// \brief Get the number of tag keys in the Experiment
    /// \return Number of tag keys in the Experiment
    qint8 get_tags_keys_count();
    /// \brief Get the tag key at index
    /// \param[in] index Index of the tag key
    /// \return Tag key at index
    QString get_tags_key(qint8 index);

public:
    // setters
    /// \brief Set the name of the Experiment
    /// \param[in] name Name of the Experiment
    void set_name(const QString& name);
    /// \brief Set the author of the Experiment
    /// \param[in] user Reference to the Experiment author
    void set_author(const SxUser& user);
    /// \brief Set the date of the Experiment
    /// \param[in] date Date of the Experiment
    void set_date(const SxDate& date);
    /// \brief Set the URI of the raw dataset
    /// \param[in] uri URI of the raw dataset
    void set_raw_dataset(const QString& uri);
    /// \brief Set the URI of a processed dataset
    /// \param[in] uri URI of the processed dataset
    void set_processed_dataset(const QString& uri);
    /// \brief Set a tag key
    /// \param[in] key Tag key
    void set_tag_key(const QString& key);

private:
    QString m_name;
    SxUser m_author;
    SxDate m_date;
    QString m_raw_dataset_uri;
    QStringList m_processed_datasets_uris;
    QStringList m_tags_keys;
};
