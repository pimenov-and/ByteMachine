/////////////////////////////////////////////////////////////////////
// ByteMachine
// Единицы измерения
/////////////////////////////////////////////////////////////////////
#include "size_units.h"
#include <QObject>
#include <QMap>

//===================================================================
// Конвертация единицы измерения в строку
//===================================================================
QString sizeUnitToStr(SizeUnits unit)
{
    const QMap<SizeUnits, QString> map
    {
        {SizeUnits::Byte, "Byte"},
        {SizeUnits::Kilobyte, "Kilobyte"},
        {SizeUnits::Megabyte, "Megabyte"}
    };

    return map.value(unit, "Unknown");
}

//===================================================================
// Конвертация строки в единицу измерения
//===================================================================
SizeUnits strToSizeUnit(const QString &str)
{
    const QMap<QString, SizeUnits> map
    {
        {"Byte", SizeUnits::Byte},
        {"Kilobyte", SizeUnits::Kilobyte},
        {"Megabyte", SizeUnits::Megabyte}
    };

    return map.value(str, SizeUnits::Unknown);
}

//===================================================================
// Конвертация числа в единицу измерения
//===================================================================
SizeUnits intToSizeUnit(int value) noexcept
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
