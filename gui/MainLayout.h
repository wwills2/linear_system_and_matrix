//
// Created by zan on 10/14/23.
//

#ifndef MATRIX_OPERATIONS_MAINLAYOUT_H
#define MATRIX_OPERATIONS_MAINLAYOUT_H

#include <stdexcept>
#include <QGridLayout>
#include <QGroupBox>
#include <QScrollArea>
#include <QVBoxLayout>
#include "NothingToShow.h"
#include "ConfigureDialog.h"
#include "LinearSystemDataEntry.h"
#include "../MatrixManager.h"

/**
 * @brief Layout instantiated in the main window
 * @extends QGridLayout
 */
class MainLayout : public QGridLayout{
    Q_OBJECT

public:
    explicit MainLayout(QWidget *parent) noexcept(false);
    ~MainLayout() override;

    void setUpLayout(ConfigureDialog &configureDialog) noexcept(false);
    IntfDataEntry *getInputLayout() noexcept(false);

private:

    /**
     * @brief Wrapper consisting of a scroll area placed inside a groupbox. the scroll area is placed inside a vboxlayout
     */
    class WrapperScrollBox;

    bool m_layoutConfigured;
    NothingToShow *m_nothingToShow;

    WrapperScrollBox *m_dataEntryScrollBox;
    IntfDataEntry *m_dataEntryIntf;

    WrapperScrollBox *m_resultsScrollBox;
    IntfDataEntry *m_resultsLayout;
};


class MainLayout::WrapperScrollBox : public QGroupBox{
    Q_OBJECT

public:
    explicit WrapperScrollBox(const QString &title);

    void setWidget(QWidget *widget) noexcept(false);
    QWidget *getWidget() noexcept(false);

private:
    QScrollArea *m_scrollArea;
    bool m_widgetSet;

    // friend function to allow setting the scroll area of the widget being added
    friend void MainLayout::setUpLayout(ConfigureDialog &configureDialog) noexcept(false);
};

#endif //MATRIX_OPERATIONS_MAINLAYOUT_H
