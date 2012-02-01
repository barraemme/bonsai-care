import QtQuick 1.0

Item {
    id: screen;
    state:"list"
    Keys.onEscapePressed: screen.state="list"
    Keys.onBacktabPressed: screen.state="list"
    Rectangle {
        id: background
        anchors.fill: parent; color: "#343434";

        state:"list"
        Image { source: "images/stripes.png"; fillMode: Image.Tile; anchors.fill: parent; opacity: 0.3 }

        /*MouseArea {
            anchors.fill: parent
            onClicked: home.focus = false;
        }*/

        LstModel { id: lstModel }
        DBModel{ id: db }        

        Loading { anchors.centerIn: parent; visible: lstModel.status==XmlListModel.Loading }

        Text {
            width: 180
            text: qsTr("Error loading list: ")+lstModel.errorString;
            color: "#cccccc"; style: Text.Raised; styleColor: "black"; wrapMode: Text.WordWrap
            visible: lstModel.status==XmlListModel.Error; anchors.centerIn: parent
        }


        Item {
            id: views
            x: 2;
            width: parent.width - 4
            y:40 //Below the title bars
            height: parent.height - 60


            FatDelegate { id: fatDelegate }

            ListView {
                id: mainView
                model: lstModel.model
                delegate: fatDelegate
                width: parent.width
                height: parent.height
                x: 0
                currentIndex: -1
                cacheBuffer: 100
                /*onCurrentItemChanged: {
                    singleView.myItem = lstModel.model.get(mainView.currentIndex)
                    screen.state="view"
                }*/
            }

            AddDelegate{ id: addDelegate }

            GridView {
                id: addView
                model: db
                delegate: addDelegate
                width: parent.width
                height: parent.height
                cellWidth: (parent.width-2)/3; cellHeight: (parent.width-2)/3
                x: -(screen.width * 1.5)
                currentIndex: -1
                cacheBuffer: 100
                onCurrentIndexChanged: {
                    console.log(addView.currentIndex);
                    var item = db.get(addView.currentIndex);
                    modelData.setModelData(itemModel,-1,-1,0,item);
                }
            }

            SingleView {
                id: singleView
                width: parent.width
                height: parent.height
                x: -(screen.width * 1.5)               
            }

        }

        //MultiTitleBar { id: titleBar; width: parent.width }
        ToolBar {
            id: toolBar; height: 40;
            y: 0
            //anchors.bottom: parent.bottom;
            //TODO: Use anchor changes instead of hard coding
            //y: 0//screen.height - 40
            width: parent.width;
            opacity: 0.9
            button2Label: qsTr("Add")
            onButton2Clicked: {
                screen.state="add"
            }
        }
    }
    states: [

      State {
            name: "add";
            PropertyChanges { target: addView; x: 0; focus:true}
            PropertyChanges { target: singleView; x: -(parent.width * 1.5)}
            PropertyChanges { target: mainView; x: -(parent.width * 1.5) }           
            PropertyChanges { target: toolBar; button2Label: qsTr("Back") }
            PropertyChanges { target: toolBar; onButton2Clicked: screen.state="list"}
        },
        State {
              name: "list";
              PropertyChanges { target: mainView; x: 0; focus:true}
              PropertyChanges { target: singleView; x: -(parent.width * 1.5)}
              PropertyChanges { target: addView; x: -(parent.width * 1.5) }              
              PropertyChanges { target: toolBar; button2Label: qsTr("Add") }
              PropertyChanges { target: toolBar; onButton2Clicked: screen.state="add"}
          },
        State {
              name: "view";
              PropertyChanges { target: singleView; x: 0; focus:true}
              PropertyChanges { target: addView; x: -(parent.width * 1.5)}
              PropertyChanges { target: mainView; x: -(parent.width * 1.5) }
              PropertyChanges { target: toolBar; button2Label: qsTr("Back") }
              PropertyChanges { target: toolBar; onButton2Clicked: screen.state="list"}
          }

    ]
    transitions: [
       Transition {
           NumberAnimation { properties: "x,y,opacity"; duration: 500; easing.type: Easing.InOutQuad } }
    ]
}
