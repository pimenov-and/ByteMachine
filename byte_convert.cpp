////////////////////////////////////////////////////////////////
// ByteMachine
// Функции конвертации стандартных типов в байты и обратно
////////////////////////////////////////////////////////////////
#include "byte_convert.h"

//==============================================================
using std::size_t;

//==============================================================
// Конвертация значения QString в список байтов
//==============================================================
template<>
QVector<uint8_t> valueToByteList<QString>(const QString &value)
{
    const QByteArray ba = value.toUtf8();
    QVector<uint8_t> values{};
    values.reserve(sizeof(int32_t) + ba.size());
    values << valueToByteList<int32_t>(ba.size());
    for (const char b: ba)
    {
        values << static_cast<uint8_t>(b);
    }

    return values;
}

//==============================================================
// Конвертация значения QColor в список байтов
//==============================================================
template<>
QVector<uint8_t> valueToByteList<QColor>(const QColor &value)
{
    const uint8_t r = static_cast<uint8_t>(value.red());
    const uint8_t g = static_cast<uint8_t>(value.green());
    const uint8_t b = static_cast<uint8_t>(value.blue());
    const uint8_t a = static_cast<uint8_t>(value.alpha());

    return QVector<uint8_t>{r, g, b, a};
}

//==============================================================
// Конвертация значения QPoint в список байтов
//==============================================================
template<>
QVector<uint8_t> valueToByteList<QPoint>(const QPoint &value)
{
    return valueToByteList(value.x()) + valueToByteList(value.y());
}

//==============================================================
// Конвертация значения QPointF в список байтов
//==============================================================
template<>
QVector<uint8_t> valueToByteList<QPointF>(const QPointF &value)
{
    return valueToByteList(value.x()) + valueToByteList(value.y());
}

//==============================================================
// Конвертация значения QSize в список байтов
//==============================================================
template<>
QVector<uint8_t> valueToByteList<QSize>(const QSize &value)
{
    return valueToByteList(value.width()) + valueToByteList(value.height());
}

//==============================================================
// Конвертация значения QSizeF в список байтов
//==============================================================
template<>
QVector<uint8_t> valueToByteList<QSizeF>(const QSizeF &value)
{
    return valueToByteList(value.width()) + valueToByteList(value.height());
}

//==============================================================
// Конвертация значения QRectF в список байтов
//==============================================================
template<>
QVector<uint8_t> valueToByteList<QRectF>(const QRectF &value)
{
    return valueToByteList(value.topLeft()) + valueToByteList(value.size());
}

//==============================================================
// Конвертация списка значений QColor в список байтов
//==============================================================
template<>
QVector<uint8_t> valueListToByteList(const QVector<QColor> &valueList)
{
    QVector<uint8_t> ba{};
    ba.reserve(valueList.size() * static_cast<int>(getTypeByteSize<QColor>()));
    for (const QColor &value: valueList)
    {
        ba << valueToByteList(value);
    }

    return ba;
}

//==============================================================
// Получение размера данных по значению для типа QString
//==============================================================
template<>
size_t getValueByteSize<QString>(const QString &value)
{
    return valueToByteList(value).size();
}

//==============================================================
// Получение размера данных по значению для типа QColor
//==============================================================
template<>
size_t getValueByteSize<QColor>(const QColor&)
{
    return getTypeByteSize<QColor>();
}

//==============================================================
// Получение размера данных по значению для типа QPoint
//==============================================================
template<>
size_t getValueByteSize<QPoint>(const QPoint&)
{
    return getTypeByteSize<QPoint>();
}

//==============================================================
// Получение размера данных по значению для типа QPointF
//==============================================================
template<>
size_t getValueByteSize<QPointF>(const QPointF&)
{
    return getTypeByteSize<QPointF>();
}

//==============================================================
// Получение размера данных по значению для типа QSize
//==============================================================
template<>
size_t getValueByteSize<QSize>(const QSize&)
{
    return getTypeByteSize<QSize>();
}

//==============================================================
// Получение размера данных по значению для типа QSizeF
//==============================================================
template<>
size_t getValueByteSize<QSizeF>(const QSizeF&)
{
    return getTypeByteSize<QSizeF>();
}

//==============================================================
// Получение размера данных по значению для типа QRect
//==============================================================
template<>
size_t getValueByteSize<QRect>(const QRect&)
{
    return getTypeByteSize<QRect>();
}

//==============================================================
// Получение размера данных по значению для типа QRectF
//==============================================================
template<>
size_t getValueByteSize<QRectF>(const QRectF&)
{
    return getTypeByteSize<QRectF>();
}
