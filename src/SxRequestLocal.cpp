/// \file SxRequestLocal.cpp
/// \brief SxRequestLocal class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include "SxRequestLocal.h"
#include "SxException.h"
#include "SxDataset.h"

#include <QDir>
#include <QFileInfo>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QRegularExpression>


SxRequestLocal::SxRequestLocal()
{

}

SxRequestLocal::~SxRequestLocal()
{

}

SxExperiment* SxRequestLocal::create_experiment(const QString& name, const QString &author, SxDate* date, const QStringList& tag_keys, const QString& destination)
{

    SxExperiment* container = new SxExperiment();
    container->set_uuid(this->_generate_uuid());
    container->set_name(name);
    container->set_author(author);
    container->set_date(date);
    container->set_tag_keys(tag_keys);

    // check the destination dir
    QFileInfo f_info(destination);
    QString uri = f_info.absoluteFilePath();
    if (!QFile::exists(uri)){
        throw SxException("Cannot create Experiment: the destination directory does not exists");
    }

    // create the experiment directory
    QString filtered_name = name;
    filtered_name = filtered_name.replace(" ", "");
    QString experiment_path = this->path_join(uri, filtered_name);
    QDir exp_dir(experiment_path);
    if (!exp_dir.exists())
    {
        exp_dir.mkdir(experiment_path);
    }
    else{
        throw SxException("Cannot create Experiment: the experiment directory already exists");
    }

    // create an empty raw dataset
    QString rawdata_path = this->path_join(experiment_path, "data");
    QString rawdataset_md_url = this->path_join(rawdata_path, "rawdataset.md.json");
    QDir raw_data_dir(rawdata_path);
    if (!raw_data_dir.exists()){
        raw_data_dir.mkdir(rawdata_path);
    }
    else
    {
        throw SxException("Cannot create Experiment raw dataset: the experiment directory does not exists");
    }

    SxDataset* rawdataset = new SxDataset();
    rawdataset->set_uuid(this->_generate_uuid());
    rawdataset->set_md_uri(rawdataset_md_url);
    rawdataset->set_name("data");
    this->update_dataset(rawdataset);
    container->set_raw_dataset(new SxDatasetMetadata(rawdataset->get_name(), rawdataset_md_url, rawdataset->get_uuid()));

    // save the experiment.md.json metadata file
    container->set_md_uri(this->path_join(experiment_path, "experiment.md.json"));
    this->update_experiment(container);
    return container;
}

SxExperiment* SxRequestLocal::get_experiment(const QString uri)
{
    QString md_uri = this->abspath(uri);
    if (QFile::exists(md_uri))
    {
        QJsonObject metadata = this->_read_json(md_uri);
        SxExperiment* container = new SxExperiment();
        container->set_uuid(metadata["uuid"].toString());
        container->set_md_uri(md_uri);

        QJsonObject information = metadata["information"].toObject();
        container->set_name(information["name"].toString());
        container->set_author(information["author"].toString());
        container->set_date(new SxDate(information["date"].toString()));

        QJsonObject json_rawdataset = metadata["rawdataset"].toObject();
        QString rawdataset_url = this->absolute_path(this->normalize_path_sep(json_rawdataset["url"].toString()), md_uri);
        container->set_raw_dataset(new SxDatasetMetadata(json_rawdataset["name"].toString(), rawdataset_url, json_rawdataset["uuid"].toString()));

        QJsonArray json_processeddatasets = metadata["processeddatasets"].toArray();
        for (qint32 i = 0 ; i < json_processeddatasets.count() ; ++i)
        {
            QJsonObject dataset = json_processeddatasets[i].toObject();
            QString processeddataset_url = this->absolute_path(this->normalize_path_sep(dataset["url"].toString()), md_uri);
            container->set_processed_dataset(new SxDatasetMetadata(dataset["name"].toString(), processeddataset_url, dataset["uuid"].toString()));
        }
        QJsonArray json_tags = metadata["tags"].toArray();
        for (qint32 i = 0 ; i < json_tags.count() ; ++i)
        {
            QString key = json_tags[i].toString();
            container->set_tag_key(key);
        }
        return container;
    }
    throw SxException(("Cannot read the experiment at " + md_uri).toStdString().c_str());
}

