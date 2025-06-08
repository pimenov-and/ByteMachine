////////////////////////////////////////////////////////////////
// ByteMachine
// Главное окно
////////////////////////////////////////////////////////////////
#include "main_window.h"
#include "ui_main_window.h"
#include "dialog_about_prog.h"
#include "form_node_panel_item.h"

//==============================================================
// Конструктор с параметром
//==============================================================
MainWindow::MainWindow(QWidget *parent) : QMainWindow{parent},
    ui_{new Ui::MainWindow{}}
{
    ui_->setupUi(this);

    initNodesPanel();
    setConnections();

    // Показ версии в заголовке окна
    const QString version = QString{"%1 %2"}.arg("ByteMachine", APP_VERSION);
    setWindowTitle(version);
}

//==============================================================
// Деструктор
//==============================================================
MainWindow::~MainWindow()
{
    delete ui_;
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
// Функция вызывается при выборе пункта главного меню "О программе"
//==============================================================
void MainWindow::slotShowAboutProg()
{
    DialogAboutProg dlg{this};
    dlg.exec();
}

//==============================================================
// Задание соединений
//==============================================================
void MainWindow::setConnections()
{
    // Меню "File"

    // Меню "Edit"

    // Меню "Settings"
    connect(ui_->actVisibleNodesPanel_, &QAction::triggered,
        this, &MainWindow::slotNodesPanelVisibleChanged);
    connect(ui_->actVisibleSettingsPanel_, &QAction::triggered,
        this, &MainWindow::slotSettingsPanelVisibleChanged);
    connect(ui_->actVisibleDesignerGrid_, &QAction::triggered,
            this, &MainWindow::slotDesignerGridVisible);

    // Меню "Tools"

    // Меню "Help"
    connect(ui_->actAboutProg_, &QAction::triggered,
        this, &MainWindow::slotShowAboutProg);
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
        QIcon{":/res_images/images/collapse_arrow_light.png"}, tr("Standart"));
    toolBoxNodes->setItemToolTip(standartItemIndex, tr("Set for standard nodes"));

    const int visualizationItemIndex = toolBoxNodes->addItem(createVisualizationPage(),
        QIcon{":/res_images/images/collapse_arrow_light.png"}, tr("Visualization"));
    toolBoxNodes->setItemToolTip(visualizationItemIndex, tr("Set for visualization nodes"));

    const int scriptItemIndex = toolBoxNodes->addItem(createScriptPage(),
        QIcon{":/res_images/images/collapse_arrow_light.png"}, tr("Script"));
    toolBoxNodes->setItemToolTip(scriptItemIndex, tr("Set for scripting nodes"));

    const int otherItemIndex = toolBoxNodes->addItem(createOtherPage(),
        QIcon{":/res_images/images/collapse_arrow_light.png"}, tr("Other"));
    toolBoxNodes->setItemToolTip(otherItemIndex, tr("Set for other nodes"));
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

    const auto generateItem = new FormNodePanelItem{"Generate"};
    generateItem->setEnabled(false);
    pageLayout->addWidget(generateItem);

    const auto inFileItem = new FormNodePanelItem{"InFile"};
    inFileItem->setEnabled(false);
    pageLayout->addWidget(inFileItem);

    const auto takeItem = new FormNodePanelItem{"Take"};
    takeItem->setEnabled(false);
    pageLayout->addWidget(takeItem);

    const auto skipItem = new FormNodePanelItem{"Skip"};
    skipItem->setEnabled(false);
    pageLayout->addWidget(skipItem);

    const auto reverseItem = new FormNodePanelItem{"Reverse"};
    reverseItem->setEnabled(false);
    pageLayout->addWidget(reverseItem);

    const auto mergeItem = new FormNodePanelItem{"Merge"};
    mergeItem->setEnabled(false);
    pageLayout->addWidget(mergeItem);

    const auto outFileItem = new FormNodePanelItem{"OutFile"};
    outFileItem->setEnabled(false);
    pageLayout->addWidget(outFileItem);

    const auto paintOpItem = new FormNodePanelItem{"PaintOp"};
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

    const auto sizeItem = new FormNodePanelItem{"Size"};
    sizeItem->setEnabled(false);
    pageLayout->addWidget(sizeItem);

    const auto dumpItem = new FormNodePanelItem{"Dump"};
    dumpItem->setEnabled(false);
    pageLayout->addWidget(dumpItem);

    const auto structItem = new FormNodePanelItem{"Struct"};
    structItem->setEnabled(false);
    pageLayout->addWidget(structItem);

    const auto graphItem = new FormNodePanelItem{"Graph"};
    graphItem->setEnabled(false);
    pageLayout->addWidget(graphItem);

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

    const auto sinItem = new FormNodePanelItem{"SIn"};
    sinItem->setEnabled(false);
    pageLayout->addWidget(sinItem);

    const auto smergeItem = new FormNodePanelItem{"SMerge"};
    smergeItem->setEnabled(false);
    pageLayout->addWidget(smergeItem);

    const auto schangeItem = new FormNodePanelItem{"SChange"};
    schangeItem->setEnabled(false);
    pageLayout->addWidget(schangeItem);

    const auto soutItem = new FormNodePanelItem{"SOut"};
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

    const auto blockItem = new FormNodePanelItem{"Block"};
    blockItem->setEnabled(false);
    pageLayout->addWidget(blockItem);

    const auto noneItem = new FormNodePanelItem{"None"};
    noneItem->setEnabled(false);
    pageLayout->addWidget(noneItem);

    auto spacer = new QSpacerItem{20, 40, QSizePolicy::Minimum,
        QSizePolicy::Expanding};
    pageLayout->addItem(spacer);

    return page;
}
