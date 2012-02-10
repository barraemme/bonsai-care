#include <QtCore/QDebug>
#include <QtGlobal>
#include <QtCore/QThread>
#include <QtCore/qmath.h>
#include "bonsaimodel.h"
#include "speciemodel.h"
#include "bonsaiworker.h"


QHash<int, QByteArray> BonsaiModel::roleNames()
{
    QHash<int, QByteArray> roles;
    roles[IndexRole] = "b_index";
    roles[NameRole] = "b_name";
    roles[DateRole] = "b_date";
    roles[ItemIdRole] = "b_itemId";

    roles[SetIndexRole] = "b_setIndex";
    roles[SetNameRole] = "b_setName";
    roles[SetDateRole] = "b_setDate";
    roles[SetItemIdRole] = "b_setItemId";

    return roles;
}

// ---------------------------------------------------------------------------
// Bonsai
// ---------------------------------------------------------------------------

BonsaiModel::BonsaiModel(SpecieModel* itemModel, QObject* parent) :
    QAbstractListModel(parent), m_itemmodel(itemModel), m_items()
{
    qRegisterMetaType<Bonsai>("Bonsai");
    qRegisterMetaType<QSqlDatabase>("QSqlDatabase");

    // create a Worker Thread
    thread = new QThread;
    workerThread = new BonsaiWorker(m_itemmodel);
    workerThread->moveToThread(thread);

    //start thread with readAll on init
    connect(this, SIGNAL(fetch()), workerThread, SLOT(readAll()));
    //add row to model
    connect(workerThread, SIGNAL(fetched(Bonsai*)),this, SLOT(addRow(Bonsai*)));
    //notify job done
    connect(workerThread, SIGNAL(finished()),thread, SLOT(quit()));

    setRoleNames(BonsaiModel::roleNames());
}

void BonsaiModel::init()
{
    thread->start();
    emit fetch();
}

BonsaiModel::~BonsaiModel()
{
    qDeleteAll(m_items);
    m_items.clear();
}

int BonsaiModel::rowCount(const QModelIndex &parent) const
{
    return m_items.count();
}

