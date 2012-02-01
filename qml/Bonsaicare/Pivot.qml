import QtQuick 1.0
import "Core" 1.1 as Core

Rectangle {
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
    property alias headerPageIndex: headerRow.currentIndex
    // Attributes to define the Cell item height, colors etc.
    property int itemHeight: visual.itemHeight
    property int bonsaiColumnWidth: visual.bonsaiColumnWidth
    property int generalLeftMargin: visual.generalLeftMargin
    property color borderColor: visual.borderColor
    property color headerTextColor: visual.headerTextColor

    // Attributes for tracking the application current views (current day).
    property Item currentPage
    property int currentPageIndex: 0
    property string currentDayName: week.dayName(currentPageIndex)

    // Internal properties, don't set from outside. This is used to
    // determine in which orientation the screen is.

    // TODO: Bind this rather to main Window's inPortrait property!
    property bool landscape: width > height

    property bool landscapeLayout: !view.inPortrait


    // A function to determine, whether we should show left to right or
    // right to left transition animation.
    /*function __switchPage(pageIndex, hidden) {
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
    }*/

    /*function __initializePage(pageIndex, hidden) {
        console.log("CurrentPage: " + container.currentPage);
        var pageComp = pivotPageComp;
        // Instantiate the component!
        if (pageComp.status == Component.Ready) {
            console.log("PageComp rdy: " + pageComp);
            container.currentPage = pageComp.createObject(contentArea);
            //container.currentPage.model = container.model.day(pageIndex).items();
            container.currentPage.state = hidden ? "Hidden" : "";
            container.currentPageIndex = pageIndex;

            console.log("CurrentPage rdy: " + container.currentPage);
        }
    }*/

    Component {
        id: pivotPageComp

        PivotPage {
            id: pivotPage

            flickMargin: visual.flickMargin
            itemHeight: container.itemHeight
            borderColor: container.borderColor
            textColor: container.headerTextColor
            bonsaiIndex: bonsaiColumn.bonsaiIndex

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
        }
    }

    // Pivot headers, used for navigation.

    PivotHeader {
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
           //__switchPage(index, true);
            console.log("AFTER PAGECHANGE, container.currentPage: "
                        + container.currentPage);
        }
    }

    // Show an hour column on the left side of the screen. Doesn't 'slide in/out'
    // with the rest of the content area and PivotPages.

    BonsaiColumn {
        id: bonsaiColumn

        // Set the bonsaiColumn to be quite narrow. The anchors will
        // define the bonsaiColumn's height.
        width: container.bonsaiColumnWidth
        itemHeight: container.itemHeight
        model: bonsai
        borderColor: container.borderColor

        anchors {
            top: headerRow.bottom
            bottom: parent.bottom
            left: parent.left
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


    Item {
        id: contentArea

        clip: true
        anchors {
            top: headerRow.bottom
            left: bonsaiColumn.right
            right: parent.right
            bottom: parent.bottom
        }
    }

    // Initialize the first Day item.
    /*Component.onCompleted: {
        __initializePage(0);
        container.currentPageIndex = 0;       
    }*/
}