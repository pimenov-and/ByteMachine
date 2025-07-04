////////////////////////////////////////////////////////////////
// ByteMachine
// Базовый класс узла
////////////////////////////////////////////////////////////////
#ifndef BASE_NODE_H
#define BASE_NODE_H

//==============================================================
#include <QObject>
#include <QSharedPointer>
#include "node_types.h"
#include "i_data.h"
#include "i_xml.h"
#include "i_to_str.h"
#include "prop_value.h"

//==============================================================
class QPainter;
class QUndoStack;

//==============================================================
// Базовый класс узла
//==============================================================
class BaseNode : public QObject, public IData, public IXml, public IToStr
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString comment READ comment WRITE setComment RESET resetComment)
    Q_PROPERTY(bool isUndo READ isUndo WRITE setUndo RESET resetUndo)
public:
    // Конструктор с параметром
    explicit BaseNode(QUndoStack *undoStack = nullptr,
        QObject *parent = nullptr);
    // Деструктор
    ~BaseNode() override;

    // Получение имени
    [[nodiscard]]
    QString name() const { return name_; }
    // Задание имени
    void setName(const QString &name);
    // Получение комментария
    [[nodiscard]]
    QString comment() const { return comment_; }
    // Задание комментария
    void setComment(const QString &comment);
    // Сброс комментария
    void resetComment();
    // Получение признака изменения комментария
    [[nodiscard]]
    bool isCommentChanged() const { return !comment_.isEmpty(); }

    // Получение типа узла
    [[nodiscard]]
    virtual NodeTypes type() const = 0;
    // Получение типа узла в виде строки
    [[nodiscard]]
    QString strType() const { return nodeTypeToStr(type()); }
    // Получение представления в виде строки
    virtual QString toStr() const override;
    // Функция вывода
    virtual void draw(QPainter *painter) const = 0;
    // Получение копии узла
    [[nodiscard]]
    virtual QSharedPointer<BaseNode> clone() const = 0;
    // Получение текста подсказки
    [[nodiscard]]
    virtual QString tooltipText() const = 0;
    // Получение признака изменения размера
    [[nodiscard]]
    virtual bool isResizeble() const = 0;
    // Получение признака того, что узел поддерживает прокрутку
    [[nodiscard]]
    virtual bool isScrollable() const = 0;

    // Получение стека отмен
    [[nodiscard]]
    QUndoStack* undoStack() { return undoStack_; }
    // Получение стека отмен (константный вариант)
    [[nodiscard]]
    const QUndoStack* undoStack() const { return undoStack_; }
    // Задание стека отмен
    void setUndoStack(QUndoStack *undoStack);

    // Получение признака режима отмены
    [[nodiscard]]
    bool isUndo() const { return isUndo_; }
    // Задание признака режима отмены
    void setUndo(bool isUndo);
    // Сброс признака режима отмены
    void resetUndo();
    // Получение признака изменения режима отмены
    [[nodiscard]]
    bool isUndoChanged() const { return isUndo_ == true; }
signals:
    // Сигнал возникает при изменении узла
    void sigChangedProp(PropValue value);
protected:
    // Имя
    QString name_{};
    // Комментарий
    QString comment_{};
    // Признак режима отмены
    bool isUndo_{false};
    // Стек отмен
    QUndoStack *undoStack_{nullptr};
private:
    // Идентификатор
    qint32 id_{0};
    // Выделение
    bool isSelected_{false};

    // Тип комментариев
    static bool isCommentsVisible_;
};

//==============================================================
using ShPtrBaseNode = QSharedPointer<BaseNode>;
using ShPtrConstBaseNode = QSharedPointer<const BaseNode>;

//==============================================================
// Прототипы функций
//==============================================================

//==============================================================
#endif // BASE_NODE_H
