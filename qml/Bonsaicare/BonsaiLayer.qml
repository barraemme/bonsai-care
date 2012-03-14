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

    GridView {
        id: bonsaiLayer
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        model: container.model
        delegate: BonsaiDelegate{
            width: bonsaiLayer.cellWidth
            height: bonsaiLayer.cellHeight
        }
        snapMode: GridView.SnapToRow
        //clip: true
        //interactive: true
        //highlightRangeMode: ListView.StrictlyEnforceRange
        // Cache the whole bonsaiLayer into memory.
        cacheBuffer: 1920
        height: Math.floor((parent.width-40)/3)//300
        cellWidth: Math.floor((parent.width-40)/3)
        cellHeight: Math.floor((parent.width-40)/3)
        //highlight: overlayOperations
        highlightFollowsCurrentItem: false
        //focus: true
        //x: -(screen.width * 1.5)
        currentIndex: -1
        onCurrentItemChanged: {
        //    currentItem.state = "overlayed"
        }

        //contentHeight:  container.model.count * container.itemHeight
        onCurrentIndexChanged: console.log("bonsayLayer current index changed to " +currentIndex)
    }

    /*ListView {
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
    }*/


}
