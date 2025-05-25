////////////////////////////////////////////////////////////////
// ByteMachine
// Главное окно
////////////////////////////////////////////////////////////////
#include "main_window.h"
#include "ui_main_window.h"

//==============================================================
// Конструктор с параметром
//==============================================================
MainWindow::MainWindow(QWidget *parent) : QMainWindow{parent},
    ui_{new Ui::MainWindow{}}
{
    ui_->setupUi(this);

    // Показ версии в заголовке окна
    const QString version = QString{"%1 %2"}.arg("ByteMachine", APP_VERSION);
    setWindowTitle(version);
}

//==============================================================
// Деструктор
//==============================================================
MainWindow::~MainWindow()
{
    delete ui_;
}
