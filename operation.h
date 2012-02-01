#ifndef OPERATION_H
#define OPERATION_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QDate>

class Operation : public QObject
{
    Q_OBJECT

public:
    Operation(const int id, const QDate &date, const QString &name, const int itemId, QObject *parent = 0 );
    Operation(QObject *parent = 0);
    Operation(const Operation &operation);
    virtual ~Operation();

public slots:
    //QObject *items() const;

    int index() const;
    void setIndex(const int);

    int bonsaiId() const;
    void setBonsaiId(const int);

    QDate lastDate() const;
    void setLastDate(const QDate &date);

    QString name() const;
    void setName(const QString &name);

private:
    //BonsaiModel *m_model;
    int m_id;
    int m_bonsaiId;
    QString m_name;
    QDate m_last_date;


};

#endif // OPERATION_H
