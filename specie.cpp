#include "bonsaiitem.h"

// Platform includes
#include <QtCore/QDebug>

// Internal includes
#include "bonsaiitemmodel.h"

BonsaiItem::BonsaiItem(const int id, const QString &name, QObject *parent):
            QObject(parent), m_id(id), m_name(name)
{
    //m_model = new BonsaiItemModel(m_id, m_name, this);
}

BonsaiItem::~BonsaiItem()
{
    delete m_model;
}

QObject* BonsaiItem::items() const
{
    qDebug() << "Requested BonsaiItem items. We have" << m_model->rowCount();
    return m_model;
}

int BonsaiItem::index() const
{
    return m_id;
}

void BonsaiItem::setIndex(const int id)
{
    m_id = id;
}

QString BonsaiItem::name() const
{
    return m_name;
}

void BonsaiItem::setName(const QString &name)
{
    m_name = name;
}
