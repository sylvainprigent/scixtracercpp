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

QJsonObject SxRequestLocal::read_json(const QString& filename)
{
    QFile loadFile(filename);

    if (!loadFile.open(QIODevice::ReadOnly)) {
        throw SxException(QString("Could not open the file (for reading): " + filename).toStdString().c_str());
    }

    QByteArray filecontent = loadFile.readAll();
    QJsonDocument filecontentjson = QJsonDocument::fromJson(filecontent);
    return filecontentjson.object();
}

void SxRequestLocal::write_json(QJsonObject object, const QString& filename)
{
    QFile jsonFile(filename);
    if (!jsonFile.open(QFile::WriteOnly)){
        throw SxException(QString("Could not open the file (for writing): " + filename).toStdString().c_str());
    }
    QJsonDocument document(object);
    jsonFile.write(document.toJson());
}

SxRawData* SxRequestLocal::read_rawdata(const QString& md_uri)
{
    QFileInfo file_info(md_uri);
    QString _md_uri = file_info.absoluteFilePath();
    if (QFile::exists(_md_uri) && _md_uri.endsWith(".md.json"))
    {
        qDebug() << "parse the json file";
        QJsonObject metadata = this->read_json(_md_uri);
        SxRawData* container = new  SxRawData();
        QJsonObject common = metadata["common"].toObject();
        container->set_type(common["type"].toString());
        container->set_name(common["name"].toString());
        container->set_author(new SxUser(common["author"].toString()));
        container->set_date(new SxDate(common["date"].toString()));
        container->set_format(new SxFormat(common["format"].toString()));
        // copy the url if absolute, append md_uri path otherwise
        container->set_uri(this->absolute_path(this->normalize_path_sep(common["url"].toString()), _md_uri));
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
        container->set_md_uri(_md_uri);
        return container;
    }
    throw SxException("Metadata file format not supported");
}

void SxRequestLocal::write_rawdata(SxRawData* container, const QString& md_uri)
{
    QFileInfo file_info(md_uri);
    QString _md_uri = file_info.absoluteFilePath();
    QJsonObject metadata;

    QJsonObject origin;
    origin["type"] = "raw";
    metadata["origin"] = origin;

    QJsonObject common;
    common["name"] = container->get_name();
    common["author"] = container->get_author()->get_username();
    common["format"] = container->get_format()->get_name();
    common["date"] = container->get_date()->get_to_string("YYYY-MM-DD");
    common["url"] = this->to_unix_path(this->relative_path(container->get_uri(), _md_uri));
    metadata["common"] = common;

    QJsonObject json_tags;
    SxTags* _tags = container->get_tags();
    QStringList keys = _tags->get_keys();
    for (qint8 i = 0 ; i < keys.count() ; ++i)
    {
        json_tags[keys[i]] = _tags->get_tag(keys[i]);
    }
    metadata["tags"] = json_tags;

    this->write_json(metadata, _md_uri);
}

SxProcessedData* SxRequestLocal::read_processeddata(const QString& md_uri)
{
    QFileInfo file_info(md_uri);
    QString _md_uri = file_info.absoluteFilePath();
    if (QFile::exists(_md_uri) and _md_uri.endsWith(".md.json"))
    {
        QJsonObject metadata = this->read_json(_md_uri);
        SxProcessedData* container = new SxProcessedData();
        QJsonObject common = metadata["common"].toObject();
        container->set_name(common["name"].toString());
        container->set_author(new SxUser(common["author"].toString()));
        container->set_date(new SxDate(common["date"].toString()));
        container->set_format(new SxFormat(common["format"].toString()));
        container->set_uri(this->absolute_path(this->normalize_path_sep(common["url"].toString()), _md_uri));
        // origin run
        QJsonObject origin = metadata["origin"].toObject();
        container->set_run_uri(this->absolute_path(this->normalize_path_sep(origin["runurl"].toString()), _md_uri));
        // origin input
        QJsonArray inputs_ = origin["inputs"].toArray();
        for (qint8 i = 0 ; i < inputs_.count() ; ++i)
        {
            QJsonObject input = inputs_[i].toObject();
            SxProcessedDataInput* input_data = new SxProcessedDataInput();
            input_data->set_name(input["name"].toString());
            input_data->set_uri(this->absolute_path(this->normalize_path_sep(input["url"].toString()), _md_uri));
            input_data->set_type(input["type"].toString());
            container->set_run_input(input["name"].toString(), input_data);
        }
        // origin
        QJsonObject output = origin["output"].toObject();
        if (output.contains("name") && output.contains("label"))
        {
            SxProcessedDataOutput* poutput = new SxProcessedDataOutput();
            poutput->set_name(output["name"].toString());
            poutput->set_label(output["label"].toString());
            container->set_run_output(poutput);
        }
        container->set_md_uri(_md_uri);
        return container;
    }
    throw SxException("Metadata file format not supported");
}

