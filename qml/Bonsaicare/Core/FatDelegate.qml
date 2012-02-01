import QtQuick 1.0

Component {
    id: list

    Item {
        //signal clicked(variant object)
        id: wrapper;
        width: wrapper.ListView.view.width;
        height: 130 //50+5+5

        DBModel{
            id: db;
        }

        Rectangle {
            id: blackRect
            color: "black";
            opacity: wrapper.ListView.index % 2 ? 0.2 : 0.3;
            height: wrapper.height-2;
            width: wrapper.width;
            y: 1
        }

        Item {
            id: moveMe;
            height: parent.height-2
            width: parent.width;

            Item {
                id: image; x: 6; width: 65; height: 65; smooth: true
                anchors.verticalCenter: parent.verticalCenter

                Loading { x: 1; y: 1; width: 65; height: 65; visible: realImage.status != Image.Ready }
                Image {
                    id: realImage;
                    source: "images/small/s_spc_"+ref+".jpg";
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
            Text {
                id:nameTxt //y:4; x: 56
                text: db.getName(ref)
                font.pixelSize: 25
                font.bold: true
                color: "#bbb"
                style: Text.Raised;
                styleColor: "black"
                wrapMode: Text.WordWrap
                anchors.left: image.right
                anchors.right: parent.right
                anchors.leftMargin: 6
                anchors.rightMargin: 6
                anchors.top: parent.top
                anchors.topMargin: 6
            }

            Text {
                id:txt; //y:4; x: 56
                text: db.getDate(date);
                font.pixelSize: 20;
                font.bold: false;
                color: "#bbb";
                style: Text.Raised;
                styleColor: "black"
                wrapMode: Text.WordWrap
                anchors.left: image.right
                //anchors.right: blackRect.right
                anchors.leftMargin: 6
                //anchors.rightMargin: 6
                anchors.top: nameTxt.bottom
                anchors.topMargin: 6
            }

            ItemDelegate{
                id: itemDelegate                
            }

            ItemModel{
                id: itemModel
                iId: itemId
            }

            // The actual list
            ListView {
                id: listView
                model: itemModel.model;
                delegate: itemDelegate;
                cacheBuffer: 10
                anchors.left: image.right;
                anchors.leftMargin: 6
                anchors.top: txt.bottom
                anchors.topMargin: 6
                orientation: ListView.Horizontal
            }

        }

        Text {
            id: go
            //width: 60
            text: ">"
            font.pixelSize: 60;
            font.bold: false;
            color: "#bbb";
           // styleColor: "black"
            anchors.right: wrapper.right
            anchors.rightMargin: 6
            verticalAlignment: Text.AlignVCenter

            anchors.verticalCenter: parent.verticalCenter
        }

        MouseArea {
            id: mouseRegion
            anchors.fill: parent
            onClicked: wrapper.ListView.view.currentIndex = index
        }

        states: [
            State {
                name: "Pressed"
                when: mouseRegion.pressed === true
                PropertyChanges { target: blackRect; color: "green" }
            }
        ]
        transitions: Transition {
            ColorAnimation { target: blackRect; }
        }

    }

}
