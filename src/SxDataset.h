/// \file SxDataset.h
/// \brief SxDataset class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include "scixtracerExport.h"
#include "SxMetadata.h"

#include <QSet>

/// \class SxDataset
/// \brief Metadata container for a dataset
class SCIXTRACER_EXPORT SxDataset: public SxMetadata{

public:
    SxDataset();
    ~SxDataset();

public:
    // getters
    /// \brief Get the dataset type: (raw or processed)
    /// \return Dataset type: (raw or processed)
    QString get_type();
    /// \brief Get the dataset name
    /// \return Dataset type: (raw or processed)
    QString get_name();
    /// \brief Get the number of data in the dataset
    /// \return Number of data in the dataset
    qint8 get_data_count();
    /// \brief Get the URI of one data in the dataset
    /// \param[in] Index of the data in the dataset
    /// \return URI of the data at index
    QString get_data_uri(qint8 index);

public:
    // setters
    /// \brief Set the dataset type
    /// \param[in] type Type of the dataset: (raw or processed)
    void set_type(const QString& type);
    /// \brief Set the dataset name
    /// \param[in] name Name of the dataset
    void set_name(const QString& name);
    /// \brief Set a data in the dataset. Add if not exists
    /// \param[in] uri URI of the data
    void set_data(const QString& uri);

private:
    QString m_type;
    QString m_name;
    QSet<QString> m_data_uris;

};
