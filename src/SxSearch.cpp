/// \file SxSearch.cpp
/// \brief SxSearch class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include "SxSearch.h"
#include "SxException.h"

QList<SxSearchContainer*> SxSearch::query_list_single(QList<SxSearchContainer*>& search_list, const QString& query)
{
    QList<SxSearchContainer*> selected_list;

    if (query.contains("name"))
    {
        QStringList split_query = query.split('=');
        if (split_query.count() != 2){
            throw SxException(QString("Error: the query " + query + "is not correct. Must be (name=value)").toStdString().c_str());
        }
        QString value = split_query[1];
        for (qint16 i = 0 ; i < search_list.count() ; ++i)
        {
            if (search_list[i]->get_name().contains(value))
            {
                selected_list.append(search_list[i]);
            }
        }
        return selected_list;
    }

    if (query.contains("<="))
    {
        QStringList split_query = query.split("<=");
        if (split_query.count() != 2){
            throw SxException(QString("Error: the query " + query + "is not correct. Must be (key<=value)").toStdString().c_str());
        }
        QString key = split_query[0];
        float value = (split_query[1].replace(" ", "")).toFloat();
        for (qint16 i = 0 ; i < search_list.count() ; ++i)
        {
            if (search_list[i]->is_tag(key) && search_list[i]->get_tag(key).replace(" ", "").toFloat() <= value)
            {
                selected_list.append(search_list[i]);
            }
        }
    }

    else if (query.contains(">="))
    {
        QStringList split_query = query.split(">=");
        if (split_query.count() != 2){
            throw SxException(QString("Error: the query " + query + "is not correct. Must be (key>=value)").toStdString().c_str());
        }
        QString key = split_query[0];
        QString value = split_query[1];
        for (qint16 i = 0 ; i < search_list.count() ; ++i)
        {
            if (search_list[i]->is_tag(key) && search_list[i]->get_tag(key).toFloat() >= value.toFloat()){
                selected_list.append(search_list[i]);
            }
        }
    }

    else if (query.contains("="))
    {
        QStringList split_query = query.split("=");
        if (split_query.count() != 2){
            throw SxException(QString("Error: the query " + query + "is not correct. Must be (key=value)").toStdString().c_str());
        }
        QString key = split_query[0];
        QString value = split_query[1];
        for (qint16 i = 0 ; i < search_list.count() ; ++i)
        {
            if (search_list[i]->is_tag(key) && search_list[i]->get_tag(key) == value){
                selected_list.append(search_list[i]);
            }
        }
    }

    else if (query.contains("<"))
    {
        QStringList split_query = query.split("<");
        if (split_query.count() != 2){
            throw SxException(QString("Error: the query " + query + "is not correct. Must be (key<value)").toStdString().c_str());
        }
        QString key = split_query[0];
        QString value = split_query[1];
        for (qint16 i = 0 ; i < search_list.count() ; ++i)
        {
            if (search_list[i]->is_tag(key) && search_list[i]->get_tag(key).toFloat() < value.toFloat()){
                selected_list.append(search_list[i]);
            }
        }
    }

    else if (query.contains(">"))
    {
        QStringList split_query = query.split(">");
        if (split_query.count() != 2){
            throw SxException(QString("Error: the query " + query + "is not correct. Must be (key>value)").toStdString().c_str());
        }
        QString key = split_query[0];
        QString value = split_query[1];
        for (qint16 i = 0 ; i < search_list.count() ; ++i)
        {
            if (search_list[i]->is_tag(key) && search_list[i]->get_tag(key).toFloat() > value.toFloat()){
                selected_list.append(search_list[i]);
            }
        }
    }

     return selected_list;
}
