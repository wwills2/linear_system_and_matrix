/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
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
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
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

#include "MainWindow.h"

#include <QAction>
#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>

MainWindow::MainWindow() {

    QSizePolicy qSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setSizePolicy(qSizePolicy);

    //main view must be contained in widget.
    m_coreLayoutWidget = new QWidget(this);
    m_coreLayoutWidget->setSizePolicy(qSizePolicy);

    m_mainLayout = new MainLayout(m_coreLayoutWidget);
    m_coreLayoutWidget->setLayout(m_mainLayout);

    //set widget with main layout as central widget
    setCentralWidget(m_coreLayoutWidget);

    createMenus();
    setWindowTitle(tr(WINDOW_NAME));
}

MainWindow::~MainWindow() {

    delete m_mainLayout;

    delete m_fileMenu;
    delete m_actionMenu;

    delete m_openAct;
    delete m_saveAct;
    delete m_exitAct;
    delete m_addAct;
    delete m_editAct;
    delete m_removeAct;
}

void MainWindow::createMenus() {

    m_fileMenu = menuBar()->addMenu(tr("&File"));

    m_openAct = new QAction(tr("&Open..."), this);
    m_fileMenu->addAction(m_openAct);
    connect(m_openAct, &QAction::triggered, this, &MainWindow::openFile);

    m_saveAct = new QAction(tr("&Save As..."), this);
    m_fileMenu->addAction(m_saveAct);
    connect(m_saveAct, &QAction::triggered, this, &MainWindow::saveFile);

    m_fileMenu->addSeparator();

    m_exitAct = new QAction(tr("E&xit"), this);
    m_fileMenu->addAction(m_exitAct);
    connect(m_exitAct, &QAction::triggered, this, &QWidget::close);

    m_actionMenu = menuBar()->addMenu(tr("&Actions"));

    m_addAct = new QAction(tr("&Configure"), this);
    m_actionMenu->addAction(m_addAct);

    /* todo: add more actions down the line
    m_editAct = new QAction(tr("&Edit Entry..."), this);
    m_editAct->setEnabled(false);
    m_actionMenu->addAction(m_editAct);
     */
    m_actionMenu->addSeparator();

    m_removeAct = new QAction(tr("&Remove Entry"), this);
    m_removeAct->setEnabled(false);
    m_actionMenu->addAction(m_removeAct);
}

void MainWindow::openFile()
{

    //todo: undo
    QMessageBox::information(this, tr("not implemented"), tr("this feature is not implemented"));
    return;

    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        ;//todo: add open file action
}

void MainWindow::saveFile()
{
    //todo: undo
    QMessageBox::information(this, tr("not implemented"), tr("this feature is not implemented"));
    return;

    QString fileName = QFileDialog::getSaveFileName(this);
    if (!fileName.isEmpty())
        ;//todo: add save file action
}
