#ifndef OPERATIONMODEL_H
#define OPERATIONMODEL_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDate>
#include "operation.h"

class OperationModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        IndexRole = Qt::UserRole+1,
        NameRole,
        LastDateRole,
        SlotIdRole,
        SetIndexRole,
        SetNameRole,
        SetLastDateRole,
        SetBonsaiIdRole
    };
    static QHash<int, QByteArray> roleNames();

public:
    explicit OperationModel(const QSqlDatabase &db, const int slotId, QObject* parent=0);
    virtual ~OperationModel();

public: // From QAbstractListModel
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags( const QModelIndex & index ) const;
    QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    bool setData( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
    void init();

    // for BonsaiTable
    static bool createTable(QSqlDatabase &db);
    void addRow(Operation* item);

    /*Q_INVOKABLE void insertBonsai(QSqlDatabase &db, const int year, const int month, const int day,
                                  const int SpecieId);
    Q_INVOKABLE void deleteBonsai(QSqlDatabase &db, const int id);
    Q_INVOKABLE QList<QObject*> Bonsais(QSqlDatabase &db);
    Q_INVOKABLE QList<QObject*> dateBonsais(QSqlDatabase &db, const int year,
                                          const int month,
                                          const int day);*/
    //Q_INVOKABLE int nextId();
    //QList<Operation*> getAgeString(QDate date);

//public slots:
    // Exposed to QML for managing the model.
    //void addRow(Bonsai* item);

//signals:
    //void fetch();

private:
    QList<Operation*> m_items;
    QSqlDatabase db;
    int m_slot_id;
    //QThread *thread;
    //BonsaiWorker *workerThread;

};

#endif // OPERATIONMODEL_H
