/// \file SxLogFile.cpp
/// \brief SxLogFile class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include <SxLogFile.h>

#include <QDebug>

SxLogFile::SxLogFile()
{

}

SxLogFile::~SxLogFile()
{
    if (m_file){
        delete m_file;
    }
}

qint8 SxLogFile::open_file(QString file)
{
    m_file = new QFile(file);
    if ( !m_file->open( QIODevice::WriteOnly | QIODevice::Append )){
        return 1;
    }
    return 0;
}

qint8 SxLogFile::close_file()
{
    if (m_file){
        m_file->close();
    }
    else{
        return 1;
    }
    return 0;
}

qint8 SxLogFile::notify(QString status, QString message)
{
    qDebug() << status << ": " << message;
    return 0;
}

qint8 SxLogFile::progress(qint8 percentage)
{
    qDebug() << "progress: " << percentage << "%";
    return 0;
}
