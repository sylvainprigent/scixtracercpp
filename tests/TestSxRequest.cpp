#include "SxTestConfig.h"
#include <scixtracercpp>

#include "CreateMetadata.h"
#include "SxCompare.h"
#include "SxSerializeJson.h"

#include <QFile>
#include <QDir>
#include <QDebug>

void tearDown()
{
    // remove myexperiment
    QString path = QString(tst_experiment_dir) + QDir::separator() + "myexperiment";
    //qDebug() << "try to clean the directory: " << path;
    QDir qt_tst_experiment_dir(path);
    if (qt_tst_experiment_dir.exists()){
        //qDebug() << "do the cleaning of: " << path;
        qt_tst_experiment_dir.removeRecursively();
    }
    QFile tst_experiment_qfile(tst_experiment_file);
    if (tst_experiment_qfile.exists())
    {
        tst_experiment_qfile.remove();
    }

    QFile tst_rawdata_qfile(tst_rawdata_file);
    if (tst_rawdata_qfile.exists())
    {
        tst_rawdata_qfile.remove();
    }

    QFile tst_processeddata_qfile(tst_processeddata_file);
    if (tst_processeddata_qfile.exists())
    {
        tst_processeddata_qfile.remove();
    }

    QFile tst_dataset_qfile(tst_dataset_file);
    if (tst_dataset_qfile.exists())
    {
        tst_dataset_qfile.remove();
    }

}

qint8 test_create_experiment()
{
    qDebug() << "create experiment to :" << tst_experiment_dir;
    SxRequestLocal req;
    req.create_experiment("myexperiment", "sprigent", new SxDate("now"), {"key1", "key2"}, tst_experiment_dir);

    QFileInfo exp_dir(QString(tst_experiment_dir) + QDir::separator() + "myexperiment");
    qint8 t1 = 1;
    if (exp_dir.exists() && exp_dir.isDir())
    {
        t1 = 0;
    }

    QFileInfo exp_md(QString(tst_experiment_dir) + QDir::separator() + "myexperiment" + QDir::separator() + "experiment.md.json");
    qint8 t2 = 1;
    if (exp_md.exists() && exp_md.isFile())
    {
        t2 = 0;
    }

    QFileInfo data_dir(QString(tst_experiment_dir) + QDir::separator() + "myexperiment" + QDir::separator() + "data");
    qint8 t3 = 1;
    if (data_dir.exists() && data_dir.isDir())
    {
        t3 = 0;
    }

    QFileInfo data_md(QString(tst_experiment_dir) + QDir::separator() + "myexperiment" + QDir::separator() + "data" + QDir::separator() + "rawdataset.md.json");
    qint8 t4 = 1;
    if (data_md.exists() && data_md.isFile())
    {
        t4 = 0;
    }

    qDebug() << "t1:" << t1;
    qDebug() << "t2:" << t2;
    qDebug() << "t3:" << t3;
    qDebug() << "t4:" << t4;

    return t1+t2+t3+t4;
}

qint8 test_get_experiment()
{
    SxRequestLocal request;
    SxExperiment* experiment = request.get_experiment(ref_experiment_file);
    SxExperiment* ref_experiment = create_experiment();

    qint8 value = SxCompare::compare_metadata(experiment, ref_experiment);
    qDebug() << "get experment cmp:" << value;
    return value;
}

qint8 test_update_experiment()
{
    SxRequestLocal request;
    SxExperiment* experiment = create_experiment();
    experiment->set_md_uri(tst_experiment_file);
    // print(serialize_experiment(experiment))
    request.update_experiment(experiment);

    qint8 value = SxCompare::compare_txt_files(tst_experiment_file, ref_experiment_file);
    qDebug() << "update experiement test:" << value;
    return value;
}

