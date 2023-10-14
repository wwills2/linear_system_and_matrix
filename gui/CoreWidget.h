//
// Created by zan on 10/14/23.
//

#ifndef MATRIX_OPERATIONS_COREWIDGET_H
#define MATRIX_OPERATIONS_COREWIDGET_H

#include <QGroupBox>
#include <QGridLayout>
#include <QTableWidget>
#include "../Matrix.h"

class CoreWidget : public QGroupBox, private wwills2::Matrix{

public:
    CoreWidget();

private:



    QGridLayout *m_matrixGridLayout;
    QTableWidget *m_matrixAsTable;
};

#endif //MATRIX_OPERATIONS_COREWIDGET_H
