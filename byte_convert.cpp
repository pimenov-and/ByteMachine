////////////////////////////////////////////////////////////////
// ByteMachine
// Функции конвертации стандартных типов в байты и обратно
////////////////////////////////////////////////////////////////
#include "byte_convert.h"

//==============================================================
// Конвертация значения QString в список байтов
//==============================================================
template<>
QVector<quint8> valueToByteList<QString>(const QString &value)
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
QVector<quint8> valueToByteList<QColor>(const QColor &value)
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
// Конвертация списка значений QColor в список байтов
//==============================================================
template<>
QVector<quint8> valueListToByteList(const QVector<QColor> &valueList)
{
    QVector<quint8> ba{};
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
int getValueByteSize<QString>(const QString &value)
{
    return valueToByteList(value).size();
}

//==============================================================
// Получение размера данных по значению для типа QColor
//==============================================================
template<>
int getValueByteSize<QColor>(const QColor&)
{
    return getTypeByteSize<QColor>();
}

//==============================================================
// Получение размера данных по значению для типа QPoint
//==============================================================
template<>
int getValueByteSize<QPoint>(const QPoint&)
{
    return getTypeByteSize<QPoint>();
}

//==============================================================
// Получение размера данных по значению для типа QPointF
//==============================================================
template<>
int getValueByteSize<QPointF>(const QPointF&)
{
    return getTypeByteSize<QPointF>();
}

//==============================================================
// Получение размера данных по значению для типа QSize
//==============================================================
template<>
int getValueByteSize<QSize>(const QSize&)
{
    return getTypeByteSize<QSize>();
}

//==============================================================
// Получение размера данных по значению для типа QSizeF
//==============================================================
template<>
int getValueByteSize<QSizeF>(const QSizeF&)
{
    return getTypeByteSize<QSizeF>();
}

//==============================================================
// Получение размера данных по значению для типа QRect
//==============================================================
template<>
int getValueByteSize<QRect>(const QRect&)
{
    return getTypeByteSize<QRect>();
}

//==============================================================
// Получение размера данных по значению для типа QRectF
//==============================================================
template<>
int getValueByteSize<QRectF>(const QRectF&)
{
    return getTypeByteSize<QRectF>();
}
