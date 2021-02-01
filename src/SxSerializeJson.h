/// \file SxSerialize.h
/// \brief SxSerialize class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once


#include "scixtracerExport.h"
#include "SxSerialize.h"

#include <QString>
#include <QJsonObject>

/// \class SxSerializeJson
/// \brief Implementation of metadata serializer in Json format
class SCIXTRACER_EXPORT SxSerializeJson: public SxSerialize{

public:
    SxSerializeJson();
    virtual ~SxSerializeJson();

public:
    QString serialize(SxData* data);
    QString serialize(SxRawData* data);
    QString serialize(SxProcessedData* data);
    QString serialize(SxDataset* data);
    QString serialize(SxExperiment* data);

private:
    QString json_object_to_string(const QJsonObject& object);
    QJsonObject data_to_json(SxData* data);
};
