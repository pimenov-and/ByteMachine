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
// Функция вызывается при изменении видимости панели узлов
//==============================================================
void MainWindow::slotNodesPanelVisibleChanged(bool visible)
{
    ui_->groupBoxNodes_->setVisible(visible);
}

//==============================================================
// Функция вызывается при изменении видимости панели свойств
//==============================================================
void MainWindow::slotSettingsPanelVisibleChanged(bool visible)
{
    ui_->groupBoxSettings_->setVisible(visible);
}

//==============================================================
// Функция вызывается при изменении видимости сетки дизайнера
//==============================================================
void MainWindow::slotDesignerGridVisible(bool visible)
{
    ui_->widgetDesigner_->setGridVisible(visible);
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
    // Меню "File"

    // Меню "Edit"

    // Меню "Settings"
    connect(ui_->actVisibleNodesPanel_, &QAction::triggered,
        this, &MainWindow::slotNodesPanelVisibleChanged);
    connect(ui_->actVisibleSettingsPanel_, &QAction::triggered,
        this, &MainWindow::slotSettingsPanelVisibleChanged);
    connect(ui_->actVisibleDesignerGrid_, &QAction::triggered,
            this, &MainWindow::slotDesignerGridVisible);

    // Меню "Tools"

    // Меню "Help"
    connect(ui_->actAboutProg_, &QAction::triggered,
        this, &MainWindow::slotShowAboutProg);
}
