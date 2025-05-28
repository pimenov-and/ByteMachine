////////////////////////////////////////////////////////////////
// ByteMachine
// Виджет дизайнера
////////////////////////////////////////////////////////////////
#ifndef FORM_DESIGNER_H
#define FORM_DESIGNER_H

//==============================================================
#include <QWidget>

//==============================================================
namespace Ui
{
    class FormDesigner;
}

//==============================================================
// Виджет дизайнера
//==============================================================
class FormDesigner : public QWidget
{
    Q_OBJECT
public:
    // Конструктор с параметром
    explicit FormDesigner(QWidget *parent = nullptr);
    // Деструктор
    ~FormDesigner() override;
private slots:
    // Функция вызывается при перерисовке
    void paintEvent(QPaintEvent *event) override;
private:
    // Задание соединений
    void setConnections();
    // Заливка фона
    void fillBackgound(QPainter *painter, const QRect &clipRect) const;
    // Вывод сетки
    void drawGrid(QPainter *painter) const;

    // Интерфейс пользователя
    Ui::FormDesigner *ui_{nullptr};
};

//==============================================================
#endif // FORM_DESIGNER_H
