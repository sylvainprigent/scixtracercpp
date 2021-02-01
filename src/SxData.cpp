/// \file SxData.cpp
/// \brief SxData class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include "SxData.h"
#include "SxException.h"

SxData::SxData() : SxMetadata()
{

}

SxData::~SxData()
{

}

QString SxData::get_type()
{
    return m_type;
}

QString SxData::get_name()
{
    return m_name;
}

SxUser SxData::get_author()
{
    return m_author;
}

SxDate SxData::get_date()
{
    return m_date;
}

SxFormat SxData::get_format()
{
    return m_format;
}

void SxData::set_type(const QString& type)
{
    m_type = type;
}

void SxData::set_name(const QString& name)
{
    m_name = name;
}

void SxData::set_author(const SxUser& user)
{
    m_author = user;
}

void SxData::set_date(const SxDate& date)
{
    m_date = date;
}

void SxData::set_format(const SxFormat& format)
{
    m_format = format;
}
