////////////////////////////////////////////////////////////////
// ByteMachine
// Виджет с настроеками проекта
////////////////////////////////////////////////////////////////
#ifndef FORM_PROJECT_SETTINGS_H
#define FORM_PROJECT_SETTINGS_H

//==============================================================
#include <QWidget>
#include "ui_form_project_settings.h"
#include "project.h"

//==============================================================
namespace Ui
{
    class FormProjectSettings;
}
class ProjectSettings;

//==============================================================
// Виджет с настроеками проекта
//==============================================================
class FormProjectSettings : public QWidget
{
    Q_OBJECT
public:
    // Конструктор с параметром
    explicit FormProjectSettings(Project *project,
        QWidget *parent = nullptr);
    // Деструктор
    ~FormProjectSettings() override;
private slots:
    // Функция вызывается при изменении в настройках
    void slotSettingsChanged(PropValue value);
    // Функция вызывается при завершении редактирования имени
    void slotEditingFinishedName();
    // Сброс имени
    void slotResetName();
    // Функция вызывается при редактировании комментария
    void slotCommentEditing();
    // Сброс комментария
    void slotResetComment();
private:
    // Функция вызывается при срабатывании таймера
    void timerEvent(QTimerEvent*) override;

    // Задание настроек
    void setSettings(Project *project);
    // Задание соединений
    void setConnections();
    // Функция вызывается при изменении комментария
    void changedComment();

    // Интерфейс пользователя
    Ui::FormProjectSettings ui_{};
    // Настройки
    Project *project_{nullptr};
    // Идентификатор таймера, используемого при редактировании комментария
    int editCommentTimerId_{-1};
    // Признак отмены
    bool isUndo_{false};
};

//==============================================================
#endif // FORM_PROJECT_SETTINGS_H
