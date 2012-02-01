import QtQuick 1.0

Item {
    id: wrapper
    property variant model: xmlModel //testModel
    property int status: xmlModel.status
    property string errorString: xmlModel.errorString()
    property int iId: 0;
    function reload() { xmlModel.reload(); }

    XmlListModel {
        id: xmlModel

        source: 'resources/items.xml'
        query: "/items/item[@id="+wrapper.iId+"]/operations/operation"

        XmlRole { name: "opid"; query: "@id/number()" }

    }

}
