////////////////////////////////////////////////////////////////
// ByteMachine
// Типы узлов
////////////////////////////////////////////////////////////////
#include "node_types.h"
#include <QMap>

//==============================================================
// Конвертация типа узла в строку
//==============================================================
QString nodeTypeToStr(NodeTypes type)
{
    const QMap<NodeTypes, QString> map =
    {
        {NodeTypes::Generate, "Generate"},
        {NodeTypes::InFile, "InFile"},
        {NodeTypes::Take, "Take"},
        {NodeTypes::Skip, "Skip"},
        {NodeTypes::Reverse, "Reverse"},
        {NodeTypes::Merge, "Merge"},
        {NodeTypes::OutFile, "OutFile"},
        {NodeTypes::PaintOp, "PaintOp"},
        {NodeTypes::Size, "Size"},
        {NodeTypes::Dump, "Dump"},
        {NodeTypes::Struct, "Struct"},
        {NodeTypes::Graph, "Graph"},
        {NodeTypes::SIn, "SIn"},
        {NodeTypes::SChange, "SChange"},
        {NodeTypes::SMerge, "SMerge"},
        {NodeTypes::SOut, "SOut"},
        {NodeTypes::Block, "Block"},
        {NodeTypes::Non, "Non"}
    };

    return map.value(type, "Unknown");
}

//==============================================================
// Конвертация строки в тип узла
//==============================================================
NodeTypes strToNodeType(const QString &str)
{
    const QMap<QString, NodeTypes> map =
    {
        {"Generate", NodeTypes::Generate},
        {"InFile", NodeTypes::InFile},
        {"Take", NodeTypes::Take},
        {"Skip", NodeTypes::Skip},
        {"Reverse", NodeTypes::Reverse},
        {"Merge", NodeTypes::Merge},
        {"OutFile", NodeTypes::OutFile},
        {"PaintOp", NodeTypes::PaintOp},
        {"Size", NodeTypes::Size},
        {"Dump", NodeTypes::Dump},
        {"Struct", NodeTypes::Struct},
        {"Graph", NodeTypes::Graph},
        {"SIn", NodeTypes::SIn},
        {"SChange", NodeTypes::SChange},
        {"SMerge", NodeTypes::SMerge},
        {"SOut", NodeTypes::SOut},
        {"Block", NodeTypes::Block},
        {"Non", NodeTypes::Non}
    };

    return map.value(str, NodeTypes::Unknown);
}
