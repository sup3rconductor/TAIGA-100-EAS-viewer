#include "taigaviewer.h"
#include "ui_taigaviewer.h"
#include "autoplotbutton.h"

#include <QVector>
#include <QString>
#include <QMessageBox>
#include <sstream>
#include <fstream>
#include <string>

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
    //Make warning message if one of the files is not opened
    std::stringstream WarningMessage;

    //Make path to SDF data
    std::ostringstream Path;
    Path << "E:\\TAIGA_EAS\\PostAnalysis\\EAS_" << EventNum << ".dat";

    //Clear vectors with SDF data
    double distance;
    int NumOfMuons;

    for(int i = 0; i < 6; i++)
        EASParams[i] = 0;

    Dist.clear();
    NumMu.clear();

    //Open file with SDF data and read it
    std::ifstream SDF_file;

    SDF_file.open(Path.str(), std::ios_base::in);
    bool sdf_flag = SDF_file.is_open();
    if(sdf_flag)
    {
        SDF_file >> EASParams[0] >> EASParams[1] >> EASParams[2] >> EASParams[3] >> EASParams[4] >> EASParams[5];

        while(SDF_file >> distance >> NumOfMuons)
        {
            Dist.push_back(distance);
            NumMu.push_back(double(NumOfMuons));
        }
    }

    //else qDebug() << "Unable to open SDF file #" << EventNum;

    SDF_file.close();
    Path.str("");
    Path.clear();

    //Make path to matrix data
    Path << "E:\\TAIGA_EAS\\PostAnalysis\\Matrix_" << EventNum << ".dat";

    //Clear arrays with response matrix data
    int idxX, idxY;
    double NumPE;

    for(int i = 0; i < 30; i++)
    {
        for(int j = 0; j < 40; j++)
        {
            CWDArr[i][j] = 0;
        }
    }

    //Open file with matrix data and read it
    std::ifstream Matrix_file;

    Matrix_file.open(Path.str(), std::ios_base::in);
    bool matr_flag = Matrix_file.is_open();
    if(matr_flag)
    {
        while(Matrix_file >> idxX >> idxY >> NumPE)
            CWDArr[idxX][idxY] = NumPE;
    }

    Matrix_file.close();
    Path.str("");
    Path.clear();


    if(!sdf_flag || !matr_flag)
    {
        if(!sdf_flag) WarningMessage << "Unable to open SDF file №" << EventNum << std::endl;
        if(!matr_flag) WarningMessage << "Unable to open Matrix file №" << EventNum << std::endl;
        QMessageBox::warning(this, tr("Event manager"), tr((WarningMessage.str()).c_str()));
        return;
    }
}

//Function to write EAS parameters inside text labels
void taigaviewer::SetEASParameters()
{
    ui->PrEnergy->setText(QString::number(EASParams[0]));
    ui->Zenith->setText(QString::number(EASParams[1]));
    ui->Azimuth->setText(QString::number(EASParams[2]));
    ui->Xaxis->setText(QString::number(EASParams[3]));
    ui->Yaxis->setText(QString::number(EASParams[4]));
    ui->NumCWD->setText(QString::number(EASParams[5]));
}

//Function to switch events
void taigaviewer::EventSwitch()
{
    //Checking state of autoplot button
    //If it's on plots will change automatically when PrevEvent of NextEvent button is pressed
    int AutoButtonState = autoBtn->GetStatus();

    if(ui->PrevEvent->isChecked() && EventNum > 0)
    {
        EventNum--;
        ui->EvNum->setText(QString::number(EventNum));

        ReadEventData();

        if(AutoButtonState == 1)
        {
            DrawSDF();
            DrawMatrix();
        }

        ui->PrevEvent->setChecked(true);
    }

    if(ui->NextEvent->isChecked() && EventNum < 10000)
    {
        EventNum++;
        ui->EvNum->setText(QString::number(EventNum));

        ReadEventData();

        if(AutoButtonState == 1)
        {
            DrawSDF();
            DrawMatrix();
        }

        ui->NextEvent->setChecked(true);
    }

    ui->PrevEvent->setChecked(false);
    ui->NextEvent->setChecked(false);
}

//Function to draw SDF on plot
void taigaviewer::DrawSDF()
{
    ui->SDFgraph->clearGraphs();
    ui->SDFgraph->addGraph();

    ui->SDFgraph->graph(0)->setData(Dist, NumMu);
    ui->SDFgraph->graph(0)->setPen(QPen(Qt::red));
    ui->SDFgraph->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->SDFgraph->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 2));

    ui->SDFgraph->replot();
}

//Function to draw response matrix on plot
void taigaviewer::DrawMatrix()
{
    ui->RespMatr->clearGraphs();
    ui->RespMatr->addGraph();

    for(int xIndex = 0; xIndex < 30; xIndex++)
    {
        for(int yIndex = 0; yIndex < 40; yIndex++)
        {
            MatrColorMap->data()->setCell(xIndex, yIndex, CWDArr[xIndex][yIndex]);
        }
    }

    ui->RespMatr->replot();
}

//Function to refresh plots
void taigaviewer::RefreshPlots()
{
    std::string MinXVal = ui->MinX->text().toStdString();
    std::string MinYVal = ui->MinY->text().toStdString();
    std::string MaxXVal = ui->MaxX->text().toStdString();
    std::string MaxYVal = ui->MaxY->text().toStdString();
    std::string EventNumber = ui->EvNum->text().toStdString();

    if(MinXVal.find_first_not_of("0123456789") != std::string::npos || MinXVal.empty())
    {
        QMessageBox::warning(this, tr("Plot range manager"), tr("Value in 'Min. y' label is not digit"));
        return;
    }

    if(MinYVal.find_first_not_of("0123456789") != std::string::npos || MinYVal.empty())
    {
        QMessageBox::warning(this, tr("Plot range manager"), tr("Value in 'Min. y' label is not digit"));
        return;
    }

    if(MaxXVal.find_first_not_of("0123456789") != std::string::npos || MaxXVal.empty())
    {
        QMessageBox::warning(this, tr("Plot range manager"), tr("Value in 'Max. x' label is not digit"));
        return;
    }

    if(MaxYVal.find_first_not_of("0123456789") != std::string::npos || MaxYVal.empty())
    {
        QMessageBox::warning(this, tr("Plot range manager"), tr("Value in 'Max. y' label is not digit"));
        return;
    }

    if(EventNumber.find_first_not_of("0123456789") != std::string::npos || EventNumber.empty())
    {
        QMessageBox::warning(this, tr("Event manager"), tr("Value in 'Event number' label is not digit"));
        return;
    }

    else
    {
        double XMin = std::stod(MinXVal.c_str());
        double YMin = std::stod(MinYVal.c_str());
        double XMax = std::stod(MaxXVal.c_str());
        double YMax = std::stod(MaxYVal.c_str());
        EventNum = std::stod(EventNumber.c_str());

        ui->SDFgraph->xAxis->setRange(XMin, XMax);
        ui->SDFgraph->yAxis->setRange(YMin, YMax);

        ReadEventData();
        DrawSDF();
    }

}

//Enter event number with keyboard (realization will be later)
void taigaviewer::keyPressEvent(QKeyEvent *ev)
{

}
