import QtQuick 1.0

Rectangle {


     DBModel{
         id: db
     }

     Component {
         id: addDelegate

         Item {
              width: grid.cellWidth; height: grid.cellHeight

             Image {
                 id: sIcon
                 y: 20; anchors.horizontalCenter: parent.horizontalCenter
                 source: "images/small/s_spc_"+sid+".jpg";
             }
             Text {
                 anchors { top: sIcon.bottom; horizontalCenter: parent.horizontalCenter }
                 text: name
                 font.pixelSize: 20;
                 font.bold: true;
                 color: "#bbb";
                 style: Text.Raised;
                 styleColor: "black"
                 wrapMode: Text.WordWrap
             }
         }
     }

     GridView {
         id: grid
         anchors.fill: parent
         cellWidth: parent.width/4; cellHeight: parent.width/4
         focus: true
         model: db
         delegate: addDelegate

     }
 }
