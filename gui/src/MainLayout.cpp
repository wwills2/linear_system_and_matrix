//
// Created by zan on 10/14/23.
//

#include "../include/MainLayout.h"
#include "../include/ConfigureDialog.h"

#define UPPER 0, 0
#define LOWER 1, 0

MainLayout::MainLayout(QWidget *parent) : QGridLayout(parent) {

    m_layoutConfigured = false;
    m_dataEntryScrollBox = new WrapperScrollBox(tr("Linear System Data Entry"));
    m_resultsScrollBox = new WrapperScrollBox(tr("Linear System Analysis Results"));

    m_dataEntryIntf = nullptr;
    m_resultsDisplayIntf = nullptr;

    m_nothingToShow = new NothingToShow;
    //display nothing to show screen
    addWidget(m_nothingToShow, UPPER);
}

MainLayout::~MainLayout(){
    delete m_nothingToShow; //explict delete because may not belong to QObject on exit
}

void MainLayout::setUpLayout(ConfigureDialog &configureDialog) noexcept(false){

    switch (configureDialog.m_operation){

        case ConfigureDialog::NOT_CONFIGURED:
            return; // if an operation has not been selected, stop

        case ConfigureDialog::ANALYZE:
        {
            int equationCount = configureDialog.m_numEquations;
            int variableCount = configureDialog.m_numVariables;
            auto *linearSystemDataEntry = new LinearSystemDataEntry(equationCount, variableCount,
                                                                                     m_dataEntryScrollBox->m_scrollArea);
            m_dataEntryIntf = linearSystemDataEntry;
            m_dataEntryScrollBox->setWidget(linearSystemDataEntry);

            // replace existing NothingToShow widget with the data entry widget
            addWidget(m_dataEntryScrollBox, UPPER);

            // add results widget
            auto *linearSystemResultsDisplay = new LinearSystemResultsDisplay(m_resultsScrollBox->m_scrollArea);
            m_resultsDisplayIntf = linearSystemResultsDisplay;
            m_resultsScrollBox->setWidget(linearSystemResultsDisplay);
            addWidget(m_resultsScrollBox, LOWER);
            m_layoutConfigured = true;
        }

        case ConfigureDialog::ARITHMETIC:
            break; // for future matrix addition, multiply, etc
    }
}

IntfDataEntry *MainLayout::getInputLayout() noexcept(false){
    if (m_layoutConfigured){
        return m_dataEntryIntf;
    }else{
        throw std::runtime_error("main layout has not been configured, cannot return data entry layout");
    }
}

IntfResultsDisplay *MainLayout::getResultsLayout() noexcept(false) {
    if (m_layoutConfigured){
        return m_resultsDisplayIntf;
    }else{
        throw std::runtime_error("main layout has not been configured, cannot return data entry layout");
    }
}

// WrapperScrollBox functions ------------------------------------------------------------------------------------------

MainLayout::WrapperScrollBox::WrapperScrollBox(const QString &title) : QGroupBox(title){

    m_widgetSet = false;
    m_scrollArea = new QScrollArea();
    m_scrollArea->setWidgetResizable(false);

    auto *layoutForGroupBox = new QVBoxLayout(this); // need layout in group box, cannot directly set widget
    layoutForGroupBox->addWidget(m_scrollArea);
    setLayout(layoutForGroupBox);
}

void MainLayout::WrapperScrollBox::setWidget(QWidget *widget) noexcept(false){

    if (widget != nullptr && m_widgetSet) {
        //delete current widget and replace
        m_scrollArea->setWidget(widget);
    }else if (widget != nullptr){
        // widget has not been set, set it
        m_widgetSet = true;
        m_scrollArea->setWidget(widget);
    }else{
        throw std::invalid_argument("main layout wrapper scroll box widget cannot be null");
    }
}

QWidget *MainLayout::WrapperScrollBox::getWidget() noexcept(false) {

    if (m_widgetSet){
        return m_scrollArea->widget();
    }else{
        throw std::runtime_error("Widget has not been set");
    }
}
