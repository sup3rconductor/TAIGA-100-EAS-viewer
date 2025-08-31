
#include "taigaviewer.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);    
    taigaviewer w;
    w.show();
    return a.exec();
}
