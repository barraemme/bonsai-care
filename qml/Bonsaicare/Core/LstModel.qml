import QtQuick 1.0

Item {
    id: wrapper
    property variant model: xmlModel //testModel
    property int status: xmlModel.status
    property string errorString: xmlModel.errorString()
    function reload() { xmlModel.reload(); }

    XmlListModel {
        id: xmlModel

        source: 'resources/items.xml'
        query: "/items/item"

        XmlRole { name: "date"; query: "date/string()" }
        XmlRole { name: "specieId"; query: "@id/number()" }
        XmlRole { name: "ref"; query: "@ref/number()" }

    }    

}
