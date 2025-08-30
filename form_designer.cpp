////////////////////////////////////////////////////////////////
// ByteMachine
// Виджет дизайнера
////////////////////////////////////////////////////////////////
#include "form_designer.h"
#include "project.h"
#include "node_helper.h"
#include "colors.h"
#include "icons.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QDebug>

//==============================================================
// Конструктор с параметром
//==============================================================
FormDesigner::FormDesigner(QWidget *parent) : QWidget{parent}
{
    ui_.setupUi(this);

    setConnections();
}

//==============================================================
// Деструктор
//==============================================================
FormDesigner::~FormDesigner()
{
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
// Добавление узла через контекстное меню
//==============================================================
void FormDesigner::slotAddNodeFromContextMenu()
{
    const auto action = qobject_cast<QAction*>(sender());
    Q_ASSERT(action != nullptr);

    QUndoStack *const undoStack = project()->undoStack();
    const QString strNodeType = action->text();
    const ShPtrBaseNode node = createNode(strNodeType, undoStack);
    Q_ASSERT(node != nullptr);
    node->setUndo(true);
    node->setTopLeft(menuPos_);
    node->setUndo(false);
    project()->addNode(node);
}

//==============================================================
// Удаление узла через контекстное меню
//==============================================================
void FormDesigner::slotRemoveNodeFromContextMenu()
{
    const ShPtrBaseNode node = project()->findSelectedNode();
    if (node != nullptr)
    {
        project()->removeNode(node);
    }

    // qDebug() << "slotRemoveNodeFromContextMenu";
}

//==============================================================
// Функция вызывается при приёме перетаскиваемого узла
//==============================================================
void FormDesigner::dragEnterEvent(QDragEnterEvent *event)
{
    const QMimeData *const mimeData = event->mimeData();
    if (mimeData->hasFormat("text/plain"))
    {
        const QString strNodeType = mimeData->text();
        const NodeTypes nodeType = strToNodeType(strNodeType);
        if (!isUnknown(nodeType))
        {
            event->acceptProposedAction();
        }
    }
}

//==============================================================
// Функция вызывается при отпускании перетаскиваемого узла
//==============================================================
void FormDesigner::dropEvent(QDropEvent *event)
{
    const QString strNodeType = event->mimeData()->text();
    const auto undoStack = project()->undoStack();
    const ShPtrBaseNode node = createNode(strNodeType, undoStack);
    Q_ASSERT(node != nullptr);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    const QPoint nodePos = event->pos();
#else
    const QPoint nodePos = event->position().toPoint();
#endif
    node->setUndo(true);
    node->setTopLeft(nodePos);
    node->setUndo(false);
    project()->addNode(node);

    update();
}

//==============================================================
// Функция вызывается при перерисовке
//==============================================================
void FormDesigner::paintEvent(QPaintEvent *event)
{
    QPainter painter{this};
    painter.setFont({"Courier New", 10});
    const QRect &clipRect = event->rect();

    fillBackgound(&painter, clipRect);
    drawGrid(&painter);
    drawNodes(&painter);
}

//==============================================================
// Функция вызывается при нажатии мыши
//==============================================================
void FormDesigner::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        const QPoint pos = event->pos();

        //------------------------------------------------------
        // Попытка захвата узла
        //------------------------------------------------------
        if (const ShPtrBaseNode node = project()->findNodeByPt(pos); node != nullptr)
        {
            project()->unselectNodes();

            // Если клавиша Ctrl не нажата, то перемещается захваченный узел
            if ((event->modifiers() & Qt::ControlModifier) != Qt::ControlModifier)
            {
                const QPoint movingBeginPos = node->topLeft();
                node->beginMove(movingBeginPos);

                movingNode_ = node;
                movingNode_->setSelected(true);
                movingDragOffsetNode_ = pos - movingBeginPos;
                project()->bringNodeToFront(movingNode_);
            }
            // Иначе создаётся копия узла и перещается уже она
            else
            {
                const auto cloneNode = node->clone();
                project()->addNode(cloneNode);

                const QPoint movingBeginPos = cloneNode->topLeft();
                cloneNode->beginMove(movingBeginPos);

                movingNode_ = cloneNode;
                movingNode_->setSelected(true);
                movingDragOffsetNode_ = pos - movingBeginPos;
            }
        }
        //------------------------------------------------------
        // Иначе
        //------------------------------------------------------
        else
        {
            project()->clearSelection();
        }

        update();
    }
}

