////////////////////////////////////////////////////////////////
// ByteMachine
// Базовый класс узла
////////////////////////////////////////////////////////////////
#include "base_node.h"
#include "undo_change_object_prop_value.h"
#include <QUndoStack>
#include <QColor>
#include <QPen>
#include <QPainter>
#include <QDebug>
#include <algorithm>

//==============================================================
using std::find;
using std::distance;

////////////////////////////////////////////////////////////////
// Реализация класса BaseNode
////////////////////////////////////////////////////////////////

//==============================================================
//  Статические поля
//==============================================================
// Тип комментариев
bool BaseNode::isCommentsVisible_{false};

//==============================================================
// Конструктор с параметром
//==============================================================
BaseNode::BaseNode(QUndoStack *undoStack, QObject *parent) :
    QObject{parent}
{
    Q_ASSERT(undoStack != nullptr);

    undoStack_ = undoStack;
}

//==============================================================
// Деструктор
//==============================================================
BaseNode::~BaseNode()
{
}

//==============================================================
// Задание имени
//==============================================================
void BaseNode::setName(const QString &name)
{
    if (name_ != name)
    {
        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
            const QString oldName = name_;
            const auto undoCmd = new UndoChangeObjectPropValue{this,
                "name", name, oldName};
            undoStack_->push(undoCmd);
        }

        name_ = name;
        const PropValue value{"name", name_};
        emit sigChangedProp(value);
    }
}

//==============================================================
// Задание комментария
//==============================================================
void BaseNode::setComment(const QString &comment)
{
    if (comment_ != comment)
    {
        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
            const QString oldComment = comment_;
            const auto undoCmd = new UndoChangeObjectPropValue{this,
                "comment", comment, oldComment};
            undoStack_->push(undoCmd);
        }

        comment_ = comment;
        const PropValue value{"comment", comment_};
        emit sigChangedProp(value);
    }
}

//==============================================================
// Сброс комментария
//==============================================================
void BaseNode::resetComment()
{
    setComment(QString{});
}

//==============================================================
// Получение представления в виде строки
//==============================================================
QString BaseNode::toStr() const
{
    return name() + " : " + strType();
}

//==============================================================
// Задание стека отмен
//==============================================================
void BaseNode::setUndoStack(QUndoStack *undoStack)
{
    Q_ASSERT(undoStack != nullptr);

    if (undoStack_ != undoStack)
    {
        undoStack_ = undoStack;
    }
}

//==============================================================
// Задание признака режима отмены
//==============================================================
void BaseNode::setUndo(bool isUndo)
{
    if (isUndo_ != isUndo)
    {
        isUndo_ = isUndo;
    }
}

//==============================================================
// Сброс признака отмены
//==============================================================
void BaseNode::resetUndo()
{
    setUndo(false);
}

//==============================================================
// Задание смещения слева
//==============================================================
void BaseNode::setLeft(qint32 left) noexcept
{
    if (left_ != left)
    {
        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
            const int oldLeft = left_;
            const auto undoCmd = new UndoChangeObjectPropValue{this,
                "left", left, oldLeft};
            undoStack_->push(undoCmd);
        }

        left_ = left;
        const PropValue value{"left", left_};
        emit sigChangedProp(value);
    }
}

//==============================================================
// Задание смещения сверху
//==============================================================
void BaseNode::setTop(qint32 top) noexcept
{
    if (top_ != top)
    {
        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
            const int oldTop = top_;
            const auto undoCmd = new UndoChangeObjectPropValue{this,
                "top", top, oldTop};
            undoStack_->push(undoCmd);
        }

        top_ = top;
        const PropValue value{"top", top_};
        emit sigChangedProp(value);
    }
}

//==============================================================
// Задание ширины узла
//==============================================================
void BaseNode::setWidth(qint32 width)
{
    if (width_ != width)
    {
        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
        }

        width_ = width;
        const PropValue value{"width", width_};
        emit sigChangedProp(value);
    }
}

//==============================================================
// Задание высоты узла
//==============================================================
void BaseNode::setHeight(qint32 height)
{
    if (height_ != height)
    {
        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
        }

        height_ = height;
        const PropValue value{"height", height_};
        emit sigChangedProp(value);
    }
}

