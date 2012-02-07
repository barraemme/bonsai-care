/**
 * Copyright (c) 2011 Nokia Corporation.
 */

#include "DatabaseManager.h"

#include <QStringList>
#include <QDir>
#include <QVariant>
#include <QBuffer>
#include <QFile>
#include <QDesktopServices>
#include <QDebug>
#include <QXmlStreamReader>

//models
#include "speciemodel.h"
#include "operationmodel.h"
#include "bonsaimodel.h"
#include "slotmodel.h"
// ---------------------------------------------------------------------------
// DatabaseManager
// ---------------------------------------------------------------------------
DatabaseManager::DatabaseManager(QObject *parent) :
    QObject(parent)
{
}

DatabaseManager::~DatabaseManager()
{
    close();
}

void DatabaseManager::open()
{
    openDB();
    initDB();
}

void DatabaseManager::close()
{
    if (db.isOpen()){
        qDebug() << "DB closed";
        db.close();
    }
}

bool DatabaseManager::openDB()
{
    // Find QSLite driver
    db = QSqlDatabase::addDatabase("QSQLITE");
    // http://doc.trolltech.com/sql-driver.html#qsqlite

    QString path(QDir::home().path());
    path.append(QDir::separator()).append("Bonsai.db.sqlite");
    path = QDir::toNativeSeparators(path);
    db.setDatabaseName(path);
    qDebug() << "DB opened";

    // Open databasee
    return db.open();
}

bool DatabaseManager::initDB()
{
    bool ret = true;

    // Create 4 tables
    if (createIdTable()) {
        //createSpecieTable();
        BonsaiModel::createTable(db);
        OperationModel::createTable(db);
        SlotModel::createTable(db);
        //createBonsaierTable();
    }

    // Check that tables exists
    if (db.tables().count() != 4)
        ret = false;

    return ret;
}

void DatabaseManager::deleteDB()
{
    db.close();

    QString path(QDir::home().path());
    path.append(QDir::separator()).append("Bonsai.db.sqlite");
    path = QDir::toNativeSeparators(path);

    QFile::remove(path);
}

QSqlError DatabaseManager::lastError()
{
    return db.lastError();
}

bool DatabaseManager::createIdTable()
{
    // Create table
    bool ret = false;
    if (db.isOpen()) {
        QSqlQuery query;
        ret = query.exec("create table id "
                         "(id integer primary key)");
    }
    return ret;
}



int DatabaseManager::nextId()
{
    int ret = 0;
    if (db.isOpen()) {
        QSqlQuery query("select id from id");
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

const QSqlDatabase DatabaseManager::getDB()
{
    return db;
}

