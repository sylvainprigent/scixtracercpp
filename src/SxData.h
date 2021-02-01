/// \file SxData.h
/// \brief SxData class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include "scixtracerExport.h"

#include "SxMetadata.h"
#include "SxDate.h"
#include "SxFormat.h"
#include "SxUser.h"

/// \class SxData
/// \brief Metadata container for any data base information
class SCIXTRACER_EXPORT SxData: public SxMetadata{

public:
    SxData();
    ~SxData();

public:
    // getters
    /// \brief Get the data type. Possible values are (raw, processed)
    /// \return Type of the data
    QString get_type();
    /// \brief Get the name of the data
    /// \return Name of the data
    QString get_name();
    /// \brief Get the the data author
    /// \return Reference to the user information
    SxUser get_author();
    /// \brief Get the creation date of the data
    /// \return Creation date of the data
    SxDate get_date();
    /// \brief Get the data format
    /// \return Data format
    SxFormat get_format();

public:
    // setters
    /// \brief Set the type of the data. Possible values are (raw, processed)
    /// \param[in] type Type of the data
    void set_type(const QString& type);
    /// \brief Set the name of the data
    /// \param[in] name Name of the data
    void set_name(const QString& name);
    /// \brief Set the username of the data author
    /// \param[in] username Username of the data author
    void set_author(const SxUser& user);
    /// \brief Set the creation date of the data
    /// \param[in] date Creation date of the data
    void set_date(const SxDate& date);
    /// \brief Set the data format
    /// \param[in] format Data format
    void set_format(const SxFormat& format);

private:
    QString m_type;
    QString m_name;
    SxUser m_author;
    SxDate m_date;
    SxFormat m_format;
};
