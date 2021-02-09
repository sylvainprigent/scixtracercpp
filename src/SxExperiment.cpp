/// \file SxExperiment.cpp
/// \brief SxExperiment class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include "SxExperiment.h"
#include "SxException.h"

SxExperiment::SxExperiment() : SxMetadata()
{

}

SxExperiment::~SxExperiment()
{

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

QString SxExperiment::get_raw_dataset()
{
    return m_raw_dataset_uri;
}

QStringList SxExperiment::get_processed_datasets()
{
    return m_processed_datasets_uris;
}

qint8 SxExperiment::get_processed_datasets_count()
{
    return m_processed_datasets_uris.count();
}

QString SxExperiment::get_processed_dataset(qint8 index)
{
    return m_processed_datasets_uris[index];
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

void SxExperiment::set_raw_dataset(const QString& uri)
{
    m_raw_dataset_uri = uri;
}

void SxExperiment::set_processed_dataset(const QString& uri)
{
    bool found = false;
    for (qint8 i = 0 ; i < m_processed_datasets_uris.count() ; i++)
    {
        if (m_processed_datasets_uris[i] == uri)
        {
            found = true;
        }
    }
    if (!found)
    {
        m_processed_datasets_uris.append(uri);
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
