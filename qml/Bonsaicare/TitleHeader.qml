import QtQuick 1.0

// Title headers
Item {
    id: container

    property alias model: pathView.model;
    // How wide the header is. Should be differentiated between portrait
    // and landscape modes.
    property int headerItemWidth: 182
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
        text: qsTr("Bonsai Weekly Planner")
        color: container.headerTextColor
    }

    PathView {
        id: pathView

        Component.onCompleted: pathItemCount = parent.landscapeLayout ? 4 : 3

        width: parent.width
        anchors {
            top: appTitle.bottom
            bottom: parent.bottom
            left: parent.left
        }

        delegate: titleHeaderDelegate

        interactive: parent.flickable
        preferredHighlightBegin: parent.landscapeLayout ? 1/4 : 1/3
        preferredHighlightEnd: parent.landscapeLayout ? 1/4 : 1/3
        currentIndex: container.currentIndex
        onCurrentIndexChanged: {
            container.currentIndex = pathView.currentIndex;
            container.indexChanged(pathView.currentIndex);
        }

        path: Path {
            id: titlePath
            property double scaleFactor: container.landscapeLayout ? 1/5 : 1/4

            // Start
            startX: landscapeLayout ? -(container.headerItemWidth * 0.50)
                                    : -(container.headerItemWidth * 0.65)
            startY: pathView.height / 2
            PathAttribute { name: "transparency"; value: 0.3 }

            PathLine {
                x: pathView.width * titlePath.scaleFactor;
                y: pathView.height / 2; }
            PathAttribute { name: "transparency"; value: 1.0 }

            PathLine {
                x: pathView.width * 2 * titlePath.scaleFactor;
                y: pathView.height / 2; }
            PathAttribute { name: "transparency"; value: 0.3 }

            // Stop
            PathLine {
                x: pathView.width + container.headerItemWidth * 1.2;
                y: pathView.height / 2; }
            PathAttribute { name: "transparency"; value: 0.0 }
        }

        Component {
            id: titleHeaderDelegate

            Item {
                id: delegateItem
                height: parent.height
                width: container.headerItemWidth

                Text {
                    color: /*delegateItem.PathView.isCurrentItem ?*/
                               container.selectedHeaderTextColor
                            /* : container.headerTextColor*/
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    text: title

                    font {
                        pixelSize: container.headerTextSize
                        bold: true
                    }

                    /*Behavior on color {
                        ColorAnimation {
                            duration: 500;
                        }
                    }*/
                }

                /*MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (pathView.currentIndex != index) {
                            console.log("Focusing on " + dayName +
                                        ". Clicked index was: " + index)
                            container.currentIndex = index;
                        }
                    }
                }*/
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
