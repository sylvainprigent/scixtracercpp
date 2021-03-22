/// \file SxSearchContainer.h
/// \brief SxSearchContainer class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include <QObject>
#include <QString>
#include "scixtracerExport.h"

#include "SxContainer.h"
#include "SxTags.h"

/// \class SxSearchContainer
/// \brief Container for data queries on tag
class SCIXTRACER_EXPORT SxSearchContainer: public SxContainer{

    Q_OBJECT

public:
    SxSearchContainer();
    SxSearchContainer(const QString& name, const QString& uri, const QString& uuid, SxTags* tags);
    ~SxSearchContainer();

public:
    // getters
    /// \brief Get the data name
    /// \return data name
    QString get_name();
    /// \brief Get the data URI
    /// \return data URI
    QString get_uri();
    /// \brief Get the data UUID
    /// \return data UUID
    QString get_uuid();
    /// \brief Get the data Tags
    /// \return Pointer to the tags
    SxTags* get_tags();

public:
    // setters
    /// \brief Set the data name
    /// \param[in] name Data name
    void set_name(const QString& name);
    /// \brief Set the data URI
    /// \param[in] uri Data URI
    void set_uri(const QString& uri);
    /// \brief Set the data UUID
    /// \param[in] uuid Data UUID
    void set_uuid(const QString& uuid);
    /// \brief set the data Tags
    /// \param[in] tags Pointer to the tags
    void set_tags(SxTags* tags);

public:
    bool is_tag(const QString& key);
    QString get_tag(const QString& key);

private:
    QString m_name;
    QString m_uri;
    QString m_uuid;
    SxTags* m_tags;
};
