//
// Created by zan on 10/14/23.
//

#ifndef MATRIX_OPERATIONS_MAINLAYOUT_H
#define MATRIX_OPERATIONS_MAINLAYOUT_H

#include <QGridLayout>
#include "NothingToShow.h"

QT_BEGIN_NAMESPACE
class QWidget;
QT_END_NAMESPACE

/**
 * @brief Layout instantiated in the main window
 * @extends QGridLayout
 */
class MainLayout : public QGridLayout{
    Q_OBJECT

public:

    explicit MainLayout(QWidget *parent = 0);


private:

    QWidget *m_dataEntryWidget;
    QWidget *m_resultsWidget;
};

#endif //MATRIX_OPERATIONS_MAINLAYOUT_H
