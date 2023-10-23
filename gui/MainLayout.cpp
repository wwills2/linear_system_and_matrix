//
// Created by zan on 10/14/23.
//

#include "MainLayout.h"
#include "ConfigureDialog.h"

#define UPPER 0, 0
#define LOWER 1, 0

MainLayout::MainLayout(QWidget *parent) : QGridLayout(parent) {

    m_dataEntryScrollBox = new WrapperScrollBox(tr("Linear System Data Entry"));
    m_resultsScrollBox = new WrapperScrollBox(tr("Linear System Analysis Results"));

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
            m_dataEntryScrollBox->setWidget(new LinearSystemDataEntry(equationCount, variableCount,
                                                                      m_dataEntryScrollBox->m_scrollArea));
            // replace existing nothing to show with the data entry widget
            replaceWidget(m_nothingToShow, m_dataEntryScrollBox);

            // add results widget
            m_resultsScrollBox->setWidget(m_nothingToShow); //todo: replace with proper results widget
            addWidget(m_resultsScrollBox, LOWER); //todo:  fix memory leak here
        }

        case ConfigureDialog::ARITHMETIC:
            break; // for future matrix addition, multiply, etc
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

void MainLayout::WrapperScrollBox::setWidget(QWidget *widget) noexcept(false) {

    if (widget != nullptr){
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
        throw std::runtime_error("cannot retrieve ");
    }
}
