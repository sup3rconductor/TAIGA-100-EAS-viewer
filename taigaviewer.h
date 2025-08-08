
#ifndef TAIGAVIEWER_H
#define TAIGAVIEWER_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "autoplotbutton.h"

#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class taigaviewer; }
QT_END_NAMESPACE

class taigaviewer : public QMainWindow

{
    Q_OBJECT

public:
    taigaviewer(QWidget *parent = nullptr);
    ~taigaviewer();

private:
    Ui::taigaviewer *ui;
    QCPColorMap *MatrColorMap;
    AutoPlotButton *autoBtn;

    QVector<double> Dist, NumMu;
    double CWDArr[30][40] = { 0 };
    double EASParams[6];
    int EventNum = -1;

protected:
    void SetupUI();
    void keyPressEvent(QKeyEvent* ev) override;
    void ReadEventData();
    void SetEASParameters();

private slots:
    void EventSwitch();
    void DrawSDF();
    void DrawMatrix();
    void RefreshPlots();

};

#endif // TAIGAVIEWER_H
