////////////////////////////////////////////////////////////////
// ByteMachine
// Виджет дизайнера
////////////////////////////////////////////////////////////////
#include "form_designer.h"
#include "project.h"
#include "node_helper.h"
#include "qt_helper.h"
#include "math_helper.h"
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

    setCharSize(&painter);

    fillBackgound(&painter, clipRect);
    drawGrid(&painter);
    drawPinConnectedLines(&painter);
    drawNodes(&painter);
    drawMoveConnection(&painter);
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
        // Попытка проведения связи из выходного пина
        //------------------------------------------------------
        if (ShPtrOutputPin pin = project()->findNodeOutputPinByPt(pos, 5); pin != nullptr)
        {
            // Выделение узла
            BaseNode *const node = pin->parentNode();
            Q_ASSERT(node != nullptr);
            const ShPtrBaseNode shPtrNode = project()->findNodeByPtr(node);
            Q_ASSERT(shPtrNode != nullptr);
            project()->setSelectedNode(shPtrNode);

            // Задание параметров подключения
            movingConnection_.outputPin = pin;
            movingConnection_.beginPt = movingConnection_.endPt = pin->rect().center();
        }
        //------------------------------------------------------
        // Попытка изменения связи из подключенного входного пина
        //------------------------------------------------------
        else if (ShPtrInputPin pin = project()->findNodeInputPinByPt(pos, 5); (pin != nullptr) && pin->isConnected())
        {
            const ShPtrOutputPin connectOutputPin = pin->outputPin();

            // Задание параметров подключения
            movingConnection_.inputPin = pin;
            movingConnection_.beginPt = connectOutputPin->rect().center();
            movingConnection_.endPt = pin->rect().center();
        }
        //------------------------------------------------------
        // При нажатии на область состояния
        //------------------------------------------------------
        else if (ShPtrBaseNode node = project()->findStateAreaNodeByPt(pos); node != nullptr)
        {
            project()->setSelectedNode(node);
        }
        //------------------------------------------------------
        // Проверка изменения размера узла
        //------------------------------------------------------
        else if (ShPtrBaseNode node = project()->findResizebleAreaNodeFromCurrentByPt(pos))
        {
            project()->setSelectedNode(node);

            resizebleNode_ = node;
            resizebleNode_->beginResize();
        }
        //------------------------------------------------------
        // Попытка захвата узла
        //------------------------------------------------------
        else if (ShPtrBaseNode node = project()->findNodeByPt(pos); node != nullptr)
        {
            // Если нажата клавиша Ctrl, то создаётся копия узла
            if (isCtrlKey(event->modifiers()))
            {
                const auto cloneNode = node->clone();
                project()->addNode(cloneNode);

                movingNode_ = cloneNode;
                const QPoint movingBeginPos = cloneNode->topLeft();
                project()->setSelectedNode(movingNode_);
                movingDragOffsetNode_ = pos - movingBeginPos;
            }
            // Если нажата клавиша Alt и есть выходные пины, то задаётся связь
            else if (isAltKey(event->modifiers()) && node->isOutputPins())
            {
                // Выделение узла
                project()->setSelectedNode(node);

                // Задание параметром связи
                const ShPtrOutputPin pin = node->outputPin(0);
                movingConnection_.outputPin = pin;
                movingConnection_.beginPt = movingConnection_.endPt = pin->rect().center();
            }
            // Иначе узел перетаскивается
            else
            {                
                movingNode_ = node;
                project()->setSelectedNode(movingNode_);
                const QPoint movingBeginPos = node->topLeft();
                movingDragOffsetNode_ = pos - movingBeginPos;
                project()->bringNodeToFront(movingNode_);
            }
        }
        //------------------------------------------------------
        // Иначе
        //------------------------------------------------------
        else
        {
            project()->setSelectedNode(nullptr);
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
        // Узел начинает перетаскиваться только при некотором смещении от начального
        if (!movingNode_->isMoving())
        {
            const QPoint topLeft = movingNode_->topLeft();
            const QPoint newTopLeft = pos - movingDragOffsetNode_;
            if ((newTopLeft - topLeft).manhattanLength() >= QApplication::startDragDistance())
            {
                movingNode_->beginMove(newTopLeft);
            }
        }
        // Перетаскивание узла собственно
        else
        {
            const QPoint topLeft = pos - movingDragOffsetNode_;
            movingNode_->move(topLeft);

            update();
        }
    }
    //----------------------------------------------------------
    // Перетаскивание связи узла
    //----------------------------------------------------------
    else if (movingConnection_.isMove())
    {
        if (movingConnection_.outputPin != nullptr)
        {
            // Если это попадание во входной пин элемента
            const BaseNode *const sourceNode = movingConnection_.outputPin->parentNode();
            const ShPtrInputPin targetPin = project()->findNodeInputPinByPt(pos, 5);
            const ShPtrBaseNode targetNode = project()->findNodeByPt(pos);
            if ((targetPin != nullptr) && (sourceNode != targetPin->parentNode()))
            {
                const QPoint inputPinCenter = targetPin->rect().center();
                movingConnection_.endPt = inputPinCenter;
            }
            else if ((targetNode != nullptr) && targetNode->isInputPins() && (sourceNode != targetNode) && isAltKey(event->modifiers()))
            {
                const QPoint inputPinCenter = targetNode->inputPin(0)->rect().center();
                movingConnection_.endPt = inputPinCenter;
            }
            else
            {
                movingConnection_.endPt = pos;
            }
        }
        else
        {
            // Если это попадание во входной пин элемента
            const ShPtrInputPin targetInputPin = project()->findNodeInputPinByPt(pos, 5);
            const BaseNode *const sourceNode = movingConnection_.inputPin->outputPin()->parentNode();
            if ((targetInputPin != nullptr) && (sourceNode != targetInputPin->parentNode()))
            {
                const QPoint targetInputPinCenter = targetInputPin->rect().center();
                movingConnection_.endPt = targetInputPinCenter;
            }
            else
            {
                movingConnection_.endPt = pos;
            }
        }

        update();
    }
    //----------------------------------------------------------
    // Если курсов находится на области состояния узла, показать подсказку
    // состояния
    //----------------------------------------------------------
    else if (ShPtrBaseNode node = project()->findStateAreaNodeByPt(pos); node != nullptr)
    {
        setToolTip(node->stateInfo().toStr());

        setCursor(Qt::ArrowCursor);
    }
    //----------------------------------------------------------
    // Изменение вида курсора при наведении на маркер изменения размера узла
    //----------------------------------------------------------
    else if (resizebleNode_ != nullptr)
    {
        setCursor(Qt::SizeFDiagCursor);

        const QPoint topLeft = resizebleNode_->topLeft();
        const int width = pos.x() - topLeft.x();
        const int height = pos.y() - topLeft.y();
        resizebleNode_->resizing(QSize{width, height});

        update();
    }
    //---------------------------------------------------------------
    // Изменение вида курсора при наведении на маркер изменения размера узла
    //---------------------------------------------------------------
    else if (project()->findResizebleAreaNodeFromCurrentByPt(pos) != nullptr)
    {
        setCursor(Qt::SizeFDiagCursor);
    }
    //----------------------------------------------------------
    // Если курсор находится на узле, показать подсказку
    //----------------------------------------------------------
    else if (ShPtrBaseNode node = project()->findNodeByPt(pos); node != nullptr)
    {
        setToolTip(node->tooltipText());

        setCursor(Qt::ArrowCursor);
    }
    //----------------------------------------------------------
    // Иначе
    //----------------------------------------------------------
    else
    {
        setToolTip(QString{});
        QToolTip::hideText();

        setCursor(Qt::ArrowCursor);
    }
}

