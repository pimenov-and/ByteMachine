////////////////////////////////////////////////////////////////
// ByteMachine
// Виджет дизайнера
////////////////////////////////////////////////////////////////
#ifndef FORM_DESIGNER_H
#define FORM_DESIGNER_H

//==============================================================
#include <QtWidgets>

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
    // Функция вызывается при показе контекстного меню
    void contextMenuEvent(QContextMenuEvent *event) override;
private:
    // Задание соединений
    void setConnections();
    // Заливка фона
    void fillBackgound(QPainter *painter, const QRect &clipRect) const;
    // Вывод сетки
    void drawGrid(QPainter *painter) const;

    // Создание контекстного меню
    [[nodiscard]]
    QMenu* createContextMenu() const;
    // Создание контекстного меню узлов "Standart"
    [[nodiscard]]
    QMenu* createStandartNodesContextMenu() const;
    // Создание контекстного меню узлов "Visualization"
    [[nodiscard]]
    QMenu* createVisualizationNodesContextMenu() const;
    // Создание контекстного меню узлов "Script"
    [[nodiscard]]
    QMenu* createScriptNodesContextMenu() const;
    // Создание контекстного меню узлов "Other"
    [[nodiscard]]
    QMenu* createOtherNodesContextMenu() const;
    // Создание контекстного меню узла
    [[nodiscard]]
    QMenu* createNodeContextMenu() const;

    // Интерфейс пользователя
    Ui::FormDesigner *ui_{nullptr};
};

//==============================================================
#endif // FORM_DESIGNER_H
