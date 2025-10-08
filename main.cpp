////////////////////////////////////////////////////////////////
// ByteMachine
// Главный файл
////////////////////////////////////////////////////////////////
#include "main_window.h"
#include "type_defs.h"
#include <QApplication>

//==============================================================
// Главная функция
//==============================================================
int main(int argc, char **argv)
{
    QApplication a{argc, argv};

    qRegisterMetaType<ByteList>("ByteList");

    MainWindow w{};
    w.showMaximized();

    return a.exec();
}
