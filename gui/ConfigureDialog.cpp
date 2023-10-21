
#include <QtWidgets>

#include "ConfigureDialog.h"

ConfigureDialog::ConfigureDialog(){

    createConfigureGroupBox();

    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(m_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(m_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    auto *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_ConfigureGroupBox);
    mainLayout->addWidget(m_buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Basic Layouts"));
}

void ConfigureDialog::createConfigureGroupBox()
{
    m_ConfigureGroupBox = new QGroupBox(tr("Configure Operation"));
    auto *layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Enter Number of Variables:")), new QSpinBox);
    layout->addRow(new QLabel(tr("Enter Number of Equations:")), new QSpinBox);
    m_ConfigureGroupBox->setLayout(layout);
}
