////////////////////////////////////////////////////////////////
// ByteMachine
// Виджет узла на панели узлов
////////////////////////////////////////////////////////////////
#ifndef FORM_NODE_PANEL_ITEM_H
#define FORM_NODE_PANEL_ITEM_H

//==============================================================
#include <QWidget>

//==============================================================
// Виджет узла на панели узлов
//==============================================================
class FormNodePanelItem : public QWidget
{
    Q_OBJECT
public:
    // Конструктор с параметром
    explicit FormNodePanelItem(const QString &text,
        QWidget *parent = nullptr);
    // Деструктор
    ~FormNodePanelItem() override;
private:
    // Функция перерисовки
    void paintEvent(QPaintEvent*) override;
    // Функция вызывается при заходе мыши на виджет
    void enterEvent(QEvent*) override;
    // Функция вызывается при покидании виджета мышью
    void leaveEvent(QEvent*) override;

    // Текст
    QString text_{};
};

//==============================================================
#endif // FORM_NODE_PANEL_ITEM_H