qint8 test_import_data()
{
    SxRequestLocal request;
    SxExperiment* experiment = request.create_experiment("myexperiment", "sprigent", new SxDate("now"), {"key1", "key2"}, tst_experiment_dir);

    QString data_path = test_images_data_file1;
    QString name = "population1_001.tif";
    QString author = "sprigent";
    SxFormat* format_ = new SxFormat("tif");
    SxTags *tags = new SxTags();
    tags->set_tag("Population", "population1");
    tags->set_tag("ID", "001");
    SxRawData *rawData = request.import_data(experiment, data_path, name, author, format_, new SxDate("now"), tags, true);

    // test generated files

    QFileInfo md_qfile(QString(tst_experiment_dir) + QDir::separator() + "myexperiment" + QDir::separator() + "data" + QDir::separator() + "population1_001.md.json");
    qint8 t1 = 1;
    if (md_qfile.exists())
    {
        t1 = 0;
    }

    qint8 t2 = 1;
    if (rawData->get_name() == "population1_001.tif")
    {
        t2 = 0;
    }

    QFileInfo data_qfile(QString(tst_experiment_dir) + QDir::separator() + "myexperiment" + QDir::separator() + "data" + QDir::separator() + "population1_001.tif");
    qint8 t3 = 1;
    if (data_qfile.exists())
    {
        t3 = 0;
    }

    qint8 t4 = 1;
     if (rawData->get_tags()->get_tag("Population") == "population1")
     {
         t4 = 0;
     }
     qint8 t5 = 1;
     if (experiment->get_tags_keys().contains("Population")){
         t5 = 0;
     }

     qDebug() << "test import data:";
     qDebug() << "t1:" << t1;
     qDebug() << "t2:" << t2;
     qDebug() << "t3:" << t3;
     qDebug() << "t4:" << t4;
     qDebug() << "t5:" << t5;

     return t1 + t2 + t3 + t4 + t5;
}

qint8 test_import_dir()
{
    SxRequestLocal request;
    SxExperiment* experiment = request.create_experiment("myexperiment", "sprigent", new SxDate("now"), {"key1", "key2"}, tst_experiment_dir);

    request.import_dir(experiment, test_images_data_dir, "\\.tif$", "sprigent", new SxFormat("tif"), new SxDate("now"), true);

    QString data_dir = QString(tst_experiment_dir) + QDir::separator() + "myexperiment" + QDir::separator() + "data";
    QDir data_qdir(data_dir);
    qint32 data_files_count = data_qdir.count();
    qDebug() << "data_files_count=" << data_files_count;
    // count the number of imported files
    qint8 t1 = 1;
    if (data_files_count == 83)
    {
        t1 = 0;
    }
    // count the number of lines in the rawdataset.md.json file
    qint8 t2 = 1;
    QFile file(data_dir+QDir::separator()+"rawdataset.md.json");
    qint32 number_of_lines = 0;
    file.open(QIODevice::ReadOnly);
    QString line;
    QTextStream in(&file);
    while( !in.atEnd())
    {
        line=in.readLine();
        number_of_lines++;
    }
    if (number_of_lines == 166)
    {
        t2 = 0;
    }

    qDebug() << "test import dir:";
    qDebug() << "t1:" << t1;
    qDebug() << "t2:" << t2;
    return t1+t2;
}

qint8 test_tag_from_name()
{
    SxRequestLocal request;
    SxExperiment* experiment = request.create_experiment("myexperiment", "sprigent", new SxDate("now"), {"key1", "key2"}, tst_experiment_dir);

    request.import_dir(experiment, test_images_data_dir, "\\.tif$", "sprigent", new SxFormat("tif"), new SxDate("now"), true);

    request.tag_from_name(experiment, "Population",{"population1", "population2"});
    // test if tag Population in the experiment metadata
    qint8 t1 = 1;
    if (experiment->get_tags_keys().contains("Population"))
    {
        t1 = 0;
    }
    // test few images tags
    QString data_dir = QString(tst_experiment_dir) + QDir::separator() + "myexperiment" + QDir::separator() + "data" + QDir::separator();
    SxRawData* data1 = request.get_rawdata(data_dir + QDir::separator() + "population1_012.md.json");

    qint8 t2 = 1;
    if ( data1->get_tags()->get_keys().contains("Population") && data1->get_tags()->get_tag("Population") == "population1")
    {
        t2 = 0;
    }

    SxRawData* data2 = request.get_rawdata(data_dir + QDir::separator() + "population2_011.md.json");
    qint8 t3 = 1;
    if (data2->get_tags()->get_keys().contains("Population") && data2->get_tags()->get_tag("Population") == "population2")
    {
        t3 = 0;
    }

    qDebug() << "test tag from name:";
    qDebug() << "t1:" << t1;
    qDebug() << "t2:" << t2;
    qDebug() << "t3:" << t3;
    return t1 + t2 + t3;
}

