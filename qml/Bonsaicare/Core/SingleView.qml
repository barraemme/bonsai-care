import QtQuick 1.0

Item {

    LstModel { id: lstModel }

    property variant myItem: lstModel.model.get(0);

    DBModel{
        id: db;
    }

    ItemDelegate{
        id: itemDelegate
    }

    ItemModel{
        id: itemModel
        iId: myItem.itemId
    }


    Item {
        id: image; x: 6; y:6; width: 65; height: 65; smooth: true
        //anchors.verticalCenter: parent.verticalCenter

        Loading { x: 1; y: 1; width: 65; height: 65; visible: realImage.status != Image.Ready }
        Image {
            id: realImage;
            source: "images/small/s_spc_"+myItem.ref+".jpg";
            x: 1; y: 1;
            width:65; height:65; opacity:0 ;
            onStatusChanged: {
                if(status==Image.Ready)
                    image.state="loaded"
            }
        }
        states: State {
            name: "loaded";
            PropertyChanges { target: realImage ; opacity:1 }
        }
        transitions: Transition { NumberAnimation { target: realImage; property: "opacity"; duration: 200 } }
    }

    Item{
        anchors.left: image.right
        anchors.leftMargin: 6

        Row{
            spacing: 5

            Text {
                text: db.getName(myItem.ref)
                font.pixelSize: 25
                font.bold: true
                color: "#bbb"
                style: Text.Raised;
                styleColor: "black"
                wrapMode: Text.WordWrap
            }

            Text {
                text: db.getDate(myItem.date);
                font.pixelSize: 20;
                font.bold: false;
                color: "#bbb";
                style: Text.Raised;
                styleColor: "black"
                wrapMode: Text.WordWrap
            }
        }
    }

    // The actual list
    ListView {
        id: listView
        model: itemModel.model;
        delegate: itemDelegate;
        cacheBuffer: 10
        orientation: ListView.Horizontal
        anchors.top: image.bottom
        anchors.topMargin: 6

    }

}
