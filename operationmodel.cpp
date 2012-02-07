#include <QtCore/QDebug>
#include <QtGlobal>
#include "operationmodel.h"

QHash<int, QByteArray> OperationModel::roleNames()
{
    QHash<int, QByteArray> roles;
    roles[IndexRole] = "o_index";
    roles[NameRole] = "o_name";
    roles[LastDateRole] = "o_lastDate";
    roles[SlotIdRole] = "o_slotId";

    roles[SetIndexRole] = "o_setIndex";
    roles[SetNameRole] = "o_setName";
    roles[SetLastDateRole] = "o_setLastDate";
    roles[SetBonsaiIdRole] = "o_setBonsaiId";

    return roles;
}

OperationModel::OperationModel(const QSqlDatabase &db, const int slotId, QObject* parent) :
    QAbstractListModel(parent), db(db), m_items(), m_slot_id(slotId)
{
    init();
    setRoleNames(OperationModel::roleNames());
}

OperationModel::~OperationModel()
{
    qDeleteAll(m_items);
    m_items.clear();
}

void OperationModel::init()
{
    /*thread->start();
    connect(this, SIGNAL(fetch()), workerThread, SLOT(readAll()));
    connect(workerThread, SIGNAL(fetched(Bonsai*)),this, SLOT(addRow(Bonsai*)));
    connect(workerThread, SIGNAL(finished()),this, SLOT(endWorker()));

    emit fetch();*/


    if (db.isOpen()) {

        QSqlQuery query(db);

        query.prepare("select id, last_date, name, slot_id,  from operations where slot_id = ?");
        query.bindValue(0, m_slot_id);

        if( !query.exec() )
            qDebug() << query.lastError();
          else
            qDebug() << "Table created!";

        while (query.next()) {
           Operation* op = new Operation(
                       query.value(0).toInt(),
                       query.value(1).toDate(),
                       query.value(2).toString(),
                       query.value(3).toInt()
           );
           addRow(op);
        }
    }
}

void OperationModel::addRow(Operation* item)
 {
     //qDebug() << Q_FUNC_INFO << QThread::currentThread();
     beginInsertRows(QModelIndex(), m_items.count(), m_items.count()+1);
     m_items.append(item);
     endInsertRows();
 }

int OperationModel::rowCount(const QModelIndex &parent) const
{
    return m_items.count();
}

QVariant OperationModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid()) {
        int row = index.row();
        if (row >= 0 && row < m_items.count()) {
            Operation *item = m_items[row];
            if (role == IndexRole){
                return QVariant(item->index());
            } else if (role == NameRole) {
                return QVariant(item->name());
            } else if (role == LastDateRole) {
                return QVariant(item->lastDate());
            } else if (role == SlotIdRole) {
                return QVariant(item->slotId());
            } else {
                return QVariant("ERR: Unknown role for daymodel: " + role);
            }
        } else {
            return QVariant("ERR: Invalid index");
        }
    } else {
        return QVariant("ERR: Invalid index");
    }

    return QVariant("ERR: other");
}

QVariant OperationModel::headerData( int section, Qt::Orientation orientation, int role) const
{
    return QVariant("HEADER");
}

Qt::ItemFlags OperationModel::flags( const QModelIndex & index) const
{
    if (!index.isValid()) {
        return 0;
    }

    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

// For editing
bool OperationModel::setData( const QModelIndex &index, const QVariant &value, int role)
{
    qDebug() << "setData(), index" << index << "role" << role;

    if (index.isValid()) {
        int row = index.row();
        if (row >= 0 && row < m_items.count()) {
            Operation* item = m_items[row];
            if (role == SetIndexRole){
                 item->setIndex(value.toInt());
                 return true;
            } else if (role == SetNameRole) {
                item->setName(value.toString());
                return true;
            } else if (role == SetLastDateRole) {
                item->setLastDate(value.toDate());
                return true;
            } else if (role == SetBonsaiIdRole) {
                item->setSlotId(value.toInt());
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    } else {
        return false;
    }

    return false;
}

bool OperationModel::createTable(QSqlDatabase &db)
{
    // Create table
    bool ret = false;
    if (db.isOpen()) {
        QSqlQuery query(db);
        ret = query.exec("CREATE TABLE operations "
                         "(id integer primary key, "
                         "name varchar(15)"
                         "slot_id integer, "
                         "last_date date)");

         if( !ret )
            qDebug() << query.lastError();
         else
            qDebug() << "Table operations created!";
    }
    return ret;
}
