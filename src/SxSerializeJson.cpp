/// \file SxSerializeJson.cpp
/// \brief SxSerializeJson class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include "SxSerializeJson.h"
#include "SxException.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include <QDir>
#include <QFileInfo>

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

    // common
    QJsonObject commonObject;
    commonObject["name"] = data->get_name();
    commonObject["author"] = data->get_author().get_username();
    commonObject["date"] = data->get_date().get_to_string("YYYY-MM-DD");
    commonObject["format"] = data->get_format().get_name();
    commonObject["url"] = data->get_url(); /// \todo convert to relative path
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
    QJsonObject object = this->data_to_json(data);

    // origin
    QJsonObject originObject;
    originObject["type"] = "raw";
    object["origin"] = originObject;

    // tags
    QJsonObject tagsObject;
    SxTags* tags = data->get_tags();
    QStringList keys = tags->get_keys();
    for (qint8 i = 0 ; i < keys.count() ; i++)
    {
        tagsObject[keys[i]] = tags->get_tag(keys[i]);
    }
    object["tags"] = tagsObject;

    return this->json_object_to_string(object);
}

QString SxSerializeJson::serialize(SxProcessedData* data)
{
    QJsonObject object = this->data_to_json(data);

    // origin
    QJsonObject originObject;
    originObject["type"] = "processed";
    /// \todo convert to relative path
    originObject["runurl"] = data->get_run_uri();

    // origin inputs
    QJsonArray inputsArray;
    for (qint8 i = 0 ; i < data->get_run_inputs_count() ; ++i)
    {
        SxProcessedDataInput input = data->get_run_input(i);
        QJsonObject inputObject;
        inputObject["name"] = input.get_name();
        inputObject["url"] = input.get_uri(); /// \todo convert to relative path
        inputObject["type"] = input.get_type();
        inputsArray.append(inputObject);
    }
    originObject["inputs"] = inputsArray;

    // origin output
    QJsonObject outputObject;
    outputObject["name"] = data->get_run_output().get_name();
    outputObject["label"] = data->get_run_output().get_label();

    object["origin"] = originObject;
    return this->json_object_to_string(object);
}

QString SxSerializeJson::serialize(SxDataset* data)
{
    QJsonObject object;
    object["name"] = data->get_name();
    QJsonArray urlsArray;
    /// \todo convert to relative path
    object["urls"] = urlsArray.fromStringList(data->get_data_list());

    return this->json_object_to_string(object);
}

QString SxSerializeJson::serialize(SxExperiment* data)
{
    QJsonObject object;

    // information
    QJsonObject informationObject;
    informationObject["name"] = data->get_name();
    informationObject["author"] = data->get_author().get_username();
    informationObject["date"] = data->get_date().get_to_string("YYYY-MM-DD");
    object["information"] = informationObject;

    // rawdataset
    /// \todo convert to relative path
    object["rawdataset"] = data->get_raw_dataset();

    // processeddatasets
    /// \todo convert to relative path
    QJsonArray processedDatasetsArray;
    object["processeddatasets"] = processedDatasetsArray.fromStringList(data->get_processed_datasets());

    // tags
    QJsonArray tagsArray;
    object["tags"] = tagsArray.fromStringList(data->get_tags_keys());

    return this->json_object_to_string(object);
}


QString SxPath::md_file_path(const QString& md_uri)
{
    QFileInfo file(md_uri);
    return file.absolutePath();
}


QString SxPath::relative_path(const QString& file, const QString& reference_file)
{
    QString file_ = file;
    QString reference_file_ = reference_file;
    QString separator = QString(QDir::separator());
    file_ = file_.replace(separator + separator, separator);
    reference_file_ = reference_file_.replace(separator + separator, separator);

    QString common_part;
    for (qint8 i = 0 ; i < file.count() ; i++)
    {
        common_part = reference_file_.left(i);
        if (!file_.contains(file)){
            break;
        }
    }

    qint8 last_separator = common_part.lastIndexOf(separator);
    QString short_reference_file = reference_file_.right(last_separator+1);

    qint8 number_of_sub_folder = short_reference_file.count(separator);
    QString short_file = file.right(last_separator + 1);
    for (qint8 i = 0 ; i < number_of_sub_folder ; i++){
        short_file = ".." + separator + short_file;
    }

    return short_file;
}

QString SxPath::absolute_path(const QString& file, const QString &reference_file)
{
    if (QFile::exists(file)){
        QFileInfo f_info(file);
        return f_info.absoluteFilePath();
    }

    qint8 last_separator = reference_file.lastIndexOf(QDir::separator());
    QString canonical_path = reference_file.left(last_separator+1);
    return SxPath::simplify_path(canonical_path + file);
}


QString SxPath::simplify_path(const QString& path)
{
    if (path.indexOf("..") < 0){
        return path;
    }

    QStringList keep_folders = path.split(QDir::separator());

    bool found = true;
    while (found)
    {
        qint8 pos = -1;
        QStringList folders = keep_folders;
        for (qint8 i=0 ; i<folders.count() ; ++i)
        {
            if (folders[i] == "..")
            {
                pos = i;
                break;
            }
        }
        if (pos > -1)
        {
            QStringList keep_folders;
            for (qint8 i = 0 ; i < pos - 1 ; ++i)
            {
                keep_folders.append(folders[i]);
            }
            for (qint8 i = pos + 1 ; i < folders.count() ; ++i)
            {
                keep_folders.append(folders[i]);
            }
        }
        else
        {
            found = false;
        }
    }

    QString clean_path = "";
    for (qint8 i = 0 ; i < keep_folders.count(); ++i )
    {
        clean_path += keep_folders[i];
        if (i < keep_folders.count() - 1)
        {
            clean_path += QDir::separator();
        }
    }
    return clean_path;
}


QString SxPath::normalize_path_sep(const QString &path)
{
    QString p = path;
    QString p1 = p.replace("/", QDir::separator()).replace("\\\\", QDir::separator());
    return p1;
}


QString SxPath::to_unix_path(const QString& path)
{
    QString p = path;
    return p.replace("\\\\", "/").replace("\\", "/");
}
