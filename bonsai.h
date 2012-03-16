#ifndef BONSAI_H
#define BONSAI_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QDate>
#include "operationmodel.h"

class Bonsai : public QObject
{
    Q_OBJECT

public:
    Bonsai(const int id, const int year, const int specieId, OperationModel* operationModel, QObject *parent = 0 );
    Bonsai(QObject *parent = 0);
    Bonsai(const Bonsai &bonsai);
    virtual ~Bonsai();

public:    

    int index() const;
    void setIndex(const int);

    int specieId() const;
    void setSpecieId(const int);

    int date() const;
    void setDate(const int date);

    QString name() const;   

    Q_INVOKABLE QObject* operations(const QDate & date = QDate::currentDate()) const;

private:    
    int m_id;
    int m_specieId;    
    int m_date;
    OperationModel* m_operation_model;
};

#endif // BONSAI_H
