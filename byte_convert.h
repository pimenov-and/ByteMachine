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
QVector<quint8> valueToByteList(const T &value);
// Конвертации значения QString в список байтов
template<>
[[nodiscard]]
QVector<quint8> valueToByteList<QString>(const QString &value);
// Конвертация значения QColor в список байтов
template<>
[[nodiscard]]
QVector<quint8> valueToByteList<QColor>(const QColor &value);
// Конвертация значения QPoint в список байтов
template<>
[[nodiscard]]
QVector<quint8> valueToByteList<QPoint>(const QPoint &value);
// Конвертация значения QPointF в список байтов
template<>
[[nodiscard]]
QVector<quint8> valueToByteList<QPointF>(const QPointF &value);
// Конвертация значения QSize в список байтов
template<>
[[nodiscard]]
QVector<quint8> valueToByteList<QSize>(const QSize &value);
// Конвертация значения QSizeF в список байтов
template<>
[[nodiscard]]
QVector<quint8> valueToByteList<QSizeF>(const QSizeF &value);
// Конвертация значения QRect в список байтов
template<>
[[nodiscard]]
QVector<quint8> valueToByteList<QRect>(const QRect &value);
// Конвертация значения QRectF в список байтов
template<>
[[nodiscard]]
QVector<quint8> valueToByteList<QRectF>(const QRectF &value);

// Конвертация списка значений в список байтов
template<typename T>
[[nodiscard]]
QVector<quint8> valueListToByteList(const QVector<T> &valueList);
// Конвертация списка значений QColor в список байтов
template<>
[[nodiscard]]
QVector<quint8> valueListToByteList(const QVector<QColor> &valueList);

// Получение размера данных по типу
template<typename T>
[[nodiscard]]
constexpr int getTypeByteSize()
{
    static_assert(std::is_pod_v<T>);

    return static_cast<int>(sizeof(T));
}
// Получение размера данных для типа QColor
template<>
[[nodiscard]]
constexpr int getTypeByteSize<QColor>()
{
    return 4;
}
// Получение размера данных для типа QPoint
template<>
[[nodiscard]]
constexpr int getTypeByteSize<QPoint>()
{
    return 8;
}
// Получение размера данных для типа QPointF
template<>
[[nodiscard]]
constexpr int getTypeByteSize<QPointF>()
{
    return 16;
}
// Получение размера данных для типа QSize
template<>
[[nodiscard]]
constexpr int getTypeByteSize<QSize>()
{
    return 8;
}
// Получение размера данных для типа QSizeF
template<>
[[nodiscard]]
constexpr int getTypeByteSize<QSizeF>()
{
    return 16;
}
// Получение размера данных для типа QRect
template<>
[[nodiscard]]
constexpr int getTypeByteSize<QRect>()
{
    return 16;
}
// Получение размера данных для типа QRectF
template<>
[[nodiscard]]
constexpr int getTypeByteSize<QRectF>()
{
    return 32;
}

// Получение размера данных по значению
template<typename T>
[[nodiscard]]
int getValueByteSize(const T &value);
// Получение размера данных по значению для типа QString
template<>
[[nodiscard]]
int getValueByteSize<QString>(const QString &value);
// Получение размера данных по значению для типа QColor
template<>
[[nodiscard]]
int getValueByteSize<QColor>(const QColor&);
// Получение размера данных по значению для типа QPoint
template<>
[[nodiscard]]
int getValueByteSize<QPoint>(const QPoint&);
// Получение размера данных по значению для типа QPointF
template<>
[[nodiscard]]
int getValueByteSize<QPointF>(const QPointF&);
// Получение размера данных по значению для типа QSize
template<>
[[nodiscard]]
int getValueByteSize<QSize>(const QSize&);
// Получение размера данных по значению для типа QSizeF
template<>
[[nodiscard]]
int getValueByteSize<QSizeF>(const QSizeF&);
// Получение размера данных по значению для типа QRect
template<>
[[nodiscard]]
int getValueByteSize<QRect>(const QRect&);
// Получение размера данных по значению для типа QRectF
template<>
[[nodiscard]]
int getValueByteSize<QRectF>(const QRectF&);

////////////////////////////////////////////////////////////
// Реализация функций
////////////////////////////////////////////////////////////

//==========================================================
// Конвертация значения в список байтов
//==========================================================
template<typename T>
QVector<quint8> valueToByteList(const T &value)
{
    static_assert(std::is_pod_v<T>);

    constexpr qint32 typeByteSize = sizeof(T);
    QVector<quint8> byteList(typeByteSize);
    std::memcpy(byteList.data(), &value, typeByteSize);

    return byteList;
}

//==============================================================
// Конвертация списка значений в список байтов
//==============================================================
template<typename T>
QVector<quint8> valueListToByteList(const QVector<T> &valueList)
{
    static_assert(std::is_pod_v<T>);

    const qint32 byteSize = valueList.size() * getTypeByteSize<T>();
    QVector<quint8> byteList(byteSize);
    std::memcpy(byteList.data(), valueList.constData(), byteSize);

    return byteList;
}

//==============================================================
// Получение размера данных по значению
//==============================================================
template<typename T>
int getValueByteSize(const T &value)
{
    static_assert(std::is_pod_v<T>);

    return static_cast<int>(sizeof(value));
}

//==============================================================
#endif // BYTE_CONVERT_H
