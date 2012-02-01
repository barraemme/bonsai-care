/**
 * Copyright (c) 2011 Nokia Corporation.
 */

#ifndef DAYMODEL_H
#define DAYMODEL_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QVariant>
#include <QtCore/QList>

#include "slot.h"

class DayModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        WeekDayIndexRole = Qt::UserRole+1,
        DayNameRole
      };
    static QHash<int, QByteArray> roleNames();

public:
    explicit DayModel(const int weekDayIndex, const QString &name, QObject *parent = 0);
    virtual ~DayModel();

public: // From QAbstractListModel
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags( const QModelIndex & index ) const;
    QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    bool setData( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );

public slots:
    // Exposed to QML for managing the Cell.
    /*void handleItemChange();
    void mergeDown(int index);
    void mergeUp(int index);
    int hourSpan(int index);
    bool setHourSpan(int index, int hourSpan);
    void setItemData(int index, QString itemData);
    void split(int index);
    bool isItemSpanned(int index);
    int itemsParent(int index);*/

private: // Methods
    /*QString dayName() const;
    QModelIndex indexFromItem(const Timeslot *item) const;
    void setSpanStatus(bool spanned, int index, int parentIndex);
    int weekDayIndex() const;*/

private: // Data
    QString m_dayName;
    QList<Slot*> m_items;
    int m_weekDayIndex;
    QSqlDatabase db;

    /*friend QDataStream &operator<<(QDataStream &, const DayModel &);
    friend QDataStream &operator>>(QDataStream &, DayModel &);*/
};

#endif // DAYMODEL_H
