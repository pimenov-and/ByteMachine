////////////////////////////////////////////////////////////////
// ByteMachine
// Описание перемещения связи узла
////////////////////////////////////////////////////////////////
#ifndef MOVING_NODE_CONNECTION_H
#define MOVING_NODE_CONNECTION_H

//==============================================================
#include <QPoint>
#include "input_pin.h"
#include "output_pin.h"

//==============================================================
// Описание перемещения связи узла
//==============================================================
struct MovingNodeConnection
{
    // Конструктор по умолчанию
    MovingNodeConnection() = default;
    // Конструктор с параметрами
    MovingNodeConnection(const ShPtrOutputPin &outputPin,
        const QPoint &beginPt, const QPoint &endPt);
    // Конструктор с параметрами
    MovingNodeConnection(const ShPtrInputPin &inputPin,
        const QPoint &beginPt, const QPoint &endPt);

    // Получение признака перемещения
    bool isMove() const;
    // Сброс
    void reset();

    // Выходной пин узла
    ShPtrOutputPin outputPin{nullptr};
    // Входной пин узла
    ShPtrInputPin inputPin{nullptr};
    // Начальная точка
    QPoint beginPt{};
    // Конечная точка
    QPoint endPt{};
};

//==============================================================
#endif // MOVING_NODE_CONNECTION_H
