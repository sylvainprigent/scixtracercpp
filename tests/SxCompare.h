/// \file SxCompare.h
/// \brief Compare methods for unit testing
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include <scixtracer>


class SxCompare{

public:
    static bool compare_txt_files(const QString& file1, const QString& file2);
};
