////////////////////////////////////////////////////////////////
// ByteMachine
// Команда отмены выделения объекта
////////////////////////////////////////////////////////////////
#ifndef UNDO_SELECT_OBJECT_H
#define UNDO_SELECT_OBJECT_H

//==============================================================
#include <QUndoCommand>
#include "base_node.h"

//==============================================================
class Project;

//==============================================================
// Команда отмены выделения объекта
//==============================================================
class UndoSelectObject : public QUndoCommand
{
public:
    // Конструктор с параметрами
    UndoSelectObject(Project *project, const ShPtrBaseNode &node1,
        const ShPtrBaseNode &node2);
    // Деструктор
    ~UndoSelectObject() override;

    // Функция отмены
    void undo() override;
    // Функция восстановления
    void redo() override;
private:
    // Проект
    Project *project_{nullptr};
    // Узел 1
    ShPtrBaseNode node1_{nullptr};
    // Узел 2
    ShPtrBaseNode node2_{nullptr};
};

//==============================================================
#endif // UNDO_SELECT_OBJECT_H
