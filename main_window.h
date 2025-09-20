////////////////////////////////////////////////////////////////
// ByteMachine
// Главное окно
////////////////////////////////////////////////////////////////
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

//==============================================================
#include <QtWidgets>
#include "base_node.h"
#include "node_types.h"

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
    // Открыть проект
    void slotOpenProject();
    // Сохранить проект как
    void slotSaveProjectAs();

    // Функция вызывается при изменении видимости панели узлов
    void slotNodesPanelVisibleChanged(bool visible);
    // Функция вызывается при изменении видимости панели свойств
    void slotSettingsPanelVisibleChanged(bool visible);
    // Функция вызывается при изменении видимости сетки дизайнера
    void slotDesignerGridVisible(bool visible);
    // Функция вызывается при изменении видимости комментариев узлов
    void slotNodesCommentsVisibleChanged(bool visible);

    // Функция вызывается при выборе пункта главного меню "О программе"
    void slotShowAboutProg();
private slots:
    // Функция вызывается при изменении страницы панели с узлами
    void slotNodesPageChanged(int index);
    // Функция вызывается при добавлении узла через панель
    void slotAddNodeByType(NodeTypes nodeType);
    // Функция вызывается при добавлении узла
    void slotAddNode(ShPtrBaseNode node);
    // Функция вызывается при изменении свойства узла
    void slotChangedNodeProp(ShPtrBaseNode node, PropValue value);
    // Функция вызывается при удалении узла
    void slotRemoveNode(ShPtrBaseNode node);
    // Функция вызывается при изменении индекса текущего объекта
    // через комбо-бокс объектов
    void slotChangeCurrentObjectIndex(int index);
    // Функция вызывается при изменении выбранного узла
    void slotChangeSelectedNode(ShPtrBaseNode node);
    // Функция вызывается при измнения состояния стека отмен
    void slotUndoStackChanged();
    // Функция вызывается при нажатии на кнопку для показа списка отмен
    // (расположена на тул-баре)
    void slotShowUndoView();
private:
    // Функция вызывается при закрытия окна
    void closeEvent(QCloseEvent*) override;

    // Задание соединений
    void setConnections();
    // Создание виджета с настройками узла
    [[nodiscard]]
    QWidget* createNodeSettingsWidget(BaseNode *node);
    // Создание кнопки для тул-бара для вызова списка отмен
    [[nodiscard]]
    QPushButton* createUndoViewBtn() const;
    // Инициализация панели с узлами
    void initNodesPanel();
    // Создание вкладки Standart для панели Nodes
    [[nodiscard]]
    QWidget* createStandartPage();
    // Создание вкладки Visualization для панели Nodes
    [[nodiscard]]
    QWidget* createVisualizationPage();
    // Создание вкладки Script для панели Nodes
    [[nodiscard]]
    QWidget* createScriptPage();
    // Создание вкладки Other для панели Nodes
    [[nodiscard]]
    QWidget* createOtherPage();

    // Интерфейс пользователя
    Ui::MainWindow *ui_{nullptr};
    // Кнопка для показа списка отмен (добавляется на тул-бар)
    QPushButton *pushBtnShowUndoView_{nullptr};
    // Признак обработки узлов проектом (выставляется и
    // сбрасывается в некоторых слотах)
    bool isNodesProcessing_{false};
};

//==============================================================
#endif // MAIN_WINDOW_H
