
#include <QtWidgets>

#include "../include/ConfigureDialog.h"

ConfigureDialog::ConfigureDialog(QWidget *parent) : QDialog(parent){

    createConfigureGroupBox();
    m_operation = NOT_CONFIGURED;
    m_numVariables = 0;
    m_numEquations = 0;

    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(m_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(m_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    auto *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_configureGroupBox);
    mainLayout->addWidget(m_buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Configure"));
}

void ConfigureDialog::createConfigureGroupBox()
{
    m_configureGroupBox = new QGroupBox(tr("Linear System Properties"));
    m_varCountSpin = new QSpinBox;
    m_eqCountSpin = new QSpinBox;

    auto *layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Enter Number of Equations:")), m_eqCountSpin);
    layout->addRow(new QLabel(tr("Enter Number of Variables:")), m_varCountSpin);
    m_configureGroupBox->setLayout(layout);
}

void ConfigureDialog::accept() {

    m_operation = ANALYZE; //future functionality: set with combo box selection
    m_numEquations = m_eqCountSpin->value();
    m_numVariables = m_varCountSpin->value();

    if (m_numEquations < 1 || m_numVariables < 1){

        QMessageBox::warning(this, tr("Invalid Configuration"), tr("A system of linear equations"
                                                    "must have at least one equation which contains at least one variable"));
        m_operation = NOT_CONFIGURED;
        m_numEquations = 0;
        m_numVariables = 0;
    }else{
        QDialog::accept();
    }
}

void ConfigureDialog::reject() {
    QDialog::reject();
}
