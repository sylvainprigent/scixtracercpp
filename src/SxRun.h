/// \file SxRun.h
/// \brief SxRun class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once


#include "scixtracerExport.h"
#include "SxContainer.h"
#include "SxMetadata.h"

class SCIXTRACER_EXPORT SRunInput: public SxContainer{

public:
    SRunInput();
    ~SRunInput();

public:
    // getters
    /// \brief Get the name of the input
    /// \return Name of the input
    QString get_name();
    /// \brief Get the URI of the dataset where the input data is stored
    /// \return Get the dataset URI of input data
    QString get_dataset();
    /// \brief Get the query used to select data in the input dataset. The query is a RegExp
    /// \return Query used to select input data
    QString get_query();
    /// \brief Get the origin output name. It is the name of the output of the previous job in the pipeline
    /// \return Output name of the run that created the input data
    QString get_origin_output_name();

public:
    // setters
    /// \brief Set the name of the input
    /// \param[i] name Name of the input
    void set_name(const QString& name);
    /// \brief Set the dataset where the input data is stored
    /// \param[in] uri URI of input dataset
    void set_dataset(const QString& uri);
    /// \brief Set the query used to select data in the input dataset. The query is a RegExp
    /// \param[in] query Query used to select input data
    void set_query(const QString& query);
    /// \brief Set the origin output name. It is the name of the output of the previous job in the pipeline
    /// \param[in] name Name of the origin output
    void set_origin_output_name(const QString& name);

private:
    QString m_name;
    QString m_dataset_uri;
    QString m_query;
    QString m_origin;

};

class SCIXTRACER_EXPORT SRunParameter: public SxContainer{

public:
    SRunParameter();
    ~SRunParameter();

public:
    // getters
    /// \brief Get the name of the parameter
    /// \return Name of the parameter
    QString get_name();
    /// \brief Get the value of the parameter
    /// \return Value of the parameter
    QString get_value();

public:
    //setters
    /// \brief Set the name of the parameter
    /// \param[in] name Name of the parameter
    void set_name(const QString& name);
    /// \brief Set the value of the parameter
    /// \param[in] value Value of the parameter
    void set_value(const QString& value);

private:
    QString m_name;
    QString m_value;

};

/// \class SxRun
/// \brief Metadata container for a process run (or job)
class SCIXTRACER_EXPORT SxRun: public SxMetadata{

public:
    SxRun();
    ~SxRun();

public:
    // getters
    /// \brief Get the URI of the processed dataset where the run stored the results
    /// \return URI of the processed dataset
    QString get_processed_dataset();
    /// \brief Get the name of the process that is runned
    /// \return Name of the process
    QString get_process_name();
    /// \brief Get the URI of the process that is runned
    /// \return URI of the process
    QString get_process_uri();
    /// \brief Get the number of input data used by the process
    /// \return Number of input data used by the process
    qint8 get_inputs_count();
    /// \brief Get the input at the index
    /// \param[in] index Index of the input in the input list
    /// \return Reference to the run input container
    SRunInput get_input(qint8 index);
    /// \brief Get the list of all inputs used by the process
    /// \return List of references to the run input containers
    QList<SRunInput> get_inputs();
    /// \brief Get the number of parameters used to tune the process
    /// \return Number of parameters
    qint8 get_parameters_count();
    /// \brief Get the parameter at the index
    /// \param[in] index Index of the parameter in the output list
    /// \return Reference to the parameter container
    SRunParameter get_parameter(qint8 index);
    /// \brief Get the list of all parameters used by the process
    /// \return List of references to the parameter containers
    QList<SRunParameter> get_parameters();

public:
    // setters
    /// \brief Set the URI of the processed dataset where the run stored the results
    /// \param[in] uri URI of the processed dataset
    void set_processed_dataset(const QString& uri);
    /// \brief Set the name of the process that is runned
    /// \param[in] name Name of the process
    void set_process_name(const QString& name);
    /// \brief Set the URI of the process that is runned
    /// \param[in] uri URI of the process
    void set_process_uri(const QString& uri);
    /// \brief Set the input at the index
    /// \param[in] input Reference to the run input container
    void set_input(SRunInput& input);
    /// \brief Set the parameter at the index
    /// \param[in] parameter Reference to the run parameter container
    void set_parameter(SRunParameter& parameter);

private:
    QString m_processed_dataset_uri;
    QString m_process_name;
    QString m_process_uri;
    QList<SRunInput> m_inputs;
    QList<SRunParameter> m_parameters;
};