//==============================================================
// Функция вызвается при перемещении мыши
//==============================================================
void FormDesigner::mouseMoveEvent(QMouseEvent *event)
{
    const QPoint pos = event->pos();

    //----------------------------------------------------------
    // Перемещении захваченного узла
    //----------------------------------------------------------
    if (movingNode_ != nullptr)
    {
        const QPoint topLeft = pos - movingDragOffsetNode_;
        movingNode_->move(topLeft);

        update();
    }
}

//==============================================================
// Функция вызывается при отпускании мыши
//==============================================================
void FormDesigner::mouseReleaseEvent(QMouseEvent *event)
{
    const QPoint pos = event->pos();

    //----------------------------------------------------------
    // Отпускание захваченного узла
    //----------------------------------------------------------
    if (movingNode_ != nullptr)
    {
        const QPoint topLeft = pos - movingDragOffsetNode_;
        movingNode_->endMove(topLeft);

        movingNode_ = nullptr;
        movingDragOffsetNode_ = QPoint{};
    }
}

//==============================================================
// Функция вызывается при показе контекстного меню
//==============================================================
void FormDesigner::contextMenuEvent(QContextMenuEvent *event)
{
    const QPoint globalPos = event->globalPos();
    const QPoint pos = event->pos();
    menuPos_ = pos;

    if (project()->findNodeByPt(menuPos_) != nullptr)
    {
        const QPointer<QMenu> menu = createNodeContextMenu();
        menu->popup(globalPos);
    }
    else
    {
        const QPointer<QMenu> menu = createContextMenu();
        menu->popup(globalPos);
    }
}

//==============================================================
// Задание соединений
//==============================================================
void FormDesigner::setConnections()
{
    connect(project(), SIGNAL(sigAddNode(ShPtrBaseNode)),
        this, SLOT(repaint()));
    connect(project(), SIGNAL(sigRemoveNode(ShPtrBaseNode)),
        this, SLOT(repaint()));
    connect(project(), SIGNAL(sigChangedNodeProp(ShPtrBaseNode,PropValue)),
        this, SLOT(repaint()));
}

//==============================================================
// Заливка фона
//==============================================================
void FormDesigner::fillBackgound(QPainter *painter, const QRect &clipRect) const
{
    painter->fillRect(clipRect, Colors::designerBack());
}

