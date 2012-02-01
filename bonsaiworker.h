#ifndef BONSAIWORKER_H
#define BONSAIWORKER_H

#include <QSqlDatabase>
#include "bonsai.h"
#include "bonsaiitemmodel.h"

class BonsaiWorker: public QObject {

    Q_OBJECT

public:
    BonsaiWorker(BonsaiItemModel* m_model);
    virtual ~BonsaiWorker();

signals:
    void fetched(Bonsai* bonsai);

public slots:
    void readAll();
private:
    BonsaiItemModel* m_itemmodel;
    QSqlDatabase db;

};

#endif // BONSAIWORKER_H
