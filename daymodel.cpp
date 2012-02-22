/**
 * Copyright (c) 2011 Nokia Corporation.
 */

// Class header
#include "daymodel.h"

// Platform includes
#include <QtCore/QDebug>
#include <QSqlQuery>
#include <QThread>

#include "operationmodel.h"
#include "slotmodel.h"
#include "day.h"

// Constants
//const int DAYS_FIRST_SLOT = 6;


/*!
  \class DayModel
  \brief DayModel depicts one day and holds the Timeslot objects.
*/

QHash<int, QByteArray> DayModel::roleNames()
{
    QHash<int, QByteArray> roles;
    roles[WeekDayIndexRole] = "d_weekDayIndex";
    roles[DayNameRole] = "d_dayName";
    return roles;
}

/*DayModel::DayModel(QObject *parent):
    QAbstractListModel(parent), m_day(), m_items()
{
    setRoleNames(DayModel::roleNames());
}

DayModel::DayModel(const DayModel &dayModel,  QObject *parent):
    QAbstractListModel(parent)
{
    m_day = dayModel.day();
    m_items = dayModel.items();
    setRoleNames(DayModel::roleNames());
}*/


DayModel::DayModel(const QDate &day, QObject *parent) :
    QAbstractListModel(parent), m_day(day), m_items()
{    

//    // Enable following comments, if you would like to generate the day
//    // full of example events.
//    QString templateItem("Day %1 Item %2");    



    setRoleNames(DayModel::roleNames());

//    // Code for generating randomly hour spans to events.
//    // Sets the seed within the range 0-999
//    qsrand(QTime::currentTime().msec());
//    // Set 0 to 3 spans / day
//    for (int i = qrand() % 4; i > 0; i--) {
//        setHourSpan(qrand() % 24, (qrand() % 3) + 2);
//    }
}

Day& DayModel::day()
{
    return m_day;
}

QList<Slot*>& DayModel::items()
{
    return m_items;
}


void DayModel::addRow(Bonsai* bonsai)
{    
    qDebug() << Q_FUNC_INFO;

    OperationModel* op = new OperationModel(bonsai->index(), m_day.date());
    Slot *sl = new Slot(bonsai->index(), m_day.date(), op);

    qDebug() << "beginInsertRows";
    beginInsertRows(QModelIndex(), m_items.count(), m_items.count());

    m_items.append(sl);

    qDebug() << "endInsertRows "<<m_items.count();
    endInsertRows();
    qDebug() << "END" <<Q_FUNC_INFO;
}

DayModel::~DayModel()
{
    qDeleteAll(m_items);
    m_items.clear();
}

/*OperationModel* DayModel::daySlots(){
    SlotModel *sl = new SlotModel(m_day.date());
    return sl;
}

OperationModel* DayModel::dayOperationsByBonsaiId(const int bonsaiId){
    OperationModel *op = new OperationModel(bonsaiId, m_day.date());
    return op;
}*/

int DayModel::rowCount(const QModelIndex &parent) const
{
    return m_items.count();
}

QVariant DayModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid()) {
        int row = index.row();
        if (row >= 0 && row < m_items.count()) {
            Slot *slot = m_items[row];
            if (role == DayNameRole) {
                return QVariant(m_day.dayName());
            } else if (role == WeekDayIndexRole) {
                return QVariant(m_day.dayOfWeekIndex());
            } else {
                return QVariant("ERR: Unknown role for daymodel: " + role);
            }
        } else {
            return QVariant("ERR: Invalid index");
        }
    } else {
        return QVariant("ERR: Invalid index");
    }

    return QVariant("ERR: other");
}

QVariant DayModel::headerData( int section, Qt::Orientation orientation, int role) const
{
    return QVariant("HEADER");
}

