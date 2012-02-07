#include <QtCore/QDebug>
#include <QtCore/QThread>
#include <QDir>
#include <QVariant>
#include <QBuffer>
#include <QFile>
#include "bonsaiworker.h"

BonsaiWorker::BonsaiWorker(SpecieModel* m_model):m_itemmodel(m_model){
    qDebug() << Q_FUNC_INFO << QThread::currentThread();

    // Find QSLite driver
    db = QSqlDatabase::addDatabase("QSQLITE", "bonsaiWorkerConnection");
    // http://doc.trolltech.com/sql-driver.html#qsqlite

    QString path(QDir::home().path());
    path.append(QDir::separator()).append("Bonsai.db.sqlite");
    path = QDir::toNativeSeparators(path);
    db.setDatabaseName(path);
    qDebug() << "DB opened ";
    qDebug() << "END" << Q_FUNC_INFO << QThread::currentThread();
}

BonsaiWorker::~BonsaiWorker(){}

void BonsaiWorker::readAll() {
    QString name;
    int itemId;

    qDebug() << Q_FUNC_INFO << QThread::currentThread();
    db.open();    
    QSqlQuery query(db);
    query.exec("select id, item_id, date from bonsai");
    qDebug() << query.lastError().text();

    while (query.next()) {
        itemId = query.value(1).toInt();
        name = m_itemmodel->getSpecieNameById(itemId);
        Bonsai* item = new Bonsai(query.value(0).toInt(),
                                  query.value(2).toDate(),
                                  name,
                                  itemId
                                  );
        qDebug()<<"fecth";
        //TODO emit signal after N fetches
        emit fetched(item);
    }

    db.close();
    emit finished();
    qDebug() << "END" << Q_FUNC_INFO << QThread::currentThread();
}

