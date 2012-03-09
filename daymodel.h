/**
 * Copyright (c) 2011 Nokia Corporation.
 */

#ifndef DAYMODEL_H
#define DAYMODEL_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QVariant>
#include <QtCore/QList>
#include <QSqlDatabase>

#include "slot.h"
#include "bonsaimodel.h"
#include "day.h"
#include "bonsaiworker.h"

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
    /*explicit DayModel(QObject *parent = 0);
    explicit DayModel(const DayModel &dayModel,  QObject *parent = 0);*/
    explicit DayModel(const QDate &day, const BonsaiWorker  & workerThread, QObject *parent = 0);
    virtual ~DayModel();

public: // From QAbstractListModel
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags( const QModelIndex & index ) const;
    QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    //bool setData( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );

    QList<Slot*>& items();


public:
    Q_INVOKABLE QString dayName() const;
    Q_INVOKABLE int weekDayIndex() const;
    Q_INVOKABLE int monthDayIndex() const;
    Q_INVOKABLE QObject * operationsBySlotIndex( const int index) const;

signals:
    void doFetchSlotOperations(const int, const QDate&);
public slots:
    void addRow(Slot* sl);
    void fetchSlot(Bonsai *bonsai);
    //Q_INVOKABLE OperationModel* dayOperations(const int bonsaiId);
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
    QDate m_day;
    QList<Slot*> m_items;
    QSqlDatabase db;
    const BonsaiWorker &workerThread;
    /*friend QDataStream &operator<<(QDataStream &, const DayModel &);
    friend QDataStream &operator>>(QDataStream &, DayModel &);*/
};

#endif // DAYMODEL_H
