import QtQuick 1.1
import com.nokia.symbian 1.1

import "Core" 1.1 as Core

Page {
    id: container

    property variant model: species
    property variant bonsaiModel: bonsai
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
    property string itemSpecie: ""
    property string itemName: "Specie"
    property string itemYear: ""


    // This is being signalled when the user has selected some other day than
    // the one from which he came. Based on the signal the Pivot can then
    // change the view to show the right day to which the event was saved.

    // Private stuff
    function __doSave() {
        // Then create a new entry.
        container.bonsaiModel.insert(itemSpecie, parseInt(itemYear,10));
        //TODO display a message
    }

    // Page attribute definitions.
    onLandscapeLayoutChanged: console.log("Changed landscapelayout: "
                                          + landscapeLayout)
    anchors.fill: parent

    // Use 2x1 or 1x2 type of grid for layouting the starttime & endtime
    // selectors a bit differently when in landscape mode. i.e. side by side.
    Grid {
        id: selectionItemGrid

        property int cellWidth: parent.width/2

        rows: 2
        columns: 2

        /*anchors {
            left: parent.left
            leftMargin: container.selectionItemLeftMargin
            right: parent.right
            top: titleTextSelection.bottom
            topMargin: container.listItemTopMargin
            bottom: parent.bottom
        }*/
        anchors.fill: parent

        Text {
            text: qsTr("Specie")
            font.pixelSize: container.textAreaTextSize
            color: container.textColor
            width: selectionItemGrid.cellWidth
            /*anchors.left: parent.left
            anchors.leftMargin: container.titleMargins*/
        }

        SelectionListItem {
            id: specieTextSelection

            width: selectionItemGrid.cellWidth

            title: qsTr(container.itemName)
            //subTitle: container.itemSpecie
            onClicked: speciesDialog.open()

            SelectionDialog {
                id: speciesDialog
                titleText: qsTr("Select bonsai specie")
                selectedIndex: -1
                model: container.model
                width: selectionItemGrid.cellWidth
                onAccepted: {                   
                    console.log(selectedIndex);
                    container.itemSpecie = selectedIndex;
                    container.itemName = speciesDialog.model.getNameById(selectedIndex);
                }
            }
        }

        Text {
            text: qsTr("Year")
            font.pixelSize: container.textAreaTextSize
            color: container.textColor
            width: selectionItemGrid.cellWidth
            /*anchors.left: parent.left
            anchors.leftMargin: container.titleMargins*/
        }

        TextField {
            width: selectionItemGrid.cellWidth
            text: ""
            onTextChanged: container.itemYear = text
        }

    }
    /*Rectangle {
        height: 1
        visible: !visual.isE6
        width: parent.width
        anchors.bottom: parent.bottom
        color: container.separatorColor
    }*/

   /* ListView {
        id: addView
        model: species
        delegate: Core.AddDelegate{}
        anchors.fill: parent
        //cellWidth: (parent.width-2)/3
        //cellHeight: (parent.width-2)/3
        //currentIndex: -1
        cacheBuffer: 100
        /*onCurrentIndexChanged: {
            console.log(addView.currentIndex);
            var item = db.get(addView.currentIndex);
            modelData.setModelData(itemModel,-1,-1,0,item);
        }*/

        // ScrollBar indicator.
        // Take the bottommost search field height into account.
       /* ScrollDecorator {
            anchors {
                right: parent.right
                top: parent.top
                bottom: parent.bottom
            }
            // flickableItem binds the scroll decorator to the ListView.
            flickableItem: addView
        }*/
   /* }*/





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
                    eventDetailsView.endHourIndex = container.selectedDayIndex + hourSpan;*/
                    // Do the model saving related things & pop exit.
                    __doSave();
                    pageStack.pop();
                }
            }

        }

}

