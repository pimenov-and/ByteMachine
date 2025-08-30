////////////////////////////////////////////////////////////////
// ByteMachine
// Функция отмены добавления узла
////////////////////////////////////////////////////////////////
#ifndef UNDO_ADD_NODE_H
#define UNDO_ADD_NODE_H

//==============================================================
#include <QUndoCommand>
#include "base_node.h"

//==============================================================
class Project;

//==============================================================
// Функция отмены для операции задания имени проекта
//==============================================================
class UndoAddNode : public QUndoCommand
{
public:
    // Конструктор с параметрами
    explicit UndoAddNode(Project *project, const ShPtrBaseNode &node);
    // Деструктор
    ~UndoAddNode();

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
#endif // UNDO_ADD_NODE_H
