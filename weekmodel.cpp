/**
 * Copyright (c) 2011 Nokia Corporation.
 */

// Class header
#include "weekmodel.h"

// Platform includes
#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/qmath.h>
#include <QtGui/QDesktopServices>

// Internal includes
#include "daymodel.h"

// Constants
const int DAYS_IN_WEEK = 7;
const int SAVE_FORMAT_VERSION = 1;

/*!
  \class WeekModel
  \brief WeekModel depicts one week and holds the day objects.
*/

QHash<int, QByteArray> WeekModel::roleNames()
{
    QHash<int, QByteArray> roles;
    roles[DayIndexRole] = "dayIndex";
    roles[DayNameRole] = "dayName";
    roles[MonthIndexRole] = "monthIndex";
    return roles;
}

WeekModel::WeekModel(QObject *parent) :
    QAbstractListModel(parent), m_days()
{
    if ( !restore() ) {
        QDate startDay = QDate::currentDate ();

        int wDay = startDay.dayOfWeek();
        if(wDay > 1)
            startDay.setDate(startDay.year(), startDay.month(), startDay.day()-(wDay-1)+7);

        /*int startMonth = 0;
        int lastMonth = 0;*/
        for (int i = 0; i < DAYS_IN_WEEK; i++) {
            DayModel* day = new DayModel(startDay.addDays(i));
            m_days.append(day);

            //Add the month to model
           /* m_months.append(new QDate());
            //m_months.append(day);
            //if is last day of the month OR is last index of different month
            if(day->day() == day->daysInMonth() || (i == (DAYS_IN_WEEK-1) && lastMonth != day->month())){
                m_months.replace(qFloor((i-startMonth)/2), day);
                startMonth = i+1;
                lastMonth = day->month();
                m_monthsCount++;
            }*/

            qDebug() << day->weekDayIndex() << "created";
        }

    }

    setRoleNames(WeekModel::roleNames());
}

WeekModel::~WeekModel()
{
    save();
    qDeleteAll(m_days);
    m_days.clear();   
}

int WeekModel::rowCount(const QModelIndex &parent) const
{
    return m_days.count();
}

QVariant WeekModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid()) {
        int row = index.row();
        if (row >= 0 && row < m_days.count()) {
            DayModel* day = m_days[row];
            if (role == DayNameRole){
                return QVariant(day->dayName());
            } if (role == MonthIndexRole){
                //return index of array
                return QVariant(day->monthDayIndex());
            }  if (role == DayIndexRole){
                return QVariant(day->weekDayIndex());
            }  else {
                return QVariant("ERR: UnkstartDayn role for weekmodel");
            }
        } else {
            return QVariant("ERR: Invalid index");
        }
    } else {
        return QVariant("ERR: Invalid index");
    }

    return QVariant("ERR: other");
}

QVariant WeekModel::headerData( int section, Qt::Orientation orientation, int role) const
{
    return QVariant("HEADER");
}

Qt::ItemFlags WeekModel::flags( const QModelIndex &index) const
{
    return Qt::ItemIsEnabled;
}

// For editing
bool WeekModel::setData( const QModelIndex &index, const QVariant &value, int role)
{
    return true;
}

QString WeekModel::dayName(int index) const
{
    qDebug() << "Requesting day for index" << index;
    if (index >= 0 && index < m_days.count()) {
        return QDate::longDayName(m_days.at(index)->weekDayIndex());
    }

    return "";
}

int WeekModel::indexOfFirstDay(int month) const
{
    int index = 0;
    foreach(DayModel *day, m_days) {
        if(day->monthDayIndex() == month)
            return index;
        index++;
    }
    return 0;
}


int WeekModel::indexOfMonth(int dayIndex) const
{    
    int monthNum = m_days.at(dayIndex)->monthDayIndex();
    qDebug()<<"day "<<m_days.at(dayIndex)->monthDayIndex()<<" month "<<monthNum;
    return monthNum-1;
}

bool WeekModel::save()
{
    bool ret = true;
    QFile file( getSaveFileName() );
    ret = file.open(QIODevice::WriteOnly);
    if (ret) {
        QDataStream out(&file);
        out << SAVE_FORMAT_VERSION;
        out << m_days.size();
        /*foreach(Day *day, m_days) {
            out << *day;
        }*/
    }

    return ret;
}

bool WeekModel::restore()
{
    qDebug() << "WeekModel::restore";
    bool ret = false;
    QFile file( getSaveFileName() );
    //ret = file.open(QIODevice::ReadOnly);
    if (ret) {
        QDataStream in(&file);

        int version = 0;
        in >> version;
        if (version != SAVE_FORMAT_VERSION) {
            qDebug() << "Incompatible versions";
            qDebug() << "Read version from QSettings: " << version;
            qDebug() << "Current version: " << SAVE_FORMAT_VERSION;
            ret = false;
        } else {
            int size = 0;
            in >> size;
            for (int i=0; i < size; i++) {
                /*Day *day = new Day(0, QString(""), this);
                in >> *day;
                m_days.append(day);*/
            }
        }

        if (in.status() != QDataStream::Ok) {
            qDebug() << "Error restoring data: " << in.status();
            qDeleteAll(m_days);
            m_days.clear();
            ret = false;
        }
    }

    qDebug() << "Restore returning: " << ret;
    return ret;
}

QString WeekModel::getSaveFileName() const
{
    QString location = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
    QString subDir = "weeklyplanner";

    qDebug() << "Save file location: " << location;

    QDir locationDir(location);
    if (!locationDir.exists()) {
        qDebug() << "No data directory, creating";
        locationDir.mkdir(".");
    }

    if (!locationDir.exists(subDir)) {
        locationDir.mkdir(subDir);
    }

    locationDir.cd(subDir);
    QString path = locationDir.absoluteFilePath("weeklyplanner.txt");
    qDebug() << "Returning path: " << path;

    return path;
}
