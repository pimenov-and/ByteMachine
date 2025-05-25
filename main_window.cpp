////////////////////////////////////////////////////////////////
// ByteMachine
// Главное окно
////////////////////////////////////////////////////////////////
#include "main_window.h"
#include "ui_main_window.h"
#include "dialog_about_prog.h"

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

    setConnections();
}

//==============================================================
// Деструктор
//==============================================================
MainWindow::~MainWindow()
{
    delete ui_;
}

//==============================================================
// Функция вызывается при выборе пункта главного меню "О программе"
//==============================================================
void MainWindow::slotShowAboutProg()
{
    DialogAboutProg dlg{this};
    dlg.exec();
}

//==============================================================
// Задание соединений
//==============================================================
void MainWindow::setConnections()
{
    connect(ui_->actAboutProg_, &QAction::triggered,
        this, &MainWindow::slotShowAboutProg);
}
