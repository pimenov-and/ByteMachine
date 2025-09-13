////////////////////////////////////////////////////////////////
// ByteMachine
// Команда отмены значения свойства объекта
////////////////////////////////////////////////////////////////
#ifndef UNDO_CHANGE_OBJECT_PROP_VALUE_H
#define UNDO_CHANGE_OBJECT_PROP_VALUE_H

//==============================================================
#include <QUndoCommand>
#include <QVariant>

//==============================================================
// Команда отмены значения свойства объекта
//==============================================================
class UndoChangeObjectPropValue : public QUndoCommand
{
public:
    // Конструктор с параметрами
    UndoChangeObjectPropValue(QObject *object, const QString &propName,
        const QVariant &propValue, const QVariant &oldPropValue);
    // Деструктор
    ~UndoChangeObjectPropValue() override;

    // Функция отмены
    void undo() override;
    // Функция восстановления
    void redo() override;
private:
    // Проект
    QObject *object_{nullptr};
    // Имя свойства
    QString propName_{};
    // Значение свойства
    QVariant propValue_{};
    // Старое значение свойства
    QVariant oldPropValue_{};
};

//==============================================================
#endif // UNDO_CHANGE_OBJECT_PROP_VALUE_H
