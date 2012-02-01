import QtQuick 1.0

Item {
    TitleBar { id: titleBar; width: parent.width; height: 60;
        y: 0
        text: "Personal bonsai list"
        //addString: "Add personal bonsai"
    }
    states: [
        State {
            name: "search"; when: screen.state!="search"
            PropertyChanges { target: titleBar; y: 0 }
        }
    ]
    transitions: [
        Transition { NumberAnimation { properties: "x,y"; duration: 500; easing.type: Easing.InOutQuad } }
    ]
}

