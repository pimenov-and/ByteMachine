////////////////////////////////////////////////////////////////
// ByteMachine
// Команда отмены значения свойства объекта
////////////////////////////////////////////////////////////////
#include "undo_change_object_prop_value.h"
#include "base_node.h"
#include "project.h"

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

    // Задание наименования отмены
    if (object != project())
    {
        const auto node = qobject_cast<BaseNode*>(object);
        Q_ASSERT(node != nullptr);
        if ((propName == "top") || (propName == "left") || (propName == "topLeft"))
        {
            setText(QString{"Move node \"%1\""}.arg(node->name()));
        }
        else if ((propName == "width") || (propName == "height"))
        {
            setText(QString{"Resize node \"%1\""}.arg(node->name()));
        }
        else
        {
            const QString uiPropName = node->getUiPropertyName(propName);
            setText(QString{"Change property \"%1\" of node \"%2\""}.
                arg(uiPropName, node->name()));
        }
    }
    else
    {
        setText(QString{"Change property \"%1\" of Project"}.arg(propName));
    }
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
