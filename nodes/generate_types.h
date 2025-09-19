////////////////////////////////////////////////////////////////
// ByteMachine
// Типы генерации для узла Generate
////////////////////////////////////////////////////////////////
#ifndef GENERATE_TYPES_H
#define GENERATE_TYPES_H

//==============================================================
#include <QString>
#include <QMetaType>

//==============================================================
// Типы генерации для узла Generate
//==============================================================
enum class GenerateTypes
{
    Unknown = -1,
    Usual,
    Random,
    Bool,
    Int8,
    UInt8,
    Int16,
    UInt16,
    Int32,
    UInt32,
    Int64,
    UInt64,
    Float,
    Double,
    String, // UTF-8
    Color
};

//==============================================================
Q_DECLARE_METATYPE(GenerateTypes)

//==============================================================
// Прототипы функций
//==============================================================
// Перевод типа генерации в строку
[[nodiscard]]
QString generateTypeToStr(GenerateTypes type);
// Перевод строки в тип генерации
[[nodiscard]]
GenerateTypes strToGenerateType(const QString &str);
[[nodiscard]]
// Конвертация типа генерации в число
[[nodiscard]]
inline int generateTypeToInt(GenerateTypes type) noexcept { return static_cast<int>(type); }
// Конвертация числа в тип генерации
[[nodiscard]]
GenerateTypes intToGenerateType(int value);
// Получение признака GenerateTypes::Unknown
[[nodiscard]]
inline bool isUnknown(GenerateTypes type) noexcept { return type == GenerateTypes::Unknown; }
// Получение признака GenerateTypes::Usual
[[nodiscard]]
inline bool isUsual(GenerateTypes type) noexcept { return type == GenerateTypes::Usual; }
// Получение признака GenerateTypes::Random
[[nodiscard]]
inline bool isRandom(GenerateTypes type) noexcept { return type == GenerateTypes::Random; }
// Получение признака GenerateTypes::Bool
[[nodiscard]]
inline bool isBool(GenerateTypes type) noexcept { return type == GenerateTypes::Bool; }
// Получение признака GenerateTypes::Int8
[[nodiscard]]
inline bool isInt8(GenerateTypes type) noexcept { return type == GenerateTypes::Int8; }
// Получение признака GenerateTypes::UInt8
[[nodiscard]]
inline bool isUInt8(GenerateTypes type) noexcept { return type == GenerateTypes::UInt8; }
// Получение признака GenerateTypes::Int16
[[nodiscard]]
inline bool isInt16(GenerateTypes type) noexcept { return type == GenerateTypes::Int16; }
// Получение признака GenerateTypes::UInt16
[[nodiscard]]
inline bool isUInt16(GenerateTypes type) noexcept { return type == GenerateTypes::UInt16; }
// Получение признака GenerateTypes::Int32
[[nodiscard]]
inline bool isInt32(GenerateTypes type) noexcept { return type == GenerateTypes::Int32; }
[[nodiscard]]
// Получение признака GenerateTypes::UInt32
[[nodiscard]]
inline bool isUInt32(GenerateTypes type) noexcept { return type == GenerateTypes::UInt32; }
// Получение признака GenerateTypes::Int64
[[nodiscard]]
inline bool isInt64(GenerateTypes type) noexcept { return type == GenerateTypes::Int64; }
// Получение признака GenerateTypes::UInt64
[[nodiscard]]
inline bool isUInt64(GenerateTypes type) noexcept { return type == GenerateTypes::UInt64; }
// Получение признака GenerateTypes::Float
[[nodiscard]]
inline bool isFloat(GenerateTypes type) noexcept { return type == GenerateTypes::Float; }
// Получение признака GenerateTypes::Double
[[nodiscard]]
inline bool isDouble(GenerateTypes type) noexcept { return type == GenerateTypes::Double; }
// Получение признака GenerateTypes::String
[[nodiscard]]
inline bool isString(GenerateTypes type) noexcept { return type == GenerateTypes::String; }
// Получение признака GenerateTypes::Color
[[nodiscard]]
inline bool isColor(GenerateTypes type) noexcept { return type == GenerateTypes::Color; }
// Получение списка типов генераций
[[nodiscard]]
QVector<GenerateTypes> getGenerateTypeValues();
// Проверка корректности значения типа генерации
[[nodiscard]]
bool isCorrect(GenerateTypes type);
// Получение количества типов генерации
[[nodiscard]]
qint32 getGenerateTypeValueCount();

//==============================================================
#endif // GENERATE_TYPES_H
