////////////////////////////////////////////////////////////////
// ByteMachine
// Виджет с настроеками проекта
////////////////////////////////////////////////////////////////
#include "form_project_settings.h"
#include <QDebug>

//==============================================================
// Конструктор с параметром
//==============================================================
FormProjectSettings::FormProjectSettings(QWidget *parent) : QWidget{parent}
{
    ui_.setupUi(this);
}

//==============================================================
// Деструктор
//==============================================================
FormProjectSettings::~FormProjectSettings()
{
}
