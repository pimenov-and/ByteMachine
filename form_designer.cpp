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

    QAction *const actOutFile = menu->addAction("OutFile");
    actOutFile->setIcon(QIcon{":/res_images/images/standart_node.png"});
    actOutFile->setEnabled(false);
    // connect(actOutFile, &QAction::triggered,
    //     this, &FormDesigner::slotAddNodeFromContextMenu);

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
    // connect(actSize, &QAction::triggered,
    //     this, &FormDesigner::slotAddNodeFromContextMenu);

    QAction *const actDump = menu->addAction("Dump");
    actDump->setIcon(QIcon{":/res_images/images/standart_node.png"});
    actDump->setEnabled(false);
    // connect(actDump, &QAction::triggered,
    //     this, &FormDesigner::slotAddNodeFromContextMenu);

    QAction *const actStruct = menu->addAction("Struct");
    actStruct->setIcon(QIcon{":/res_images/images/standart_node.png"});
    actStruct->setEnabled(false);
    // connect(actDump, &QAction::triggered,
    //     this, &FormDesigner::slotAddNodeFromContextMenu);

    return menu;
}

//==============================================================
// Создание контекстного меню узлов "Script"
//==============================================================
QMenu* FormDesigner::createScriptNodesContextMenu() const
{
    const auto menu = new QMenu(tr("Script"));

    return menu;
}

//==============================================================
// Создание контекстного меню узлов "Other"
//==============================================================
QMenu* FormDesigner::createOtherNodesContextMenu() const
{
    const auto menu = new QMenu(tr("Other"));

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
