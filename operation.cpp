#include "operation.h"

// Platform includes
#include <QtCore/QDebug>
#include <QtCore/QDate>

Operation::Operation(const int id, const QDate &date, const QString &name, const int slot_id, QObject *parent):
    QObject(parent), m_id(id), m_last_date(date), m_name(name), m_slot_id(slot_id)
{
}

Operation::Operation(QObject *parent ):
    QObject(parent), m_id(-1), m_last_date(), m_name(), m_slot_id(-1)
{

}

Operation::Operation(const Operation &operation): QObject(0)
{
    m_id = operation.index();
    m_last_date = operation.lastDate();
    m_name = operation.name();
    m_slot_id = operation.slotId();
}

Operation::~Operation()
{

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

int Operation::slotId() const
{
    return m_slot_id;
}

void Operation::setSlotId(const int slot_id)
{
    m_slot_id = slot_id;
}

QDate Operation::lastDate() const
{
    return m_last_date;
}

void Operation::setLastDate(const QDate &date)
{
    m_last_date = date;
}
