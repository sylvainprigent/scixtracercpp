/// \file SxMetadata.h
/// \brief SxMetadata class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once


#include "scixtracerExport.h"
#include "SxContainer.h"

/// \class SxMetadata
/// \brief Abstract parent class to all metadata containers
class SCIXTRACER_EXPORT SxMetadata: public SxContainer{

    Q_OBJECT

public:
    SxMetadata();
    SxMetadata(const QString &md_uri, const QString &uuid);
    virtual ~SxMetadata();

public:
    // getters
    /// \brief Get the metadata URI
    /// \return URI of the metadata
    QString get_md_uri();
    /// \brief Get the metadata UUID
    /// \return a string contining the UUID
    QString get_uuid();

public:
    // setters
    /// \brief Set the container URI
    /// \param[in] md_uri URI of the metadata
    void set_md_uri(const QString& md_uri);

    /// \brief Set the container URI
    /// \param[in] md_uri URI of the metadata
    void set_uuid(const QString& uuid);

private:
    QString m_md_uri;
    QString m_uuid;
};
