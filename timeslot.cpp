/**
 * Copyright (c) 2011 Nokia Corporation.
 */

// Class header
#include "timeslot.h"

// Platform includes
#include <QtCore/QDebug>


/*!
  \class Timeslot
  \brief Timeslot depicts one calendar event, which can span over multiple hours.
*/

Timeslot::Timeslot(int hourId, QTime start, QObject *parent) :
    QObject(parent), m_hourId(hourId), m_start(start), m_data(""), m_hours(1),
    m_spanned(false), m_parentIndex(-1)
{
}

Timeslot::~Timeslot()
{
}

bool Timeslot::setStartTime(const QTime &time)
{
    if (time != m_start) {
        m_start = time;
        emit dataChanged();
        return true;
    }

    return false;
}

bool Timeslot::setItemData(const QString &data)
{
    if (data != m_data) {
        m_data = data;
        // Uncomment, if you want debug output of the event's description changes.
//        qDebug() << "Item data changed to: " << data;
        emit dataChanged();
        return true;
    }

    return false;
}

bool Timeslot::setHourSpan(int hours)
{
    if (hours != m_hours) {
        qDebug() << "Timeslot::setHourSpan():" << hours << "(on item" << m_hourId << ")";
        m_hours = hours;
        emit dataChanged();
        return true;
    }

    return false;
}

QString Timeslot::startTime() const
{
    return m_start.toString("HH:mm");
}

QString Timeslot::endTime() const
{
    // Add the hourSpan to the start time in seconds, and return the end time!
    QTime endTime = m_start.addSecs(60*60*hourSpan());
    return endTime.toString("HH:mm");
}

QString Timeslot::itemData() const
{
    return m_data;
}

int Timeslot::hourSpan() const
{
    return m_hours;
}

QString Timeslot::toString() const
{
    return startTime() + ": " + itemData();
}

bool Timeslot::setSpanStatus(bool spanned, int parentIndex)
{
    qDebug() << "setSpanStatus:" << spanned << "on Item:" << m_hourId
             << "with parentIndex:" << parentIndex;
    m_spanned = spanned;
    if (m_spanned) {
        m_parentIndex = parentIndex;
    } else {
        m_parentIndex = -1;
    }

    emit dataChanged();

    return true;
}

bool Timeslot::spanned() const
{
    return m_spanned;
}

int Timeslot::parentIndex() const
{
    return m_parentIndex;
}

int Timeslot::hourId() const
{
    return m_hourId;
}

QDataStream &operator<<(QDataStream &stream, const Timeslot &timeSlot)
{
    stream << timeSlot.m_hourId;
    stream << timeSlot.m_start;
    stream << timeSlot.m_data;
    stream << timeSlot.m_hours;
    stream << timeSlot.m_spanned;
    stream << timeSlot.m_parentIndex;
    return stream;
}

QDataStream &operator>>(QDataStream &stream, Timeslot &timeSlot)
{
    stream >> timeSlot.m_hourId;
    stream >> timeSlot.m_start;
    stream >> timeSlot.m_data;
    stream >> timeSlot.m_hours;
    stream >> timeSlot.m_spanned;
    stream >> timeSlot.m_parentIndex;
    return stream;
}
