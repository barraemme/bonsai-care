import QtQuick 1.0

// Pivot headers
Item {
    id: container

    property alias model: dayPathView.model
    // How wide the header is. Should be differentiated between portrait
    // and landscape modes.
    property int headerItemWidth: 182
    property int headerItemMonthWidth: 300
    // Colors, text sizes etc.
    property int headerTextSize: visual.headerTextSize
    property int fontSize: visual.generalFontSize
    property color selectedHeaderTextColor: "#BE5215"
    property color headerTextColor: "#6A5147"
    property color borderColor: "#C4AE94"
    property int generalLeftMargin: 25
    // Defines, whether the pathview can be flicked or only clicked.
    property bool flickable: true
    signal indexChanged(int index)
    property int currentIndex: 0
    property alias currentMonthIndex:monthPathView.currentIndex
    property bool landscapeLayout: mainWindow.landscapeLayout

    Text {
        id: appTitle

        anchors {
            left: parent.left
            leftMargin: container.generalLeftMargin
            top: parent.top
            topMargin: 2
        }
        font.pixelSize: container.fontSize
        text: qsTr("Bonsai Weekly Care")
        color: container.headerTextColor
    }

    PathView {
        id: monthPathView
        model: months
        width: parent.width

        anchors {
            top: appTitle.bottom
            left: parent.left
        }

        delegate: monthPivotHeaderDelegate
        interactive: false
        pathItemCount: 1
        preferredHighlightBegin: parent.landscapeLayout ? 2/4 : 2/3
        preferredHighlightEnd: parent.landscapeLayout ? 2/4 : 2/3
        z:1

        path: Path {
            id: monthPath

            property double scaleFactor: container.landscapeLayout ? 1/5 : 1/4

            // Start
            startX: landscapeLayout ? -(container.headerItemMonthWidth * 0.50)
                                    : -(container.headerItemMonthWidth * 0.65)
            startY: monthPathView.height / 2
            PathAttribute { name: "transparency"; value: 0.3 }

            PathLine {
                x: monthPathView.width * monthPath.scaleFactor;
                y: monthPathView.height / 2; }
            PathAttribute { name: "transparency"; value: 1.0 }

            PathLine {
                x: monthPathView.width * 2 * monthPath.scaleFactor;
                y: monthPathView.height / 2; }
            PathAttribute { name: "transparency"; value: 0.3 }

            // Stop
            PathLine {
                x: monthPathView.width + container.headerItemMonthWidth// * 1.2;
                y: monthPathView.height / 2; }
            PathAttribute { name: "transparency"; value: 0.0 }

        }       

        Component {
            id: monthPivotHeaderDelegate

            Item {
                id: monthDelegateItem
                height: parent.height
                width: container.headerItemMonthWidth

                Text {
                    color: monthDelegateItem.PathView.isCurrentItem ?
                               container.selectedHeaderTextColor
                             : container.headerTextColor
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    text: monthName

                    font {
                        pixelSize: container.headerTextSize*2
                        bold: false
                        weight: Font.Light
                    }

                    Behavior on color {
                        ColorAnimation {
                            duration: 500;
                        }
                    }
                }

            }
        }
    }

    PathView {
        id: dayPathView

        Component.onCompleted: pathItemCount = parent.landscapeLayout ? 4 : 3

        width: parent.width
        anchors {
            top: monthPathView.bottom
            bottom: parent.bottom
            left: parent.left
        }

        delegate: dayPivotHeaderDelegate

        interactive: parent.flickable
        preferredHighlightBegin: parent.landscapeLayout ? 1/4 : 1/3
        preferredHighlightEnd: parent.landscapeLayout ? 1/4 : 1/3
        currentIndex: container.currentIndex
        onCurrentIndexChanged: {
            console.log(parent.width +" dayPathView index change " + dayPathView.currentIndex);
            container.currentIndex = dayPathView.currentIndex;            
            container.currentMonthIndex = dayPathView.model.indexOfMonth(dayPathView.currentIndex)
            container.indexChanged(dayPathView.currentIndex);           
        }

        path: Path {
            id: dayPivotPath
            property double scaleFactor: container.landscapeLayout ? 1/5 : 1/4

            // Start
            startX: landscapeLayout ? -(container.headerItemWidth * 0.50)
                                    : -(container.headerItemWidth * 0.65)
            startY: dayPathView.height / 2
            PathAttribute { name: "transparency"; value: 0.3 }

            PathLine {
                x: dayPathView.width * dayPivotPath.scaleFactor;
                y: dayPathView.height / 2; }
            PathAttribute { name: "transparency"; value: 1.0 }

            PathLine {
                x: dayPathView.width * 2 * dayPivotPath.scaleFactor;
                y: dayPathView.height / 2; }
            PathAttribute { name: "transparency"; value: 0.3 }

            // Stop
            PathLine {
                x: dayPathView.width + container.headerItemWidth * 1.2;
                y: dayPathView.height / 2; }
            PathAttribute { name: "transparency"; value: 0.0 }
        }

        Component {
            id: dayPivotHeaderDelegate

            Item {
                id: dayDelegateItem

                height: parent.height
                width: container.headerItemWidth

                Text {
                    color: dayDelegateItem.PathView.isCurrentItem ?
                               container.selectedHeaderTextColor
                             : container.headerTextColor
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    text: dayName

                    font {
                        pixelSize: container.headerTextSize                        
                        weight: Font.Bold
                    }

                    Behavior on color {
                        ColorAnimation {
                            duration: 500;
                        }
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (dayPathView.currentIndex != index) {
                            console.log("Focusing on " + dayName +
                                        ". Clicked index was: " + index)
                            container.currentIndex = index;
                        }
                    }
                }
            }
        }
    }

    // Bottom border line
    Rectangle {
        width: parent.width
        height: 2
        anchors.bottom: parent.bottom
        color: container.borderColor
    }

}
