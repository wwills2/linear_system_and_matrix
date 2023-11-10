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
#include "../Matrix.h"

class LinearSystemResultsDisplay : public IntfResultsDisplay, public QWidget{
public:
    LinearSystemResultsDisplay() = delete;
    explicit LinearSystemResultsDisplay(QWidget *parent);

    bool setResultsUiData(wwills2::MatrixManager &matrixManager) override;

    const std::string m_matrixName = "matrix";
private:

    void calcNumDisplayCharacters(wwills2::Matrix &matrix);
    std::string getFormattedQstring(const mpq_class &element) const;

    size_t m_numDisplayCharacters;
    QGridLayout *m_displayBox;
};


#endif //MATRIX_OPERATIONS_LINEARSYSTEMRESULTSDISPLAY_H
