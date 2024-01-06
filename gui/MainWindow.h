/* this file is based on a QT example file.
 * the original header comment is included at the bottom for licensing purposes */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../MatrixManager.h"
#include "MainLayout.h"
#include "ConfigureDialog.h"

/**
 * @brief main window for the application. controls configuration and macro actions
 */
class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow() = delete;

    /**
     * constructor for the main window. configures the window's properties and initializes the main layout
     * to its default state
     * @param matrixManager the matrix manager for this application
     */
    explicit MainWindow(wwills2::MatrixManager &matrixManager);

    /**
     * destructor. cleans up the main layout and this window's QActions
     */
    ~MainWindow() override;
/**
 * slots to receive toolbar menu signals
 */
private slots:
    void openFile();
    void saveFile();
    void configure();
    void run();

private:

    /**
     * creates action toolbar drop down menus
     */
    void createMenus();

    wwills2::MatrixManager m_matrixManager;
    ConfigureDialog::Operation m_operation;

    /**
     * @brief the main window exists as widget containing a layout. this widget serves as a wrapper for the main layout
     * to be set as the window's central widget
     */
    QWidget *m_mainLayoutWrapperWidget;
    MainLayout *m_mainLayout;

    QMenu *m_fileMenu;
    QMenu *m_actionMenu;

    QAction *m_openAct;
    QAction *m_saveAct;
    QAction *m_exitAct;
    QAction *m_configureAct;
    QAction *m_editAct;
    QAction *m_runAct;
};

#endif // MAINWINDOW_H


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