////////////////////////////////////////////////////////////////
// ByteMachine
// Главное окно
////////////////////////////////////////////////////////////////
#include "main_window.h"
#include "ui_main_window.h"
#include "dialog_about_prog.h"
#include "form_node_panel_item.h"
#include "form_project_settings.h"
#include "form_generate_node.h"
#include "form_size_node.h"
#include "node_helper.h"
#include "generate_node.h"
#include "icons.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>

//==============================================================
// Конструктор с параметром
//==============================================================
MainWindow::MainWindow(QWidget *parent) : QMainWindow{parent},
    ui_{new Ui::MainWindow{}}
{
    ui_->setupUi(this);

    setConnections();
    initNodesPanel();

    ui_->scrollAreaSettings_->setWidget(new FormProjectSettings{project()});

    // Показ версии в заголовке окна
    const QString version = QString{"%1 %2"}.arg("ByteMachine", APP_VERSION);
    setWindowTitle(version);

    // Добавление действий Undo/Redo в меню Edit
    QAction *const actUndo = project()->createActionUndo();
    QAction *const actRedo = project()->createActionRedo();
    ui_->menuEdit_->insertActions(ui_->actUndo_, {actUndo, actRedo});
    ui_->toolBar_->insertActions(ui_->actUndo_, {actUndo, actRedo});
    delete ui_->actUndo_;
    delete ui_->actRedo_;
}

//==============================================================
// Деструктор
//==============================================================
MainWindow::~MainWindow()
{
    delete ui_;
}

//==============================================================
// Открыть проект
//==============================================================
void MainWindow::slotOpenProject()
{
    const QString caption = "Open project";
    const QString filter = "Project (*.bm)";
    const QString dir{};
    const QString path = QFileDialog::getOpenFileName(this, caption, dir, filter);
    if (!path.isEmpty())
    {
    }
}

//==============================================================
// Сохранить проект как...
//==============================================================
void MainWindow::slotSaveProjectAs()
{
    const QString caption = "Save project as";
    const QString filter = "Project (*.bm)";
    const QString dir = "Project";
    const QString path = QFileDialog::getSaveFileName(this, caption, dir, filter);
    if (!path.isEmpty())
    {
        QFile file{path};
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
        }
    }
}

//==============================================================
// Функция вызывается при изменении видимости панели узлов
//==============================================================
void MainWindow::slotNodesPanelVisibleChanged(bool visible)
{
    ui_->groupBoxNodes_->setVisible(visible);
}

//==============================================================
// Функция вызывается при изменении видимости панели свойств
//==============================================================
void MainWindow::slotSettingsPanelVisibleChanged(bool visible)
{
    ui_->groupBoxSettings_->setVisible(visible);
}

//==============================================================
// Функция вызывается при изменении видимости сетки дизайнера
//==============================================================
void MainWindow::slotDesignerGridVisible(bool visible)
{
    ui_->widgetDesigner_->setGridVisible(visible);
}

//==============================================================
// Функция вызывается при изменении видимости комментариев узлов
//==============================================================
void MainWindow::slotNodesCommentsVisibleChanged(bool visible)
{
    BaseNode::setCommentsVisible(visible);
    ui_->widgetDesigner_->repaint();
}

//==============================================================
// Функция вызывается при выборе пункта главного меню "О программе"
//==============================================================
void MainWindow::slotShowAboutProg()
{
    DialogAboutProg dlg{this};
    dlg.exec();
}

//==============================================================
// Функция вызывается при изменении страницы панели с узлами
//==============================================================
void MainWindow::slotNodesPageChanged(int index)
{
    if (index == -1)
    {
        return;
    }

    for (int i = 0; i < ui_->toolBoxNodes_->count(); ++i)
    {
        ui_->toolBoxNodes_->setItemIcon(i, Icons::collapseArrow());
    }

    ui_->toolBoxNodes_->setItemIcon(index, Icons::expandArrow());
}

//==============================================================
// Функция вызывается при добавлении узла через панель
//==============================================================
void MainWindow::slotAddNodeByType(NodeTypes nodeType)
{
    QUndoStack *undoStack = project()->undoStack();
    const auto node = createNode(nodeType, undoStack);
    const auto selNode = project()->selectedNode();
    if (selNode != nullptr)
    {
        // selNode->setSelected(false);

        const QPoint selTopLeft = selNode->topLeft();
        node->setUndo(true);
        node->setTopLeft(selTopLeft + QPoint{20, 20});
        node->setUndo(false);
    }

    project()->addNode(node);
}

