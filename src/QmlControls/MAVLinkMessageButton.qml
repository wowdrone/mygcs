/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

import QtQuick                      2.11
import QtQuick.Controls             2.4
import QtQuick.Layouts              1.11

import QGroundControl.Palette       1.0
import QGroundControl.ScreenTools   1.0

Button {
    id:                 control
    height:             ScreenTools.defaultFontPixelHeight * 2
    autoExclusive:      true
    leftPadding:        ScreenTools.defaultFontPixelWidth
    rightPadding:       leftPadding

    property real _compIDWidth: ScreenTools.defaultFontPixelWidth * 2.5
    property real _hzWidth:     ScreenTools.defaultFontPixelWidth * 5
    property real _nameWidth:   nameLabel.contentWidth

    background: Rectangle {
        anchors.fill:   parent
        color:          checked ? qgcPal.buttonHighlight : qgcPal.button
    }

    property double messageHz:  0
    property int    compID:     0

    contentItem: RowLayout {
        id:         rowLayout
        spacing:    ScreenTools.defaultFontPixelWidth

        QGCLabel {
            text:                   control.compID
            color:                  checked ? qgcPal.buttonHighlightText : qgcPal.buttonText
            font.pointSize:         ScreenTools.smallFontPointSize
            Layout.minimumWidth:    _compIDWidth
        }
        QGCLabel {
            id:                     nameLabel
            text:                   control.text
            color:                  checked ? qgcPal.buttonHighlightText : qgcPal.buttonText
            font.pointSize:         ScreenTools.smallFontPointSize
            Layout.fillWidth:       true
        }
        QGCLabel {
            color:                  checked ? qgcPal.buttonHighlightText : qgcPal.buttonText
            text:                   messageHz.toFixed(1) + 'Hz'
            font.pointSize:         ScreenTools.smallFontPointSize
            horizontalAlignment:    Text.AlignRight
            Layout.minimumWidth:    _hzWidth
        }
    }

    Component.onCompleted: maxButtonWidth = Math.max(maxButtonWidth, _compIDWidth + _hzWidth + _nameWidth + (rowLayout.spacing * 2) + (control.leftPadding * 2))
}
