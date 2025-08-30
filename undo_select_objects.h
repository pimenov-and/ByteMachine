////////////////////////////////////////////////////////////////
// ByteMachine
//
////////////////////////////////////////////////////////////////
#ifndef UNDO_SELECT_OBJECTS_H
#define UNDO_SELECT_OBJECTS_H

//==============================================================
#include <QUndoCommand>
#include "base_node.h"

//==============================================================
class Project;

//==============================================================
//
//==============================================================
class UndoSelectObjects : public QUndoCommand
{
public:
    // Конструктор с параметрами
    UndoSelectObjects(Project *project, const ShPtrBaseNode &node1,
        const ShPtrBaseNode &node2, bool isSelected);
    // Деструктор
    ~UndoSelectObjects();

    // Функция отмены
    void undo() override;
    // Функция восстановления
    void redo() override;
private:
    // Узел 1
    ShPtrBaseNode node1_{nullptr};
    // Узел 2
    ShPtrBaseNode node2_{nullptr};
    // Признак выделения
    bool isSelected_{false};
};

//==============================================================
#endif // UNDO_SELECT_OBJECTS_H
