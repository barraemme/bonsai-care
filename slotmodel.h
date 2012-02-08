#ifndef SLOTMODEL_H
#define SLOTMODEL_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDate>
//#include "bonsai.h"
//#include "daymodel.h"

/*class SlotModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        SlotIndexRole = Qt::UserRole+1,
        SlotDayIndexRole,
        SlotBonsaiIndexRole
      };
    static QHash<int, QByteArray> roleNames();

public:
    explicit SlotModel(QDate &day, QObject* parent=0);
    virtual ~SlotModel();

public: // From QAbstractListModel
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags( const QModelIndex & index ) const;
    QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    bool setData( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );

public:
    static bool createTable(QSqlDatabase &db);
private:
    QList<Operation*> m_items;
    QSqlDatabase db;
};*/

#endif // SLOTMODEL_H
