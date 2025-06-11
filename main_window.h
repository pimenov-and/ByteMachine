////////////////////////////////////////////////////////////////
// ByteMachine
// Главное окно
////////////////////////////////////////////////////////////////
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

//==============================================================
#include <QtWidgets>

//==============================================================
QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

//==============================================================
// Главное окно
//==============================================================
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    // Конструктор с параметром
    MainWindow(QWidget *parent = nullptr);
    // Деструктор
    ~MainWindow() override;
private slots:
    // Сохранить проект как...
    void slotSaveProjectAs();

    // Функция вызывается при изменении видимости панели узлов
    void slotNodesPanelVisibleChanged(bool visible);
    // Функция вызывается при изменении видимости панели свойств
    void slotSettingsPanelVisibleChanged(bool visible);
    // Функция вызывается при изменении видимости сетки дизайнера
    void slotDesignerGridVisible(bool visible);

    // Функция вызывается при выборе пункта главного меню "О программе"
    void slotShowAboutProg();
private:
    // Задание соединений
    void setConnections();
    // Инициализация панели с узлами
    void initNodesPanel();
    // Создание вкладки Standart для панели Nodes
    QWidget* createStandartPage();
    // Создание вкладки Visualization для панели Nodes
    QWidget* createVisualizationPage();
    // Создание вкладки Script для панели Nodes
    QWidget* createScriptPage();
    // Создание вкладки Other для панели Nodes
    QWidget* createOtherPage();

    // Интерфейс пользователя
    Ui::MainWindow *ui_{nullptr};
};

//==============================================================
#endif // MAIN_WINDOW_H
