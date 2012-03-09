#include "bonsaiserializer.h"
#include "specie.h"
#include "operation.h"
#include <QDebug>

BonsaiSerializer::BonsaiSerializer(const QXmlNamePool &namePool)
    : QAbstractXmlReceiver(),namePool(namePool)
{
}

BonsaiSerializer::~BonsaiSerializer(){
    //qDebug()<<"BonsaiSerializer destroied";
}

void BonsaiSerializer::characters ( const QStringRef & valueref ){
    QString currentElement = elements.top();

    if (currentElement == "operation"){
        currentOperation.setScheduleValue( valueref.toString());
    }
}

void BonsaiSerializer::attribute(const QXmlName &xmlname, const QStringRef &valueref)
{
    QString name = xmlname.localName(namePool);
    QString value = valueref.toString();
    QString currentElement = elements.top();

    //qDebug()<<name<<" "<<value;

    /** SPECIE **/
    if (currentElement == "specie"){
        if(name == "id")
            currentSpecie.setIndex(value.toInt());
        else if (name == "name")
            currentSpecie.setName(value);
    }else
    /** OPERATION **/
    if (currentElement == "operation"){
        if(name == "type")
            currentOperation.setType(value.toInt());
        else if(name == "name")
            currentOperation.setName(value);
        else if(name == "month")
            currentOperation.setMonth(value.toInt());
        else if(name == "schedule")
            currentOperation.setSchedule(value);
    }
}

void BonsaiSerializer::startElement(const QXmlName &xmlname)
{
    QString name = xmlname.localName(namePool);

    elements.push(name);

    //qDebug()<<"<"<<name<<">";

    if (name == "specie"){
        currentSpecie =  Specie();

    }
    if (name == "operation"){
        currentOperation = Operation();
    }


}

void BonsaiSerializer::endElement()
{
   QString name = elements.pop();
    if (name == "specie"){
        species.append(currentSpecie);

    }
    if (name == "operation"){
        operations.append(currentOperation);

    }

    //qDebug()<<"</"<<name<<">";

}
