/// \file SxRequestLocal.cpp
/// \brief SxRequestLocal class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include "SxRequestLocal.h"
#include "SxException.h"

#include <QDir>
#include <QFileInfo>
#include <QJsonObject>
#include <QJsonDocument>


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
        QJsonObject metadata = this->read_json(_md_uri);
        SxRawData* container = new  SxRawData();
        QJsonObject common = metadata["common"].toObject();
        container->set_type(common["type"].toString());
        container->set_name(common["name"].toString());
        container->set_author(SxUser(common["author"].toString()));
        container->set_date(SxDate(common["date"].toString()));
        container->set_format(SxFormat(common["format"].toString()));
        // copy the url if absolute, append md_uri path otherwise
        container->set_url(this->absolute_path(this->normalize_path_sep(common["url"].toString()), _md_uri));
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
    common["author"] = container->get_author().get_username();
    common["date"] = container->get_date().get_to_string("YYYY-MM-DD");
    common["format"] = container->get_format().get_name();
    common["url"] = this->to_unix_path(this->relative_path(container->get_url(), _md_uri));
    metadata["common"] = common;

    QJsonObject tags;
    SxTags* _tags = container->get_tags();
    QStringList keys = _tags->get_keys();
    for (qint8 i = 0 ; i < keys.count() ; ++i)
    {
        tags[keys[i]] = _tags->get_tag(keys[i]);
    }

    this->write_json(metadata, _md_uri);
}

SxProcessedData* SxRequestLocal::read_processeddata(const QString& md_uri)
{

}

void SxRequestLocal::write_processeddata(SxProcessedData* container, const QString& md_uri)
{

}

SxDataset* SxRequestLocal::read_rawdataset(const QString& md_uri)
{

}

void SxRequestLocal::write_rawdataset(SxDataset* container, const QString& md_uri)
{

}

SxDataset* SxRequestLocal::read_processeddataset(const QString& md_uri)
{

}

void SxRequestLocal::write_processeddataset(SxDataset* container, const QString& md_uri)
{

}

void SxRequestLocal::add_run_processeddataset(SxRun* run, const QString& dataset_md_uri)
{

}

void SxRequestLocal::create_processed_dataset(const QString& name, const QString& experiment_md_uri)
{

}

void SxRequestLocal::create_data_processeddataset(SxProcessedData* container, const QString& md_uri)
{

}

SxExperiment* SxRequestLocal::read_experiment(const QString& md_uri)
{

}

void SxRequestLocal::write_experiment(SxExperiment* container, const QString& md_uri)
{

}

void SxRequestLocal::create_experiment(SxExperiment* container, const QString& uri)
{

}

void SxRequestLocal::import_data(const QString& data_path, const QString& rawdataset_uri, SxRawData* metadata, bool copy)
{

}

SxRun* SxRequestLocal::read_run(const QString& md_uri)
{

}

void SxRequestLocal::write_run(SxRun* container, const QString& md_uri)
{

}

QStringList SxRequestLocal::query_rep(const QString& repository_uri, const QString& filter_)
{

}

QString SxRequestLocal::create_output_uri(const QString& output_rep_uri, const QString& output_name, const QString& format_, const QString& corresponding_input_uri)
{

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

QString SxRequestLocal::absolute_path(const QString& file, const QString &reference_file)
{
    if (QFile::exists(file)){
        QFileInfo f_info(file);
        return f_info.absoluteFilePath();
    }

    qint8 last_separator = reference_file.lastIndexOf(QDir::separator());
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
