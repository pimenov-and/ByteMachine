////////////////////////////////////////////////////////////////
// ByteMachine
// Виджет узла на панели узлов
////////////////////////////////////////////////////////////////
#include "form_node_panel_item.h"
#include <QPainter>

//==============================================================
// Конструктор с параметром
//==============================================================
FormNodePanelItem::FormNodePanelItem(const QString &text, QWidget *parent) :
    QWidget{parent},
    text_{text}
{
    setMinimumHeight(28);
    setMaximumHeight(28);
}

//==============================================================
// Деструктор
//==============================================================
FormNodePanelItem::~FormNodePanelItem()
{
}

//==============================================================
// Функция перерисовки
//==============================================================
void FormNodePanelItem::paintEvent(QPaintEvent *)
{
    QPainter painter{this};

    // Вывод иконки узла
    const QString imagePath = isEnabled()
        ? ":/res_images/images/standart_node.png"
        : ":/res_images/images/standart_node_disable.png";
    const QPixmap image{imagePath};
    painter.drawPixmap(0, height() / 2 - image.height() / 2 + 1, image);

    // const QString nodeTypeStr = nodeTypeToStr(nodeType_);
    painter.drawText(23, 0, width(), height(), Qt::AlignLeft | Qt::AlignVCenter,
        text_);
}

//==============================================================
// Функция вызывается при заходе мыши на виджет
//==============================================================
void FormNodePanelItem::enterEvent(QEvent *)
{
    update();
}

//==============================================================
// Функция вызывается при покидании виджета мышью
//==============================================================
void FormNodePanelItem::leaveEvent(QEvent *)
{
    update();
}
