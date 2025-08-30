////////////////////////////////////////////////////////////////
// ByteMachine
// Базовый класс узла
////////////////////////////////////////////////////////////////
#include "base_node.h"
#include "node_name_manager.h"
#include "undo_change_object_prop_value.h"
#include "colors.h"
#include "xml_helper.h"
#include "qt_helper.h"
#include "base_exception.h"
#include <QUndoStack>
#include <QColor>
#include <QPen>
#include <QPainter>
#include <QDomDocument>
#include <QDebug>
#include <algorithm>
#include <optional>

//==============================================================
using std::find;
using std::distance;
using std::optional;

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
        QString newName = name;
        if (name.isEmpty())
        {
            newName = name_;
        }

        nodeNameManager()->removeName(name_);
        newName = nodeNameManager()->addName(newName);

        const QString oldName = name_;
        name_ = newName;
        const PropValue value{"name", name_};
        emit sigChangedProp(value);

        if (!isUndo_ && (oldName != newName))
        {
            Q_ASSERT(undoStack_ != nullptr);
            const auto undoCmd = new UndoChangeObjectPropValue{this,
                "name", newName, oldName};
            undoStack_->push(undoCmd);
        }
    }
}

//==============================================================
// Задание комментария
//==============================================================
void BaseNode::setComment(const QString &comment)
{
    if (comment_ != comment)
    {
        const QString oldComment = comment_;
        comment_ = comment;
        const PropValue value{"comment", comment_};
        emit sigChangedProp(value);

        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
            const auto undoCmd = new UndoChangeObjectPropValue{this,
                "comment", comment, oldComment};
            undoStack_->push(undoCmd);
        }
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
    if (left < gridSize())
    {
        left = gridSize();
    }

    if (left_ != left)
    {
        const int oldLeft = left_;
        left_ = left;
        const PropValue value{"left", left_};
        emit sigChangedProp(value);

        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
            const auto undoCmd = new UndoChangeObjectPropValue{this,
                "left", left, oldLeft};
            undoStack_->push(undoCmd);
        }
    }
}

//==============================================================
// Задание смещения сверху
//==============================================================
void BaseNode::setTop(qint32 top) noexcept
{
    if (top < gridSize())
    {
        top = gridSize();
    }

    if (top_ != top)
    {
        const int oldTop = top_;
        top_ = top;
        const PropValue value{"top", top_};
        emit sigChangedProp(value);

        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
            const auto undoCmd = new UndoChangeObjectPropValue{this,
                "top", top, oldTop};
            undoStack_->push(undoCmd);
        }
    }
}

//==============================================================
// Задание ширины узла
//==============================================================
void BaseNode::setWidth(qint32 width)
{
    if (width_ != width)
    {
        const int oldWidth = width_;
        width_ = width;
        const PropValue value{"width", width_};
        emit sigChangedProp(value);

        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
            const auto undoCmd = new UndoChangeObjectPropValue{this,
                "width", width, oldWidth};
            undoStack_->push(undoCmd);
        }
    }
}

//==============================================================
// Задание высоты узла
//==============================================================
void BaseNode::setHeight(qint32 height)
{
    if (height_ != height)
    {
        const int oldHeight = height_;
        height_ = height;
        const PropValue value{"height", height_};
        emit sigChangedProp(value);

        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
            const auto undoCmd = new UndoChangeObjectPropValue{this,
                "height", height, oldHeight};
            undoStack_->push(undoCmd);
        }
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
void BaseNode::setTopLeft(QPoint topLeft)
{
    if (topLeft.x() < gridSize())
    {
        topLeft.setX(gridSize());
    }
    if (topLeft.y() < gridSize())
    {
        topLeft.setY(gridSize());
    }

    if (this->topLeft() != topLeft)
    {
        const int oldLeft = left_;
        const int oldTop = top_;
        left_ = topLeft.x();
        top_ = topLeft.y();

        const PropValue value{"topLeft", topLeft};
        emit sigChangedProp(value);

        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
            const auto undoCmd = new UndoChangeObjectPropValue{this,
                "topLeft", QPoint{left_, top_},
                QPoint{oldLeft, oldTop}};
            undoStack_->push(undoCmd);
        }
    }
}

