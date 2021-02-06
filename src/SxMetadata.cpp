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

void SxMetadata::add_child(SxMetadata* container)
{
    m_children[container->get_md_uri()] = container;
}

SxMetadata* SxMetadata::get_child(QString uri)
{
    return m_children[uri];
}

SxMetadata* SxMetadata::get_child_at(qint8 index)
{
    QMapIterator<QString, SxMetadata*> i(m_children);
    qint8 j = -1;
    while (i.hasNext()) {
        i.next();
        j++;
        if (j == index){
            return i.value();
        }
    }
    return nullptr;
}

qint8 SxMetadata::get_children_count()
{
    return m_children.count();
}

void SxMetadata::set_md_uri(const QString& md_uri)
{
    m_md_uri = md_uri;
}