//==============================================================
// Вывод сетки
//==============================================================
void FormDesigner::drawGrid(QPainter *painter) const
{
    if (isGridVisible_)
    {
        const QColor color{Colors::designerGrid()};
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
}

//==============================================================
// Вывод узлов
//==============================================================
void FormDesigner::drawNodes(QPainter *painter) const
{
    Q_ASSERT(painter != nullptr);

    const QVector<ShPtrBaseNode> &nodes = project()->nodes();
    for (const ShPtrBaseNode &node: nodes)
    {
        node->draw(painter);
    }
}

//==============================================================
// Создание контекстного меню
//==============================================================
QMenu* FormDesigner::createContextMenu() const
{
    auto menu = new QMenu{};

    QMenu *const menuAddNode = menu->addMenu("Add node");
    menuAddNode->addMenu(createStandartNodesContextMenu());
    menuAddNode->addMenu(createVisualizationNodesContextMenu());
    menuAddNode->addMenu(createScriptNodesContextMenu());
    menuAddNode->addMenu(createOtherNodesContextMenu());

    QAction *const actPaste = menu->addAction("Paste");
    actPaste->setIcon(Icons::paste());
    actPaste->setShortcut(QString{"Ctrl+V"});
    actPaste->setEnabled(false);

    return menu;
}

//==============================================================
// Создание контекстного меню узлов "Standart"
//==============================================================
QMenu* FormDesigner::createStandartNodesContextMenu() const
{
    const auto menu = new QMenu("Standart");

    QAction *const actGenerate =
        menu->addAction(Icons::standartNode(), "Generate");
    connect(actGenerate, &QAction::triggered,
        this, &FormDesigner::slotAddNodeFromContextMenu);

    QAction *const actInFile =
        menu->addAction(Icons::standartNode(), "InFile");
    actInFile->setEnabled(false);

    QAction *const actTake =
        menu->addAction(Icons::standartNode(), "Take");
    actTake->setEnabled(false);

    QAction *const actSkip =
        menu->addAction(Icons::standartNode(), "Skip");
    actSkip->setEnabled(false);

    QAction *const actReverse =
        menu->addAction(Icons::standartNode(), "Reverse");
    actReverse->setEnabled(false);

    QAction *const actMerge =
        menu->addAction(Icons::standartNode(), "Merge");
    actMerge->setEnabled(false);

    QAction *const actOutFile =
        menu->addAction(Icons::standartNode(), "OutFile");
    actOutFile->setEnabled(false);

    QAction *const actPaintOp =
        menu->addAction(Icons::standartNode(), "PaintOp");
    actPaintOp->setEnabled(false);

    return menu;
}

//==============================================================
// Создание контекстного меню узлов "Visualization"
//==============================================================
QMenu* FormDesigner::createVisualizationNodesContextMenu() const
{
    const auto menu = new QMenu("Visualization");

    QAction *const actSize =
        menu->addAction(Icons::standartNode(), "Size");
    connect(actSize, &QAction::triggered,
        this, &FormDesigner::slotAddNodeFromContextMenu);

    QAction *const actDump =
        menu->addAction(Icons::standartNode(), "Dump");
    actDump->setEnabled(false);

    QAction *const actStruct =
        menu->addAction(Icons::standartNode(), "Struct");
    actStruct->setEnabled(false);

    QAction *const actGraph =
        menu->addAction(Icons::standartNode(), "Graph");
    actGraph->setEnabled(false);

    QAction *const actPaint =
        menu->addAction(Icons::standartNode(), "Paint");
    actPaint->setEnabled(false);

    return menu;
}

//==============================================================
// Создание контекстного меню узлов "Script"
//==============================================================
QMenu* FormDesigner::createScriptNodesContextMenu() const
{
    const auto menu = new QMenu("Script");

    QAction *const actSIn =
        menu->addAction(Icons::standartNode(), "SIn");
    actSIn->setEnabled(false);

    QAction *const actSChange =
        menu->addAction(Icons::standartNode(), "SChange");
    actSChange->setEnabled(false);

    QAction *const actSMerge =
        menu->addAction(Icons::standartNode(), "SMerge");
    actSMerge->setEnabled(false);

    QAction *const actSOut =
        menu->addAction(Icons::standartNode(), "SOut");
    actSOut->setEnabled(false);

    return menu;
}

//==============================================================
// Создание контекстного меню узлов "Other"
//==============================================================
QMenu* FormDesigner::createOtherNodesContextMenu() const
{
    const auto menu = new QMenu("Other");

    QAction *const actBlock =
        menu->addAction(Icons::standartNode(), "Block");
    actBlock->setEnabled(false);

    QAction *const actNon =
        menu->addAction(Icons::standartNode(), "Non");
    actNon->setEnabled(false);

    return menu;
}

//==============================================================
// Создание контекстного меню узлов "Standart"
//==============================================================
QMenu* FormDesigner::createNodeContextMenu() const
{
    auto menu = new QMenu{};

    QAction *const actMoveToBlock = menu->addAction("Move to block");
    actMoveToBlock->setEnabled(false);

    QMenu *const menuMorphTo = menu->addMenu("Morph to");
    menuMorphTo->setEnabled(false);

    menu->addSeparator();

    QAction *const actCut = menu->addAction("Cut");
    actCut->setShortcut(QString{"Ctrl+X"});
    actCut->setEnabled(false);

    QAction *const actCopy = menu->addAction("Copy");
    actCopy->setShortcut(QString{"Ctrl+C"});
    actCopy->setEnabled(false);

    QAction *const actPaste = menu->addAction("Paste");
    actPaste->setShortcut(QString{"Ctrl+V"});
    actPaste->setEnabled(false);

    menu->addSeparator();

    QAction *const actRemove = menu->addAction("Remove");
    actRemove->setShortcut(QString{"Del"});
    connect(actRemove, &QAction::triggered,
        this, &FormDesigner::slotRemoveNodeFromContextMenu);

    return menu;
}
