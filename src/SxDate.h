/// \file SxDate.h
/// \brief SxDate class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include "scixtracerExport.h"

#include "SxContainer.h"

/// \class SxDate
/// \brief Container for a date. It manage only year, month and day. Not minutes and hours
class SCIXTRACER_EXPORT SxDate: public SxContainer{

public:
    SxDate();
    SxDate(const QString& date);
    ~SxDate();

public:
    // getters
    /// \brief Get the the date as a string
    /// \param[in] format Format of the date. Possible values are 'YYYY-MM-DD' or 'DD/MM/YYYY'
    /// \return Date representation as a string
    QString get_to_string(QString format);
    /// \brief Get the the date year
    /// \return Year value. Ex 2021
    qint8 get_year();
    /// \brief Get the the date month
    /// \return Month value. Ex 9
    qint8 get_month();
    /// \brief Get the the date day
    /// \return Day value. Ex 2
    qint8 get_day();

public:
    // setters
    /// \brief Set the date year
    /// \param[in] value Year of the date
    void set_year(qint8 value);
    /// \brief Set the date month
    /// \param[in] value Month of the date
    void set_month(qint8 value);
    /// \brief Set the date day
    /// \param[in] value Day of the date
    void set_day(qint8 value);
    /// \brief Set the date by parsing a string. Possible formats are 'YYYY-MM-DD' or 'DD/MM/YYYY'
    /// \param[in] value Date as a string
    void set_from_string(QString value);

private:
    /// \brief Convert a number to string with a fixed number of digit
    /// \param[in] number Number to convert
    /// \param[in] digit Number of digits
    QString number_to_str(qint8 number, qint8 digits=2);

private:
    qint8 m_year; ///< date year
    qint8 m_month; ///< date month
    qint8 m_day; ///< date day

};