//==============================================================
// Получение центра
//==============================================================
QPoint BaseNode::center() const
{
    return QPoint{left() + width() / 2, top() + height() / 2};
}

//==============================================================
// Задание левого верхнего угла
//==============================================================
void BaseNode::setTopLeft(const QPoint &topLeft)
{
    if (this->topLeft() != topLeft)
    {
        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
        }

        setLeft(topLeft.x());
        setTop(topLeft.y());
    }
}

//==============================================================
// Задание размера узла
//==============================================================
void BaseNode::setSize(const QSize &size)
{
    if (this->size() != size)
    {
        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
        }

        setWidth(size.width());
        setHeight(size.height());
    }
}

//==============================================================
// Получение входных пинов
//==============================================================
QVector<ShPtrInputPin> BaseNode::inputPins()
{
    return QVector<ShPtrInputPin>{};
}

//==============================================================
// Получение входных пинов (константный вариант)
//==============================================================
QVector<ShPtrConstInputPin> BaseNode::inputPins() const
{
    return QVector<ShPtrConstInputPin>{};
}

//==============================================================
// Получение областей входных пинов (константный вариант)
//==============================================================
QVector<QRect> BaseNode::inputPinRects() const
{
    const QSet<int> possiblePinCount = {0, 1, 2};
    const int pinCount = inputPinCount();
    Q_ASSERT(possiblePinCount.contains(pinCount));

    const int pinWidth = BasePin::width();
    const int pinHeight = BasePin::height();
    const int pinTop = top() - pinHeight / 2;
    const int centerX = left() + width() / 2;
    QVector<QRect> rects{};

    // Два пина
    if (pinCount == 2)
    {
        const int pinLeft = centerX - width() / 4 - pinWidth / 2 + 4;
        rects << QRect{pinLeft, pinTop, pinWidth, pinHeight};

        const int pinRight = centerX + width() / 4 - pinWidth / 2 - 4;
        rects << QRect{pinRight, pinTop, pinWidth, pinHeight};

        return rects;
    }
    // Один пин
    else if (pinCount == 1)
    {
        const int pinLeft = center().x() - pinWidth / 2;
        rects << QRect{pinLeft, pinTop, pinWidth, pinHeight};

        return rects;
    }
    // Нет пинов
    else
    {
        return QVector<QRect>{};
    }
}

//==============================================================
// Получение входного пина по индексу
//==============================================================
ShPtrInputPin BaseNode::inputPin(int index)
{
    if (inputPinCount() != 0)
    {
        Q_ASSERT((index >= 0) && (index < inputPinCount()));

        return inputPins().at(index);
    }
    else
    {
        return nullptr;
    }
}

//==============================================================
// Получение входного пина по индексу (константный вариант)
//==============================================================
ShPtrConstInputPin BaseNode::inputPin(int index) const
{
    if (inputPinCount() != 0)
    {
        Q_ASSERT((index >= 0) && (index < inputPinCount()));

        return inputPins().at(index);
    }
    else
    {
        return nullptr;
    }
}

//==============================================================
// Получение области входного пина по индексу
//==============================================================
QRect BaseNode::inputPinRect(int index) const
{
    if (inputPinCount() != 0)
    {
        return inputPinRects().at(index);
    }
    else
    {
        return QRect{};
    }
}

//==============================================================
// Проверка наличия входного пина
//==============================================================
bool BaseNode::containsInputPin(const ShPtrInputPin &pin) const
{
    return inputPins().contains(pin);
}

//==============================================================
// Провека наличия выходного пина (константный вариант)
//==============================================================
bool BaseNode::containsInputPin(const InputPin *pin) const
{
    const QVector<ShPtrConstInputPin> pins = inputPins();

    return find(pins.cbegin(), pins.cend(), pin) != pins.cend();
}

//==============================================================
// Получение индекса входного пина
//==============================================================
int BaseNode::indexOfInputPin(const ShPtrInputPin &pin) const
{
    return inputPins().indexOf(pin);
}

