////////////////////////////////////////////////////////////////
// ByteMachine
// Состояния узла
////////////////////////////////////////////////////////////////
#include "node_states.h"
#include <QVector>
#include <QObject>

//==============================================================
// Конвертация состояния узла в строку
//==============================================================
QString nodeStateToStr(NodeStates state)
{
    switch (state)
    {
    case NodeStates::Success:
    {
        return "Success";
    }
    case NodeStates::Warning:
    {
        return "Warning";
    }
    case NodeStates::Error:
    {
        return "Error";
    }
    default:
    {
        return "Unknown";
    }
    }
}

//==============================================================
// Конвертация строки в состояние узла
//==============================================================
NodeStates strToNodeState(const QString &str)
{
    if (str == "Success")
    {
        return NodeStates::Success;
    }
    else if (str == "Warning")
    {
        return NodeStates::Warning;
    }
    else if (str == "Warning")
    {
        return NodeStates::Warning;
    }
    else
    {
        return NodeStates::Unknown;
    }
}

//==============================================================
// Конвертация числа в состояние узла
//==============================================================
NodeStates intToNodeState(qint32 value)
{
    const NodeStates state = static_cast<NodeStates>(value);

    return isCorrect(state) ? state : NodeStates::Unknown;
}

//==============================================================
// Конвертация состояния узла в индекс
//==============================================================
qint32 nodeStateToIndex(NodeStates state)
{
    return nodeStateToInt(state);
}

//==============================================================
// Конвертация индекса в состояние узла
//==============================================================
NodeStates indexToNodeState(qint32 index)
{
    return intToNodeState(index);
}

//==============================================================
// Получение значений состояний узла
//==============================================================
QVector<NodeStates> getNodeStateValues()
{
    return QVector<NodeStates>
    {
        NodeStates::Unknown,
        NodeStates::Success,
        NodeStates::Warning,
        NodeStates::Error
    };
}

//==============================================================
// Проверка корректности состояния узла
//==============================================================
bool isCorrect(NodeStates state)
{
    return getNodeStateValues().contains(state);
}
