////////////////////////////////////////////////////////////////
// ByteMachine
// Команда отмены удаления узла
////////////////////////////////////////////////////////////////
#ifndef UNDO_REMOVE_NODE_H
#define UNDO_REMOVE_NODE_H

//==============================================================
#include <QUndoCommand>
#include "base_node.h"
#include "input_pin.h"
#include "output_pin.h"

//==============================================================
class Project;

//==============================================================
// Команда отмены удаления узла
//==============================================================
class UndoRemoveNode : public QUndoCommand
{
public:
    // Конструктор с параметрами
    UndoRemoveNode(Project *project, const ShPtrBaseNode &node);
    // Деструктор
    ~UndoRemoveNode() override;

    // Функция отмены
    void undo() override;
    // Функция восстановления
    void redo() override;
private:
    // Инициализация подключенных к узлу пинов
    void initOtherPins();
    // Отключение входных пинов
    void disconnectInPins();
    // Отключение выходных пинов
    void disconnectOutPins();
    // Подключение входных пинов
    void connectInPins();
    // Подлючение выходных пинов
    void connectOutPins();

    // Проект
    Project *project_{nullptr};
    // Узел
    ShPtrBaseNode node_{nullptr};
    // Подключенные ко входным пинам выходные узлы
    ShPtrOutputPin connectOtherOutPins_[2];
    // Подключенные к выходному пину
    QVector<ShPtrInputPin> connectOtherInPins_{};
};

//==============================================================
#endif // UNDO_REMOVE_NODE_H
