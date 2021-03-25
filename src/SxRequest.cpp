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

void SxRequest::import_dir(SxExperiment* experiment, const QString& dir_uri, const QString& filter,
                           const QString& author, SxFormat* format, SxDate* date, bool copy_data)
{
    QDir directory(dir_uri);
    QStringList data_files = directory.entryList(QDir::Files);
    data_files.sort();

    qint32 count = 0;
    for (qint32 i = 0 ; i < data_files.count() ; ++i){
        QString filename = data_files[i];
        count += 1;
        QRegularExpression re(filter);
        QRegularExpressionMatch match = re.match(filename);
        if (match.hasMatch()){
            //this->notify_observers(int(100 * count / data_files.count()), filename)
            QString data_url = dir_uri + QDir::separator() + filename;
            this->import_data(experiment, data_url, filename,
                              author, format, date,
                              new SxTags(), copy_data);
        }
    }
}

void SxRequest::tag_from_name(SxExperiment* experiment, const QString& tag, const QStringList& values)
{
    experiment->set_tag_key(tag);
    this->update_experiment(experiment);
    SxDataset* _rawdataset = this->get_rawdataset(experiment);
    for (qint32 i = 0 ; i < _rawdataset->get_data_count() ; ++i){
        SxRawData* _rawdata = this->get_rawdata(_rawdataset->get_data(i)->get_md_uri());
        for (qint32 j = 0 ; j < values.count() ; j++){
            QString value = values[j];
            if (_rawdata->get_name().contains(value)){
                _rawdata->get_tags()->set_tag(tag, value);
                this->update_rawdata(_rawdata);
                break;
            }
        }
    }
}

void SxRequest::tag_using_separator(SxExperiment* experiment, const QString& tag, const QString& separator, const qint16& value_position)
{
    experiment->set_tag_key(tag);
    this->update_experiment(experiment);
    SxDataset* _rawdataset = this->get_rawdataset(experiment);
    for (qint32 i = 0 ; i < _rawdataset->get_data_count() ; i++)
    {
        SxRawData* _rawdata = this->get_rawdata(_rawdataset->get_data(i)->get_md_uri());
        QFileInfo qt_file(_rawdata->get_uri());
        QStringList splited_name = qt_file.baseName().split(separator);
        QString value = "";
        if (splited_name.count() > value_position){
            value = splited_name[value_position];
        }
        _rawdata->get_tags()->set_tag(tag, value);
        this->update_rawdata(_rawdata);
    }
}

SxData* SxRequest::get_parent(SxProcessedData* processed_data)
{
    if (processed_data->get_run_inputs_count() > 0)
    {
        if (processed_data->get_run_input(0)->get_type() == "raw")
        {
            return this->get_rawdata(processed_data->get_run_input(0)->get_data()->get_md_uri());
        }
        else
        {
            return this->get_processeddata(processed_data->get_run_input(0)->get_data()->get_md_uri());
        }
    }
    return nullptr;
}


SxRawData *SxRequest::get_origin(SxProcessedData* processed_data)
{
    if (processed_data->get_run_inputs_count() > 0)
    {
        if (processed_data->get_run_input(0)->get_type() == "raw"){
            return this->get_rawdata(processed_data->get_run_input(0)->get_data()->get_md_uri());
        }
        else
        {
            return this->get_origin(this->get_processeddata(processed_data->get_run_input(0)->get_data()->get_md_uri()));
        }
    }
    return nullptr;
}

SxDataset* SxRequest::get_dataset(SxExperiment* experiment, const QString& name)
{
    if (name == "data"){
        return this->get_dataset_from_uri(experiment->get_raw_dataset()->get_md_uri());
    }
    else
    {
        for (qint16 i = 0 ; i < experiment->get_processed_datasets_count() ; ++i)
        {
            SxDataset* pdataset = this->get_dataset_from_uri(experiment->get_processed_dataset(i)->get_md_uri());
            if (pdataset->get_name() == name)
            {
                return pdataset;
            }
        }
    }
    return nullptr;
}

SxDataset* SxRequest::get_rawdataset(SxExperiment* experiment)
{
    return this->get_dataset_from_uri(experiment->get_raw_dataset()->get_md_uri());
}

QList<SxData*> SxRequest::get_data(SxDataset* dataset, const QString& query, const QString& origin_output_name)
{

    if (dataset->get_data_count() < 1)
    {
        QList<SxData*> li;
        return li;
    }

    // search the dataset
    QStringList queries = query.split(" AND ");

    // initially all the raw data are selected
    QList<SxSearchContainer*> selected_list;
    // raw dataset
    if (dataset->get_name() == "data")
    {
        for (qint32 i = 0 ; i < dataset->get_data_count() ; ++i)
        {
            SxMetadata* data_info = dataset->get_data(i);
            SxRawData* data_container = this->get_rawdata(data_info->get_md_uri());
            selected_list.append(this->_rawdata_to_search_container(data_container));
        }
    }
    // processed dataset
    else{
        QList<SxSearchContainer*> pre_list;
        for (qint32 i = 0 ; i < dataset->get_data_count() ; ++i)
        {
            SxProcessedData* p_con = this->get_processeddata(dataset->get_data(i)->get_md_uri());
            pre_list.append(this->_processed_data_to_search_container(p_con));
        }
        // remove the data where output origin is not the asked one
        if (origin_output_name != "")
        {
            for (qint32 i = 0 ; i < pre_list.count() ; ++i)
            {
                SxProcessedData* data = this->get_processeddata(pre_list[i]->get_uri());
                if (data->get_run_output()->get_name() == origin_output_name){
                    selected_list.append(pre_list[i]);
                }
            }
        }
        else{
            selected_list = pre_list;
        }
    }
    // run all the AND queries on the preselected dataset
    if (query != "")
    {
        for (qint32 i = 0 ; i < queries.count() ; ++i)
        {
            selected_list = SxSearch::query_list_single(selected_list, queries[i]);
        }
    }

    // convert SearchContainer list to uri list
    QList<SxData*> out;
    for (qint32 i = 0 ; i < selected_list.count() ; ++i)
    {
        SxSearchContainer* d = selected_list[i];
        if (dataset->get_name() == "data")
        {
            out.append(this->get_rawdata(d->get_uri()));
        }
        else
        {
            out.append(this->get_processeddata(d->get_uri()));
        }
    }
    return out;
}


SxSearchContainer* SxRequest::_rawdata_to_search_container(SxRawData* rawdata)
{
    SxSearchContainer* info = new SxSearchContainer(rawdata->get_name(),
                                                    rawdata->get_md_uri(),
                                                    rawdata->get_uuid(),
                                                    rawdata->get_tags());
    return info;
}

SxSearchContainer* SxRequest::_processed_data_to_search_container(SxProcessedData* processeddata)
{

    SxSearchContainer* container;
    try{
        SxRawData* origin = this->get_origin(processeddata);
        if (origin){
            container = this->_rawdata_to_search_container(origin);
        }
        else{
            container = new SxSearchContainer();
        }
    }
    catch (SxException e){
               container = new SxSearchContainer();
    }
    container->set_name(processeddata->get_name());
    container->set_uri(processeddata->get_md_uri());
    container->set_uuid(processeddata->get_uuid());
    return container;
}
