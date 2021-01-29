/// \file SxLog.h
/// \brief SxLog class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include <QString>
#include "scixtracerExport.h"

#include "SxObject.h"

/// \class SxLog
/// \brief Abstract class for logger. Logger here mention tools to print error and progress in console or GUI
class SCIXTRACER_EXPORT SxLog: public SxObject{

public:
    SxLog();
    virtual ~SxLog();

public:
    /// \brief Virtual method to implement the log notification
    /// \param[in] status Notification status: [default, highlight, header, warning, error]
    /// \param[in] message Content of the notification
    /// \return 0 if ok, or 1 if an error occured
    virtual qint8 notify(QString status, QString message) = 0;

    /// \brief Virtual method to implement the log progress
    /// \param[in] percentage
    /// \return 0 if ok, or 1 if an error occured
    virtual qint8 progress(qint8 percentage) = 0;

};
