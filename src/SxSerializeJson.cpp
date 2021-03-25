/// \file SxSerializeJson.cpp
/// \brief SxSerializeJson class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include <SxSerializeJson.h>
#include "SxException.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

SxSerializeJson::SxSerializeJson()
{

}

SxSerializeJson::~SxSerializeJson()
{

}

QString SxSerializeJson::serialize_rawdata(SxRawData* container)
{
    QJsonObject metadata;
    metadata["uuid"] = container->get_uuid();

    QJsonObject origin;
    origin["type"] = "raw";
    metadata["origin"] = origin;

    QJsonObject common;
    common["name"] = container->get_name();
    common["author"] = container->get_author();
    common["date"] = container->get_date()->get_to_string("YYYY-MM-DD");
    common["format"] = container->get_format()->get_name();
    common["url"] = container->get_uri();
    metadata["common"] = common;

    QJsonObject tags;
    SxTags* _tags = container->get_tags();
    QStringList keys = _tags->get_keys();
    for (qint8 i = 0 ; i < keys.count() ; ++i)
    {
        tags[keys[i]] = _tags->get_tag(keys[i]);
    }

    QJsonDocument doc(metadata);
    return doc.toJson(QJsonDocument::Indented);
}

QString SxSerializeJson::serialize_processeddata(SxProcessedData* container)
{
    QJsonObject metadata;
    metadata["uuid"] = container->get_uuid();

     // common
    QJsonObject common;
    common["name"] = container->get_name();
    common["author"] = container->get_author();
    common["date"] = container->get_date()->get_to_string("YYYY-MM-DD");
    common["format"] = container->get_format()->get_name();
    common["url"] = container->get_uri();
    metadata["common"] = common;
    // origin type
    QJsonObject origin;
    origin["type"] = "processed";
    // run url
    QJsonObject runObject;
    runObject["uuid"] = container->get_run()->get_uuid();
    runObject["url"] = container->get_run()->get_md_uri();
    origin["run"] = runObject;
    // origin inputs
    QJsonArray inputs_json;
    for (qint8 i = 0 ; i < container->get_run_inputs_count() ; ++i)
    {
        SxProcessedDataInput* input_data = container->get_run_input(i);
        QJsonObject input_json;
        input_json["name"] = input_data->get_name();
        input_json["uuid"] = input_data->get_data()->get_uuid();
        input_json["url"] = input_data->get_data()->get_uuid();
        input_json["type"] = input_data->get_type();
        inputs_json.append(input_json);
    }
    origin["inputs"] = inputs_json;
    // origin ouput
    QJsonObject output_json;
    output_json["name"] = container->get_run_output()->get_name();
    output_json["label"] = container->get_run_output()->get_label();
    origin["output"] = inputs_json;
    metadata["origin"] = origin;

    QJsonDocument doc(metadata);
    return doc.toJson(QJsonDocument::Indented);
}

QString SxSerializeJson::serialize_dataset(SxDataset* container)
{
    QJsonObject metadata;
    metadata["uuid"] = container->get_uuid();
    metadata["name"] = container->get_name();
    QJsonArray urls_json;
    for (qint8 i = 0 ; i < container->get_data_count() ; ++i)
    {
        QJsonObject obj;
        obj["uuid"] = container->get_data(i)->get_uuid();
        obj["url"] = container->get_data(i)->get_md_uri();
        urls_json.append(obj);
    }
    metadata["urls"] = urls_json;

    QJsonDocument doc(metadata);
    return doc.toJson(QJsonDocument::Indented);
}

QString SxSerializeJson::serialize_run(SxRun* container)
{
    QJsonObject json_metadata;
    json_metadata["uuid"] = container->get_uuid();
    QJsonObject json_process;
    json_process["name"] = container->get_process_name();
    json_process["url"] = container->get_process_uri();
    json_metadata["process"] = json_process;

    QJsonObject json_processeddataset;
    json_processeddataset["uuid"] = container->get_processed_dataset()->get_uuid();
    json_processeddataset["url"] = container->get_processed_dataset()->get_md_uri();
    json_metadata["processeddataset"] = json_processeddataset;

    QJsonArray json_inputs;
    for (qint8 i = 0 ; i < container->get_inputs_count() ; ++i){
        QJsonObject json_input;
        SxRunInput* input = container->get_input(i);
        json_input["name"] = input->get_name();
        json_input["dataset"] = input->get_dataset_name();
        json_input["query"] = input->get_query();
        json_input["origin_output_name"] = input->get_origin_output_name();
        json_inputs.append(json_input);
    }
    json_metadata["inputs"] = json_inputs;

    QJsonArray json_parameters;
    for (qint8 i = 0 ; i < container->get_parameters_count() ; ++i){
        QJsonObject json_parameter;
        json_parameter["name"] = container->get_parameter(i)->get_name();
        json_parameter["value"] = container->get_parameter(i)->get_value();
        json_parameters.append(json_parameter);
    }
    json_metadata["parameters"] = json_parameters;

    QJsonDocument doc(json_metadata);
    return doc.toJson(QJsonDocument::Indented);
}

QString SxSerializeJson::serialize_experiment(SxExperiment* container)
{
    QJsonObject metadata;
    QJsonObject information;
    information["name"] = container->get_name();
    information["author"] = container->get_author();
    information["date"] = container->get_date()->get_to_string("YYYY-MM-DD");
    metadata["information"] = information;

    QJsonObject json_rawdataset;
    json_rawdataset["name"] = container->get_raw_dataset()->get_name();
    json_rawdataset["url"] = container->get_raw_dataset()->get_md_uri();
    json_rawdataset["uuid"] = container->get_raw_dataset()->get_uuid();
    metadata["rawdataset"] = json_rawdataset;

    QJsonArray jprocesseddatasets;
    for (qint8 i = 0 ; i < container->get_processed_datasets_count() ; ++i)
    {
        SxDatasetMetadata* met = container->get_processed_dataset(i);
        QJsonObject json_met;
        json_met["name"] = met->get_name();
        json_met["url"] = met->get_md_uri();
        json_met["uuid"] = met->get_uuid();
        jprocesseddatasets.append(json_met);
    }
    metadata["processeddatasets"] = jprocesseddatasets;
    QJsonArray jtags;
    for (qint8 i = 0 ; i < container->get_tags_keys_count() ; ++i)
    {
        jtags.append(container->get_tags_key(i));
    }
    metadata["tags"] = jtags;

    QJsonDocument doc(metadata);
    return doc.toJson(QJsonDocument::Indented);
}
