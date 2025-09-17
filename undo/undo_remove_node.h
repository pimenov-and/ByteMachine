////////////////////////////////////////////////////////////////
// ByteMachine
// Команда отмены удаления узла
////////////////////////////////////////////////////////////////
#ifndef UNDO_REMOVE_NODE_H
#define UNDO_REMOVE_NODE_H

//==============================================================
#include <QUndoCommand>
#include "base_node.h"

//==============================================================
class Project;

//==============================================================
// Команда отмены удаления узла
//==============================================================
class UndoRemoveNode : public QUndoCommand
{
public:
    // Конструктор с параметрами
    explicit UndoRemoveNode(Project *project, const ShPtrBaseNode &node);
    // Деструктор
    ~UndoRemoveNode() override;

    // Функция отмены
    void undo() override;
    // Функция восстановления
    void redo() override;
private:
    // Проект
    Project *project_{nullptr};
    // Узел
    ShPtrBaseNode node_{nullptr};
};

//==============================================================
#endif // UNDO_REMOVE_NODE_H
