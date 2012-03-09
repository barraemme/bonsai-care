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

Q_DECLARE_METATYPE(QSqlDatabase)
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
    void open();
    void close();
    void deleteDB();
    int nextId(const QString & table);
    QSqlError lastError();
    const QSqlDatabase getDB();
private:

    bool initDB();
    bool createIdTable();

private:
    QSqlDatabase db;


};

#endif /* DATABASEMANAGER_H_ */
