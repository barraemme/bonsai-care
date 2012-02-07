#ifndef OPERATION_H
#define OPERATION_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QDate>

class Operation : public QObject
{
    Q_OBJECT

public:
    Operation(const int id, const QDate &date, const QString &name, const int slotId, QObject *parent = 0 );
    Operation(QObject *parent = 0);
    Operation(const Operation &operation);
    virtual ~Operation();

public:

    int index() const;
    void setIndex(const int);

    int slotId() const;
    void setSlotId(const int);

    QDate lastDate() const;
    void setLastDate(const QDate &date);

    QString name() const;
    void setName(const QString &name);

private:

    int m_id;
    int m_slot_id;
    QString m_name;
    QDate m_last_date;

};

#endif // OPERATION_H
