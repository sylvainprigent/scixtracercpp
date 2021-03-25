/// \file CreateMetadata.cpp
/// \brief Functions to create reference metadata for testing
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include "SxTestConfig.h"
#include "CreateMetadata.h"

SxRawData* create_raw_data(){
    SxRawData* raw_data_container2 = new SxRawData();
    raw_data_container2->set_uuid("fake_uuid");
    raw_data_container2->set_name("population1_001.tif");
    raw_data_container2->set_author("Sylvain Prigent");
    raw_data_container2->set_date(new SxDate("2019-03-17"));
    raw_data_container2->set_uri(ref_rawdata_img_uri);
    raw_data_container2->set_format(new SxFormat("tif"));
    SxTags* tags = new SxTags();
    tags->set_tag("Population", "population1");
    tags->set_tag("number", "001");
    raw_data_container2->set_tags(tags);
    return raw_data_container2;
}

SxProcessedData* create_processed_data()
{
    SxProcessedData* processed_data_container2 = new SxProcessedData();
    processed_data_container2->set_uuid("fake_uuid");
    processed_data_container2->set_name("population1_001_o");
    processed_data_container2->set_author("Sylvain Prigent");
    processed_data_container2->set_date(new SxDate("2020-03-04"));
    processed_data_container2->set_uri(ref_processeddata_img_uri);
    processed_data_container2->set_format(new SxFormat("tif"));
    processed_data_container2->set_run(new SxMetadata(ref_process1_run_file, "fake_uuid"));

    processed_data_container2->set_run_input("i", new SxProcessedDataInput("i", new SxMetadata(ref_rawdata_file1, "fake_uuid"), "raw"));
    processed_data_container2->set_run_output(new SxProcessedDataOutput("o", "Denoised image"));

    return processed_data_container2;
}

SxDataset* create_dataset()
{
    SxDataset* container = new SxDataset();
    container->set_uuid("fake_uuid");
    container->set_name("data");
    container->set_data(new SxMetadata(ref_rawdata_file1, "fake_uuid"));
    container->set_data(new SxMetadata(ref_rawdata_file2, "fake_uuid"));
    container->set_data(new SxMetadata(ref_rawdata_file3, "fake_uuid"));
    return container;
}

SxExperiment* create_experiment()
{
    SxExperiment* container = new SxExperiment();
    container->set_uuid("fake_uuid");
    container->set_name("myexperiment");
    container->set_author("Sylvain Prigent");
    container->set_date(new SxDate("2020-03-04"));
    container->set_raw_dataset( new SxDatasetMetadata("data", ref_rawdataset_file, "fake_uuid"));
    container->set_processed_dataset(new SxDatasetMetadata("process1", ref_processeddataset1_file, "fake_uuid"));
    container->set_processed_dataset(new SxDatasetMetadata("process2", ref_processeddataset2_file, "fake_uuid"));
    container->set_tag_key("Population");
    container->set_tag_key("number");
    return container;
}
