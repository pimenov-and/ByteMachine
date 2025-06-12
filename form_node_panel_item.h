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
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    void enterEvent(QEvent*) override;
#else
    void enterEvent(QEnterEvent*) override;
#endif // QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    // Функция вызывается при покидании виджета мышью
    void leaveEvent(QEvent*) override;

    // Текст
    QString text_{};
};

//==============================================================
#endif // FORM_NODE_PANEL_ITEM_H
