#ifndef AUTORNAMECOLLECTION_H
#define AUTORNAMECOLLECTION_H

#include<QObject>

class autorNameCollection : public QObject
{
    Q_OBJECT
public:
    explicit autorNameCollection(QObject *parent = 0);//继承QObject用与析构

    QStringList getUrls(const QString& name);//get the urllist using autor name

    QStringList getAutorNames();//get all name of the autors

    //add information of a autor into database
    void addAutor(const QString& name,const QString& path);

    ~autorNameCollection();

private:
    void populateDatabase();

};

#endif // AUTORNAMECOLLECTION_H
