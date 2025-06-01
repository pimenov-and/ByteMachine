////////////////////////////////////////////////////////////////
// ByteMachine
// Статус-бар
////////////////////////////////////////////////////////////////
#ifndef STATUS_BAR_H
#define STATUS_BAR_H

//==============================================================
#include <QStatusBar>

//==============================================================
// Статус-бар
//==============================================================
class StatusBar : public QStatusBar
{
    Q_OBJECT
public:
    // Конструктор с параметром
    explicit StatusBar(QWidget *parent = nullptr);
    // Деструктор
    ~StatusBar() override;
private:
    // Функция вызывается при перерисовке
    void paintEvent(QPaintEvent*) override;

    // Задание соединений
    void setConnections();
    // Заливка фона
    void fillBackground(QPainter *painter) const;
    // Вывод количества узлов
    void drawNumberOfNodes(QPainter *painter) const;
    // Вывод области с версией
    void drawVersionArea(QPainter *painter) const;
};

//==============================================================
#endif // STATUS_BAR_H
