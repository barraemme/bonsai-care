import QtQuick 1.1
import com.nokia.symbian 1.1
import "Core" 1.1 as Core

Item {
    id: container

    // Public properties
    property int bonsaiMargin: visual.bonsaiMargin
    property int bonsaiMarginRight: visual.bonsaiMarginRight
    property int textTopMargin: visual.textTopMargin
    property color borderColor: visual.borderColor
    property color delimiterColor: visual.delimiterColor
    // **MUST BE SET FROM OUTSIDE**
    property variant model

    // Defines the column height. Should be set from outside.
    property int itemHeight: visual.itemHeight
    // Settable colors.
    property int fontSize: visual.generalFontSize
    property color textColor: visual.headerTextColor
    // Defined in order to scroll the bonsai column with content pane.
    property alias contentY: bonsaiColumn.contentY
    property alias bonsaiIndex: bonsaiColumn.currentIndex

    property bool landscapeLayout: mainWindow.landscapeLayout

    // bonsais are being shown in a vertical list
    ListView {
        id: bonsaiColumn

        anchors.fill: parent
        contentHeight:  container.model.count * container.itemHeight

        model: container.model
        delegate: bonsaiDelegate
        snapMode: ListView.SnapToItem
        clip: true
        interactive: true
        highlightRangeMode: ListView.StrictlyEnforceRange
        // Cache the whole bonsaicolumn into memory.
        cacheBuffer: 1920

        Component.onCompleted: {
            console.log("BonsaiColumn size: ("
                        + bonsaiColumn.width + "," + bonsaiColumn.height
                        + "), contentSize: ("
                        + bonsaiColumn.contentWidth + "x" + bonsaiColumn.contentHeight
                        + ") bonsaiModel count: " + container.model.count
                        + " itemHeight: " + container.itemHeight);
        }

        onCountChanged: {
            if (Component.status != Component.Ready)
            {
                console.log("Not ready: " + Component.status + " progress: " + Component.progress);
                return;
            }

            console.log("QML BonsaiColumn onCountChanged count:"+count);
        }

        // ScrollBar indicator.
        // Take the bottommost search field height into account.
        ScrollDecorator {
            anchors {
                right: parent.right
                top: parent.top
                bottom: parent.bottom
            }
            // flickableItem binds the scroll decorator to the ListView.
            flickableItem: bonsaiColumn
        }

    }



    // bonsai prototype item.
    Component {
        id: bonsaiDelegate

        Item {
            id: bonsaiRect
            width: container.width
            height: container.itemHeight

            Text {
                id: nameTxt
                color: container.textColor
                anchors {
                    top: parent.top
                    topMargin: container.textTopMargin
                    /*right: parent.right
                    rightMargin: container.bonsaiMarginRight*/
                    left: parent.left
                    leftMargin: container.bonsaiMarginRight
                }
                font.weight: Font.Bold
                font.pixelSize: container.fontSize
                wrapMode : Text.Wrap
                text: b_name
            }

            Item {
                id: image;
                width: 200;
                height: 200;
                smooth: true
                anchors {
                    horizontalCenter: parent.horizontalCenter
                    verticalCenter: parent.verticalCenter
                    top: nameTxt.bottom
                    topMargin: container.textTopMargin
                    /*left: parent.left
                    leftMargin: 0*/
                }

                Core.Loading {
                    width: 200;
                    height: 200;
                    visible: realImage.status != Image.Ready
                }

                Image {
                    id: realImage;
                    source: "images/medium/m_spc_"+b_itemId+".png";
                    width:200; height:200; opacity:0 ;
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
                id: dateTxt
                color: container.textColor
                anchors {
                    top: image.bottom
                    topMargin: container.textTopMargin
                    left: parent.left
                    leftMargin: container.bonsaiMarginRight
                    /*right: parent.right
                    rightMargin: container.bonsaiMarginRight*/
                }
                font.pixelSize: container.fontSize
                wrapMode : Text.WordWrap
                text: container.model.getAgeString(b_date)
            }

            // Line in the bottom of the item.
            Rectangle {
                color: container.borderColor
                width: parent.width
                height: 1
                anchors.top: parent.bottom
            }

            // The thin red line.
            Rectangle {
                id: delimiter
                height: parent.height
                width: 3
                anchors.right: parent.right
                color: container.delimiterColor
            }
        }
    }
}
