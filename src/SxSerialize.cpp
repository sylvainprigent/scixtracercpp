/// \file SxSerialize.cpp
/// \brief SxSerialize class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include <SxSerialize.h>


SxSerialize::SxSerialize()
{

}

SxSerialize::~SxSerialize()
{

}

QString SxSerialize::serialize(SxMetadata* data)
{
    SxRawData* rawData = dynamic_cast<SxRawData*>(data);
    if (rawData){
        return this->serialize(rawData);
    }
    SxProcessedData* processedData = dynamic_cast<SxProcessedData*>(data);
    if (processedData){
        return this->serialize(processedData);
    }
}