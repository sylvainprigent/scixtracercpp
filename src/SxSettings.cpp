/// \file SxSettings.cpp
/// \brief SxSettings class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include "SxSettings.h"
#include "SxException.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>

SxSettings::SxSettings()
{

}

SxSettings::SxSettings(const QString& filename)
{
    this->set_file(filename);
}

SxSettings::~SxSettings()
{

}

void SxSettings::set_file(const QString& filename)
{
    QFile loadFile(filename);

    if (!loadFile.open(QIODevice::ReadOnly)) {
        throw SxException(QString("Could not oppen the setting file: " + filename).toStdString().c_str());
    }

    QByteArray filecontent = loadFile.readAll();
    QJsonDocument filecontentjson = QJsonDocument::fromJson(filecontent);
    m_settings_object = filecontentjson.object();
}

QString SxSettings::get_parameter_string(const QString& key)
{
    QJsonValue value = this->get_parameter(key);
    return value.toString();
}

qint8 SxSettings::get_paramerter_int(const QString& key)
{
    QJsonValue value = this->get_parameter(key);
    return value.toInt();
}

float SxSettings::get_paramerter_float(const QString& key)
{
    QJsonValue value = this->get_parameter(key);
    return float(value.toDouble());
}

QStringList SxSettings::get_paramerter_stringlist(const QString& key)
{
    QJsonValue value = this->get_parameter(key);
    QJsonArray array = value.toArray();

    QStringList values;
    for (int i = 0; i < array.size(); ++i) {
        values.append(array[i].toString());
    }
    return values;
}

QList<qint8> SxSettings::get_paramerter_intlist(const QString& key)
{
    QJsonValue value = this->get_parameter(key);
    QJsonArray array = value.toArray();

    QList<qint8> values;
    for (int i = 0; i < array.size(); ++i) {
        values.append(array[i].toInt());
    }
    return values;
}

QList<float> SxSettings::get_paramerter_floatlist(const QString& key)
{
    QJsonValue value = this->get_parameter(key);
    QJsonArray array = value.toArray();

    QList<float> values;
    for (int i = 0; i < array.size(); ++i) {
        values.append(float(array[i].toDouble()));
    }
    return values;
}

QString SxSettings::get_parameter_string(const QStringList& keys)
{
    QJsonValue value = this->get_parameter(keys);
    return value.toString();
}

qint8 SxSettings::get_paramerter_int(const QStringList& keys)
{
    QJsonValue value = this->get_parameter(keys);
    return value.toInt();
}

float SxSettings::get_paramerter_float(const QStringList& keys)
{
    QJsonValue value = this->get_parameter(keys);
    return float(value.toDouble());
}

QStringList SxSettings::get_paramerter_stringlist(const QStringList& keys)
{
    QJsonValue value = this->get_parameter(keys);
    QJsonArray array = value.toArray();

    QStringList values;
    for (int i = 0; i < array.size(); ++i) {
        values.append(array[i].toString());
    }
    return values;
}

QList<qint8> SxSettings::get_paramerter_intlist(const QStringList& keys)
{
    QJsonValue value = this->get_parameter(keys);
    QJsonArray array = value.toArray();

    QList<qint8> values;
    for (int i = 0; i < array.size(); ++i) {
        values.append(array[i].toInt());
    }
    return values;
}

QList<float> SxSettings::get_paramerter_floatlist(const QStringList& keys)
{
    QJsonValue value = this->get_parameter(keys);
    QJsonArray array = value.toArray();

    QList<float> values;
    for (int i = 0; i < array.size(); ++i) {
        values.append(float(array[i].toDouble()));
    }
    return values;
}

QJsonValue SxSettings::get_parameter(const QString& key)
{
    if (m_settings_object.contains(key)){
        return m_settings_object[key];
    }
    else{
        throw SxException(("The setting file does not contains the key: " + key).toStdString().c_str());
    }
}

QJsonValue SxSettings::get_parameter(const QStringList& keys)
{
    QJsonValue object = m_settings_object;
    for (qint8 i = 0 ; i < keys.count() ; i++){
        object = object[keys[i]].toObject();
    }
    return object;
}
