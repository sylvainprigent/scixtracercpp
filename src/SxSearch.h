/// \file SxSearch.h
/// \brief SxSearch class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include <QString>
#include "scixtracerExport.h"
#include "SxSearchContainer.h"

/// \class SxSearch
/// \brief Class to implement search engine functions
class SCIXTRACER_EXPORT SxSearch{


public:
    /// \brief query internal function
    /// Search if the query is on the search_list
    /// \param[in] search_list Data search list (list of SearchContainer)
    /// \param[in] query  String query with the key=value format. No 'AND', 'OR'...
    /// \return list of selected SearchContainer
    static QList<SxSearchContainer*> query_list_single(QList<SxSearchContainer*>& search_list, const QString& query);
};
