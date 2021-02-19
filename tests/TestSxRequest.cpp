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
}

SxExperiment* _create_experiment()
{
    SxExperiment* container = create_experiment();
    container->set_md_uri(tst_experiment_dir);
    SxRequestLocal request;
    request.create_experiment(container, tst_experiment_dir);
    return container;
}

qint8 test_import_data()
{
    SxExperiment* experiment = _create_experiment();
    SxRequestLocal request;
    QString data_path = test_images_data_file1;
    QString name = "population1_001.tif";
    SxUser *author = new SxUser("Sylvain Prigent");
    SxFormat *format = new SxFormat("tif");
    SxDate* date = new SxDate("2021-02-11");
    SxTags* tags = new SxTags();
    tags->set_tag("Population", "p1");
    SxRawData* data = request.import_data_experiment(experiment, data_path, name, author, format, date, tags, true);

    QFile qt_md_data_file(QString(tst_experiment_dir)+QDir::separator()+"myexperiment"+QDir::separator()+"data"+QDir::separator()+"population1_001.md.json");
    qint8 t1 = 1;
    if (qt_md_data_file.exists())
    {
        t1 = 0;
    }
    qint8 t2 = 1;
    if (data->get_name() == "population1_001.tif")
    {
        t2 = 0;
    }
    qint8 t3 = 1;
    QFile qt_data_file(QString(tst_experiment_dir)+QDir::separator()+"myexperiment"+QDir::separator()+"data"+QDir::separator()+"population1_001.tif");
    if (qt_data_file.exists())
    {
        t3 = 0;
    }
    qint8 t4 = 1;
    if (data->get_tags()->get_tag("Population") == "p1")
    {
        t4 = 0;
    }
    return t1+t2+t3+t4;
}

qint8 test_import_dir()
{
    // run the command
    SxExperiment* experiment = _create_experiment();
    SxRequestLocal request;
    QString dir_uri = test_images_data_dir;
    QString filter_ = "\\.tif$";
    SxUser *author = new SxUser("Sylvain Prigent");
    SxFormat *format = new SxFormat("tif");
    SxDate* date = new SxDate("2021-02-11");
    request.import_dir_experiment(experiment, dir_uri, filter_, author, format, date, true);

    // run the checks
    QString data_dir = QString(tst_experiment_dir) + QDir::separator() + "myexperiment" + QDir::separator() + "data";
    // count the number of imported files
    QDir qt_raw_data_dir(data_dir);
    QStringList data_files = qt_raw_data_dir.entryList(QDir::Files);
    qint8 t1 = 1;
    if (data_files.count() == 81){
        t1 = 0;
    }
    // count the number of lines in the rawdataset.md.json file
    qint8 t2 = 1;
    QFile file(data_dir+QDir::separator()+"rawdataset.md.json");
    int line_count=0;
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    while( !in.atEnd())
    {
        in.readLine();
        line_count++;
    }
    if (line_count == 45)
    {
        t2 = 0;
    }
    return t1 + t2;
}

qint8 test_tag_from_name()
{
    // run the command
    SxExperiment* experiment = _create_experiment();
    SxRequestLocal request;
    QString dir_uri = test_images_data_dir;
    QString filter_ = "\\.tif$";
    SxUser *author = new SxUser("Sylvain Prigent");
    SxFormat *format = new SxFormat("tif");
    SxDate* date = new SxDate("2021-02-11");
    request.import_dir_experiment(experiment, dir_uri, filter_, author, format, date, true);

    QStringList values = {"population1", "population2"};
    request.tag_from_name(experiment, "Population", values);

    // check
    // test if tag Population in the experiment metadata
    qint8 t1 = 1;
    if (experiment->get_tags_keys().contains("Population"))
    {
        t1 = 0;
    }
    // test few images tags
    SxRawData* data1 = request.read_rawdata(QString(tst_experiment_dir)+"myexperiment"+QDir::separator()+"data"+QDir::separator()+"population1_012.md.json");
    qint8 t2 = 1;
    if (data1->get_tags()->get_keys().contains("Population") &&
            data1->get_tags()->get_tag("Population") == "population1")
    {
        t2 = 0;
    }
    SxRawData* data2 = request.read_rawdata(QString(tst_experiment_dir)+"myexperiment"+QDir::separator()+"data"+QDir::separator()+"population2_011.md.json");
    qint8 t3 = 1;
    if (data2->get_tags()->get_keys().contains("Population") &&
            data2->get_tags()->get_tag("Population") == "population2")
    {
        t3 = 0;
    }

    //qDebug() << "t1=" << t1 << ", t2=" << t2 << ", t3=" << t3;
    return t1+t2+t3;
}

