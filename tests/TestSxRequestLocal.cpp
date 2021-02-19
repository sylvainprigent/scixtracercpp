#include "SxTestConfig.h"
#include <scixtracercpp>

#include "CreateMetadata.h"
#include "SxCompare.h"
#include "SxSerializeJson.h"

#include <QFile>
#include <QDir>
#include <QDebug>

void tearDown(){

    QFile qt_tst_rawdata_file(tst_rawdata_file);
    if (qt_tst_rawdata_file.exists()){
        qt_tst_rawdata_file.remove();
    }
    QFile qt_tst_processeddata_file(tst_processeddata_file);
    if (qt_tst_processeddata_file.exists()){
        qt_tst_processeddata_file.remove();
    }
    QFile qt_tst_dataset_file(tst_dataset_file);
    if (qt_tst_dataset_file.exists()){
        qt_tst_dataset_file.remove();
    }
    QFile qt_tst_experiment_file(tst_experiment_file);
    if (qt_tst_experiment_file.exists()){
        qt_tst_experiment_file.remove();
    }
    QString path = QString(tst_experiment_dir) + QDir::separator() + "myexperiment";
    QDir qt_tst_experiment_dir(path);
    if (qt_tst_experiment_dir.exists()){
        qt_tst_experiment_dir.removeRecursively();
    }
}

qint8 test_simplify_path1(const QString& sep)
{
    QString file = sep+"my"+sep+"computer"+sep+"experiment"+sep+"svdeconv"+sep+".."+sep+"data"+sep+"raw.md.json";
    QString simplified_file = SxRequestLocal::simplify_path(file);

    QString ref = sep+"my"+sep+"computer"+sep+"experiment"+sep+"data"+sep+"raw.md.json";
    qDebug() << "file:" << file;
    qDebug() << "res:" << simplified_file;
    qDebug() << "exp:" << ref;

    if (simplified_file == ref){
        return 0;
    }
    return 1;
}

qint8 test_simplify_path2(const QString& sep)
{
    QString file = sep + "my" + sep + "computer" + sep + "experiment" + sep
            + "svdeconv" + sep + "denoise" + sep + ".." + sep + ".." + sep
            + "data" + sep + "raw.md.json";
    QString simplified_file = SxRequestLocal::simplify_path(file);

    QString ref = sep + "my" + sep + "computer" + sep + "experiment" + sep + "data" + sep + "raw.md.json";
    qDebug() << "file:" << file;
    qDebug() << "res:" << simplified_file;
    qDebug() << "exp:" << ref;

    if (simplified_file == ref)
    {
        return 0;
    }
    return 1;
}

qint8 test_relative_path1(const QString& sep)
{
    QString reference_file = "my" + sep + "computer" + sep + "experiment" + sep + "data" + sep + "rawdata.md.json";
    QString file = "my" + sep + "computer" + sep + "experiment" + sep + "data" + sep + "rawdata.tif";
    QString relative_file = SxRequestLocal::relative_path(file, reference_file);

    qDebug() << "reference_file:" << reference_file;
    qDebug() << "file:" << file;
    qDebug() << "relative_file:" << relative_file;
    qDebug() << "exp:" << "rawdata.tif";

    if (relative_file == "rawdata.tif")
    {
        return 0;
    }
    return 1;
}

qint8 test_relative_path2(const QString& sep)
{
    QString reference_file = "my" + sep + "computer" + sep + "experiment" + sep + "svdeconv" + sep + "processeddata.md.json";
    QString file = "my" + sep + "computer" + sep + "experiment" + sep + "data" + sep + "raw.md.json";
    QString relative_file = SxRequestLocal::relative_path(file, reference_file);

    qDebug() << "reference_file:" << reference_file;
    qDebug() << "file:" << file;
    qDebug() << "relative_file:" << relative_file;
    qDebug() << "exp:" << ".." + sep + "data" + sep + "raw.md.json";

    if (relative_file == ".." + sep + "data" + sep + "raw.md.json")
    {
        return 0;
    }
    return 1;
}

qint8 test_absolute_path(const QString& sep)
{
    QString reference_file = "my" + sep + "computer" + sep + "experiment" + sep + "data" + sep + "rawdata.md.json";
    QString file = "rawdata.tif";
    QString abs_file = SxRequestLocal::absolute_path(file, reference_file);
    QString exp = "my" + sep + "computer" + sep + "experiment" + sep + "data" + sep + "rawdata.tif";

    qDebug() << "reference_file:" << reference_file;
    qDebug() << "file:" << file;
    qDebug() << "abs_file:" << abs_file;
    qDebug() << "exp:" << exp;

    if( abs_file == exp)
    {
        return 0;
    }
    return 1;
}

qint8 test_read_rawdata()
{
    SxRequestLocal request;
    SxRawData* raw_data_container1 = request.read_rawdata(ref_rawdata_file);
    SxRawData* raw_data_container2 = create_raw_data();

    return SxCompare::compare_metadata(raw_data_container1, raw_data_container2);
}

