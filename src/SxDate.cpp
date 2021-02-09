/// \file SxDate.cpp
/// \brief SxDate class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include "SxDate.h"
#include "SxException.h"

#include <QStringList>

SxDate::SxDate() : SxContainer()
{

}

SxDate::SxDate(const QString& date) : SxContainer()
{
    this->set_from_string(date);
}

SxDate::~SxDate()
{

}

QString SxDate::get_to_string(QString format)
{
    if (format == "YYYY-MM-DD"){
        return this->number_to_str(m_year, 4) + "-" + this->number_to_str(m_month, 2) + "-" + this->number_to_str(m_day, 2);
    }
    else if ("DD/MM/YYYY"){
        return this->number_to_str(m_day, 2) + "/" + this->number_to_str(m_month, 2) + "/" + this->number_to_str(m_year, 4);
    }
    else{
        throw SxException("Date format not correct");
    }
}

qint8 SxDate::get_year()
{
    return m_year;
}

qint8 SxDate::get_month()
{
    return m_month;
}

qint8 SxDate::get_day()
{
    return m_day;
}

void SxDate::set_year(qint8 value)
{
    m_year = value;
}

void SxDate::set_month(qint8 value)
{
    m_month = value;
}

void SxDate::set_day(qint8 value)
{
    m_day = value;
}

void SxDate::set_from_string(QString value)
{
    QString v1 = value;
    QStringList date_fr = v1.split("/");
    if (date_fr.count() == 3){
        m_day = date_fr[0].toInt();
        m_month = date_fr[1].toInt();
        m_year = date_fr[2].toInt();
        return;
    }

    QString v2 = value;
    QStringList date_en = v2.split("-");
    if (date_en.count() == 3){
        m_day = date_en[2].toInt();
        m_month = date_en[1].toInt();
        m_year = date_en[0].toInt();
        return;
    }

    throw SxException("Cannot set the date from string. Format not correct");
}

QString SxDate::number_to_str(qint8 number, qint8 digits)
{
    return QStringLiteral("%1").arg(number, digits, 10, QLatin1Char('0'));
}
