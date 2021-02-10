/// \file SxRequest.cpp
/// \brief SxRequest class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include <SxRequest.h>


SxRequest::SxRequest()
{

}

SxRequest::~SxRequest()
{

}

SxData* SxRequest::get_parent(const QString& data_md_uri)
{
    SxProcessedData* processed_data = this->read_processeddata(data_md_uri);
    if (processed_data->get_run_inputs_count() > 0)
    {
        if (processed_data->get_run_input(0)->get_type() == "raw"){
            return this->read_rawdata(processed_data->get_run_input(0)->get_uri());
        }
        else
        {
            return this->read_processeddata(processed_data->get_run_input(0)->get_uri());
        }
    }
    return nullptr;
}

SxRawData* SxRequest::get_origin(const QString& data_md_uri)
{
    SxProcessedData* processed_data = this->read_processeddata(data_md_uri);
    if (processed_data->get_run_inputs_count() > 0)
    {
        if (processed_data->get_run_input(0)->get_type() == "raw"){
            return this->read_rawdata(processed_data->get_run_input(0)->get_uri());
        }
        else
        {
            return this->get_origin(processed_data->get_run_input(0)->get_uri());
        }
    }
    return nullptr;
}
