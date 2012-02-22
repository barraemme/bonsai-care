#include <QtCore/QDebug>
#include <QtCore/QThread>
#include <QDir>
#include <QVariant>
#include <QBuffer>
#include <QFile>
#include "bonsaiworker.h"

BonsaiWorker::BonsaiWorker(SpecieModel &m_model):m_itemmodel(m_model){

    // Find QSLite driver
    db = QSqlDatabase::addDatabase("QSQLITE", "bonsaiWorkerConnection");
    // http://doc.trolltech.com/sql-driver.html#qsqlite

    QString path(QDir::home().path());
    path.append(QDir::separator()).append("Bonsai.db.sqlite");
    path = QDir::toNativeSeparators(path);
    db.setDatabaseName(path);    

}

BonsaiWorker::~BonsaiWorker(){}

void BonsaiWorker::readAll() {
    QString name;
    int itemId;

    qDebug() << Q_FUNC_INFO << QThread::currentThread();
    db.open();    
    QSqlQuery query(db);
    if(!query.exec("select id, item_id, date from bonsai"))
        qDebug() << query.lastError().text();

    while (query.next()) {
        itemId = query.value(1).toInt();
        name = m_itemmodel.getNameById(itemId);
        Bonsai* item = new Bonsai(query.value(0).toInt(),
                                  query.value(2).toInt(),
                                  name,
                                  itemId
                                  );

        //TODO emit signal after N fetches
        qDebug() << "emit fetched(item)";
        emit fetched(item);
    }

    db.close();
    emit finished();
    qDebug() << "END" << Q_FUNC_INFO << QThread::currentThread();
}

void BonsaiWorker::insertBonsai(const int specieId, const int year)
{
    bool ret = false;

    int id = this->nextId();
    QString name = m_itemmodel.getNameById(specieId);

    qDebug() << Q_FUNC_INFO << QThread::currentThread();
    db.open();

    QSqlQuery query(db);
    ret = query.exec(QString("insert into bonsai values(%1,'%2',%3)").arg(id).arg(
                         specieId).arg(year));
    if( !ret )
        qDebug() << query.lastError();

    Bonsai* item = new Bonsai(id, year, name, specieId);
    db.close();
    emit fetched(item);
    emit finished();
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