void SxRequestLocal::update_experiment(SxExperiment* experiment)
{
    QString md_uri = this->abspath(experiment->get_md_uri());
    QJsonObject metadata;
    metadata["uuid"] = experiment->get_uuid();

    // informations
    QJsonObject information;
    information["name"] = experiment->get_name();
    information["author"] = experiment->get_author();
    information["date"] = experiment->get_date()->get_to_string("YYYY-MM-DD");
    metadata["information"] = information;

    // raw dataset
    QString tmp_url = this->to_unix_path(this->relative_path(experiment->get_raw_dataset()->get_md_uri(), md_uri));
    QJsonObject json_rawdataset;
    json_rawdataset["name"] = experiment->get_raw_dataset()->get_name();
    json_rawdataset["url"] = tmp_url;
    json_rawdataset["uuid"] = experiment->get_raw_dataset()->get_uuid();
    metadata["rawdataset"] = json_rawdataset;

    // processed datasets
    QJsonArray json_pdatasets;
    for (qint32 i = 0 ; i < experiment->get_processed_datasets_count() ; ++i)
    {
        SxDatasetMetadata* pdataset = experiment->get_processed_dataset(i);
        QString tmp_url = this->to_unix_path(this->relative_path(pdataset->get_md_uri(), md_uri));

        QJsonObject json_pdataset;
        json_pdataset["name"] = pdataset->get_name();
        json_pdataset["url"] = tmp_url;
        json_pdataset["uuid"] = pdataset->get_uuid();

        json_pdatasets.append(json_pdataset);
    }
    metadata["processeddatasets"] = json_pdatasets;

    // tags keys
    QJsonArray json_tags;
    for (qint32 i = 0 ; i < experiment->get_tags_keys_count() ; ++i)
    {
        json_tags.append(experiment->get_tags_key(i));
    }
    metadata["tags"] = json_tags;

    // write
    this->_write_json(metadata, md_uri);
}

SxRawData* SxRequestLocal::import_data(SxExperiment* experiment, const QString& data_path, const QString& name, const QString& author, SxFormat* format, SxDate* date, SxTags* tags, bool copy)
{
    QString rawdataset_uri = this->abspath(experiment->get_raw_dataset()->get_md_uri());
    QFileInfo file_info(rawdataset_uri);
    QString data_dir_path = file_info.absolutePath();

    // create the new data uri
    QFileInfo data_file_info(data_path);
    QString data_base_name = data_file_info.baseName();
    QString filtered_name = data_base_name.replace(" ", "");
    QString md_uri = this->path_join(data_dir_path, filtered_name + ".md.json");

    // create the container
    SxRawData* metadata = new SxRawData();
    metadata->set_uuid(this->_generate_uuid());
    metadata->set_md_uri(md_uri);
    metadata->set_name(name);
    metadata->set_author(author);
    metadata->set_format(format);
    metadata->set_date(date);
    metadata->set_tags(tags);

    // import data
    if (copy){
        QString extension;
        if (format->get_name().startsWith(".")){
            extension = format->get_name();
        }
        else{
            extension = "." + format->get_name();
        }
        QString copied_data_path = this->path_join(data_dir_path, data_base_name + extension);
        QFile copyfile(data_path);
        copyfile.copy(copied_data_path);
        metadata->set_uri(copied_data_path);
    }
    else
    {
        metadata->set_uri(data_path);
    }
    this->update_rawdata(metadata);

    // add data to experiment RawDataSet
    SxDataset* rawdataset_container = this->get_dataset_from_uri(rawdataset_uri);
    SxMetadata* raw_c = new SxMetadata(metadata->get_md_uri(), metadata->get_uuid());
    rawdataset_container->set_data(raw_c);
    this->update_dataset(rawdataset_container);

    // add tags keys to experiment
    QStringList keys = tags->get_keys();
    for (qint32 i = 0 ; i < tags->get_count() ; ++i)
    {
        experiment->set_tag_key(keys[i]);
    }
    this->update_experiment(experiment);

    return metadata;
}

