////////////////////////////////////////////////////////////////
// ByteMachine
// Виджет с настроеками проекта
////////////////////////////////////////////////////////////////
#include "form_project_settings.h"
#include <QDebug>
#include <chrono>

//==============================================================
using namespace std::chrono;

//==============================================================
// Конструктор с параметром
//==============================================================
FormProjectSettings::FormProjectSettings(Project *project,
    QWidget *parent) :
    QWidget{parent}
{
    Q_ASSERT(project != nullptr);

    ui_.setupUi(this);

    setSettings(project);
    setConnections();
}

//==============================================================
// Деструктор
//==============================================================
FormProjectSettings::~FormProjectSettings()
{
}

//==============================================================
// Функция вызывается при изменении в настройках
//==============================================================
void FormProjectSettings::slotSettingsChanged(PropValue value)
{
    if (value.name == "name")
    {
        const QString projectName = project_->name();
        ui_.lineEditName_->setText(projectName);
        ui_.lineEditName_->setToolTip(projectName);
        emit ui_.lineEditName_->returnPressed();
        const bool isProjectNameChanged = project_->isNameChanged();
        ui_.pushBtnResetName_->setEnabled(isProjectNameChanged);
    }
    else if (value.name == "comment")
    {
        const QString comment = project_->comment();
        if (ui_.plainTextEditComment_->toPlainText() != comment)
        {
            ui_.plainTextEditComment_->setPlainText(comment);
        }
        const bool isCommentChanged = project_->isCommentChanged();
        ui_.pushBtnResetComment_->setEnabled(isCommentChanged);
    }
}

//==============================================================
// Функция вызывается при завершении редактирования имени
//==============================================================
void FormProjectSettings::slotEditingFinishedName()
{
    const QString name = ui_.lineEditName_->text();
    project_->setName(name);
}

//==============================================================
// Сброс имени
//==============================================================
void FormProjectSettings::slotResetName()
{
    project_->resetName();
    ui_.lineEditName_->setFocus();
}

//==============================================================
// Функция вызывается при редактировании комментария
//==============================================================
void FormProjectSettings::slotCommentEditing()
{
    if (editCommentTimerId_ != -1)
    {
        killTimer(editCommentTimerId_);
    }
    editCommentTimerId_ = startTimer(200ms);
}

//==============================================================
// Сброс комментария
//==============================================================
void FormProjectSettings::slotResetComment()
{
    project_->resetComment();
    ui_.plainTextEditComment_->setFocus();
}

//==============================================================
// Задание настроек
//==============================================================
void FormProjectSettings::setSettings(Project *project)
{
    Q_ASSERT(project != nullptr);

    project_ = project;

    const QString projectName = project_->name();
    ui_.lineEditName_->setText(projectName);
    const bool isProjectNameChanged = project_->isNameChanged();
    ui_.pushBtnResetName_->setEnabled(isProjectNameChanged);

    const QString comment = project_->comment();
    ui_.plainTextEditComment_->setPlainText(comment);
    const bool isCommentChanged = project_->isCommentChanged();
    ui_.pushBtnResetComment_->setEnabled(isCommentChanged);
}

//==============================================================
// Задание соединений
//==============================================================
void FormProjectSettings::setConnections()
{
    connect(project_, &Project::sigChangedProp,
        this, &FormProjectSettings::slotSettingsChanged);

    connect(ui_.lineEditName_, &QLineEdit::editingFinished,
        this, &FormProjectSettings::slotEditingFinishedName);
    connect(ui_.pushBtnResetName_, &QPushButton::clicked,
        this, &FormProjectSettings::slotResetName);

    connect(ui_.plainTextEditComment_, &QPlainTextEdit::textChanged,
        this, &FormProjectSettings::slotCommentEditing);
    connect(ui_.pushBtnResetComment_, &QPushButton::clicked,
        this, &FormProjectSettings::slotResetComment);
}

//==============================================================
// Функция вызывается при изменении комментария
//==============================================================
void FormProjectSettings::changedComment()
{
    const QString comment = ui_.plainTextEditComment_->toPlainText();
    project_->setComment(comment);
}

//==============================================================
// Функция вызывается при срабатывании таймера
//==============================================================
void FormProjectSettings::timerEvent(QTimerEvent*)
{
    killTimer(editCommentTimerId_);
    editCommentTimerId_ = -1;
    changedComment();
}
