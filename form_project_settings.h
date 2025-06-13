////////////////////////////////////////////////////////////////
// ByteMachine
// Виджет с настроеками проекта
////////////////////////////////////////////////////////////////
#ifndef FORM_PROJECT_SETTINGS_H
#define FORM_PROJECT_SETTINGS_H

//==============================================================
#include <QWidget>
#include "ui_form_project_settings.h"

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
    explicit FormProjectSettings(QWidget *parent = nullptr);
    // Деструктор
    ~FormProjectSettings() override;
private slots:
private:
    // Интерфейс пользователя
    Ui::FormProjectSettings ui_{};
};

//==============================================================
#endif // FORM_PROJECT_SETTINGS_H
