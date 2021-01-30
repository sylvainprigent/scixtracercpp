/// \file SxException.h
/// \brief SxException
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021
///
/// Copyright (C) SciXTracer 2021

#pragma once

#include <iostream>
#include <sstream>
#include <exception>

#include "scixtracerExport.h"

/// \class SxException
/// \brief class defining the exeptions used in the code
/// heritate from the std::exception
class SCIXTRACER_EXPORT SxException : public std::exception
{
public:
    /// \fn SxException( const char * Msg )
    /// \brief Constructor
    /// \param[in] Msg Message
    SxException( const char * Msg )
    {
        std::ostringstream oss;
        oss << "Error:" << Msg;
        this->msg = oss.str();
    }

    /// \fn virtual ~SxException() throw()
    /// \brief Desctructor
    virtual ~SxException() throw()
    {

    }

    /// \fn virtual const char * what() const throw()
    /// \return the error message
    virtual const char * what() const throw()
    {
        return this->msg.c_str();
    }

private:
    std::string msg; ///< Error message
};
