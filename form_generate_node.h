////////////////////////////////////////////////////////////////
// ByteMachine
// Виджет для настройки узла "Generate"
////////////////////////////////////////////////////////////////
#ifndef FORM_GENERATE_NODE_H
#define FORM_GENERATE_NODE_H

//==============================================================
#include <QWidget>
#include "ui_form_generate_node.h"
#include "prop_value.h"

//==============================================================
namespace Ui
{
    class FormGenerateNode;
}
class GenerateNode;

//==============================================================
// Виджет для настройки узла "Generate"
//==============================================================
class FormGenerateNode : public QWidget
{
    Q_OBJECT
public:
    // Конструктор с параметром
    explicit FormGenerateNode(GenerateNode *node,
        QWidget *parent = nullptr);
    // Деструктор
    ~FormGenerateNode() override;
private slots:
    // Функция вызывается при изменении свойств узла
    void slotChangedNodeProp(PropValue value);
    // Функция вызывается при завершении редактирования имени
    void slotEditingFinishedName();
    // Функция вызывается при изменении типа генерации
    void slotChangedGenerateType(int index);
    // Сброс типа генерации
    void slotResetGenerateType();
    // Функция вызывается при завершении редактирования комментария
    void slotEditingFinishedComment();
    // Сброс комментария
    void slotResetComment();
private:
    // Задание узла
    void setNode(GenerateNode *node);
    // Задание соединений
    void setConnections();

    // Интерфейс пользователя
    Ui::FormGenerateNode ui_{};
    // Узел
    GenerateNode *node_{nullptr};
};

//==============================================================
#endif // FORM_GENERATE_NODE_H
