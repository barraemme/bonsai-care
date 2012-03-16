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
#include "operation.h"
#include "slot.h"
#include "operationmodel.h"

BonsaiWorker::BonsaiWorker()
{
    // Find QSLite driver
    db = QSqlDatabase::database("bonsaiConnection");

}

BonsaiWorker::~BonsaiWorker(){

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

                        emit fetchSpecieRecordDone(item);
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

    QFile specieDB(":/resources/db.xml");
    QFile specieQuery(":/resources/species.xq");

    if ( !specieDB.exists() || !specieDB.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Error opening Specie database";
        return;
    }

    if ( !specieQuery.exists() || !specieQuery.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Error opening query file";
        return;
    }

    QXmlQuery query;
    query.bindVariable("inputDocument", &specieDB);
    query.setQuery(&specieQuery/*, QUrl::fromLocalFile(xq.fileName())*/);

    if( query.isValid() )
    {
        BonsaiSerializer serializer(query.namePool());

        if (query.evaluateTo(&serializer))
        {
            for (int i = 0; i < serializer.species.size(); i++) {
                emit fetchSpecieRecordDone(new Specie(serializer.species.at(i)));
            }
        }
    }

    specieQuery.close();
    specieDB.close();

}

void BonsaiWorker::fetchAllBonsai() {

    int specieId;
    OperationModel* opm;
    qDebug() << Q_FUNC_INFO << QThread::currentThread();
    //TODO if db open
    QSqlQuery query(db);
    if(!query.exec("select id, item_id, date from bonsai"))
        qDebug() << query.lastError().text();

    while (query.next()) {
        specieId = query.value(1).toInt();
        opm = getOperations(query.value(0).toInt(), QDate::currentDate());
        Bonsai* item = new Bonsai(query.value(0).toInt(),
                                  query.value(2).toInt(),                                  
                                  specieId,
                                  opm
                                  );
        this->schedule(item);
        //TODO emit signal after N fetches
        //qDebug() << "emit fetched(item)";
        emit fetchBonsaiRecordDone(item);
    }

    emit fetchBonsaiDone();
    qDebug() << "END" << Q_FUNC_INFO << QThread::currentThread();
}

OperationModel* BonsaiWorker::getOperations(const int bonsai_id, const QDate &date){
    qDebug() << Q_FUNC_INFO << QThread::currentThread();
    //TODO if db open
    QSqlQuery query(db);

    query.prepare("SELECT id, name, type, bonsai_id, last_date FROM operations  WHERE bonsai_id = ? AND last_date = ? ");
    query.bindValue(0, bonsai_id);
    query.bindValue(1, date.toJulianDay());

    if(!query.exec())
        qDebug() << query.lastError().text();

    OperationModel* opm = new OperationModel(bonsai_id);
    while (query.next()) {
        Operation* op = new Operation();
        op->setIndex(query.value(0).toInt());
        op->setName(query.value(1).toString());
        op->setType(query.value(2).toInt());
        op->setBonsaiId(query.value(3).toInt());
        op->setLastDate(QDate::fromJulianDay(query.value(4).toInt()));
        opm->addRow(*op);
    }

    qDebug() << "END" << Q_FUNC_INFO << QThread::currentThread();
    return opm;
}

void BonsaiWorker::fetchSlot(const int bonsai_id, const QDate &date) {

    qDebug() << Q_FUNC_INFO << QThread::currentThread();
    //TODO if db open
    QSqlQuery query(db);
    //TODO ripristinare query
    query.prepare("SELECT id, name, type, bonsai_id, last_date FROM operations  ");//WHERE bonsai_id = ? AND last_date = ? ");
    //query.bindValue(0, bonsai_id);
    //query.bindValue(1, date.toJulianDay());

    if(!query.exec())
        qDebug() << query.lastError().text();

    OperationModel* opm = new OperationModel(bonsai_id);
    while (query.next()) {
        Operation* op = new Operation();
        op->setIndex(query.value(0).toInt());
        op->setName(query.value(1).toString());
        op->setType(query.value(2).toInt());
        op->setBonsaiId(query.value(3).toInt());
        op->setLastDate(QDate::fromJulianDay(query.value(4).toInt()));
        opm->addRow(*op);
    }

    Slot* sl = new Slot(bonsai_id, date, opm);
    //TODO emit signal after N fetches
    qDebug() << "emit fetchSlotDone(slot)";
    emit fetchSlotDone(sl);
    //emit fetchOperationDone();
    qDebug() << "END" << Q_FUNC_INFO << QThread::currentThread();
}

