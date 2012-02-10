#ifndef BONSAIMODEL_H
#define BONSAIMODEL_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDate>
#include "bonsai.h"
#include "speciemodel.h"
#include "bonsaiworker.h"

Q_DECLARE_METATYPE(Bonsai)
Q_DECLARE_METATYPE(QSqlDatabase)
// ---------------------------------------------------------------------------
// Bonsai
// ---------------------------------------------------------------------------
class BonsaiModel : public QAbstractListModel // Bonsai data
{
    Q_OBJECT
    //Q_PROPERTY(int index READ index WRITE setIndex)
    //Q_PROPERTY(int itemId READ itemId WRITE setItemId)
    /*Q_PROPERTY(int BonsaierId READ BonsaierId WRITE setBonsaierId)*/
   // Q_PROPERTY(int date READ date WRITE setDate)
    /*Q_PROPERTY(int BonsaiBlockIndex READ BonsaiBlockIndex WRITE setBonsaiBlockIndex)*/

public:
    enum Roles {
        IndexRole = Qt::UserRole+1,
        NameRole,
        DateRole,
        ItemIdRole,
        SetIndexRole,
        SetNameRole,
        SetDateRole,
        SetItemIdRole
      };
    static QHash<int, QByteArray> roleNames();

public:
    explicit BonsaiModel(SpecieModel* itemModel, QObject* parent=0);
    virtual ~BonsaiModel();

public: // From QAbstractListModel
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags( const QModelIndex & index ) const;
    QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    bool setData( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
    void init();

    // for BonsaiTable
    static bool createTable(QSqlDatabase &db);
    /*Q_INVOKABLE void insertBonsai(QSqlDatabase &db, const int year, const int month, const int day,
                                  const int SpecieId);
    Q_INVOKABLE void deleteBonsai(QSqlDatabase &db, const int id);
    Q_INVOKABLE QList<QObject*> Bonsais(QSqlDatabase &db);
    Q_INVOKABLE QList<QObject*> dateBonsais(QSqlDatabase &db, const int year,
                                          const int month,
                                          const int day);*/
    Q_INVOKABLE int nextId();
    Q_INVOKABLE QString getAgeString(QDate date);
    Q_INVOKABLE int getIdByIndex(const int index) const;

public slots:
    // Exposed to QML for managing the model.
    void addRow(Bonsai* item);    

signals:
    void fetch();
    void addedBonsaiRow(Bonsai* item);

private:
    QList<Bonsai*> m_items;    
    SpecieModel* m_itemmodel;
    QThread *thread;
    BonsaiWorker *workerThread;

};


#endif // BONSAIMODEL_H
