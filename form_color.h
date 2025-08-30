////////////////////////////////////////////////////////////////
// ByteMachine
// Виджет с цветом
////////////////////////////////////////////////////////////////
#ifndef FORM_COLOR_H
#define FORM_COLOR_H

//==============================================================
#include <QtWidgets>
#include <QColor>
#include "ui_form_color.h"

//==============================================================
namespace Ui
{
    class FormColor;
}

//==============================================================
// Виджет с цветом
//==============================================================
class FormColor : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY sigColorChanged RESET resetColor)
public:
    // Конструткор по умолчанию
    explicit FormColor(QWidget *parent = nullptr);
    // Деструктор
    ~FormColor() override;

    // Получение цвета
    const QColor& color() const;
    // Задание цвета
    void setColor(const QColor &color);
    // Сброс цвета
    void resetColor();
    // Получение признака изменения цвета
    bool isColorChanged() const;
public slots:
    // Функция для изменения цвета
    void slotChangeColor();
signals:
    // Сигнал возникает при изменении цвета
    void sigColorChanged(QColor color);
private:
    // Функция вызывается при перерисовке
    void paintEvent(QPaintEvent*) override;
    // Функция вызывается при нажатии мыши
    void mousePressEvent(QMouseEvent *event) override;

    // Интерфейс пользователя
    Ui::FormColor ui_{};
    // Цвет
    QColor color_{Qt::black};
    // Цвет рамки
    QColor borderColor_{Qt::darkGray};
};

//==============================================================
#endif // FORM_COLOR_H
