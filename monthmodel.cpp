#include <QtCore/QDebug>
#include <QtCore/QDate>
#include "monthmodel.h"

QHash<int, QByteArray> MonthModel::roleNames()
{
    QHash<int, QByteArray> roles;
    roles[MonthIndexRole] = "monthIndex";
    roles[MonthNameRole] = "monthName";

    return roles;
}

MonthModel::MonthModel(QObject *parent) :
    QAbstractListModel(parent), m_months()
{
//    // Enable following comments, if you would like to generate the day
//    // full of example events.
//    QString templateItem("Day %1 Item %2");
    for (int i = 0; i < 12; i++) {
       m_months.append(QDate::longMonthName(i+1, QDate::StandaloneFormat));

    }

    setRoleNames(MonthModel::roleNames());

//    // Code for generating randomly hour spans to events.
//    // Sets the seed within the range 0-999
//    qsrand(QTime::currentTime().msec());
//    // Set 0 to 3 spans / day
//    for (int i = qrand() % 4; i > 0; i--) {
//        setHourSpan(qrand() % 24, (qrand() % 3) + 2);
//    }
}

MonthModel::~MonthModel()
{
   m_months.clear();
}

int MonthModel::rowCount(const QModelIndex &parent) const
{
    return m_months.count();
}

QVariant MonthModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid()) {
        int row = index.row();
        if (row >= 0 && row < m_months.count()) {                 
            if (role == MonthIndexRole){               
                return row+1;
            } if (role == MonthNameRole){
                return m_months[row];
            } else {
                return QVariant("ERR: UnkstartDayn role for MonthModel");
            }
        } else {
            return QVariant("ERR: Invalid index");
        }
    } else {
        return QVariant("ERR: Invalid index");
    }

    return QVariant("ERR: other");
}

QVariant MonthModel::headerData( int section, Qt::Orientation orientation, int role) const
{
    return QVariant("HEADER");
}

Qt::ItemFlags MonthModel::flags( const QModelIndex &index) const
{
    return Qt::ItemIsEnabled;
}

// For editing
bool MonthModel::setData( const QModelIndex &index, const QVariant &value, int role)
{
    return true;
}
