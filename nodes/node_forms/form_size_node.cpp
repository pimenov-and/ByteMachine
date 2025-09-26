////////////////////////////////////////////////////////////////
// ByteMachine
// Форма для настройки узла Size
////////////////////////////////////////////////////////////////
#include "form_size_node.h"
#include "show_node_state.h"
// #include <QDebug>

//==============================================================
// Конструктор с параметром
//==============================================================
FormSizeNode::FormSizeNode(SizeNode *node, QWidget *parent) :
    QWidget{parent}
{
    Q_ASSERT(node != nullptr);

    ui_.setupUi(this);

    setNode(node);
    setConnections();
}

//==============================================================
// Деструктор
//==============================================================
FormSizeNode::~FormSizeNode()
{
}

//==============================================================
// Функция вызывается при изменении свойств узла
//==============================================================
void FormSizeNode::slotChangedNodeProp(PropValue value)
{
    // Имя
    if (value.name == "name")
    {
        const QString name = node_->name();
        ui_.lineEditName_->setText(name);
        ui_.lineEditName_->setToolTip(name);
    }
    // Размерность
    else if (value.name == "unit")
    {
        const SizeUnits unit = node_->unit();
        const int unitIndex = sizeUnitToInt(unit);
        ui_.comboBoxUnit_->setCurrentIndex(unitIndex);
        const bool isUnitChanged = node_->isUnitChanged();
        ui_.pushBtnResetUnit_->setEnabled(isUnitChanged);
    }
    // Признак пропуска
    else if (value.name == "bypass")
    {
        const bool isBypass = node_->isBypass();
        ui_.checkBoxBypass_->setChecked(isBypass);
        const bool isBypassChanged = node_->isBypassChanged();
        ui_.pushBtnResetBypass_->setEnabled(isBypassChanged);
    }
    // Признак кеширования
    else if (value.name == "caching")
    {
        const bool isCaching = node_->isCaching();
        ui_.checkBoxCaching_->setChecked(isCaching);
        const bool isCachingChanged = node_->isCachingChanged();
        ui_.pushBtnResetCaching_->setEnabled(isCachingChanged);
    }
    // Комментарий
    else if (value.name == "comment")
    {
        const QString comment = node_->comment();
        ui_.lineEditComment_->setText(comment);
        ui_.lineEditComment_->setToolTip(comment);
        const bool isCommentChanged = node_->isCommentChanged();
        ui_.pushBtnResetComment_->setEnabled(isCommentChanged);
    }
}

//==============================================================
// Функция вызывается при изменении состояния узла
//==============================================================
void FormSizeNode::slotChangedNodeState(const NodeStateInfo &stateInfo)
{
    showNodeState(stateInfo, ui_.plainTextEditState_);
}

//==============================================================
// Функция вызывается при завершении редактирования имени
//==============================================================
void FormSizeNode::slotEditingFinishedName()
{
    const QString name = ui_.lineEditName_->text();
    node_->setName(name);
}

//==============================================================
// Функция вызывается при изменении размерности
//==============================================================
void FormSizeNode::slotChangedUnit(int index)
{
    if (index == -1)
    {
        return;
    }

    const SizeUnits unit = intToSizeUnit(index);
    Q_ASSERT(!isUnknown(unit));
    node_->setUnit(unit);
}

//==============================================================
// Сброс размерности
//==============================================================
void FormSizeNode::slotResetUnit()
{
    node_->resetUnit();

    ui_.comboBoxUnit_->setFocus();
}

//==============================================================
// Функция вызывается при изменении признака пропуска узла
//==============================================================
void FormSizeNode::slotChangedBypass(int state)
{
    const bool bypass = static_cast<bool>(state);
    node_->setBypass(bypass);
}

//==============================================================
// Сброс признака пропуска узла
//==============================================================
void FormSizeNode::slotResetBypass()
{
    node_->resetBypass();

    ui_.checkBoxBypass_->setFocus();
}

