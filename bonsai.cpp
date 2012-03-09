#include "bonsai.h"
#include "bonsaimodel.h"

// Platform includes
#include <QtCore/QDebug>
#include <QtCore/QDate>

Bonsai::Bonsai(const int id, const int date, const int specie, QObject *parent ):
    QObject(parent), m_id(id), m_date(date), m_specieId(specie)
{
    //m_model = new BonsaiModel(m_date, m_name, m_specieId, this);
}

Bonsai::Bonsai(QObject *parent ):
    QObject(parent), m_id(-1), m_date(), m_specieId(-1)
{
    //m_model = new BonsaiModel(m_date, m_name, m_specieId, this);
}

Bonsai::Bonsai(const Bonsai &bonsai): QObject(0)
{
    m_id = bonsai.index();
    m_date = bonsai.date();   
    m_specieId = bonsai.specieId();
    //m_model = new BonsaiModel(m_date, m_name, m_specieId, this);
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

int Bonsai::specieId() const
{
    return m_specieId;
}

void Bonsai::setSpecieId(const int specieId)
{
    m_specieId = specieId;
}

int Bonsai::date() const
{
    return m_date;
}

void Bonsai::setDate(const int date)
{
    m_date = date;
}
