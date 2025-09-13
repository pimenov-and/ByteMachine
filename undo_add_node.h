////////////////////////////////////////////////////////////////
// ByteMachine
// Команда отмены добавления узла
////////////////////////////////////////////////////////////////
#ifndef UNDO_ADD_NODE_H
#define UNDO_ADD_NODE_H

//==============================================================
#include <QUndoCommand>
#include "base_node.h"

//==============================================================
class Project;

//==============================================================
// Команда отмены добавления узла
//==============================================================
class UndoAddNode : public QUndoCommand
{
public:
    // Конструктор с параметрами
    UndoAddNode(Project *project, const ShPtrBaseNode &node,
        const ShPtrBaseNode &prevSelectedObject);
    // Деструктор
    ~UndoAddNode() override;

    // Функция отмены
    void undo() override;
    // Функция восстановления
    void redo() override;
private:
    // Проект
    Project *project_{nullptr};
    // Узел
    ShPtrBaseNode node_{nullptr};
    // Предыдущий выделенный объект
    ShPtrBaseNode prevSelectedObject_{nullptr};
};

//==============================================================
#endif // UNDO_ADD_NODE_H
