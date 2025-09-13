////////////////////////////////////////////////////////////////
// ByteMachine
// Виджет дизайнера
////////////////////////////////////////////////////////////////
#ifndef FORM_DESIGNER_H
#define FORM_DESIGNER_H

//==============================================================
#include <QtWidgets>
#include <QPoint>
#include "base_node.h"
#include "ui_form_designer.h"

//==============================================================
namespace Ui
{
    class FormDesigner;
}

//==============================================================
// Виджет дизайнера
//==============================================================
class FormDesigner : public QWidget
{
    Q_OBJECT
public:
    // Конструктор с параметром
    explicit FormDesigner(QWidget *parent = nullptr);
    // Деструктор
    ~FormDesigner() override;

    // Получение видимости сетки
    [[nodiscard]]
    bool isGridVisible() const { return isGridVisible_; }
    // Задание видимости сетки
    void setGridVisible(bool visible);
private slots:
    // Добавление узла через контекстное меню
    void slotAddNodeFromContextMenu();
    // Удаление узла через контекстное меню
    void slotRemoveNodeFromContextMenu();
private:
    // Функция вызывается при перерисовке
    void paintEvent(QPaintEvent *event) override;
    // Функция вызывается при нажатии мыши
    void mousePressEvent(QMouseEvent *event) override;
    // Функция вызвается при перемещении мыши
    void mouseMoveEvent(QMouseEvent *event) override;
    // Функция вызывается при отпускании мыши
    void mouseReleaseEvent(QMouseEvent *event) override;
    // Функция вызывается при показе контекстного меню
    void contextMenuEvent(QContextMenuEvent *event) override;
    // Функция вызывается при приёме перетаскиваемого узла
    void dragEnterEvent(QDragEnterEvent *event) override;
    // Функция вызывается при отпускании перетаскиваемого узла
    void dropEvent(QDropEvent *event) override;

    // Задание соединений
    void setConnections();
    // Заливка фона
    void fillBackgound(QPainter *painter, const QRect &clipRect) const;
    // Вывод сетки
    void drawGrid(QPainter *painter) const;
    // Вывод узлов
    void drawNodes(QPainter *painter) const;
    // Задание размера символа
    void setCharSize(QPainter *painter);

    // Создание контекстного меню
    [[nodiscard]]
    QMenu* createContextMenu() const;
    // Создание контекстного меню узлов "Standart"
    [[nodiscard]]
    QMenu* createStandartNodesContextMenu() const;
    // Создание контекстного меню узлов "Visualization"
    [[nodiscard]]
    QMenu* createVisualizationNodesContextMenu() const;
    // Создание контекстного меню узлов "Script"
    [[nodiscard]]
    QMenu* createScriptNodesContextMenu() const;
    // Создание контекстного меню узлов "Other"
    [[nodiscard]]
    QMenu* createOtherNodesContextMenu() const;
    // Создание контекстного меню узла
    [[nodiscard]]
    QMenu* createNodeContextMenu() const;

    // Интерфейс пользователя
    Ui::FormDesigner ui_{};
    // Перемещаемый узел
    ShPtrBaseNode movingNode_{};
    // Смещение при захвате перетаскиваемого узла
    QPoint movingDragOffsetNode_{};
    // Видимость сетки
    bool isGridVisible_{true};
    // Положение меню
    QPoint menuPos_{};

    // Признак перетаскивания узла
    bool isDragNode_{false};
    // Позиция перетаскиваемого узла
    QPoint dragNodePos_{};
};

//==============================================================
#endif // FORM_DESIGNER_H
