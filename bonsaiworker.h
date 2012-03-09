#ifndef BONSAIWORKER_H
#define BONSAIWORKER_H

#include <QSqlDatabase>
#include "bonsai.h"
#include "specie.h"
#include "operation.h"
#include "slot.h"

class BonsaiWorker: public QObject {

    Q_OBJECT

public:
    BonsaiWorker();
    virtual ~BonsaiWorker();

signals:
    void fetchBonsaiRecordDone(Bonsai* bonsai);
    void fetchSpecieRecordDone(const Specie* specie);
    void fetchBonsaiDone();
    void fetchSpeciesDone();
    void fetchSlotDone(Slot* sl);

public slots:
    void fetchAllBonsai();
    void fetchAllSpecies();
    void fetchSlot(const int bonsai_id, const QDate &date);

    void insertBonsai(const int specieId, const int year);

public:
    int nextId(const QString & table);
    void schedule(Bonsai *bonsai);
    void cleanOldOperations();
    void insertOperation(Operation &op);

private:
    QSqlDatabase db;

    void parseSpeciesWithXQuery();

};

#endif // BONSAIWORKER_H
