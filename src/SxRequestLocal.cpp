/// \file SxRequestLocal.cpp
/// \brief SxRequestLocal class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include "SxRequestLocal.h"
#include "SxException.h"
#include "SxDataset.h"

#include <QDir>
#include <QFileInfo>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QRegularExpression>


SxRequestLocal::SxRequestLocal()
{

}

SxRequestLocal::~SxRequestLocal()
{

}

SxExperiment* SxRequestLocal::create_experiment(const QString& name, const QString &author, SxDate* date, const QStringList& tag_keys, const QString& destination){}

SxExperiment* SxRequestLocal::get_experiment(const QString uri){}

void SxRequestLocal::update_experiment(SxExperiment* experiment){}

SxRawData* SxRequestLocal::import_data(SxExperiment* experiment, const QString& data_path, const QString& name, const QString& author, SxFormat* format, SxDate* date, SxTags* tags, bool copy){}

SxRawData* SxRequestLocal::get_rawdata(const QString&  uri){}

void SxRequestLocal::update_rawdata(SxRawData* rawdata){}

SxProcessedData* SxRequestLocal::get_processeddata(const QString& uri){}

void SxRequestLocal::update_processeddata(SxProcessedData* processeddata){}

SxDataset* SxRequestLocal::get_dataset_from_uri(const QString& uri){}

void SxRequestLocal::update_dataset(SxDataset* dataset){}

SxDataset* SxRequestLocal::get_rawdataset(SxExperiment* experiment){}

SxDataset* SxRequestLocal::create_dataset(SxExperiment* experiment, const QString& dataset_name){}

SxRun* SxRequestLocal::create_run(SxDataset* dataset, SxRun* run_info){}

SxRun* SxRequestLocal::get_run(const QString& uri){}

SxProcessedData* SxRequestLocal::create_data(SxDataset* dataset, SxRun* run, SxProcessedData* processed_data)
{

}
