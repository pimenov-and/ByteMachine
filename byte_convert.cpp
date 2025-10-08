////////////////////////////////////////////////////////////////
// ByteMachine
// Функции конвертации стандартных типов в байты и обратно
////////////////////////////////////////////////////////////////
#include "byte_convert.h"

//==============================================================
using std::size_t;
using std::copy;

//==============================================================
// Конвертация значения QString в список байтов
//==============================================================
template<>
QVector<uint8_t> valueToByteList<QString>(const QString &value)
{
    const QByteArray ba = value.toUtf8();
    QVector<quint8> values{};
    values.reserve(sizeof(qint32) + ba.size());
    values << valueToByteList<qint32>(ba.size());
    for (const char b: ba)
    {
        values << static_cast<quint8>(b);
    }

    return values;
}

//==============================================================
// Конвертация значения QColor в список байтов
//==============================================================
template<>
QVector<uint8_t> valueToByteList<QColor>(const QColor &value)
{
    const quint8 r = static_cast<quint8>(value.red());
    const quint8 g = static_cast<quint8>(value.green());
    const quint8 b = static_cast<quint8>(value.blue());
    const quint8 a = static_cast<quint8>(value.alpha());

    return QVector<quint8>{r, g, b, a};
}

//==============================================================
// Конвертация значения QPoint в список байтов
//==============================================================
template<>
QVector<quint8> valueToByteList<QPoint>(const QPoint &value)
{
    return valueToByteList(value.x()) + valueToByteList(value.y());
}

//==============================================================
// Конвертация значения QPointF в список байтов
//==============================================================
template<>
QVector<quint8> valueToByteList<QPointF>(const QPointF &value)
{
    return valueToByteList(value.x()) + valueToByteList(value.y());
}

//==============================================================
// Конвертация значения QSize в список байтов
//==============================================================
template<>
QVector<quint8> valueToByteList<QSize>(const QSize &value)
{
    return valueToByteList(value.width()) + valueToByteList(value.height());
}

//==============================================================
// Конвертация значения QSizeF в список байтов
//==============================================================
template<>
QVector<quint8> valueToByteList<QSizeF>(const QSizeF &value)
{
    return valueToByteList(value.width()) + valueToByteList(value.height());
}

//==============================================================
// Конвертация значения QRectF в список байтов
//==============================================================
template<>
QVector<quint8> valueToByteList<QRectF>(const QRectF &value)
{
    return valueToByteList(value.topLeft()) + valueToByteList(value.size());
}

//==============================================================
// Конвертации значения QString в список байтов
//==============================================================
template<>
ByteList valueToByteList2<QString>(const QString &value)
{
    const QByteArray valueByteList = value.toUtf8();
    const qint32 valueByteListSize = static_cast<qint32>(valueByteList.size());
    const quint8 *const pValueByteListSize = reinterpret_cast<const quint8*>(&valueByteListSize);
    ByteList byteList(sizeof(valueByteListSize) + valueByteList.size());
    const auto it = copy(pValueByteListSize, pValueByteListSize + sizeof(valueByteListSize),
        byteList.begin());
    copy(valueByteList.cbegin(), valueByteList.cend(), it);

    return byteList;
}

//==============================================================
// Конвертация значения QColor в список байтов
//==============================================================
template<>
ByteList valueToByteList2<QColor>(const QColor &value)
{
    const quint8 r = static_cast<quint8>(value.red());
    const quint8 g = static_cast<quint8>(value.green());
    const quint8 b = static_cast<quint8>(value.blue());
    const quint8 a = static_cast<quint8>(value.alpha());

    return ByteList{r, g, b, a};
}

//==============================================================
// Конвертация значения QPoint в список байтов
//==============================================================
template<>
ByteList valueToByteList2<QPoint>(const QPoint &value)
{
    const ByteList byteListX = valueToByteList2(value.x());
    const ByteList byteListY = valueToByteList2(value.y());

    ByteList byteList{};
    const auto it = byteList.insert(byteList.cbegin(),
        byteListX.cbegin(), byteListX.cend());
    byteList.insert(it, byteListY.cbegin(), byteListY.cend());

    return byteList;
}

//==============================================================
// Конвертация значения QPointF в список байтов
//==============================================================
template<>
ByteList valueToByteList2<QPointF>(const QPointF &value)
{
    const ByteList byteListX = valueToByteList2(value.x());
    const ByteList byteListY = valueToByteList2(value.y());

    ByteList byteList{};
    const auto it = byteList.insert(byteList.cbegin(),
        byteListX.cbegin(), byteListX.cend());
    byteList.insert(it, byteListY.cbegin(), byteListY.cend());

    return byteList;
}

//==============================================================
// Конвертация значения QSize в список байтов
//==============================================================
template<>
ByteList valueToByteList2<QSize>(const QSize &value)
{
    const ByteList byteListWidth = valueToByteList2(value.width());
    const ByteList byteListHeight = valueToByteList2(value.height());

    ByteList byteList{};
    const auto it = byteList.insert(byteList.cbegin(),
        byteListWidth.cbegin(), byteListWidth.cend());
    byteList.insert(it, byteListHeight.cbegin(), byteListHeight.cend());

    return byteList;
}

//==============================================================
// Конвертация значения QSizeF в список байтов
//==============================================================
template<>
ByteList valueToByteList2<QSizeF>(const QSizeF &value)
{
    const ByteList byteListWidth = valueToByteList2(value.width());
    const ByteList byteListHeight = valueToByteList2(value.height());

    ByteList byteList{};
    const auto it = byteList.insert(byteList.cbegin(),
        byteListWidth.cbegin(), byteListWidth.cend());
    byteList.insert(it, byteListHeight.cbegin(), byteListHeight.cend());

    return byteList;
}

//==============================================================
// Конвертация значения QRect в список байтов
//==============================================================
template<>
ByteList valueToByteList2<QRect>(const QRect &value)
{
    const ByteList byteListTopLeft = valueToByteList2(value.topLeft());
    const ByteList byteListSize = valueToByteList2(value.size());

    ByteList byteList{};
    const auto it = byteList.insert(byteList.cbegin(),
        byteListTopLeft.cbegin(), byteListTopLeft.cend());
    byteList.insert(it, byteListSize.cbegin(), byteListSize.cend());

    return byteList;
}

//==============================================================
// Конвертация значения QRectF в список байтов
//==============================================================
template<>
ByteList valueToByteList2<QRectF>(const QRectF &value)
{
    const ByteList byteListTopLeft = valueToByteList2(value.topLeft());
    const ByteList byteListSize = valueToByteList2(value.size());

    ByteList byteList{};
    const auto it = byteList.insert(byteList.cbegin(),
        byteListTopLeft.cbegin(), byteListTopLeft.cend());
    byteList.insert(it, byteListSize.cbegin(), byteListSize.cend());

    return byteList;
}

//==============================================================
// Конвертация списка значений QColor в список байтов
//==============================================================
template<>
QVector<quint8> valueListToByteList(const QVector<QColor> &valueList)
{
    QVector<quint8> ba{};
    ba.reserve(valueList.size() * static_cast<qint32>(getTypeByteSize<QColor>()));
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
