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
        SetDateRole,
        SetItemIdRole
      };
    static QHash<int, QByteArray> roleNames();

public:
    explicit BonsaiModel(SpecieModel &species, BonsaiWorker* worker, QObject* parent=0);
    virtual ~BonsaiModel();

public: // From QAbstractListModel
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags( const QModelIndex & index ) const;
    QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    bool setData( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );


    // for BonsaiTable
    static bool createTable(QSqlDatabase &db);
    Q_INVOKABLE void insert(const int specieId, const int year);
    /*Q_INVOKABLE void deleteBonsai(QSqlDatabase &db, const int id);
    Q_INVOKABLE QList<QObject*> Bonsais(QSqlDatabase &db);
    Q_INVOKABLE QList<QObject*> dateBonsais(QSqlDatabase &db, const int year,
                                          const int month,
                                          const int day);*/
    Q_INVOKABLE QString getAgeString(const int date);
    Q_INVOKABLE int getIdByIndex(const int index) const;

public slots:
    // Exposed to QML for managing the model.
    void addRow(Bonsai* item);    
    void init();

signals:
    void doFetchAllBonsai();
    void addedBonsaiRow(Bonsai* item);
    void doInsert(const int specieId, const int year);

private:
    QList<Bonsai*> m_items;    
    SpecieModel &m_itemmodel;    
    BonsaiWorker *workerThread;

};


#endif // BONSAIMODEL_H
