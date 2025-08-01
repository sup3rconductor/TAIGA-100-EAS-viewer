
#include "taigaviewer.h"
#include "ui_taigaviewer.h"


taigaviewer::taigaviewer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::taigaviewer)
{
    ui->setupUi(this);
}

taigaviewer::~taigaviewer()
{
    delete ui;
}


