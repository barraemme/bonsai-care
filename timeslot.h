/**
 * Copyright (c) 2011 Nokia Corporation.
 */

#ifndef TIMESLOT_H
#define TIMESLOT_H

#include <QtCore/QObject>
#include <QtCore/QTime>
#include <QtCore/QVariant>
#include <QtCore/QHash>

class Timeslot : public QObject
{
    Q_OBJECT

public:
    Timeslot(int hourId, QTime start, QObject *parent = 0);
    virtual ~Timeslot();

public:
    bool setStartTime(const QTime &time);
    bool setItemData(const QString &data);
    bool setHourSpan(int hours);
    bool setSpanStatus(bool spanned, int parentIndex);

    QString startTime() const;
    QString endTime() const;
    QString itemData() const;
    int hourSpan() const;

    QString toString() const;

    bool spanned() const;
    int parentIndex() const;
    int hourId() const;

signals:
      void dataChanged();

private:
    int m_hourId;
    QTime m_start;
    QString m_data;
    int m_hours;
    bool m_spanned;
    int m_parentIndex;

    friend QDataStream &operator<<(QDataStream &, const Timeslot &);
    friend QDataStream &operator>>(QDataStream &, Timeslot &);
};

#endif // TIMESLOT_H
