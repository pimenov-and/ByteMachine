////////////////////////////////////////////////////////////////
// ByteMachine
// Продвинутый SpinBox
////////////////////////////////////////////////////////////////
#ifndef FORM_ADV_SPIN_BOX_H
#define FORM_ADV_SPIN_BOX_H

//==============================================================
#include <QSpinBox>

//==============================================================
// Продвинутый SpinBox
//==============================================================
class FormAdvSpinBox : public QSpinBox
{
    Q_OBJECT
public:
    // Конструктор с параметром
    explicit FormAdvSpinBox(QWidget *parent = nullptr);
    // Деструктор
    ~FormAdvSpinBox() override;
private:
    // Функция перевода значения в строку
    QString textFromValue(int value) const override;
};

//==============================================================
#endif // FORM_ADV_SPIN_BOX_H
