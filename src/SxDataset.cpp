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

}

QString SxDataset::get_type()
{
    return m_type;
}

QString SxDataset::get_name()
{
    return m_name;
}

qint8 SxDataset::get_data_count()
{
    return m_data_uris.count();
}

QString SxDataset::get_data_uri(qint8 index)
{
    QSetIterator<QString> i(m_data_uris);
    qint8 c = -1;
    while (i.hasNext()){
        c++;
        if (c == index){
            return i.next();
        }
        i.next();
    }
    throw SxException("SxDataset::get_data_uri: Index not found");
}

void SxDataset::set_type(const QString& type)
{
    m_type = type;
}

void SxDataset::set_name(const QString& name)
{
    m_name = name;
}

void SxDataset::set_data(const QString& uri)
{
    m_data_uris.insert(uri);
}
