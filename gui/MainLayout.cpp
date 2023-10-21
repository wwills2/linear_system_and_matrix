//
// Created by zan on 10/14/23.
//

#include "MainLayout.h"

#define UPPER 0, 0
#define LOWER 1, 0

MainLayout::MainLayout(QWidget *parent) {

    Q_UNUSED(parent)

    m_dataEntryWidget = new NothingToShow();
    m_resultsWidget = new NothingToShow();
    addWidget(m_dataEntryWidget, UPPER);
}
