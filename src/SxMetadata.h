/// \file SxMetadata.h
/// \brief SxMetadata class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once


#include "scixtracerExport.h"
#include "SxContainer.h"

#include <QMap>

/// \class SxMetadata
/// \brief Abstract parent class to all metadata containers
class SCIXTRACER_EXPORT SxMetadata: public SxContainer{

public:
    SxMetadata();
    ~SxMetadata();

public:
    // methods
    /// \brief Add a child container
    /// \param[in] container Reference to the child container
    void add_child(SxMetadata* container);

public:
    // getters
    /// \brief Get the metadata URI
    /// \return URI of the metadata
    QString get_uri();
    /// \brief Get a child from it URI
    /// \param[in] uri URI of the child metadata
    /// \return Reference to the child container, or null reference if not exists
    SxMetadata* get_child(QString uri);
    /// \brief Get a child from it index in the children map
    /// \param[in] index Index of the child metadata in the children map
    /// \return Reference to the child container, or null reference if not exists
    SxMetadata* get_child_at(qint8 index);
    /// \brief Get a number of children in the children map
    /// \return Number of children in the children map
    qint8 get_children_count();

public:
    // setters
    /// \brief Set the container URI
    /// \param[in] uri URI of the metadata
    void set_uri(const QString& uri);

private:
    QString m_uri;
    QMap<QString, SxMetadata*> m_children;
};