SxRawData* SxRequestLocal::get_rawdata(const QString&  uri)
{
    QString md_uri = this->abspath(uri);
    if (QFile::exists(md_uri) && md_uri.endsWith(".md.json"))
    {
        QJsonObject metadata = this->_read_json(md_uri);
        SxRawData* container = new SxRawData();
        container->set_uuid(metadata["uuid"].toString());
        container->set_md_uri(md_uri);
        QJsonObject json_origin =  metadata["origin"].toObject();
        container->set_type(json_origin["type"].toString());

        QJsonObject json_common = metadata["common"].toObject();
        container->set_name(json_common["name"].toString());
        container->set_author(json_common["author"].toString());
        container->set_date(new SxDate(json_common["date"].toString()));
        container->set_format(new SxFormat(json_common["format"].toString()));
        // copy the url if absolute, append md_uri path otherwise
        container->set_uri(this->absolute_path(this->normalize_path_sep(json_common["url"].toString()), md_uri));

        if (metadata.keys().contains("tags"))
        {
            QJsonObject tags = metadata["tags"].toObject();
            QStringList keys = tags.keys();
            SxTags* tags_container = new SxTags();
            for (qint8 i = 0 ; i < keys.count() ; ++i)
            {
                tags_container->set_tag(keys[i], tags[keys[i]].toString());
            }
            container->set_tags(tags_container);
        }
        return container;
    }
    throw(SxException("Metadata file format not supported"));
}

void SxRequestLocal::update_rawdata(SxRawData* rawdata)
{
    QString md_uri = this->abspath(rawdata->get_md_uri());

    QJsonObject metadata;
    metadata["uuid"] = rawdata->get_uuid();

    QJsonObject json_origin;
    json_origin["type"] = "raw";
    metadata["origin"] = json_origin;

    QJsonObject json_common;
    json_common["name"] = rawdata->get_name();
    json_common["author"] = rawdata->get_author();
    json_common["date"] = rawdata->get_date()->get_to_string("YYYY-MM-DD");
    json_common["format"] = rawdata->get_format()->get_name();
    json_common["url"] = this->to_unix_path(this->relative_path(rawdata->get_uri(), md_uri));
    metadata["common"] = json_common;

    QJsonObject json_tags;
    SxTags* _tags = rawdata->get_tags();
    QStringList keys = _tags->get_keys();
    for (qint32 i = 0 ; i < keys.count() ; ++i)
    {
        json_tags[keys[i]] = _tags->get_tag(keys[i]);
    }
    metadata["tags"] = json_tags;

    this->_write_json(metadata, md_uri);
}

