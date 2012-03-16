import QtQuick 1.0
import com.nokia.symbian 1.1
import "Core" 1.1 as Core

Item{

    property alias model: pathOperations.model
    state: "normal"
    width: 250
    height: width
    z:2

    states: [
        State {
            name: "overlayed"
            PropertyChanges { target: overlay; enabled: true; opacity:1 }
        },
        State {
            name: "normal"
            PropertyChanges { target: overlay; enabled: false; opacity:0 }
        }
    ]

    transitions: [
        Transition {
               from: "normal"; to: "overlayed"
               PropertyAnimation { target: overlay
                                   properties: "opacity"; duration: 1000; easing.type: Easing.OutQuad }
           },
           Transition {
               from: "overlayed"; to: "normal"
               PropertyAnimation { target: overlay
                                   properties: "opacity"; duration: 1000; easing.type: Easing.OutQuad }
           }
    ]

    Item {
         id: overlay

         enabled: false
         opacity: 0
         width: parent.width
         height: width
         /*color: "transparent"
         border.color: "black"
         border.width: 1
         radius: width
         */

         Image {
             id: realImage;
             source: "images/overlay_meego.png";
             width:parent.width-100
             height:parent.height-100
             anchors.horizontalCenter: parent.horizontalCenter
             anchors.verticalCenter: parent.verticalCenter
         }




         PathView {
             id: pathOperations
             property int itemPerArc: 2
             anchors.horizontalCenter: parent.horizontalCenter
             anchors.verticalCenter: parent.verticalCenter
             width: parent.width
             height: parent.height
             model: 0

             //offset:1
             delegate:
                 Image {
                     source: "images/operation_meego.png";
                     width:50; height:50;

                     Image {
                         id: realOperationImage;
                         source: "images/"+o_name+".png";
                         width:40; height:40;
                          anchors.fill: parent
                         anchors {
                             horizontalCenter: parent.horizontalCenter
                             verticalCenter: parent.verticalCenter
                         }
                     }

                 }

             path: Core.EllipsePath {
                     id: ellipsePath
                     width: 250
                     height: 250
                 }

             onCountChanged: {
                 console.log("changed item of day layer to "+count);

                 var maxArc = Math.ceil(count / pathOperations.itemPerArc);

                 ellipsePath.tlq = 1*1/maxArc;
                 if(ellipsePath.tlq>1) ellipsePath.tlq = 0

                 ellipsePath.trq = 1*2/maxArc;
                 if(ellipsePath.trq>1) ellipsePath.trq = 0

                 ellipsePath.brq = 1*3/maxArc;
                 if(ellipsePath.brq>1) ellipsePath.brq = 0

                 ellipsePath.blq = 1*4/maxArc;
                 if(ellipsePath.blq>1) ellipsePath.blq = 0

                 console.log(ellipsePath.tlq+" "+ellipsePath.trq+" "+ellipsePath.brq+" "+ellipsePath.blq+" ");

             }

         }

         /*Rectangle {
             width: bonsaiLayer.cellWidth; height: bonsaiLayer.cellHeight
             color: "lightsteelblue"; radius: 5
             x: bonsaiLayer.currentItem.x
             y: bonsaiLayer.currentItem.y
             Behavior on x { SpringAnimation { spring: 3; damping: 0.2 } }
             Behavior on y { SpringAnimation { spring: 3; damping: 0.2 } }
         }*/
     }

    ListView {
        id: priority
        //anchors.horizontalCenter: parent.horizontalCenter
        //anchors.verticalCenter: parent.verticalCenter
        width: 30
        height: 30
        model: 1
        x: parent.width/2+15
        y: parent.height/2+15
        //offset:1

        delegate:
            Image {
                source: "images/operation_meego.png";
                width:30; height:30;

            }

    }
}
// Flickable element is used for emulating left/right swiping page switch.
/*Flickable {
    id: container

    // Model *MUST BE* set from outside!
    property variant model: null
    property int itemHeight: visual.itemHeight
    property int marginTop: 40
    property int marginLeft: 40
    property color borderColor: "#C4AE94"
    property color textColor: "#6A5147"

    // Current index from the HourColumn. This will be used to position the
    // weekDay list component correctly, when it has fully loaded.
    property int bonsaiIndex: 0

    //signal contentYChanged(int y)
    property alias contentY: weekDay.contentY
    property int hackFixListOffset: 0

    // Attribute & signals to help with emulating 'swipe' behaviour.
    property int flickMargin: 25
    signal flickedRight()
    signal flickedLeft()
    // For signalling parent when the ListView's index is changed.
    signal indexChanged(int index);
    // Method for activating keyboard focus for the ListView.
    function forceKeyboardFocus() {
//        weekDay.forceActiveFocus();
    }

    // Private properties, not to be set from outside.
    property bool __cleanupAfterTransition: false
    property int __transitionDuration: 200
    property bool __pageAlreadyFlicked: false
    property int __startingBonsaiIndex: 0

    // Internal property definitions.
    width: parent ? parent.width : 0
    height: parent ? parent.height : 0
    contentWidth: parent.width
    flickableDirection: Flickable.HorizontalAndVerticalFlick

    // Use the x-axis to determine, if the user has 'flicked' far enough to
    // trigger the page change. This emulates the swipe gesture.
    onContentXChanged: {
        if (!__pageAlreadyFlicked && contentX >= container.flickMargin) {
            __pageAlreadyFlicked = true;
            container.flickedLeft();
        } else if (!__pageAlreadyFlicked && contentX <= -container.flickMargin) {
            __pageAlreadyFlicked = true;
            container.flickedRight();
        }
    }

    // This ListView Element is the beef of the PivotPage, it contains the
    // day event data in a list.
    ListView {
        id: weekDay

        anchors.fill: parent
        anchors.bottomMargin: 30
        model: container.model
        snapMode: ListView.SnapToItem
        interactive: true
        anchors.topMargin: container.marginTop
        anchors.leftMargin: visual.bonsaiNameMarginLeft
        //contentHeight: container.itemHeight * container.model.count
        cacheBuffer: 1920
        //flickableDirection: Flickable.HorizontalFlick

        delegate:  Operation {
            model: container.model
            //itemHeight: container.itemHeight
            width: container.width
            height: container.itemHeight
            textColor: container.textColor
            borderColor: container.borderColor
        }


        onCountChanged: {
            // When the component is FINALLY loaded, set the list to correct position.
            var idx = container.__startingBonsaiIndex;

            /*weekDay.positionViewAtIndex(container.__startingBonsaiIndex,
                                        ListView.Beginning);
            currentIndex = container.__startingBonsaiIndex;

            // ALARM! Here's an ugly hack fix for the issue with long events not
            // focusing the lists (weekDay & hourColumn) correctly. The root cause
            // is unknown, but this has something to do with the ListView's
            // contentHeight being calculated incorrectly, if there's delegates of
            // different sizes...
            //
            // TODO HACK FIX WARNING ALARM
            //
            if (contentY != container.itemHeight*currentIndex) {
                // Don't set the hack fix offset if it's negative
                var offset = contentY - container.itemHeight*currentIndex;
                if (offset > 0) {
                    container.hackFixListOffset = weekDay.atYEnd
                            ? (visual.isE6 ? offset+1 : offset+8)
                            : offset
                    console.log("ALARM! ALARM! Setting hack fix offset: "
                                + container.hackFixListOffset);
                }
                console.log("Offset was: " + offset);
            }
        }

        Component.onCompleted: {

            //console.log("PIVOTPAGE index: "+ container.bonsaiIndex+ ", count: "+weekDay.model.count);

            // TODO: As the PivotPage is being created dynamically, the ListView
            // isn't really complete when Component.onCompleted is called, but it's
            // still waiting for the model to load.
            //
            // Thus, we have a sort of 'hack fix' here in order to center the ListView
            // to the correct index AFTER the model has fully loaded, i.e. when the
            // ListView.count attribut changes (resulting in onCountChanged).
            __startingBonsaiIndex = container.bonsaiIndex;
//            weekDay.forceActiveFocus();
        }


        onFlickEnded: {
            console.log("PivotPage flick ended");
        }

        onCurrentIndexChanged: {
            container.indexChanged(currentIndex);
        }

        // Notify the changed value.
        onContentYChanged: container.contentYChanged(weekDay.contentY)

        // ScrollBar indicator.
        // Take the bottommost search field height into account.
        ScrollDecorator {
            anchors {
                right: parent.right
                top: parent.top
                bottom: parent.bottom
            }
            // flickableItem binds the scroll decorator to the ListView.
            flickableItem: weekDay
        }

        // Key navigation handling.
        // NOTE! Key navigation is currently disabled, as it doesn't fully work
        // with hackFix(ListOffset), but causes the lists (weekDay & hourColumn)
        // to go out of sync.
//        Keys.onPressed: {

//            switch (event.key) {
//                case Qt.Key_Select:
//                case Qt.Key_Enter:
//                case Qt.Key_Return: {
//                    console.log("ENTER Pressed!")
//                    event.accepted = true
//                    break
//                }

//                case Qt.Key_Up: {
//                    if (symbian.listInteractionMode != Symbian.KeyNavigation) {
//                        symbian.listInteractionMode = Symbian.KeyNavigation;
//                        weekDay.positionViewAtIndex(currentIndex, ListView.Beginning);
//                        console.log("!KeyNavigation UP Pressed");
//                    } else {
//                        var parentIdx = model.itemsParent(currentIndex-1);
//                        if (parentIdx != -1) {
//                            console.log("Parent index not -1! Positioning view @ index:"
//                                        + parentIdx);
//                            weekDay.positionViewAtIndex(parentIdx, ListView.Beginning);
//                            currentIndex = parentIdx;
//                        } else {
//                            weekDay.decrementCurrentIndex();
//                        }
//                        console.log("UP Pressed");
//                    }
//                    event.accepted = true;
//                    break;
//                }

//                case Qt.Key_Down: {
//                    if (symbian.listInteractionMode != Symbian.KeyNavigation) {
//                        symbian.listInteractionMode = Symbian.KeyNavigation;
//                        weekDay.positionViewAtIndex(currentIndex, ListView.Beginning);
//                        console.log("!KeyNavigation DOWN Pressed");
//                    } else {
//                        var span = model.hourSpan(currentIndex);
//                        console.log("HourSpan for current index: " + span);
//                        if (span > 1) {
//                            console.log("Span bigger than 1! Position view @ index: "
//                                        + (currentIndex + span));
//                            weekDay.positionViewAtIndex(currentIndex+span,
//                                                        ListView.Beginning);
//                            currentIndex += span;
//                        } else {
//                            weekDay.incrementCurrentIndex();
//                        }
//                        console.log("DOWN Pressed")
//                    }
//                    event.accepted = true;
//                    break;
//                }

//                case Qt.Key_Left: {
//                    console.log("LEFT Key clicked. CHANGE PAGE!");
//                    __pageAlreadyFlicked = true;
//                    container.flickedRight();
//                    event.accepted = true;
//                    break;
//                }

//                case Qt.Key_Right: {
//                    console.log("RIGHT Key clicked. CHANGE PAGE!");
//                    __pageAlreadyFlicked = true;
//                    container.flickedLeft();
//                    event.accepted = true;
//                    break;
//                }

//                default: {
//                    console.log("Default. Not accepted.")
//                    event.accepted = false
//                    break
//                }
//            }
//        }
    }


    // These functions, states & transitions have been borrowed from the Qt
    // Quick Component's PageStack, in order to imitate similar kind of
    // 'PageStack' transitions when changing the PivotPages back and forth.

    // Performs a push enter transition.
    function pushEnter(immediate) {
        if (!immediate) {
            container.state = "Right";
        }
        container.state = "";
        container.visible = true;
    }

    // Performs a push exit transition.
    function pushExit(immediate) {
        container.state = immediate ? "Hidden" : "Left";
        if (immediate)
            __cleanup();
        else
            container.__cleanupAfterTransition = true;
    }

    // Performs a pop enter transition.
    function popEnter(immediate) {
        if (!immediate)
            container.state = "Left";
        container.state = "";
        container.visible = true;
    }

    // Performs a pop exit transition.
    function popExit(immediate) {
        container.state = immediate ? "Hidden" : "Right";
        if (immediate)
            __cleanup();
        else
            container.__cleanupAfterTransition = true;
    }

    // Called when a transition has started.
    function transitionStarted() {
        // A placeholder, if some initializing should be done.
    }

    // Called when a transition has ended.
    function transitionEnded() {
        if (container.state != "")
            container.state = "Hidden";
        if (container.__cleanupAfterTransition)
            __cleanup();
    }

    // Cleans up the container and then destroys it.
    function __cleanup() {
        console.log("DESTROYING PivotPage");
        container.destroy();
    }

    states: [
        // Explicit properties for default state.
        State {
            name: ""
            PropertyChanges { target: container; visible: true; opacity: 1 }
        },
        // Start state for pop entry, end state for push exit.
        State {
            name: "Left"
            PropertyChanges { target: container; x: -width / 2; opacity: 0 }
        },
        // Start state for push entry, end state for pop exit.
        State {
            name: "Right"
            PropertyChanges { target: container; x: width / 2; opacity: 0 }
        },
        // Inactive state.
        State {
            name: "Hidden"
            PropertyChanges { target: container; visible: false }
        }
    ]

    transitions: [
        // Push exit transition
        Transition {
            from: ""; to: "Left"
            SequentialAnimation {
                ScriptAction { script: transitionStarted() }
                ParallelAnimation {
                    PropertyAnimation {
                        properties: "x"
                        easing.type: Easing.InQuad
                        duration: __transitionDuration
                    }
                    PropertyAnimation {
                        properties: "opacity"
                        easing.type: Easing.Linear
                        duration: __transitionDuration
                    }
                }
                ScriptAction { script: transitionEnded() }
            }
        },
        // Pop entry transition
        Transition {
            from: "Left"; to: ""
            SequentialAnimation {
                ScriptAction { script: transitionStarted() }
                ParallelAnimation {
                    PropertyAnimation {
                        properties: "x"
                        easing.type: Easing.OutQuad
                        duration: __transitionDuration
                    }
                    PropertyAnimation {
                        properties: "opacity"
                        easing.type: Easing.Linear
                        duration: __transitionDuration
                    }
                }
                ScriptAction { script: transitionEnded() }
            }
        },
        // Pop exit transition
        Transition {
            from: ""; to: "Right"
            SequentialAnimation {
                ScriptAction { script: transitionStarted() }
                ParallelAnimation {
                    PropertyAnimation {
                        properties: "x"
                        easing.type: Easing.InQuad
                        duration: __transitionDuration
                    }
                    PropertyAnimation {
                        properties: "opacity"
                        easing.type: Easing.Linear
                        duration: __transitionDuration
                    }
                }
                // Workaround for transition animation bug causing
                // ghost view with page pop transition animation.
                // TODO: Root cause still unknown
                PropertyAnimation {}
                ScriptAction { script: transitionEnded() }
            }
        },
        // Push entry transition
        Transition {
            from: "Right"; to: ""
            SequentialAnimation {
                ScriptAction { script: transitionStarted() }
                ParallelAnimation {
                    PropertyAnimation {
                        properties: "x"
                        easing.type: Easing.OutQuad
                        duration: __transitionDuration
                    }
                    PropertyAnimation {
                        properties: "opacity"
                        easing.type: Easing.Linear
                        duration: __transitionDuration
                    }
                }
                ScriptAction { script: transitionEnded() }
            }
        }
    ]

}*/
