/// \file SxLogTerminal.h
/// \brief SxLogTerminal class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include "scixtracerExport.h"

#include "SxLog.h"

/// \class SxLogTerminal
/// \brief Implementation of SLog to print log in a terminal
class SCIXTRACER_EXPORT SxLogTerminal: public SxLog{

public:
    SxLogTerminal();
    virtual ~SxLogTerminal();

public:
    /// \brief Print the notification in the terminal
    /// \param[in] status Notification status: [default, highlight, header, warning, error]
    /// \param[in] message Content of the notification
    /// \return 0 if ok, or 1 if an error occured
    qint8 notify(QString status, QString message);

    /// \brief Print a progress in the terminal
    /// \param[in] percentage
    /// \return 0 if ok, or 1 if an error occured
    qint8 progress(qint8 percentage);

};
