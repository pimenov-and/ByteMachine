////////////////////////////////////////////////////////////////
// ByteMachine
// Класс проекта
////////////////////////////////////////////////////////////////
#include "project.h"
#include "undo_add_node.h"
#include "undo_remove_node.h"
#include "undo_change_object_prop_value.h"
#include "icons.h"
#include <QAction>
#include <QFile>
#include <QTextStream>
#include <QDomDocument>
#include <QDebug>
#include <algorithm>

//==============================================================
using std::copy;
using std::any_of;
using std::as_const;
using std::back_inserter;

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
// Добавление узла
//==============================================================
bool Project::addNode(const ShPtrBaseNode &node)
{
    Q_ASSERT(node != nullptr);

    if (nodes_.contains(node))
    {
        return false;
    }

    nodes_ << node;
    emit sigAddNode(node);
    connect(node.get(), &BaseNode::sigChangedProp,
        this, &Project::slotChangedNodeProp);

    if (!isUndo_)
    {
        const auto undoCmd = new UndoAddNode(this, node);
        undoStack_.push(undoCmd);
    }

    return true;
}

//==============================================================
// Удаление узла
//==============================================================
bool Project::removeNode(const ShPtrBaseNode &node)
{
    Q_ASSERT(node != nullptr);

    if (!nodes_.contains(node))
    {
        return false;
    }

    nodes_.removeOne(node);
    emit sigRemoveNode(node);

    if (!isUndo_)
    {
        const auto undoCmd = new UndoRemoveNode(this, node);
        undoStack_.push(undoCmd);
    }

    return true;
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
                "comment", comment, oldComment};
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
// Получение выделенного узла
//==============================================================
ShPtrBaseNode Project::selectedNode()
{
    for (const ShPtrBaseNode &node: as_const(nodes_))
    {
        if (node->isSelected())
        {
            return node;
        }
    }

    return nullptr;
}

//==============================================================
// Получение выделенного узла (константный вариант)
//==============================================================
ShPtrConstBaseNode Project::selectedNode() const
{
    for (const ShPtrBaseNode &node: nodes_)
    {
        if (node->isSelected())
        {
            return node;
        }
    }

    return nullptr;
}

//==============================================================
// Сброс выделения всех узлов
//==============================================================
void Project::unselectNodes()
{
    for (const ShPtrBaseNode &node: as_const(nodes_))
    {
        node->setSelected(false);
    }
}

//==============================================================
// Сброс выделения с последующим сигналом
//==============================================================
void Project::clearSelection()
{
    unselectNodes();

    emit sigClearSelection();
}

//==============================================================
// Перенос узла наверх
//==============================================================
bool Project::bringNodeToFront(ShPtrBaseNode node)
{
    Q_ASSERT(node != nullptr);

    if (!nodes_.removeOne(node))
    {
        return false;
    }

    nodes_ << node;
    return true;
}

//==============================================================
// Получение списка узлов (константная версия)
//==============================================================
QVector<ShPtrConstBaseNode> Project::nodes() const
{
    QVector<ShPtrConstBaseNode> constNodes{};
    constNodes.reserve(nodes_.count());
    copy(nodes_.cbegin(), nodes_.cend(), back_inserter(constNodes));

    return constNodes;
}

//==============================================================
// Создание действия Undo
//==============================================================
QAction* Project::createActionUndo() const
{
    QAction *const actUndo = undoStack_.createUndoAction(nullptr);
    actUndo->setIcon(Icons::undo());
    actUndo->setShortcut(QKeySequence{"Ctrl+Z"});

    return actUndo;
}

//==============================================================
// Создание действия Redo
//==============================================================
QAction* Project::createActionRedo() const
{
    QAction *const actRedo = undoStack_.createRedoAction(nullptr);
    actRedo->setIcon(Icons::redo());
    actRedo->setShortcut(QKeySequence{"Ctrl+Y"});

    return actRedo;
}

//==============================================================
// Поиск узла по имени
//==============================================================
ShPtrBaseNode Project::findNodeByName(const QString &name)
{
    for (const auto &node: as_const(nodes_))
    {
        if (node->name() == name)
        {
            return node;
        }
    }

    return nullptr;
}

//==============================================================
// Поиск узал по имени (константный вариант)
//==============================================================
ShPtrConstBaseNode Project::findNodeByName(const QString &name) const
{
    for (const auto &node: nodes_)
    {
        if (node->name() == name)
        {
            return node;
        }
    }

    return nullptr;
}

//==============================================================
// Поиск узла по идентификатору
//==============================================================
ShPtrBaseNode Project::findNodeById(int id)
{
    for (const auto &node: as_const(nodes_))
    {
        if (node->id() == id)
        {
            return node;
        }
    }

    return nullptr;
}

//==============================================================
// Поиск узла по идентификатору (константный вариант)
//==============================================================
ShPtrConstBaseNode Project::findNodeById(int id) const
{
    for (const auto &node: nodes_)
    {
        if (node->id() == id)
        {
            return node;
        }
    }

    return nullptr;
}

//==============================================================
// Поиск узла по указателю
//==============================================================
ShPtrBaseNode Project::findNodeByPtr(BaseNode *node)
{
    Q_ASSERT(node != nullptr);

    for (const ShPtrBaseNode &n: as_const(nodes_))
    {
        if (n == node)
        {
            return n;
        }
    }

    return nullptr;
}

