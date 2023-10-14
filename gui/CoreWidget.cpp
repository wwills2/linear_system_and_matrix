//
// Created by zan on 10/14/23.
//

#include "CoreWidget.h"

CoreWidget::CoreWidget() : QGroupBox(tr("Matrix")){

    //create table representation of matrix
    auto matrixDims = getDimensions();
    m_matrixAsTable = new QTableWidget(matrixDims->numRows, matrixDims->numColumns);


    //set up the grid layout
    m_matrixGridLayout = new QGridLayout;
    m_matrixGridLayout->addWidget(m_matrixGridLayout, );

    setLayout(m_matrixGridLayout);

};