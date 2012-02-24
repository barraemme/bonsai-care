#include "bonsai.h"
#include "bonsaimodel.h"

// Platform includes
#include <QtCore/QDebug>
#include <QtCore/QDate>

Bonsai::Bonsai(const int id, const int date, const int itemId, QObject *parent ):
    QObject(parent), m_id(id), m_date(date), m_itemId(itemId)
{
    //m_model = new BonsaiModel(m_date, m_name, m_itemId, this);
}

Bonsai::Bonsai(QObject *parent ):
    QObject(parent), m_id(-1), m_date(), m_itemId(-1)
{
    //m_model = new BonsaiModel(m_date, m_name, m_itemId, this);
}

Bonsai::Bonsai(const Bonsai &bonsai): QObject(0)
{
    m_id = bonsai.index();
    m_date = bonsai.date();   
    m_itemId = bonsai.itemId();
    //m_model = new BonsaiModel(m_date, m_name, m_itemId, this);
}

Bonsai::~Bonsai()
{
    //delete m_model;
}

/*QObject* Bonsai::items() const
{
    qDebug() << "Requested Bonsai items. We have" << m_model->rowCount();
    return m_model;
}*/

int Bonsai::index() const
{
    return m_id;
}

void Bonsai::setIndex(const int index)
{
    m_id = index;
}

int Bonsai::itemId() const
{
    return m_itemId;
}

void Bonsai::setItemId(const int itemId)
{
    m_itemId = itemId;
}

int Bonsai::date() const
{
    return m_date;
}

void Bonsai::setDate(const int date)
{
    m_date = date;
}