//==============================================================
// Функция вызывается при отпускании мыши
//==============================================================
void FormDesigner::mouseReleaseEvent(QMouseEvent *event)
{
    const QPoint pos = event->pos();

    //----------------------------------------------------------
    // Отпускание проведение связи из выходного пина
    //----------------------------------------------------------
    if (movingConnection_.isMove())
    {
        if (movingConnection_.outputPin != nullptr)
        {
            const ShPtrInputPin inputPin = project()->findNodeInputPinByPt(movingConnection_.endPt);
            if (inputPin != nullptr)
            {
                project()->setNodeConnection(movingConnection_.outputPin, nullptr,
                    inputPin);
            }
        }
        else
        {
            const ShPtrInputPin inputPin = project()->findNodeInputPinByPt(pos);
            if (inputPin != movingConnection_.inputPin)
            {
                const ShPtrInputPin connectInputPin = movingConnection_.inputPin;
                const ShPtrOutputPin sourceOutputPin = connectInputPin->outputPin();
                project()->setNodeConnection(sourceOutputPin, connectInputPin,
                    inputPin);
            }
        }

        movingConnection_.reset();
        update();
    }
    //----------------------------------------------------------
    // Отпускание захваченного узла
    //----------------------------------------------------------
    else if (movingNode_ != nullptr)
    {
        const QPoint topLeft = pos - movingDragOffsetNode_;
        movingNode_->endMove(topLeft);

        movingNode_ = nullptr;
        movingDragOffsetNode_ = QPoint{};
    }
    //----------------------------------------------------------
    // Изменение размеров узла
    //----------------------------------------------------------
    else if (resizebleNode_ != nullptr)
    {
        const QPoint topLeft = resizebleNode_->topLeft();
        const int width = pos.x() - topLeft.x();
        const int height = pos.y() - topLeft.y();
        resizebleNode_->endResize(QSize{width, height});

        resizebleNode_ = nullptr;
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
    connect(project(), &Project::sigAddNode,
        this, [this]() { this->update(); });
    connect(project(), &Project::sigRemoveNode,
        this, [this]() { this->update(); });
    connect(project(), &Project::sigChangedNodeProp,
        this, [this]() { this->update(); });
    connect(project(), &Project::sigChangeSelectedNode,
        this, [this]() { this->update(); });
    connect(project(), &Project::sigChangedNodeState,
        this, [this]() { this->update(); });
    connect(project(), &Project::sigChangeNodeConnection,
        this, [this]() { this->update(); });
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
// Вывод перемещаемого соединения
//==============================================================
void FormDesigner::drawMoveConnection(QPainter *painter) const
{
    Q_ASSERT(painter != nullptr);

    if (movingConnection_.isMove())
    {
        painter->save();

        painter->setRenderHint(QPainter::Antialiasing);
        QPen pen{Qt::blue, 2.0, Qt::CustomDashLine, Qt::RoundCap};
        pen.setDashPattern({1, 3});
        painter->setPen(pen);
        const QPoint &pt1 = movingConnection_.beginPt;
        const QPoint &pt2 = movingConnection_.endPt;
        painter->drawLine(pt1, pt2);

        painter->restore();
    }
}

//==============================================================
// Рисование соединений пинов
//==============================================================
void FormDesigner::drawPinConnectedLines(QPainter *painter) const
{
    Q_ASSERT(painter != nullptr);

    const QVector<ShPtrBaseNode> &nodes = project()->nodes();
    for (const ShPtrBaseNode &node: nodes)
    {
        const QVector<ShPtrOutputPin> outPins = node->outputPins();
        for (const ShPtrOutputPin &outPin: outPins)
        {
            const QVector<ShPtrInputPin> inputPins = outPin->inputPins();
            for (const ShPtrInputPin &inputPin: inputPins)
            {
                const QPoint pt1 = outPin->rect().center();
                const QPoint pt2 = inputPin->rect().center();
                const QColor color = Colors::nodeBorder();
                drawLineWithArraw(painter, color, pt1, pt2);
            }
        }
    }
}

//==============================================================
// Вывод линии со стрелкой
//==============================================================
void FormDesigner::drawLineWithArraw(QPainter *painter,
    const QColor &color, const QPoint &pt1, const QPoint &pt2) const
{
    Q_ASSERT(painter != nullptr);

    painter->save();

    // Рисование линии
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen({color, 2});
    painter->drawLine(pt1, pt2);

    // Рисование стрелки
    const QPointF vector = pt2 - pt1;
    const double halfLen = sqrt(vector.x() * vector.x() + vector.y() * vector.y()) / 2;
    const double rad = calcAngle(pt1, pt2);
    const QPointF arrowPt1 = pt1 + QPointF{(halfLen + 5) * cos(rad),
                                           (halfLen + 5) * sin(rad)};
    const double rad1_ = rad + qDegreesToRadians(150.0);
    const QPointF arrowPt2{arrowPt1.x() + cos(rad1_) * 8,
                           arrowPt1.y() + sin(rad1_) * 8};
    const double rad2_ = rad - qDegreesToRadians(150.0);
    const QPointF arrowPt3{arrowPt1.x() + cos(rad2_) * 8,
                           arrowPt1.y() + sin(rad2_) * 8};
    const QPolygonF polygon = QPolygonF{} << arrowPt2 << arrowPt1 << arrowPt3;
    painter->setPen(color);
    painter->setBrush(color);
    painter->drawPolygon(polygon);

    painter->restore();
}

//==============================================================
// Задание размера символа
//==============================================================
void FormDesigner::setCharSize(QPainter *painter)
{
    Q_ASSERT(painter != nullptr);

    const QSize charSize = ::strSize(*painter, "0");
    BaseNode::setCharSize(charSize);
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
