/// \file SxSerializeJson.cpp
/// \brief SxSerializeJson class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include "SxSerializeJson.h"
#include "SxException.h"

#include <QJsonObject>
#include <QJsonDocument>

SxSerializeJson::SxSerializeJson() : SxSerialize()
{

}

SxSerializeJson::~SxSerializeJson()
{

}

QString SxSerializeJson::json_object_to_string(const QJsonObject& object)
{
    QJsonDocument doc(object);
    return doc.toJson(QJsonDocument::Indented);
}

QJsonObject SxSerializeJson::data_to_json(SxData* data)
{
    QJsonObject object;

    // origin
    QJsonObject originObject;
    originObject["type"]= "unknown";
    object["origin"] = originObject;

    // common
    QJsonObject commonObject;
    commonObject["name"] = data->get_name();
    commonObject["author"] = data->get_author().get_username();
    commonObject["date"] = data->get_date().get_to_string("YYYY-MM-DD");
    commonObject["format"] = data->get_format().get_name();
    commonObject["url"] = data->get_url();
    object["common"] = commonObject;

    return object;
}

QString SxSerializeJson::serialize(SxData* data)
{
    QJsonObject obj = this->data_to_json(data);
    return this->json_object_to_string(obj);
}

QString SxSerializeJson::serialize(SxRawData* data)
{

}

QString SxSerializeJson::serialize(SxProcessedData* data)
{

}

QString SxSerializeJson::serialize(SxDataset* data)
{

}

QString SxSerializeJson::serialize(SxExperiment* data)
{

}
