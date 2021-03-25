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

SxProcessedDataInput::SxProcessedDataInput(const QString& name, SxMetadata *data, const QString& type) : SxContainer()
{
    m_name = name;
    m_data = data;
    m_type = type;
}

SxProcessedDataInput::~SxProcessedDataInput()
{
    delete m_data;
}

QString SxProcessedDataInput::get_name()
{
    return m_name;
}

SxMetadata* SxProcessedDataInput::get_data()
{
    return m_data;
}

QString SxProcessedDataInput::get_type()
{
    return m_type;
}

void SxProcessedDataInput::set_name(const QString& name)
{
    m_name = name;
}

void SxProcessedDataInput::set_data(SxMetadata* data)
{
    m_data = data;
}

void SxProcessedDataInput::set_type(const QString& type)
{
    m_type = type;
}



SxProcessedDataOutput::SxProcessedDataOutput() : SxContainer()
{

}

SxProcessedDataOutput::SxProcessedDataOutput(const QString& name, const QString& label) : SxContainer()
{
    m_name = name;
    m_label = label;
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
    delete m_run;
}

SxMetadata* SxProcessedData::get_run()
{
    return m_run;
}
SxProcessedDataOutput* SxProcessedData::get_run_output()
{
    return m_output;
}
qint8 SxProcessedData::get_run_inputs_count()
{
    return m_inputs.count();
}
SxProcessedDataInput* SxProcessedData::get_run_input(qint8 index)
{
    QMapIterator<QString, SxProcessedDataInput*> i(m_inputs);
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

void SxProcessedData::set_run(SxMetadata* run)
{
    m_run = run;
}

void SxProcessedData::set_run_input(const QString& name, SxProcessedDataInput *input)
{
    m_inputs[name] = input;
}

void SxProcessedData::set_run_output(SxProcessedDataOutput* output)
{
    m_output = output;
}

void SxProcessedData::set_info(const QString& name, const QString& author, SxDate* date, SxFormat* format_, const QString& uri)
{
    m_name = name;
    m_author = author;
    m_date = date;
    m_format = format_;
    m_uri = uri;
}

void SxProcessedData::add_input(const QString& name, SxMetadata *data, const QString& type)
{
    this->set_run_input(name, new SxProcessedDataInput(name, data, type));
}

void SxProcessedData::set_output(const QString &name, const QString &label)
{
    this->set_run_output(new SxProcessedDataOutput(name, label));
}
