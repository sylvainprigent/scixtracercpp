/// \file SxRequest.cpp
/// \brief SxRequest class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include "SxRequest.h"
#include "SxException.h"
#include "SxSearch.h"

#include <QDir>
#include <QRegularExpression>

SxRequest::SxRequest()
{

}

SxRequest::~SxRequest()
{

}

SxData* SxRequest::get_parent(const QString& data_md_uri)
{
    SxProcessedData* processed_data = this->read_processeddata(data_md_uri);
    if (processed_data->get_run_inputs_count() > 0)
    {
        if (processed_data->get_run_input(0)->get_type() == "raw"){
            return this->read_rawdata(processed_data->get_run_input(0)->get_uri());
        }
        else
        {
            return this->read_processeddata(processed_data->get_run_input(0)->get_uri());
        }
    }
    return nullptr;
}

SxRawData* SxRequest::get_origin(const QString& data_md_uri)
{
    SxProcessedData* processed_data = this->read_processeddata(data_md_uri);
    if (processed_data->get_run_inputs_count() > 0)
    {
        if (processed_data->get_run_input(0)->get_type() == "raw"){
            return this->read_rawdata(processed_data->get_run_input(0)->get_uri());
        }
        else
        {
            return this->get_origin(processed_data->get_run_input(0)->get_uri());
        }
    }
    return nullptr;
}

SxRawData* SxRequest::import_data_experiment(SxExperiment* experiment, const QString& data_path, const QString& name,
                                             SxUser* author, SxFormat* format, SxDate *date,
                                             SxTags* tags, bool copy)
{
    SxRawData* metadata = new SxRawData();
    metadata->set_name(name);
    metadata->set_author(author);
    metadata->set_format(format);
    metadata->set_date(date);
    metadata->set_tags(tags);
    this->import_data(data_path, experiment->get_raw_dataset(), metadata, copy);
    return metadata;
}

void SxRequest::import_dir_experiment(SxExperiment* experiment, const QString& dir_uri, const QString& filter_,
                                      SxUser* author, SxFormat* format, SxDate *date, bool copy)
{
    QDir directory(dir_uri);
    QStringList data_files = directory.entryList(QDir::Files);
    qint16 count = 0;
    foreach(QString filename, data_files) {
        count ++;
        QRegularExpression re(filter_);
        QRegularExpressionMatch match = re.match(filename);
        if (match.hasMatch()){
            // this->notify(int(100 * count / data_files.count()), filename);
            QString data_url = dir_uri + QDir::separator() + filename;
            this->import_data_experiment(experiment, data_url, filename,
                                         author, format, date,
                                         new SxTags(), copy);
        }
    }
}

void SxRequest::tag_from_name(SxExperiment* experiment, const QString& tag, const QStringList& values)
{
    experiment->set_tag_key(tag);
    SxDataset* rawdataset = this->read_rawdataset(experiment->get_raw_dataset());
    for (qint16 i = 0 ; i < rawdataset->get_data_count() ; ++i){
        SxRawData* rawdata = this->read_rawdata(rawdataset->get_data_uri(i));
        for (qint16 j = 0 ; j < values.count() ; ++j){
            if ( rawdata->get_name().contains(values[j])){
                rawdata->get_tags()->set_tag(tag, values[j]);
            }
        }
        this->write_rawdata(rawdata, rawdata->get_md_uri());
    }
}

void SxRequest::tag_using_seperator(SxExperiment* experiment, const QString& tag, const QString& separator, const qint16& value_position)
{
    experiment->set_tag_key(tag);
    SxDataset* rawdataset = this->read_rawdataset(experiment->get_raw_dataset());
    for (qint16 i = 0 ; i < rawdataset->get_data_count() ; ++i){
        SxRawData* rawdata = this->read_rawdata(rawdataset->get_data_uri(i));
        QFileInfo qt_file(rawdata->get_uri());
        QStringList splited_name = qt_file.baseName().split(separator);
        QString value = "";
        if (splited_name.count() > value_position){
            value = splited_name[value_position];
        }
        rawdata->get_tags()->set_tag(tag, value);
        this->write_rawdata(rawdata, rawdata->get_md_uri());
    }
}