qint8 test_tag_using_separator()
{
    SxRequestLocal request;
    SxExperiment* experiment = request.create_experiment("myexperiment", "sprigent", new SxDate("now"), {"key1", "key2"}, tst_experiment_dir);

    request.import_dir(experiment, test_images_data_dir, "\\.tif$", "sprigent", new SxFormat("tif"), new SxDate("now"), true);

     request.tag_using_separator(experiment, "ID", "_", 1);
     // test if tag ID in the experiment metadata
     qint8 t1 = 1;
     if (experiment->get_tags_keys().contains("ID"))
     {
         t1 = 0;
     }
     // test few images tags
     QString data_dir = QString(tst_experiment_dir) + QDir::separator() + "myexperiment" + QDir::separator() + "data" + QDir::separator();
     SxRawData* data1 = request.get_rawdata(data_dir + QDir::separator() + "population1_012.md.json");

     qint8 t2 = 1;
     if (data1->get_tags()->get_keys().contains("ID") && data1->get_tags()->get_tag("ID")== "012")
     {
         t2 = 0;
     }

     SxRawData* data2 = request.get_rawdata(data_dir + QDir::separator() + "population2_011.md.json");
     qint8 t3 = 1;
     if (data2->get_tags()->get_keys().contains("ID") && data2->get_tags()->get_tag("ID")== "011")
     {
         t3 = 0;
     }

     qDebug() << "test_tag_using_separator:";
     qDebug() << "t1:" << t1;
     qDebug() << "t2:" << t2;
     qDebug() << "t3:" << t3;
     return t1 + t2 + t3;
}

qint8 test_get_rawdata()
{
    SxRequestLocal request;
    SxRawData* raw_data_read = request.get_rawdata(ref_rawdata_file);
    SxRawData* raw_data_ref = create_raw_data();
    qint8 value = SxCompare::compare_metadata(raw_data_read, raw_data_ref);
    qDebug() << "test_get_rawdata cmp:" << value;
    return value;
}

qint8 test_update_rawdata()
{
    SxRequestLocal request;
    SxRawData* raw_data = create_raw_data();
    raw_data->set_md_uri(tst_rawdata_file);
    request.update_rawdata(raw_data);

    qint8 value = SxCompare::compare_txt_files(tst_rawdata_file, ref_rawdata_file);
    qDebug() << "test_get_rawdata cmp:" << value;
    return value;
}

qint8 test_get_processeddata()
{
    SxRequestLocal request;
    SxProcessedData* processed_data_read = request.get_processeddata(ref_processeddata_file);
    SxProcessedData* processed_data_ref = create_processed_data();

    qint8 value = SxCompare::compare_metadata(processed_data_read, processed_data_ref);
    qDebug() << "test_get_processeddata cmp:" << value;
    return value;
}

qint8 test_update_processeddata()
{
    SxRequestLocal request;
    SxProcessedData* processed_data = create_processed_data();
    processed_data->set_md_uri(tst_processeddata_file);
    request.update_processeddata(processed_data);
    qint8 value = SxCompare::compare_txt_files(tst_processeddata_file, ref_processeddata_file);
    qDebug() << "test_update_processeddata cmp:" << value;
    return value;
}

qint8 test_get_dataset_from_uri()
{
    SxRequestLocal request;
    SxDataset* ref_dataset = create_dataset();
    SxDataset* read_dataset = request.get_dataset_from_uri(ref_dataset_file);

    qint8 value = SxCompare::compare_metadata(ref_dataset, read_dataset);
    qDebug() << "test_get_dataset_from_uri cmp:" << value;
    return value;
}

qint8 test_update_dataset()
{
    SxRequestLocal request;
    SxDataset* container = create_dataset();
    container->set_md_uri(tst_dataset_file);
    request.update_dataset(container);

    qint8 value = SxCompare::compare_txt_files(tst_dataset_file, ref_dataset_file);
    qDebug() << "test_update_dataset cmp:" << value;
    return value;
}

qint8 test_get_rawdataset()
{
    SxRequestLocal request;
    SxExperiment* experiment = request.get_experiment(ref_experiment_file);
    SxDataset* read_dataset = request.get_rawdataset(experiment);
    SxDataset* ref_dataset = create_dataset();

    qint8 value = SxCompare::compare_metadata(ref_dataset, read_dataset);
    qDebug() << "test_get_rawdataset cmp:" << value;
    return value;
}

