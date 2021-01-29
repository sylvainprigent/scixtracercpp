/// \file SxLogFile.h
/// \brief SxLogFile class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include <QFile>

#include "scixtracerExport.h"

#include "SxLog.h"

/// \class SxLogFile
/// \brief Implementation of SLog to print log in a txt log file
class SCIXTRACER_EXPORT SxLogFile: public SxLog{

public:
    SxLogFile();
    virtual ~SxLogFile();

public:
    /// \brief Append the notification in a log file
    /// \param[in] status Notification status: [default, highlight, header, warning, error]
    /// \param[in] message Content of the notification
    /// \return 0 if ok, or 1 if an error occured
    qint8 notify(QString status, QString message);

    /// \brief Append a progress in the log file
    /// \param[in] percentage
    /// \return 0 if ok, or 1 if an error occured
    qint8 progress(qint8 percentage);

public:
    /// \brief Open the log file
    /// \param[in] file Path of the log file
    /// \return 0 if ok, or 1 if an error occured
    qint8 open_file(QString file);
    /// \brief close_file()
    /// \return 0 if ok, or 1 if an error occured
    qint8 close_file();

private:
    QFile* m_file; ///< Pointer to the log file object
};
