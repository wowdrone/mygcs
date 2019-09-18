/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/


/**
 * @file
 *   @brief QGC Video Background
 *   @author Gus Grubba <mavlink@grubba.com>
 */

import QtQuick                          2.11
import QtQuick.Controls                 2.4
import org.freedesktop.gstreamer.GLVideoItem 1.0

GstGLVideoItem {
    id: video
    anchors.centerIn: parent
    width: parent.width
    height: parent.height
    anchors.fill: parent
}
