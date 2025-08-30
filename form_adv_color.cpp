/////////////////////////////////////////////////////////////////////
// ByteMachine
// Виджет для настройки цвета
/////////////////////////////////////////////////////////////////////
#include "form_adv_color.h"
#include "form_color.h"
#include <QColorDialog>
#include <QDebug>

//===================================================================
// Конструктор с параметром
//===================================================================
FormAdvColor::FormAdvColor(QWidget *parent) : QWidget{parent}
{
    ui_.setupUi(this);

#ifdef Q_OS_WASM
    ui_.widgetColor_->setCursor(Qt::ArrowCursor);
    ui_.widgetColor_->setEnabled(false);
#endif // Q_OS_WASM

    setConnections();
}

//===================================================================
// Деструктор
//===================================================================
FormAdvColor::~FormAdvColor()
{
}

//===================================================================
// Получение цвета
//===================================================================
QColor FormAdvColor::color() const
{
    return ui_.widgetColor_->color();
}

//===================================================================
// Задание цвета
//===================================================================
void FormAdvColor::setColor(const QColor &color)
{
    ui_.widgetColor_->setColor(color);
}

//===================================================================
// Сброс цвета
//===================================================================
void FormAdvColor::resetColor()
{
    ui_.widgetColor_->resetColor();
}

//===================================================================
// Получение слайдера с красной составляющей цвета
//===================================================================
QSlider* FormAdvColor::sliderRed()
{
    return ui_.horzSliderRed_;
}

//===================================================================
// Получение слайдера с красной составляющей цвета (константный вариант)
//===================================================================
const QSlider* FormAdvColor::sliderRed() const
{
    return ui_.horzSliderRed_;
}

//===================================================================
// Получение слайдера с зелёной составляющей цвета
//===================================================================
QSlider* FormAdvColor::sliderGreen()
{
    return ui_.horzSliderGreen_;
}

//===================================================================
// Получение слайдера с зелёной составляющей цвета (константный вариант)
//===================================================================
const QSlider* FormAdvColor::sliderGreen() const
{
    return ui_.horzSliderGreen_;
}

//===================================================================
// Получение слайдера с синей составляющей цвета
//===================================================================
QSlider* FormAdvColor::sliderBlue()
{
    return ui_.horzSliderBlue_;
}

//===================================================================
// Получение слайдера с синей составляющей цвета (константный вариант)
//===================================================================
const QSlider* FormAdvColor::sliderBlue() const
{
    return ui_.horzSliderBlue_;
}

//===================================================================
// Получение слайдера с прозрачной составляющей цвета
//===================================================================
QSlider* FormAdvColor::sliderAlpha()
{
    return ui_.horzSliderAlpha_;
}

//===================================================================
// Получение слайдера с прозрачной составляющей цвета (константный вариант)
//===================================================================
const QSlider* FormAdvColor::sliderAlpha() const
{
    return ui_.horzSliderAlpha_;
}

//===================================================================
// Получение спин-бокс с красной составляющей цвета
//===================================================================
QSpinBox* FormAdvColor::spinBoxRed()
{
    return ui_.spinBoxRed_;
}

//===================================================================
// Получение спин-бокс с красной составляющей цвета (константный вариант)
//===================================================================
const QSpinBox* FormAdvColor::spinBoxRed() const
{
    return ui_.spinBoxRed_;
}

//===================================================================
// Получение спин-бокс с зелёной составляющей цвета
//===================================================================
QSpinBox* FormAdvColor::spinBoxGreen()
{
    return ui_.spinBoxGreen_;
}

//===================================================================
// Получение спин-бокс с зелёной составляющей цвета (константный вариант)
//===================================================================
const QSpinBox* FormAdvColor::spinBoxGreen() const
{
    return ui_.spinBoxGreen_;
}

//===================================================================
// Получение спин-бокс с синей составляющей цвета
//===================================================================
QSpinBox* FormAdvColor::spinBoxBlue()
{
    return ui_.spinBoxBlue_;
}