SxProcessedData* SxRequestLocal::get_processeddata(const QString& uri)
{
    QString md_uri = this->abspath(uri);
    if (QFile::exists(md_uri) and md_uri.endsWith(".md.json"))
    {
        QJsonObject metadata = this->_read_json(md_uri);
        SxProcessedData* container = new SxProcessedData();
        container->set_uuid(metadata["uuid"].toString());
        container->set_md_uri(md_uri);

        QJsonObject json_common = metadata["common"].toObject();
        container->set_name(json_common["name"].toString());
        container->set_author(json_common["author"].toString());
        container->set_date(new SxDate(json_common["date"].toString()));
        container->set_format(new SxFormat(json_common["format"].toString()));
        container->set_uri(this->absolute_path(this->normalize_path_sep(json_common["url"].toString()), md_uri));
        // origin run
        QJsonObject json_run = metadata["origin"].toObject()["run"].toObject();
        container->set_run(new SxMetadata(this->absolute_path(this->normalize_path_sep(json_run["url"].toString()), md_uri), json_run["uuid"].toString()));
        // origin input
        QJsonArray json_inputs = metadata["origin"].toObject()["inputs"].toArray();
        for(qint32 i = 0 ; i < json_inputs.count() ; ++i)
        {
            QJsonObject json_input = json_inputs[i].toObject();
            container->set_run_input(json_input["name"].toString(),
                                     new SxProcessedDataInput(
                                            json_input["name"].toString(),
                                            new SxMetadata(this->absolute_path(this->normalize_path_sep(json_input["url"].toString()), md_uri), json_input["uuid"].toString()),
                                            json_input["type"].toString()
                                        ));
        }

        // origin output
        QJsonObject json_output = metadata["origin"].toObject()["output"].toObject();
        if (json_output.contains("name") && json_output.contains("label"))
        {
            SxProcessedDataOutput* poutput = new SxProcessedDataOutput();
            poutput->set_name(json_output["name"].toString());
            poutput->set_label(json_output["label"].toString());
            container->set_run_output(poutput);
        }
        return container;
    }
    throw(SxException("Metadata file format not supported"));
}

void SxRequestLocal::update_processeddata(SxProcessedData* processeddata)
{
    QString md_uri = this->abspath(processeddata->get_md_uri());
    QJsonObject metadata;
    metadata["uuid"] = processeddata->get_uuid();

    // common
    QJsonObject json_common;
    json_common["name"] = processeddata->get_name();
    json_common["author"] = processeddata->get_author();
    json_common["date"] = processeddata->get_date()->get_to_string("YYYY-MM-DD");
    json_common["format"] = processeddata->get_format()->get_name();
    json_common["url"] = this->to_unix_path(this->relative_path(processeddata->get_uri(), md_uri));
    metadata["common"] = json_common;

    // origin type
    QJsonObject json_origin;
    json_origin["type"] = "processed";


    // run url
    QString run_url = this->to_unix_path(this->relative_path(processeddata->get_run()->get_md_uri(), md_uri));
    QJsonObject json_run;
    json_run["url"] = run_url;
    json_run["uuid"] = processeddata->get_run()->get_uuid();
    json_origin["run"] = json_run;

    // origin inputs
    QJsonArray json_inputs;
    for (qint32 i = 0 ; i < processeddata->get_run_inputs_count() ; ++i)
    {
        SxProcessedDataInput* input_ = processeddata->get_run_input(i);
        QJsonObject json_input;
        json_input["name"] = input_->get_name();
        json_input["url"] = this->to_unix_path(this->relative_path(input_->get_data()->get_md_uri(), md_uri));
        json_input["uuid"] = input_->get_data()->get_uuid();
        json_input["type"] = input_->get_type();
        json_inputs.append(json_input);
    }
    json_origin["inputs"] = json_inputs;

    // origin ouput
    QJsonObject json_output;
    json_output["name"] = processeddata->get_run_output()->get_name();
    json_output["label"] = processeddata->get_run_output()->get_label();
    json_origin["output"] = json_output;

    metadata["origin"] = json_origin;
    this->_write_json(metadata, md_uri);
}

SxDataset* SxRequestLocal::get_dataset_from_uri(const QString& uri)
{
    QString md_uri = this->abspath(uri);
    if (QFile::exists(md_uri) && md_uri.endsWith(".md.json"))
    {
        QJsonObject metadata = this->_read_json(md_uri);
        SxDataset* container = new SxDataset();
        container->set_uuid(metadata["uuid"].toString());
        container->set_md_uri(md_uri);
        container->set_name(metadata["name"].toString());
        QJsonArray json_datas = metadata["urls"].toArray();
        for (qint32 i = 0 ; i < json_datas.count(); ++i)
        {
            QJsonObject json_data = json_datas[i].toObject();
            container->set_data(new SxMetadata(this->absolute_path(this->normalize_path_sep(json_data["url"].toString()), md_uri), json_data["uuid"].toString()));
        }
        return container;
    }
    throw(SxException("Dataset not found"));
}

