#include "operation.h"

// Platform includes
#include <QtCore/QDebug>
#include <QtCore/QDate>

Operation::Operation(QObject *parent ):
    QObject(parent), m_id(0), m_name(), m_type(0), m_month(0),
    m_schedule("never"), m_schedule_value(0), m_last_date(), m_bonsai_id(-1)
{
}

Operation::Operation(const Operation &operation): QObject(0)
{
        m_id = operation.index();
        m_name = operation.name();
        m_type = operation.type();
        m_month = operation.month();
        m_schedule = operation.schedule();
        m_schedule_value = operation.scheduleValue();
        m_last_date = operation.lastDate();
        m_bonsai_id = operation.bonsaiId();

}

Operation::~Operation()
{
}

Operation & Operation::operator=(const Operation & operation){
    if(this != &operation){
        m_id = operation.index();
        m_name = operation.name();
        m_type = operation.type();
        m_month = operation.month();
        m_schedule = operation.schedule();
        m_schedule_value = operation.scheduleValue();
        m_last_date = operation.lastDate();
        m_bonsai_id = operation.bonsaiId();
    }
    return *this;
}


QString Operation::name() const
{
    return m_name;
}

void Operation::setName(const QString &name)
{
    m_name = name;
}

int Operation::index() const
{
    return m_id;
}

void Operation::setIndex(const int index)
{
    m_id = index;
}

int Operation::bonsaiId() const
{
    return m_bonsai_id;
}

void Operation::setBonsaiId(const int slot_id)
{
    m_bonsai_id = slot_id;
}

QDate Operation::lastDate() const
{
    return m_last_date;
}

void Operation::setLastDate(const QDate &date)
{
    m_last_date = date;
}

int Operation::type() const
{
    return m_type;
}

void Operation::setType(const int type)
{
    m_type = type;
}

int Operation::month() const
{
    return m_month;
}

void Operation::setMonth(const int month)
{
    m_month = month;
}

QString Operation::schedule() const
{
    return m_schedule;
}

void Operation::setSchedule(const QString &schedule)
{
    m_schedule = schedule;
}

QVariant Operation::scheduleValue() const
{
    return m_schedule_value;
}

void Operation::setScheduleValue(const QVariant &value)
{
    m_schedule_value = value;
}
