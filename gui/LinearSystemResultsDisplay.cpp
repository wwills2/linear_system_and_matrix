//
// Created by zan on 11/4/23.
//

#include "LinearSystemResultsDisplay.h"
#include "../Matrix.h"

#define NUM_DECIMAL_PLACES (char) 3

LinearSystemResultsDisplay::LinearSystemResultsDisplay(QWidget *parent) : QWidget(parent), m_numDisplayCharacters(0){

    m_displayBox = new QGridLayout(parent);

    QSizePolicy qSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setSizePolicy(qSizePolicy);
}

bool LinearSystemResultsDisplay::setResultsUiData(wwills2::MatrixManager &matrixManager) {

    QString formattedDisplayString = "";
    auto matrixToLoad = matrixManager.getMatrix(m_matrixName);
    int cols = matrixToLoad->getDimensions()->numColumns;

    calcNumDisplayCharacters(*matrixToLoad);

    /*
    int i = 0;
    for (auto &element : *matrixToLoad){
        QString stringFormattedElement(getFormattedQstring(element).c_str());

        if (i == 0){
            formattedDisplayString += "\t";
        }

        if (i == cols - 1){
            formattedDisplayString += stringFormattedElement + "\t\n";
            i = 0;
        }else if (i == cols - 2){
            formattedDisplayString += stringFormattedElement + " x" + QString::number(i) + "\t=\t";
            i++;
        }else{
            formattedDisplayString += stringFormattedElement + " x" + QString::number(i) + "  +  ";
            i++;
        }
    }
     */

    for (int i = 0; i < 500; i++){
        for (int j = 0; j < 500; j++){
            formattedDisplayString += "a";
        }
        formattedDisplayString += "\n";
    }

    auto *displayLabel = new QLabel;
    displayLabel->setText(formattedDisplayString);

    m_displayBox->addWidget(displayLabel);

    return true;
}

void LinearSystemResultsDisplay::calcNumDisplayCharacters(wwills2::Matrix &matrix) {

    //todo: openMP parallelism
    mpq_class largestEntry(0);
    for (auto &element : matrix){
        if (abs(element) > largestEntry){
            largestEntry = abs(element);
        }
    }

    std::stringstream largestNumAsStringStream;
    largestNumAsStringStream << std::setprecision(NUM_DECIMAL_PLACES) << std::fixed;
    largestNumAsStringStream << largestEntry.get_d();

    m_numDisplayCharacters = largestNumAsStringStream.str().size() + 1; // +1 to account for possible negative sign
}

std::string LinearSystemResultsDisplay::getFormattedQstring(const mpq_class &element) const {

    std::stringstream stringReprStream;
    stringReprStream << std::setprecision(NUM_DECIMAL_PLACES) << std::fixed;
    stringReprStream << element.get_d();

    auto stringRepr = stringReprStream.str();
    std::string prependingPad(m_numDisplayCharacters - stringRepr.size(), ' ');

    return prependingPad + stringRepr;
}
