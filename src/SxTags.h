/// \file SxTags.h
/// \brief SxTags class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include "scixtracerExport.h"
#include "SxContainer.h"

#include <QMap>

/// \class SxTags
/// \brief Container for a map of tags associated to a RawData. Tags are represented as key=value
class SCIXTRACER_EXPORT SxTags: public SxContainer{

    Q_OBJECT

public:
    SxTags();
    ~SxTags();

public:
    // getters
    /// \brief Get the value of a tag from it key
    /// \param[in] key Key of the tag
    /// \return value of the tag
    QString get_tag(QString key);
    /// \brief Get the number of pairs 'key=value' of tags
    /// \return Number of tag in the Tags map
    qint8 get_count();
    /// \brief Get the list of keys in the Tags map
    /// \return List of tags keys
    QStringList get_keys();

public:
    // setters
    /// \brief Set a tag to the map. If the tag already exists, it is replaced
    /// \param[in] key Key of the tag
    /// \param[in] value Value of the tag
    void set_tag(QString key, QString value);

private:
    QMap<QString, QString> m_tags;

};