//===================================================================
// Получение спин-бокс с синей составляющей цвета (константный вариант)
//===================================================================
const QSpinBox* FormAdvColor::spinBoxBlue() const
{
    return ui_.spinBoxBlue_;
}

//===================================================================
// Получение спин-бокс с прозрачной составляющей цвета
//===================================================================
QSpinBox* FormAdvColor::spinBoxAlpha()
{
    return ui_.spinBoxAlpha_;
}

//===================================================================
// Получение спин-бокс с прозрачной составляющей цвета (константный вариант)
//===================================================================
const QSpinBox* FormAdvColor::spinBoxAlpha() const
{
    return ui_.spinBoxAlpha_;
}

//===================================================================
// Функция вызывается при изменении цвета
//===================================================================
void FormAdvColor::slotChangedColor(QColor color)
{
    blockWidgetSignals(true);
    ui_.spinBoxRed_->setValue(color.red());
    ui_.spinBoxGreen_->setValue(color.green());
    ui_.spinBoxBlue_->setValue(color.blue());
    ui_.spinBoxAlpha_->setValue(color.alpha());
    ui_.horzSliderRed_->setValue(color.red());
    ui_.horzSliderGreen_->setValue(color.green());
    ui_.horzSliderBlue_->setValue(color.blue());
    ui_.horzSliderAlpha_->setValue(color.alpha());
    blockWidgetSignals(false);

    emit sigColorChanged(color);
}

//===================================================================
// Функция вызывается при изменении составляющей Red цвета через спин-бокс
//===================================================================
void FormAdvColor::slotChangedSpinBoxRed(int value)
{
    blockWidgetSignals(true);
    ui_.horzSliderRed_->setValue(value);
    blockWidgetSignals(false);

    const QColor color = colorFromSpinEdits();
    ui_.widgetColor_->setColor(color);

    ui_.spinBoxRed_->setFocus();
}

//===================================================================
// Функция вызывается при изменении составляющей Green цвета через спин-бокс
//===================================================================
void FormAdvColor::slotChangedSpinBoxGreen(int value)
{
    blockWidgetSignals(true);
    ui_.horzSliderGreen_->setValue(value);
    blockWidgetSignals(false);

    const QColor color = colorFromSpinEdits();
    ui_.widgetColor_->setColor(color);

    ui_.spinBoxGreen_->setFocus();
}

//===================================================================
// Функция вызывается при изменении составляющей Blue цвета через спин-бокс
//===================================================================
void FormAdvColor::slotChangedSpinBoxBlue(int value)
{
    blockWidgetSignals(true);
    ui_.horzSliderBlue_->setValue(value);
    blockWidgetSignals(false);

    const QColor color = colorFromSpinEdits();
    ui_.widgetColor_->setColor(color);

    ui_.spinBoxBlue_->setFocus();
}

//===================================================================
// Функция вызывается при изменении составляющей Alpha цвета через спин-бокс
//===================================================================
void FormAdvColor::slotChangedSpinBoxAlpha(int value)
{
    blockWidgetSignals(true);
    ui_.horzSliderAlpha_->setValue(value);
    blockWidgetSignals(false);

    const QColor color = colorFromSpinEdits();
    ui_.widgetColor_->setColor(color);

    ui_.spinBoxAlpha_->setFocus();
}

//===================================================================
// Функция вызывается при изменении составляющей Red цвета через комбо-бокс
//===================================================================
void FormAdvColor::slotChangedSliderRed(int value)
{
    blockWidgetSignals(true);
    ui_.spinBoxRed_->setValue(value);
    blockWidgetSignals(false);

    const QColor color = colorFromSliders();
    ui_.widgetColor_->setColor(color);

    ui_.horzSliderRed_->setFocus();
}

//===================================================================
// Функция вызывается при изменении составляющей Green цвета через комбо-бокс
//===================================================================
void FormAdvColor::slotChangedSliderGreen(int value)
{
    blockWidgetSignals(true);
    ui_.spinBoxGreen_->setValue(value);
    blockWidgetSignals(false);

    const QColor color = colorFromSliders();
    ui_.widgetColor_->setColor(color);

    ui_.horzSliderGreen_->setFocus();
}

