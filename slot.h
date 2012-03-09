/**
 * Copyright (c) 2011 Nokia Corporation.
 */

#ifndef SLOT_H
#define SLOT_H

#include <QtCore/QObject>
#include <QtCore/QTime>
#include <QtCore/QVariant>
#include <QtCore/QHash>
#include "operationmodel.h"

class Slot : public QObject
{
    Q_OBJECT

public:
    Slot(const int bonsaiId, const QDate &day, OperationModel* operationModel, QObject *parent = 0);
    virtual ~Slot();

public:
    QDate date() const;
    OperationModel* operations();
    /*bool setStartTime(const QTime &time);
    bool setItemData(const QString &data);
    bool setHourSpan(int hours);
    bool setSpanStatus(bool spanned, int parentIndex);*/

    /*QString startTime() const;
    QString endTime() const;
    QString itemData() const;
    int hourSpan() const;

    QString toString() const;

    bool spanned() const;
    int parentIndex() const;
    int hourId() const;

signals:
      void dataChanged();*/

private:
    /*QString m_data;
    int m_hours;
    bool m_spanned;*/
    int m_bonsai_id;
    QDate m_date;
    OperationModel* m_operation_model;
    /*friend QDataStream &operator<<(QDataStream &, const Timeslot &);
    friend QDataStream &operator>>(QDataStream &, Timeslot &);*/
};

#endif // SLOT_H