Qt::ItemFlags DayModel::flags( const QModelIndex & index) const
{
    if (!index.isValid()) {
        return 0;
    }

    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

// For editing
/*bool DayModel::setData( const QModelIndex &index, const QVariant &value, int role)
{
    qDebug() << "setData(), index" << index << "role" << role;

    if (index.isValid()) {
        int row = index.row();
        if (row >= 0 && row < m_items.count()) {
            Timeslot* slot = m_items[row];
            if (role == SetStartTimeRole){
                return slot->setStartTime(value.toTime());
            } else if (role == SetItemDataRole) {
                return slot->setItemData(value.toString());
            } else if (role == SetHourSpanRole) {
                return setHourSpan(row, value.toInt());
            } else {
                return false;
            }
        } else {
            return false;
        }
    } else {
        return false;
    }

    return false;
}

/*void DayModel::handleItemChange()
{
    Timeslot *item = static_cast<Timeslot*>(sender());
    QModelIndex modelIndex = indexFromItem(item);
    if(modelIndex.isValid()) {
        emit dataChanged(modelIndex, modelIndex);
    }
}

QModelIndex DayModel::indexFromItem(const Timeslot* item) const
{
  Q_ASSERT(item);

  for(int row=0; row<m_items.size(); ++row) {
    if(m_items.at(row) == item) return index(row);
  }

  return QModelIndex();
}

int DayModel::hourSpan(int index)
{
    if (index >= 0 && index < m_items.count()) {
        return m_items[index]->hourSpan();
    }
}

bool DayModel::setHourSpan(int index, int hourSpan)
{
    bool retVal = false;
    if (index >= 0 && index < m_items.count()) {
        retVal = m_items[index]->setHourSpan(hourSpan);
    }

    for (int i = hourSpan-1; i > 0; i-- ) {
        m_items[index+i]->setSpanStatus(true, index);
    }

    return retVal;
}

void DayModel::setItemData(int index, QString itemData)
{
    if (index >= 0 && index < m_items.count()) {
        m_items[index]->setItemData(itemData);
    }
}

void DayModel::mergeDown(int index)
{
    if (index == m_items.count()-1) {
        qDebug() << "Cannot span downwards!";
    }
    else if (index >= 0 && index < m_items.count()-1) {
        // Check that we're not spanning on already spanned hours!
        int oldHourSpan = m_items[index]->hourSpan();
        if (m_items[index+oldHourSpan]->hourSpan() > 1) {
            qDebug() << "Cannot span on already spanned hours! Please split first!";
        } else {
            m_items[index]->setHourSpan(oldHourSpan+1);
            // Set the next item beneath the spanned item as newly spanned!
            m_items[index+oldHourSpan]->setSpanStatus(true, index);
        }
    } else {
        qDebug() << "Something went severely wrong!";
    }
}

void DayModel::mergeUp(int index)
{
    qDebug() << "DayModel::mergeUp! Index:" << index;

    if (index == 0) {
        qDebug() << "Cannot span upwards!";
    } else if (index > 0 && index < m_items.count()) {
        // Get the previous item, as the hourSpan must be set to it.
        int parentIndex = m_items[index-1]->parentIndex();
        qDebug() << "parentIndex:" << parentIndex;
        if (parentIndex != -1) {
            qDebug() << "Cannot span on already spanned hours! Please split first!";
        } else {
            // The item hasn't been spanned before, the given index is valid.
            int oldHourSpan = m_items[index]->hourSpan();
            m_items[index-1]->setHourSpan(oldHourSpan+1);
            // Reset the span hour count for the current item and set it to
            // be spanned.
            m_items[index]->setHourSpan(1);
            m_items[index]->setSpanStatus(true, index);
        }
    } else {
        qDebug() << "Something went severely wrong!";
    }
}

void DayModel::split(int index)
{
    if (index >= 0 && index < m_items.count()) {
        int hourSpan = m_items[index]->hourSpan();
        m_items[index]->setHourSpan(1);
        for (int i = index; i < index+hourSpan; i++ ) {
            m_items[i]->setSpanStatus(false, -1);
        }
    }
}

bool DayModel::isItemSpanned(int index)
{
    if (index >= 0 && index < m_items.count()) {
        return m_items[index]->spanned();
    }
}

int DayModel::itemsParent(int index)
{
    if (index >= 0 && index < m_items.count()) {
        return m_items[index]->parentIndex();
    } else {
        return -1;
    }
}
*/
QString DayModel::dayName() const
{
    return m_day.dayName();
}

int DayModel::weekDayIndex() const
{
    return m_day.dayOfWeekIndex();
}

int DayModel::monthDayIndex() const
{
    return m_day.monthIndex();
}
/*
QDataStream &operator<<(QDataStream &stream, const DayModel &dayModel)
{
    stream << dayModel.m_weekDayIndex;
    stream << dayModel.m_dayName;
    stream << dayModel.m_items.size();
    foreach (Timeslot *slot, dayModel.m_items) {
        stream << *slot;
    }

    return stream;
}

QDataStream &operator>>(QDataStream &stream, DayModel &dayModel)
{
    stream >> dayModel.m_weekDayIndex;
    stream >> dayModel.m_dayName;
    int size = 0;
    stream >> size;
    for (int i = 0; i < size; i++) {
        if ( i < dayModel.m_items.count() ) {
            Q_ASSERT(dayModel.m_items[i]);
            stream >> *dayModel.m_items[i];
        } else {
            qDebug() << "Incorrect index: ignoring data";
            QScopedPointer<Timeslot> serializationSlot(new Timeslot(0, QTime(0, 0, 0, 0)));
            stream >> *serializationSlot;
        }
    }

    return stream;
}*/

