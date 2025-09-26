////////////////////////////////////////////////////////////////
// ByteMachine
// Типы узлов
////////////////////////////////////////////////////////////////
#ifndef NODE_TYPES_H
#define NODE_TYPES_H

//==============================================================
#include <QVector>
#include <QString>
#include <QMetaType>

//==============================================================
// Типы узлов
//==============================================================
enum class NodeTypes
{
    Unknown = -1,
    Generate,
    InFile,
    Take,
    Skip,
    Reverse,
    Merge,
    OutFile,
    PaintOp,
    Size,
    Dump,
    Struct,
    Graph,
    Paint,
    SIn,
    SChange,
    SMerge,
    SOut,
    TcpServer,
    TcpClient,
    UdpServer,
    UdpClient,
    Block,
    Cache,
    Non,
    Count
};

//==============================================================
Q_DECLARE_METATYPE(NodeTypes)

//==============================================================
// Прототипы функций
//==============================================================
// Конвертация типа узла в строку
[[nodiscard]]
QString nodeTypeToStr(NodeTypes type);
// Конвертация строки в тип узла
[[nodiscard]]
NodeTypes strToNodeType(const QString &str);
// Получение признака NodeTypes::Unknown
[[nodiscard]]
inline bool isUnknown(NodeTypes type) noexcept { return type == NodeTypes::Unknown; }
// Получение признака NodeTypes::Generate
[[nodiscard]]
inline bool isGenerate(NodeTypes type) noexcept { return type == NodeTypes::Generate; }
// Получение признака NodeTypes::InFile
[[nodiscard]]
inline bool isInFile(NodeTypes type) noexcept { return type == NodeTypes::InFile; }
// Получение признака NodeTypes::Take
[[nodiscard]]
inline bool isTake(NodeTypes type) noexcept { return type == NodeTypes::Take; }
// Получение признака NodeTypes::Skip
[[nodiscard]]
inline bool isSkip(NodeTypes type) noexcept { return type == NodeTypes::Skip; }
// Получение признака NodeTypes::Reverse
[[nodiscard]]
inline bool isReverse(NodeTypes type) noexcept { return type == NodeTypes::Reverse; }
// Получение признака NodeTypes::Merge
[[nodiscard]]
inline bool isMerge(NodeTypes type) noexcept { return type == NodeTypes::Merge; }
// Получение признака NodeTypes::OutFile
[[nodiscard]]
inline bool isOutFile(NodeTypes type) noexcept { return type == NodeTypes::OutFile; }
// Получение признака NodeTypes::PaintOp
[[nodiscard]]
inline bool isPaintOp(NodeTypes type) noexcept { return type == NodeTypes::PaintOp; }
// Получение признака NodeTypes::Size
[[nodiscard]]
inline bool isSize(NodeTypes type) noexcept { return type == NodeTypes::Size; }
// Получение признака NodeTypes::Dump
[[nodiscard]]
inline bool isDump(NodeTypes type) noexcept { return type == NodeTypes::Dump; }
// Получение признака NodeTypes::Struct
[[nodiscard]]
inline bool isStruct(NodeTypes type) noexcept { return type == NodeTypes::Struct; }
// Получение признака NodeTypes::Struct
[[nodiscard]]
inline bool isGraph(NodeTypes type) noexcept { return type == NodeTypes::Graph; }
// Получение признака NodeTypes::Paint
[[nodiscard]]
inline bool isPaint(NodeTypes type) noexcept { return type == NodeTypes::Paint; }
// Получение признака NodeTypes::SIn
[[nodiscard]]
inline bool isSIn(NodeTypes type) noexcept { return type == NodeTypes::SIn; }
// Получение признака NodeTypes::SChange
[[nodiscard]]
inline bool isSChange(NodeTypes type) noexcept { return type == NodeTypes::SChange; }
// Получение признака NodeTypes::SMerge
[[nodiscard]]
inline bool isSMerge(NodeTypes type) noexcept { return type == NodeTypes::SMerge; }
// Получение признака NodeTypes::SOut
[[nodiscard]]
inline bool isSOut(NodeTypes type) noexcept { return type == NodeTypes::SOut; }
// Получение признака NodeTypes::TcpServer
[[nodiscard]]
inline bool isTcpServer(NodeTypes type) noexcept { return type == NodeTypes::TcpServer; }
// Получение признака NodeTypes::TcpClient
[[nodiscard]]
inline bool isTcpClient(NodeTypes type) noexcept { return type == NodeTypes::TcpClient; }
// Получение признака NodeTypes::UdpServer
[[nodiscard]]
inline bool isUdpServer(NodeTypes type) noexcept { return type == NodeTypes::UdpServer; }
// Получение признака NodeTypes::UdpClient
[[nodiscard]]
inline bool isUdpClient(NodeTypes type) noexcept { return type == NodeTypes::UdpClient; }
// Получение признака NodeTypes::Block
[[nodiscard]]
inline bool isBlock(NodeTypes type) noexcept { return type == NodeTypes::Block; }
// Получение признака NodeTypes::Cache
[[nodiscard]]
inline bool isCache(NodeTypes type) noexcept { return type == NodeTypes::Cache; }
// Получение признака NodeTypes::Non
[[nodiscard]]
inline bool isNon(NodeTypes type) noexcept { return type == NodeTypes::Non; }
// Получение значений состояний подключения
[[nodiscard]]
QVector<NodeTypes> nodeTypes();
// Проверка корректности типа узлов
bool isCorrect(NodeTypes type);

//==============================================================
#endif // NODE_TYPES_H
