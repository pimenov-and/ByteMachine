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
inline int32_t nodeStateToInt(NodeStates state) noexcept { return static_cast<int32_t>(state); }
// Конвертация числа в состояние узла
[[nodiscard]]
NodeStates intToNodeState(int32_t value);
// Конвертация состояния узла в индекс
[[nodiscard]]
int32_t nodeStateToIndex(NodeStates state);
// Конвертация индекса в состояние узла
[[nodiscard]]
NodeStates indexToNodeState(int32_t index);
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
constexpr int32_t getNodeStateCount() noexcept { return 4; }

//==============================================================
#endif // NODE_STATES_H
