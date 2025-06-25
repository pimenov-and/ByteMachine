////////////////////////////////////////////////////////////////
// ByteMachine
// Описание значения свойства
////////////////////////////////////////////////////////////////
#ifndef PROP_VALUE_H
#define PROP_VALUE_H

//==============================================================
#include <QString>
#include <QVariant>
#include "i_to_str.h"

//==============================================================
// Описание значения свойства
//==============================================================
struct PropValue : public IToStr
{
    // Конструктор по умолчанию
    PropValue() = default;
    // Конструктор с параметрами
    PropValue(const QString &name, const QVariant &value,
        const QVariant &oldValue);

    // Получение представления в виде строки
    QString toStr() const override { return name; }

    // Имя
    QString name{};
    // Значение
    QVariant value{};
    // Старое значение
    QVariant oldValue{};
};

//==============================================================
#endif // PROP_VALUE_H
