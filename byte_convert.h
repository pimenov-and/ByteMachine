////////////////////////////////////////////////////////////////
// ByteMachine
// Функции конвертации стандартных типов в байты и обратно
////////////////////////////////////////////////////////////////
#ifndef BYTE_CONVERT_H
#define BYTE_CONVERT_H

//==============================================================
#include <QString>
#include <QColor>
#include <QPoint>
#include <QPointF>
#include <QSize>
#include <QSizeF>
#include <QRect>
#include <QRectF>
#include <type_traits>
#include <cstring>

////////////////////////////////////////////////////////////////
// Прототипы функций
////////////////////////////////////////////////////////////////
// Конвертация значения в список байтов
template<typename T>
[[nodiscard]]
QVector<uint8_t> valueToByteList(const T &value);
// Конвертации значения QString в список байтов
template<>
[[nodiscard]]
QVector<uint8_t> valueToByteList<QString>(const QString &value);
// Конвертация значения QColor в список байтов
template<>
[[nodiscard]]
QVector<uint8_t> valueToByteList<QColor>(const QColor &value);
// Конвертация значения QPoint в список байтов
template<>
[[nodiscard]]
QVector<uint8_t> valueToByteList<QPoint>(const QPoint &value);
// Конвертация значения QPointF в список байтов
template<>
[[nodiscard]]
QVector<uint8_t> valueToByteList<QPointF>(const QPointF &value);
// Конвертация значения QSize в список байтов
template<>
[[nodiscard]]
QVector<uint8_t> valueToByteList<QSize>(const QSize &value);
// Конвертация значения QSizeF в список байтов
template<>
[[nodiscard]]
QVector<uint8_t> valueToByteList<QSizeF>(const QSizeF &value);
// Конвертация значения QRect в список байтов
template<>
[[nodiscard]]
QVector<uint8_t> valueToByteList<QRect>(const QRect &value);
// Конвертация значения QRectF в список байтов
template<>
[[nodiscard]]
QVector<uint8_t> valueToByteList<QRectF>(const QRectF &value);

// Конвертация списка значений в список байтов
template<typename T>
[[nodiscard]]
QVector<uint8_t> valueListToByteList(const QVector<T> &valueList);
// Конвертация списка значений QColor в список байтов
template<>
[[nodiscard]]
QVector<uint8_t> valueListToByteList(const QVector<QColor> &valueList);

// Получение размера данных по типу
template<typename T>
[[nodiscard]]
constexpr std::size_t getTypeByteSize()
{
    static_assert(std::is_pod_v<T>);

    return sizeof(T);
}
// Получение размера данных для типа QColor
template<>
[[nodiscard]]
constexpr std::size_t getTypeByteSize<QColor>()
{
    return 4;
}
// Получение размера данных для типа QPoint
template<>
[[nodiscard]]
constexpr std::size_t getTypeByteSize<QPoint>()
{
    return 8;
}
// Получение размера данных для типа QPointF
template<>
[[nodiscard]]
constexpr std::size_t getTypeByteSize<QPointF>()
{
    return 16;
}
// Получение размера данных для типа QSize
template<>
[[nodiscard]]
constexpr std::size_t getTypeByteSize<QSize>()
{
    return 8;
}
// Получение размера данных для типа QSizeF
template<>
[[nodiscard]]
constexpr std::size_t getTypeByteSize<QSizeF>()
{
    return 16;
}
// Получение размера данных для типа QRect
template<>
[[nodiscard]]
constexpr std::size_t getTypeByteSize<QRect>()
{
    return 16;
}
// Получение размера данных для типа QRectF
template<>
[[nodiscard]]
constexpr std::size_t getTypeByteSize<QRectF>()
{
    return 32;
}

// Получение размера данных по значению
template<typename T>
[[nodiscard]]
std::size_t getValueByteSize(const T &value);
// Получение размера данных по значению для типа QString
template<>
[[nodiscard]]
std::size_t getValueByteSize<QString>(const QString &value);
// Получение размера данных по значению для типа QColor
template<>
[[nodiscard]]
std::size_t getValueByteSize<QColor>(const QColor&);
// Получение размера данных по значению для типа QPoint
template<>
[[nodiscard]]
std::size_t getValueByteSize<QPoint>(const QPoint&);
// Получение размера данных по значению для типа QPointF
template<>
[[nodiscard]]
std::size_t getValueByteSize<QPointF>(const QPointF&);
// Получение размера данных по значению для типа QSize
template<>
[[nodiscard]]
std::size_t getValueByteSize<QSize>(const QSize&);
// Получение размера данных по значению для типа QSizeF
template<>
[[nodiscard]]
std::size_t getValueByteSize<QSizeF>(const QSizeF&);
// Получение размера данных по значению для типа QRect
template<>
[[nodiscard]]
std::size_t getValueByteSize<QRect>(const QRect&);
// Получение размера данных по значению для типа QRectF
template<>
[[nodiscard]]
std::size_t getValueByteSize<QRectF>(const QRectF&);

////////////////////////////////////////////////////////////
// Реализация функций
////////////////////////////////////////////////////////////

//==========================================================
// Конвертация значения в список байтов
//==========================================================
template<typename T>
QVector<uint8_t> valueToByteList(const T &value)
{
    static_assert(std::is_pod_v<T>);

    constexpr std::size_t typeByteSize = sizeof(T);
    QVector<uint8_t> byteList(typeByteSize);
    std::memcpy(byteList.data(), &value, typeByteSize);

    return byteList;
}

//==============================================================
// Конвертация списка значений в список байтов
//==============================================================
template<typename T>
QVector<uint8_t> valueListToByteList(const QVector<T> &valueList)
{
    static_assert(std::is_pod_v<T>);

    const std::size_t byteSize = valueList.size() * getTypeByteSize<T>();
    QVector<uint8_t> byteList(byteSize);
    std::memcpy(byteList.data(), valueList.constData(), byteSize);

    return byteList;
}

//==============================================================
// Получение размера данных по значению
//==============================================================
template<typename T>
std::size_t getValueByteSize(const T &value)
{
    static_assert(std::is_pod_v<T>);

    return sizeof(value);
}

//==============================================================
#endif // BYTE_CONVERT_H
