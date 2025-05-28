////////////////////////////////////////////////////////////////
// ByteMachine
// Виджет дизайнера
////////////////////////////////////////////////////////////////
#include "form_designer.h"
#include "ui_form_designer.h"
#include <QPainter>
#include <QPaintEvent>

//==============================================================
// Конструктор с параметром
//==============================================================
FormDesigner::FormDesigner(QWidget *parent) : QWidget{parent},
    ui_{new Ui::FormDesigner{}}
{
    ui_->setupUi(this);

    setConnections();
}

//==============================================================
// Деструктор
//==============================================================
FormDesigner::~FormDesigner()
{
    delete ui_;
}

//==============================================================
// Функция вызывается при перерисовке
//==============================================================
void FormDesigner::paintEvent(QPaintEvent *event)
{
    QPainter painter{this};
    const QRect &clipRect = event->rect();

    fillBackgound(&painter, clipRect);
    drawGrid(&painter);
}

//==============================================================
// Задание соединений
//==============================================================
void FormDesigner::setConnections()
{
}

//==============================================================
// Заливка фона
//==============================================================
void FormDesigner::fillBackgound(QPainter *painter, const QRect &clipRect) const
{
    painter->fillRect(clipRect, Qt::white);
}

//==============================================================
// Вывод сетки
//==============================================================
void FormDesigner::drawGrid(QPainter *painter) const
{
    const QColor color{225, 225, 225};
    painter->setPen(color);

    constexpr int gridSize = 20;
    for (int i = gridSize; i < width(); i += gridSize)
    {
        painter->drawLine(i, 0, i, height());
    }
    for (int i = gridSize; i < height(); i += gridSize)
    {
        painter->drawLine(0, i, width(), i);
    }
}
