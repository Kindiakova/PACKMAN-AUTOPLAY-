#include "mainwindow.h"
#include <QApplication>
#include "options.h"
void generate_map();

int main(int argc, char *argv[])
{
    if (GENERETE_MAP) generate_map();
    QApplication a(argc, argv);
    MainWindow w;
    w.setStyleSheet("QMainWindow {background: 'black';}");
    w.show();
    return a.exec();
}
