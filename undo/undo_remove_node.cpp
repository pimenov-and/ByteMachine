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

    initOtherPins();

    setText(QString{"Remove node \"%1\""}.arg(node->name()));
}

//==============================================================
// Деструктор
//==============================================================
UndoRemoveNode::~UndoRemoveNode()
{
}

//==============================================================
// Инициализация подключенных к узлу пинов
//==============================================================
void UndoRemoveNode::initOtherPins()
{
    // Входных пинов сейчас может быть от 0 до 2
    for (int i = 0; i < node_->inputPinCount(); ++i)
    {
        const ShPtrInputPin inPin = node_->inputPin(i);
        if (inPin->isConnected())
        {
            connectOtherOutPins_[i] = inPin->outputPin();
        }
    }

    // Выходных пинов сейчас может быть 0 или 1
    if (node_->isOutputPins())
    {
        const ShPtrOutputPin outPin = node_->outputPin(0);
        connectOtherInPins_ = outPin->inputPins();
    }
}

//==============================================================
// Отключение входных пинов
//==============================================================
void UndoRemoveNode::disconnectInPins()
{
    for (int i = 0; i < 2; ++i)
    {
        ShPtrOutputPin &otherOutPin = connectOtherOutPins_[i];
        if (otherOutPin != nullptr)
        {
            ShPtrInputPin inPin = node_->inputPin(i);
            disconnectPins(otherOutPin, inPin, false);
        }
    }
}

//==============================================================
// Отключение выходных пинов
//==============================================================
void UndoRemoveNode::disconnectOutPins()
{
    if (node_->isOutputPins() && !connectOtherInPins_.isEmpty())
    {
        ShPtrOutputPin outPin = node_->outputPin(0);
        for (ShPtrInputPin &otherInPin: connectOtherInPins_)
        {
            disconnectPins(outPin, otherInPin, false);
        }
    }
}

//==============================================================
// Подключение входных пинов
//==============================================================
void UndoRemoveNode::connectInPins()
{
    for (int i = 0; i < 2; ++i)
    {
        ShPtrOutputPin &otherOutPin = connectOtherOutPins_[i];
        if (otherOutPin != nullptr)
        {
            ShPtrInputPin inPin = node_->inputPin(i);
            connectPins(otherOutPin, inPin, false);
        }
    }
}

//==============================================================
// Подлючение выходных пинов
//==============================================================
void UndoRemoveNode::connectOutPins()
{
    if (node_->isOutputPins() && !connectOtherInPins_.isEmpty())
    {
        ShPtrOutputPin outPin = node_->outputPin(0);
        for (ShPtrInputPin &otherInPin: connectOtherInPins_)
        {
            connectPins(outPin, otherInPin, false);
        }
    }
}


//==============================================================
// Функция отмены
//==============================================================
void UndoRemoveNode::undo()
{
    project_->setProperty("isUndo", true);
    project_->addNode(node_);
    connectInPins();
    connectOutPins();
    project_->setProperty("isUndo", false);
}

//==============================================================
// Функция восстановления
//==============================================================
void UndoRemoveNode::redo()
{
    project_->setProperty("isUndo", true);
    disconnectInPins();
    disconnectOutPins();
    project_->removeNode(node_);
    project_->setProperty("isUndo", false);
}
