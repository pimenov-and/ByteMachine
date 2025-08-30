////////////////////////////////////////////////////////////////
// ByteMachine
// Виджет узла на панели узлов
////////////////////////////////////////////////////////////////
#include "form_node_panel_item.h"
#include <QPainter>
#include <QDrag>
#include <QMimeData>
#include <QApplication>
#include <QMouseEvent>

//==============================================================
// Конструктор с параметром
//==============================================================
FormNodePanelItem::FormNodePanelItem(NodeTypes nodeType,
    QWidget *parent) :
    QWidget{parent}
{
    Q_ASSERT(!isUnknown(nodeType));

    setFixedHeight(28);
    nodeType_ = nodeType;
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
void FormNodePanelItem::paintEvent(QPaintEvent *event)
{
    QPainter painter{this};

    if (underMouse() && isEnabled())
    {
        painter.fillRect(rect(), QColor{198, 231, 255});
    }

    // Вывод иконки узла
    const QString imagePath = isEnabled()
        ? ":/res_images/images/standart_node.png"
        : ":/res_images/images/standart_node_disable.png";
    const QPixmap image{imagePath};
    painter.drawPixmap(0, height() / 2 - image.height() / 2 + 1, image);

    const QString nodeTypeStr = nodeTypeToStr(nodeType_);
    painter.drawText(23, 0, width(), height(), Qt::AlignLeft | Qt::AlignVCenter,
        nodeTypeStr);

    QWidget::paintEvent(event);
}

//==============================================================
// Функция вызывается при заходе мыши на виджет
//==============================================================
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
void FormNodePanelItem::enterEvent(QEvent *event)
{
    update();

    QWidget::enterEvent(event);
}
#else
void FormNodePanelItem::enterEvent(QEnterEvent *event)
{
    update();

    QWidget::enterEvent(event);
}
#endif // QT_VERSION < QT_VERSION_CHECK(6, 0, 0)

//==============================================================
// Функция вызывается при покидании виджета мышью
//==============================================================
void FormNodePanelItem::leaveEvent(QEvent *event)
{
    update();

    QWidget::leaveEvent(event);
}

//==============================================================
// Функция вызывается при нажатии кнопки мыши
//==============================================================
void FormNodePanelItem::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        beginDragPos_ = event->pos();
    }

    QWidget::mousePressEvent(event);
}

//==============================================================
// Функция вызывается при перемещении мыши
//==============================================================
void FormNodePanelItem::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        const int distance = (event->pos() - beginDragPos_).manhattanLength();
        if (distance > QApplication::startDragDistance())
        {
            startDrag();
        }
    }

    QWidget::mousePressEvent(event);
}

//==============================================================
// Функция вызывается при отпускании кнопки мыши
//==============================================================
void FormNodePanelItem::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (rect().contains(event->pos()))
        {
            emit sigClicked(nodeType_);
        }
    }

    QWidget::mousePressEvent(event);
}

//==============================================================
// Начало перетаскивания
//==============================================================
void FormNodePanelItem::startDrag()
{
    const auto mimeData = new QMimeData{};
    const QString nodeTypeStr = nodeTypeToStr(nodeType_);
    mimeData->setText(nodeTypeStr);

    const auto drag = new QDrag{this};
    drag->setMimeData(mimeData);
    drag->setPixmap(QPixmap(":/res_images/images/drag_node.png"));
    drag->exec();
}
