// Visual style for Desktop/Symbian
import QtQuick 1.0

Item {

    // Defines, if the screen is in landscape or portrait mode. This property
    // should be bound from outside to act on orientation changes correctly.
    property bool inLandscape: false

    // E6 has different screen resolution & aspect ratio (640x480), thus
    // there's some differentation for it separately.
    property bool isE6: false

    // General definitions (to define the Cell & Header item height, colors etc.)
    property int generalFontSize: 15//platformStyle.fontSizeMedium
    property int generalLeftMargin: inLandscape ? 50 : 25
    property int generalRightMargin: inLandscape ? 50 : 10
    property int generalTopMargin: 10
    property int bonsaiMargin: generalLeftMargin
    property int bonsaiMarginRight: inLandscape ? (isE6 ? 15 : 25) : 7
    property int textTopMargin: 3
    property color borderColor: "#C4AE94"
    property color generalTextColor: "#6A5147"
    property int itemHeight: 170
    property int bonsaiColumnWidth: inLandscape ? 140 : 100

    // For PivotHeader
    property int landscapeHeaderItemWidth: 214
    property int portraitHeaderItemWidth: 182
    property int headerHeight: isE6 ? 100 : 75
    property int headerTextSize: /*platformStyle.fontSizeMedium*/ 15 * 1.75

    // For bonsaiColumn
    property color delimiterColor: "#DF4C34"

    // Definitions for Pivot component
    property color headerTextColor: "#6A5147"

    // For PivotPage
    property int flickMargin: 25

    // For Cell Item
    property int selectionIndicatorWidth: 17
    property int cellFontSize: generalFontSize
    property color cellTextColor: generalTextColor

    // For EventDetailsView
    property int largeTopMargin: 50
    property int detailsFontSize: 20 /*platformStyle.fontSizeLarge*/
    property color detailsTextColor: generalTextColor
    property color detailsHeaderTextColor: "#BE5215"

    // For EventEditView
    property color editSeparatorColor: "#444444"
    property int editTitleMargins: 10
    property int editItemTopMargin: 0
    property int editTopMargin: inLandscape ? 4 : largeTopMargin
    property int selectionItemLeftMargin: inLandscape ? 42 : 18
    property int selectionItemRightMargin: inLandscape ? 50 : 0

    // For SelectionListItem
    property int listItemDefaultMargin: 6
}
