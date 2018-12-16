#include <QApplication>
#include "wuziqi.h"

int main(int argc,char *argv[])
{
    QApplication app(argc,argv);
    wuziqi w;
    w.show();
    return app.exec();
}
