////////////////////////////////////////////////////////////////
// ByteMachine
// Интерфейс настроек проекта
////////////////////////////////////////////////////////////////
#ifndef I_PROJECT_SETTINGS_H
#define I_PROJECT_SETTINGS_H

//==============================================================
#include <QString>

//==============================================================
// Интерфейс настроек проекта
//==============================================================
struct IProjectSettings
{
    // Деструктор
    virtual ~IProjectSettings() = default;

    // Получение имени
    [[nodiscard]]
    virtual QString name() const = 0;
    // Задание имени
    virtual void setName(const QString &name) = 0;
    // Сброс имени
    virtual void resetName() = 0;
    // Получение признака изменения имени
    [[nodiscard]]
    virtual bool isNameChanged() const = 0;

    // Получение комментария
    [[nodiscard]]
    virtual QString comment() const = 0;
    // Задание комментария
    virtual void setComment(const QString &comment) = 0;
    // Сброс комментария
    virtual void resetComment() = 0;
    // Получение признака изменения комментария
    [[nodiscard]]
    virtual bool isCommentChanged() const = 0;
};

//==============================================================
#endif // I_PROJECT_SETTINGS_H
