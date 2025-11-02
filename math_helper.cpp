////////////////////////////////////////////////////////////////
// ByteMachine
// Дополнительные математические функции
////////////////////////////////////////////////////////////////
#include "math_helper.h"
#include <cmath>

//==============================================================
// Расчёт угла по двум точкам QPointF
//==============================================================
double calcAngle(const QPointF &beginPt, const QPointF &endPt)
{
    if (beginPt == endPt)
    {
        return 0;
    }

    const double x = endPt.x() - beginPt.x();
    const double y = endPt.y() - beginPt.y();

    return atan2(y, x);
}
