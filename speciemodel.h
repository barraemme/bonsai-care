#ifndef BONSAIITEMMODEL_H
#define BONSAIITEMMODEL_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QVariant>
#include <QtCore/QList>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "specie.h"
#include "bonsaiworker.h"

Q_DECLARE_METATYPE(Specie)

// ---------------------------------------------------------------------------
// Specie
// ---------------------------------------------------------------------------
class SpecieModel : public QAbstractListModel
{
    Q_OBJECT   

    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
    enum Roles {
        IndexRole = Qt::UserRole+1,
        NameRole,
        DataRole,
        SetIndexRole,
        SetNameRole
      };
    static QHash<int, QByteArray> roleNames();

public:
    explicit SpecieModel(const BonsaiWorker &worker, QObject *parent = 0);
    virtual ~SpecieModel();

public: // From QAbstractListModel
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags( const QModelIndex & index ) const;
    QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    //bool setData( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
    int count() const;    

    void init();
    // for SpecieTable
    Q_INVOKABLE QString getNameById(const int id) const;
    Q_INVOKABLE QString getNameByIndex(const int index) const;
    Q_INVOKABLE int getIdByIndex(const int index) const;

    /*Q_INVOKABLE QVariant insertSpecie(QSqlDatabase &db, const QVariant& name);
    Q_INVOKABLE QList<QObject*> Species(QSqlDatabase &db, const QVariant& useCache);
    Q_INVOKABLE QVariant updateSpecie(QSqlDatabase &db, const QVariant& id,
                                        const QVariant& name);
    Q_INVOKABLE void deleteSpecie(QSqlDatabase &db, const int id);
    */
public slots:
    // Exposed to QML for managing the model.
    void addRow(const Specie* specie);
    void commit();

signals:
    void countChanged(int newCount);
    void doFetchSpecies();
    void doInit();

private:
    QList<const Specie*> m_items;
    //QThread *thread;
    const BonsaiWorker &workerThread;

};

#endif // BONSAIITEMMODEL_H
