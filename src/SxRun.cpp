/// \file SxRun.cpp
/// \brief SxRun class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include "SxRun.h"


SxRunInput::SxRunInput() : SxContainer()
{

}

SxRunInput::SxRunInput(const QString& name, const QString& dataset_name, const QString& query, const QString& origin) : SxContainer()
{
    m_name = name;
    m_dataset_name = dataset_name;
    m_query = query;
    m_origin = origin;
}

SxRunInput::~SxRunInput()
{

}

QString SxRunInput::get_name()
{
    return m_name;
}

QString SxRunInput::get_dataset_name()
{
    return m_dataset_name;
}

QString SxRunInput::get_query()
{
    return m_query;
}

QString SxRunInput::get_origin_output_name()
{
    return m_origin;
}

void SxRunInput::set_name(const QString& name)
{
    m_name = name;
}

void SxRunInput::set_dataset_name(const QString &name)
{
    m_dataset_name = name;
}

void SxRunInput::set_query(const QString& query)
{
    m_query = query;
}

void SxRunInput::set_origin_output_name(const QString& name)
{
    m_origin = name;
}



SxRunParameter::SxRunParameter() : SxContainer()
{

}

SxRunParameter::SxRunParameter(const QString& name, const QString& value) : SxContainer()
{
    m_name = name;
    m_value = value;
}

SxRunParameter::~SxRunParameter()
{

}

QString SxRunParameter::get_name()
{
    return m_name;
}

QString SxRunParameter::get_value()
{
    return m_value;
}

void SxRunParameter::set_name(const QString& name)
{
    m_name = name;
}
void SxRunParameter::set_value(const QString& value)
{
    m_value = value;
}

SxRun::SxRun() : SxMetadata()
{

}

SxRun::~SxRun()
{
    delete m_processed_dataset;
}


SxMetadata* SxRun::get_processed_dataset()
{
    return m_processed_dataset;
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

SxRunInput* SxRun::get_input(qint8 index)
{
    return m_inputs[index];
}

QList<SxRunInput*> SxRun::get_inputs()
{
    return m_inputs;
}

qint8 SxRun::get_parameters_count()
{
    return m_parameters.count();
}

SxRunParameter *SxRun::get_parameter(qint8 index)
{
    return m_parameters[index];
}

QList<SxRunParameter*> SxRun::get_parameters()
{
    return m_parameters;
}


void SxRun::set_processed_dataset(SxMetadata *dataset)
{
    m_processed_dataset = dataset;
}

void SxRun::set_process_name(const QString& name)
{
    m_process_name = name;
}

void SxRun::set_process_uri(const QString& uri)
{
    m_process_uri = uri;
}

void SxRun::set_input(SxRunInput *input)
{
    bool found = false;
    for (qint8 i = 0 ; i < m_inputs.count() ; i++){
        if (m_inputs[i]->get_name() == input->get_name()){
            m_inputs[i] = input;
            found = true;
        }
    }
    if (!found)
    {
        m_inputs.append(input);
    }
}

void SxRun::set_parameter(SxRunParameter* parameter)
{
    bool found = false;
    for (qint8 i = 0 ; i < m_parameters.count() ; i++){
        if (m_parameters[i]->get_name() == parameter->get_name()){
            m_parameters[i] = parameter;
            found = true;
        }
    }
    if (!found)
    {
       m_parameters.append(parameter);
    }
}
