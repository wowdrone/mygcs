# -------------------------------------------------
# QGroundControl - Micro Air Vehicle Groundstation
# Please see our website at <http://qgroundcontrol.org>
# Maintainer:
# Lorenz Meier <lm@inf.ethz.ch>
# (c) 2009-2015 QGroundControl Developers
#
# This file is part of the open groundstation project
# QGroundControl is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# QGroundControl is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# You should have received a copy of the GNU General Public License
# along with QGroundControl. If not, see <http://www.gnu.org/licenses/>.
#
# Author: Gus Grubba <mavlink@grubba.com>
# -------------------------------------------------

#
#-- Depends on gstreamer, which can be found at: http://gstreamer.freedesktop.org/download/
#

LinuxBuild {
    QT += x11extras waylandclient
    CONFIG += link_pkgconfig
    packagesExist(gstreamer-1.0) {
        PKGCONFIG   += gstreamer-1.0  gstreamer-video-1.0 gstreamer-gl-1.0
        CONFIG      += VideoEnabled
    }
} else:MacBuild {
    #- gstreamer framework installed by the gstreamer devel installer
    GST_ROOT = /Library/Frameworks/GStreamer.framework
    exists($$GST_ROOT) {
        CONFIG      += VideoEnabled
        INCLUDEPATH += $$GST_ROOT/Headers
        LIBS        += -F/Library/Frameworks -framework GStreamer
    }
} else:iOSBuild {
    #- gstreamer framework installed by the gstreamer iOS SDK installer (default to home directory)
    GST_ROOT = $$(HOME)/Library/Developer/GStreamer/iPhone.sdk/GStreamer.framework
    exists($$GST_ROOT) {
        CONFIG      += VideoEnabled
        INCLUDEPATH += $$GST_ROOT/Headers
        LIBS        += -F$$(HOME)/Library/Developer/GStreamer/iPhone.sdk -framework GStreamer -liconv -lresolv
    }
} else:WindowsBuild {
    #- gstreamer installed by default under c:/gstreamer
    GST_ROOT = c:/gstreamer/1.0/x86
    exists($$GST_ROOT) {
        CONFIG      += VideoEnabled

        LIBS        += -L$$GST_ROOT/lib -lgstreamer-1.0 -lgstgl-1.0 -lgstvideo-1.0 -lgstbase-1.0
        LIBS        += -lglib-2.0 -lintl -lgobject-2.0

        INCLUDEPATH += \
            $$GST_ROOT/include \
            $$GST_ROOT/include/gstreamer-1.0 \
            $$GST_ROOT/include/glib-2.0 \
            $$GST_ROOT/lib/gstreamer-1.0/include \
            $$GST_ROOT/lib/glib-2.0/include

        DESTDIR_WIN = $$replace(DESTDIR, "/", "\\")
        GST_ROOT_WIN = $$replace(GST_ROOT, "/", "\\")

        # Copy main GStreamer runtime files
        QMAKE_POST_LINK += $$escape_expand(\\n) xcopy \"$$GST_ROOT_WIN\\bin\*.dll\" \"$$DESTDIR_WIN\" /S/Y $$escape_expand(\\n)
        QMAKE_POST_LINK += xcopy \"$$GST_ROOT_WIN\\bin\*.\" \"$$DESTDIR_WIN\" /S/Y $$escape_expand(\\n)

        # Copy GStreamer plugins
        QMAKE_POST_LINK += $$escape_expand(\\n) xcopy \"$$GST_ROOT_WIN\\lib\\gstreamer-1.0\\*.dll\" \"$$DESTDIR_WIN\\gstreamer-plugins\\\" /Y $$escape_expand(\\n)
        QMAKE_POST_LINK += $$escape_expand(\\n) xcopy \"$$GST_ROOT_WIN\\lib\\gstreamer-1.0\\validate\\*.dll\" \"$$DESTDIR_WIN\\gstreamer-plugins\\validate\\\" /Y $$escape_expand(\\n)
    }
} else:AndroidBuild {
    #- gstreamer assumed to be installed in $$PWD/../../gstreamer-1.0-android-universal-1.14.4/***
    contains(QT_ARCH, arm) {
        GST_ROOT = $$PWD/../../gstreamer-1.0-android-universal-1.14.4/armv7
    } else:contains(QT_ARCH, arm64) {
        GST_ROOT = $$PWD/../../gstreamer-1.0-android-universal-1.14.4/arm64
    } else {
        GST_ROOT = $$PWD/../../gstreamer-1.0-android-universal-1.14.4/x86
    }
    exists($$GST_ROOT) {
        QMAKE_CXXFLAGS  += -pthread
        CONFIG          += VideoEnabled

        # We want to link these plugins statically
        LIBS += -L$$GST_ROOT/lib/gstreamer-1.0 \
            -lgstvideo-1.0 \
            -lgstcoreelements \
            -lgstudp \
            -lgstrtp \
            -lgstrtsp \
            -lgstx264 \
            -lgstlibav \
            -lgstsdpelem \
            -lgstvideoparsersbad \
            -lgstrtpmanager \
            -lgstisomp4 \
            -lgstmatroska \
            -lgstandroidmedia \
            -lgstopengl

        # Rest of GStreamer dependencies
        LIBS += -L$$GST_ROOT/lib \
            -lgraphene-1.0 -ljpeg -lpng16 \
            -lgstfft-1.0 -lm  \
            -lgstnet-1.0 -lgio-2.0 \
            -lgstphotography-1.0 -lgstgl-1.0 -lEGL \
            -lgstaudio-1.0 -lgstcodecparsers-1.0 -lgstbase-1.0 \
            -lgstreamer-1.0 -lgstrtp-1.0 -lgstpbutils-1.0 -lgstrtsp-1.0 -lgsttag-1.0 \
            -lgstvideo-1.0 -lavformat -lavcodec -lavutil -lx264 -lavfilter -lswresample \
            -lgstriff-1.0 -lgstcontroller-1.0 -lgstapp-1.0 \
            -lgstsdp-1.0 -lbz2 -lgobject-2.0 \
            -Wl,--export-dynamic -lgmodule-2.0 -pthread -lglib-2.0 -lorc-0.4 -liconv -lffi -lintl \

        INCLUDEPATH += \
            $$GST_ROOT/include/gstreamer-1.0 \
            $$GST_ROOT/lib/gstreamer-1.0/include \
            $$GST_ROOT/include/glib-2.0 \
            $$GST_ROOT/lib/glib-2.0/include
    }
}

VideoEnabled {

    message("Including support for video streaming")

    DEFINES += \
        QGC_GST_STREAMING

    iOSBuild {
        OBJECTIVE_SOURCES += \
            $$PWD/iOS/gst_ios_init.m
        INCLUDEPATH += \
            $$PWD/iOS
    }

} else {
    LinuxBuild|MacBuild|iOSBuild|WindowsBuild|AndroidBuild {
        message("Skipping support for video streaming (GStreamer libraries not installed)")
        message("Installation instructions here: https://github.com/mavlink/qgroundcontrol/blob/master/src/VideoStreaming/README.md")
    } else {
        message("Skipping support for video streaming (Unsupported platform)")
    }
}

