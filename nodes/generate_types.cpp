////////////////////////////////////////////////////////////////
// ByteMachine
// Типы генерации для узла Generate
////////////////////////////////////////////////////////////////
#include "generate_types.h"
#include <QMap>
#include <QObject>

//==============================================================
// Перевод типа генерации в строку
//==============================================================
QString generateTypeToStr(GenerateTypes type)
{
    const QMap<GenerateTypes, QString> map
    {
        {GenerateTypes::Usual, "Usual"},
        {GenerateTypes::Random, "Random"},
        {GenerateTypes::Bool, "Bool"},
        {GenerateTypes::Int8, "Int8"},
        {GenerateTypes::UInt8, "UInt8"},
        {GenerateTypes::Int16, "Int16"},
        {GenerateTypes::UInt16, "UInt16"},
        {GenerateTypes::Int32, "Int32"},
        {GenerateTypes::UInt32, "UInt32"},
        {GenerateTypes::Int64, "Int64"},
        {GenerateTypes::UInt64, "UInt64"},
        {GenerateTypes::Float, "Float"},
        {GenerateTypes::Double, "Double"},
        {GenerateTypes::String, "String"}, // UTF-8
        {GenerateTypes::Color, "Color"}
    };

    return map.value(type, "Unknown");
}

//==============================================================
// Перевод строки в тип генерации
//==============================================================
GenerateTypes strToGenerateType(const QString &str)
{
    const QMap<QString, GenerateTypes> map
    {
        {"Usual", GenerateTypes::Usual},
        {"Random", GenerateTypes::Random},
        {"Bool", GenerateTypes::Bool},
        {"Int8", GenerateTypes::Int8},
        {"UInt8", GenerateTypes::UInt8},
        {"Int16", GenerateTypes::Int16},
        {"UInt16", GenerateTypes::UInt16},
        {"Int32", GenerateTypes::Int32},
        {"UInt32", GenerateTypes::UInt32},
        {"Int64", GenerateTypes::Int64},
        {"UInt64", GenerateTypes::UInt64},
        {"Float", GenerateTypes::Float},
        {"Double", GenerateTypes::Double},
        {"String", GenerateTypes::String}, // UTF-8
        {"Color", GenerateTypes::Color}
    };

    return map.value(str, GenerateTypes::Unknown);
}

//==============================================================
// Конвертация числа в тип генерации
//==============================================================
GenerateTypes intToGenerateType(int value)
{
    const GenerateTypes type = static_cast<GenerateTypes>(value);

    return isCorrect(type) ? type : GenerateTypes::Unknown;
}

//==============================================================
// Получение списка типов генераций
//==============================================================
QVector<GenerateTypes> getGenerateTypeValues()
{
    return QVector<GenerateTypes>
    {
        GenerateTypes::Unknown,
        GenerateTypes::Usual,
        GenerateTypes::Random,
        GenerateTypes::Bool,
        GenerateTypes::Int8,
        GenerateTypes::UInt8,
        GenerateTypes::Int16,
        GenerateTypes::UInt16,
        GenerateTypes::Int32,
        GenerateTypes::UInt32,
        GenerateTypes::Int64,
        GenerateTypes::UInt64,
        GenerateTypes::Float,
        GenerateTypes::Double,
        GenerateTypes::String, // UTF-8
        GenerateTypes::Color
    };
}

//==============================================================
// Проверка корректности значения типа генерации
//==============================================================
bool isCorrect(GenerateTypes type)
{
    return getGenerateTypeValues().contains(type);
}

//==============================================================
// Получение количества типов генерации
//==============================================================
qint32 getGenerateTypeValueCount()
{
    static qint32 count = getGenerateTypeValues().count();

    return count;
}
