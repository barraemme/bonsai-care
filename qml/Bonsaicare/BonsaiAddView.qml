import QtQuick 1.0
import com.nokia.symbian 1.1
import "Core" 1.1 as Core

Page {
    id: container

    property variant model: bonsaiItem
    property variant titleModel;
    property bool landscapeLayout: mainWindow.landscapeLayout

    property int headerHeight: visual.headerHeight
    property int headerTextSize: visual.headerTextSize

    // Properties
    property int titleMargins: visual.editTitleMargins
    property int generalLeftMargin: visual.generalLeftMargin
    property int selectionItemLeftMargin: visual.selectionItemLeftMargin
    property int generalTopMargin: visual.generalTopMargin
    property int generalRightMargin: visual.selectionItemRightMargin
    property int listItemTopMargin: visual.editItemTopMargin
    property int editTopMargin: visual.editTopMargin
    property int headingFontSize: visual.generalFontSize
    property int textAreaTextSize: visual.detailsFontSize
    property color separatorColor: visual.editSeparatorColor
    property color textColor: "#6A5147"
    property color headerTextColor: "#BE5215"
    // These will be changed dynamically based on the selected Cell item.
    property string eventTitle: ""

    // This is being signalled when the user has selected some other day than
    // the one from which he came. Based on the signal the Pivot can then
    // change the view to show the right day to which the event was saved.

    // Private stuff
    /*function __doSave() {
        console.log("Spanning the hour: " + container.eventStart + " of day "
                    + eventDay + " for "
                    + (container.endHourIndex-container.startHourIndex)
                    + " hours.");
        if (originalStartHourIndex >= 0) {
            // originalStartHourIndex will be set only when coming navigated from
            // eventDetailsView

            var origDay = container.model.day(container.originalDayIndex).items();
            // First delete the previous entry
            // Split, just to make sure the cell is really in default state.
            origDay.split(container.originalStartHourIndex);
            // Empty string will get rid of the item
            origDay.setItemData(container.originalStartHourIndex, "");

            // originalStartHourIndex must be unset because eventDetailsView
            // will set this when actually needed again
            originalStartHourIndex = -1;
        }

        // Then create a new entry.
        var dayModel = container.model.day(container.selectedDayIndex).items();
        // Next save the new Set the text content for the event item.
        dayModel.setItemData(container.startHourIndex, contentText.text);
        // Then start merging the cells.
        for (var i = 1; i < container.endHourIndex-container.startHourIndex; i++) {
            dayModel.mergeDown(container.startHourIndex);
        }

        if (container.selectedDayIndex != container.originalDayIndex) {
            eventDayChanged(container.selectedDayIndex);
        }
    }*/

    Core.AddDelegate{ id: addDelegate }

    Component {
        id: pivotPageComp

        Item {
            id: addViewBox

            //height: visual.isE6 ? titleTextSelection.height-20
             //                   : titleTextSelection.height
            width: parent.width
            anchors {
                top: bonsaiAddTitle.bottom
                topMargin: container.editTopMargin
                left: parent.left
                leftMargin: container.selectionItemLeftMargin
                right: parent.right
            }

            Rectangle {
                height: 1
                visible: !visual.isE6
                width: parent.width
                anchors.bottom: parent.bottom
                color: container.separatorColor
            }

            ListView {
                id: addView
                model: parent.model
                delegate: addDelegate
                anchors.fill: parent
                //cellWidth: (parent.width-2)/3
                //cellHeight: (parent.width-2)/3
                currentIndex: -1
                cacheBuffer: 100
                onCurrentIndexChanged: {
                    /*console.log(addView.currentIndex);
                    var item = db.get(addView.currentIndex);
                    modelData.setModelData(itemModel,-1,-1,0,item);*/
                }
            }
        }

        /*PivotPage {
            id: pivotPage

            flickMargin: visual.flickMargin
            itemHeight: container.itemHeight
            borderColor: container.borderColor
            textColor: container.headerTextColor
            //hourIndex: bonsaiColumn.hourIndex

            onFlickedLeft: {
                var idxx = 0;
                if (container.currentPageIndex == 6) {
                    console.log("Switching to page: 0 (FORCED)");
                    idxx = 0;
                } else {
                    idxx = container.currentPageIndex + 1;
                    console.log("Switching to page: " + idxx);
                }
                // Switch the page by setting the header to correct index too.
                container.headerPageIndex = idxx;
            }

            onFlickedRight: {
                var idxx = 0;
                if (container.currentPageIndex == 0) {
                    console.log("Switching to page: 6 (FORCED)");
                    idxx = 6;
                } else {
                    idxx = container.currentPageIndex - 1;
                    console.log("Switching to page: " + idxx);
                }
                container.headerPageIndex = idxx;
            }
        }*/
    }

    // Pivot headers, used for navigation.
    TitleHeader {
        id: headerRow

        model: container.titleModel

        height: parent.headerHeight
        width: parent.width
        headerItemWidth: parent.headerItemWidth
        // Set the background image
        borderColor: container.borderColor
        headerTextColor: container.headerTextColor
        headerTextSize: container.headerTextSize
        landscapeLayout: landscapeLayout
        generalLeftMargin: container.generalLeftMargin
        // If the header should work both ways and by flicking,
        // set this property to true.
        flickable: true

        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
        }

        onIndexChanged: {
            console.log("BEFORE PAGECHANGE, container.currentPage: "
                        + container.currentPage);
            __switchPage(index, true);
            console.log("AFTER PAGECHANGE, container.currentPage: "
                        + container.currentPage);
        }
    }

    Item {
        id: contentArea

        clip: true
        anchors {
            top: headerRow.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
    }

    // Initialize the first Day item.
    Component.onCompleted: {
        //__initializePage(0);
        //container.currentPageIndex = 0;
    }



    // This item groups the bottomline, text title & textfield as one Element.


    // This item groups the bottomline, text title & textfield as one Element.
    /*Item {
        id: inputTitle

        height: visual.isE6 ? titleTextSelection.height-20
                            : titleTextSelection.height
        width: parent.width
        anchors {
            top: bonsaiAddTitle.bottom
            topMargin: container.editTopMargin
            left: parent.left
            leftMargin: container.selectionItemLeftMargin
            right: parent.right
        }

        Rectangle {
            height: 1
            visible: !visual.isE6
            width: parent.width
            anchors.bottom: parent.bottom
            color: container.separatorColor
        }

        Text {
            id: contentTextTitle

            text: qsTr("Title")
            font.pixelSize: container.textAreaTextSize
            color: container.textColor
            anchors.left: parent.left
            anchors.leftMargin: container.titleMargins
        }

        TextField {
            id: contentText

            width: parent.width - 2*container.titleMargins
            text: container.eventTitle

            onTextChanged: container.eventTitle = text
            anchors {
                top: contentTextTitle.bottom
                left: parent.left
                leftMargin: container.titleMargins
            }
        }
    }

    SelectionListItem {
        id: titleTextSelection

        title: qsTr("Day")
        subTitle: container.eventDay
        anchors {
            top: inputTitle.bottom
            topMargin: container.listItemTopMargin
            left: parent.left
            leftMargin: container.selectionItemLeftMargin
            right: parent.right
        }

        onClicked: dayDialog.open()

        SelectionDialog {
            id: dayDialog
            titleText: qsTr("Day")
            selectedIndex: 0
            model: ListModel {
                // A ListModel for the star ratings.
                ListElement { name: "Monday" }
                ListElement { name: "Tuesday" }
                ListElement { name: "Wednesday" }
                ListElement { name: "Thursday" }
                ListElement { name: "Friday" }
                ListElement { name: "Saturday" }
                ListElement { name: "Sunday" }
            }
            onAccepted: {
                container.selectedDayIndex = selectedIndex;
                container.eventDay = dayDialog.model.get(selectedIndex).name;
            }
        }
    }

    // Use 2x1 or 1x2 type of grid for layouting the starttime & endtime
    // selectors a bit differently when in landscape mode. i.e. side by side.
    Grid {
        id: selectionItemGrid

        property int cellWidth: container.landscapeLayout ? width/2 : width

        rows: container.landscapeLayout ? 1 : 2
        columns: container.landscapeLayout ? 2 : 1
        anchors {
            left: parent.left
            leftMargin: container.selectionItemLeftMargin
            right: parent.right
            top: titleTextSelection.bottom
            topMargin: container.listItemTopMargin
            bottom: parent.bottom
        }

        SelectionListItem {
            id: startTimeSelection

            width: selectionItemGrid.cellWidth
            title: qsTr("Starts at")
            subTitle: container.eventStart

            onClicked: {
                hourDialog.currentItem = startTimeSelection;
                hourDialog.titleText = qsTr("Select event start time")
                hourDialog.open();
            }

            onSubTitleChanged: {
                // Check that the end time isn't before the start time!
                if(startTimeSelection.subTitle > endTimeSelection.subTitle) {
                    container.eventEnd = startTimeSelection.subTitle;
                    container.endHourIndex = container.startHourIndex;
                }
            }
        }

        SelectionListItem {
            id: endTimeSelection

            width: selectionItemGrid.cellWidth
            title: qsTr("Ends at")
            subTitle: container.eventEnd

            onClicked: {
                hourDialog.currentItem = endTimeSelection;
                hourDialog.titleText = qsTr("Select event end time")
                hourDialog.open();
            }

            onSubTitleChanged: {
                // Check that the end time isn't before the start time!
                if(startTimeSelection.subTitle > endTimeSelection.subTitle) {
                    container.eventStart = endTimeSelection.subTitle;
                    container.startHourIndex = container.endHourIndex;
                }
            }
        }

        SelectionDialog {
            id: hourDialog

            property variant currentItem

            titleText: qsTr("")
            selectedIndex: -1
            model: HourModel {}
            onAccepted: {
                if (currentItem == startTimeSelection) {
                    container.startHourIndex = selectedIndex;
                    container.eventStart = model.get(selectedIndex).name;
                } else {
                    container.endHourIndex = selectedIndex;
                    container.eventEnd = model.get(selectedIndex).name;
                }
            }
        }
    }*/
    // A ToolBarLayout for event editing view.
        tools: ToolBarLayout {
            ToolButton {
                iconSource: "toolbar-back"
                onClicked: {
                    if (pageStack.depth > 1) {
                        pageStack.pop();
                    } else {
                        Qt.quit();
                    }
                }
            }

            ToolButton {
                text: qsTr("Save")
                enabled: true//contentText.text.length > 0
                onClicked: {
                    // Update the Event details view info, in case we were coming
                    // from the details view itself.
                    /*eventDetailsView.selectedDayIndex = container.selectedDayIndex;
                    eventDetailsView.eventDay = container.eventDay;
                    eventDetailsView.eventTitle = container.eventTitle;
                    eventDetailsView.eventStart = container.eventStart;
                    eventDetailsView.eventEnd = container.eventEnd;
                    eventDetailsView.startHourIndex = container.startHourIndex;
                    eventDetailsView.endHourIndex = container.selectedDayIndex + hourSpan;
                    // Do the model saving related things & pop exit.
                    __doSave();
                    pageStack.pop();*/
                }
            }

        }

}