qint8 test_tag_using_separator()
{
    // run the command
    SxExperiment* experiment = _create_experiment();
    SxRequestLocal request;
    QString dir_uri = test_images_data_dir;
    QString filter_ = "\\.tif$";
    SxUser *author = new SxUser("Sylvain Prigent");
    SxFormat *format = new SxFormat("tif");
    SxDate* date = new SxDate("2021-02-11");
    request.import_dir_experiment(experiment, dir_uri, filter_, author, format, date, true);
    request.tag_using_seperator(experiment, "ID", "_", 1);

    // checks
    // test if tag ID in the experiment metadata
    qint8 t1 = 1;
    if ( experiment->get_tags_keys().contains("ID") )
    {
        t1 = 0;
    }
    // test few images tags
    SxRawData* data1 = request.read_rawdata(QString(tst_experiment_dir)+"myexperiment"+QDir::separator()+"data"+QDir::separator()+"population1_012.md.json");
    qint8 t2 = 1;
    if ( data1->get_tags()->get_keys().contains("ID") &&
         data1->get_tags()->get_tag("ID") == "012")
    {
        t2 = 0;
    }
    SxRawData* data2 = request.read_rawdata(QString(tst_experiment_dir)+"myexperiment"+QDir::separator()+"data"+QDir::separator()+"population2_011.md.json");
    qint8 t3 = 1;
    if (data2->get_tags()->get_keys().contains("ID") &&
            data2->get_tags()->get_tag("ID") == "011")
    {
        t3 = 0;
    }
    return t1+t2+t3;
}

qint8 test_get_data1()
{
    // run the command
    SxExperiment* experiment = _create_experiment();
    SxRequestLocal request;
    QString dir_uri = test_images_data_dir;
    QString filter_ = "\\.tif$";
    SxUser *author = new SxUser("Sylvain Prigent");
    SxFormat *format = new SxFormat("tif");
    SxDate* date = new SxDate("2021-02-11");
    request.import_dir_experiment(experiment, dir_uri, filter_, author, format, date, true);
    QStringList values = {"population1", "popilation2"};
    request.tag_from_name(experiment, "Population", values);
    request.tag_using_seperator(experiment, "ID", "_", 1);

    // get data
    QStringList data_list = request.get_data(experiment, "data", "Population=population1");

    if (data_list.count() == 20)
    {
        return 0;
    }
    return 1;
}

qint8 test_get_data2()
{
    // run the command
    SxExperiment* experiment = _create_experiment();
    SxRequestLocal request;
    QString dir_uri = test_images_data_dir;
    QString filter_ = "\\.tif$";
    SxUser *author = new SxUser("Sylvain Prigent");
    SxFormat *format = new SxFormat("tif");
    SxDate* date = new SxDate("2021-02-11");
    request.import_dir_experiment(experiment, dir_uri, filter_, author, format, date, true);
    QStringList values = {"population1", "population2"};
    request.tag_from_name(experiment, "Population", values);
    request.tag_using_seperator(experiment, "ID", "_", 1);

    // get data
    QStringList data_list = request.get_data(experiment, "data", "Population=population2 AND ID<=2");
    //qDebug() << "query res = " << data_list;
    if (data_list.count() == 2){
        return 0;
    }
    return 1;
}

qint8 test_parent()
{
    SxRequestLocal request;
    SxData* parent_data = request.get_parent(ref_processed2data2_file);

    qDebug() << "parent data name=" << parent_data->get_name();

    if (parent_data->get_name() == "population1_002_o")
    {
        return 0;
    }
    return 1;
}

qint8 test_origin()
{
    SxRequestLocal request;
    SxData* origin_data = request.get_origin(ref_processed2data2_file);

    qDebug() << "origin data name=" << origin_data->get_name();

    if (origin_data->get_name() == "population1_002.tif")
    {
        return 0;
    }
    return 1;
}

int main(void)
{
    if (test_import_data()){
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

    if (test_get_data1()){
        return 1;
    }
    tearDown();

    if (test_get_data2()){
        return 1;
    }
    tearDown();

    if (test_parent()){
        return 1;
    }

    if (test_origin()){
        return 1;
    }

    tearDown();

    return 0;
}
