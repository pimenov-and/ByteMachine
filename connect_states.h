////////////////////////////////////////////////////////////////
// ByteMachine
// Состояния подключения
////////////////////////////////////////////////////////////////
#ifndef CONNECT_STATES_H
#define CONNECT_STATES_H

//==============================================================
#include <QString>
#include <QMetaType>

//==============================================================
// Состояние подключения
//==============================================================
enum class ConnectStates
{
    Unknown = -1,
    Connect,
    Disconnect
};

//==============================================================
Q_DECLARE_METATYPE(ConnectStates)

//==============================================================
// Прототипы функций
//==============================================================
// Конвертация состояния подключения в виде строки
[[nodiscard]]
QString connectStateToStr(ConnectStates state);
// Конвертация состояния подключения из строки
[[nodiscard]]
ConnectStates strToConnectState(const QString &str);
// Конвертация состояния подключание в число
[[nodiscard]]
inline int connectStateToInt(ConnectStates state) noexcept { return static_cast<int>(state); }
// Конвертация числа в состояние подключения
[[nodiscard]]
ConnectStates intToConnectState(int value) noexcept;
// Конвертация состояния подключения в индекс
[[nodiscard]]
int connectStateToIndex(ConnectStates state) noexcept;
// Конвертация индекса в состояние подключения
[[nodiscard]]
ConnectStates indexToConnectState(int index);
// Получение признака ConnectStates::None
[[nodiscard]]
inline bool isUnknown(ConnectStates state) noexcept { return state == ConnectStates::Unknown; }
// Получение признака ConnectStates::Connect
[[nodiscard]]
inline bool isConnect(ConnectStates state) noexcept { return state == ConnectStates::Connect; }
// Получение признака ConnectStates::Disconnect
[[nodiscard]]
inline bool isDisconnect(ConnectStates state) noexcept { return state == ConnectStates::Disconnect; }
// Получение значений состояний подключения
[[nodiscard]]
QVector<ConnectStates> connectStateValues();
// Проверка корректности значения состояния подключения
[[nodiscard]]
bool isCorrect(ConnectStates state);
// Получение количества состояний подключения в виде строки
[[nodiscard]]
constexpr qint32 getConnectStateCount() noexcept { return 3; }

//==============================================================
#endif // CONNECT_STATES_H
