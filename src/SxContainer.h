/// \file SxContainer.h
/// \brief SxContainer class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include <QObject>
#include <QString>
#include "scixtracerExport.h"

#include "SxObject.h"

/// \class SxContainer
/// \brief Abstract class for an information container. Information here is used as a generic word for any kind of data like user information, metadata...
class SCIXTRACER_EXPORT SxContainer: public SxObject{

    Q_OBJECT

public:
    SxContainer();
    ~SxContainer();

};