void SxRequestLocal::update_dataset(SxDataset* dataset)
{
    QString md_uri = this->abspath(dataset->get_md_uri());
    QJsonObject metadata;
    metadata["uuid"] = dataset->get_uuid();
    metadata["name"] = dataset->get_name();

    QJsonArray json_urls;
    for (qint32 i = 0 ; i < dataset->get_data_count() ; ++i)
    {
        SxMetadata* data = dataset->get_data(i);
        QJsonObject json_data;
        json_data["url"] = this->to_unix_path(this->relative_path(data->get_md_uri(), md_uri));
        json_data["uuid"] = data->get_uuid();
        json_urls.append(json_data);
    }
    metadata["urls"] = json_urls;
    this->_write_json(metadata, md_uri);
}

SxDataset* SxRequestLocal::create_dataset(SxExperiment* experiment, const QString& dataset_name)
{
    // create the dataset metadata
    QString experiment_md_uri = this->abspath(experiment->get_md_uri());
    QString experiment_dir = this->md_file_path(experiment_md_uri);
    QString dataset_dir = this->path_join(experiment_dir, dataset_name);
    QDir dataset_qdir(dataset_dir);
    if (!dataset_qdir.exists()){
        dataset_qdir.mkdir(dataset_dir);
    }
    QString processeddataset_uri = this->path_join(this->path_join(experiment_dir, dataset_name), "processeddataset.md.json");
    SxDataset* container = new SxDataset();
    container->set_uuid(this->_generate_uuid());
    container->set_md_uri(processeddataset_uri);
    container->set_name(dataset_name);
    this->update_dataset(container);

    // add the dataset to the experiment
    QString tmp_url = this->to_unix_path(processeddataset_uri);
    experiment->set_processed_dataset(new SxDatasetMetadata(dataset_name, tmp_url, container->get_uuid()));
    this->update_experiment(experiment);

    return container;
}

SxRun* SxRequestLocal::create_run(SxDataset* dataset, SxRun* run_info)
{
    // create run URI
    QString dataset_md_uri = this->abspath(dataset->get_md_uri());
    QString dataset_dir = this->md_file_path(dataset_md_uri);
    QString run_md_file_name = "run.md.json";
    qint32 runid_count = 0;

    while (QFile::exists(this->path_join(dataset_dir, run_md_file_name)))
    {
        runid_count += 1;
        run_md_file_name = "run_" + QString::number(runid_count) + ".md.json";
    }
    QString run_uri = this->path_join(dataset_dir, run_md_file_name);

    // write run
    run_info->set_processed_dataset(new SxMetadata(dataset->get_md_uri(), dataset->get_uuid()));
    run_info->set_uuid(this->_generate_uuid());
    run_info->set_md_uri(run_uri);
    this->_write_run(run_info);
    return run_info;
}

SxRun* SxRequestLocal::get_run(const QString& uri)
{
    QString md_uri = this->abspath(uri);
    qDebug() << "read run from "<< md_uri;
    if (QFile::exists(md_uri))
    {
        QJsonObject metadata = this->_read_json(md_uri);
        SxRun* container = new SxRun();
        container->set_uuid(metadata["uuid"].toString());
        container->set_md_uri(md_uri);

        // process info
        QJsonObject json_process = metadata["process"].toObject();
        container->set_process_name(json_process["name"].toString());
        container->set_process_uri(this->normalize_path_sep(json_process["url"].toString()));

        // processed dataset
        QJsonObject json_processeddataset = metadata["processeddataset"].toObject();
        container->set_processed_dataset(new SxMetadata(this->absolute_path(this->normalize_path_sep(json_processeddataset["url"].toString()), md_uri),
                                                        json_processeddataset["uuid"].toString()));

        // inputs
        QJsonArray json_inputs = metadata["inputs"].toArray();
        for (qint32 i = 0 ; i < json_inputs.count() ; ++i)
        {
            QJsonObject json_input = json_inputs[i].toObject();
            container->set_input(
                new SxRunInput(
                    json_input["name"].toString(),
                    json_input["dataset"].toString(),
                    json_input["query"].toString(),
                    json_input["origin_output_name"].toString()
                )
            );
        }

        // parameter
        QJsonArray json_parameters = metadata["parameters"].toArray();
        for (qint32 i = 0 ; i < json_parameters.count() ; ++i)
        {
            QJsonObject json_parameter = json_parameters[i].toObject();
            container->set_parameter(new SxRunParameter(json_parameter["name"].toString(), json_parameter["value"].toString()));
        }
        return container;
    }
    throw(SxException("Run not found"));
}

