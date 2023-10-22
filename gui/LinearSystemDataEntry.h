//
// Created by zan on 10/20/23.
//

#ifndef MATRIX_OPERATIONS_LINEARSYSTEMDATAENTRY_H
#define MATRIX_OPERATIONS_LINEARSYSTEMDATAENTRY_H

#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include "NothingToShow.h" //todo: remove

/**
 * @brief Layout for entering coefficient values for a linear system
 * @extends QWidget, QGridLayout
 */
class LinearSystemDataEntry : public QWidget, private QGridLayout{

public:

    LinearSystemDataEntry() = delete;
    explicit LinearSystemDataEntry(int numEquations, int numVars, QWidget *parent);
private:

    int m_numEquations;
    int m_numVars;
};

#endif //MATRIX_OPERATIONS_LINEARSYSTEMDATAENTRY_H
