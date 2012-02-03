#ifndef BONSAIITEM_H
#define BONSAIITEM_H

#include <QtCore/QObject>
#include <QtCore/QString>

class BonsaiItemModel;

class BonsaiItem : public QObject
{
    Q_OBJECT

public:
    BonsaiItem(const int id, const QString &name, QObject *parent = 0);
    virtual ~BonsaiItem();

public slots:
    QObject *items() const;
    int index() const;
    void setIndex(const int);
    QString name() const;
    void setName(const QString &name);

private:
    BonsaiItemModel *m_model;
    int m_id;
    QString m_name;
};

#endif // BONSAIITEM_H
