/// \file SxUser.cpp
/// \brief SxUser class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include "SxUser.h"
#include "SxException.h"

SxUser::SxUser() : SxContainer()
{

}

SxUser::SxUser(const QString& username) : SxContainer(){
    m_username = username;
}

SxUser::~SxUser()
{

}

QString SxUser::get_username()
{
    return m_username;
}

QString SxUser::get_email()
{
    return m_email;
}
QString SxUser::get_name()
{
    return m_name;
}
QString SxUser::get_firstname()
{
    return m_firstname;
}

void SxUser::set_username(QString username)
{
    m_username = username;
}
void SxUser::set_email(QString email)
{
    if (email.contains("@")){
        m_email = email;
    }
    else{
        throw SxException("The email is not correct");
    }
}
void SxUser::set_name(QString name)
{
    m_name = name;
}

void SxUser::set_firstname(QString firstname)
{
    m_firstname = firstname;
}
