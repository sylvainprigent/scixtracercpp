/// \file SxCompare.cpp
/// \brief SxCompare implementation
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include "SxCompare.h"
#include "../src/SxSerializeJson.h"

bool SxCompare::compare_txt_files(const QString& file1, const QString& file2)
{
    QFile qfile1(file1);
    if (!qfile1.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QFile qfile2(file2);
    if (!qfile2.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QString content1 = QString::fromStdString(qfile1.readAll().toStdString());
    QString content2 = QString::fromStdString(qfile2.readAll().toStdString());

    if (content1 == content2){
        return false;
    }
    return true;
}

bool SxCompare::compare_metadata(SxMetadata* container1, SxMetadata* container2)
{
    SxSerializeJson serializer;
    QString c1 = serializer.serialize(container1);
    QString c2 = serializer.serialize(container2);

    qDebug() << "c1:" << c1;
    qDebug() << "c2:" << c2;

    if (c1 == c2){
        return false;
    }
    return true;
}
