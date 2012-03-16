// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import "Core" 1.1 as Core

// bonsai prototype item.
Item {
        id: bonsaiDelegate
        z:1
        property variant modelData: model

        onFocusChanged: {
            if(bonsaiLayer.currentIndex === index){
                pathOperations.state = 'overlayed';
            }
            else{
                pathOperations.state = 'normal';
            }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log("clicked bonsai at index "+index);                
                if(bonsaiLayer.currentIndex !== index){
                    bonsaiLayer.currentIndex = index

                }
            }
        }

        DayLayer{
            id: pathOperations
            model: bonsai.getOperationsByIndex(index);
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }

        /*Text {
            id: nameTxt
            color: container.textColor
            anchors {
                top: parent.top
                topMargin: visual.textTopMargin
                left: parent.left
                leftMargin: visual.bonsaiNameMarginLeft
            }
            font.weight: Font.Bold
            font.pixelSize: container.fontSize
            wrapMode : Text.Wrap
            text: b_name+", "+ container.model.getAgeString(b_date)
        }*/

        Item {
            id: image;
            width: bonsaiLayer.cellWidth//100;
            height: bonsaiLayer.cellWidth//100;
            smooth: true
            /*anchors {
                top: nameTxt.bottom
                topMargin: visual.textTopMargin
                right: parent.right
                rightMargin:20
            }*/

            Core.Loading {
                width: 100;
                height: 100;
                visible: realImage.status != Image.Ready
            }

            Image {
                id: realImage;
                source: "images/medium/m_spc_"+b_specieId+".png";
                width:bonsaiLayer.cellWidth//100;
                height:bonsaiLayer.cellWidth//100;
                opacity:0 ;
                onStatusChanged: {
                    if(status==Image.Ready)
                        image.state="loaded"
                }

            }
            states: State {
                name: "loaded";
                PropertyChanges { target: realImage ; opacity:1 }
            }
            transitions: Transition { NumberAnimation { target: realImage; property: "opacity"; duration: 200 } }
        }        
}

