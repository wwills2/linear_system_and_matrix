//
// Created by zan on 11/4/23.
//

#include "LinearSystemResultsDisplay.h"
#include "../Matrix.h"

#define NUM_DECIMAL_PLACES (char) 3

LinearSystemResultsDisplay::LinearSystemResultsDisplay(QWidget *parent) : QLabel(parent), m_numDisplayCharacters(0){

    QSizePolicy qSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setSizePolicy(qSizePolicy);
}

bool LinearSystemResultsDisplay::setResultsUiData(wwills2::MatrixManager &matrixManager) {

    QString formattedDisplayString = "";
    auto matrixToLoad = matrixManager.getMatrix(m_matrixName);
    int cols = matrixToLoad->getDimensions()->numColumns;

    calcNumDisplayCharacters(*matrixToLoad);

    int i = 0;
    for (auto &element : *matrixToLoad){
        QString stringFormattedElement(getFormattedQstring(element).c_str());

        if (i == 0){
            formattedDisplayString + "\t";
        }

        if (i == cols - 1){
            formattedDisplayString + stringFormattedElement + "\t\n";
            i = 0;
        }else if (i == cols - 2){
            formattedDisplayString + stringFormattedElement + " x" + QString::number(i) + "\t=\t";
            i++;
        }else{
            formattedDisplayString + stringFormattedElement + " x" + QString::number(i) + "  +  ";
            i++;
        }
    }

    setText(formattedDisplayString);
    return true;
}

void LinearSystemResultsDisplay::calcNumDisplayCharacters(wwills2::Matrix &matrix) {

    //todo: openMP parallelism
    mpq_class largestEntry(0);
    for (auto &element : matrix){
        if (element > largestEntry){
            largestEntry = element;
        }
    }

    auto largestNumAsString = std::to_string(largestEntry.get_d());
    auto eraseIt = std::find(largestNumAsString.begin(), largestNumAsString.end(), '.');

    if (eraseIt == largestNumAsString.end()){
        m_numDisplayCharacters = largestNumAsString.size() + NUM_DECIMAL_PLACES;
    }else{
        eraseIt += NUM_DECIMAL_PLACES;
        largestNumAsString.erase(eraseIt, largestNumAsString.end());
        m_numDisplayCharacters = largestNumAsString.size();
    }
}

std::string LinearSystemResultsDisplay::getFormattedQstring(const mpq_class &element) const {

    auto stringRepr= std::to_string(element.get_d());

    int numZeroPad = NUM_DECIMAL_PLACES;
    auto it = std::find(stringRepr.begin(), stringRepr.end(), '.');

    while (it != stringRepr.end()){
        numZeroPad--;
        it++;
    }

    stringRepr.erase(it, stringRepr.end());

    std::string trailingPad(numZeroPad, '0');
    std::string prependingPad(m_numDisplayCharacters - stringRepr.size(), ' ');

    return prependingPad + stringRepr + trailingPad;
}
