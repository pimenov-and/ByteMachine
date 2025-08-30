////////////////////////////////////////////////////////////////
// ByteMachine
// Функция отмены добавления узла
////////////////////////////////////////////////////////////////
#include "undo_add_node.h"
#include "project.h"

//==============================================================
// Конструктор с параметрами
//==============================================================
UndoAddNode::UndoAddNode(Project *project, const ShPtrBaseNode &node)
{
    Q_ASSERT(project != nullptr);
    Q_ASSERT(node != nullptr);

    project_ = project;
    node_ = node;
}

//==============================================================
// Деструктор
//==============================================================
UndoAddNode::~UndoAddNode()
{
}

//==============================================================
// Функция отмены
//==============================================================
void UndoAddNode::undo()
{
    project_->setProperty("isUndo", true);
    project_->removeNode(node_);
    project_->setProperty("isUndo", false);
}

//==============================================================
// Функция восстановления
//==============================================================
void UndoAddNode::redo()
{
    project_->setProperty("isUndo", true);
    project_->addNode(node_);
    project_->setProperty("isUndo", false);
}