//==============================================================
// Функция вызывается при добавлении узла
//==============================================================
void MainWindow::slotAddNode(ShPtrBaseNode node)
{
    Q_ASSERT(node != nullptr);

    isNodesProcessing_ = true;
    const QString nodeDescript = node->toStr();
    ui_->comboBoxObjects_->addItem(nodeDescript);
    ui_->comboBoxObjects_->setCurrentText(nodeDescript);
    isNodesProcessing_ = false;
}

//==============================================================
// Функция вызывается при изменении свойства узла
//==============================================================
void MainWindow::slotChangedNodeProp(ShPtrBaseNode node, PropValue value)
{
    Q_UNUSED(node);
    Q_UNUSED(value);
}

//==============================================================
// Функция вызывается при удалении узла
//==============================================================
void MainWindow::slotRemoveNode(ShPtrBaseNode node)
{
    Q_ASSERT(node != nullptr);

    isNodesProcessing_ = true;
    const QString descript = node->toStr();
    const int index = ui_->comboBoxObjects_->findText(descript);
    Q_ASSERT(index != -1);
    ui_->comboBoxObjects_->removeItem(index);
    isNodesProcessing_ = false;
}

//==============================================================
// Функция вызывается при сбросе выделения со узлов
//==============================================================
void MainWindow::slotChangeSelectedNode(ShPtrBaseNode node)
{
    isNodesProcessing_ = true;
    if (node != nullptr)
    {
        const QString descript = node->toStr();
        ui_->comboBoxObjects_->setCurrentText(descript);
    }
    else
    {
        ui_->comboBoxObjects_->setCurrentText("Project");
    }
    isNodesProcessing_ = false;
}


//==============================================================
// Функция вызывается при изменении индекса текущего объекта
// через комбо-бокс объектов
//==============================================================
void MainWindow::slotChangeCurrentObjectIndex(int index)
{
    if (index == -1)
    {
        return;
    }

    const QString text = ui_->comboBoxObjects_->currentText();
    ui_->comboBoxObjects_->setToolTip(text);

    if (text == "Project")
    {
        const auto projectWidget = new FormProjectSettings(project());
        ui_->scrollAreaSettings_->setWidget(projectWidget);

        if (!isNodesProcessing_)
        {
            project()->setSelectedNode(nullptr);
        }
    }
    else
    {
        const int delimIndex = text.lastIndexOf(":");
        Q_ASSERT(delimIndex != -1);
        const QString nodeName = text.left(delimIndex - 1);
        Q_ASSERT(!nodeName.isEmpty());
        const ShPtrBaseNode node = project()->findNodeByName(nodeName);
        QWidget *const nodeWidget = createNodeSettingsWidget(node.get());
        Q_ASSERT(nodeWidget != nullptr);
        ui_->scrollAreaSettings_->setWidget(nodeWidget);

        if (!isNodesProcessing_)
        {
            project()->setSelectedNode(node);
        }
    }
}

//==============================================================
// Функция вызывается при закрытия окна
//==============================================================
void MainWindow::closeEvent(QCloseEvent*)
{
    qDebug() << "MainWindow::closeEvent()";
}

//==============================================================
// Создание виджета с настройками узла
//==============================================================
QWidget* MainWindow::createNodeSettingsWidget(BaseNode *node)
{
    if (const auto generateNode = qobject_cast<GenerateNode*>(node); generateNode != nullptr)
    {
        return new FormGenerateNode{generateNode};
    }
    else if (const auto sizeNode = qobject_cast<SizeNode*>(node); sizeNode != nullptr)
    {
        return new FormSizeNode{sizeNode};
    }
    else
    {
        return nullptr;
    }
}

//==============================================================
// Задание соединений
//==============================================================
void MainWindow::setConnections()
{
    // Меню "File"
    connect(ui_->actOpen_, &QAction::triggered,
        this, &MainWindow::slotOpenProject);
    connect(ui_->actSaveAs_, &QAction::triggered,
        this, &MainWindow::slotSaveProjectAs);

    // Меню "Edit"

    // Меню "Settings"
    connect(ui_->actVisibleNodesPanel_, &QAction::triggered,
        this, &MainWindow::slotNodesPanelVisibleChanged);
    connect(ui_->actVisibleSettingsPanel_, &QAction::triggered,
        this, &MainWindow::slotSettingsPanelVisibleChanged);
    connect(ui_->actVisibleDesignerGrid_, &QAction::triggered,
        this, &MainWindow::slotDesignerGridVisible);
    connect(ui_->actVisibleNodeComments_, &QAction::triggered,
        this, &MainWindow::slotNodesCommentsVisibleChanged);

    // Меню "Tools"

    // Меню "Help"
    connect(ui_->actAboutProg_, &QAction::triggered,
        this, &MainWindow::slotShowAboutProg);

    // Панель с узлами
    connect(ui_->toolBoxNodes_, &QToolBox::currentChanged,
        this, &MainWindow::slotNodesPageChanged);

    // Проект
    connect(project(), &Project::sigAddNode,
        this, &MainWindow::slotAddNode);
    connect(project(), &Project::sigRemoveNode,
        this, &MainWindow::slotRemoveNode);
    connect(project(), &Project::sigChangedNodeProp,
        this, &MainWindow::slotChangedNodeProp);
    connect(project(), &Project::sigChangeSelectedNode,
        this, &MainWindow::slotChangeSelectedNode);

    // Комбо-бокс объектов
    connect(ui_->comboBoxObjects_, SIGNAL(currentIndexChanged(int)),
        this, SLOT(slotChangeCurrentObjectIndex(int)));
}

