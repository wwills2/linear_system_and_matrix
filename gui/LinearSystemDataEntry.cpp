//
// Created by zan on 10/20/23.
//
#include "LinearSystemDataEntry.h"

#define LINE_EDIT_WIDTH 100 //pixels

LinearSystemDataEntry::LinearSystemDataEntry(int numEquations, int numVars, QWidget *parent) :
        QWidget(parent), m_numEquations(numEquations), m_numEdits(numVars + 1), m_lineEdits(m_numEquations * m_numEdits) {

    m_entryGrid = new QGridLayout(this);

    QSizePolicy qSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setSizePolicy(qSizePolicy);

    QLineEdit *xCoeffEdit;
    QLabel *xnDisplay;
    int numWidgetsInRow = m_numEdits * 2;
    auto lineEditIt = m_lineEdits.begin();

    //todo: openMP parallelism
    for (int i = 0; i < m_numEquations; i++){
        for(int j = 0; j < numWidgetsInRow; j++) {

            xCoeffEdit = new QLineEdit;
            xCoeffEdit->setMinimumWidth(LINE_EDIT_WIDTH);
            xCoeffEdit->setMaximumWidth(LINE_EDIT_WIDTH);

            // add line edit to layout and line edits vector
            m_entryGrid->addWidget(xCoeffEdit, i, j);
            *lineEditIt = xCoeffEdit;
            lineEditIt++;

            xnDisplay = new QLabel;
            if (j == numWidgetsInRow - 4) {
                xnDisplay->setText("x" + QString::number(j / 2) + "\t=\t");
                m_entryGrid->addWidget(xnDisplay, i, ++j);
            }else if (j < numWidgetsInRow - 4){
                xnDisplay->setText("x" + QString::number(j / 2) + " + ");
                m_entryGrid->addWidget(xnDisplay, i, ++j);
            }else{
                j++;
            }
        }
    }
}

bool LinearSystemDataEntry::loadUiData(wwills2::MatrixManager &matrixManager) {

    if (!matrixManager.hasMatrix("matrix")){
        matrixManager.createMatrix(m_matrixName, m_numEquations, m_numEdits);
    }

    auto matrix = matrixManager.getMatrix(m_matrixName);

    auto matrixIt = matrix->begin();
    auto lineEditIt = m_lineEdits.begin();

    for (/*declared above*/ ;matrixIt != matrix->end() && lineEditIt != m_lineEdits.end(); ++matrixIt, lineEditIt++){

        try{
            (*matrixIt) = mpq_class((*lineEditIt)->text().toStdString());
        }catch (std::invalid_argument &error){

            // value was not entered as rational, attempt to parse as decimal
            mpf_class mpf((*lineEditIt)->text().toStdString());
            (*matrixIt) = mpq_class(mpf.get_d());
        }
    }

    return true;
}