QVariant BonsaiModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid()) {
        int row = index.row();
        if (row >= 0 && row < m_items.count()) {
            Bonsai *item = m_items[row];
            if (role == IndexRole){
                return QVariant(item->index());
            } else if (role == NameRole) {
                return QVariant(item->name());
            } else if (role == DateRole) {
                return QVariant(item->date());
            } else if (role == ItemIdRole) {
                return QVariant(item->itemId());
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

QVariant BonsaiModel::headerData( int section, Qt::Orientation orientation, int role) const
{
    return QVariant("HEADER");
}

Qt::ItemFlags BonsaiModel::flags( const QModelIndex & index) const
{
    if (!index.isValid()) {
        return 0;
    }

    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

// For editing
bool BonsaiModel::setData( const QModelIndex &index, const QVariant &value, int role)
{
    qDebug() << "setData(), index" << index << "role" << role;

    if (index.isValid()) {
        int row = index.row();
        if (row >= 0 && row < m_items.count()) {
            Bonsai* item = m_items[row];
            if (role == SetIndexRole){
                 item->setIndex(value.toInt());
                 return true;
            } else if (role == SetNameRole) {
                item->setName(value.toString());
                return true;
            } else if (role == SetDateRole) {
                item->setDate(value.toDate());
                return true;
            } else if (role == SetItemIdRole) {
                item->setItemId(value.toInt());
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

bool BonsaiModel::createTable(QSqlDatabase &db)
{
    // Create table
    bool ret = false;
    if (db.isOpen()) {
        QSqlQuery query(db);
        ret = query.exec("CREATE TABLE bonsai "
                         "(id integer primary key, "
                         "item_id integer, "
                         "date date)");

        /****** TODO da eliminare **********************/
        query.prepare("INSERT INTO bonsai VALUES (?,?,?);");
        query.bindValue(0,1);
        query.bindValue(1,1);
        query.bindValue(2,QDate::fromString("20000510", "yyyyMMdd"));

        if( !query.exec() )
            qDebug() << query.lastError();
          else
            qDebug() << "Table created!";


         query.bindValue(0,2);
         query.bindValue(1,5);
         query.bindValue(2,QDate::fromString("20120110", "yyyyMMdd"));


         if( !query.exec() )
            qDebug() << query.lastError();
         else
            qDebug() << "Table created!";

         /********* FINE ELIMINAZIONE *******************************/
    }
    return ret;
}

void BonsaiModel::addRow(Bonsai* item)
 {
     qDebug() << Q_FUNC_INFO;

     //TODO bloccare m_items
     qDebug() << "beginInsertRows";
     beginInsertRows(QModelIndex(), m_items.count(), m_items.count());

     m_items.append(item);

     qDebug() << "endInsertRows "<<m_items.count();
     endInsertRows();

     qDebug() << "emit addedBonsaiRow(item);";
     emit addedBonsaiRow(item);     

     qDebug() << "END " << Q_FUNC_INFO;
 }

int BonsaiModel::getIdByIndex(const int index) const
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << "count :"<< m_items.count() <<", index: "<<index;
    if(index < m_items.count())
        return m_items.at(index)->index();
    return 0;
}

/*bool BonsaiModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
        m_items.removeAt(position);
    }

    endRemoveRows();
    return true;
}*/

/*
void BonsaiModel::insertBonsai(QSqlDatabase &db, const int year, const int month, const int day, const int SpecieId)
{
    QDate date;
    date.setDate(year,month,day);

    if (db.isOpen()) {
        BonsaiModel* bonsai = new BonsaiModel();
        bonsai->m_id = this->nextId(db);
        bonsai->m_itemId = SpecieId;
        bonsai->m_date = date.toJulianDay();

        QSqlQuery query(db);
        query.exec(QString("insert into Bonsai values(%1,'%2',%3)").arg(bonsai->m_id).arg(
                       bonsai->m_itemId).arg(bonsai->m_date));
        delete bonsai;
    }
}

void BonsaiModel::deleteBonsai(QSqlDatabase &db, const int id)
{
    if (db.isOpen()) {
        QSqlQuery query(db);
        query.exec(QString("delete from Bonsai where id = %1").arg(id));
    }
}*/
/*
bool BonsaiModel::readAll()
{    
    QSqlQuery query("select * from bonsai", db);
    QString name;
    int itemId;
    while (query.next()) {
        itemId = query.value(1).toInt();
        name = m_itemmodel->getSpecieNameById(itemId);
        Bonsai* item = new Bonsai(query.value(0).toInt(),
                                  QDate::fromJulianDay(query.value(2).toInt()),
                                  name,
                                  itemId
                                  );
        m_items.append(item);
    }

    //USE ONLY FOR TEST
     Bonsai* item = new Bonsai(1,
                              QDate::fromString("20000110", "yyyyMMdd"),
                              "Acer buergerianum",
                              1
                              );
     m_items.append(item);

     Bonsai* item2 = new Bonsai(2,
                               QDate::fromString("20000110", "yyyyMMdd"),
                               "Acer palmatum",
                               5
                               );
      m_items.append(item2);


     return true;
}*/

/*QList<QObject*> BonsaiModel::dateBonsais(QSqlDatabase &db, const int year, const int month, const int day)
{
    QList<QObject*> result;
    QDate date;
    date.setDate(year,month,day);

    QSqlQuery query(QString("select * from Bonsai where date = %1").arg(date.toJulianDay()));
    while (query.next()) {
        BonsaiModel* item = new BonsaiModel();
        item->m_id = query.value(0).toInt();
        item->m_itemId = query.value(1).toInt();
        item->m_date = query.value(2).toInt();
        result.append(item);
    }
    return result;
}*/

int BonsaiModel::nextId()
{
    int ret = 0;
    /*if (db.isOpen()) {
        QSqlQuery query("select id from id", db);
        if (query.next()) {
            // Get last used id
            ret = query.value(0).toInt();
            // Increase that
            ret++;
            // Store new value
            query.exec(QString("update id set id=%1 where id=%2").arg(ret).arg(ret - 1));
        }
        else {
            // Set first id to zero
            query.exec("insert into id values(1)");
            ret = 1;
        }
    }*/

    return ret;
}

QString BonsaiModel::getAgeString(QDate date){

    double varYear = 365.25;
    double varMonth = 30.43;

    int days = date.daysTo(QDate::currentDate());
    int years = qFloor(days / varYear);
    days -= years*varYear;
    int months = qFloor(days/varMonth);
    days -= months*varMonth;
/*
        QString result = tr("\nYears: ") + ;
        result = result + tr("\nMonths: ") + ;
        result = result + tr("\nWeeks: ") + QString::number(Days/7,'f',2);
        result = result + tr("\nDays: ") + ;
        result = result + tr("\nHours: ") + QString::number(Years*(24*varYear),'f',2);
        result = result + tr("\nMinutes: ") + QString::number(Years*((24*varYear)*60),'f',2);
        result = result + tr("\nSeconds: ") + QString::number(Years*(((24*varYear)*60)*60),'f',2);
*/     
    /*int numYears = qRound(days/31536000000);
    int numMonths = qRound((days % 31536000000)/2628000000);
    int numdays = qRound(((days % 31536000000) % 2628000000)/86400000);
    */
    QString result = "";

    if(days>0)
        result.append(QString("%1 days, ").arg(days));
    if(months>0)
        result.append(QString("%1 months, ").arg(months));
    if(years>0)
        result.append(QString("%1 years ").arg(years));

    return result;
}


/*bool DatabaseManager::isFreeBonsaiDate(const int SpecieId, const int year, const int month, const int day)
{
    QDate date;
    date.setDate(year,month,day);

    QSqlQuery query(QString("select * from Bonsai where date = %1 and itemid = %2").arg(date.toJulianDay()).arg(SpecieId));
    while (query.next()) {
        return false;
    }
    return true;
}*/

/*qint64 DatabaseManager::lastBookedBonsaiBlockDate(const int BonsaiBlockId)
{
    qint64 ret = -1;
    QSqlQuery query(QString("select * from Bonsai where block = %1").arg(BonsaiBlockId));
    while (query.next()) {
        if(query.last()) {
            int julian = query.value(4).toInt();
            QDate date = QDate::fromJulianDay(julian);
            QDateTime dt(date);
            ret = dt.toMSecsSinceEpoch();
        }
    }
    return ret;
}*/

/*qint64 DatabaseManager::firstBookedBonsaiBlockDate(const int BonsaiBlockId)
{
    qint64 ret = -1;
    QSqlQuery query(QString("select * from Bonsai where block = %1").arg(BonsaiBlockId));
    while (query.next()) {
        if (query.first()) {
            int julian = query.value(4).toInt();
            QDate date = QDate::fromJulianDay(julian);
            QDateTime dt(date);
            ret = dt.toMSecsSinceEpoch();
            break;
        }
    }
    return ret;
}*/


