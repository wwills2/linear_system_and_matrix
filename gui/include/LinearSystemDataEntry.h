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
#include "../../libmatrix/Matrix.h"

/**
 * @brief Layout for entering coefficient values for a linear system
 */
class LinearSystemDataEntry : public IntfDataEntry, public QWidget{

public:

    LinearSystemDataEntry() = delete;

    /**
     * constructor for the linear system data entry view. generates a grid of text edits annotated with the
     * appropriate coefficient (x0 ... xn)
     * @param numEquations number of equations in the linear system
     * @param numVars number of variables in the linear system. does not include constants left of the equals
     * @param parent parent view
     */
    explicit LinearSystemDataEntry(int numEquations, int numVars, QWidget *parent);

    /**
     * loads the data in the linear system view into a matrix object in the matrix manager
     * @param matrixManager the matrix manager instance
     * @return true if load successful
     */
    bool loadUiData(wwills2::MatrixManager &matrixManager) override;

    /**
     * defines a valid numerical decimal or rational input
     */
    const QRegExp m_regEx;
    const std::string m_matrixName = "matrix";
private:

    int m_numEquations;
    /**
     * number of variables + 1 to account for constant to right of =
     */
    int m_numEdits;
    std::vector<QLineEdit *> m_lineEdits;
    QGridLayout *m_entryGrid;
};

#endif //MATRIX_OPERATIONS_LINEARSYSTEMDATAENTRY_H
