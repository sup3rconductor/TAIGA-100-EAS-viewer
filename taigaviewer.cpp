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

    //Creating autoplot button
    autoBtn = new AutoPlotButton(parent);
    QVector<QString> AutoBtnCols = {"4b4b4b", "#519fc7", "#519fc7", "#ffffff"};
    autoBtn->SetColors(AutoBtnCols);

    //Connectring buttons with signals
    connect(ui->PrevEvent, SIGNAL(clicked()), this, SLOT(EventSwitch()));
    connect(ui->NextEvent, SIGNAL(clicked()), this, SLOT(EventSwitch()));
    connect(ui->ShowMatr, SIGNAL(clicked()), this, SLOT(DrawMatrix()));
    connect(ui->ShowSDF, SIGNAL(clicked()), this, SLOT(DrawSDF()));
    connect(ui->Refresh, SIGNAL(clicked()), this, SLOT(RefreshPlots()));

    ui->PrevEvent->setCheckable(true);
    ui->NextEvent->setCheckable(true);
    ui->ShowMatr->setCheckable(true);
    ui->ShowSDF->setCheckable(true);
    ui->Refresh->setCheckable(true);

    //Setup SDF plot and response matrix
    SetupUI();
}

taigaviewer::~taigaviewer()
{
    delete ui;
    delete MatrColorMap;
    delete autoBtn;
}

//Function to read event data
//Event number is stored in private taigaviewer class field
void taigaviewer::ReadEventData()
{

}

//Function to create SDF from data
void taigaviewer::CreateSDF()
{

}

//Function to create response matrix from data
void taigaviewer::CreateMatrix()
{

}

//Function to write EAS parameters inside text labels
void taigaviewer::SetEASParameters()
{

}

//Function to setup limits on SDF plot axis values
void taigaviewer::SetSDFLimits()
{

}

//Function to switch events
void taigaviewer::EventSwitch()
{

}

//Function to draw SDF on plot
void taigaviewer::DrawSDF()
{

}

//Function to draw response matrix on plot
void taigaviewer::DrawMatrix()
{

}

//Function to refresh plots
void taigaviewer::RefreshPlots()
{

}

//Enter event number with keyboard (realization will be later)
void taigaviewer::keyPressEvent(QKeyEvent *ev)
{

}
