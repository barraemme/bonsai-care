import QtQuick 1.0
import "Core" 1.1 as Core
import "resources/script.js" as Script

Rectangle {
    id: window;

    // Platform differentitation for visual style & theming.
    Visual {
        id: visual

        // Bind the landscape layout property in order to get the correct
        // margin values etc. for the different layouts
        inLandscape: view.inPortrait

        // Check, whether or not the device is E6
        isE6: window.height == 480
    }

    function orientationChanged(orientation) {

            if(orientation == 1) {
                view.state = "Portrait"
                //view.rotation = 0
                //view.width = window.width; view.height = window.height
            }
            else if(orientation == 2) {
                view.state = "PortraitInverted"
               // view.rotation = 180
                //view.width = window.width; view.height = window.height
            }
            else if(orientation == 3) {
                view.state = "LandscapeInverted"
               //view.rotation = 270
                //view.width = window.height; view.height = window.width
            }
            else if(orientation == 4) {
                view.state = "Landscape"
                //view.rotation = 90
                //view.width = window.height; view.height = window.width
            }
        }


    Rectangle {
        id: view
        state:  "Landscape"
        property bool inPortrait: (state == "Portrait" || state == "PortraitInverted");
        Behavior on rotation { RotationAnimation { direction: RotationAnimation.Shortest; duration: 500; easing.type: Easing.OutBounce } }
        Behavior on width    { NumberAnimation   { duration: 500 } }
        Behavior on height   { NumberAnimation   { duration: 500 } }
        property int angle: 0;
        anchors.centerIn: parent
        width: window.width; height: window.height

        Loader{
            id:loader
            source: "Pivot.qml"
            width: view.width;
            height: view.height
            anchors.fill: parent

        }

        /*Connections {
            target: loader.item
            onChangeApp: Script.switchApp(app)
         }*/
    // Background image for the Pages
    /*Image {
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
    }*/

    states: [
        State {
              name: "Landscape"
              PropertyChanges {
                target: view
                /*rotation: 90
                angle: 90
                width: window.height
                height: window.width*/
              }
            },
            State {
              name: "LandscapeInverted"
              PropertyChanges {
                target: view
                /*rotation: 270
                angle: 270
                width: window.height
                height: window.width*/
              }
            },
            State {
              name: "Portrait"
              PropertyChanges {
                target: view
                /*rotation: 0
                angle: 0
                width: window.width
                height: window.height*/
              }
            },
            State {
              name: "PortraitInverted"
              PropertyChanges {
                target: view
                /*rotation: 180
                angle: 180
                width: window.width
                height: window.height*/
              }
        }
    ]

    transitions: [
        Transition {
            from: "*"
            to: "*"

            ParallelAnimation {
              RotationAnimation {
                properties: "rotation"
                duration: 250
                direction: RotationAnimation.Shortest
              }
              PropertyAnimation {
                target: window
                properties: "x,y,width,height"
                duration: 250
              }
            }
          }
    ]
}

}