//==============================================================
// Функция вызывается при изменении признак кеширования узла
//==============================================================
void FormSizeNode::slotChangedCaching(int state)
{
    const bool caching = static_cast<bool>(state);
    node_->setCaching(caching);
}

//==============================================================
// Сброс признака кеширования
//==============================================================
void FormSizeNode::slotResetCaching()
{
    node_->resetCaching();

    ui_.checkBoxCaching_->setFocus();
}

//==============================================================
// Функция вызывается при завершении редактирования комментария
//==============================================================
void FormSizeNode::slotEditingFinishedComment()
{
    const QString comment = ui_.lineEditComment_->text();
    node_->setComment(comment);
}

//==============================================================
// Сброс комментария
//==============================================================
void FormSizeNode::slotResetComment()
{
    node_->resetComment();

    ui_.lineEditComment_->setFocus();
}

//==============================================================
// Задание узла
//==============================================================
void FormSizeNode::setNode(SizeNode *node)
{
    Q_ASSERT(node != nullptr);

    node_ = node;

    // Задание имени
    const QString name = node_->name();
    ui_.lineEditName_->setText(name);
    ui_.lineEditName_->setToolTip(name);

    // Задание размерности
    const SizeUnits unit = node->unit();
    const int unitIndex = sizeUnitToInt(unit);
    ui_.comboBoxUnit_->setCurrentIndex(unitIndex);
    const bool isUnitChanged = node->isUnitChanged();
    ui_.pushBtnResetUnit_->setEnabled(isUnitChanged);

    // Задание признака пропуска
    const bool isBypass = node->isBypass();
    ui_.checkBoxBypass_->setChecked(isBypass);
    const bool isBypassChanged = node->isBypassChanged();
    ui_.pushBtnResetBypass_->setEnabled(isBypassChanged);

    // Задание признака кеширования
    const bool isCaching = node->isCaching();
    ui_.checkBoxCaching_->setChecked(isCaching);
    const bool isCachingChanged = node->isCachingChanged();
    ui_.pushBtnResetCaching_->setEnabled(isCachingChanged);

    // Задание комментария
    const QString comment = node->comment();
    ui_.lineEditComment_->setText(comment);
    ui_.lineEditComment_->setToolTip(comment);
    const bool isCommentChanged = node->isCommentChanged();
    ui_.pushBtnResetComment_->setEnabled(isCommentChanged);

    // Задание состояния
    showNodeState(node_->stateInfo(), ui_.plainTextEditState_);
}

//==============================================================
// Задание соединений
//==============================================================
void FormSizeNode::setConnections()
{
    connect(node_, &BaseNode::sigChangedProp,
        this, &FormSizeNode::slotChangedNodeProp);
    connect(node_, &SizeNode::sigChangedState,
        this, &FormSizeNode::slotChangedNodeState);

    connect(ui_.lineEditName_, &QLineEdit::editingFinished,
        this, &FormSizeNode::slotEditingFinishedName);

    connect(ui_.comboBoxUnit_, qOverload<int>(&QComboBox::currentIndexChanged),
        this, &FormSizeNode::slotChangedUnit);
    connect(ui_.pushBtnResetUnit_, &QPushButton::clicked,
        this, &FormSizeNode::slotResetUnit);

    connect(ui_.checkBoxBypass_, &QCheckBox::stateChanged,
        this, &FormSizeNode::slotChangedBypass);
    connect(ui_.pushBtnResetBypass_, &QPushButton::clicked,
        this, &FormSizeNode::slotResetBypass);

    connect(ui_.checkBoxCaching_, &QCheckBox::stateChanged,
        this, &FormSizeNode::slotChangedCaching);
    connect(ui_.pushBtnResetCaching_, &QPushButton::clicked,
        this, &FormSizeNode::slotResetCaching);

    connect(ui_.lineEditComment_, &QLineEdit::editingFinished,
        this, &FormSizeNode::slotEditingFinishedComment);
    connect(ui_.pushBtnResetComment_, &QPushButton::clicked,
        this, &FormSizeNode::slotResetComment);
}
