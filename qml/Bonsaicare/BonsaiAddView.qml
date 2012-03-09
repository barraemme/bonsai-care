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
    anchors.fill: parent

    // Use 2x1 or 1x2 type of grid for layouting the starttime & endtime
    // selectors a bit differently when in landscape mode. i.e. side by side.
    Grid {
        id: selectionItemGrid

        property int cellWidth: parent.width/2
        rows: 2
        columns: 2
        anchors.fill: parent

        Text {
            text: qsTr("Specie")
            font.pixelSize: container.textAreaTextSize
            color: container.textColor
            width: selectionItemGrid.cellWidth           
        }

        SelectionListItem {
            id: specieTextSelection

            width: selectionItemGrid.cellWidth
            title: qsTr(container.itemName)
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
        }

        TextField {
            width: selectionItemGrid.cellWidth
            text: ""
            onTextChanged: container.itemYear = text
        }

    }

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
                    // Do the model saving related things & pop exit.
                    __doSave();
                    pageStack.pop();
                }
            }

     }

}

