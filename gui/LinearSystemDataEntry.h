//
// Created by zan on 10/20/23.
//

#ifndef MATRIX_OPERATIONS_LINEARSYSTEMDATAENTRY_H
#define MATRIX_OPERATIONS_LINEARSYSTEMDATAENTRY_H

#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QGroupBox>

#include "IntfDataEntry.h"
#include "../Matrix.h"

/**
 * @brief Layout for entering coefficient values for a linear system
 * @extends QWidget
 */
class LinearSystemDataEntry : public IntfDataEntry, public QWidget{

public:

    LinearSystemDataEntry() = delete;
    explicit LinearSystemDataEntry(int numEquations, int numVars, QWidget *parent);

    bool loadUiData(wwills2::MatrixManager &matrixManager) override;

    const std::string m_matrixName = "matrix";
private:

    int m_numEquations;
    int m_numEdits;
    std::vector<QLineEdit *> m_lineEdits;
    QGridLayout *m_entryGrid;
};

#endif //MATRIX_OPERATIONS_LINEARSYSTEMDATAENTRY_H