qint8 test_get_parent()
{
    SxRequestLocal request;
    SxProcessedData* processed_data = request.get_processeddata(ref_processed2data2_file);
    SxData* parent_data = request.get_parent(processed_data);
    qint8 cmp = 1;
    qDebug() << "get parent original name " <<  processed_data->get_name();
    qDebug() << "get parent name " <<  parent_data->get_name();
    if (parent_data->get_name() == "population1_002_o")
    {
        cmp = 0;
    }
    qDebug() << "test_get_parent cmp:" << cmp;
    return cmp;
}

qint8 test_get_origin()
{
    SxRequestLocal request;
    SxProcessedData* processed_data = request.get_processeddata(ref_processed2data2_file);
    SxRawData* origin_data = request.get_origin(processed_data);
    qint8 cmp = 1;
    qDebug() << "get origin original name " <<  processed_data->get_name();
    qDebug() << "get origin name " <<  origin_data->get_name();
    if (origin_data->get_name() == "population1_002.tif")
    {
        cmp = 0;
    }
    qDebug() << "test_get_origin cmp:" << cmp;
    return cmp;
}

qint8 test_get_dataset_raw()
{
    SxRequestLocal request;
    SxExperiment* experiment = request.get_experiment(ref_experiment_file);
    SxDataset* dataset = request.get_dataset(experiment, "data");
    qint8 cmp = 1;
    if (dataset->get_name() == "data")
    {
        cmp = 0;
    }
    qDebug() << "test_get_dataset_raw cmp:" << cmp;
    return cmp;
}

qint8 test_get_dataset_processed()
{
    SxRequestLocal request;
    SxExperiment* experiment = request.get_experiment(ref_experiment_file);
    SxDataset* dataset = request.get_dataset(experiment, "process1");
    qint8 cmp = 1;
    if (dataset->get_name() == "process1")
    {
        cmp = 0;
    }
    qDebug() << "test_get_dataset_processed cmp:" << cmp;
    return cmp;
}

qint8 test_get_data()
{
    SxRequestLocal request;
    SxExperiment* experiment = request.get_experiment(ref_experiment_file);
    SxDataset* dataset = request.get_dataset(experiment, "process1");
    QList<SxData*> data = request.get_data(dataset, "name=population1_001_o", "o");
    qint8 cmp = 1;
    if (data[0]->get_name() == "population1_001_o")
    {
        cmp = 0;
    }
    qDebug() << "test_get_data cmp:" << cmp;
    return cmp;
}

qint8 test_create_dataset()
{
    SxRequestLocal request;
    SxExperiment* experiment = request.create_experiment("myexperiment", "sprigent", new SxDate("now"), {"key1", "key2"}, tst_experiment_dir);
    request.create_dataset(experiment, "myprocess");

    qint8 t1 = 1;
    QString dataset_file = QString(tst_experiment_dir) + QDir::separator() + "myexperiment" + QDir::separator() + "myprocess"+ QDir::separator() + "processeddataset.md.json";
    if (QFile::exists(dataset_file))
    {
        t1 = 0;
    }

    qint8 t2 = 1;
    SxDataset* dataset = request.get_dataset(experiment, "myprocess");
    if (dataset->get_name() == "myprocess")
    {
        t2 = 0;
    }

    qDebug() << "test_create_dataset:";
    qDebug() << "t1:" << t1;
    qDebug() << "t2:" << t2;
    return t1 + t2;
}

qint8 test_create_run()
{
    SxRequestLocal request;
    SxExperiment* experiment = request.create_experiment("myexperiment", "sprigent", new SxDate("now"), {"key1", "key2"}, tst_experiment_dir);

    SxDataset* dataset = request.create_dataset(experiment, "threshold");
    SxRun* run_info = new SxRun();
    run_info->set_process("threshold", "uniqueIdOfMyAlgorithm");
    run_info->add_input("image", "data","Population=Population1");
    run_info->add_parameter("threshold", "100");
    request.create_run(dataset, run_info);

    qint8 t1 = 1;
    QString run_file =QString(tst_experiment_dir) + QDir::separator() + "myexperiment" + QDir::separator() + "threshold" + QDir::separator() + "run.md.json";
    if (QFile::exists(run_file)){
        t1 = 0;
    }

    qint8 t2 = 1;
    if (run_info->get_process_name() == "threshold")
    {
        t2 = 0;
    }

    qDebug() << "test_create_run:";
    qDebug() << "t1:" << t1;
    qDebug() << "t2:" << t2;
    return t1 + t2;
}

