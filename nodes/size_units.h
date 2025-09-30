/////////////////////////////////////////////////////////////////////
// ByteMachine
// Единицы измерения
/////////////////////////////////////////////////////////////////////
#ifndef SIZE_UNITS_H
#define SIZE_UNITS_H

//===================================================================
#include <QString>
#include <QVector>
#include <QMetaType>

//===================================================================
// Единицы измерения
//===================================================================
enum class SizeUnits
{
    Unknown = -1,
    Byte,
    Kilobyte,
    Megabyte
};

//===================================================================
Q_DECLARE_METATYPE(SizeUnits)

//===================================================================
// Прототипы функций
//===================================================================
// Конвертация единицы измерения в строку
[[nodiscard]]
QString sizeUnitToStr(SizeUnits unit);
// Конвертация строки в единицу измерения
[[nodiscard]]
SizeUnits strToSizeUnit(const QString &str);
// Конвертация единицы изменения в число
[[nodiscard]]
inline int32_t sizeUnitToInt(SizeUnits unit) noexcept { return static_cast<int32_t>(unit); }
// Конвертация числа в единицу измерения
[[nodiscard]]
SizeUnits intToSizeUnit(int32_t value) noexcept;
// Получение признака SizeUnits::Unknown
[[nodiscard]]
inline bool isUnknown(SizeUnits unit) noexcept { return unit == SizeUnits::Unknown; }
// Получение признака SizeUnits::Byte
[[nodiscard]]
inline bool isByte(SizeUnits unit) noexcept { return unit == SizeUnits::Byte; }
// Получение признака SizeUnits::Kilobyte
[[nodiscard]]
inline bool isKilobyte(SizeUnits unit) noexcept { return unit == SizeUnits::Kilobyte; }
// Получение признака SizeUnits::Megabyte
[[nodiscard]]
inline bool isMegabyte(SizeUnits unit) noexcept { return unit == SizeUnits::Megabyte; }
// Получение значений единиц измерения
[[nodiscard]]
QVector<SizeUnits> sizeUnitValues();
// Проверка корректности значения единицы измерения
[[nodiscard]]
bool isCorrect(SizeUnits unit);

//===================================================================
#endif // SIZE_UNITS_H
