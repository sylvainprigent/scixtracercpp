/// \file SxObject.h
/// \brief SxObject class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include <QString>
#include "scixtracerExport.h"

/// \class SxObject
/// \brief Mother class for each class of the API
class SCIXTRACER_EXPORT SxObject{

public:
    SxObject();

public:
    // getters
    QString get_object_name();

public:
    // setters
    qint8 set_object_name(const QString& name);


private:
    QString m_object_name;   
};
