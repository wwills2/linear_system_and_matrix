//
// Created by zan on 10/20/23.
//
#include "LinearSystemDataEntry.h"

#define MIN_LINE_EDIT_WIDTH 100

LinearSystemDataEntry::LinearSystemDataEntry(int numEquations, int numVars, QWidget *parent) :
        QWidget(parent), m_numEquations(numEquations), m_numVars(numVars) {

    m_entryGrid = new QGridLayout(this);

    QSizePolicy qSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setSizePolicy(qSizePolicy);

    QLineEdit *xCoeffEdit;
    QLabel *xnDisplay;
    int numWidgetsInRow = m_numVars * 2;

    for (int i = 0; i < m_numEquations; i++){
        for(int j = 0; j < numWidgetsInRow; j++){

            xCoeffEdit = new QLineEdit;
            xCoeffEdit->setMinimumWidth(MIN_LINE_EDIT_WIDTH);
            xCoeffEdit->setMaximumWidth(MIN_LINE_EDIT_WIDTH);
            m_entryGrid->addWidget(xCoeffEdit, i, j);

            xnDisplay = new QLabel;
            if (j != numWidgetsInRow - 2){
                xnDisplay->setText("x" + QString::number(j / 2) + " + ");
            }else{
                xnDisplay->setText("x" + QString::number(j / 2));
            }
            m_entryGrid->addWidget(xnDisplay, i, ++j);
        }
    }
}

