/// \file SxRun.cpp
/// \brief SxRun class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include "SxRun.h"


SRunInput::SRunInput() : SxContainer()
{

}

SRunInput::~SRunInput()
{

}

QString SRunInput::get_name()
{
    return m_name;
}

QString SRunInput::get_dataset()
{
    return m_dataset_uri;
}

QString SRunInput::get_query()
{
    return m_query;
}

QString SRunInput::get_origin_output_name()
{
    return m_origin;
}

void SRunInput::set_name(const QString& name)
{
    m_name = name;
}

void SRunInput::set_dataset(const QString& uri)
{
    m_dataset_uri = uri;
}

void SRunInput::set_query(const QString& query)
{
    m_query = query;
}

void SRunInput::set_origin_output_name(const QString& name)
{
    m_origin = name;
}



SRunParameter::SRunParameter() : SxContainer()
{

}

SRunParameter::~SRunParameter()
{

}

QString SRunParameter::get_name()
{
    return m_name;
}

QString SRunParameter::get_value()
{
    return m_value;
}

void SRunParameter::set_name(const QString& name)
{
    m_name = name;
}
void SRunParameter::set_value(const QString& value)
{
    m_value = value;
}

SxRun::SxRun() : SxMetadata()
{

}

SxRun::~SxRun()
{

}


QString SxRun::get_processed_dataset()
{
    return m_processed_dataset_uri;
}

QString SxRun::get_process_name()
{
    return m_process_name;
}

QString SxRun::get_process_uri()
{
    return m_process_uri;
}

qint8 SxRun::get_inputs_count()
{
    return m_inputs.count();
}

SRunInput SxRun::get_input(qint8 index)
{
    return m_inputs[index];
}

QList<SRunInput> SxRun::get_inputs()
{
    return m_inputs;
}

qint8 SxRun::get_parameters_count()
{
    return m_parameters.count();
}

SRunParameter SxRun::get_parameter(qint8 index)
{
    return m_parameters[index];
}

QList<SRunParameter> SxRun::get_parameters()
{
    return m_parameters;
}


void SxRun::set_processed_dataset(const QString& uri)
{
    m_processed_dataset_uri = uri;
}

void SxRun::set_process_name(const QString& name)
{
    m_process_name = name;
}

void SxRun::set_process_uri(const QString& uri)
{
    m_process_uri = uri;
}

void SxRun::set_input(SRunInput& input)
{
    bool found = false;
    for (qint8 i = 0 ; i < m_inputs.count() ; i++){
        if (m_inputs[i].get_name() == input.get_name()){
            m_inputs[i] = input;
            found = true;
        }
    }
    if (!found)
    {
        m_inputs.append(input);
    }
}

void SxRun::set_parameter(SRunParameter &parameter)
{
    bool found = false;
    for (qint8 i = 0 ; i < m_parameters.count() ; i++){
        if (m_parameters[i].get_name() == parameter.get_name()){
            m_parameters[i] = parameter;
            found = true;
        }
    }
    if (!found)
    {
       m_parameters.append(parameter);
    }
}
