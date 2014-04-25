#include "view/d3helper.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    D3Helper w;
    w.show();

    return a.exec();
}
