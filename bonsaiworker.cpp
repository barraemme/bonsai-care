#include <QtCore/QDebug>
#include <QtCore/QThread>
#include <QDir>
#include <QVariant>
#include <QBuffer>
#include <QFile>
#include "bonsaiworker.h"

BonsaiWorker::BonsaiWorker(SpecieModel* m_model):m_itemmodel(m_model){

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
        name = m_itemmodel->getSpecieNameById(itemId);
        Bonsai* item = new Bonsai(query.value(0).toInt(),
                                  query.value(2).toDate(),
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

