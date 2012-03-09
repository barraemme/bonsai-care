#ifndef BONSAISERIALIZER_H
#define BONSAISERIALIZER_H

#include <QAbstractXmlReceiver>
#include <QHash>
#include <QStack>
#include <QString>
#include <QXmlNamePool>
#include "specie.h"
#include "operation.h"

class BonsaiSerializer : public QAbstractXmlReceiver
{
public:
    BonsaiSerializer(const QXmlNamePool &namePool);
    ~BonsaiSerializer();
    void attribute(const QXmlName &name, const QStringRef &value);
    void endElement();
    void startElement(const QXmlName &name);

    void atomicValue(const QVariant &) {}
    void characters(const QStringRef &);
    void comment(const QString &) {}
    void endDocument() {}
    void endOfSequence() {}
    void namespaceBinding(const QXmlName &) {}
    void processingInstruction(const QXmlName &, const QString &) {}
    void startDocument() {}
    void startOfSequence() {}

    QList<Specie> species;
    QList<Operation> operations;

private:
    QXmlNamePool namePool;
    QStack<QString> elements;
    Specie currentSpecie;
    Operation currentOperation;
};

#endif // BONSAISERIALIZER_H
