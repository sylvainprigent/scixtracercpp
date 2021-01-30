/// \file SxContainer.h
/// \brief SxContainer class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include <QString>
#include "scixtracerExport.h"

#include "SxObject.h"

/// \class SxContainer
/// \brief Abstract class for an information container. Information here is used as a generic word for any kind of data like user information, metadata...
class SCIXTRACER_EXPORT SxContainer: public SxObject{

public:
    SxContainer();
    ~SxContainer();

public:
    // methods
    /// \brief True if the container is up to date with the database, False otherwise
    /// \return True if the container is up to date with the database, False otherwise
    bool is_up_to_date();

public:
    // getters
    /// \brief Get the parent data container
    /// \return Reference to the parent container. Null reference if no parent
    SxContainer* get_parent();

public:
    // setters
    /// \brief Force the up to date to True. You should not use this method, it is for Request internal use.
    /// \param[in] value True if up to date, false otherwise
    void set_up_to_date(bool value);
    /// \brief Set the parent data container
    /// \param[in] parent Reference to the parent container. Null reference if no parent.
    void set_parent(SxContainer* parent);

private:
    bool m_is_up_to_date; ///< True if the container informations are up to date with the database, false otherwise
    SxContainer* m_parent; ///< Pointer to the parent container
};
