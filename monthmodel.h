#ifndef MONTHMODEL_H
#define MONTHMODEL_H

#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QtCore/QAbstractListModel>
//#include "day.h"

class MonthModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        MonthIndexRole = Qt::UserRole+1,
        MonthNameRole
      };

    static QHash<int, QByteArray> roleNames();
public:
    explicit MonthModel(QObject *parent = 0);
    virtual ~MonthModel();

public: // From QAbstractListModel
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags( const QModelIndex & index ) const;
    QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    bool setData( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );

private:
    QList<QString> m_months;
};

#endif // MONTHMODEL_H
