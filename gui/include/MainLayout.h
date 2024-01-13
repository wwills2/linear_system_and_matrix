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
#include "LinearSystemResultsDisplay.h"
#include "libmatrix/MatrixManager.h"

/**
 * @brief Layout instantiated in the main window
 * @extends QGridLayout
 */
class MainLayout : public QGridLayout{
    Q_OBJECT

public:

    /**
     * constructor for the main layout. the layout is divided into an upper and lower view.
     * data entry is in the upper view, and output display is in the lower view
     * @param parent view
     */
    explicit MainLayout(QWidget *parent);

    /**
     * explicitly deallocates the NothingToShow member since it does not have a parent when this
     * object goes out of scope and is deallocated
     */
    ~MainLayout() override;

    /**
     * configures the main layout based on the configuration settings
     * @param configureDialog configuration settings for the current task
     */
    void setUpLayout(ConfigureDialog &configureDialog) noexcept(false);

    /**
     * returns the main layout's data input layout (upper layout)
     */
    IntfDataEntry *getInputLayout() noexcept(false);

    /**
     * returns the main layout's operation output layout (lower layout)
     */
    IntfResultsDisplay *getResultsLayout() noexcept(false);

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
    IntfResultsDisplay *m_resultsDisplayIntf;
};

/**
 * Custom group box widget which contains a QScrollArea. acts as an interface to handle placing widgets into groupbox
 * in a scrollable fashion
 */
class MainLayout::WrapperScrollBox : public QGroupBox{
    Q_OBJECT

public:

    /**
     * constructor
     * @param title of the group box
     */
    explicit WrapperScrollBox(const QString &title);

    /**
     * set the widget to display
     * @param widget to display
     */
    void setWidget(QWidget *widget) noexcept(false);

    /**
     * @return the widget set in this scrollbox
     */
    QWidget *getWidget() noexcept(false);

private:
    QScrollArea *m_scrollArea;
    bool m_widgetSet;

    // friend function to allow setting the scroll area of the widget being added
    friend void MainLayout::setUpLayout(ConfigureDialog &configureDialog) noexcept(false);
};

#endif //MATRIX_OPERATIONS_MAINLAYOUT_H
