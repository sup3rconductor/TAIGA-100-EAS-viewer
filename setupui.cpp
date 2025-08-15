#include "taigaviewer.h"
#include "ui_taigaviewer.h"

void taigaviewer::SetupUI()
{
    /* SETTING UP SDF PLOT */

    //There will be many lines of code bcs I don't give a shit how to do this UI editor

    //Setup range and transparent background
    int MaxSDFX = 1000, MaxSDFY = 5000, MinSDF = 0;

    ui->SDFgraph->xAxis->setRange(MinSDF, MaxSDFX);
    ui->SDFgraph->yAxis->setRange(MinSDF, MaxSDFY);
    ui->SDFgraph->xAxis->rescale(true);
    ui->SDFgraph->yAxis->rescale(true);
    ui->SDFgraph->setBackground(Qt::GlobalColor::transparent);
    ui->SDFgraph->setAttribute(Qt::WA_OpaquePaintEvent, false);

    //Setup tick label colors
    QColor col = RGB(255, 255, 255);

    ui->SDFgraph->xAxis->setTickLabelColor(col);
    ui->SDFgraph->yAxis->setTickLabelColor(col);

    //Setup axis labels and grid
    QFont font;
    font.setPixelSize(16);
    font.setBold(false);
    font.setStyleName("Ubuntu");

    ui->SDFgraph->xAxis->setLabel("Distance from shower axis, m");
    ui->SDFgraph->yAxis->setLabel("Number of muons");
    ui->SDFgraph->xAxis->setLabelFont(font);
    ui->SDFgraph->yAxis->setLabelFont(font);
    ui->SDFgraph->xAxis->setLabelColor(col);
    ui->SDFgraph->yAxis->setLabelColor(col);

    ui->SDFgraph->xAxis->grid()->setPen(QPen(Qt::white));
    ui->SDFgraph->yAxis->grid()->setPen(QPen(Qt::white));

    //Setup axis tick labels font and size
    QPen CustomPen = ui->SDFgraph->xAxis->basePen();
    CustomPen.setColor(col);
    font.setPixelSize(14);

    ui->SDFgraph->xAxis->setTickLabelFont(font);
    ui->SDFgraph->xAxis->setTickPen(CustomPen);
    ui->SDFgraph->xAxis->setBasePen(CustomPen);
    ui->SDFgraph->xAxis->setSubTickPen(CustomPen);

    CustomPen = ui->SDFgraph->yAxis->basePen();
    CustomPen.setColor(col);

    ui->SDFgraph->yAxis->setTickLabelFont(font);
    ui->SDFgraph->yAxis->setTickPen(CustomPen);
    ui->SDFgraph->yAxis->setBasePen(CustomPen);
    ui->SDFgraph->yAxis->setSubTickPen(CustomPen);

    //Setup title
    QCPTextElement *SDFTitle = new QCPTextElement(ui->SDFgraph);
    SDFTitle->setText("Spatial distribution function of muons");
    SDFTitle->setTextColor(col);
    SDFTitle->setFont(QFont("Ubuntu", 16, QFont::Bold));

    ui->SDFgraph->plotLayout()->insertRow(0);
    ui->SDFgraph->plotLayout()->addElement(0, 0, SDFTitle);

    /* SETTING UP RESPONSE MATRIX */

    //Most operations on style setup are same as for SDF plot, so comments only on special features
    int MaxMatrX = 30, MaxMatrY = 40, MinMatr = 0;

    ui->RespMatr->xAxis->setRange(MinMatr, MaxMatrX);
    ui->RespMatr->yAxis->setRange(MinMatr, MaxMatrY);
    ui->RespMatr->setBackground(Qt::GlobalColor::transparent);
    ui->RespMatr->setAttribute(Qt::WA_OpaquePaintEvent, false);

    ui->RespMatr->xAxis->setTickLabelColor(col);
    ui->RespMatr->yAxis->setTickLabelColor(col);

    CustomPen = ui->RespMatr->xAxis->basePen();
    CustomPen.setColor(col);

    ui->RespMatr->xAxis->setTickLabelFont(font);
    ui->RespMatr->xAxis->setTickPen(CustomPen);
    ui->RespMatr->xAxis->setBasePen(CustomPen);
    ui->RespMatr->xAxis->setSubTickPen(CustomPen);

    CustomPen = ui->RespMatr->yAxis->basePen();
    CustomPen.setColor(col);

    ui->RespMatr->yAxis->setTickLabelFont(font);
    ui->RespMatr->yAxis->setTickPen(CustomPen);
    ui->RespMatr->yAxis->setBasePen(CustomPen);
    ui->RespMatr->yAxis->setSubTickPen(CustomPen);

    QCPTextElement *MatrTitle = new QCPTextElement(ui->RespMatr);
    MatrTitle->setText("Response matrix of CWD array");
    MatrTitle->setTextColor(col);
    MatrTitle->setFont(QFont("Ubuntu", 16, QFont::Bold));

    ui->RespMatr->plotLayout()->insertRow(0);
    ui->RespMatr->plotLayout()->addElement(0, 0, MatrTitle);

    //Allow rescaling the color scale whed zooming/dragging
    ui->RespMatr->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);

    //Setup color map
    MatrColorMap = new QCPColorMap(ui->RespMatr->xAxis, ui->RespMatr->yAxis);
    MatrColorMap->data()->setSize(MaxMatrX, MaxMatrY);
    MatrColorMap->data()->setRange(QCPRange(MinMatr, MaxMatrX), QCPRange(MinMatr, MaxMatrY));

    /* TEST BLOCK - DRAWING MATRIX */
    /*double x, y, z;
    for (int xIndex = MinMatr; xIndex < MaxMatrX; ++xIndex)
    {
        for (int yIndex = MinMatr; yIndex < MaxMatrY; ++yIndex)
        {
            MatrColorMap->data()->cellToCoord(xIndex, yIndex, &x, &y);
            double r = 3*qSqrt(x*x+y*y)+1e-2;
            z = 20*x*(qCos(r+2)/r-qSin(r+2)/r);
            MatrColorMap->data()->setCell(xIndex, yIndex, z);
        }
    }*/

    //Setup color scale
    QCPColorScale *MatrColorScale = new QCPColorScale(ui->RespMatr);
    ui->RespMatr->plotLayout()->addElement(1, 1, MatrColorScale);
    MatrColorScale->setType(QCPAxis::atRight);
    MatrColorMap->setColorScale(MatrColorScale);
    MatrColorScale->axis()->setLabel("Number of muons");
    MatrColorScale->axis()->setLabelFont(QFont("Ubuntu", 12, QFont::Normal));
    MatrColorScale->axis()->setLabelColor(col);
    MatrColorScale->axis()->setTickLabelFont(QFont("Ubuntu", 10, QFont::Normal));
    MatrColorScale->axis()->setTickLabelColor(col);

    //Add gradient to matrix and allow rescaling
    MatrColorMap->setGradient(QCPColorGradient::gpJet);
    MatrColorMap->rescaleDataRange();

    //Syncronize axes with color scale
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->RespMatr);
    ui->RespMatr->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    MatrColorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

    //Rescale axes so the whole color map is visible
    ui->RespMatr->rescaleAxes();

    //Set text to min and max x and y values linedits
    ui->MinX->setText(QString::number(MinSDF));
    ui->MinY->setText(QString::number(MinSDF));
    ui->MaxX->setText(QString::number(MaxSDFX));
    ui->MaxY->setText(QString::number(MaxSDFY));
    ui->EvNum->setText(QString::number(0));
}




