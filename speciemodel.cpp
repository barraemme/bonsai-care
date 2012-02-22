#include "speciemodel.h"
#include <QStringList>
#include <QDir>
#include <QVariant>
#include <QBuffer>
#include <QFile>
#include <QDebug>
#include <QXmlStreamReader>

#include <QMessageBox>

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

SpecieModel::SpecieModel(QObject *parent):
    QAbstractListModel(parent), m_items()
{
    //QSqlQuery query("select * from bonsai_item");
    this->parseXML();
    /*while (query.next()) {
        Specie* item = new Specie();
        item->m_id = query.value(0).toInt();
        item->m_name = query.value(1).toString();
        m_SpeciesCache.append(item);
    }*/
    //qDebug() << "Bonsai items count :"  << m_SpeciesCache.length();

    setRoleNames(SpecieModel::roleNames());
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
    qDebug()<<"Specie Model data: "<<role;
    if (index.isValid()) {
        int row = index.row();
        if (row >= 0 && row < m_items.count()) {
            Specie *item = m_items[row];
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
bool SpecieModel::setData( const QModelIndex &index, const QVariant &value, int role)
{
    qDebug() << "setData(), index" << index << "role" << role;

    if (index.isValid()) {
        int row = index.row();
        if (row >= 0 && row < m_items.count()) {
            Specie* item = m_items[row];
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


bool SpecieModel::parseXML() {

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
                            Specie* item = new Specie(fID.toString().toInt(), fname.toString());

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
                            emit countChanged(m_items.count());

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