void SxRequestLocal::write_processeddata(SxProcessedData* container, const QString& md_uri)
{
    QFileInfo file_info(md_uri);
    QString _md_uri = file_info.absoluteFilePath();
    QJsonObject metadata;
     // common
    QJsonObject common;
    common["name"] = container->get_name();
    common["author"] = container->get_author()->get_username();
    common["date"] = container->get_date()->get_to_string("YYYY-MM-DD");
    common["format"] = container->get_format()->get_name();
    common["url"] = this->to_unix_path(this->relative_path(container->get_uri(), _md_uri));
    metadata["common"] = common;
    // origin type
    QJsonObject origin;
    origin["type"] = "processed";
    // run url
    origin["runurl"] = this->to_unix_path(this->relative_path(container->get_run_uri(), _md_uri));
    // origin inputs
    QJsonArray inputs_json;
    for (qint8 i = 0 ; i < container->get_run_inputs_count() ; ++i)
    {
        SxProcessedDataInput* input_data = container->get_run_input(i);
        QJsonObject input_json;
        input_json["name"] = input_data->get_name();
        input_json["url"] = this->to_unix_path(this->relative_path(input_data->get_uri(), _md_uri));
        input_json["type"] = input_data->get_type();
        inputs_json.append(input_json);
    }
    origin["inputs"] = inputs_json;
    // origin ouput
    QJsonObject output_json;
    output_json["name"] = container->get_run_output()->get_name();
    output_json["label"] = container->get_run_output()->get_label();
    origin["output"] = output_json;
    metadata["origin"] = origin;

    this->write_json(metadata, _md_uri);
}

SxDataset* SxRequestLocal::read_rawdataset(const QString& md_uri)
{
    QFileInfo file_info(md_uri);
    QString _md_uri = file_info.absoluteFilePath();
    if (QFile::exists(_md_uri) && _md_uri.endsWith(".md.json"))
    {
        QJsonObject metadata = this->read_json(_md_uri);
        SxDataset* container = new SxDataset();
        container->set_name(metadata["name"].toString());
        QJsonArray urls_json = metadata["urls"].toArray();
        for (qint8 i = 0 ; i < urls_json.count(); ++i)
        {
            container->set_data(this->absolute_path(this->normalize_path_sep(urls_json[i].toString()), _md_uri));
        }
        container->set_md_uri(_md_uri);
        return container;
    }
    throw SxException("Metadata file format not supported");
}

void SxRequestLocal::write_rawdataset(SxDataset* container, const QString& md_uri)
{
    QFileInfo file_info(md_uri);
    QString _md_uri = file_info.absoluteFilePath();

    QJsonObject metadata;
    metadata["name"] = container->get_name();
    QJsonArray urls_json;
    for (qint8 i = 0 ; i < container->get_data_count() ; ++i)
    {
        urls_json.append(this->to_unix_path(this->relative_path(container->get_data_uri(i), _md_uri)));
    }
    metadata["urls"] = urls_json;
    this->write_json(metadata, _md_uri);
}

SxDataset* SxRequestLocal::read_processeddataset(const QString& md_uri)
{
    QFileInfo file_info(md_uri);
    QString _md_uri = file_info.absoluteFilePath();
    if (QFile::exists(_md_uri) && _md_uri.endsWith(".md.json"))
    {
        QJsonObject metadata = this->read_json(_md_uri);
        SxDataset* container = new SxDataset();
        container->set_name(metadata["name"].toString());
        QJsonArray urls_json = metadata["urls"].toArray();
        for (qint8 i = 0 ; i < urls_json.count(); ++i)
        {
            container->set_data(this->absolute_path(this->normalize_path_sep(urls_json[i].toString()), _md_uri));
        }
        container->set_md_uri(_md_uri);
        return container;
    }
    throw SxException("Metadata file format not supported");
}