qint8 test_get_run()
{
    SxRequestLocal request;
    SxRun* run = request.get_run(ref_run_file);
    qint8 t1 = 1;
    if (run->get_process_name() =="SPARTION 2D")
    {
        t1 = 0;
    }
    qint8 t2 = 1;
    if (run->get_processed_dataset()->get_uuid() == "fake_uuid")
    {
        t2 = 0;
    }
    qDebug() << "test_get_run:";
    qDebug() << "t1:" << t1;
    qDebug() << "t2:" << t2;
    return t1 + t2;
}

qint8 test_create_data()
{
    SxRequestLocal request;
    SxExperiment* experiment = request.create_experiment("myexperiment", "sprigent", new SxDate("now"), {"key1", "key2"}, tst_experiment_dir);
    request.import_dir(experiment, test_images_data_dir, "\\.tif$", "sprigent", new SxFormat("tif"), new SxDate("now"), true);

    SxDataset* raw_dataset = request.get_dataset(experiment, "data");

    QList<SxData*> raw_data_list = request.get_data(raw_dataset, "name=population1_001");
    SxData* raw_data = raw_data_list[0];

    SxDataset* dataset = request.create_dataset(experiment, "threshold");
    SxRun* run_info = new SxRun();
    run_info->set_process("threshold", "uniqueIdOfMyAlgorithm");
    run_info->add_input("image", "data", "Population=Population1");
    run_info->add_parameter("threshold", "100");
    request.create_run(dataset, run_info);
    SxProcessedData* processed_data = new SxProcessedData();
    QString output_image_path = QString(tst_experiment_dir) + QDir::separator() + "myexperiment" + QDir::separator() + "threshold" + QDir::separator() + "o_" + raw_data->get_name() +".tif";

    processed_data->set_info("myimage","sprigent", new SxDate("now"), new SxFormat("tif"), output_image_path);
    processed_data->add_input("i", raw_data, raw_data->get_type());
    processed_data->set_output("o", "threshold");

    request.create_data(dataset, run_info, processed_data);

    qint8 t1 = 1;
    if (QFile::exists(processed_data->get_md_uri()))
    {
        t1 = 0;
    }
    qint8 t2 = 1;
    if (processed_data->get_name() == "myimage")
    {
        t2 = 0;
    }
    qint8 t3 = 1;
    if (processed_data->get_uri().contains("o_population1_001.tif.tif"))
    {
        t3 = 0;
    }
    qint8 t4 = 1;
    if (processed_data->get_run()->get_md_uri().contains("run.md.json"))
    {
        t4 = 0;
    }

    qDebug() << "test_create_data:";
    qDebug() << "t1:" << t1;
    qDebug() << "t2:" << t2;
    qDebug() << "t3:" << t3;
    qDebug() << "t4:" << t4;
    return t1 + t2 + t3 + t4;
}

int main(void)
{
    if (test_create_experiment())
    {
        return 1;
    }
    tearDown();

    if (test_get_experiment())
    {
        return 1;
    }

    if (test_update_experiment())
    {
        return 1;
    }
    tearDown();

    if (test_import_data())
    {
        return 1;
    }
    tearDown();

    if (test_import_dir()){
        return 1;
    }
    tearDown();

    if (test_tag_from_name()){
        return 1;
    }
    tearDown();

    if (test_tag_using_separator()){
        return 1;
    }
    tearDown();

    if (test_get_rawdata()){
        return 1;
    }
    tearDown();


    if (test_update_rawdata()){
        return 1;
    }
    tearDown();


    if (test_get_processeddata()){
        return 1;
    }

    if (test_update_processeddata()){
        return 1;
    }

    if (test_get_dataset_from_uri()){
        return 1;
    }

    if(test_update_dataset()){
        return 1;
    }

    if (test_get_rawdataset()){
        return 1;
    }

    if (test_get_parent()){
        return 1;
    }

    if (test_get_origin()){
        return 1;
    }

    if(test_get_dataset_raw()){
        return 1;
    }

    if(test_get_dataset_processed()){
        return 1;
    }

    if (test_get_data()){
        return 1;
    }

    if (test_create_dataset()){
        return 1;
    }
    tearDown();

    if (test_create_run()){
        return 1;
    }
    tearDown();

    if (test_get_run()){
        return 1;
    }
    tearDown();

    if (test_create_data()){
        return 1;
    }
    tearDown();

    return 0;
}
