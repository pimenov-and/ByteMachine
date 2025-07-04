////////////////////////////////////////////////////////////////
// ByteMachine
// Базовый класс узла
////////////////////////////////////////////////////////////////
#include "base_node.h"
#include "undo_change_object_prop_value.h"
#include <QUndoStack>
#include <QDebug>

////////////////////////////////////////////////////////////////
// Реализация класса BaseNode
////////////////////////////////////////////////////////////////

//==============================================================
//  Статические поля
//==============================================================
// Тип комментариев
bool BaseNode::isCommentsVisible_{false};

//==============================================================
// Конструктор с параметром
//==============================================================
BaseNode::BaseNode(QUndoStack *undoStack, QObject *parent) : QObject{parent}
{
    Q_ASSERT(undoStack != nullptr);

    undoStack_ = undoStack;
}

//==============================================================
// Деструктор
//==============================================================
BaseNode::~BaseNode()
{
}

//==============================================================
// Задание имени
//==============================================================
void BaseNode::setName(const QString &name)
{
    if (name_ != name)
    {
        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
            const QString oldName = name_;
            const auto undoCmd = new UndoChangeObjectPropValue{this,
                "name", name, oldName};
            undoStack_->push(undoCmd);
        }

        name_ = name;
        const PropValue value{"name", name_};
        emit sigChangedProp(value);
    }
}

//==============================================================
// Задание комментария
//==============================================================
void BaseNode::setComment(const QString &comment)
{
    if (comment_ != comment)
    {
        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
            const QString oldComment = comment_;
            const auto undoCmd = new UndoChangeObjectPropValue{this,
                "comment", comment, oldComment};
            undoStack_->push(undoCmd);
        }

        comment_ = comment;
        const PropValue value{"comment", comment_};
        emit sigChangedProp(value);
    }
}

//==============================================================
// Сброс комментария
//==============================================================
void BaseNode::resetComment()
{
    setComment(QString{});
}

//==============================================================
// Получение представления в виде строки
//==============================================================
QString BaseNode::toStr() const
{
    return name() + " : " + strType();
}

//==============================================================
// Задание стека отмен
//==============================================================
void BaseNode::setUndoStack(QUndoStack *undoStack)
{
    if (undoStack_ != undoStack)
    {
        undoStack_ = undoStack;
    }
}

//==============================================================
// Задание признака режима отмены
//==============================================================
void BaseNode::setUndo(bool isUndo)
{
    if (isUndo_ != isUndo)
    {
        isUndo_ = isUndo;
    }
}

//==============================================================
// Сброс признака отмены
//==============================================================
void BaseNode::resetUndo()
{
    setUndo(false);
}

////////////////////////////////////////////////////////////////
// Реализация функций
////////////////////////////////////////////////////////////////
