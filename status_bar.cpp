////////////////////////////////////////////////////////////////
// ByteMachine
// Статус-бар
////////////////////////////////////////////////////////////////
#include "status_bar.h"
#include "colors.h"
#include "project.h"
#include <QFont>
#include <QPainter>

//==============================================================
// Конструктор с параметром
//==============================================================
StatusBar::StatusBar(QWidget *parent) : QStatusBar{parent}
{
    setConnections();
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
    connect(project(), &Project::sigAddNode,
        this, [this]() { this->update(); });
    connect(project(), &Project::sigRemoveNode,
        this, [this]() { this->update(); });
}

//==============================================================
// Заливка фона
//==============================================================
void StatusBar::fillBackground(QPainter *painter) const
{
    Q_ASSERT(painter != nullptr);

    painter->fillRect(rect(), Colors::statusBarBackColor());
}

//==============================================================
// Вывод количества узлов
//==============================================================
void StatusBar::drawNumberOfNodes(QPainter *painter) const
{
    Q_ASSERT(painter != nullptr);

    painter->setPen(Colors::statusBarTextColor());
    constexpr int32_t textFlags = Qt::AlignLeft | Qt::AlignVCenter;
    const QString text = QString{"%1: %2"}.arg("Number of nodes").
        arg(project()->nodeCount());
    const QRect textRect{5, 0, width() - 8, height()};
    painter->drawText(textRect, textFlags, text);
}

//==============================================================
// Вывод области с брендом
//==============================================================
void StatusBar::drawVersionArea(QPainter *painter) const
{
    constexpr int32_t areaWidth = 160;
    const QRect rect{width() - areaWidth, 0, areaWidth, height()};
    painter->fillRect(rect, Colors::statusBarVersionAreaBackColor());

    constexpr int32_t textFlags = Qt::AlignHCenter | Qt::AlignVCenter;
    painter->setPen(Colors::statusBarTextColor());
    const QString version = QString{"ByteMachine %1"}.arg(APP_VERSION);
    painter->drawText(rect, textFlags, version);
}