SxProcessedData* SxRequestLocal::create_data(SxDataset* dataset, SxRun* run, SxProcessedData* processed_data)
{
    QString md_uri = this->abspath(dataset->get_md_uri());
    QString dataset_dir = this->md_file_path(md_uri);

    // create the data metadata
    QString data_md_file = this->path_join(dataset_dir, processed_data->get_name()+ ".md.json");
    processed_data->set_uuid(this->_generate_uuid());
    processed_data->set_md_uri(data_md_file);

    processed_data->set_run(new SxMetadata(run->get_md_uri(), run->get_uuid()));

    this->update_processeddata(processed_data);

    // add the data to the dataset
    dataset->set_data(new SxMetadata(data_md_file, processed_data->get_uuid()));
    this->update_dataset(dataset);

    return processed_data;
}

void SxRequestLocal::_write_run(SxRun* run)
{
    QJsonObject metadata;
    metadata["uuid"] = run->get_uuid();

    // process
    QJsonObject json_process;
    json_process["name"] = run->get_process_name();
    json_process["url"] = this->to_unix_path(run->get_process_uri());
    metadata["process"] = json_process;

    // processed dataset
    QJsonObject json_pdataset;
    json_pdataset["uuid"] = run->get_processed_dataset()->get_uuid();
    json_pdataset["url"] = this->to_unix_path(this->relative_path(run->get_processed_dataset()->get_md_uri(), run->get_md_uri()));
    metadata["processeddataset"] = json_pdataset;

    // inputs
    QJsonArray json_inputs;
    for (qint32 i = 0 ; i < run->get_inputs_count() ; ++i)
    {
        SxRunInput* input_ = run->get_input(i);
        QJsonObject json_input;
        json_input["name"] = input_->get_name();
        json_input["dataset"] = input_->get_dataset_name();
        json_input["query"] = input_->get_query();
        json_input["origin_output_name"] =  input_->get_origin_output_name();
        json_inputs.append(json_input);
    }
    metadata["inputs"] =  json_inputs;

    // parameters
    QJsonArray json_parameters;
    for (qint32 i = 0 ; i < run->get_parameters_count() ; ++i)
    {
        SxRunParameter* param = run->get_parameter(i);
        QJsonObject json_param;
        json_param["name"] = param->get_name();
        json_param["value"] = param->get_value();
        json_parameters.append(json_param);
    }
    metadata["parameters"] = json_parameters;
    this->_write_json(metadata, run->get_md_uri());
}

QString SxRequestLocal::_generate_uuid()
{
    QString uuid = QUuid::createUuid().toString();
    return uuid.replace("{", "").replace("}", "");
}

QJsonObject SxRequestLocal::_read_json(const QString& filename)
{
    QFile loadFile(filename);

    if (!loadFile.open(QIODevice::ReadOnly)) {
        throw SxException(QString("Could not open the file (for reading): " + filename).toStdString().c_str());
    }

    QByteArray filecontent = loadFile.readAll();
    QJsonDocument filecontentjson = QJsonDocument::fromJson(filecontent);
    return filecontentjson.object();
}