void SxRequestLocal::write_processeddataset(SxDataset* container, const QString& md_uri)
{
    QFileInfo file_info(md_uri);
    QString _md_uri = file_info.absoluteFilePath();

    QJsonObject metadata;
    metadata["name"] = container->get_name();
    QJsonArray urls_json;
    for (qint8 i = 0 ; i < container->get_data_count() ; ++i)
    {
        urls_json.append(this->to_unix_path(this->relative_path(container->get_data_uri(i), _md_uri)));
    }
    metadata["urls"] = urls_json;
    this->write_json(metadata, _md_uri);
}

QString SxRequestLocal::add_run_processeddataset(SxRun* run, const QString& dataset_md_uri)
{
    // create run URI
    QFileInfo file_info(dataset_md_uri);
    QString _dataset_md_uri = file_info.absoluteFilePath();
    QString dataset_dir = this->md_file_path(_dataset_md_uri);
    QString run_md_file_name = "run.md.json";
    qint8 runid_count = 0;
    while (QFile::exists(this->path_join(dataset_dir, run_md_file_name)))
    {
        runid_count += 1;
        run_md_file_name = "run_" + QString::number(runid_count) + ".md.json";
    }
    QString run_uri = this->path_join(dataset_dir, run_md_file_name);

    // write run
    this->write_run(run, run_uri);
    return run_uri;
}

SxDataset* SxRequestLocal::create_processed_dataset(const QString& name, const QString& experiment_md_uri)
{
    // create the dataset metadata
    QFileInfo file_info(experiment_md_uri);
    QString _experiment_md_uri = file_info.absoluteFilePath();
    QString experiment_dir = this->md_file_path(_experiment_md_uri);
    QString dataset_dir = this->path_join(experiment_dir, name);
    QDir dataset_qdir(dataset_dir);
    if (!dataset_qdir.exists())
    {
        dataset_qdir.mkdir(dataset_dir);
    }
    QString processeddataset_uri = this->path_join(this->path_join(experiment_dir, name), "processeddataset.md.json");

    SxDataset *container = new SxDataset();
    container->set_md_uri(processeddataset_uri);
    container->set_name(name);
    this->write_processeddataset(container, processeddataset_uri);

    //print("experiment at:", experiment_md_uri);
    //print("create the processed dataset at:", processeddataset_uri);

    // add the dataset to the experiment
    SxExperiment* experiment_container = this->read_experiment(_experiment_md_uri);
    experiment_container->set_processed_dataset(this->to_unix_path(processeddataset_uri));
    this->write_experiment(experiment_container, _experiment_md_uri);

    return container;
}

void SxRequestLocal::create_data_processeddataset(SxProcessedData* container, const QString& md_uri)
{
    QFileInfo file_info(md_uri);
    QString _md_uri = file_info.absoluteFilePath();
    QString dataset_dir = this->md_file_path(_md_uri);

    // create the data metadata
    QString data_md_file = this->path_join(dataset_dir, container->get_name() + ".md.json");
    container->set_uri(this->path_join(dataset_dir, container->get_name() + '.' + container->get_format()->get_name()));

    this->write_processeddata(container, data_md_file);

    // add the data to the dataset
    SxDataset* dataset_container = this->read_processeddataset(_md_uri);
    dataset_container->set_data(data_md_file);
    this->write_processeddataset(dataset_container, _md_uri);
}

