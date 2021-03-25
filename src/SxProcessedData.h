/// \file SxProcessedData.h
/// \brief SxProcessedData class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include "scixtracerExport.h"

#include "SxData.h"

#include <QMap>


/// \class SxProcessedDataInput
/// \brief Container for run input information
class SCIXTRACER_EXPORT SxProcessedDataInput: public SxContainer{

    Q_OBJECT

public:
    SxProcessedDataInput();
    SxProcessedDataInput(const QString& name, SxMetadata* data, const QString& type);
    ~SxProcessedDataInput();

public:
    // getters
    /// \brief Get the input name
    /// \return Name of the process input
    QString get_name();
    /// \briefGet the input data URI
    /// \return Pointer of the input data metadata
    SxMetadata* get_data();
    /// \brief Get the input data type (raw or processed)
    /// \return Type of the data (raw or processed)
    QString get_type();

public:
    // setters
    /// \brief Set the input name
    /// \param[in] name Name of the process input
    void set_name(const QString& name);
    /// \brief Set the input data URI
    /// \param[in] data Metadata of the input data
    void set_data(SxMetadata* data);
    /// \brief Set the input data type (raw or processed)
    /// \param[in] type Type of the data (raw or processed)
    void set_type(const QString& type);

private:
    QString m_name;
    SxMetadata* m_data;
    QString m_type;
};


/// \class SProcessedDataOutput
/// \brief Container for run output information
class SCIXTRACER_EXPORT SxProcessedDataOutput: public SxContainer{

    Q_OBJECT

public:
    SxProcessedDataOutput();
    SxProcessedDataOutput(const QString& name, const QString& label);
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

    Q_OBJECT

public:
    SxProcessedData();
    ~SxProcessedData();

public:
    // getters
    /// \brief Get the run metadata
    /// \return The run metadata
    SxMetadata* get_run();
    /// \brief Get the run output. Only one ouput possible which is this processed data
    /// \return Container of the run output
    SxProcessedDataOutput* get_run_output();
    /// \brief Get the number of run inputs
    /// \return Number of run inputs
    qint8 get_run_inputs_count();
    /// \brief Get a run inputs
    /// \param[in] index Index of the input in the input list
    /// \return Container of run input
    SxProcessedDataInput* get_run_input(qint8 index);

public:
    // setters
    /// \brief Set the run metadata
    /// \param[in] run Run metadata
    void set_run(SxMetadata* run);
    /// \brief Set an input of the run. Update it if already exists or append it to the inputs list otherwise
    /// \param[in] name Name of the input data
    /// \param[in] input Container for a run input
    void set_run_input(const QString& name, SxProcessedDataInput* input);
    /// \brief Set the run output. Only one ouput possible which is this processed data
    /// \param[in] output Container for a run output
    void set_run_output(SxProcessedDataOutput* output);
    /// \brief Set the common information of the data
    void set_info(const QString& name, const QString& author, SxDate* date, SxFormat* format_, const QString& uri);
    void add_input(const QString& name, SxMetadata *data, const QString& type);
    void set_output(const QString &name, const QString &label);

private:
    SxMetadata* m_run;
    QMap<QString, SxProcessedDataInput*> m_inputs;
    SxProcessedDataOutput* m_output;
};
