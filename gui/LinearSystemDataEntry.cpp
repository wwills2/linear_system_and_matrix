//
// Created by zan on 10/20/23.
//
#include "LinearSystemDataEntry.h"

#define LINE_EDIT_PERCENT_WIDGET_WIDTH (int) 10

LinearSystemDataEntry::LinearSystemDataEntry(int numEquations, int numVars, QWidget *parent) :
        QGridLayout(parent), m_numEquations(numEquations), m_numVars(numVars) {

    QSizePolicy qSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setSizePolicy(qSizePolicy);

    QLineEdit *xCoeffEdit;
    QLabel *xnDisplay;
    int numWidgetsInRow = m_numVars * 2;

    for (int i = 0; i < m_numEquations; i++){
        for(int j = 0; j < numWidgetsInRow; j++){

            xCoeffEdit = new QLineEdit;
            xCoeffEdit->setMinimumWidth(width() / LINE_EDIT_PERCENT_WIDGET_WIDTH);
            addWidget(xCoeffEdit, i, j);

            xnDisplay = new QLabel;
            if (j != numWidgetsInRow - 2){
                xnDisplay->setText("x" + QString::number(j / 2) + " + ");
            }else{
                xnDisplay->setText("x" + QString::number(j / 2));
            }
            addWidget(xnDisplay, i, ++j);
        }
    }
}

