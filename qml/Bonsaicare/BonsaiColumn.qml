import QtQuick 1.0
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
    // Defined in order to scorll the bonsai column with content pane.
    property alias contentY: bonsaiColumn.contentY
    property alias bonsaiIndex: bonsaiColumn.currentIndex

    property bool landscapeLayout: !view.inPortrait

    // bonsais are being shown in a vertical list
    ListView {
        id: bonsaiColumn

        anchors.fill: parent
        contentHeight:  container.model.count * container.itemHeight

        model: container.model
        delegate: bonsaiDelegate
        snapMode: ListView.SnapToItem
        clip: true
        interactive: false
        highlightRangeMode: ListView.StrictlyEnforceRange
        // Cache the whole bonsaicolumn into memory.
        cacheBuffer: 1920
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
                    right: parent.right
                    rightMargin: container.bonsaiMarginRight
                    left: parent.left
                    leftMargin: container.bonsaiMarginRight
                }
                font.pixelSize: container.fontSize
                wrapMode : Text.Wrap
                text: b_name
            }

            Item {
                id: image; x: 6; width: 65; height: 65; smooth: true
                anchors {
                    top: nameTxt.bottom
                    topMargin: container.textTopMargin
                    left: parent.left
                    leftMargin: 0
                }

                Core.Loading { x: 1; y: 1; width: 65; height: 65; visible: realImage.status != Image.Ready }
                Image {
                    id: realImage;
                    source: "images/small/s_spc_"+b_itemId+".jpg";
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
                id: dateTxt
                color: container.textColor
                anchors {
                    top: image.bottom
                    topMargin: container.textTopMargin
                    left: parent.left
                    leftMargin: 2
                    right: parent.right
                    rightMargin: container.bonsaiMarginRight
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
