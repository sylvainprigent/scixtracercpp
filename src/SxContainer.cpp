/// \file SxContainer.cpp
/// \brief SxContainer class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include <SxContainer.h>

SxContainer::SxContainer() : SxObject()
{

}

SxContainer::~SxContainer()
{

}

bool SxContainer::is_up_to_date()
{
    return m_is_up_to_date;
}

SxContainer* SxContainer::get_parent()
{
    return m_parent;
}

void SxContainer::set_up_to_date(bool value)
{
    m_is_up_to_date = value;
}

void SxContainer::set_parent(SxContainer* parent)
{
    m_parent = parent;
}
