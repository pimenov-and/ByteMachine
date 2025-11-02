////////////////////////////////////////////////////////////////
// ByteMachine
// Описание перемещения связи узла
////////////////////////////////////////////////////////////////
#include "moving_node_connection.h"

//==============================================================
// Конструктор с параметрами
//==============================================================
MovingNodeConnection::MovingNodeConnection(const ShPtrOutputPin &outputPin,
    const QPoint &beginPt, const QPoint &endPt)
{
    this->outputPin = outputPin;
    this->beginPt = beginPt;
    this->endPt = endPt;
}

//==============================================================
// Конструктор с параметрами
//==============================================================
MovingNodeConnection::MovingNodeConnection(const ShPtrInputPin &inputPin,
    const QPoint &beginPt, const QPoint &endPt)
{
    this->inputPin = inputPin;
    this->beginPt = beginPt;
    this->endPt = endPt;
}

//==============================================================
// Получение признака перемещения
//==============================================================
bool MovingNodeConnection::isMove() const
{
    return (outputPin != nullptr) || (inputPin != nullptr);
}

//==============================================================
// Сброс
//==============================================================
void MovingNodeConnection::reset()
{
    outputPin = nullptr;
    inputPin = nullptr;
    beginPt = endPt = QPoint{};
}
