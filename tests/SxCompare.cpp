/// \file SxCompare.cpp
/// \brief SxCompare implementation
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include "SxCompare.h"


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
        return true;
    }
    return false;
}
