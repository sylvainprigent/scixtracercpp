/// \file SxRawData.cpp
/// \brief SxRawData class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include "SxRawData.h"

#include <QJsonObject>

SxRawData::SxRawData() : SxData()
{

}

SxRawData::~SxRawData()
{

}

SxTags* SxRawData::get_tags()
{
    return m_tags;
}

void SxRawData::set_tags(SxTags* tags)
{
    m_tags = tags;
}
