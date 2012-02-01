import QtQuick 1.0

Item {
    id: toolbar

    property alias button2Label: button2.text
    property alias button1Enable: exit.opacity
    property alias button2Enable: button2.opacity
    signal button1Clicked
    signal button2Clicked
    property string titleText: qsTr("My bonsai list")

    focus:true
    BorderImage { source: "images/titlebar.sci"; width: parent.width; height: parent.height + 14; y: -7 }
    Button {
        id: exit
        text: qsTr("exit")
        anchors.left: parent.left; anchors.leftMargin: 5; y: 3; width: 70; height: 30
        onClicked: Qt.quit()
        focus:true
        opacity: 1
    }

    Text {
        id: categoryText
        anchors {
            left: exit.right;
            right: button2.left;
            leftMargin: 10;
            rightMargin: 10
            verticalCenter: parent.verticalCenter
        }
        elide: Text.ElideLeft
        text:  titleText
        font.bold: true;
        color: "White";
        style: Text.Raised;
        styleColor: "Black"
        font.pixelSize: 20
    }

    Button {
        id: button2
        anchors.right: parent.right; anchors.rightMargin: 5; y: 3; width: 70; height: 30
        onClicked: toolbar.button2Clicked()
        opacity: 1
    }

    transitions: [
       Transition {
        //   PropertyAnimation { properties: "button1Enable";  duration: 500; easing.type: Easing.InBounce          }
         //  PropertyAnimation { properties: "button2Enable";  duration: 500; easing.type: Easing.InBounce           }
        }
    ]
}
