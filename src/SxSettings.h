/// \file SxSettings.h
/// \brief SxSettings class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include <QString>
#include <QStringList>
#include <QJsonObject>
#include "scixtracerExport.h"

/// \class SxSettings
/// \brief Class that read settings from a json settings file
class SCIXTRACER_EXPORT SxSettings{

public:
    SxSettings();
    SxSettings(const QString& filename);
    virtual ~SxSettings();

public:
    void set_file(const QString& filename);

public:
    QString get_parameter_string(const QString& key);
    qint8 get_paramerter_int(const QString& key);
    float get_paramerter_float(const QString& key);
    QStringList get_paramerter_stringlist(const QString& key);
    QList<qint8> get_paramerter_intlist(const QString& key);
    QList<float> get_paramerter_floatlist(const QString& key);

    QString get_parameter_string(const QStringList& keys);
    qint8 get_paramerter_int(const QStringList& keys);
    float get_paramerter_float(const QStringList& keys);
    QStringList get_paramerter_stringlist(const QStringList& keys);
    QList<qint8> get_paramerter_intlist(const QStringList& keys);
    QList<float> get_paramerter_floatlist(const QStringList& keys);

public:
    QJsonValue get_parameter(const QString& key);
    QJsonValue get_parameter(const QStringList& key);

private:
    QJsonObject m_settings_object;
};
