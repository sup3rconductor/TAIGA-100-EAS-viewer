
#ifndef TAIGAVIEWER_H
#define TAIGAVIEWER_H

#include <QMainWindow>



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
};

#endif // TAIGAVIEWER_H
