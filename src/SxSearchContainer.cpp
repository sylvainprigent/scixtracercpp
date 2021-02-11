/// \file SxSearchContainer.cpp
/// \brief SxSearchContainer class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include <SxSearchContainer.h>

SxSearchContainer::SxSearchContainer() : SxContainer()
{

}

SxSearchContainer::SxSearchContainer(const QString& name, const QString& uri, SxTags* tags) : SxContainer()
{
    m_name = name;
    m_uri = uri;
    m_tags = tags;
}

SxSearchContainer::~SxSearchContainer()
{

}

QString SxSearchContainer::get_name()
{
    return m_name;
}

QString SxSearchContainer::get_uri()
{
    return m_uri;
}

SxTags* SxSearchContainer::get_tags()
{
    return m_tags;
}

void SxSearchContainer::set_name(const QString& name)
{
    m_name = name;
}

void SxSearchContainer::set_uri(const QString& uri)
{
    m_uri = uri;
}

void SxSearchContainer::set_tags(SxTags* tags)
{
    m_tags = tags;
}

bool SxSearchContainer::is_tag(const QString& key)
{
    return m_tags->get_keys().contains(key);
}

QString SxSearchContainer::get_tag(const QString& key)
{
    return m_tags->get_tag(key);
}
