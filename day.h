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
    //virtual ~Day();

public slots:
    //QObject *items() const;
    QString dayName() const;
    QString monthName() const;
    int dayOfWeekIndex() const;
    int monthIndex() const;
    int dayIndex() const;

private:
    QDate m_day;


    /*friend QDataStream &operator<<(QDataStream &, const Day &);
    friend QDataStream &operator>>(QDataStream &, Day &);*/
};

#endif // DAY_H
