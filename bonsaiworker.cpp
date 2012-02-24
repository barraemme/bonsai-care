#include <QtCore/QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QtCore/QThread>
#include <QDir>
#include <QVariant>
#include <QBuffer>
#include <QFile>
#include <QXmlStreamReader>
#include <QtXmlPatterns>
#include <QXmlQuery>
#include "bonsaiworker.h"
#include "bonsaiserializer.h"

BonsaiWorker::BonsaiWorker()
{
    // Find QSLite driver
    db = QSqlDatabase::addDatabase("QSQLITE", "bonsaiWorkerConnection");
    // http://doc.trolltech.com/sql-driver.html#qsqlite

    QString path(QDir::home().path());
    path.append(QDir::separator()).append("Bonsai.db.sqlite");
    path = QDir::toNativeSeparators(path);
    db.setDatabaseName(path);
}

BonsaiWorker::~BonsaiWorker(){
    db.close();
}

void BonsaiWorker::fetchAllSpecies() {

    qDebug() << Q_FUNC_INFO << QThread::currentThread();
    // We'll parse the example.xml
    /*QFile* file = new QFile(":/resources/db.xml");
    // If we can't open it, let's show an error message.
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "parseXML, Couldn't open db.xml";
            emit fetchSpeciesDone();
            return;
    }
    // QXmlStreamReader takes any QIODevice.
    QXmlStreamReader xml(file);

    // We'll parse the XML until we reach end of it.
    while(!xml.atEnd() && !xml.hasError()) {
            // Read next element.
            QXmlStreamReader::TokenType token = xml.readNext();
            // If token is just StartDocument, we'll go to next.
            if(token == QXmlStreamReader::StartDocument) {
                    continue;
            }
            // If token is StartElement, we'll see if we can read it.
            if(token == QXmlStreamReader::StartElement) {
                    // If it's named persons, we'll go to the next.
                    if(xml.name() == "species") {
                            continue;
                    }
                    // If it's named person, we'll dig the information from there.
                    if(xml.name() == "specie") {

                        QXmlStreamAttributes attrs = xml.attributes();
                        //get value of each attribute from QXmlStreamAttributes
                        QStringRef fID = attrs.value("id");
                        QStringRef fname = attrs.value("name");
                        Specie* item = new Specie(fID.toString().toInt(), fname.toString());

                        //xml.readNext();
                        while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
                                        xml.name() == "specie")) {
                                if(xml.tokenType() == QXmlStreamReader::StartElement) {
                                        if(xml.name() == "firstname") {
                                                this->addElementDataToMap(xml, person);
                                        }

                                        if(xml.name() == "surname") {
                                                this->addElementDataToMap(xml, person);
                                        }

                                        if(xml.name() == "email") {
                                                this->addElementDataToMap(xml, person);
                                        }

                                        if(xml.name() == "website") {
                                                this->addElementDataToMap(xml, person);
                                        }
                                }

                                xml.readNext();
                        }//

                        emit specieRowFetchDone(item);
                    }
            }
    }
    // Error handling.
   if(xml.hasError()) {
       qDebug() << xml.errorString();
    }
    xml.clear();*/
    this->parseSpeciesWithXQuery();
    emit fetchSpeciesDone();
    qDebug() << "END " << Q_FUNC_INFO << QThread::currentThread();
}

void BonsaiWorker::parseSpeciesWithXQuery(){

    QFile sourceDocument(":/resources/db.xml");
    QFile xq(":/resources/species.xq");

    if ( !sourceDocument.exists()){
        qDebug() << "sourceDocument not exist";
        return;
    }

    if (!sourceDocument.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "sourceDocument not ReadOnly";
        return;
    }

    if ( !xq.exists()){
        qDebug() << "xq not exist";
        return;
    }

    if (!sourceDocument.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "xq not ReadOnly";
        return;
    }


    QXmlQuery query;
    query.bindVariable("inputDocument", &sourceDocument);
    query.setQuery(&xq, QUrl::fromLocalFile(xq.fileName()));

    if( query.isValid() )
    {
        BonsaiSerializer serializer(query.namePool());

        if (query.evaluateTo(&serializer))
        {
            foreach (Specie* specie, serializer.species) {
                emit specieRowFetchDone(specie);
            }
        }
    }

}

void BonsaiWorker::fetchAllBonsai() {

    int itemId;

    qDebug() << Q_FUNC_INFO << QThread::currentThread();
    db.open();    
    QSqlQuery query(db);
    if(!query.exec("select id, item_id, date from bonsai"))
        qDebug() << query.lastError().text();

    while (query.next()) {
        itemId = query.value(1).toInt();        
        Bonsai* item = new Bonsai(query.value(0).toInt(),
                                  query.value(2).toInt(),                                  
                                  itemId
                                  );

        //TODO emit signal after N fetches
        qDebug() << "emit fetched(item)";
        emit bonsaiRowFetchDone(item);
    }

    db.close();
    emit fetchBonsaiDone();
    qDebug() << "END" << Q_FUNC_INFO << QThread::currentThread();
}

void BonsaiWorker::insertBonsai(const int specieId, const int year)
{
    bool ret = false;

    int id = this->nextId();    

    qDebug() << Q_FUNC_INFO << QThread::currentThread();
    db.open();

    QSqlQuery query(db);
    ret = query.exec(QString("insert into bonsai values(%1,'%2',%3)").arg(id).arg(
                         specieId).arg(year));
    if( !ret )
        qDebug() << query.lastError();

    Bonsai* item = new Bonsai(id, year, specieId);
    db.close();
    emit bonsaiRowFetchDone(item);
    //emit jobDone();
    qDebug() << "END" << Q_FUNC_INFO << QThread::currentThread();
}

int BonsaiWorker::nextId()
{
    int ret = 0;
    if (db.isOpen()) {
        QSqlQuery query("select id from id", db);
        if (query.next()) {
            // Get last used id
            ret = query.value(0).toInt();
            // Increase that
            ret++;
            // Store new value
            query.exec(QString("update id set id=%1 where id=%2").arg(ret).arg(ret - 1));
        }
        else {
            // Set first id to zero
            query.exec("insert into id values(1)");
            ret = 1;
        }
    }

    return ret;
}