//==============================================================
// Инициализация панели с узлами
//==============================================================
void MainWindow::initNodesPanel()
{
    QToolBox *const toolBoxNodes = ui_->toolBoxNodes_;
    while (toolBoxNodes->count() > 0)
    {
        toolBoxNodes->removeItem(0);
    }

    const int standartItemIndex = toolBoxNodes->addItem(createStandartPage(),
        Icons::collapseArrow(), "Standart");
    toolBoxNodes->setItemToolTip(standartItemIndex, "Set for standard nodes");

    const int visualizationItemIndex = toolBoxNodes->addItem(createVisualizationPage(),
        Icons::collapseArrow(), "Visualization");
    toolBoxNodes->setItemToolTip(visualizationItemIndex, "Set for visualization nodes");

    const int scriptItemIndex = toolBoxNodes->addItem(createScriptPage(),
        Icons::collapseArrow(), "Script");
    toolBoxNodes->setItemToolTip(scriptItemIndex, "Set for scripting nodes");

    const int otherItemIndex = toolBoxNodes->addItem(createOtherPage(),
        Icons::collapseArrow(), "Other");
    toolBoxNodes->setItemToolTip(otherItemIndex, "Set for other nodes");
}

//==============================================================
// Создание вкладки Standart для панели Nodes
//==============================================================
QWidget* MainWindow::createStandartPage()
{
    auto page = new QWidget{};

    auto pageLayout = new QVBoxLayout{page};
    pageLayout->setContentsMargins(QMargins{});
    pageLayout->setSpacing(0);

    const auto generateItem = new FormNodePanelItem{NodeTypes::Generate};
    connect(generateItem, &FormNodePanelItem::sigClicked,
        this, &MainWindow::slotAddNodeByType);
    pageLayout->addWidget(generateItem);

    const auto inFileItem = new FormNodePanelItem{NodeTypes::InFile};
    connect(inFileItem, &FormNodePanelItem::sigClicked,
        this, &MainWindow::slotAddNodeByType);
    inFileItem->setEnabled(false);
    pageLayout->addWidget(inFileItem);

    const auto takeItem = new FormNodePanelItem{NodeTypes::Take};
    connect(takeItem, &FormNodePanelItem::sigClicked,
        this, &MainWindow::slotAddNodeByType);
    takeItem->setEnabled(false);
    pageLayout->addWidget(takeItem);

    const auto skipItem = new FormNodePanelItem{NodeTypes::Skip};
    connect(skipItem, &FormNodePanelItem::sigClicked,
        this, &MainWindow::slotAddNodeByType);
    skipItem->setEnabled(false);
    pageLayout->addWidget(skipItem);

    const auto reverseItem = new FormNodePanelItem{NodeTypes::Reverse};
    connect(reverseItem, &FormNodePanelItem::sigClicked,
        this, &MainWindow::slotAddNodeByType);
    reverseItem->setEnabled(false);
    pageLayout->addWidget(reverseItem);

    const auto mergeItem = new FormNodePanelItem{NodeTypes::Merge};
    connect(mergeItem, &FormNodePanelItem::sigClicked,
        this, &MainWindow::slotAddNodeByType);
    mergeItem->setEnabled(false);
    pageLayout->addWidget(mergeItem);

    const auto outFileItem = new FormNodePanelItem{NodeTypes::OutFile};
    connect(outFileItem, &FormNodePanelItem::sigClicked,
        this, &MainWindow::slotAddNodeByType);
    outFileItem->setEnabled(false);
    pageLayout->addWidget(outFileItem);

    const auto paintOpItem = new FormNodePanelItem{NodeTypes::PaintOp};
    paintOpItem->setEnabled(false);
    pageLayout->addWidget(paintOpItem);

    auto spacer = new QSpacerItem{20, 40, QSizePolicy::Minimum,
        QSizePolicy::Expanding};
    pageLayout->addItem(spacer);

    return page;
}

