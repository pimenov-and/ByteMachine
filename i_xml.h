////////////////////////////////////////////////////////////////
// ByteMachine
// Интерфейс для работы с XML
////////////////////////////////////////////////////////////////
#ifndef I_XML_H
#define I_XML_H

//==============================================================
class QDomDocument;
class QDomElement;

//==============================================================
// Интерфейс для работы с XML
//==============================================================
struct IXml
{
    // Деструктор
    virtual ~IXml() = default;

    // Чтение из XML
    virtual void readFromXml(const QDomElement &elem) = 0;
    // Запись в XML
    virtual void writeToXml(QDomDocument &doc, QDomElement &elem) const = 0;
};

//==============================================================
#endif // I_XML_H
