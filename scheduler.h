#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <QSqlDatabase>
#include "bonsai.h"
#include "speciemodel.h"

class Scheduler: public QObject
{

    Q_OBJECT
public:
    Scheduler();
    //virtual ~Scheduler();

private:
    /*SpecieModel* m_itemmodel;
    QSqlDatabase db;*/

};

#endif // SCHEDULER_H
