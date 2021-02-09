/// \file SxUser.h
/// \brief SxUser class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include "scixtracerExport.h"

#include "SxContainer.h"

/// \class SxUser
/// \brief Container for user information
class SCIXTRACER_EXPORT SxUser: public SxContainer{

    Q_OBJECT

public:
    SxUser();
    SxUser(const QString& username);
    ~SxUser();

public:
    // getters
    /// \brief Get the username (or login)
    /// \return The username (or login)
    QString get_username();
    /// \brief Get the user email address
    /// \return The user email address
    QString get_email();
    /// \brief Get the user name (familly name)
    /// \return The user name (familly name)
    QString get_name();
    /// \brief Get the user firstname
    /// \return The user firstname
    QString get_firstname();

public:
    // setters
    /// \brief Set the username (or login)
    /// \param[in] username The username (or login)
    void set_username(QString username);
    /// \brief Set the user email address
    /// \param[in] email The user email address
    void set_email(QString email);
    /// \brief Set the user name (familly name)
    /// \param[in] name The user name (familly name)
    void set_name(QString name);
    /// \brief Set the user firstname
    /// \param[in] firstname The user firstname
    void set_firstname(QString firstname);

private:
    QString m_username;
    QString m_email;
    QString m_name;
    QString m_firstname;

};
