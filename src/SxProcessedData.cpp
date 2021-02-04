/// \file SxProcessedData.cpp
/// \brief SxProcessedData class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021


#include "SxProcessedData.h"
#include "SxException.h"

SxProcessedDataInput::SxProcessedDataInput() : SxContainer()
{

}

SxProcessedDataInput::~SxProcessedDataInput()
{

}

QString SxProcessedDataInput::get_name()
{
    return m_name;
}

QString SxProcessedDataInput::get_uri()
{
    return m_uri;
}

QString SxProcessedDataInput::get_type()
{
    return m_type;
}

void SxProcessedDataInput::set_name(const QString& name)
{
    m_name = name;
}
void SxProcessedDataInput::set_uri(const QString& uri)
{
    m_uri = uri;
}

void SxProcessedDataInput::set_type(const QString& type)
{
    m_type = type;
}



SxProcessedDataOutput::SxProcessedDataOutput() : SxContainer()
{

}

SxProcessedDataOutput::~SxProcessedDataOutput()
{

}

QString SxProcessedDataOutput::get_name()
{
    return m_name;
}

QString SxProcessedDataOutput::get_label()
{
    return m_label;
}

void SxProcessedDataOutput::set_name(const QString& name)
{
    m_name = name;
}

void SxProcessedDataOutput::set_label(const QString& label)
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
SxProcessedDataOutput SxProcessedData::get_run_output()
{
    return m_output;
}
qint8 SxProcessedData::get_run_inputs_count()
{
    return m_inputs.count();
}
SxProcessedDataInput SxProcessedData::get_run_input(qint8 index)
{
    QMapIterator<QString, SxProcessedDataInput> i(m_inputs);
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

void SxProcessedData::set_run_input(const QString& name, const SxProcessedDataInput& input)
{
    m_inputs[name] = input;
}

void SxProcessedData::set_run_output(const SxProcessedDataOutput& output)
{
    m_output = output;
}

