
#ifndef TAIGAVIEWER_H
#define TAIGAVIEWER_H

#include <QMainWindow>
#include "qcustomplot.h"

#include "autoplotbutton.h"

QT_BEGIN_NAMESPACE
namespace Ui { class taigaviewer; }
QT_END_NAMESPACE

class taigaviewer : public QMainWindow

{
    Q_OBJECT

public:
    taigaviewer(QWidget *parent = nullptr);
    ~taigaviewer();

    void SetupUI();

private:
    Ui::taigaviewer *ui;
    QCPColorMap *MatrColorMap;
    AutoPlotButton *autoBtn;

private slots:

};

#endif // TAIGAVIEWER_H
