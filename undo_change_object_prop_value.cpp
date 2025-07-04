////////////////////////////////////////////////////////////////
// ByteMachine
// Функция отмены для операции задания имени проекта
////////////////////////////////////////////////////////////////
#include "undo_change_object_prop_value.h"

//==============================================================
// Конструктор с параметрами
//==============================================================
UndoChangeObjectPropValue::UndoChangeObjectPropValue(QObject *object,
    const QString &propName, const QVariant &propValue,
    const QVariant &oldPropValue)
{
    Q_ASSERT(object != nullptr);
    Q_ASSERT(!propName.isEmpty());

    object_ = object;
    propName_ = propName;
    propValue_ = propValue;
    oldPropValue_ = oldPropValue;
}

//==============================================================
// Деструктор
//==============================================================
UndoChangeObjectPropValue::~UndoChangeObjectPropValue()
{
}

//==============================================================
// Функция отмены
//==============================================================
void UndoChangeObjectPropValue::undo()
{
    object_->setProperty("isUndo", true);
    object_->setProperty(propName_.toStdString().c_str(), oldPropValue_);
    object_->setProperty("isUndo", false);
}

//==============================================================
// Функция восстановления
//==============================================================
void UndoChangeObjectPropValue::redo()
{
    object_->setProperty("isUndo", true);
    object_->setProperty(propName_.toStdString().c_str(), propValue_);
    object_->setProperty("isUndo", false);
}
