////////////////////////////////////////////////////////////////
// ByteMachine
// Состояния узла
////////////////////////////////////////////////////////////////
#ifndef NODE_STATES_H
#define NODE_STATES_H

//==============================================================
#include <QString>
#include <QMetaType>

//==============================================================
// Состояния узла
//==============================================================
enum class NodeStates
{
    Unknown = -1,
    Success,
    Warning,
    Error
};

//==============================================================
Q_DECLARE_METATYPE(NodeStates)

//==============================================================
// Прототипы функций
//==============================================================
// Конвертация состояния узла в строку
[[nodiscard]]
QString nodeStateToStr(NodeStates state);
// Конвертация строки в состояние узла
[[nodiscard]]
NodeStates strToNodeState(const QString &str);
// Конвертация состояния узла в число
[[nodiscard]]
inline qint32 nodeStateToInt(NodeStates state) noexcept { return static_cast<qint32>(state); }
// Конвертация числа в состояние узла
[[nodiscard]]
NodeStates intToNodeState(qint32 value);
// Конвертация состояния узла в индекс
[[nodiscard]]
qint32 nodeStateToIndex(NodeStates state);
// Конвертация индекса в состояние узла
[[nodiscard]]
NodeStates indexToNodeState(qint32 index);
// Является ли состояние узла None
[[nodiscard]]
inline bool isUnknown(NodeStates state) noexcept { return state == NodeStates::Unknown; }
// Является ли состояние узла Success
[[nodiscard]]
inline bool isSuccess(NodeStates state) noexcept { return state == NodeStates::Success; }
// Является ли состояние узла Warning
[[nodiscard]]
inline bool isWarning(NodeStates state) noexcept { return state == NodeStates::Warning; }
// Является ли состояние узла Error
[[nodiscard]]
inline bool isError(NodeStates state) noexcept { return state == NodeStates::Error; }
// Получение значений состояний узла
[[nodiscard]]
QVector<NodeStates> getNodeStateValues();
// Проверка корректности состояния узла
[[nodiscard]]
bool isCorrect(NodeStates state);
// Получение количества состояний узла
[[nodiscard]]
constexpr qint32 getNodeStateCount() noexcept { return 4; }

//==============================================================
#endif // NODE_STATES_H
