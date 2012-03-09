/**
 * Copyright (c) 2011 Nokia Corporation.
 */

#include "DatabaseManager.h"

#include <QStringList>
#include <QDir>
#include <QVariant>
#include <QBuffer>
#include <QFile>
#include <QtSql>
#include <QDebug>


//models
#include "bonsaimodel.h"
#include "operationmodel.h"

// ---------------------------------------------------------------------------
// DatabaseManager
// ---------------------------------------------------------------------------
DatabaseManager::DatabaseManager(QObject *parent) :
    QObject(parent)
{

    // Find QSLite driver
    if(!QSqlDatabase::isDriverAvailable("QSQLITE")){
        qDebug()<<"Driver SQLITE not avaiable";
        return;
    }
    db = QSqlDatabase::addDatabase("QSQLITE", "bonsaiConnection");
    QString path(QDir::home().path());
    path.append(QDir::separator()).append("bonsai.db.sqlite");
    path = QDir::toNativeSeparators(path);
    db.setDatabaseName(path);

    qRegisterMetaType<QSqlDatabase>("QSqlDatabase");

}

DatabaseManager::~DatabaseManager()
{
    close();
}

void DatabaseManager::open()
{
    db.open();
    if(db.isOpenError())
        qDebug()<<"Error opening DB connection: " <<db.lastError();

    if(!initDB())
        qDebug()<<"Error creating database tables";
}

void DatabaseManager::close()
{
    if (db.isOpen()){
        qDebug() << "connection bonsaiConnection to bonsai-care.db closed";
        db.close();
    }
}

bool DatabaseManager::initDB()
{

    bool ret = false;

        // Create 4 tables
        BonsaiModel::createTable(db);
        OperationModel::createTable(db);

        // Check that tables exists
        if (db.tables().count() == 4)
            ret = true;

    return ret;
}

void DatabaseManager::deleteDB()
{
    db.close();

    QString path(QDir::home().path());
    path.append(QDir::separator()).append("bonsai.db.sqlite");
    path = QDir::toNativeSeparators(path);

    QFile::remove(path);
}

QSqlError DatabaseManager::lastError()
{
    return db.lastError();
}

int DatabaseManager::nextId(const QString & table)
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

const QSqlDatabase DatabaseManager::getDB()
{
    return db;
}

