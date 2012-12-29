/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>
#include "HUD2.h"

HUD2::~HUD2()
{
    if (usegl != true){
        renderergl = new HUD2RendererGL(&helper, this);
    }
    else{
        renderersoft = new HUD2RendererSoft(&helper, this);
    }

    disconnect(&timer, SIGNAL(timeout()));
    timer.stop();

}

HUD2::HUD2(QWidget *parent)
    : QWidget(parent)
{
    usegl = false;

    if (usegl == true){
        renderergl = new HUD2RendererGL(&helper, this);
        renderersoft = NULL;
        btn.setText(tr("GL"));
        layout.addWidget(renderergl, 0, 0);
        connect(&timer, SIGNAL(timeout()), renderergl, SLOT(animate()));
    }
    else{
        renderersoft = new HUD2RendererSoft(&helper, this);
        renderergl = NULL;
        btn.setText(tr("Soft"));
        layout.addWidget(renderersoft, 0, 0);
        connect(&timer, SIGNAL(timeout()), renderersoft, SLOT(animate()));
    }

    connect(&btn, SIGNAL(clicked()), this, SLOT(togglerenderer()));
    layout.addWidget(&btn, 1, 0);
    setLayout(&layout);

    timer.start(50);
}

void HUD2::togglerenderer(void)
{
    if (usegl == true){
        disconnect(&timer, SIGNAL(timeout()), renderergl, SLOT(animate()));
        layout.removeWidget(renderergl);
        delete renderergl;
        renderersoft = new HUD2RendererSoft(&helper, this);
        connect(&timer, SIGNAL(timeout()), renderersoft, SLOT(animate()));
        layout.addWidget(renderersoft, 0, 0);
        btn.setText(tr("Soft"));
        usegl = false;
    }
    else{
        disconnect(&timer, SIGNAL(timeout()), renderersoft, SLOT(animate()));
        layout.removeWidget(renderersoft);
        delete renderersoft;
        renderergl = new HUD2RendererGL(&helper, this);
        connect(&timer, SIGNAL(timeout()), renderergl, SLOT(animate()));
        layout.addWidget(renderergl, 0, 0);
        btn.setText(tr("GL"));
        usegl = true;
    }
}
