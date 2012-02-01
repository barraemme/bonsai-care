/**
 * Copyright (c) 2011 Nokia Corporation.
 */

// Class header
#include "slot.h"

// Platform includes
#include <QtCore/QDebug>


/*!
  \class Slot
  \brief Slot depicts one calendar event, which can span over multiple hours.
*/

Slot::Slot(int bonsaiId, QObject *parent) :
    QObject(parent), m_bonsai_id(bonsaiId), m_items()
{
}

Slot::~Slot()
{
    qDeleteAll( m_items);
    m_items.clear();
}

/*
bool Slot::setStartTime(const QTime &time)
{
    if (time != m_start) {
        m_start = time;
        emit dataChanged();
        return true;
    }

    return false;
}

bool Slot::setItemData(const QString &data)
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

bool Slot::setHourSpan(int hours)
{
    if (hours != m_hours) {
        qDebug() << "Slot::setHourSpan():" << hours << "(on item" << m_hourId << ")";
        m_hours = hours;
        emit dataChanged();
        return true;
    }

    return false;
}

QString Slot::startTime() const
{
    return m_start.toString("HH:mm");
}

QString Slot::endTime() const
{
    // Add the hourSpan to the start time in seconds, and return the end time!
    QTime endTime = m_start.addSecs(60*60*hourSpan());
    return endTime.toString("HH:mm");
}

QString Slot::itemData() const
{
    return m_data;
}

int Slot::hourSpan() const
{
    return m_hours;
}

QString Slot::toString() const
{
    return startTime() + ": " + itemData();
}

bool Slot::setSpanStatus(bool spanned, int parentIndex)
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

bool Slot::spanned() const
{
    return m_spanned;
}

int Slot::parentIndex() const
{
    return m_parentIndex;
}

int Slot::hourId() const
{
    return m_hourId;
}

QDataStream &operator<<(QDataStream &stream, const Slot &Slot)
{
    stream << Slot.m_hourId;
    stream << Slot.m_start;
    stream << Slot.m_data;
    stream << Slot.m_hours;
    stream << Slot.m_spanned;
    stream << Slot.m_parentIndex;
    return stream;
}

QDataStream &operator>>(QDataStream &stream, Slot &Slot)
{
    stream >> Slot.m_hourId;
    stream >> Slot.m_start;
    stream >> Slot.m_data;
    stream >> Slot.m_hours;
    stream >> Slot.m_spanned;
    stream >> Slot.m_parentIndex;
    return stream;
}
*/
