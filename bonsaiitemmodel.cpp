#include "bonsaiitemmodel.h"
#include <QStringList>
#include <QDir>
#include <QVariant>
#include <QBuffer>
#include <QFile>
#include <QDebug>
#include <QXmlStreamReader>

#include <QMessageBox>

// ---------------------------------------------------------------------------
// BonsaiItem
// ---------------------------------------------------------------------------
QHash<int, QByteArray> BonsaiItemModel::roleNames()
{
    QHash<int, QByteArray> roles;
    roles[IndexRole] = "bi_index";
    roles[NameRole] = "bi_name";

    roles[SetIndexRole] = "bi_setIndex";
    roles[SetNameRole] = "bi_setName";
    return roles;
}

BonsaiItemModel::BonsaiItemModel(QObject *parent):
    QAbstractListModel(parent), m_items()
{
    //QSqlQuery query("select * from bonsai_item");
    this->parseXML();
    /*while (query.next()) {
        BonsaiItem* item = new BonsaiItem();
        item->m_id = query.value(0).toInt();
        item->m_name = query.value(1).toString();
        m_BonsaiItemsCache.append(item);
    }*/
    //qDebug() << "Bonsai items count :"  << m_BonsaiItemsCache.length();

    setRoleNames(BonsaiItemModel::roleNames());
}


BonsaiItemModel::~BonsaiItemModel(){
    qDeleteAll(m_items);
    m_items.clear();
}

int BonsaiItemModel::rowCount(const QModelIndex &parent) const
{
    return m_items.count();
}

QVariant BonsaiItemModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid()) {
        int row = index.row();
        if (row >= 0 && row < m_items.count()) {
            BonsaiItem *item = m_items[row];
            if (role == IndexRole){
                return QVariant(item->index());
            } else if (role == NameRole) {
                return QVariant(item->name());
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

QVariant BonsaiItemModel::headerData( int section, Qt::Orientation orientation, int role) const
{
    return QVariant("HEADER");
}

Qt::ItemFlags BonsaiItemModel::flags( const QModelIndex & index) const
{
    if (!index.isValid()) {
        return 0;
    }

    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

// For editing
bool BonsaiItemModel::setData( const QModelIndex &index, const QVariant &value, int role)
{
    qDebug() << "setData(), index" << index << "role" << role;

    if (index.isValid()) {
        int row = index.row();
        if (row >= 0 && row < m_items.count()) {
            BonsaiItem* item = m_items[row];
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
}

QString BonsaiItemModel::getBonsaiItemNameById(const int &id) const
{
  for(int row=0; row<m_items.size(); ++row) {
    if(m_items.at(row)->index() == id)
        return m_items.at(row)->name();
  }

  return "";
}
/*
QVariant BonsaiItemModel::updateBonsaiItem(QSqlDatabase &db, const QVariant& id,
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

void BonsaiItemModel::deleteBonsaiItem(QSqlDatabase &db, const int id)
{
    QSqlQuery query(db);
    query.exec(QString("delete from bonsai_item where id = %1").arg(id));
}

QVariant BonsaiItemModel::insertBonsaiItem(QSqlDatabase &db, const QVariant& name)
{
    bool ret = false;
    int retVal = -1;
    BonsaiItemModel item;
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


bool BonsaiItemModel::parseXML() {

        /* We'll parse the example.xml */
        QFile* file = new QFile(":/resources/db.xml");
        /* If we can't open it, let's show an error message. */
        if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
                qDebug() << "parseXML, Couldn't open db.xml";
                return false;
        }
        /* QXmlStreamReader takes any QIODevice. */
        QXmlStreamReader xml(file);

        /* We'll parse the XML until we reach end of it.*/
        while(!xml.atEnd() && !xml.hasError()) {
                /* Read next element.*/
                QXmlStreamReader::TokenType token = xml.readNext();
                /* If token is just StartDocument, we'll go to next.*/
                if(token == QXmlStreamReader::StartDocument) {
                        continue;
                }
                /* If token is StartElement, we'll see if we can read it.*/
                if(token == QXmlStreamReader::StartElement) {
                        /* If it's named persons, we'll go to the next.*/
                        if(xml.name() == "items") {
                                continue;
                        }
                        /* If it's named person, we'll dig the information from there.*/
                        if(xml.name() == "item") {

                            QXmlStreamAttributes attrs = xml.attributes();
                            /*get value of each attribute from QXmlStreamAttributes */
                            QStringRef fID = attrs.value("id");
                            QStringRef fname = attrs.value("name");
                            BonsaiItem* item = new BonsaiItem(fID.toString().toInt(), fname.toString());

                            /*
                            xml.readNext();
                            while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
                                            xml.name() == "person")) {
                                    if(xml.tokenType() == QXmlStreamReader::StartElement) {

                                            if(xml.name() == "firstname") {
                                                    this->addElementDataToMap(xml, person);
                                            }

                                            if(xml.name() == "surname") {
                                                    this->addElementDataToMap(xml, person);
                                            }

                                            if(xml.name() == "email") {
                                                    this->addElementDataToMap(xml, person);
                                            }

                                            if(xml.name() == "website") {
                                                    this->addElementDataToMap(xml, person);
                                            }
                                    }

                                    xml.readNext();
                            }
                            */
                            m_items.append(item);
                        }
                }
        }
        /* Error handling. */
       if(xml.hasError()) {
           qDebug() << xml.errorString();
        }
        xml.clear();
        return xml.hasError();
}
