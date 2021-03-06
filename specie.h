#ifndef BONSAIITEM_H
#define BONSAIITEM_H

#include <QtCore/QObject>
#include <QtCore/QString>

class SpecieModel;

class Specie : public QObject
{
    Q_OBJECT

public:
    Specie(const int id, const QString &name, QObject *parent = 0);
    Specie(QObject *parent = 0);
    Specie(const Specie &specie);
    virtual ~Specie();

    Specie & operator =(const Specie &other);
public slots:
    //QObject *items() const;
    int index() const;
    void setIndex(const int);
    QString name() const;
    void setName(const QString &name);

private:
    //SpecieModel *m_model;
    int m_id;
    QString m_name;
};

#endif // BONSAIITEM_H
