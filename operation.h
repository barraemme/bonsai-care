#ifndef OPERATION_H
#define OPERATION_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QDate>
#include <QVariant>

class Operation : public QObject
{
    Q_OBJECT

public:
    Operation(QObject *parent = 0);
    Operation(const Operation &operation);
    virtual ~Operation();

    Operation & operator =(const Operation &operation);

public:

    int index() const;
    void setIndex(const int index);

    int type() const;
    void setType(const int type);

    QString name() const;
    void setName(const QString &name);

    int month() const;
    void setMonth(const int month);

    QString schedule() const;
    void setSchedule(const QString &schedule);

    QVariant scheduleValue() const;
    void setScheduleValue(const QVariant &value);

    int bonsaiId() const;
    void setBonsaiId(const int);

    QDate lastDate() const;
    void setLastDate(const QDate &date);


private:
    int m_id;
    int m_type;
    QString m_name;
    int m_month;
    QString m_schedule;
    QVariant m_schedule_value;
    int m_bonsai_id;
    QDate m_last_date;

};

#endif // OPERATION_H
