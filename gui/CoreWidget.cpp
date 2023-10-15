//
// Created by zan on 10/14/23.
//

#include "CoreWidget.h"

CoreWidget::CoreWidget() : QGroupBox(tr("Matrix")){

    //create table representation of matrix
    auto matrixDims = getDimensions();
    m_matrixAsTable = new QTableWidget(matrixDims->numRows, matrixDims->numColumns, this);
    loadMatrixIntoTable();

    //set up the grid layout
    m_matrixGridLayout = new QGridLayout;
    m_matrixGridLayout->addWidget(m_matrixAsTable, 0, 0);

    setLayout(m_matrixGridLayout);

}

void CoreWidget::loadMatrixIntoTable() {

    auto matrixIt = begin();
    mpq_class rationRep;
    QTableWidgetItem *itemToAdd;

    for (int i = 0; i < m_matrixAsTable->rowCount(); i++){
        for (int j = 0; j < m_matrixAsTable->columnCount(); j++){

            rationRep = *matrixIt;
            itemToAdd = new QTableWidgetItem(rationRep.get_str().c_str());
            m_matrixAsTable->setItem(i, j, itemToAdd);
            m_matrixAsTable->update();
            ++matrixIt;
        }
    }
}