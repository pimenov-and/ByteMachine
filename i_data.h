////////////////////////////////////////////////////////////////
// ByteMachine
// Интерфейс для работы с данными
////////////////////////////////////////////////////////////////
#ifndef I_DATA_H
#define I_DATA_H

//==============================================================
#include <deque>
#include <cstdint>

//==============================================================
// Интерфейс для работы с данными
//==============================================================
struct IData
{
    // Деструктор
    virtual ~IData() = default;

    // Получение размера данных
    [[nodiscard]]
    virtual std::size_t dataSize() const = 0;
    // Получение байта данных
    [[nodiscard]]
    virtual uint8_t dataByte(std::size_t index) const = 0;
    // Получение блока данных
    [[nodiscard]]
    virtual std::deque<uint8_t> dataBlock(std::size_t index,
        std::size_t count) const = 0;
    // Функция вызывается при изменении данных
    virtual void dataChanged() = 0;
};

//==============================================================
#endif // I_DATA_H
