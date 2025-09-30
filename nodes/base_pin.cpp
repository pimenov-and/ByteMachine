////////////////////////////////////////////////////////////////
// ByteMachine
// Базовый класс пина
////////////////////////////////////////////////////////////////
#include "base_pin.h"
#include <QDebug>

//==============================================================
// Конструктор с параметрами
//==============================================================
BasePin::BasePin(BaseNode *parentNode, int32_t index)
{
    Q_ASSERT(parentNode != nullptr);
    Q_ASSERT_X(index >= 0, "Check index", qPrintable(QString::number(index)));

    parentNode_ = parentNode;
    index_ = index;
}
