////////////////////////////////////////////////////////////////
// ByteMachine
// Состояния подключения
////////////////////////////////////////////////////////////////
#include "connect_states.h"
#include <QVector>

//==============================================================
// Конвертация состояния подключения в виде строки
//==============================================================
QString connectStateToStr(ConnectStates state)
{
    switch (state)
    {
    case ConnectStates::Connect:
    {
        return "Connect";
    }
    case ConnectStates::Disconnect:
    {
        return "Disconnect";
    }
    default:
    {
        return "Unknown";
    }
    }
}

//==============================================================
// Конвертация состояния подключения из строки
//==============================================================
ConnectStates strToConnectState(const QString &str)
{
    if (str == "Connect")
    {
        return ConnectStates::Connect;
    }
    else if (str == "Disconnect")
    {
        return ConnectStates::Disconnect;
    }
    else
    {
        return ConnectStates::Unknown;
    }
}

//==============================================================
// Конвертация числа в состояние подключения
//==============================================================
ConnectStates intToConnectState(int value) noexcept
{
    const ConnectStates state = static_cast<ConnectStates>(value);

    return isCorrect(state) ? state : ConnectStates::Unknown;
}

//==============================================================
// Конвертация состояния подключения в индекс
//==============================================================
int connectStateToIndex(ConnectStates state) noexcept
{
    return connectStateToInt(state);
}

//==============================================================
// Конвертация индекса в состояние подключения
//==============================================================
ConnectStates indexToConnectState(int index)
{
    return intToConnectState(index);
}

//===================================================================
// Получение значений состояний подключения
//===================================================================
QVector<ConnectStates> connectStateValues()
{
    return QVector<ConnectStates>
        {
            ConnectStates::Unknown,
            ConnectStates::Connect,
            ConnectStates::Disconnect
        };
}

//===================================================================
// Проверка корректности значения состояния подключения
//===================================================================
bool isCorrect(ConnectStates state)
{
    return connectStateValues().contains(state);
}
