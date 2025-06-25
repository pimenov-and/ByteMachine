////////////////////////////////////////////////////////////////
// ByteMachine
// Класс проекта
////////////////////////////////////////////////////////////////
#ifndef PROJECT_H
#define PROJECT_H

//==============================================================
#include <QObject>
#include <QVector>
#include <QUndoStack>
#include "i_project_settings.h"
#include "base_node.h"
#include "prop_value.h"

//==============================================================
// Класс проекта
//==============================================================
class Project : public QObject, public IProjectSettings
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(Project)
    Q_PROPERTY(QString name READ name WRITE setName RESET resetName)
    Q_PROPERTY(QString comment READ comment WRITE setComment RESET resetComment)
    Q_PROPERTY(bool isUndo READ isUndo WRITE setUndo RESET resetUndo)
public:
    // Получение экземпляра
    static Project* instance();

    // Получение имени
    QString name() const override { return name_; }
    // Задание имени
    void setName(const QString &name) override;
    // Сброс имени
    void resetName() override;
    // Получение признака изменения имени
    bool isNameChanged() const override { return name_ != "Project"; }
    // Получение комментария
    QString comment() const override { return comment_; }
    // Задание комментария
    void setComment(const QString &comment) override;
    // Сброс комментария
    void resetComment() override;
    // Получение признака изменения комментария
    bool isCommentChanged() const override { return !comment_.isEmpty(); }

    // Получение признака режима отмены
    bool isUndo() const { return isUndo_; }
    // Задание признака режима отмены
    void setUndo(bool isUndo);
    // Сброс признака режима отмены
    void resetUndo();
    // Получение признака изменения режима отмены
    bool isUndoChanged() const { return isUndo_ == true; }

    // Получение списка узлов
    [[nodiscard]]
    const QVector<ShPtrBaseNode>& nodes() { return nodes_; }
    // Получение списка узлов (константная версия)
    [[nodiscard]]
    QVector<ShPtrConstBaseNode> nodes() const;
    // Получение количества узлов
    [[nodiscard]]
    qint32 nodeCount() const { return nodes_.count(); }

    // Создание действия Undo
    QAction* createActionUndo() const;
    // Создание действия Redo
    QAction* createActionRedo() const;
signals:
    // Сигнал возникает при изменении узла
    void sigChangedProp(PropValue value);
private:
    // Конструктор с параметром
    explicit Project(QObject *parent = nullptr);

    // Задание соединений
    void setConnections();

    // Имя
    QString name_{"Project"};
    // Комментарий
    QString comment_{};
    // Путь к файлу проекта
    mutable QString path_{};
    // Узлы
    QVector<ShPtrBaseNode> nodes_{};
    // Стек отмен
    QUndoStack undoStack_{};
    // Признак режима отмены
    bool isUndo_{false};
};

//==============================================================
// Прототипы функций
//==============================================================
// Получение проекта
Project* project();

//==============================================================
#endif // PROJECT_H