SxExperiment* SxRequestLocal::read_experiment(const QString& md_uri)
{
    QFileInfo file_info(md_uri);
    QString _md_uri = file_info.absoluteFilePath();
    if (QFile::exists(_md_uri))
    {
        QJsonObject metadata = this->read_json(_md_uri);
        SxExperiment *container = new SxExperiment();
        QJsonObject information = metadata["information"].toObject();
        container->set_name(information["name"].toString());
        container->set_author(new SxUser(information["author"].toString()));
        container->set_date(new SxDate(information["date"].toString()));
        container->set_raw_dataset(this->absolute_path(this->normalize_path_sep(metadata["rawdataset"].toString()), _md_uri));

        QJsonArray pdatasets = metadata["processeddatasets"].toArray();
        for (qint8 i = 0 ; i < pdatasets.count() ; ++i)
        {
            QString dataset = pdatasets[i].toString();
            container->set_processed_dataset(this->absolute_path(this->normalize_path_sep(dataset),_md_uri));
        }
        QJsonArray jtags = metadata["tags"].toArray();
        for (qint8 i = 0 ; i < jtags.count() ; ++i)
        {
            container->set_tag_key(jtags[i].toString());
        }
        return container;
    }
    throw SxException(("Cannot read the experiment at " + md_uri).toStdString().c_str());
}

void SxRequestLocal::write_experiment(SxExperiment* container, const QString& md_uri)
{
    QFileInfo file_info(md_uri);
    QString _md_uri = file_info.absoluteFilePath();
    QJsonObject metadata;
    QJsonObject information;
    information["name"] = container->get_name();
    information["author"] = container->get_author()->get_username();
    information["date"] = container->get_date()->get_to_string("YYYY-MM-DD");
    metadata["information"] = information;
    metadata["rawdataset"] = this->to_unix_path(this->relative_path(container->get_raw_dataset(), _md_uri));

    QJsonArray jprocesseddatasets;
    for (qint8 i = 0 ; i < container->get_processed_datasets_count() ; ++i)
    {
        QString dataset = container->get_processed_dataset(i);
        jprocesseddatasets.append(to_unix_path(relative_path(dataset, _md_uri)));
    }
    metadata["processeddatasets"] = jprocesseddatasets;
    QJsonArray jtags;
    for (qint8 i = 0 ; i < container->get_tags_keys_count() ; ++i)
    {
        jtags.append(container->get_tags_key(i));
    }
    metadata["tags"] = jtags;
    this->write_json(metadata, _md_uri);
}

void SxRequestLocal::create_experiment(SxExperiment* container, const QString& uri)
{
    // check the destination dir
    QFileInfo file_info(uri);
    QString _uri = file_info.absoluteFilePath();
    if ( !QFile::exists(_uri)){
        throw SxException("Cannot create Experiment: the destination directory does not exists");
    }

    // create the experiment directory
    QString filtered_name = container->get_name().replace(" ", "");
    QString experiment_path = this->path_join(_uri, filtered_name);
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
    container->set_raw_dataset(rawdataset_md_url);
    QDir raw_data_dir(rawdata_path);
    if (!raw_data_dir.exists()){
        raw_data_dir.mkdir(rawdata_path);
    }
    else
    {
        throw SxException("Cannot create Experiment raw dataset: the experiment directory does not exists");
    }

    SxDataset* rawdataset = new SxDataset();
    rawdataset->set_md_uri(rawdataset_md_url);
    rawdataset->set_name("data");
    this->write_rawdataset(rawdataset, rawdataset_md_url);

    // save the experiment.md.json metadata file
    QString md_uri = this->path_join(experiment_path, "experiment.md.json");
    container->set_md_uri(md_uri);
    this->write_experiment(container, md_uri);
}

QString SxRequestLocal::import_data(const QString& data_path, const QString& rawdataset_uri, SxRawData* metadata, bool copy)
{
    QFileInfo file_info(rawdataset_uri);
    QString _rawdataset_uri = file_info.absoluteFilePath();
    QString data_dir_path = file_info.absolutePath();

    // create the new data uri
    QFileInfo data_file_info(data_path);
    QString data_base_name = data_file_info.baseName();
    QString filtered_name = data_base_name.replace(" " , "");
    QString md_uri = this->path_join(data_dir_path, filtered_name + ".md.json");

    // import data
    if (copy){
        QString copied_data_path = this->path_join(data_dir_path, data_base_name);
        QFile copyfile(data_path);
        copyfile.copy(copied_data_path);
        metadata->set_uri(copied_data_path);
    }
    else
    {
        metadata->set_uri(data_path);
    }
    metadata->set_md_uri(md_uri);
    this->write_rawdata(metadata, md_uri);

    // add data to experiment RawDataSet
    SxDataset* rawdataset_container = this->read_rawdataset(rawdataset_uri);
    rawdataset_container->set_data(md_uri);
    this->write_rawdataset(rawdataset_container, rawdataset_uri);

    return md_uri;
}

