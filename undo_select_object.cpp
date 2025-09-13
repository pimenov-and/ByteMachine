////////////////////////////////////////////////////////////////
// ByteMachine
// Команда отмены выделения объекта
////////////////////////////////////////////////////////////////
#include "undo_select_object.h"
#include "project.h"

//==============================================================
// Конструктор с параметрами
//==============================================================
UndoSelectObject::UndoSelectObject(Project *project,
    const ShPtrBaseNode &node1,
    const ShPtrBaseNode &node2)
{
    Q_ASSERT(project != nullptr);
    Q_ASSERT(!(node1 == nullptr && node2 == nullptr));

    project_ = project;
    node1_ = node1;
    node2_ = node2;

    // Задание наименования отмены
    if (node1 != nullptr)
    {
        setText(QString{"Select node \"%1\""}.arg(node1->name()));
    }
    else
    {
        setText("Select project");
    }
}

//==============================================================
// Деструктор
//==============================================================
UndoSelectObject::~UndoSelectObject()
{
}

//==============================================================
// Функция отмены
//==============================================================
void UndoSelectObject::undo()
{
    project_->setProperty("isUndo", true);
    project_->setSelectedNode(node2_);
    project_->setProperty("isUndo", false);
}

//==============================================================
// Функция восстановления
//==============================================================
void UndoSelectObject::redo()
{
    project_->setProperty("isUndo", true);
    project_->setSelectedNode(node1_);
    project_->setProperty("isUndo", false);
}
