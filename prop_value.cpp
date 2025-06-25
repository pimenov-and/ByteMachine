////////////////////////////////////////////////////////////////
// ByteMachine
// Описание значения свойства
////////////////////////////////////////////////////////////////
#include "prop_value.h"

//==============================================================
// Конструктор с параметрами
//==============================================================
PropValue::PropValue(const QString &name, const QVariant &value,
    const QVariant &oldValue)
{
    Q_ASSERT(!name.isEmpty());

    this->name = name;
    this->value = value;
    this->oldValue = oldValue;
    // this->isUndo = isUndo;
}
