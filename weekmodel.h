/**
 * Copyright (c) 2011 Nokia Corporation.
 */

#ifndef WEEKMODEL_H
#define WEEKMODEL_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QList>

#include "daymodel.h"

class WeekModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        DayIndexRole = Qt::UserRole+1,
        DayNameRole,
        MonthIndexRole
      };
    static QHash<int, QByteArray> roleNames();

public:
    explicit WeekModel(QObject *parent = 0);
    virtual ~WeekModel();

public: // From QAbstractListModel
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags( const QModelIndex & index) const;
    bool setData( const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

public:    
    Q_INVOKABLE QString dayName(int index) const;
    Q_INVOKABLE bool save();
    Q_INVOKABLE bool restore();
    Q_INVOKABLE int indexOfFirstDay(int month) const;
    Q_INVOKABLE int indexOfMonth(int dayIndex) const;

private:
    QString getSaveFileName() const;

private:
    QList<DayModel*> m_days;
};

#endif // WEEKMODEL_H
