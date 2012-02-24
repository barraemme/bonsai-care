#ifndef BONSAIWORKER_H
#define BONSAIWORKER_H

#include <QSqlDatabase>
#include "bonsai.h"
#include "specie.h"

class BonsaiWorker: public QObject {

    Q_OBJECT

public:
    BonsaiWorker();
    virtual ~BonsaiWorker();

signals:
    void bonsaiRowFetchDone(Bonsai* bonsai);
    void specieRowFetchDone(Specie* specie);
    void fetchBonsaiDone();
    void fetchSpeciesDone();

public slots:
    void fetchAllBonsai();
    void fetchAllSpecies();

    void insertBonsai(const int specieId, const int year);

public:
    int nextId();


private:
    QSqlDatabase db;

    void parseSpeciesWithXQuery();

};

#endif // BONSAIWORKER_H
