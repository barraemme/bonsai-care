import QtQuick 1.0

Component {
     id: addDelegate

     Item {
         id: wrapper
         width: addView.cellWidth
         height: addView.cellHeight

         Rectangle {
             id: blackRect
             color: "black"
             opacity: 0.3
             radius: 10
             height: parent.height-4
             width: parent.width-4
             y: 4
             x: 4
         }

         Item {
             id: sIcon;

             width: 65;
             height: 65;
             smooth: true
             y: 6;
             anchors.horizontalCenter: parent.horizontalCenter

             Loading { x: 1; y: 1; width: 65; height: 65; visible: realImage.status != Image.Ready }
             Image {
                 id: realImage;
                 source: "images/small/s_spc_"+bi_index+".jpg";
                 x: 1; y: 1;
                 width:65; height:65; opacity:0 ;
                 onStatusChanged: {
                     if(status==Image.Ready)
                         sIcon.state="loaded"
                 }
             }
             states: State {
                 name: "loaded";
                 PropertyChanges { target: realImage ; opacity:1 }
             }
             transitions: Transition { NumberAnimation { target: realImage; property: "opacity"; duration: 200 } }

         }

         Text {
             text: bi_name
             width: parent.width;
             font.pixelSize: 20;
             font.bold: true;
             horizontalAlignment: Text.AlignHCenter
             color: "#bbb";
             style: Text.Raised;
             styleColor: "black"
             wrapMode: Text.WordWrap
             anchors.top: sIcon.bottom;
             anchors.horizontalCenter: parent.horizontalCenter
             anchors.margins: 6
         }

         MouseArea {
             id: mouseRegion
             anchors.fill: blackRect
             onClicked: { wrapper.GridView.view.currentIndex = index; }
         }

         states: [
             State {
                 name: "Pressed"
                 when: mouseRegion.pressed === true
                 PropertyChanges { target: blackRect; color: "green" }
             }
         ]
         transitions: Transition {
             ColorAnimation { target: blackRect; }
         }
     }
 }
