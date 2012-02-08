/**
 * Copyright (c) 2011 Nokia Corporation.
 */

#ifndef DAY_H
#define DAY_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QDate>

class QDataStream;

class Day : public QObject
{
    Q_OBJECT

public:
    Day(const QDate &date, QObject *parent = 0);
    Day(const Day &date, QObject *parent = 0);
    //virtual ~Day();

public:
    //QObject *items() const;
    Q_INVOKABLE QString dayName() const;
    Q_INVOKABLE QString monthName() const;
    Q_INVOKABLE int dayOfWeekIndex() const;
    Q_INVOKABLE int monthIndex() const;
    Q_INVOKABLE int dayIndex() const;
    QDate date() const;

private:
    QDate m_day;


    /*friend QDataStream &operator<<(QDataStream &, const Day &);
    friend QDataStream &operator>>(QDataStream &, Day &);*/
};

#endif // DAY_H
