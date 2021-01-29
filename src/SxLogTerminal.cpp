/// \file SxLogTerminal.cpp
/// \brief SxLogTerminal class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include <SxLogTerminal.h>

#include <QDebug>

SxLogTerminal::SxLogTerminal()
{

}

SxLogTerminal::~SxLogTerminal()
{

}

qint8 SxLogTerminal::notify(QString status, QString message)
{
    qDebug() << status << ": " << message;
    return 0;
}

qint8 SxLogTerminal::progress(qint8 percentage)
{
    qDebug() << "progress: " << percentage << "%";
    return 0;
}
