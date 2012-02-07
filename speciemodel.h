#ifndef BONSAIITEMMODEL_H
#define BONSAIITEMMODEL_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QVariant>
#include <QtCore/QList>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "specie.h"
// ---------------------------------------------------------------------------
// Specie
// ---------------------------------------------------------------------------
class SpecieModel : public QAbstractListModel
{
    Q_OBJECT   

public:
    enum Roles {
        IndexRole = Qt::UserRole+1,
        NameRole,
        SetIndexRole,
        SetNameRole
      };
    static QHash<int, QByteArray> roleNames();

public:
    explicit SpecieModel(QObject *parent = 0);
    virtual ~SpecieModel();

public: // From QAbstractListModel
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags( const QModelIndex & index ) const;
    QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    bool setData( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );

public:
    // for SpecieTable
    QString getSpecieNameById(const int &id) const;

    /*Q_INVOKABLE QVariant insertSpecie(QSqlDatabase &db, const QVariant& name);
    Q_INVOKABLE QList<QObject*> Species(QSqlDatabase &db, const QVariant& useCache);
    Q_INVOKABLE QVariant updateSpecie(QSqlDatabase &db, const QVariant& id,
                                        const QVariant& name);
    Q_INVOKABLE void deleteSpecie(QSqlDatabase &db, const int id);
    */

private:
    QList<Specie*> m_items;    

private:
    bool parseXML();
};

#endif // BONSAIITEMMODEL_H
