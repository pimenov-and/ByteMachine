////////////////////////////////////////////////////////////////
// ByteMachine
// Команда отмены удаления узла
////////////////////////////////////////////////////////////////
#include "undo_remove_node.h"
#include "project.h"

//==============================================================
// Конструктор с параметрами
//==============================================================
UndoRemoveNode::UndoRemoveNode(Project *project, const ShPtrBaseNode &node)
{
    Q_ASSERT(project != nullptr);
    Q_ASSERT(node != nullptr);

    project_ = project;
    node_ = node;

    setText(QString{"Remove node \"%1\""}.arg(node->name()));
}

//==============================================================
// Деструктор
//==============================================================
UndoRemoveNode::~UndoRemoveNode()
{
}

//==============================================================
// Функция отмены
//==============================================================
void UndoRemoveNode::undo()
{
    project_->setProperty("isUndo", true);
    project_->addNode(node_);
    project_->setProperty("isUndo", false);
}

//==============================================================
// Функция восстановления
//==============================================================
void UndoRemoveNode::redo()
{
    project_->setProperty("isUndo", true);
    project_->removeNode(node_);
    project_->setProperty("isUndo", false);
}
