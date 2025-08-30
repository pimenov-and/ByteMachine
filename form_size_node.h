////////////////////////////////////////////////////////////////
// ByteMachine
// Форма для настройки узла Size
////////////////////////////////////////////////////////////////
#ifndef FORM_SIZE_NODE_H
#define FORM_SIZE_NODE_H

//==============================================================
#include <QWidget>
#include "size_node.h"

//==============================================================
namespace Ui
{
    class FormSizeNode;
}

//==============================================================
// Форма для настройки узла Size
//==============================================================
class FormSizeNode : public QWidget
{
    Q_OBJECT
public:
    // Конструктор с параметром
    explicit FormSizeNode(SizeNode *node, QWidget *parent = nullptr);
    // Деструктор
    ~FormSizeNode() override;
private slots:
    // Функция вызывается при изменении свойств узла
    void slotChangedNodeProp(PropValue value);
    // Функция вызывается при завершении редактирования имени
    void slotEditingFinishedName();
    // Функция вызывается при изменении размерности
    void slotChangedUnit(int index);
    // Сброс размерности
    void slotResetUnit();
    // Функция вызывается при изменении признака пропуска узла
    void slotChangedBypass(int state);
    // Сброс признака пропуска узла
    void slotResetBypass();
    // Функция вызывается при изменении признак кеширования узла
    void slotChangedCaching(int state);
    // Сброс признака кеширования
    void slotResetCaching();
    // Функция вызывается при завершении редактирования комментария
    void slotEditingFinishedComment();
    // Сброс комментария
    void slotResetComment();
private:
    // Задание узла
    void setNode(SizeNode *node);
    // Задание соединений
    void setConnections();

    // Интерфейс пользователя
    Ui::FormSizeNode *ui_{nullptr};
    // Узел
    SizeNode *node_{nullptr};
};

//==============================================================
#endif // FORM_SIZE_NODE_H
