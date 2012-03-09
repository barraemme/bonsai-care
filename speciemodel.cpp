#include "speciemodel.h"
#include <QStringList>
#include <QDir>
#include <QVariant>
#include <QBuffer>
#include <QFile>
#include <QDebug>
#include <QXmlStreamReader>
#include <QtCore/QThread>

#include "bonsaiworker.h"

// ---------------------------------------------------------------------------
// Specie
// ---------------------------------------------------------------------------
QHash<int, QByteArray> SpecieModel::roleNames()
{
    QHash<int, QByteArray> roles;
    roles[IndexRole] = "index";
    roles[NameRole] = "name";
    roles[DataRole] = "modelData";
    roles[SetIndexRole] = "setIndex";
    roles[SetNameRole] = "setName";
    return roles;
}

SpecieModel::SpecieModel(const BonsaiWorker & worker, QObject *parent):
    QAbstractListModel(parent), workerThread(worker), m_items()
{
    //QSqlQuery query("select * from bonsai_item");

    /*while (query.next()) {
        Specie* item = new Specie();
        item->m_id = query.value(0).toInt();
        item->m_name = query.value(1).toString();
        m_SpeciesCache.append(item);
    }*/
    //qDebug() << "Bonsai items count :"  << m_SpeciesCache.length();

    qRegisterMetaType<Specie>("Specie");

    // create a Worker Thread
    //thread = new QThread;
    //workerThread = new BonsaiWorker();
    //workerThread->moveToThread(thread);

    /** connect THIS -> WORKER THREAD **/
    //start thread with readAll on init
    connect(this, SIGNAL(doFetchSpecies()), &workerThread, SLOT(fetchAllSpecies()));

    /** connect WORKER HTREAD -> THIS **/
    //add row to model
    connect(&workerThread, SIGNAL(fetchSpecieRecordDone(const Specie*)),this, SLOT(addRow(const Specie*)));
    //notify job done
    connect(&workerThread, SIGNAL(fetchSpeciesDone()),this, SLOT(commit()));

    setRoleNames(SpecieModel::roleNames());
}

void SpecieModel::init()
{    
    emit doFetchSpecies();
}

SpecieModel::~SpecieModel(){
    qDeleteAll(m_items);
    m_items.clear();
}

int SpecieModel::rowCount(const QModelIndex &parent) const
{
    return m_items.count();
}

QVariant SpecieModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid()) {
        int row = index.row();
        if (row >= 0 && row < m_items.count()) {
            const Specie *item = m_items[row];
            if (role == IndexRole){
                return QVariant(item->index());
            } else if (role == NameRole || role == DataRole) {
                return QVariant(item->name());
            } else {
                return QVariant("ERR: Unknown role for speciemodel: " + role);
            }
        } else {
            return QVariant("ERR: Invalid index");
        }
    } else {
        return QVariant("ERR: Invalid index");
    }

    return QVariant("ERR: other");
}

QVariant SpecieModel::headerData( int section, Qt::Orientation orientation, int role) const
{
    return QVariant("HEADER");
}

Qt::ItemFlags SpecieModel::flags( const QModelIndex & index) const
{
    if (!index.isValid()) {
        return 0;
    }

    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

// For editing
/*bool SpecieModel::setData( const QModelIndex &index, const QVariant &value, int role)
{
    qDebug() << "setData(), index" << index << "role" << role;

    if (index.isValid()) {
        int row = index.row();
        if (row >= 0 && row < m_items.count()) {
            const Specie* item = m_items[row];
            if (role == SetIndexRole){
                item->setIndex(value.toInt());
                return true;
            } else if (role == SetNameRole) {
                item->setName(value.toString());
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
}*/

int SpecieModel::count() const
{
    return m_items.count();
}

QString SpecieModel::getNameById(const int id) const
{
  for(int row=0; row<m_items.size(); ++row) {
    if(m_items.at(row)->index() == id)
        return m_items.at(row)->name();
  }

  return "";
}

QString SpecieModel::getNameByIndex(const int index) const
{
  return m_items.at(index)->name();
}

int SpecieModel::getIdByIndex(const int index) const
{
  return m_items.at(index)->index();
}

void SpecieModel::addRow(const Specie* item)
 {
     //qDebug() << Q_FUNC_INFO;

     //TODO bloccare m_items
     beginInsertRows(QModelIndex(), m_items.count(), m_items.count());

     m_items.append(item);

     endInsertRows();

     //qDebug() << "END " << Q_FUNC_INFO;
}

void SpecieModel::commit()
{
    //thread->quit();
    emit doInit();
}
/*
QVariant SpecieModel::updateSpecie(QSqlDatabase &db, const QVariant& id,
                                         const QVariant& name
                                         )
{
    bool ret = false;
    QSqlQuery query(db);
    ret = query.prepare("UPDATE bonsai_item SET name = :name where id = :id");
    if (ret) {
        query.bindValue(":name", name);
        query.bindValue(":id", id);
        ret = query.exec();
    }
    return QVariant(ret);
}

void SpecieModel::deleteSpecie(QSqlDatabase &db, const int id)
{
    QSqlQuery query(db);
    query.exec(QString("delete from bonsai_item where id = %1").arg(id));
}

QVariant SpecieModel::insertSpecie(QSqlDatabase &db, const QVariant& name)
{
    bool ret = false;
    int retVal = -1;
    SpecieModel item;
    item.m_name = name.toString();



    if (db.isOpen()) {
        //item->id = nextId(); // We demostrates autoincrement in this case

        // http://www.sqlite.org/autoinc.html
        // NULL = is the keyword for the autoincrement to generate next value

        QSqlQuery query(db);
        ret = query.prepare("INSERT INTO bonsai_item (name) "
                            "VALUES (:name)");
        if (ret) {
            query.bindValue(":name", item.m_name);
            ret = query.exec();
        }

        // Get database given autoincrement value
        if (ret) {
            // http://www.sqlite.org/c3ref/last_insert_rowid.html
            item.m_id = query.lastInsertId().toInt();
            retVal = item.m_id;
        }
    }
    return QVariant(retVal);
}*/



