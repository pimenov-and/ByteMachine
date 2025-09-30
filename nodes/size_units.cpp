/////////////////////////////////////////////////////////////////////
// ByteMachine
// Единицы измерения
/////////////////////////////////////////////////////////////////////
#include "size_units.h"

//===================================================================
// Конвертация единицы измерения в строку
//===================================================================
QString sizeUnitToStr(SizeUnits unit)
{
    switch (unit)
    {
        case SizeUnits::Byte:
        {
            return "Byte";
        }
        case SizeUnits::Kilobyte:
        {
            return "Kilobyte";
        }
        case SizeUnits::Megabyte:
        {
            return "Megabyte";
        }
        default:
        {
            return "Unknown";
        }
    }
}

//===================================================================
// Конвертация строки в единицу измерения
//===================================================================
SizeUnits strToSizeUnit(const QString &str)
{
    if (str == "Byte")
    {
        return SizeUnits::Byte;
    }
    else if (str == "Kilobyte")
    {
        return SizeUnits::Kilobyte;
    }
    else if (str == "Megabyte")
    {
        return SizeUnits::Megabyte;
    }
    else
    {
        return SizeUnits::Unknown;
    }
}

//===================================================================
// Конвертация числа в единицу измерения
//===================================================================
SizeUnits intToSizeUnit(int32_t value) noexcept
{
    switch (value)
    {
        case 0:
        {
            return SizeUnits::Byte;
        }
        case 1:
        {
            return SizeUnits::Kilobyte;
        }
        case 2:
        {
            return SizeUnits::Megabyte;
        }
        default:
        {
            return SizeUnits::Unknown;
        }
    }
}

//===================================================================
// Получение значений единиц измерения
//===================================================================
QVector<SizeUnits> sizeUnitValues()
{
    return QVector<SizeUnits>
    {
        SizeUnits::Unknown,
        SizeUnits::Byte,
        SizeUnits::Kilobyte,
        SizeUnits::Megabyte
    };
}

//===================================================================
// Проверка корректности значения единицы измерения
//===================================================================
bool isCorrect(SizeUnits unit)
{
    return sizeUnitValues().contains(unit);
}
