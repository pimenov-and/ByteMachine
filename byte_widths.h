////////////////////////////////////////////////////////////////
// ByteMachine
// Ширина в байтах
////////////////////////////////////////////////////////////////
#ifndef BYTE_WIDTHS_H
#define BYTE_WIDTHS_H

//==============================================================
#include <QString>
#include <QMetaType>

//==============================================================
// Ширина в байтах
//==============================================================
enum class ByteWidths
{
    Unknown = -1,
    Width8 = 8,
    Width16 = 16
};

//==============================================================
Q_DECLARE_METATYPE(ByteWidths)

//==============================================================
// Прототипы функций
//==============================================================
[[nodiscard]]
// Конвертация ширины в байтах в строку
QString byteWidthToStr(ByteWidths width);
// Конвертация строки в ширину в байтах
[[nodiscard]]
ByteWidths strToWidthByte(const QString &str);
// Конвертация ширины в байтах в число
[[nodiscard]]
inline int32_t byteWidthToInt(ByteWidths width) noexcept { return static_cast<int32_t>(width); }
// Конвертация числа в ширину в байтах
[[nodiscard]]
ByteWidths intToByteWidth(int32_t value) noexcept;
// Конвертация ширины в байтах в индекс
[[nodiscard]]
int32_t byteWidthToIndex(ByteWidths width) noexcept;
// Конвертация индекса в ширину в байтах
[[nodiscard]]
ByteWidths indexToByteWidth(int32_t index) noexcept;
// Получение признака ByteWidths::None
[[nodiscard]]
inline bool isUnknown(ByteWidths width) noexcept { return width == ByteWidths::Unknown; }
// Получение признака ByteWidths::Width8
[[nodiscard]]
inline bool isWidth8(ByteWidths width) noexcept { return width == ByteWidths::Width8; }
// Получение признака ByteWidths::Width16
[[nodiscard]]
inline bool isWidth16(ByteWidths width) noexcept { return width == ByteWidths::Width16; }
// Получение значений ширины в байтах
[[nodiscard]]
QVector<ByteWidths> getByteWidthValues();
// Проверка корректности значения ByteWidths
[[nodiscard]]
bool isCorrect(ByteWidths width);
// Получение количества значений ByteWidths
[[nodiscard]]
constexpr int32_t getByteWidthValueCount() { return 3; }

//==============================================================
#endif // BYTE_WIDTHS_H
