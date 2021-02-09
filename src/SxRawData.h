/// \file SxRawData.h
/// \brief SxRawData class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include "scixtracerExport.h"

#include "SxData.h"
#include "SxTags.h"

/// \class SxRawData
/// \brief Metadata container for a raw data
class SCIXTRACER_EXPORT SxRawData: public SxData{

    Q_OBJECT

public:
    SxRawData();
    ~SxRawData();

public:
    // getters
    /// \brief Get the map of the tag associated to the data
    /// \return Map of the tags describing to the data
    SxTags* get_tags();

public:
    // setters
    /// \brief Set the map of the tag associated to the data
    /// \param[in] tags Map of the tags describing to the data
    void set_tags(SxTags* tags);

private:
    SxTags* m_tags;
};
