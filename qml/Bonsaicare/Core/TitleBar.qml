import QtQuick 1.0

Item {
    id: titleBar
    property string text: "My bonsai list"

    BorderImage { source: "images/titlebar.sci"; width: parent.width; height: parent.height + 14; y: -7 }

    Item {
        id: container
        width: (parent.width * 2) - 55 ; height: parent.height

        function accept() {
            titleBar.state = ""
            background.state = ""
        }        

        Image {
            id: quitButton
            x: 5
            anchors.verticalCenter: parent.verticalCenter
            source: "images/quit.png"
            MouseArea {
                anchors.fill: parent
                onClicked: Qt.quit()
            }
        }

        Text {
            id: categoryText
            anchors {
                right: quitButton.left; left: parent.left; leftMargin: 10; rightMargin: 10
                verticalCenter: parent.verticalCenter
            }
            elide: Text.ElideLeft
            text:  text
            font.bold: true; color: "White"; style: Text.Raised; styleColor: "Black"
            font.pixelSize: 12
        }
    }

   states: State {
        name: "Tags"
        PropertyChanges { target: container; x: -tagButton.x + 5 }
    }

    transitions: Transition {
        NumberAnimation { properties: "x"; easing.type: Easing.InOutQuad }
    }
}
