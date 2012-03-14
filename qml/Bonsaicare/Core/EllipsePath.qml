// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Path {
    id: p
    property real width: 200
    property real height: 200
    property real margin: 50
    property real cx: width / 2
    property real cy: height / 2
    property real rx: width / 2 - margin
    property real ry: height / 2 - margin
    property real mx: rx * magic
    property real my: ry * magic
    property real magic: 0.551784
    //percentual of item on quadrant arc
    property real tlq: 0.25
    property real trq: 0.25
    property real blq: 0.25
    property real brq: 0.25

    startX: p.cx - p.rx
    startY: p.cy //+ p.ry

    PathCubic { // third quadrant arc
        control1X: p.cx - p.rx; control1Y: p.cy - p.my
        control2X: p.cx - p.mx; control2Y: p.cy - p.ry
        x: p.cx; y: p.cy - p.ry
    }
    PathPercent{value: p.tlq}

    PathCubic { // forth quadrant arc
        control1X: p.cx + p.mx; control1Y: p.cy - p.ry
        control2X: p.cx + p.rx; control2Y: p.cy - p.my
        x: p.cx + p.rx; y: p.cy
    }
    PathPercent{value: p.trq}
    PathCubic { // first quadrant arc
        control1X: p.cx + p.rx; control1Y: p.cy + p.my
        control2X: p.cx + p.mx; control2Y: p.cy + p.ry
        x: p.cx; y: p.cy + p.ry
    }
    PathPercent{value: p.brq}
    PathCubic { // second quadrant arc
        control1X: p.cx - p.mx; control1Y: p.cy + p.ry
        control2X: p.cx - p.rx; control2Y: p.cy + p.my
        x: p.cx - p.rx; y: p.cy
    }
    PathPercent{value: p.blq}
}
