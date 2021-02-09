/// \file SxSerialize.cpp
/// \brief SxSerialize class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include <SxSerialize.h>
#include "SxException.h"

SxSerialize::SxSerialize()
{

}

SxSerialize::~SxSerialize()
{

}

QString SxSerialize::serialize(SxMetadata* container)
{
    SxRawData* raw_data = qobject_cast<SxRawData*>(container);
    if(raw_data)
    {
        return this->serialize_rawdata(raw_data);
    }
    SxProcessedData* processed_data = qobject_cast<SxProcessedData*>(container);
    if(processed_data)
    {
        return this->serialize_processeddata(processed_data);
    }
    SxDataset* dataset = qobject_cast<SxDataset*>(container);
    if(dataset)
    {
        return this->serialize_dataset(dataset);
    }
    SxRun* run = qobject_cast<SxRun*>(container);
    if(run)
    {
        return this->serialize_run(run);
    }
    SxExperiment* experiment = qobject_cast<SxExperiment*>(container);
    if(experiment)
    {
        return this->serialize_experiment(experiment);
    }
    throw SxException("SxSerialize cannot cast the metadata container");
}