qint8 test_write_rawdata()
{
    SxRawData* raw_data_container2 = create_raw_data();
    SxRequestLocal request;
    request.write_rawdata(raw_data_container2, tst_rawdata_file);

    qDebug() << tst_rawdata_file << " and " << ref_rawdata_file << " must be identical";

    return SxCompare::compare_txt_files(tst_rawdata_file, ref_rawdata_file);
}

qint8 test_read_processeddata()
{
    SxRequestLocal request;
    SxProcessedData* processed_data_container1 = request.read_processeddata(ref_processeddata_file);
    SxProcessedData* processed_data_container2 = create_processed_data();

    return SxCompare::compare_metadata(processed_data_container1, processed_data_container2);
}

qint8 test_write_processeddata()
{
    SxProcessedData* processed_data_container2 = create_processed_data();
    SxRequestLocal request;
    request.write_processeddata(processed_data_container2, tst_processeddata_file);

    return SxCompare::compare_txt_files(tst_processeddata_file, ref_processeddata_file);
}

qint8 test_read_rawdataset()
{
    SxDataset* reff_dataset = create_dataset();
    SxRequestLocal request;
    SxDataset* read_dataset = request.read_rawdataset(ref_dataset_file);

    return SxCompare::compare_metadata(reff_dataset, read_dataset);
}

qint8 test_write_rawdataset()
{
    SxDataset* container = create_dataset();
    SxRequestLocal request;
    request.write_rawdataset(container, tst_dataset_file);

    return SxCompare::compare_txt_files(tst_dataset_file, ref_dataset_file);
}

qint8 test_read_processeddataset()
{
    SxDataset* reff_dataset = create_dataset();
    SxRequestLocal request;
    SxDataset* read_dataset = request.read_processeddataset(ref_dataset_file);
    return SxCompare::compare_metadata(reff_dataset, read_dataset);
}

qint8 test_write_processeddataset()
{
    SxDataset* container = create_dataset();
    SxRequestLocal request;
    request.write_processeddataset(container, tst_dataset_file);

    return SxCompare::compare_txt_files(tst_dataset_file, ref_dataset_file);
}

qint8 test_read_experiment()
{
    SxExperiment* ref_container = create_experiment();
    SxRequestLocal request;
    SxExperiment* read_container = request.read_experiment(ref_experiment_file);

    return SxCompare::compare_metadata(ref_container, read_container);
}

qint8 test_write_experiment()
{
    SxExperiment* container = create_experiment();
    SxRequestLocal request;
    request.write_experiment(container, tst_experiment_file);

    return SxCompare::compare_txt_files(tst_experiment_file, ref_experiment_file);
}

qint8 test_create_experiment()
{
    SxExperiment* container = create_experiment();
    SxRequestLocal request;
    request.create_experiment(container, tst_experiment_dir);
    qint8 t1 = 0;
    QDir qt_exp_dir(QString(tst_experiment_dir) + QDir::separator() + "myexperiment");
    if (!qt_exp_dir.exists()){
        t1 = 1;
    }
    qint8 t2 = 0;
    QFile qt_exp_file(QString(tst_experiment_dir)+"myexperiment"+QDir::separator()+"experiment.md.json");
    if (!qt_exp_file.exists()){
        t2 = 1;
    }
    qint8 t3 = 0;
    QDir qt_data_dir(QString(tst_experiment_dir)+"myexperiment"+QDir::separator()+"data");
    if (!qt_data_dir.exists()){
        t3 = 1;
    }
    qint8 t4 = 0;
    QFile qt_dataset_file(QString(tst_experiment_dir)+"myexperiment"+QDir::separator()+"data"+QDir::separator()+"rawdataset.md.json");
    if (!qt_dataset_file.exists()){
        t4 = 1;
    }
    return t1+t2+t3+t4;
}

int main(void)
{
    QString sep = QDir::separator();
    if(test_simplify_path1(sep))
    {
        return 1;
    }
    if(test_simplify_path2(sep))
    {
        return 1;
    }

    if(test_relative_path1(sep))
    {
        return 1;
    }

    if(test_relative_path2(sep))
    {
        return 1;
    }

    if(test_absolute_path(sep))
    {
        return 1;
    }

    if (test_read_rawdata())
    {
        return 1;
    }

    if (test_write_rawdata())
    {
        return 1;
    }
    if (test_read_processeddata())
    {
        return 1;
    }

    if (test_write_processeddata())
    {
        return 1;
    }

    if (test_read_rawdataset())
    {
        return 1;
    }

    if (test_write_rawdataset())
    {
        return 1;
    }

    if (test_read_processeddataset())
    {
        return 1;
    }

    if (test_write_processeddataset())
    {
        return 1;
    }

    if (test_read_experiment())
    {
        return 1;
    }

    if (test_write_experiment())
    {
        return 1;
    }

    if (test_create_experiment())
    {
        return 1;
    }

    tearDown();
    return 0;
}
