/**
 * Copyright (c) 2011 Nokia Corporation.
 */

// Class header
#include "day.h"

// Platform includes
#include <QtCore/QDataStream>
#include <QtCore/QDebug>

// Internal includes
//#include "daymodel.h"
//#include "timeslot.h"

/*!
  \class Day
  \brief Day is a wrapper class for DayModel.
*/

Day::Day(const QDate &date, QObject *parent) :
    QObject(parent), m_day(date)
{

}

QString Day::dayName() const
{
    return QDate::longDayName(m_day.dayOfWeek());
}

int Day::dayIndex() const
{
    return m_day.dayOfWeek();
}

QString Day::monthName() const
{
    return QDate::longMonthName(m_day.month());
}

int Day::monthIndex() const
{
    return m_day.month();
}


/*QDataStream &operator<<(QDataStream &stream, const Day &day)
{
    stream << day.m_dayIndex;
    stream << day.m_dayName;
    Q_ASSERT(day.m_model);
    stream << *(day.m_model);
    return stream;
}*/

/*QDataStream &operator>>(QDataStream &stream, Day &day)
{
    stream >> day.m_dayIndex;
    stream >> day.m_dayName;
    Q_ASSERT(day.m_model);
    stream >> *(day.m_model);
    return stream;
}*/
