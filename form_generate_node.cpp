////////////////////////////////////////////////////////////////
// ByteMachine
// Виджет для настройки узла "Generate"
////////////////////////////////////////////////////////////////
#include "form_generate_node.h"
#include "ui_form_generate_node.h"
#include "generate_node.h"

//==============================================================
// Конструктор с параметром
//==============================================================
FormGenerateNode::FormGenerateNode(GenerateNode *node, QWidget *parent) :
    QWidget{parent},
    ui_{new Ui::FormGenerateNode{}}
{
    Q_ASSERT(node != nullptr);

    ui_->setupUi(this);

    setNode(node);
    setConnections();
}

//==============================================================
// Деструктор
//==============================================================
FormGenerateNode::~FormGenerateNode()
{
    delete ui_;
}

//==============================================================
// Функция вызывается при изменении свойств узла
//==============================================================
void FormGenerateNode::slotChangedNodeProp(PropValue value)
{
    // Имя
    if (value.name == "name")
    {
    }
    // Комментарий
    else if (value.name == "comment")
    {
    }
}

//==============================================================
// Функция вызывается при завершении редактирования имени
//==============================================================
void FormGenerateNode::slotEditingFinishedName()
{
}

//==============================================================
// Функция вызывается при завершении редактирования комментария
//==============================================================
void FormGenerateNode::slotEditingFinishedComment()
{
    const QString comment = ui_->lineEditComment_->text();
    node_->setComment(comment);
}

//==============================================================
// Сброс комментария
//==============================================================
void FormGenerateNode::slotResetComment()
{
    node_->resetComment();

    ui_->lineEditComment_->setFocus();
}

//==============================================================
// Задание соединений
//==============================================================
void FormGenerateNode::setConnections()
{
}

//==============================================================
// Задание узла
//==============================================================
void FormGenerateNode::setNode(GenerateNode *node)
{
    Q_ASSERT(node != nullptr);
}
