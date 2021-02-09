/// \file SxFormat.h
/// \brief SxFormat class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include "scixtracerExport.h"

#include "SxContainer.h"

/// \class SxFormat
/// \brief Container for the descriptions of a data format
class SCIXTRACER_EXPORT SxFormat: public SxContainer{

    Q_OBJECT

public:
    SxFormat();
    SxFormat(const QString& name);
    ~SxFormat();

public:
    // getters
    /// \brief Get the name of the format
    /// \return Name of the format
    QString get_name();

public:
    // setters
    /// \brief Set the name of the format
    /// \param[in] name Name of the format
    void set_name(QString name);

private:
    QString m_name;

};
