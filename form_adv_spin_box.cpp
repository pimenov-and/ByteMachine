////////////////////////////////////////////////////////////////
// ByteMachine
// Продвинутый SpinBox
////////////////////////////////////////////////////////////////
#include "form_adv_spin_box.h"

//==============================================================
// Конструктор с параметром
//==============================================================
FormAdvSpinBox::FormAdvSpinBox(QWidget *parent) : QSpinBox{parent}
{
}

//==============================================================
// Деструктор
//==============================================================
FormAdvSpinBox::~FormAdvSpinBox()
{
}

//==============================================================
// Функция перевода значения в строку
//==============================================================
QString FormAdvSpinBox::textFromValue(int value) const
{
    if (displayIntegerBase() == 16)
    {
        const QString textValue = QSpinBox::textFromValue(value).toUpper();
        if (textValue.length() == 1)
        {
            return '0' + textValue;
        }
        else
        {
            return textValue;
        }
    }
    else
    {
        return QSpinBox::textFromValue(value);
    }
}
