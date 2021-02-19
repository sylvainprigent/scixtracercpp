/// \file CreateMetadata.h
/// \brief Functions to create reference metadata for testing
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include <scixtracercpp>

SxRawData* create_raw_data();
SxProcessedData* create_processed_data();
SxDataset* create_dataset();
SxExperiment* create_experiment();