SxRun* SxRequestLocal::read_run(const QString& md_uri)
{
    QFileInfo file_info(md_uri);
    QString _md_uri = file_info.absoluteFilePath();
    if (QFile::exists(_md_uri))
    {
        QJsonObject metadata = this->read_json(md_uri);
        SxRun* container = new SxRun();
        container->set_md_uri(_md_uri);

        QJsonObject json_process = metadata["process"].toObject();
        container->set_process_name(json_process["name"].toString());
        container->set_process_uri(json_process["url"].toString());

        container->set_processed_dataset(metadata["processeddataset"].toString());
        QJsonArray json_inputs = metadata["inputs"].toArray();
        for (qint8 i = 0 ; i < json_inputs.count() ; ++i){
            QJsonObject json_input = json_inputs[i].toObject();
            SxRunInput *input = new SxRunInput(json_input["name"].toString(),
                                               json_input["dataset"].toString(),
                                               json_input["query"].toString(),
                                               json_input["origin_output_name"].toString());
            container->set_input(input);
        }
        QJsonArray json_parameters = metadata["parameters"].toArray();
        for (qint8 i = 0 ; i < json_parameters.count() ; ++i)
        {
            QJsonObject json_parameter = json_parameters[i].toObject();
            SxRunParameter* parameter = new SxRunParameter(json_parameter["name"].toString(),
                                                           json_parameter["value"].toString());
            container->set_parameter(parameter);

        }
        return container;
    }
    throw SxException("The run metadata at the given URI does not exists");
}

void SxRequestLocal::write_run(SxRun* container, const QString& md_uri)
{
    QFileInfo file_info(md_uri);
    QString _md_uri = file_info.absoluteFilePath();

    QJsonObject json_metadata;
    QJsonObject json_process;
    json_process["name"] = container->get_process_name();
    json_process["url"] = this->to_unix_path(container->get_process_uri());
    json_metadata["process"] = json_process;

    json_metadata["processeddataset"] = container->get_processed_dataset();

    QJsonArray json_inputs;
    for (qint8 i = 0 ; i < container->get_inputs_count() ; ++i){
        QJsonObject json_input;
        SxRunInput* input = container->get_input(i);
        json_input["name"] = input->get_name();
        json_input["dataset"] = input->get_dataset();
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

    this->write_json(json_metadata, _md_uri);
}

QStringList SxRequestLocal::query_rep(const QString& repository_uri, const QString& filter_)
{
    QDir dir(repository_uri);
    QFileInfoList entries = dir.entryInfoList( QDir::NoDotAndDotDot | QDir::Files );

    qint8 count = 0;
    QStringList out_uris;
    foreach ( QFileInfo entryInfo, entries )
    {
        QString path = entryInfo.absoluteFilePath();
        count++;

        QRegularExpression re(filter_);
        QRegularExpressionMatch match = re.match(path);
        bool hasMatch = match.hasMatch(); // true
        if (hasMatch){
            out_uris.append(path);
        }
    }
    return out_uris;
}

QString SxRequestLocal::create_output_uri(const QString& output_rep_uri, const QString& output_name, const QString& format_, const QString& corresponding_input_uri)
{
    QString _output_rep_uri = output_rep_uri;
    QFileInfo input_file_info(corresponding_input_uri);
    if (_output_rep_uri == ""){
        _output_rep_uri = input_file_info.absolutePath();
    }
    QString input_name = input_file_info.baseName();
    QString output_uri = this->path_join(output_rep_uri, output_name + "_" + input_name + "." + format_);

    if (QFile::exists(output_uri)){
        QFile file(output_uri);
        file.remove();
    }
    return output_uri;
}

QString SxRequestLocal::path_join(QString path1, QString path2)
{
    if (path1.endsWith(QDir::separator()))
    {
        return path1 + path2;
    }
    return path1 + QDir::separator() + path2;
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

QString SxRequestLocal::absolute_path(const QString& file, const QString &reference_file)
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


QString SxRequestLocal::normalize_path_sep(const QString &path)
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
