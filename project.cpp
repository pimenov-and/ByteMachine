////////////////////////////////////////////////////////////////
// ByteMachine
// Класс проекта
////////////////////////////////////////////////////////////////
#include "project.h"
#include "undo_change_object_prop_value.h"
#include <QAction>
#include <algorithm>

//==============================================================
using std::copy;

////////////////////////////////////////////////////////////////
// Реализация класса Project
////////////////////////////////////////////////////////////////

//==============================================================
// Получение экземпляра
//==============================================================
Project* Project::instance()
{
    static Project project{};

    return &project;
}

//==============================================================
// Задание имени
//==============================================================
void Project::setName(const QString &name)
{
    const QString n = name.left(32);

    if (name_ != n)
    {
        if (!n.isEmpty())
        {
            if (!isUndo_)
            {
                const QString oldName = name_;
                const auto undoCmd = new UndoChangeObjectPropValue{this,
                    "name", n, oldName};
                undoStack_.push(undoCmd);
            }

            name_ = n;
            const PropValue value{"name", name_};
            emit sigChangedProp(value);
        }
        else
        {
            const PropValue value{"name", name_};
            emit sigChangedProp(value);
        }
    }
}

//==============================================================
// Сброс имени
//==============================================================
void Project::resetName()
{
    setName("Project");
}

//==============================================================
// Задание комментария
//==============================================================
void Project::setComment(const QString &comment)
{
    if (comment_ != comment)
    {
        if (!isUndo_)
        {
            const QString oldComment = comment_;
            const auto undoCmd = new UndoChangeObjectPropValue{this,
                "comment", comment_, oldComment};
            undoStack_.push(undoCmd);
        }

        comment_ = comment;
        const PropValue value{"comment", comment};
        emit sigChangedProp(value);
    }
}

//==============================================================
// Сброс комментария
//==============================================================
void Project::resetComment()
{
    setComment(QString{});
}

//==============================================================
// Задание признака режима отмены
//==============================================================
void Project::setUndo(bool isUndo)
{
    if (isUndo_ != isUndo)
    {
        isUndo_ = isUndo;
    }
}

//==============================================================
// Сброс признака режима отмены
//==============================================================
void Project::resetUndo()
{
    setUndo(false);
}

//==============================================================
// Получение списка узлов (константная версия)
//==============================================================
QVector<ShPtrConstBaseNode> Project::nodes() const
{
    QVector<ShPtrConstBaseNode> constNodes(nodes_.count());
    copy(nodes_.cbegin(), nodes_.cend(), constNodes.begin());

    return constNodes;
}

//==============================================================
// Создание действия Undo
//==============================================================
QAction* Project::createActionUndo() const
{
    QAction *const actUndo = undoStack_.createUndoAction(nullptr);
    actUndo->setIcon(QIcon{":/res_images/images/undo.png"});
    actUndo->setShortcut(QKeySequence{"Ctrl+Z"});

    return actUndo;
}

//==============================================================
// Создание действия Redo
//==============================================================
QAction* Project::createActionRedo() const
{
    QAction *const actRedo = undoStack_.createRedoAction(nullptr);
    actRedo->setIcon(QIcon{":/res_images/images/redo.png"});
    actRedo->setShortcut(QKeySequence{"Ctrl+Y"});

    return actRedo;
}

//==============================================================
// Конструктор с параметром
//==============================================================
Project::Project(QObject *parent) : QObject{parent}
{
    setConnections();
}

//==============================================================
// Задание соединений
//==============================================================
void Project::setConnections()
{
}

////////////////////////////////////////////////////////////////
// Прототипы функций
////////////////////////////////////////////////////////////////

//==============================================================
// Получение проекта
//==============================================================
Project* project()
{
    return Project::instance();
}
