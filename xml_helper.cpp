////////////////////////////////////////////////////////////////
// ByteMachine
// Дополнительные функции для работы с XML
////////////////////////////////////////////////////////////////
#include "xml_helper.h"
#include <QDomElement>

//==============================================================
using std::optional;
using std::nullopt;

//==============================================================
// Чтение значения из узла XML
//==============================================================
optional<QString> readValueFromXml(const QDomElement &elem)
{
    Q_ASSERT(!elem.isNull());

    if ((elem.childNodes().count() != 1) || !elem.firstChild().isText())
    {
        return nullopt;
    }

    const QDomText textValue = elem.childNodes().at(0).toText();
    if (textValue.isNull())
    {
        return nullopt;
    }

    return textValue.data();
}

//==============================================================
// Запись значения в узел XML
//==============================================================
void writeValueToXml(QDomDocument &doc, QDomElement &elem,
    const QString &value)
{
    Q_ASSERT(!elem.isNull());

    const QDomText textValue = doc.createTextNode(value);
    elem.appendChild(textValue);
}

//==============================================================
// Преобразование строки в XML формат (добавление кавычек)
//==============================================================
QString strToXmlFormat(const QString &str)
{
    return "\"" + str + "\"";
}

//==============================================================
// Получение строки из XML формата (удаление кавычек)
//==============================================================
optional<QString> strFromXmlFormat(const QString &str)
{
    if ((str.length() < 2) || !str.startsWith("\"") || !str.endsWith("\""))
    {
        return nullopt;
    }

    return str.mid(1, str.length() - 2);
}

//==============================================================
// Чтение QPoint из XML
//==============================================================
optional<QPoint> readPointFromXml(const QDomElement &elem)
{
    Q_ASSERT(!elem.isNull());

    const QString strX = elem.attribute("x");
    bool ok = false;
    const int x = strX.toInt(&ok);
    if (!ok)
    {
        return nullopt;
    }

    const QString strY = elem.attribute("y");
    const int y = strY.toInt(&ok);
    if (!ok)
    {
        return nullopt;
    }

    return QPoint{x, y};
}

//==============================================================
// Запись QPoint в XML
//==============================================================
void writePointToXml(QDomElement &elem, const QPoint &point)
{
    Q_ASSERT(!elem.isNull());

    elem.setAttribute("x", point.x());
    elem.setAttribute("y", point.y());
}

//==============================================================
// Чтение QPointF из XML
//==============================================================
std::optional<QPointF> readPointfFromXml(const QDomElement &elem)
{
    Q_ASSERT(!elem.isNull());

    const QString strX = elem.attribute("x");
    bool ok = false;
    const double x = strX.toDouble(&ok);
    if (!ok)
    {
        return nullopt;
    }

    const QString strY = elem.attribute("y");
    const double y = strY.toDouble(&ok);
    if (!ok)
    {
        return nullopt;
    }

    return QPointF{x, y};
}

//==============================================================
// Запись QPointF в XML
//==============================================================
void writePointfToXml(QDomElement &elem, const QPointF &point)
{
    Q_ASSERT(!elem.isNull());

    elem.setAttribute("x", point.x());
    elem.setAttribute("y", point.y());
}

//==============================================================
// Чтение QLine из XML
//==============================================================
optional<QLine> readLineFromXml(const QDomElement &elem)
{
    Q_ASSERT(!elem.isNull());

    const QString strX1 = elem.attribute("x1");
    bool ok = false;
    const int x1 = strX1.toInt(&ok);
    if (!ok)
    {
        return nullopt;
    }

    const QString strY1 = elem.attribute("y1");
    const int y1 = strY1.toInt(&ok);
    if (!ok)
    {
        return nullopt;
    }

    const QString strX2 = elem.attribute("x2");
    const int x2 = strX2.toInt(&ok);
    if (!ok)
    {
        return nullopt;
    }

    const QString strY2 = elem.attribute("x2");
    const int y2 = strY2.toInt(&ok);
    if (!ok)
    {
        return nullopt;
    }

    return QLine{x1, y1, x2, y2};
}