void SxRequestLocal::_write_json(const QJsonObject& metadata, const QString& filename)
{
    QFile jsonFile(filename);
    if (!jsonFile.open(QFile::WriteOnly)){
        throw SxException(QString("Could not open the file (for writing): " + filename).toStdString().c_str());
    }
    QJsonDocument document(metadata);
    jsonFile.write(document.toJson());
}

QString SxRequestLocal::md_file_path(const QString& md_uri)
{
    QFileInfo file(md_uri);
    return file.absolutePath();
}

QString SxRequestLocal::relative_path(const QString& file, const QString& reference_file)
{
    QString file_ = file;
    QString reference_file_ = reference_file;
    QString separator = QString(QDir::separator());
    file_ = file_.replace(separator + separator, separator);
    reference_file_ = reference_file_.replace(separator + separator, separator);

    QString common_part;
    for (qint16 i = 0 ; i < reference_file_.count() ; i++)
    {
        common_part = reference_file_.left(i);
        if (!file_.contains(common_part)){
            common_part = reference_file_.left(i-1);
            break;
        }
    }

    //qDebug() << "common part:" << common_part;

    qint16 last_separator = common_part.lastIndexOf(separator);
    QString short_reference_file = reference_file_.right(reference_file_.count() - (last_separator+1));
    //qDebug() << "short_reference_file:" << short_reference_file;

    qint16 number_of_sub_folder = short_reference_file.count(separator);
    //qDebug() << "number_of_sub_folder:" << number_of_sub_folder;
    QString short_file = file.right(file.count() - (last_separator + 1));
    //qDebug() << "short_file:" << short_file;
    for (qint16 i = 0 ; i < number_of_sub_folder ; i++){
        short_file = ".." + separator + short_file;
    }

    return short_file;
}

QString SxRequestLocal::absolute_path(const QString& file, const QString& reference_file)
{
    if (QFile::exists(file)){
        QFileInfo f_info(file);
        return f_info.absoluteFilePath();
    }

    qint16 last_separator = reference_file.lastIndexOf(QDir::separator());
    QString canonical_path = reference_file.left(last_separator+1);
    return SxRequestLocal::simplify_path(canonical_path + file);
}

QString SxRequestLocal::simplify_path(const QString& path)
{
    if (path.indexOf("..") < 0){
        return path;
    }

    QStringList keep_folders = path.split(QDir::separator());

    bool found = true;
    QStringList folders = keep_folders;
    while (found)
    {
        qint16 pos = -1;
        folders = keep_folders;
        for (qint16 i=0 ; i<folders.count() ; ++i)
        {
            if (folders[i] == "..")
            {
                pos = i;
                break;
            }
        }
        if (pos > -1)
        {
            keep_folders = {};

            for (qint16 i = 0 ; i < pos-1 ; ++i)
            {
                keep_folders.append(folders[i]);
            }
            for (qint16 i = pos+1 ; i < folders.count() ; ++i)
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
    for (qint16 i = 0 ; i < keep_folders.count(); ++i )
    {
        clean_path += keep_folders[i];
        if (i < keep_folders.count() - 1)
        {
            clean_path += QDir::separator();
        }
    }
    return clean_path;
}

QString SxRequestLocal::normalize_path_sep(const QString& path)
{
    QString p = path;
    QString p1 = p.replace("/", QDir::separator()).replace("\\\\", QDir::separator());
    return p1;
}

QString SxRequestLocal::to_unix_path(const QString& path)
{
    QString p = path;
    return p.replace("\\\\", "/").replace("\\", "/");
}

QString SxRequestLocal::path_join(QString path1, QString path2)
{
    if (path1.endsWith(QDir::separator()))
    {
        return path1 + path2;
    }
    return path1 + QDir::separator() + path2;
}

QString SxRequestLocal::abspath(const QString& path)
{
    QFileInfo file_info(path);
    return file_info.absoluteFilePath();
}
