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

    Q_OBJECT

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
    qint32 get_data_count();
    /// \brief Get the URI of one data in the dataset
    /// \param[in] Index of the data in the dataset
    /// \return URI of the data at index
    QString get_data_uri(qint32 index);
    /// \brief Get the UUID of one data in the dataset
    /// \param[in] Index of the data in the dataset
    /// \return UUID of the data at index
    QString get_data_uuid(qint32 index);
    /// \brief Get the metadata (URI and UUID) of one data in the dataset
    /// \return a pointer to the data metadata
    SxMetadata *get_data(qint32 index);
    /// \brief Get the URIs list of the data the dataset
    /// \return URIs list of the data the dataset
    QStringList get_data_list();

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
    void set_data(SxMetadata* metadata);

private:
    QString m_type;
    QString m_name;
    QList<SxMetadata*> m_data;

};