//==============================================================
// Запись QLine в XML
//==============================================================
void writeLineToXml(QDomElement &elem, const QLine &line)
{
    Q_ASSERT(!elem.isNull());

    elem.setAttribute("x1", line.x1());
    elem.setAttribute("y1", line.y1());
    elem.setAttribute("x2", line.x2());
    elem.setAttribute("y2", line.y2());
}

//==============================================================
// Чтение QLineF из XML
//==============================================================
optional<QLineF> readLinefFromXml(const QDomElement &elem)
{
    Q_ASSERT(!elem.isNull());

    bool ok = false;
    const QString strX1 = elem.attribute("x1");
    const double x1 = strX1.toDouble(&ok);
    if (!ok)
    {
        return nullopt;
    }

    const QString strY1 = elem.attribute("y1");
    const double y1 = strY1.toInt(&ok);
    if (!ok)
    {
        return nullopt;
    }

    const QString strX2 = elem.attribute("x2");
    const double x2 = strX2.toInt(&ok);
    if (!ok)
    {
        return nullopt;
    }

    const QString strY2 = elem.attribute("y2");
    const double y2 = strY2.toInt(&ok);
    if (!ok)
    {
        return nullopt;
    }

    return QLineF{x1, y1, x2, y2};
}

//==============================================================
// Запись QLineF в XML
//==============================================================
void writeLinefToXml(QDomElement &elem, const QLineF &line)
{
    Q_ASSERT(!elem.isNull());

    elem.setAttribute("x1", line.x1());
    elem.setAttribute("y1", line.y1());
    elem.setAttribute("x2", line.x2());
    elem.setAttribute("y2", line.y2());
}

//==============================================================
// Чтение QRect из XML
//==============================================================
optional<QRect> readRectFromXml(const QDomElement &elem)
{
    Q_ASSERT(!elem.isNull());

    bool ok = false;
    const QString strLeft = elem.attribute("left");
    const int left = strLeft.toInt(&ok);
    if (!ok)
    {
        return nullopt;
    }

    const QString strTop = elem.attribute("top");
    const int top = strTop.toInt(&ok);
    if (!ok)
    {
        return nullopt;
    }

    const QString strWidth = elem.attribute("width");
    const int width = strWidth.toInt(&ok);
    if (!ok)
    {
        return nullopt;
    }

    const QString strHeight = elem.attribute("height");
    const int height = strHeight.toInt(&ok);
    if (!ok)
    {
        return nullopt;
    }

    return QRect{left, top, width, height};
}

//==============================================================
// Запись QRect в XML
//==============================================================
void writeRectToXml(QDomElement &elem, const QRect &rect)
{
    Q_ASSERT(!elem.isNull());

    elem.setAttribute("left", rect.left());
    elem.setAttribute("top", rect.top());
    elem.setAttribute("width", rect.width());
    elem.setAttribute("height", rect.height());
}

//==============================================================
// Чтение QRectF из XML
//==============================================================
optional<QRectF> readRectfFromXml(const QDomElement &elem)
{
    Q_ASSERT(!elem.isNull());

    bool ok = false;
    const QString strLeft = elem.attribute("left");
    const double left = strLeft.toDouble(&ok);
    if (!ok)
    {
        return nullopt;
    }

    const QString strTop = elem.attribute("top");
    const double top = strTop.toDouble(&ok);
    if (!ok)
    {
        return nullopt;
    }

    const QString strWidth = elem.attribute("width");
    const double width = strWidth.toDouble(&ok);
    if (!ok)
    {
        return nullopt;
    }

    const QString strHeight = elem.attribute("height");
    const double height = strHeight.toDouble(&ok);
    if (!ok)
    {
        return nullopt;
    }

    return QRectF{left, top, width, height};
}

//==============================================================
// Запись QRectF в XML
//==============================================================
void writeRectfToXml(QDomElement &elem, const QRectF &rect)
{
    Q_ASSERT(!elem.isNull());

    elem.setAttribute("left", rect.left());
    elem.setAttribute("top", rect.top());
    elem.setAttribute("width", rect.width());
    elem.setAttribute("height", rect.height());
}
