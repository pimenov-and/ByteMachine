////////////////////////////////////////////////////////////////
// ByteMachine
// Команда отмены добавления узла
////////////////////////////////////////////////////////////////
#include "undo_add_node.h"
#include "project.h"

//==============================================================
// Конструктор с параметрами
//==============================================================
UndoAddNode::UndoAddNode(Project *project, const ShPtrBaseNode &node,
    const ShPtrBaseNode &prevSelectedObject)
{
    Q_ASSERT(project != nullptr);
    Q_ASSERT(node != nullptr);

    project_ = project;
    node_ = node;
    prevSelectedObject_ = prevSelectedObject;

    setText(QString{"Add node \"%1\""}.arg(node->name()));
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
    if (prevSelectedObject_ != nullptr)
    {
        prevSelectedObject_->setSelected(false);
    }
    project_->setSelectedNode(prevSelectedObject_);
    project_->setProperty("isUndo", false);
}

//==============================================================
// Функция восстановления
//==============================================================
void UndoAddNode::redo()
{
    project_->setProperty("isUndo", true);
    project_->addNode(node_);
    node_->setSelected(false);
    project_->setSelectedNode(node_);
    project_->setProperty("isUndo", false);
}
