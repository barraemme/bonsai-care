#include "bonsai.h"
#include "bonsaimodel.h"

// Platform includes
#include <QtCore/QDebug>
#include <QtCore/QDate>

Bonsai::Bonsai(const int id, const int date, const int specie, OperationModel* operationModel, QObject *parent ):
    QObject(parent), m_id(id), m_date(date), m_specieId(specie), m_operation_model(operationModel)
{

}

Bonsai::Bonsai(QObject *parent ):
    QObject(parent), m_id(-1), m_date(), m_specieId(-1), m_operation_model()
{

}

Bonsai::Bonsai(const Bonsai &bonsai): QObject(0)
{
    m_id = bonsai.index();
    m_date = bonsai.date();   
    m_specieId = bonsai.specieId();
    m_operation_model = qobject_cast<OperationModel *>(bonsai.operations(QDate::currentDate()));
}

Bonsai::~Bonsai()
{
    delete m_operation_model;
}

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

QObject* Bonsai::operations(const QDate &date) const
{
    return m_operation_model;
}
