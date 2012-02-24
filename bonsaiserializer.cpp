#include "bonsaiserializer.h"
#include "specie.h"
#include "operation.h"

BonsaiSerializer::BonsaiSerializer(const QXmlNamePool &namePool)
    : namePool(namePool)
{
}

void BonsaiSerializer::attribute(const QXmlName &xmlname, const QStringRef &valueref)
{
    QString name = xmlname.localName(namePool);
    QString value = valueref.toString();
    QString currentElement = elements.top();

    /** SPECIE **/
    if (currentElement == "specie" && name == "id")
        currentSpecie->setIndex(value.toInt());
    else if (currentElement == "specie" && name == "name")
        currentSpecie->setName(value);

    /** OPERATION **/
    if (currentElement == "operation" && name == "id")
        currentOperation->setIndex(value.toInt());

}

void BonsaiSerializer::startElement(const QXmlName &xmlname)
{
    QString name = xmlname.localName(namePool);
    elements.push(name);

    if (name == "specie")
        currentSpecie = new Specie();
    if (name == "operation")
        currentOperation = new Operation();
}

void BonsaiSerializer::endElement()
{
    if (elements.pop() == "specie")
        species.append(currentSpecie);
    if (elements.pop() == "operation")
        operations.append(currentOperation);
}
