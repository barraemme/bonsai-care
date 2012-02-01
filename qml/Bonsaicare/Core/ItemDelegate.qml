import QtQuick 1.0

Component {
     id: itemDelegate

     Item{
     width:44; height:40;
        Image {
                id: realImage;
                source: "images/shape_"+opid+"a.png";
                width:40; height:40;
                anchors.horizontalCenter: parent.horizontalCenter
             }
     }

 }
