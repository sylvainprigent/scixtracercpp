/// \file SxSerialize.h
/// \brief SxSerialize class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once


#include "scixtracerExport.h"
#include "SxSerialize.h"

#include <QString>
#include <QJsonObject>

/// \class SxSerializeJson
/// \brief Implementation of metadata serializer in Json format
class SCIXTRACER_EXPORT SxSerializeJson: public SxSerialize{

public:
    SxSerializeJson();
    virtual ~SxSerializeJson();

public:
    QString serialize(SxData* data);
    QString serialize(SxRawData* data);
    QString serialize(SxProcessedData* data);
    QString serialize(SxDataset* data);
    QString serialize(SxExperiment* data);

private:
    QString json_object_to_string(const QJsonObject& object);
    QJsonObject data_to_json(SxData* data);
};


/// \class SxPath
/// \brief Path manipulation methods
class SxPath{

public:
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
