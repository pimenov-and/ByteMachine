////////////////////////////////////////////////////////////////
// ByteMachine
// Базовый класс узла
////////////////////////////////////////////////////////////////
#ifndef BASE_NODE_H
#define BASE_NODE_H

//==============================================================
#include <QObject>
#include <QSharedPointer>

//==============================================================
// Базовый класс узла
//==============================================================
class BaseNode : public QObject
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
