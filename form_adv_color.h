////////////////////////////////////////////////////////////////
// ByteMachine
// Виджет для настройки цвета
////////////////////////////////////////////////////////////////
#ifndef FORM_ADV_COLOR_H
#define FORM_ADV_COLOR_H

//==============================================================
#include <QWidget>
#include "ui_form_adv_color.h"

//==============================================================
namespace Ui
{
    class FormAdvColor;
}
class QSlider;
class QSpinBox;

//==============================================================
// Виджет для настройки цвета
//==============================================================
class FormAdvColor : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY sigColorChanged RESET resetColor)
public:
    // Конструктор с параметром
    explicit FormAdvColor(QWidget *parent = nullptr);
    // Деструктор
    ~FormAdvColor() override;

    // Получение цвета
    QColor color() const;
    // Задание цвета
    void setColor(const QColor &color);
    // Сброс цвета
    void resetColor();

    // Получение слайдера с красной составляющей цвета
    QSlider* sliderRed();
    // Получение слайдера с красной составляющей цвета (константный вариант)
    const QSlider* sliderRed() const;
    // Получение слайдера с зелёной составляющей цвета
    QSlider* sliderGreen();
    // Получение слайдера с зелёной составляющей цвета (константный вариант)
    const QSlider* sliderGreen() const;
    // Получение слайдера с синей составляющей цвета
    QSlider* sliderBlue();
    // Получение слайдера с синей составляющей цвета (константный вариант)
    const QSlider* sliderBlue() const;
    // Получение слайдера с прозрачной составляющей цвета
    QSlider* sliderAlpha();
    // Получение слайдера с прозрачной составляющей цвета (константный вариант)
    const QSlider* sliderAlpha() const;
    // Получение спин-бокс с красной составляющей цвета
    QSpinBox* spinBoxRed();
    // Получение спин-бокс с красной составляющей цвета (константный вариант)
    const QSpinBox* spinBoxRed() const;
    // Получение спин-бокс с зелёной составляющей цвета
    QSpinBox* spinBoxGreen();
    // Получение спин-бокс с зелёной составляющей цвета (константный вариант)
    const QSpinBox* spinBoxGreen() const;
    // Получение спин-бокс с синей составляющей цвета
    QSpinBox* spinBoxBlue();
    // Получение спин-бокс с синей составляющей цвета (константный вариант)
    const QSpinBox* spinBoxBlue() const;
    // Получение спин-бокс с прозрачной составляющей цвета
    QSpinBox* spinBoxAlpha();
    // Получение спин-бокс с прозрачной составляющей цвета (константный вариант)
    const QSpinBox* spinBoxAlpha() const;
signals:
    // Сигнал возникает при изменении цвета
    void sigColorChanged(QColor color);
private slots:
    // Функция вызывается при изменении цвета
    void slotChangedColor(QColor color);
    // Функция вызывается при изменении составляющей Red цвета через спин-бокс
    void slotChangedSpinBoxRed(int32_t value);
    // Функция вызывается при изменении составляющей Green цвета через спин-бокс
    void slotChangedSpinBoxGreen(int32_t value);
    // Функция вызывается при изменении составляющей Blue цвета через спин-бокс
    void slotChangedSpinBoxBlue(int32_t value);
    // Функция вызывается при изменении составляющей Alpha цвета через спин-бокс
    void slotChangedSpinBoxAlpha(int32_t value);
    // Функция вызывается при изменении составляющей Red цвета через слайдер
    void slotChangedSliderRed(int32_t value);
    // Функция вызывается при изменении составляющей Green цвета через слайдер
    void slotChangedSliderGreen(int32_t value);
    // Функция вызывается при изменении составляющей Blue цвета через слайдер
    void slotChangedSliderBlue(int32_t value);
    // Функция вызывается при изменении составляющей Alpha цвет через слайдер
    void slotChangedSliderAlpha(int32_t value);
private:
    // Задание соединений
    void setConnections() noexcept;
    // Блокировка сигналов виджетов
    void blockWidgetSignals(bool isBlock) noexcept;
    // Получение цвета из слайдеров
    QColor colorFromSliders() const noexcept;
    // Получение цвета из спин-эдитов
    QColor colorFromSpinEdits() const noexcept;

    // Интерфейс пользователя
    Ui::FormAdvColor ui_{};
};

//==============================================================
#endif // FORM_ADV_COLOR_H
