import QtQuick 1.0

Item {
    id: container

    property variant model: null
    property int bonsaiMargin: visual.bonsaiMargin
    property int textTopMargin: visual.textTopMargin
    property int selectionIndicatorWidth: visual.selectionIndicatorWidth
    property color borderColor: visual.borderColor
    property int itemHeight: visual.itemHeight
    // Define color & size of the text
    property color textColor: visual.cellTextColor
    property int fontSize: visual.cellFontSize

    // Internal properties, don't touch from outside!
    //width: spanned ? 0 : parent.width
    //height: spanned ? 0 : bonsaiSpan * container.itemHeight
    // Visible only, if not under bonsai spanning
    //visible: spanned ? false : true
    Component.onCompleted: {
        console.log("Cell" +d_dayName);
    }


    // Gradient rectangle that indicates the "pressed" status of the item.
    Rectangle {
        id: gradientRect
        anchors.fill: parent
        //opacity: ma.pressed ? 1 : 0

        gradient: Gradient {
            GradientStop { position: 0.0; color: Qt.rgba(9,0,0,0.1) }
            GradientStop { position: 0.8; color: Qt.rgba(9,0,0,0.5) }
            GradientStop { position: 1.0; color: Qt.rgba(9,0,0,0.1) }
        }

        Behavior on opacity {
            NumberAnimation {
                duration: 100
            }
        }
    }

    // bonsais are being shown in a vertical list
    /*ListView {
        id: operationsList
        anchors.fill: parent
        orientation: ListView.Horizontal
        model: container.model
        delegate: bonsaiDelegate
        snapMode: ListView.SnapToItem
        clip: true
        interactive: false
        highlightRangeMode: ListView.StrictlyEnforceRange
        // Cache the whole bonsaicolumn into memory.
        cacheBuffer: 1920
    }*/

    Item {
        id: cellItem

        width: parent.width
        height: parent.height
        anchors.left: parent.left
        clip: true

        /*BorderImage {
            visible: cellText.text ? true : false
            width: container.selectionIndicatorWidth
            height: cellItem.height
            source: index % 2 ? "gfx/selection_green.png"
                              : "gfx/selection_turquoise.png"
            border.left: 3; border.top: 10
            border.right: 35; border.bottom: 10
        }*/

        Text {
            id: cellText

            anchors {
                top: parent.top
                topMargin: container.textTopMargin
                left: parent.left
                leftMargin: container.bonsaiMargin
                right: parent.right
                bottom: parent.bottom
                bottomMargin: container.textTopMargin/2
            }
            text: d_dayName//itemData
            color: container.textColor
            font.pixelSize: container.fontSize
            wrapMode: Text.WordWrap
        }
    }

    // A thin line below the item to separate Cells from each other.
    Rectangle {
        color: parent.borderColor
        width: parent.width
        height: 1
        anchors.top: parent.bottom
    }

    // Manually adjust the text edit focus.
    /*MouseArea {
        id: ma
        anchors.fill: parent

        onClicked: {
            if (cellText.text == "") {
                eventEditView.selectedDayIndex = weekDayIndex;
                eventEditView.originalDayIndex = weekDayIndex;
                eventEditView.eventDay = dayName;
                eventEditView.eventTitle = itemData;
                eventEditView.eventStart = startTime;
                eventEditView.eventEnd = endTime;
                eventEditView.startbonsaiIndex = index;
                eventEditView.endbonsaiIndex = index + bonsaiSpan;
                pageStack.push(eventEditView);
            } else {
                eventDetailsView.selectedDayIndex = weekDayIndex;
                eventDetailsView.eventDay = dayName;
                eventDetailsView.eventTitle = itemData;
                eventDetailsView.eventStart = startTime;
                eventDetailsView.eventEnd = endTime;
                eventDetailsView.startbonsaiIndex = index;
                eventDetailsView.endbonsaiIndex = index + bonsaiSpan;
                pageStack.push(eventDetailsView);
            }
        }
    }*/
}