//==============================================================
// Поиск узла по указателю (константный вариант)
//==============================================================
ShPtrConstBaseNode Project::findNodeByPtr(BaseNode * const node) const
{
    Q_ASSERT(node != nullptr);

    for (const ShPtrBaseNode &n: as_const(nodes_))
    {
        if (n == node)
        {
            return n;
        }
    }

    return nullptr;
}

//==============================================================
// // Поиск узла по координате
//==============================================================
ShPtrBaseNode Project::findNodeByPt(const QPoint &pt)
{
    for (auto it = nodes_.crbegin(); it != nodes_.crend(); ++it)
    {
        const ShPtrBaseNode &node = *it;
        if (node->rect().contains(pt))
        {
            return node;
        }
    }

    return nullptr;
}

//==============================================================
// Поиск узла по координате (константный вариант)
//==============================================================
ShPtrConstBaseNode Project::findNodeByPt(const QPoint &pt) const
{
    for (auto it = nodes_.crbegin(); it != nodes_.crend(); ++it)
    {
        const ShPtrBaseNode &node = *it;
        if (node->rect().contains(pt))
        {
            return *it;
        }
    }

    return nullptr;
}

//==============================================================
// Поиск выделенного узла
//==============================================================
ShPtrBaseNode Project::findSelectedNode()
{
    for (const ShPtrBaseNode &n: as_const(nodes_))
    {
        if (n->isSelected())
        {
            return n;
        }
    }

    return nullptr;
}

//==============================================================
// Поиск выделенного узла (константный вариант)
//==============================================================
ShPtrConstBaseNode Project::findSelectedNode() const
{
    for (const ShPtrBaseNode &n: nodes_)
    {
        if (n->isSelected())
        {
            return n;
        }
    }

    return nullptr;
}

//==============================================================
// Поиск входного пина узла по координате
//==============================================================
ShPtrInputPin Project::findInputPinByPt(const QPoint &pt)
{
    for (auto it = nodes_.crbegin(); it != nodes_.crend(); ++it)
    {
        const ShPtrBaseNode &node = *it;
        const QVector<ShPtrInputPin> pins = node->inputPins();
        for (const ShPtrInputPin &pin: pins)
        {
            if (pin->rect().contains(pt))
            {
                return pin;
            }
        }
    }

    return nullptr;
}

//==============================================================
// Поиск входного пина узла по координате (константный вариант)
//==============================================================
ShPtrConstInputPin Project::findInputPinByPt(const QPoint &pt) const
{
    for (auto it = nodes_.crbegin(); it != nodes_.crend(); ++it)
    {
        const ShPtrBaseNode &node = *it;
        const QVector<ShPtrInputPin> pins = node->inputPins();
        for (const ShPtrInputPin &pin: pins)
        {
            if (pin->rect().contains(pt))
            {
                return pin;
            }
        }
    }

    return nullptr;
}

//==============================================================
// Поиск выходного пина узла по координате
//==============================================================
ShPtrOutputPin Project::findOutputPinByPt(const QPoint &pt)
{
    for (auto it = nodes_.crbegin(); it != nodes_.crend(); ++it)
    {
        const ShPtrBaseNode &node = *it;
        const QVector<ShPtrOutputPin> pins = node->outputPins();
        for (const ShPtrOutputPin &pin: pins)
        {
            if (pin->rect().contains(pt))
            {
                return pin;
            }
        }
    }

    return nullptr;
}

//==============================================================
// Поиск выходного пина узла по координате (константный вариант)
//==============================================================
ShPtrConstOutputPin Project::findOutputPinByPt(const QPoint &pt) const
{
    for (auto it = nodes_.crbegin(); it != nodes_.crend(); ++it)
    {
        const ShPtrBaseNode &node = *it;
        const QVector<ShPtrOutputPin> pins = node->outputPins();
        for (const ShPtrOutputPin &pin: pins)
        {
            if (pin->rect().contains(pt))
            {
                return pin;
            }
        }
    }

    return nullptr;
}

//==============================================================
// Функция вызывается при изменении свойства узла
//==============================================================
void Project::slotChangedNodeProp(PropValue value)
{
    BaseNode *node = qobject_cast<BaseNode*>(sender());
    Q_ASSERT(node != nullptr);

    ShPtrBaseNode shPtrNode = findNodeByPtr(node);
    Q_ASSERT(shPtrNode != nullptr);

    emit sigChangedNodeProp(shPtrNode, value);
}

//==============================================================
// Конструктор с параметром
//==============================================================
Project::Project(QObject *parent) : QObject{parent}
{
    setConnections();

    undoStack_.setUndoLimit(100);
}

//==============================================================
// Задание соединений
//==============================================================
void Project::setConnections()
{
}

//==============================================================
// Запись имени проекта в XML
//==============================================================
void Project::writeNameToXml(QDomDocument &doc, QDomElement &elem) const
{
    Q_UNUSED(doc);
    Q_UNUSED(elem);
}

//==============================================================
// Запись комментария к проекту в XML
//==============================================================
void Project::writeCommentToXml(QDomDocument &doc, QDomElement &elem) const
{
    Q_UNUSED(doc);
    Q_UNUSED(elem);
}

//==============================================================
// Запись узлов в XML
//==============================================================
void Project::writeNodesToXml(QDomDocument &doc, QDomElement &elem) const
{
    Q_UNUSED(doc);
    Q_UNUSED(elem);
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
