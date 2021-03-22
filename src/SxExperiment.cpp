/// \file SxExperiment.cpp
/// \brief SxExperiment class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include "SxExperiment.h"
#include "SxException.h"

SxDatasetMetadata::SxDatasetMetadata()
{

}

SxDatasetMetadata::SxDatasetMetadata(const QString& name, const QString& md_uri, const QString& uuid)
{
    m_name = name;
    m_md_uri = md_uri;
    m_uuid = uuid;
}

SxDatasetMetadata::~SxDatasetMetadata()
{

}

QString SxDatasetMetadata::get_name()
{
    return m_name;
}

QString SxDatasetMetadata::get_md_uri()
{
   return m_md_uri;
}

QString SxDatasetMetadata::get_uuid()
{
    return m_uuid;
}

void SxDatasetMetadata::set_name(const QString& value)
{
    m_name = value;
}

void SxDatasetMetadata::set_md_uri(const QString& value)
{
    m_md_uri = value;
}

void SxDatasetMetadata::set_uuid(const QString& value)
{
    m_uuid = value;
}

SxExperiment::SxExperiment() : SxMetadata()
{

}

SxExperiment::~SxExperiment()
{
    delete m_raw_dataset;
    for(qint32 i = 0 ; i < m_processed_datasets.count() ; ++i)
    {
        delete m_processed_datasets[i];
    }
}

QString SxExperiment::get_name()
{
    return m_name;
}

SxUser* SxExperiment::get_author()
{
    return m_author;
}

SxDate* SxExperiment::get_date()
{
    return m_date;
}

SxDatasetMetadata *SxExperiment::get_raw_dataset()
{
    return m_raw_dataset;
}

QList<SxDatasetMetadata *> SxExperiment::get_processed_datasets()
{
    return m_processed_datasets;
}

qint8 SxExperiment::get_processed_datasets_count()
{
    return m_processed_datasets.count();
}

SxDatasetMetadata *SxExperiment::get_processed_dataset(qint8 index)
{
    return m_processed_datasets[index];
}

QStringList SxExperiment::get_tags_keys()
{
    return m_tags_keys;
}

qint8 SxExperiment::get_tags_keys_count()
{
    return m_tags_keys.count();
}

QString SxExperiment::get_tags_key(qint8 index)
{
    return m_tags_keys[index];
}

void SxExperiment::set_name(const QString& name)
{
    m_name = name;
}

void SxExperiment::set_author(SxUser *user)
{
    m_author = user;
}

void SxExperiment::set_date(SxDate *date)
{
    m_date = date;
}

void SxExperiment::set_raw_dataset(SxDatasetMetadata *metadata)
{
    m_raw_dataset = metadata;
}

void SxExperiment::set_processed_dataset(SxDatasetMetadata* metadata)
{
    bool found = false;
    for (qint8 i = 0 ; i < m_processed_datasets.count() ; i++)
    {
        if (m_processed_datasets[i]->get_md_uri() == metadata->get_md_uri())
        {
            found = true;
        }
    }
    if (!found)
    {
        m_processed_datasets.append(metadata);
    }
}

void SxExperiment::set_tag_key(const QString& key)
{
    bool found = false;
    for (qint8 i = 0 ; i < m_tags_keys.count() ; i++)
    {
        if (m_tags_keys[i] == key)
        {
            found = true;
        }
    }
    if (!found)
    {
        m_tags_keys.append(key);
    }
}
