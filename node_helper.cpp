////////////////////////////////////////////////////////////////
// ByteMachine
// Вспомогательные функции для работы с узлами
////////////////////////////////////////////////////////////////
#include "node_helper.h"
#include "generate_node.h"
#include "size_node.h"

//==============================================================
// Создание узла по типу
//==============================================================
ShPtrBaseNode createNode(NodeTypes type, QUndoStack *undoStack,
    QObject *parent)
{
    switch (type)
    {
        case NodeTypes::Generate:
        {
            return QSharedPointer<GenerateNode>::create(undoStack, parent);
        }
        case NodeTypes::Size:
        {
            return QSharedPointer<SizeNode>::create(undoStack, parent);
        }
        default:
        {
            return nullptr;
        }
    }
}

//==============================================================
// Создание узла по строке типа
//==============================================================
ShPtrBaseNode createNode(const QString &strType, QUndoStack *undoStack,
    QObject *parent)
{
    const NodeTypes type = strToNodeType(strType);

    return createNode(type, undoStack, parent);
}