//==============================================================
// Задание размера узла
//==============================================================
void BaseNode::setSize(const QSize &size)
{
    if (this->size() != size)
    {
        const int oldWidth = width_;
        const int oldHeight = height_;
        width_ = size.width();
        height_ = size.height();

        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
            const auto undoCmd = new UndoChangeObjectPropValue{this,
                "size", QPoint{width_, height_},
                QPoint{oldWidth, oldHeight}};
            undoStack_->push(undoCmd);
        }
    }
}

//==============================================================
// Начало перемещения
//==============================================================
void BaseNode::beginMove(const QPoint &topLeft)
{
    isMoving_ = true;
    movingBeginPos_ = topLeft;
}

//==============================================================
// Функция вызывается при перетаскивании
//==============================================================
void BaseNode::move(const QPoint &topLeft)
{
    if (!isMoving_)
    {
        return;
    }

    setUndo(true);
    setTopLeft(topLeft);
    setUndo(false);
}

//==============================================================
// Завершение перемещения
//==============================================================
void BaseNode::endMove(const QPoint &topLeft)
{
    // Формирование операции отмены
    Q_ASSERT(undoStack_ != nullptr);
    const QPoint oldPos = movingBeginPos_;
    const auto undoCmd = new UndoChangeObjectPropValue{this,
        "topLeft", topLeft, oldPos};
    undoStack_->push(undoCmd);

    isMoving_ = false;
    movingBeginPos_ = QPoint{};
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
// Задание признака выделения
//==============================================================
void BaseNode::setSelected(bool selected)
{
    if (isSelected_ != selected)
    {
        // const bool oldSelected = isSelected_;
        isSelected_ = selected;
        PropValue value{"selected", isSelected_};
        emit sigChangedProp(value);

        /* if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
            const auto undoCmd = new UndoChangeObjectPropValue{this,
                "selected", isSelected_, oldSelected};
            undoStack_->push(undoCmd);
        } */
    }
}

//==============================================================
// Сброс признака выделения
//==============================================================
void BaseNode::resetSelected()
{
    setSelected(false);
}

//==============================================================
// Получение области маркера изменения размера
//==============================================================
QRect BaseNode::resizebleMarkerRect() const
{
    if (!isResizeble())
    {
        return QRect{};
    }

    constexpr int size = resizebleMarkerSize_ + 2;

    return QRect{right() - size / 2, bottom() - size / 2, size, size};
}

//==============================================================
// Получение области с состоянием
//==============================================================
QRect BaseNode::stateAreaRect() const
{
    if (stateInfo().isSuccess())
    {
        return QRect{};
    }

    return QRect{right() - 8, top() - 8, 16, 16};
}

//==============================================================
// Рисование примитивной основы
//==============================================================
void BaseNode::drawSimpleBody(QPainter *painter) const
{
    Q_ASSERT(painter != nullptr);

    // Вывод основы
    QPen pen{currentBorderColor(), 2};
    pen.setJoinStyle(Qt::MiterJoin);
    painter->setPen(pen);
    painter->setBrush(Colors::nodeBack());
    painter->drawRect(rect());

    // Вывод типа
    painter->setPen(Colors::nodeText());
    painter->drawText(rect(), Qt::AlignCenter, strType());
}

//==============================================================
// Рисование входных пинов
//==============================================================
void BaseNode::drawInputPins(QPainter *painter) const
{
    Q_ASSERT(painter != nullptr);

    const QVector<ShPtrConstInputPin> pins = inputPins();
    for (const ShPtrConstInputPin &pin: pins)
    {
        drawPin(painter, pin);
    }
}

//==============================================================
// Рисование выходных пинов
//==============================================================
void BaseNode::drawOutputPins(QPainter *painter) const
{
    Q_ASSERT(painter != nullptr);

    const QVector<ShPtrConstOutputPin> pins = outputPins();
    for (const ShPtrConstOutputPin &pin: pins)
    {
        drawPin(painter, pin);
    }
}

//==============================================================
// Получение текущего цвета границы
//==============================================================
QColor BaseNode::currentBorderColor() const
{
    return !isSelected_ ? Colors::nodeBorder() : Colors::nodeSelectBorder();
}

//==============================================================
// Рисование пина
//==============================================================
void BaseNode::drawPin(QPainter *painter, const ShPtrConstBasePin &pin) const
{
    Q_ASSERT(painter != nullptr);
    Q_ASSERT(pin != nullptr);

    const QRect pinRect = pin->rect();
    QPen pen{currentBorderColor(), 2};
    pen.setJoinStyle(Qt::MiterJoin);
    painter->setPen(pen);
    painter->setBrush(Qt::white);
    painter->drawRect(pinRect);
}

//==============================================================
// Рисование состояния ошибки
//==============================================================
void BaseNode::drawErrorStateArea(QPainter *painter) const
{
    Q_ASSERT(painter != nullptr);

    painter->save();

    painter->setRenderHint(QPainter::Antialiasing);

    painter->setPen({Qt::black, 2.0});
    painter->setBrush(QColor{255, 107, 107});
    const int centerX = right();
    const int centerY = top();
    const int radius = 8;
    painter->drawEllipse(QPoint{centerX, centerY}, radius, radius);

    // Вывод восклицательного знака
    painter->setPen(Qt::black);
    QFont font = painter->font();
    font.setBold(true);
    painter->setFont(font);
    const QRect textRect{centerX - radius, centerY - radius, 2 * radius, 2 * radius};
    painter->drawText(textRect, Qt::AlignCenter, "!");

    painter->restore();
}

//==============================================================
// Рисование состояния предупреждения
//==============================================================
void BaseNode::drawWarningStateArea(QPainter *painter) const
{
    Q_ASSERT(painter != nullptr);

    painter->save();

    painter->setRenderHint(QPainter::Antialiasing);

    painter->setPen({Qt::black, 2.0});
    painter->setBrush(Qt::yellow);
    const int centerX = right();
    const int centerY = top();
    const int radius = 8;
    painter->drawEllipse(QPoint{centerX, centerY}, radius, radius);

    // Вывод восклицательного знака
    painter->setPen(Qt::black);
    QFont font = painter->font();
    font.setBold(true);
    painter->setFont(font);
    const QRect textRect{centerX - radius, centerY - radius, 2 * radius, 2 * radius};
    painter->drawText(textRect, Qt::AlignCenter, "!");

    painter->restore();
}

//==============================================================
// Чтение имени из XML
//==============================================================
QString BaseNode::readNameFromXml(const QDomElement &elem) const
{
    Q_ASSERT(!elem.isNull());

    const QString propName = "name";

    // Получение узла
    const QDomElement elemName = elem.firstChildElement(propName);
    if (elemName.isNull())
    {
        const QString msg = QString{"Not find property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения в виде строки
    const optional<QString> strName = readValueFromXml(elemName);
    if (!strName)
    {
        const QString msg = QString{"Not read property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения
    const optional<QString> name = strFromXmlFormat(strName.value());
    if (!name)
    {
        const QString msg = QString{"Bad value of property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    return name.value();
}

//==============================================================
// Чтение смещения слева из XML
//==============================================================
qint32 BaseNode::readLeftFromXml(const QDomElement &elem) const
{
    Q_ASSERT(!elem.isNull());

    const QString propName = "left";

    // Получение узла
    const QDomElement elemLeft = elem.firstChildElement(propName);
    if (elemLeft.isNull())
    {
        const QString msg = QString{"Not find property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения в виде строки
    const optional<QString> strLeft = readValueFromXml(elemLeft);
    if (!strLeft)
    {
        const QString msg = QString{"Not read property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения
    bool ok = false;
    const int left = strLeft.value().toInt(&ok);
    if (!ok)
    {
        const QString msg = QString{"Bad value of property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    return left;
}

//==============================================================
// Чтение смещения сверху из XML
//==============================================================
qint32 BaseNode::readTopFromXml(const QDomElement &elem) const
{
    Q_ASSERT(!elem.isNull());

    const QString propName = "top";

    // Получение узла
    const QDomElement elemTop = elem.firstChildElement(propName);
    if (elemTop.isNull())
    {
        const QString msg = QString{"Not find property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения в виде строки
    const optional<QString> strTop = readValueFromXml(elemTop);
    if (!strTop)
    {
        const QString msg = QString{"Not read property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения
    bool ok = false;
    const int top = strTop.value().toInt(&ok);
    if (!ok)
    {
        const QString msg = QString{"Bad value of property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    return top;
}

//==============================================================
// Чтение ширины из XML
//==============================================================
qint32 BaseNode::readWidthFromXml(const QDomElement &elem) const
{
    Q_ASSERT(!elem.isNull());

    const QString propName = "width";

    // Получение узла
    const QDomElement elemWidth = elem.firstChildElement(propName);
    if (elemWidth.isNull())
    {
        const QString msg = QString{"Not find property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения в виде строки
    const optional<QString> strWidth = readValueFromXml(elemWidth);
    if (!strWidth)
    {
        const QString msg = QString{"Not read property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения
    bool ok = false;
    const int width = strWidth.value().toInt(&ok);
    if (!ok)
    {
        const QString msg = QString{"Bad value of property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    return width;
}

//==============================================================
// Чтение высоты из XML
//==============================================================
qint32 BaseNode::readHeightFromXml(const QDomElement &elem) const
{
    Q_ASSERT(!elem.isNull());

    const QString propName = "height";

    // Получение узла
    const QDomElement elemHeight = elem.firstChildElement(propName);
    if (elemHeight.isNull())
    {
        const QString msg = QString{"Not find property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения в виде строки
    const optional<QString> strHeight = readValueFromXml(elemHeight);
    if (!strHeight)
    {
        const QString msg = QString{"Not read property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения
    bool ok = false;
    const int height = strHeight.value().toInt(&ok);
    if (!ok)
    {
        const QString msg = QString{"Bad value of property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    return height;
}

//==============================================================
// Чтение признака пропуска из XML
//==============================================================
bool BaseNode::readBypassFromXml(const QDomElement &elem) const
{
    Q_ASSERT(!elem.isNull());

    const QString propName = "bypass";

    // Получение узла
    const QDomElement elemBypass = elem.firstChildElement(propName);
    if (elemBypass.isNull())
    {
        const QString msg = QString{"Not find property \"%1\" of type %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения в виде строки
    const optional<QString> strBypass = readValueFromXml(elemBypass);
    if (!strBypass)
    {
        const QString msg = QString{"Not read property \"%1\" of type %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения
    const optional<bool> bypass = strToBool(strBypass.value());
    if (!bypass)
    {
        const QString msg = QString{"Bad value of property \"%1\" of type %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    return bypass.value();
}

//==============================================================
// Чтение комментария из XML
//==============================================================
QString BaseNode::readCommentFromXml(const QDomElement &elem) const
{
    const QString propName = "comment";

    // Получение узла
    const QDomElement elemComment = elem.firstChildElement(propName);
    if (elemComment.isNull())
    {
        const QString msg = QString{"Not find property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения в виде строки
    const optional<QString> xmlComment = readValueFromXml(elemComment);
    if (!xmlComment)
    {
        const QString msg = QString{"Not read property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения
    const optional<QString> comment = strFromXmlFormat(xmlComment.value());
    if (!comment)
    {
        const QString msg = QString{"Bad value of property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    return comment.value();
}

//==============================================================
// Запись имени в XML
//==============================================================
void BaseNode::writeNameToXml(QDomDocument &doc, QDomElement &elem) const
{
    Q_ASSERT(!doc.isNull());
    Q_ASSERT(!elem.isNull());

    QDomElement elemName = doc.createElement("name");
    const QString strName = strToXmlFormat(name());
    writeValueToXml(doc, elemName, strName);
    elem.appendChild(elemName);
}

//==============================================================
// Запись типа в XML
//==============================================================
void BaseNode::writeTypeToXml(QDomDocument &, QDomElement &elem) const
{
    elem.setAttribute("type", strType());
}

//==============================================================
// Запись идентификатора в XML
//==============================================================
void BaseNode::writeIdToXml(QDomDocument &, QDomElement &elem) const
{
    Q_ASSERT(!elem.isNull());

    elem.setAttribute("id", id());
}

//==============================================================
// Запись смещения слева в XML
//==============================================================
void BaseNode::writeLeftToXml(QDomDocument &doc, QDomElement &elem) const
{
    Q_ASSERT(!doc.isNull());
    Q_ASSERT(!elem.isNull());

    QDomElement elemLeft = doc.createElement("left");
    const QString strLeft = QString::number(left());
    writeValueToXml(doc, elemLeft, strLeft);
    elem.appendChild(elemLeft);
}

//==============================================================
// Запись смещения сверху в XML
//==============================================================
void BaseNode::writeTopToXml(QDomDocument &doc, QDomElement &elem) const
{
    Q_ASSERT(!doc.isNull());
    Q_ASSERT(!elem.isNull());

    QDomElement elemTop = doc.createElement("top");
    const QString strTop = QString::number(top());
    writeValueToXml(doc, elemTop, strTop);
    elem.appendChild(elemTop);
}

//==============================================================
// Запись ширины в XML
//==============================================================
void BaseNode::writeWidthToXml(QDomDocument &doc, QDomElement &elem) const
{
    Q_ASSERT(!doc.isNull());
    Q_ASSERT(!elem.isNull());

    QDomElement elemTop = doc.createElement("width");
    const QString strTop = QString::number(width());
    writeValueToXml(doc, elemTop, strTop);
    elem.appendChild(elemTop);
}

//==============================================================
// Запись высоты в XML
//==============================================================
void BaseNode::writeHeightToXml(QDomDocument &doc, QDomElement &elem) const
{
    Q_ASSERT(!doc.isNull());
    Q_ASSERT(!elem.isNull());

    QDomElement elemTop = doc.createElement("height");
    const QString strTop = QString::number(height());
    writeValueToXml(doc, elemTop, strTop);
    elem.appendChild(elemTop);
}

//==============================================================
// Запись признака пропуска в XML
//==============================================================
void BaseNode::writeBypassToXml(QDomDocument &doc, QDomElement &elem) const
{
    Q_ASSERT(!doc.isNull());
    Q_ASSERT(!elem.isNull());

    QDomElement elemBypass = doc.createElement("bypass");
    const QString strBypass = boolToStr(isBypass_);
    writeValueToXml(doc, elemBypass, strBypass);
    elem.appendChild(elemBypass);
}

//==============================================================
// Запись комментария в XML
//==============================================================
void BaseNode::writeCommentToXml(QDomDocument &doc, QDomElement &elem) const
{
    Q_ASSERT(!doc.isNull());
    Q_ASSERT(!elem.isNull());

    QDomElement elemLeft = doc.createElement("comment");
    const QString xmlComment = strToXmlFormat(comment_);
    writeValueToXml(doc, elemLeft, xmlComment);
    elem.appendChild(elemLeft);
}

////////////////////////////////////////////////////////////////
// Реализация функций
////////////////////////////////////////////////////////////////
