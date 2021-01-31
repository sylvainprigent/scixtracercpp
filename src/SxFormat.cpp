/// \file SxFormat.cpp
/// \brief SxFormat class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include "SxFormat.h"

SxFormat::SxFormat() : SxContainer()
{

}

SxFormat::~SxFormat()
{

}


QString SxFormat::get_name()
{
    return m_name;
}

void SxFormat::set_name(QString name)
{
    m_name = name;
}
