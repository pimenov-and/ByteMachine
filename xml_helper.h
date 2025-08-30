////////////////////////////////////////////////////////////////
// ByteMachine
// Дополнительные функции для работы с XML
////////////////////////////////////////////////////////////////
#ifndef XML_HELPER_H
#define XML_HELPER_H

//==============================================================
#include <QString>
#include <QPoint>
#include <QPointF>
#include <QLine>
#include <QLineF>
#include <QRect>
#include <QRectF>
#include <optional>

//==============================================================
class QDomDocument;
class QDomElement;

//==============================================================
// Прототипы функций
//==============================================================
// Чтение значения из узла XML
std::optional<QString> readValueFromXml(const QDomElement &elem);
// Запись значения в узел XML
void writeValueToXml(QDomDocument &doc, QDomElement &elem,
    const QString &value);
// Преобразование строки в XML формат (добавление кавычек)
QString strToXmlFormat(const QString &str);
// Получение строки из XML формата (удаление кавычек)
std::optional<QString> strFromXmlFormat(const QString &str);

// Чтение QPoint из XML
std::optional<QPoint> readPointFromXml(const QDomElement &elem);
// Запись QPoint в XML
void writePointToXml(QDomElement &elem, const QPoint &point);

// Чтение QPointF из XML
std::optional<QPointF> readPointfFromXml(const QDomElement &elem);
// Запись QPointF в XML
void writePointfToXml(QDomElement &elem, const QPointF &point);

// Чтение QLine из XML
std::optional<QLine> readLineFromXml(const QDomElement &elem);
// Запись QLine в XML
void writeLineToXml(QDomElement &elem, const QLine &line);

// Чтение QLineF из XML
std::optional<QLineF> readLinefFromXml(const QDomElement &elem);
// Запись QLineF в XML
void writeLinefToXml(QDomElement &elem, const QLineF &line);

// Чтение QRect из XML
std::optional<QRect> readRectFromXml(const QDomElement &elem);
// Запись QRect в XML
void writeRectToXml(QDomElement &elem, const QRect &rect);

// Чтение QRectF из XML
std::optional<QRectF> readRectfFromXml(const QDomElement &elem);
// Запись QRectF в XML
void writeRectfToXml(QDomElement &elem, const QRectF &rect);

//==============================================================
#endif // XML_HELPER_H
