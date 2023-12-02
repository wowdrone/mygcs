import QtQuick
import QtQuick.Controls
import QtQuick.Controls

import QGroundControl.Palette
import QGroundControl.ScreenTools

CheckBox {
    id:             control
    spacing:        _noText ? 0 : ScreenTools.defaultFontPixelWidth
    focusPolicy:    Qt.ClickFocus

    property color  textColor:          _qgcPal.text
    property bool   textBold:           false
    property real   textFontPointSize:  ScreenTools.defaultFontPointSize

    property var    _qgcPal: QGCPalette { colorGroupEnabled: enabled }
    property bool   _noText: text === ""

    property ButtonGroup buttonGroup: null
    onButtonGroupChanged: {
        if (buttonGroup) {
            buttonGroup.addButton(control)
        }
    }

    contentItem: Text {
        //implicitWidth:  _noText ? 0 : text.implicitWidth + ScreenTools.defaultFontPixelWidth * 0.25
        //implicitHeight: _noText ? 0 : Math.max(text.implicitHeight, ScreenTools.checkBoxIndicatorSize)
        leftPadding:        control.indicator.width + control.spacing
        verticalAlignment:  Text.AlignVCenter
        text:               control.text
        font.pointSize:     textFontPointSize
        font.bold:          control.textBold
        font.family:        ScreenTools.normalFontFamily
        color:              control.textColor
    }

    /*
    // FIXME-QT6: Temporarily disabled, using standard Qt for now
    indicator:  Rectangle {
        implicitWidth:  ScreenTools.checkBoxIndicatorSize
        implicitHeight: implicitWidth
        x:              control.leftPadding
        y:              parent.height / 2 - height / 2
        color:          control.enabled ? "white" : _qgcPal.text
        border.color:   _qgcPal.text
        border.width:   1
        opacity:        control.checkedState === Qt.PartiallyChecked ? 0.5 : 1

        QGCColoredImage {
            source:     "/qmlimages/checkbox-check.svg"
            color:      "black"
            opacity:    control.checkedState === Qt.Checked ? (control.enabled ? 1 : 0.5) : 0
            mipmap:     true
            fillMode:   Image.PreserveAspectFit
            width:      parent.width * 0.75
            height:     width
            sourceSize.height: height
            anchors.centerIn:  parent
        }
    }
    */
}