QStringList SxRequest::get_data(SxExperiment* experiment, const QString& dataset_name, const QString& query, const QString& origin_output_name)
{
    SxDataset* raw_dataset = this->read_rawdataset(experiment->get_raw_dataset());
    if (raw_dataset->get_name() == dataset_name)
    {
        return this->query_rawdataset(raw_dataset, query);
    }
    else{
        for (qint16 i = 0 ; i < experiment->get_processed_datasets_count() ; ++i){
            SxDataset* processeddataset = this->read_processeddataset(experiment->get_processed_dataset(i));
            if (processeddataset->get_name() == dataset_name){
                return this->query_processeddataset(processeddataset, query, origin_output_name);
            }
        }
    }
    throw SxException(QString("Query dataset: " + dataset_name + " not found").toStdString().c_str());
}


// private
SxSearchContainer* SxRequest::raw_data_to_search_container(SxRawData* raw_data)
{
    SxSearchContainer* info = new SxSearchContainer();
    info->set_name(raw_data->get_name());
    info->set_uri(raw_data->get_md_uri());
    info->set_tags(raw_data->get_tags());
    return info;
}

SxSearchContainer* SxRequest::processed_data_to_search_container(SxProcessedData* processed_data)
{
    SxSearchContainer* info = new SxSearchContainer();
    info->set_name(processed_data->get_name());
    info->set_uri(processed_data->get_md_uri());

    SxRawData* origin = this->get_origin(processed_data->get_md_uri());
    if (origin){
        info->set_tags(origin->get_tags());
    }
    return info;
}

QList<SxSearchContainer*> SxRequest::raw_dataset_to_search_containers(SxDataset* raw_dataset)
{
    QList<SxSearchContainer*> search_list;
    for (qint16 i = 0 ; i < raw_dataset->get_data_count() ; ++i)
    {
        SxRawData* data = this->read_rawdata(raw_dataset->get_data_uri(i));
        search_list.append(this->raw_data_to_search_container(data));
    }
    return search_list;
}

QList<SxSearchContainer*> SxRequest::processed_dataset_to_search_containers(SxDataset* processed_dataset)
{
    QList<SxSearchContainer*> search_list;
    for (qint16 i = 0 ; i < processed_dataset->get_data_count() ; ++i)
    {
        SxProcessedData* data = this->read_processeddata(processed_dataset->get_data_uri(i));
        search_list.append(this->processed_data_to_search_container(data));
    }
    return search_list;
}

QStringList SxRequest::query_rawdataset(SxDataset* raw_dataset, const QString& query)
{

    QStringList queries = query.split(" AND ");

    // initially all the raw data are selected
    QList<SxSearchContainer*> selected_list = this->raw_dataset_to_search_containers(raw_dataset);

    if (query == ""){
        return this->serach_container_list_to_uri_list(selected_list);
    }

    // run all the AND queries on the preselected dataset
    foreach(QString q, queries){
        selected_list = SxSearch::query_list_single(selected_list, q);
    }

    // convert SearchContainer list to uri list
    return this->serach_container_list_to_uri_list(selected_list);
}

QStringList SxRequest::query_processeddataset(SxDataset* processed_dataset, const QString& query, const QString& origin_output_name)
{
    // get all the tags per data
    QList<SxSearchContainer*> pre_list = this->processed_dataset_to_search_containers(processed_dataset);

    // remove the data where output origin is not the asked one
    QList<SxSearchContainer*> selected_list;
    if (origin_output_name != "")
    {
        for (qint16 i = 0 ; i < pre_list.count() ; ++i)
        {
            SxProcessedData* data = this->read_processeddata(pre_list[i]->get_uri());
            if (data->get_run_output()->get_name() == origin_output_name)
            {
                selected_list.append(pre_list[i]);
            }

        }
    }
    else
    {
        selected_list = pre_list;
    }

    if (query == ""){
        return this->serach_container_list_to_uri_list(selected_list);
    }

    // query on tags
    QStringList queries = query.split(" AND ");

    // run all the AND queries on the preselected dataset
    foreach(QString q, queries){
        selected_list = SxSearch::query_list_single(selected_list, q);
    }

    // convert SearchContainer list to uri list
    return this->serach_container_list_to_uri_list(selected_list);
}

QStringList SxRequest::serach_container_list_to_uri_list(QList<SxSearchContainer*>& containers)
{
    QStringList out;
    for (qint16 i = 0 ; i < containers.count() ; ++i)
    {
        out.append(containers[i]->get_uri());
    }
    return out;
}