//==============================================================
// Создание вкладки Visualization для панели Nodes
//==============================================================
QWidget* MainWindow::createVisualizationPage()
{
    auto page = new QWidget{};

    auto pageLayout = new QVBoxLayout{page};
    pageLayout->setContentsMargins(QMargins{});
    pageLayout->setSpacing(0);

    const auto sizeItem = new FormNodePanelItem{NodeTypes::Size};
    connect(sizeItem, &FormNodePanelItem::sigClicked,
        this, &MainWindow::slotAddNodeByType);
    pageLayout->addWidget(sizeItem);

    const auto dumpItem = new FormNodePanelItem{NodeTypes::Dump};
    connect(dumpItem, &FormNodePanelItem::sigClicked,
        this, &MainWindow::slotAddNodeByType);
    dumpItem->setEnabled(false);
    pageLayout->addWidget(dumpItem);

    const auto structItem = new FormNodePanelItem{NodeTypes::Struct};
    connect(structItem, &FormNodePanelItem::sigClicked,
        this, &MainWindow::slotAddNodeByType);
    structItem->setEnabled(false);
    pageLayout->addWidget(structItem);

    const auto graphItem = new FormNodePanelItem{NodeTypes::Graph};
    connect(graphItem, &FormNodePanelItem::sigClicked,
        this, &MainWindow::slotAddNodeByType);
    graphItem->setEnabled(false);
    pageLayout->addWidget(graphItem);

    const auto paintItem = new FormNodePanelItem{NodeTypes::Paint};
    connect(paintItem, &FormNodePanelItem::sigClicked,
        this, &MainWindow::slotAddNodeByType);
    paintItem->setEnabled(false);
    pageLayout->addWidget(paintItem);

    auto spacer = new QSpacerItem{20, 40, QSizePolicy::Minimum,
        QSizePolicy::Expanding};
    pageLayout->addItem(spacer);

    return page;
}

//==============================================================
// Создание вкладки Script для панели Nodes
//==============================================================
QWidget* MainWindow::createScriptPage()
{
    auto page = new QWidget{};

    auto pageLayout = new QVBoxLayout{page};
    pageLayout->setContentsMargins(QMargins{});
    pageLayout->setSpacing(0);

    const auto sinItem = new FormNodePanelItem{NodeTypes::SIn};
    connect(sinItem, &FormNodePanelItem::sigClicked,
        this, &MainWindow::slotAddNodeByType);
    sinItem->setEnabled(false);
    pageLayout->addWidget(sinItem);

    const auto smergeItem = new FormNodePanelItem{NodeTypes::SMerge};
    connect(smergeItem, &FormNodePanelItem::sigClicked,
        this, &MainWindow::slotAddNodeByType);
    smergeItem->setEnabled(false);
    pageLayout->addWidget(smergeItem);

    const auto schangeItem = new FormNodePanelItem{NodeTypes::SChange};
    connect(schangeItem, &FormNodePanelItem::sigClicked,
        this, &MainWindow::slotAddNodeByType);
    schangeItem->setEnabled(false);
    pageLayout->addWidget(schangeItem);

    const auto soutItem = new FormNodePanelItem{NodeTypes::SOut};
    connect(soutItem, &FormNodePanelItem::sigClicked,
        this, &MainWindow::slotAddNodeByType);
    soutItem->setEnabled(false);
    pageLayout->addWidget(soutItem);

    auto spacer = new QSpacerItem{20, 40, QSizePolicy::Minimum,
        QSizePolicy::Expanding};
    pageLayout->addItem(spacer);

    return page;
}

//==============================================================
// Создание вкладки Other для панели Nodes
//==============================================================
QWidget* MainWindow::createOtherPage()
{
    auto page = new QWidget{};

    auto pageLayout = new QVBoxLayout{page};
    pageLayout->setContentsMargins(QMargins{});
    pageLayout->setSpacing(0);

    const auto blockItem = new FormNodePanelItem{NodeTypes::Block};
    connect(blockItem, &FormNodePanelItem::sigClicked,
        this, &MainWindow::slotAddNodeByType);
    blockItem->setEnabled(false);
    pageLayout->addWidget(blockItem);

    const auto nonItem = new FormNodePanelItem{NodeTypes::Non};
    connect(nonItem, &FormNodePanelItem::sigClicked,
        this, &MainWindow::slotAddNodeByType);
    nonItem->setEnabled(false);
    pageLayout->addWidget(nonItem);

    auto spacer = new QSpacerItem{20, 40, QSizePolicy::Minimum,
        QSizePolicy::Expanding};
    pageLayout->addItem(spacer);

    return page;
}
