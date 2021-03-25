/// \file SxCompare.h
/// \brief Compare methods for unit testing
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include <scixtracercpp>


class SxCompare{

public:
    static qint8 compare_txt_files(const QString& file1, const QString& file2);
    static qint8 compare_metadata(SxMetadata* container1, SxMetadata* container2);
};
