////////////////////////////////////////////////////////////////
// ByteMachine
// Вспомогательные функции для работы с узлами
////////////////////////////////////////////////////////////////
#ifndef NODE_HELPER_H
#define NODE_HELPER_H

//==============================================================
#include "base_node.h"
#include "node_types.h"

//==============================================================
// Прототипы функций
//==============================================================
// Создание узла по типу
[[nodiscard]]
ShPtrBaseNode createNode(NodeTypes type, QUndoStack *undoStack,
    QObject *parent = nullptr);
// Создание узла по строке типа
[[nodiscard]]
ShPtrBaseNode createNode(const QString &strType, QUndoStack *undoStack,
    QObject *parent = nullptr);

//==============================================================
#endif // NODE_HELPER_H
