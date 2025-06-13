////////////////////////////////////////////////////////////////
// ByteMachine
// Базовый класс узла
////////////////////////////////////////////////////////////////
#ifndef BASE_NODE_H
#define BASE_NODE_H

//==============================================================
#include <QObject>
#include <QSharedPointer>
#include "i_xml.h"
#include "i_to_str.h"

//==============================================================
// Базовый класс узла
//==============================================================
class BaseNode : public QObject, public IXml, public IToStr
{
public:
    // Конструктор с параметром
    explicit BaseNode(QObject *parent = nullptr);
    // Деструктор
    ~BaseNode() override;
private:
};

//==============================================================
using ShPtrBaseNode = QSharedPointer<BaseNode>;
using ShPtrConstBaseNode = QSharedPointer<const BaseNode>;

//==============================================================
#endif // BASE_NODE_H
