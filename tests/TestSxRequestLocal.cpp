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

    tearDown();
    return 0;
}
