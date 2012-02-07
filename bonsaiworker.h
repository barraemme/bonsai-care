#ifndef BONSAIWORKER_H
#define BONSAIWORKER_H

#include <QSqlDatabase>
#include "bonsai.h"
#include "speciemodel.h"

class BonsaiWorker: public QObject {

    Q_OBJECT

public:
    BonsaiWorker(SpecieModel* m_model);
    virtual ~BonsaiWorker();

signals:
    void fetched(Bonsai* bonsai);
    void finished();

public slots:
    void readAll();
private:
    SpecieModel* m_itemmodel;
    QSqlDatabase db;

};

#endif // BONSAIWORKER_H