//==============================================================
// Получение индекса входного пина (сырой указатель)
//==============================================================
int BaseNode::indexOfInputPin(const InputPin *pin) const
{
    const QVector<ShPtrConstInputPin> pins = inputPins();
    const auto it = find(pins.cbegin(), pins.cend(), pin);
    if (it != pins.cend())
    {
        return distance(pins.begin(), it);
    }
    else
    {
        return -1;
    }
}

//==============================================================
// Получение выходных пинов
//==============================================================
QVector<ShPtrOutputPin> BaseNode::outputPins()
{
    return QVector<ShPtrOutputPin>{};
}

//==============================================================
// Получение выходных пинов (константный вариант)
//==============================================================
QVector<ShPtrConstOutputPin> BaseNode::outputPins() const
{
    return QVector<QSharedPointer<const OutputPin>>{};
}

//==============================================================
// Получение областей выходных пинов
//==============================================================
QVector<QRect> BaseNode::ouputPinRects() const
{
    const int pinCount = outputPinCount();
    Q_ASSERT((pinCount == 0) || (pinCount == 1));

    if (pinCount == 1)
    {
        const int pinWidth = BasePin::width();
        const int pinHeight = BasePin::height();
        const int pinLeft = center().x() - pinWidth / 2;
        const int pinTop = bottom() - pinHeight / 2;
        const QRect pinRect{pinLeft, pinTop, pinWidth, pinHeight};

        return QVector<QRect>{pinRect};
    }
    else
    {
        return QVector<QRect>{};
    }
}

//==============================================================
// Получение выходного пина по индексу
//==============================================================
ShPtrOutputPin BaseNode::outputPin(int index)
{
    if (outputPinCount() != 0)
    {
        Q_ASSERT((index >= 0) && (index < outputPinCount()));

        return outputPins().at(index);
    }
    else
    {
        return nullptr;
    }
}

//==============================================================
// Получение выходного пина по индексу (константный вариант)
//==============================================================
ShPtrConstOutputPin BaseNode::outputPin(int index) const
{
    if (outputPinCount() != 0)
    {
        Q_ASSERT((index >= 0) && (index < outputPinCount()));

        return outputPins().at(index);
    }
    else
    {
        return nullptr;
    }
}

//==============================================================
// Получение области выходного пина по индексу
//==============================================================
QRect BaseNode::outputPinRect(int index) const
{
    if (outputPinCount() != 0)
    {
        Q_ASSERT((index >= 0) && (index < outputPinCount()));

        return ouputPinRects().at(index);
    }
    else
    {
        return QRect{};
    }
}

//==============================================================
// Проверка наличия выходного пина
//==============================================================
bool BaseNode::containsOutputPin(const ShPtrOutputPin &pin) const
{
    return outputPins().contains(pin);
}

//==============================================================
// Проверка наличия выходного пина (сырой указатель)
//==============================================================
bool BaseNode::containsOutputPin(const OutputPin *pin) const
{
    const QVector<ShPtrConstOutputPin> pins = outputPins();

    return find(pins.cbegin(), pins.cend(), pin) != pins.cend();
}

//==============================================================
// Получение индекса выходного пина
//==============================================================
int BaseNode::indexOfOutputPin(const ShPtrOutputPin &pin) const
{
    return outputPins().indexOf(pin);
}

//==============================================================
// Получение индекса выходного пина (сырой указатель)
//==============================================================
int BaseNode::indexOfOutputPin(const OutputPin *pin) const
{
    const QVector<ShPtrConstOutputPin> pins = outputPins();
    const auto it = find(pins.cbegin(), pins.cend(), pin);
    if (it != pins.cend())
    {
        return distance(pins.begin(), it);
    }
    else
    {
        return -1;
    }
}

//==============================================================
// Рисование примитивной основы
//==============================================================
void BaseNode::drawSimpleBody(QPainter *painter) const
{
    Q_ASSERT(painter != nullptr);

    const QColor color{110, 110, 110};
    QPen pen{color, 2};
    pen.setJoinStyle(Qt::MiterJoin);
    painter->setPen(pen);
    painter->setBrush(Qt::white);
    painter->drawRect(rect());
}

////////////////////////////////////////////////////////////////
// Реализация функций
////////////////////////////////////////////////////////////////
