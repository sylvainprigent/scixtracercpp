/// \file SxProcessedData.cpp
/// \brief SxProcessedData class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021


#include "SxProcessedData.h"
#include "SxException.h"

SProcessedDataInput::SProcessedDataInput() : SxContainer()
{

}

SProcessedDataInput::~SProcessedDataInput()
{

}

QString SProcessedDataInput::get_name()
{
    return m_name;
}

QString SProcessedDataInput::get_uri()
{
    return m_uri;
}

QString SProcessedDataInput::get_type()
{
    return m_type;
}

void SProcessedDataInput::set_name(const QString& name)
{
    m_name = name;
}
void SProcessedDataInput::set_uri(const QString& uri)
{
    m_uri = uri;
}

void SProcessedDataInput::set_type(const QString& type)
{
    m_type = type;
}



SProcessedDataOutput::SProcessedDataOutput() : SxContainer()
{

}

SProcessedDataOutput::~SProcessedDataOutput()
{

}

QString SProcessedDataOutput::get_name()
{
    return m_name;
}

QString SProcessedDataOutput::get_label()
{
    return m_label;
}

void SProcessedDataOutput::set_name(const QString& name)
{
    m_name = name;
}

void SProcessedDataOutput::set_label(const QString& label)
{
    m_label = label;
}


SxProcessedData::SxProcessedData() : SxData()
{

}

SxProcessedData::~SxProcessedData()
{

}

QString SxProcessedData::get_run_uri()
{
    return m_run_uri;
}
SProcessedDataOutput SxProcessedData::get_run_output()
{
    return m_output;
}
qint8 SxProcessedData::get_run_inputs_count()
{
    return m_inputs.count();
}
SProcessedDataInput SxProcessedData::get_run_input(qint8 index)
{
    QMapIterator<QString, SProcessedDataInput> i(m_inputs);
    qint8 j = -1;
    while (i.hasNext()) {
        i.next();
        j++;
        if (j == index){
            return i.value();
        }
    }
    throw SxException( QString("Cannot find processed data input at index" + QString::number(index)).toStdString().c_str());
}

void SxProcessedData::set_run_uri(const QString& uri)
{
    m_run_uri = uri;
}

void SxProcessedData::set_run_input(const QString& name, const SProcessedDataInput& input)
{
    m_inputs[name] = input;
}

void SxProcessedData::set_run_output(const SProcessedDataOutput& output)
{
    m_output = output;
}

