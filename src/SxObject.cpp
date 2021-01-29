/// \file SxObject.cpp
/// \brief SxObject class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include <SxObject.h>

SxObject::SxObject()
{
    m_object_name = "SxObject";
}

QString SxObject::get_object_name()
{
    return m_object_name;
}

qint8 SxObject::set_object_name(const QString& name)
{
    m_object_name = name;
    return 0;
}
