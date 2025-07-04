////////////////////////////////////////////////////////////////
// ByteMachine
// Ширина в байтах
////////////////////////////////////////////////////////////////
#include "byte_widths.h"
#include <QVector>

//==============================================================
// Конвертация ширины в байтах в строку
//==============================================================
QString byteWidthToStr(ByteWidths width)
{
    switch (width)
    {
    case ByteWidths::Width8:
    {
        return "Width8";
    }
    case ByteWidths::Width16:
    {
        return "Width16";
    }
    default:
    {
        return "Unknown";
    }
    }
}

//==============================================================
// Конвертация строки в ширину в байтах
//==============================================================
ByteWidths strToWidthByte(const QString &str)
{
    if (str == "Width8")
    {
        return ByteWidths::Width8;
    }
    else if (str == "Width16")
    {
        return ByteWidths::Width16;
    }
    else
    {
        return ByteWidths::Unknown;
    }
}

//==============================================================
// Конвертация числа в ширину в байтах
//==============================================================
ByteWidths intToByteWidth(int value) noexcept
{
    switch (value)
    {
    case 8:
    {
        return ByteWidths::Width8;
    }
    case 16:
    {
        return ByteWidths::Width16;
    }
    default:
    {
        return ByteWidths::Unknown;
    }
    }
}

//==============================================================
// Конвертация ширины в байтах в индекс
//==============================================================
int byteWidthToIndex(ByteWidths width) noexcept
{
    switch (width)
    {
    case ByteWidths::Width8:
    {
        return 0;
    }
    case ByteWidths::Width16:
    {
        return 1;
    }
    default:
    {
        return -1;
    }
    }
}

//==============================================================
// Конвертация индекса в ширину в байтах
//==============================================================
ByteWidths indexToByteWidth(int index) noexcept
{
    switch (index)
    {
    case 0:
    {
        return ByteWidths::Width8;
    }
    case 1:
    {
        return ByteWidths::Width16;
    }
    default:
    {
        return ByteWidths::Unknown;
    }
    }
}

//==============================================================
// Получение значений ширины в байтах
//==============================================================
QVector<ByteWidths> getByteWidthValues()
{
    return QVector<ByteWidths>
    {
        ByteWidths::Unknown,
        ByteWidths::Width8,
        ByteWidths::Width16
    };
}

//==============================================================
// Проверка корректности значения ByteWidths
//==============================================================
bool isCorrect(ByteWidths width)
{
    return getByteWidthValues().contains(width);
}
