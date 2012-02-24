#include "specie.h"

// Platform includes
#include <QtCore/QDebug>

// Internal includes
#include "speciemodel.h"

Specie::Specie(const int id, const QString &name, QObject *parent):
            QObject(parent), m_id(id), m_name(name)
{
    //m_model = new SpecieModel(m_id, m_name, this);
}

Specie::Specie(QObject *parent):
    QObject(parent),m_id(-1), m_name()
{

}

Specie::Specie(const Specie &specie): QObject(0)
{
    m_id = specie.index();
    m_name = specie.name();

}

Specie::~Specie()
{
   // delete m_model;
}

/*QObject* Specie::items() const
{
    qDebug() << "Requested Specie items. We have" << m_model->rowCount();
    return m_model;
}*/

int Specie::index() const
{
    return m_id;
}

void Specie::setIndex(const int id)
{
    m_id = id;
}

QString Specie::name() const
{
    return m_name;
}

void Specie::setName(const QString &name)
{
    m_name = name;
}
