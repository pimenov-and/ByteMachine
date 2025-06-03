////////////////////////////////////////////////////////////////
// ByteMachine
// Виджет дизайнера
////////////////////////////////////////////////////////////////
#include "form_designer.h"
#include "ui_form_designer.h"
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>

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
// Задание видимости сетки
//==============================================================
void FormDesigner::setGridVisible(bool visible)
{
    if (isGridVisible_ != visible)
    {
        isGridVisible_ = visible;
        update();
    }
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
// Функция вызывается при показе контекстного меню
//==============================================================
void FormDesigner::contextMenuEvent(QContextMenuEvent *event)
{
    const QPoint pos = event->globalPos();
    const QPointer<QMenu> menu = createContextMenu();
    menu->popup(pos);
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
    if (!isGridVisible_)
    {
        return;
    }

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

//==============================================================
// Создание контекстного меню
//==============================================================
QMenu* FormDesigner::createContextMenu() const
{
    auto menu = new QMenu{};

    QMenu *const menuAddNode = menu->addMenu(tr("Add node"));
    menuAddNode->addMenu(createStandartNodesContextMenu());
    menuAddNode->addMenu(createVisualizationNodesContextMenu());
    menuAddNode->addMenu(createScriptNodesContextMenu());
    menuAddNode->addMenu(createOtherNodesContextMenu());

    QAction *const actPaste = menu->addAction(tr("Paste"));
    actPaste->setIcon(QIcon{":/res_images/images/paste.png"});
    actPaste->setShortcut(QString{"Ctrl+V"});
    actPaste->setEnabled(false);

    return menu;
}

//==============================================================
// Создание контекстного меню узлов "Standart"
//==============================================================
QMenu* FormDesigner::createStandartNodesContextMenu() const
{
    const auto menu = new QMenu(tr("Standart"));

    QAction *const actGenerate = menu->addAction("Generate");
    actGenerate->setIcon(QIcon{":/res_images/images/standart_node.png"});
    actGenerate->setEnabled(false);
    // connect(actGenerate, &QAction::triggered,
    //     this, &FormDesigner::slotAddNodeFromContextMenu);

    QAction *const actInFile = menu->addAction("InFile");
    actInFile->setIcon(QIcon{":/res_images/images/standart_node.png"});
    actInFile->setEnabled(false);

    QAction *const actTake = menu->addAction("Take");
    actTake->setIcon(QIcon{":/res_images/images/standart_node.png"});
    actTake->setEnabled(false);

    QAction *const actSkip = menu->addAction("Skip");
    actSkip->setIcon(QIcon{":/res_images/images/standart_node.png"});
    actSkip->setEnabled(false);

    QAction *const actReverse = menu->addAction("Reverse");
    actReverse->setIcon(QIcon{":/res_images/images/standart_node.png"});
    actReverse->setEnabled(false);

    QAction *const actMerge = menu->addAction("Merge");
    actMerge->setIcon(QIcon{":/res_images/images/standart_node.png"});
    actMerge->setEnabled(false);

    QAction *const actOutFile = menu->addAction("OutFile");
    actOutFile->setIcon(QIcon{":/res_images/images/standart_node.png"});
    actOutFile->setEnabled(false);

    QAction *const actPaintOp = menu->addAction("PaintOp");
    actPaintOp->setIcon(QIcon{":/res_images/images/standart_node.png"});
    actPaintOp->setEnabled(false);

    return menu;
}

//==============================================================
// Создание контекстного меню узлов "Visualization"
//==============================================================
QMenu* FormDesigner::createVisualizationNodesContextMenu() const
{
    const auto menu = new QMenu(tr("Visualization"));

    QAction *const actSize = menu->addAction("Size");
    actSize->setIcon(QIcon{":/res_images/images/standart_node.png"});
    actSize->setEnabled(false);

    QAction *const actDump = menu->addAction("Dump");
    actDump->setIcon(QIcon{":/res_images/images/standart_node.png"});
    actDump->setEnabled(false);

    QAction *const actStruct = menu->addAction("Struct");
    actStruct->setIcon(QIcon{":/res_images/images/standart_node.png"});
    actStruct->setEnabled(false);

    QAction *const actGraph = menu->addAction("Graph");
    actGraph->setIcon(QIcon{":/res_images/images/standart_node.png"});
    actGraph->setEnabled(false);

    QAction *const actPaint = menu->addAction("Paint");
    actPaint->setIcon(QIcon{":/res_images/images/standart_node.png"});
    actPaint->setEnabled(false);

    return menu;
}

//==============================================================
// Создание контекстного меню узлов "Script"
//==============================================================
QMenu* FormDesigner::createScriptNodesContextMenu() const
{
    const auto menu = new QMenu(tr("Script"));

    QAction *const actSIn = menu->addAction("SIn");
    actSIn->setIcon(QIcon{":/res_images/images/standart_node.png"});
    actSIn->setEnabled(false);

    QAction *const actSChange = menu->addAction("SChange");
    actSChange->setIcon(QIcon{":/res_images/images/standart_node.png"});
    actSChange->setEnabled(false);

    QAction *const actSMerge = menu->addAction("SMerge");
    actSMerge->setIcon(QIcon{":/res_images/images/standart_node.png"});
    actSMerge->setEnabled(false);

    QAction *const actSOut = menu->addAction("SOut");
    actSOut->setIcon(QIcon{":/res_images/images/standart_node.png"});
    actSOut->setEnabled(false);

    return menu;
}

//==============================================================
// Создание контекстного меню узлов "Other"
//==============================================================
QMenu* FormDesigner::createOtherNodesContextMenu() const
{
    const auto menu = new QMenu(tr("Other"));

    QAction *const actBlock = menu->addAction("Block");
    actBlock->setIcon(QIcon{":/res_images/images/standart_node.png"});
    actBlock->setEnabled(false);

    QAction *const actNon = menu->addAction("Non");
    actNon->setIcon(QIcon{":/res_images/images/standart_node.png"});
    actNon->setEnabled(false);

    return menu;
}

//==============================================================
// Создание контекстного меню узлов "Standart"
//==============================================================
QMenu* FormDesigner::createNodeContextMenu() const
{
    auto menu = new QMenu{};

    QAction *const actMoveToBlock = menu->addAction(tr("Move to block"));
    actMoveToBlock->setEnabled(false);

    QMenu *const menuMorphTo = menu->addMenu(tr("Morph to"));
    menuMorphTo->setEnabled(false);

    menu->addSeparator();

    QAction *const actCut = menu->addAction(tr("Cut"));
    actCut->setShortcut(QString{"Ctrl+X"});
    actCut->setEnabled(false);

    QAction *const actCopy = menu->addAction(tr("Copy"));
    actCopy->setShortcut(QString{"Ctrl+C"});
    actCopy->setEnabled(false);

    QAction *const actPaste = menu->addAction(tr("Paste"));
    actPaste->setShortcut(QString{"Ctrl+V"});
    actPaste->setEnabled(false);

    menu->addSeparator();

    QAction *const actDelete = menu->addAction(tr("Delete"));
    actDelete->setShortcut(QString{"Del"});
    actDelete->setEnabled(false);

    return menu;
}