void BonsaiWorker::cleanOldOperations() {

    qDebug() << Q_FUNC_INFO << QThread::currentThread();

    QDate startDay = QDate::currentDate();

    int wDay = startDay.dayOfWeek();
    if(wDay > 1)
        startDay.setDate(startDay.year(), startDay.month(), startDay.day()-(wDay-1));

    //TODO if db open
    QSqlQuery query(db);
    query.prepare("DELETE FROM operations WHERE last_date < ?");
    query.bindValue(0, startDay.toJulianDay());

    bool ret = query.exec();
    if(!ret)
        qDebug() << query.lastError().text();

    qDebug() << "END" << Q_FUNC_INFO << QThread::currentThread();
}

void BonsaiWorker::insertBonsai(const int specieId, const int year)
{
    bool ret = false;

    int id = this->nextId("bonsai");

    qDebug() << Q_FUNC_INFO << QThread::currentThread();

    QSqlQuery query(db);
    ret = query.exec(QString("insert into bonsai values(%1,'%2',%3)").arg(id).arg(
                         specieId).arg(year));

    if( !ret )
        qDebug() << query.lastError();
    OperationModel* opm = new OperationModel(id);
    Bonsai* item = new Bonsai(id, year, specieId, opm);
    //add schedule
    this->schedule(item);

    emit fetchBonsaiRecordDone(item);
    //emit jobDone();
    qDebug() << "END" << Q_FUNC_INFO << QThread::currentThread();
}

void BonsaiWorker::insertOperation(Operation &op)
{
    qDebug() << Q_FUNC_INFO << QThread::currentThread();

    //bool ret = false;
    int id = this->nextId("operations");

    //TODO if db open
    QSqlQuery query(db);
    query.prepare("INSERT INTO operations (id, name, type, bonsai_id, last_date) VALUES ( ?, ?, ?, ?, ? )");
    query.bindValue(0, id);
    query.bindValue(1, op.name());
    query.bindValue(2, op.type());
    query.bindValue(3, op.bonsaiId());
    query.bindValue(4, op.lastDate().toJulianDay());

    bool ret = query.exec();

    if(!ret)
      qDebug() << query.lastError();

    //Operation* item = new Operation(op);

    //addRow(op);
    //add schedule

    //emit operationRowFetchDone(item);
    //emit jobDone();
    qDebug() << "END" << Q_FUNC_INFO << QThread::currentThread();
}

int BonsaiWorker::nextId(const QString & table)
{
    int ret = 0;
    if (db.isOpen()) {
        QSqlQuery query(QString("select id from %1_id").arg(table), db);
        if (query.next()) {
            // Get last used id
            ret = query.value(0).toInt();
            // Increase that
            ret++;
            // Store new value
            query.exec(QString("update %1_id set id=%2 where id=%3").arg(table).arg(ret).arg(ret - 1));
        }
        else {
            // Set first id to zero
            query.exec(QString("insert into %1_id values(1)").arg(table));
            ret = 1;
        }
    }

    return ret;
}

void BonsaiWorker::schedule(Bonsai* bonsai){
    qDebug() <<  Q_FUNC_INFO << QThread::currentThread();
    const int month = QDate::currentDate().month();
    QFile specieDB(":/resources/db.xml");
    QFile specieQuery(":/resources/operations-by-specie.xq");

    if ( !specieDB.exists() || !specieDB.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Error opening Specie database";
        return;
    }

    if ( !specieQuery.exists() || !specieQuery.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Error opening query file";
        return;
    }


    QXmlQuery query;
    query.bindVariable("inputDocument", &specieDB);
    query.bindVariable("specie_id", QVariant(bonsai->specieId()));
    query.bindVariable("month", QVariant(month));
    query.setQuery(&specieQuery/*, QUrl::fromLocalFile(xq.fileName())*/);

    //OperationModel op;
    if( query.isValid() )
    {
        BonsaiSerializer serializer(query.namePool());

        if (query.evaluateTo(&serializer))
        {
            foreach (Operation operation, serializer.operations) {
                operation.setBonsaiId(bonsai->index());
                operation.setLastDate(QDate::currentDate());
                this->insertOperation(operation);
            }
        }
    }

    specieQuery.close();
    specieDB.close();
    qDebug() << "END" << Q_FUNC_INFO << QThread::currentThread();
}
