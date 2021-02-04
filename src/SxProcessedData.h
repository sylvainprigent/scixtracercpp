/// \file SxProcessedData.h
/// \brief SxProcessedData class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include "scixtracerExport.h"

#include "SxData.h"

/// \class SxProcessedDataInput
/// \brief Container for run input information
class SCIXTRACER_EXPORT SxProcessedDataInput: public SxContainer{

public:
    SxProcessedDataInput();
    ~SxProcessedDataInput();

public:
    // getters
    /// \brief Get the input name
    /// \return Name of the process input
    QString get_name();
    /// \briefGet the input data URI
    /// \return URI of the input data
    QString get_uri();
    /// \brief Get the input data type (raw or processed)
    /// \return Type of the data (raw or processed)
    QString get_type();

public:
    // setters
    /// \brief Set the input name
    /// \param[in] name Name of the process input
    void set_name(const QString& name);
    /// \brief Set the input data URI
    /// \param[in] uri URI of the input data
    void set_uri(const QString& uri);
    /// \brief Set the input data type (raw or processed)
    /// \param[in] type Type of the data (raw or processed)
    void set_type(const QString& type);

private:
    QString m_name;
    QString m_uri;
    QString m_type;
};

/// \class SProcessedDataOutput
/// \brief Container for run output information
class SCIXTRACER_EXPORT SxProcessedDataOutput: public SxContainer{

public:
    SxProcessedDataOutput();
    ~SxProcessedDataOutput();

public:
    // getters
    /// \brief Get the output name
    /// \return Name of the process output
    QString get_name();
    /// \brief Get the output label
    /// \brief Label of the process output
    QString get_label();

public:
    // setters
    /// \brief Set the output name
    /// \param[in] name Name of the process output
    void set_name(const QString& name);
    /// \brief Set the output label
    /// \param[in] label Label of the process output
    void set_label(const QString& label);

private:
    QString m_name;
    QString m_label;
};

/// \class SxProcessedData
/// \brief Metadata container for a processed data
class SCIXTRACER_EXPORT SxProcessedData: public SxData{

public:
    SxProcessedData();
    ~SxProcessedData();

public:
    // getters
    /// \brief Get the URI of the run metadata
    /// \return URI of the run metadata
    QString get_run_uri();
    /// \brief Get the run output. Only one ouput possible which is this processed data
    /// \return Container of the run output
    SxProcessedDataOutput get_run_output();
    /// \brief Get the number of run inputs
    /// \return Number of run inputs
    qint8 get_run_inputs_count();
    /// \brief Get a run inputs
    /// \param[in] index Index of the input in the input list
    /// \return Container of run input
    SxProcessedDataInput get_run_input(qint8 index);

public:
    // setters
    /// \brief Set the URI of the run metadata
    /// \param[in] uri URI of the run metadata
    void set_run_uri(const QString& uri);

    /// \brief Set an input of the run. Update it if already exists or append it to the inputs list otherwise
    /// \param[in] name Name of the input data
    /// \param[in] input Container for a run input
    void set_run_input(const QString& name, const SxProcessedDataInput& input);

    /// \brief Set the run output. Only one ouput possible which is this processed data
    /// \param[in] output Container for a run output
    void set_run_output(const SxProcessedDataOutput& output);

private:
    QString m_run_uri;
    QMap<QString, SxProcessedDataInput> m_inputs;
    SxProcessedDataOutput m_output;
};
