#include "StartFB.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartFB w;
    w.show();
    return a.exec();
}
