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
        {NodeTypes::Paint, "Paint"},
        {NodeTypes::SIn, "SIn"},
        {NodeTypes::SChange, "SChange"},
        {NodeTypes::SMerge, "SMerge"},
        {NodeTypes::SOut, "SOut"},
        {NodeTypes::TcpServer, "TcpServer"},
        {NodeTypes::TcpClient, "TcpClient"},
        {NodeTypes::UdpServer, "UdpServer"},
        {NodeTypes::UdpClient, "UdpClient"},
        {NodeTypes::Block, "Block"},
        {NodeTypes::Cache, "Cache"},
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
        {"Paint", NodeTypes::Paint},
        {"SIn", NodeTypes::SIn},
        {"SChange", NodeTypes::SChange},
        {"SMerge", NodeTypes::SMerge},
        {"SOut", NodeTypes::SOut},
        {"Block", NodeTypes::Block},
        {"Cache", NodeTypes::Cache},
        {"Non", NodeTypes::Non}
    };

    return map.value(str, NodeTypes::Unknown);
}

//==============================================================
// Получение значений состояний подключения
//==============================================================
QVector<NodeTypes> nodeTypes()
{
    return QVector<NodeTypes>
    {
        NodeTypes::Generate,
        NodeTypes::InFile,
        NodeTypes::Take,
        NodeTypes::Skip,
        NodeTypes::Reverse,
        NodeTypes::Merge,
        NodeTypes::OutFile,
        NodeTypes::PaintOp,
        NodeTypes::Size,
        NodeTypes::Dump,
        NodeTypes::Struct,
        NodeTypes::Graph,
        NodeTypes::Paint,
        NodeTypes::SIn,
        NodeTypes::SChange,
        NodeTypes::SMerge,
        NodeTypes::SOut,
        NodeTypes::TcpServer,
        NodeTypes::TcpClient,
        NodeTypes::UdpServer,
        NodeTypes::UdpClient,
        NodeTypes::Block,
        NodeTypes::Cache,
        NodeTypes::Non,
        NodeTypes::Count
    };
}

//==============================================================
// Проверка корректности типа узлов
//==============================================================
bool isCorrect(NodeTypes type)
{
    return nodeTypes().contains(type);
}
