#include "taigaviewer.h"
#include "ui_taigaviewer.h"
#include "autoplotbutton.h"

#include <QVector>

taigaviewer::taigaviewer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::taigaviewer)
{
//    this->setWindowFlags(Qt::FramelessWindowHint);
//    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->setupUi(this);

    autoBtn = new AutoPlotButton(parent);
    QVector<QString> AutoBtnCols = {"4b4b4b", "#519fc7", "#519fc7", "#ffffff"};
    autoBtn->SetColors(AutoBtnCols);

    SetupUI();
}

taigaviewer::~taigaviewer()
{
    delete ui;
    delete MatrColorMap;
    delete autoBtn;
}


