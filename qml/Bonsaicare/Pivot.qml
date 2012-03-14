import QtQuick 1.0
import com.nokia.symbian 1.1
import "Core" 1.1 as Core

Page {
    id: container

    property variant model: week
    // How high the header is. Can be differentiated between portrait
    // and landscape modes.
    property int headerHeight: visual.headerHeight
    property int headerTextSize: visual.headerTextSize
    // Defines the width of one header item.
    property int headerItemWidth: landscapeLayout ? visual.landscapeHeaderItemWidth
                                                  : visual.portraitHeaderItemWidth

    // This index is used to change the day to the selected index.
    //property alias headerPageIndex: headerRow.currentIndex
    // Attributes to define the Cell item height, colors etc.
    property int itemHeight: visual.itemHeight
    //property int bonsaiColumnWidth: visual.bonsaiColumnWidth
    property int generalLeftMargin: visual.generalLeftMargin
    property color borderColor: visual.borderColor
    property color headerTextColor: visual.headerTextColor

    // Attributes for tracking the application current views (current day).
    property Item currentPage
    property int currentPageIndex: 0

    //property string currentDayName: week.dayName(currentPageIndex)

    // Internal properties, don't set from outside. This is used to
    // determine in which orientation the screen is.

    // TODO: Bind this rather to main Window's inPortrait property!
    property bool landscape: width > height

    property bool landscapeLayout: mainWindow.landscapeLayout


    // A function to determine, whether we should show left to right or
    // right to left transition animation.
    function __switchPage(pageIndex, hidden) {
        // Check first special cases (Sunday <=> Monday transitions)
        if (container.currentPageIndex === 0 && pageIndex === 6) {
            // Switching from Monday to Sunday. Use pop() type of transition.
            __popTransition(pageIndex, hidden, false);
        } else if (container.currentPageIndex === 6 && pageIndex === 0) {
            // Switching from Sunday to Monday. Use push() type of transition.
            __pushTransition(pageIndex, hidden, false);
        } else if (container.currentPageIndex < pageIndex) {
            // Moving 'forward' in the week, use push() transition.
            __pushTransition(pageIndex, hidden, false);
        } else {
            // Moving 'backwards' in the week, use pop() transition.
            __popTransition(pageIndex, hidden, false);
        }
    }

    function __pushTransition(pageIndex, hidden, immediate) {
        container.currentPage.pushExit(immediate);
        __initializePage(pageIndex, hidden);
        container.currentPage.pushEnter(immediate);
    }

    function __popTransition(pageIndex, hidden, immediate) {
        container.currentPage.popExit(immediate);
        __initializePage(pageIndex, hidden);
        container.currentPage.popEnter(immediate);
    }


    function __initializePage(pageIndex, hidden) {
        var pageComp = dayLayerComp;

        // Instantiate the component!
        if (pageComp.status == Component.Ready) {
            container.currentPage = pageComp.createObject(contentArea);
            container.currentPage.model = container.model.day(pageIndex);
            container.currentPage.state = hidden ? "Hidden" : "";
            container.currentPageIndex = pageIndex;
        }
    }    

    // Background image for the Pages
    Image {
        id: bgImg
        anchors.fill: parent
        /*anchors {
            top: statusBar.bottom
            bottom: toolBar.top
            left: parent.left
            right: parent.right
        }*/
        source: landscapeLayout ?
                    (visual.isE6 ? "Core/images/diary_640x480.png"
                                 : "Core/images/diary_640x360.png")
                  : "images/japanese_room_center_480x854.jpg"
                  //: "images/japanese_room_side_480x854.jpg"
                    //: "Core/images/diary_360x640.png"
    }


    // Pivot headers, used for navigation.
    /*PivotHeader {
        id: headerRow

        model: parent.model
        height: parent.headerHeight
        width: parent.width
        headerItemWidth: parent.headerItemWidth
        // Set the background image
        borderColor: container.borderColor
        headerTextColor: container.headerTextColor
        headerTextSize: container.headerTextSize
        landscapeLayout: landscapeLayout
        generalLeftMargin: container.generalLeftMargin
        currentIndex: container.currentPageIndex
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
    }*/

    // Show an hour column on the left side of the screen. Doesn't 'slide in/out'
    // with the rest of the content area and PivotPages.

    BonsaiLayer {
        id: bonsaiLayer

        // Set the bonsaiColumn to be quite narrow. The anchors will
        // define the bonsaiColumn's height.
        width: parent.width
        itemHeight: container.itemHeight
        model: bonsai

        anchors {
            top: headerRow.bottom
            bottom: parent.bottom
            left: parent.left
            right:parent.right
        }

        // Bind the bonsaiColumn's content Y-coordinate to the PivotPage's
        // corresponding one.
        //
        // TODO: the hackFixListOffset is being used in order to temporarily
        // fix the issues with two lists positioning incorrectly. Check the
        // PivotPage for more details.
        contentY: container.currentPage.contentY
                  - container.currentPage.hackFixListOffset
        onContentYChanged: {
            // Cannot bind back to the PivotPage's contentY, as it kills the
            // flick. Perhaps some sort of work around could be implemented?
//            container.currentPage.contentY = contentY;
//            console.log("bonsaiColumn's content y: " + contentY);
        }
    }

    //Layer with tasks
    /*Component {
        id: dayLayerComp

        DayLayer {
            id: dayLayer
            flickMargin: visual.flickMargin
            itemHeight: container.itemHeight
            borderColor: container.borderColor
            textColor: container.headerTextColor
            bonsaiIndex: bonsaiLayer.bonsaiIndex

            model: week.day(0)
            onFlickedLeft: {
                var idxx = 0;
                if (container.currentPageIndex == 6) {                    
                    idxx = 0;
                } else {
                    idxx = container.currentPageIndex + 1;
                }
                // Switch the page by setting the header to correct index too.
                container.headerPageIndex = idxx;
            }

            onFlickedRight: {
                var idxx = 0;
                if (container.currentPageIndex == 0) {
                    idxx = 6;
                } else {
                    idxx = container.currentPageIndex - 1;
                }
                container.headerPageIndex = idxx;
            }
        }
    }*/


    /*Item {
        id: contentArea
        z: 1;
        clip: true
        anchors {
            top: headerRow.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

    }*/

    // Initialize the first Day item.
    /*Component.onCompleted: {
        var now = new Date();
        var dayNum = now.getDay();
        dayNum = dayNum-1;
        __initializePage(dayNum);        
    }*/
}
