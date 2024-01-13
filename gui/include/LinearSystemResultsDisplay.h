//
// Created by zan on 11/4/23.
//

#ifndef MATRIX_OPERATIONS_LINEARSYSTEMRESULTSDISPLAY_H
#define MATRIX_OPERATIONS_LINEARSYSTEMRESULTSDISPLAY_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <sstream>
#include <iomanip>
#include <QTextEdit>

#include "IntfResultsDisplay.h"
#include "libmatrix/Matrix.h"

/**
 * @brief Layout for displaying a reduced linear system
 */
class LinearSystemResultsDisplay : public IntfResultsDisplay, public QWidget{
public:
    LinearSystemResultsDisplay() = delete;

    /**
     * constructor for the view to display the result of the linear system reduction
     * @param parent the parent widget
     */
    explicit LinearSystemResultsDisplay(QWidget *parent);

    /**
     * loads, formats, and displays the reduced linear
     * @param matrixManager the matrix manager instance
     * @return true if successful
     */
    bool setResultsUiData(wwills2::MatrixManager &matrixManager) override;

    const std::string m_matrixName = "matrix";
private:

    /**
     * determines how many characters should be displayed for decimal values
     * @param matrix to use for calculation
     */
    void calcNumDisplayCharacters(wwills2::Matrix &matrix);
    std::string getFormattedQString(const mpq_class &element) const;

    size_t m_numDisplayCharacters;
    QGridLayout *m_displayGrid;
};


#endif //MATRIX_OPERATIONS_LINEARSYSTEMRESULTSDISPLAY_H
