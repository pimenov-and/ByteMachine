////////////////////////////////////////////////////////////////
// ByteMachine
// Статус-бар
////////////////////////////////////////////////////////////////
#include "status_bar.h"
#include <QFont>
#include <QPainter>

//==============================================================
// Конструктор с параметром
//==============================================================
StatusBar::StatusBar(QWidget *parent) : QStatusBar{parent}
{
}

//==============================================================
// Деструктор
//==============================================================
StatusBar::~StatusBar()
{
}

//==============================================================
// Функция вызывается при перерисовке
//==============================================================
void StatusBar::paintEvent(QPaintEvent*)
{
    QPainter painter{this};

    fillBackground(&painter);
    drawNumberOfNodes(&painter);
    drawVersionArea(&painter);
}

//==============================================================
// Задание соединений
//==============================================================
void StatusBar::setConnections()
{
}

//==============================================================
// Заливка фона
//==============================================================
void StatusBar::fillBackground(QPainter *painter) const
{
    Q_ASSERT(painter != nullptr);

    painter->fillRect(rect(), QColor{0, 122, 204});
}

//==============================================================
// Вывод количества узлов
//==============================================================
void StatusBar::drawNumberOfNodes(QPainter *painter) const
{
    Q_ASSERT(painter != nullptr);

    painter->setPen(Qt::white);
    constexpr int textFlags = Qt::AlignLeft | Qt::AlignVCenter;
    const QString text = QString{"%1: 0"}.arg(tr("Number of nodes"));
    const QRect textRect{5, 0, width() - 8, height()};
    painter->drawText(textRect, textFlags, text);
}

//==============================================================
// Вывод области с брендом
//==============================================================
void StatusBar::drawVersionArea(QPainter *painter) const
{
    constexpr int areaWidth = 160;
    const QRect rect{width() - areaWidth, 0, areaWidth, height()};
    painter->fillRect(rect, QColor{0, 80, 152});

    constexpr int textFlags = Qt::AlignHCenter | Qt::AlignVCenter;
    painter->setPen(Qt::white);
    const QString version = QString{"ByteMachine %1"}.arg(APP_VERSION);
    painter->drawText(rect, textFlags, version);
}
