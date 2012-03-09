import QtQuick 1.1
import com.nokia.symbian 1.1
//import com.nokia.meego 1.0
import "Core" 1.1 as Core
import "resources/script.js" as Script

Window {
    id: mainWindow;

    property bool landscapeLayout: !mainWindow.inPortrait

    state: "start"
    
    // Background image for the Pages
    Image {
        id: bgImg
        anchors {
            top: statusBar.bottom
            bottom: toolBar.top
            left: parent.left
            right: parent.right
        }
        source: landscapeLayout ?
                    (visual.isE6 ? "Core/images/diary_640x480.png"
                                 : "Core/images/diary_640x360.png")
                  : "Core/images/diary_360x640.png"
    }

    // Platform differentitation for visual style & theming.
    Visual {
        id: visual

        // Bind the landscape layout property in order to get the correct
        // margin values etc. for the different layouts
        inLandscape: mainWindow.landscapeLayout

        // Check, whether or not the device is E6
        isE6: mainWindow.height == 480
    }

    /*ListModel {
        id: titles
                ListElement {
                    title: "New Bonsai"
                }

                ListElement {
                    title: "Edit Bonsai"
                }
            }*/

    // Application uses the statusbar, for balancing the view look and feel
    // as it also uses the toolbar.
    StatusBar {
        id: statusBar
        anchors.top: parent.top
    }

    PageStack {
        id: pageStack
        toolBar: toolBar

        anchors {
            top: statusBar.bottom
            bottom: toolBar.top
            left: parent.left
            right: parent.right
        }

        onCurrentPageChanged: {
            // Force the keyboard focus always on the PivotPage.
            // (coz e.g. EventEditView's text input might have changed it).
            /*if (pageStack.currentPage == mainPivot) {
                mainPivot.currentPage.forceKeyboardFocus();
            }*/
        }

        // Uses the Pivot component for showing/navigating through content.
        Pivot {
            id: mainPivot
            anchors.fill: parent

            // Default ToolBarLayout, shown when the main Pivot view is visible.
            tools: ToolBarLayout {
                // Button for exiting the application.
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
                    iconSource: "toolbar-add"
                    onClicked: {
                        pageStack.push(Qt.resolvedUrl("BonsaiAddView.qml"));
                    }
                }                
            }
        }
    }

    // ToolBar. Used for exiting the app & adding new event etc.
    ToolBar {
        id: toolBar
        anchors.bottom: parent.bottom
        tools: defaultTools
    }

    states: [
        State {
            name: "start"
            PropertyChanges { target: mainWindow; x: width / 2; opacity: 0 }
        },
        State {
            name: "end"
            PropertyChanges { target: mainWindow; x: 0; opacity: 1 }
        }
    ]

    transitions: [
        Transition {
            from: "start"; to: "end"
            ParallelAnimation {
                PropertyAnimation {
                    properties: "x"
                    easing.type: Easing.OutQuad
                    duration: 300
                }
                PropertyAnimation {
                    properties: "opacity"
                    easing.type: Easing.Linear
                    duration: 300
                }
            }
        }
    ]


    Component.onCompleted: {
        pageStack.push(mainPivot);
        mainWindow.state = "end";
    }

}
