////////////////////////////////////////////////////////////////
// ByteMachine
// Виджет узла на панели узлов
////////////////////////////////////////////////////////////////
#ifndef FORM_NODE_PANEL_ITEM_H
#define FORM_NODE_PANEL_ITEM_H

//==============================================================
#include <QWidget>
#include "node_types.h"

//==============================================================
// Виджет узла на панели узлов
//==============================================================
class FormNodePanelItem final : public QWidget
{
    Q_OBJECT
public:
    // Конструктор с параметром
    explicit FormNodePanelItem(NodeTypes nodeType,
        QWidget *parent = nullptr);
    // Деструктор
    ~FormNodePanelItem() override;

    // Получение типа узла
    [[nodiscard]]
    NodeTypes nodeType() const { return nodeType_; }
signals:
    // Функция вызывается при нажатии на элемент
    void sigClicked(NodeTypes nodeType);
    // Функция вызывается при перетаскивании узла
    void sigDragNode(NodeTypes type, const QPoint &pos);
    // Функция вызывается при отпускании перетаскиваемого узла
    void sigDropNode(NodeTypes type, const QPoint &pos);
private:
    // Функция перерисовки
    void paintEvent(QPaintEvent *event) override;
    // Функция вызывается при заходе мыши на виджет
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    void enterEvent(QEvent *event) override;
#else
    void enterEvent(QEnterEvent *event) override;
#endif // QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    // Функция вызывается при покидании виджета мышью
    void leaveEvent(QEvent *event) override;
    // Функция вызывается при нажатии кнопки мыши
    void mousePressEvent(QMouseEvent *event) override;
    // Функция вызывается при перемещении мыши
    void mouseMoveEvent(QMouseEvent *event) override;
    // Функция вызывается при отпускании кнопки мыши
    void mouseReleaseEvent(QMouseEvent *event) override;

    // Начало перетаскивания
    void startDrag();

    // Тип узла
    NodeTypes nodeType_{NodeTypes::Generate};
    // Начальная координата перетаскивания
    QPoint beginDragPos_{};
};

//==============================================================
#endif // FORM_NODE_PANEL_ITEM_H
