#ifndef BONSAI_H
#define BONSAI_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QDate>


class Bonsai : public QObject
{
    Q_OBJECT

public:
    Bonsai(const int id, const int year, const int itemId, QObject *parent = 0 );
    Bonsai(QObject *parent = 0);
    Bonsai(const Bonsai &bonsai);
    virtual ~Bonsai();

public:
    //QObject *items() const;

    int index() const;
    void setIndex(const int);

    int itemId() const;
    void setItemId(const int);

    int date() const;
    void setDate(const int date);

    QString name() const;   

private:
    //BonsaiModel *m_model;
    int m_id;
    int m_itemId;    
    int m_date;
};

#endif // BONSAI_H
