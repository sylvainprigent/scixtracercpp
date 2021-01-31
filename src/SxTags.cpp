/// \file SxTags.cpp
/// \brief SxTags class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include "SxTags.h"

SxTags::SxTags() : SxContainer()
{

}

SxTags::~SxTags()
{

}

QString SxTags::get_tag(QString key)
{
    return m_tags[key];
}

qint8 SxTags::get_count()
{
    return m_tags.count();
}

QStringList SxTags::get_keys()
{
    return m_tags.keys();
}

void SxTags::set_tag(QString key, QString value)
{
    m_tags[key] = value;
}
