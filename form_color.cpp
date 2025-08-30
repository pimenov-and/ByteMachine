////////////////////////////////////////////////////////////////
// ByteMachine
// Виджет с цветом
////////////////////////////////////////////////////////////////
#include "form_color.h"
#include <QPainter>
#include <QMouseEvent>

//==============================================================
// Конструткор по умолчанию
//==============================================================
FormColor::FormColor(QWidget *parent) : QWidget{parent}
{
    ui_.setupUi(this);
}

//==============================================================
// Деструктор
//==============================================================
FormColor::~FormColor()
{
}

//==============================================================
// Получение цвета
//==============================================================
const QColor& FormColor::color() const
{
    return color_;
}

//==============================================================
// Задание цвета
//==============================================================
void FormColor::setColor(const QColor &color)
{
    if (color_ != color)
    {
        color_ = color;
        update();

        emit sigColorChanged(color_);
    }
}

//==============================================================
// Сброс цвета
//==============================================================
void FormColor::resetColor()
{
    if (isColorChanged())
    {
        setColor(Qt::black);
    }
}

//==============================================================
// Получение признака изменения цвета
//==============================================================
bool FormColor::isColorChanged() const
{
    return color_ == Qt::black;
}

//==============================================================
// Функция для изменения цвета
//==============================================================
void FormColor::slotChangeColor()
{
    const QString title = "Select color";
    const QColor color = QColorDialog::getColor(color_, this, title);
    if (color.isValid())
    {
        color_ = color;
        update();

        emit sigColorChanged(color);
    }
}

//==============================================================
// Функция вызывается при перерисовке
//==============================================================
void FormColor::paintEvent(QPaintEvent*)
{
    QPainter painter{this};

    painter.fillRect(rect(), color_);

    painter.setPen(borderColor_);
    painter.setBrush(Qt::transparent);
    painter.drawRect(0, 0, width() - 1, height() - 1);
}

//==============================================================
// Функция вызывается при нажатии мыши
//==============================================================
void FormColor::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        slotChangeColor();
    }
}
