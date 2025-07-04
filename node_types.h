////////////////////////////////////////////////////////////////
// ByteMachine
// Типы узлов
////////////////////////////////////////////////////////////////
#ifndef NODE_TYPES_H
#define NODE_TYPES_H

//==============================================================
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
    SIn,
    SChange,
    SMerge,
    SOut,
    Block,
    Non,
    Count
};

//==============================================================
Q_DECLARE_METATYPE(NodeTypes);

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


//==============================================================
#endif // NODE_TYPES_H
