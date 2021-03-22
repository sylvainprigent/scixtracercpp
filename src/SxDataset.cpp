/// \file SxDataset.cpp
/// \brief SxDataset class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include "SxDataset.h"
#include "SxException.h"

#include <QSetIterator>

SxDataset::SxDataset() : SxMetadata()
{

}

SxDataset::~SxDataset()
{
    for (qint32 i = 0 ; i < m_data.count() ; ++i ){
        delete m_data[i];
    }
}

QString SxDataset::get_type()
{
    return m_type;
}

QString SxDataset::get_name()
{
    return m_name;
}

qint32 SxDataset::get_data_count()
{
    return m_data.count();
}

QString SxDataset::get_data_uri(qint32 index)
{
    return m_data[index]->get_md_uri();
}

QString SxDataset::get_data_uuid(qint32 index)
{
    return m_data[index]->get_uuid();
}

SxMetadata* SxDataset::get_data(qint32 index)
{
    return m_data[index];
}

void SxDataset::set_type(const QString& type)
{
    m_type = type;
}

void SxDataset::set_name(const QString& name)
{
    m_name = name;
}

void SxDataset::set_data(SxMetadata* metadata)
{
    bool found = false;
    for (qint32 i = 0 ; i < m_data.count() ; ++i){
        if (m_data[i]->get_md_uri() == metadata->get_md_uri()){
            found = true;
            break;
        }
    }
    if (!found){
        m_data.append(metadata);
    }
}

QStringList SxDataset::get_data_list()
{
    QStringList uris;
    for (qint32 i = 0 ; i < m_data.count() ; ++i){
        uris.append(m_data[i]->get_md_uri());
    }
    return uris;
}
