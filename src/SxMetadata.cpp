/// \file SxMetadata.cpp
/// \brief SxMetadata class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include <SxMetadata.h>

SxMetadata::SxMetadata() : SxContainer()
{

}

SxMetadata::~SxMetadata()
{

}

QString SxMetadata::get_md_uri(){
    return m_md_uri;
}

QString SxMetadata::get_uuid(){
    return m_uuid;
}

void SxMetadata::set_md_uri(const QString& md_uri)
{
    m_md_uri = md_uri;
}

void SxMetadata::set_uuid(const QString& uuid)
{
    m_uuid = uuid;
}
