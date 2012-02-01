/**
 * Copyright (c) 2011 Nokia Corporation.
 */

#ifndef DATABASEMANAGER_H_
#define DATABASEMANAGER_H_

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDate>
#include <QVariant>

// ---------------------------------------------------------------------------
// DatabaseManager
// ---------------------------------------------------------------------------
class DatabaseManager: public QObject
{
    Q_OBJECT

public:
    DatabaseManager(QObject *parent = 0);
    ~DatabaseManager();

public:
    Q_INVOKABLE void open();
    Q_INVOKABLE void close();
    Q_INVOKABLE void deleteDB();
    Q_INVOKABLE int nextId();
    QSqlError lastError();
    const QSqlDatabase getDB();
private:
    bool openDB();
    bool initDB();
    bool createIdTable();

private:
    QSqlDatabase db;

};

#endif /* DATABASEMANAGER_H_ */