//===================================================================
// Функция вызывается при изменении составляющей Blue цвета через комбо-бокс
//===================================================================
void FormAdvColor::slotChangedSliderBlue(int value)
{
    blockWidgetSignals(true);
    ui_.spinBoxBlue_->setValue(value);
    blockWidgetSignals(false);

    const QColor color = colorFromSliders();
    ui_.widgetColor_->setColor(color);

    ui_.horzSliderBlue_->setFocus();
}

//===================================================================
// Функция вызывается при изменении составляющей Alpha цвет через комбо-бокс
//===================================================================
void FormAdvColor::slotChangedSliderAlpha(int value)
{
    blockWidgetSignals(true);
    ui_.spinBoxAlpha_->setValue(value);
    blockWidgetSignals(false);

    const QColor color = colorFromSliders();
    ui_.widgetColor_->setColor(color);

    ui_.horzSliderAlpha_->setFocus();
}

//===================================================================
// Задание соединений
//===================================================================
void FormAdvColor::setConnections() noexcept
{
    connect(ui_.spinBoxRed_, qOverload<int>(&QSpinBox::valueChanged),
        this, &FormAdvColor::slotChangedSpinBoxRed);
    connect(ui_.horzSliderRed_, qOverload<int>(&QSlider::valueChanged),
        this, &FormAdvColor::slotChangedSliderRed);

    connect(ui_.spinBoxGreen_, qOverload<int>(&QSpinBox::valueChanged),
        this, &FormAdvColor::slotChangedSpinBoxGreen);
    connect(ui_.horzSliderGreen_, qOverload<int>(&QSlider::valueChanged),
        this, &FormAdvColor::slotChangedSliderGreen);

    connect(ui_.spinBoxBlue_, qOverload<int>(&QSpinBox::valueChanged),
        this, &FormAdvColor::slotChangedSpinBoxBlue);
    connect(ui_.horzSliderBlue_, qOverload<int>(&QSlider::valueChanged),
        this, &FormAdvColor::slotChangedSliderBlue);

    connect(ui_.spinBoxAlpha_, qOverload<int>(&QSpinBox::valueChanged),
        this, &FormAdvColor::slotChangedSpinBoxAlpha);
    connect(ui_.horzSliderAlpha_, qOverload<int>(&QSlider::valueChanged),
        this, &FormAdvColor::slotChangedSliderAlpha);

    connect(ui_.widgetColor_, &FormColor::sigColorChanged,
            this, &FormAdvColor::slotChangedColor);
}

//===================================================================
// Блокировка сигналов виджетов
//===================================================================
void FormAdvColor::blockWidgetSignals(bool isBlock) noexcept
{
    ui_.spinBoxRed_->blockSignals(isBlock);
    ui_.spinBoxGreen_->blockSignals(isBlock);
    ui_.spinBoxBlue_->blockSignals(isBlock);
    ui_.spinBoxAlpha_->blockSignals(isBlock);

    ui_.horzSliderRed_->blockSignals(isBlock);
    ui_.horzSliderGreen_->blockSignals(isBlock);
    ui_.horzSliderBlue_->blockSignals(isBlock);
    ui_.horzSliderAlpha_->blockSignals(isBlock);
}

//===================================================================
// Получение цвета из слайдеров
//===================================================================
QColor FormAdvColor::colorFromSliders() const noexcept
{
    const int red = ui_.horzSliderRed_->value();
    const int green = ui_.horzSliderGreen_->value();
    const int blue = ui_.horzSliderBlue_->value();
    const int alpha = ui_.horzSliderAlpha_->value();

    return QColor{red, green, blue, alpha};
}

//===================================================================
// Получение цвета из спин-эдитов
//===================================================================
QColor FormAdvColor::colorFromSpinEdits() const noexcept
{
    const int red = ui_.spinBoxRed_->value();
    const int green = ui_.spinBoxGreen_->value();
    const int blue = ui_.spinBoxBlue_->value();
    const int alpha = ui_.spinBoxAlpha_->value();

    return QColor{red, green, blue, alpha};
}
