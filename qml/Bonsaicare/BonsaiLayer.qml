import QtQuick 1.1
import com.nokia.symbian 1.1
import "Core" 1.1 as Core

Item {
    id: container

    // **MUST BE SET FROM OUTSIDE**
    property variant model

    // Defines the column height. Should be set from outside.
    property int itemHeight: visual.itemHeight
    // Settable colors.
    property int fontSize: visual.generalFontSize
    property color textColor: visual.headerTextColor
    // Defined in order to scroll the bonsai column with content pane.
    property alias contentY: bonsaiLayer.contentY
    property alias bonsaiIndex: bonsaiLayer.currentIndex

    property bool landscapeLayout: mainWindow.landscapeLayout

    // bonsais are being shown in a vertical list
    ListView {
        id: bonsaiLayer

        anchors.fill: parent
        anchors.bottomMargin: 30
        contentHeight:  container.model.count * container.itemHeight

        model: container.model
        delegate: bonsaiDelegate
        snapMode: ListView.SnapToItem
        clip: true
        interactive: true
        highlightRangeMode: ListView.StrictlyEnforceRange
        // Cache the whole bonsaiLayer into memory.
        cacheBuffer: 1920

        // ScrollBar indicator.
        // Take the bottommost search field height into account.
        ScrollDecorator {
            anchors {
                right: parent.right
                top: parent.top
                bottom: parent.bottom
            }
            // flickableItem binds the scroll decorator to the ListView.
            flickableItem: bonsaiLayer
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
                    topMargin: visual.textTopMargin
                    left: parent.left
                    leftMargin: visual.bonsaiNameMarginLeft
                }
                font.weight: Font.Bold
                font.pixelSize: container.fontSize
                wrapMode : Text.Wrap
                text: b_name+", "+ container.model.getAgeString(b_date)
            }

            Item {
                id: image;
                width: 100;
                height: 100;
                smooth: true
                anchors {
                    top: nameTxt.bottom
                    topMargin: visual.textTopMargin
                    right: parent.right
                    rightMargin:20
                }

                Core.Loading {
                    width: 100;
                    height: 100;
                    visible: realImage.status != Image.Ready
                }

                Image {
                    id: realImage;
                    source: "images/medium/m_spc_"+b_specieId+".png";
                    width:100; height:100; opacity:0 ;
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

            // Line in the bottom of the item.
            Rectangle {
                color: visual.borderColor
                width: parent.width-visual.bonsaiNameMarginLeft
                height: 1
                anchors.top: parent.bottom
                anchors.right: parent.right
            }
        }
    }
}
