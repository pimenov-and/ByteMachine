////////////////////////////////////////////////////////////////
// ByteMachine
// Узел для показа размера данных
////////////////////////////////////////////////////////////////
#include "size_node.h"
#include "xml_helper.h"
#include "qt_helper.h"
#include "colors.h"
#include "node_name_manager.h"
#include "undo_change_object_prop_value.h"
#include <QPainter>
#include <QMap>
#include <QDomDocument>
#include <QUndoStack>
// #include <QDebug>

//==============================================================
// Конструктор с параметром
//==============================================================
SizeNode::SizeNode(QUndoStack *undoStack, QObject *parent) :
    BaseNode{undoStack, parent}
{
    name_ = nodeNameManager()->addName("size");
    Q_ASSERT(!name_.isEmpty());

    createInputPin();
    createOutputPin();
}

//==============================================================
// Деструктор
//==============================================================
SizeNode::~SizeNode()
{
}

//==============================================================
// Чтение из XML
//==============================================================
void SizeNode::readFromXml(const QDomElement &elem)
{
    Q_ASSERT(!elem.isNull());

    const QString name = readNameFromXml(elem);
    const qint32 left = readLeftFromXml(elem);
    const qint32 top = readTopFromXml(elem);
    const qint32 width = readWidthFromXml(elem);
    // const qint32 height = readHeightFromXml(elem);
    const SizeUnits unit = readUnitFromXml(elem);
    const bool isBypass = readBypassFromXml(elem);
    const QString comment = readCommentFromXml(elem);

    setName(name);
    setLeft(left);
    setTop(top);
    setWidth(width);
    // setHeight(height);
    setUnit(unit);
    setBypass(isBypass);
    setComment(comment);
}

//==============================================================
// Запись в XML
//==============================================================
void SizeNode::writeToXml(QDomDocument &doc, QDomElement &elem) const
{
    Q_ASSERT(!doc.isNull());
    Q_ASSERT(!elem.isNull());

    writeIdToXml(doc, elem);
    writeNameToXml(doc, elem);
    writeLeftToXml(doc, elem);
    writeTopToXml(doc, elem);
    writeWidthToXml(doc, elem);
    writeHeightToXml(doc, elem);
    writeUnitToXml(doc, elem);
    writeBypassToXml(doc, elem);
    writeCommentToXml(doc, elem);
}

//==============================================================
// Получение входных пинов
//==============================================================
QVector<ShPtrInputPin> SizeNode::inputPins()
{
    return QVector<ShPtrInputPin>{inputPin_};
}

//==============================================================
// Получение входных пинов (2 вариант)
//==============================================================
QVector<ShPtrConstInputPin> SizeNode::inputPins() const
{
    return QVector<ShPtrConstInputPin>{inputPin_};
}

//==============================================================
// Получение выходных пинов
//==============================================================
QVector<ShPtrOutputPin> SizeNode::outputPins()
{
    return QVector<ShPtrOutputPin>{outputPin_};
}

//==============================================================
// Получение выходных пинов (константный вариант)
//==============================================================
QVector<ShPtrConstOutputPin> SizeNode::outputPins() const
{
    return QVector<ShPtrConstOutputPin>{outputPin_};
}

//==============================================================
// Функция вывода
//==============================================================
void SizeNode::draw(QPainter *painter) const
{
    Q_ASSERT(painter != nullptr);

    drawBody(painter);
    drawInputPins(painter);
    drawOutputPins(painter);
    // drawResizebleMarker(painter);
    drawComments(painter);
}

//==============================================================
// Получение копии узла
//==============================================================
ShPtrBaseNode SizeNode::clone() const
{
    const auto cloneNode = ShPtrSizeNode::create(undoStack());
    cloneNode->setUndo(true);
    cloneNode->setLeft(left());
    cloneNode->setTop(top());
    cloneNode->setWidth(width());
    // cloneNode->setHeight(height());
    cloneNode->setUnit(unit());
    cloneNode->setBypass(isBypass());
    cloneNode->setComment(comment());
    cloneNode->setUndo(false);

    return cloneNode;
}

//==============================================================
// Получение текста подсказки
//==============================================================
QString SizeNode::tooltipText() const
{
    return QString{};
}

//==============================================================
// Получение размера данных
//==============================================================
qint32 SizeNode::dataSize() const
{
    if (stateInfo_.isError())
    {
        return 0;
    }

    return inputDataSize();
}

//==============================================================
// Получение байта данных
//==============================================================
quint8 SizeNode::dataByte(qint32 index) const
{
    Q_UNUSED(index);

    return 0;
}

//==============================================================
// Получение блока данных
//==============================================================
QVector<quint8> SizeNode::dataBlock(qint32 index, qint32 count) const
{
    Q_UNUSED(index);
    Q_UNUSED(count);

    return QVector<quint8>{};
}

//==============================================================
// Функция вызывается при изменении данных
//==============================================================
void SizeNode::dataChanged()
{
    updateStateInfo();

    outputPin_->dataChanged();
}

//==============================================================
// Задание размерности
//==============================================================
void SizeNode::setUnit(SizeUnits unit)
{
    if (unit_ != unit)
    {
        const SizeUnits oldUnit = unit_;
        unit_ = unit;
        const PropValue value{"unit", QVariant::fromValue(unit)};
        emit sigChangedProp(value);

        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
            const auto undoCmd = new UndoChangeObjectPropValue{this, "unit",
                QVariant::fromValue(unit_), QVariant::fromValue(oldUnit)};
            undoStack_->push(undoCmd);
        }
    }
}

//==============================================================
// Сброс размерности
//==============================================================
void SizeNode::resetUnit()
{
    setUnit(SizeUnits::Byte);
}

//==============================================================
// Задание признака пропуска
//==============================================================
void SizeNode::setBypass(bool bypass)
{
    if (isBypass_ != bypass)
    {
        const bool oldBypass = isBypass_;
        isBypass_ = bypass;
        const PropValue value{"bypass", QVariant::fromValue(isBypass_)};
        emit sigChangedProp(value);

        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
            const auto undoCmd = new UndoChangeObjectPropValue{this,
                "bypass", isBypass_, oldBypass};
            undoStack_->push(undoCmd);
        }
    }
}

//==============================================================
// Сброс признака пропуска
//==============================================================
void SizeNode::resetBypass()
{
    setBypass(false);
}

//==============================================================
// Задание признака кеширования
//==============================================================
void SizeNode::setCaching(bool caching)
{
    if (isCaching_ != caching)
    {
        const bool oldCaching = caching;
        isCaching_ = caching;
        const PropValue value{"caching", isCaching_};
        emit sigChangedProp(value);

        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
            const auto undoCmd = new UndoChangeObjectPropValue{this,
                "caching", isCaching_, oldCaching};
            undoStack_->push(undoCmd);
        }
    }
}

//==============================================================
// Сброс признака кеширования
//==============================================================
void SizeNode::resetCaching()
{
    setCaching(false);
}

//==============================================================
// Виртуальная функция получения имени свойства из графического
// интерфейса по его системному имени
//==============================================================
QString SizeNode::getUiPropertyName(const QString &systemName)
{
    const QMap<QString, QString> map
    {
        {"name", "Name"},
        {"left", "Left"},
        {"top", "Top"},
        {"width", "Width"},
        {"height", "Height"},
        {"topLeft", "Top and left"},
        {"size", "Size"},
        {"comment", "Comment"},
        {"unit", "Unit"},
        {"bypass", "Bypass"},
        {"caching", "Caching"}
    };

    return map.value(systemName, "Unknown property");
}

//==============================================================
// Вывод основы
//==============================================================
void SizeNode::drawBody(QPainter *painter) const
{
    Q_ASSERT(painter != nullptr);

    // Вывод основы
    QPen borderPen{currentBorderColor(), 2};
    borderPen.setJoinStyle(Qt::MiterJoin);
    painter->setPen(borderPen);
    painter->setBrush(Colors::nodeBack());
    painter->drawRect(rect());

    // Линия, разделяющая заголовок и данные
    painter->setPen(currentBorderColor());
    painter->drawLine(left() + 1, top() + headerHeight(), right() - 2, top() + headerHeight());

    // Вывод названия
    painter->setPen(Colors::nodeText());
    painter->drawText(left(), top(), width(), headerHeight(), Qt::AlignCenter, strType());

    // Вывод размера данных
    if (!stateInfo().isError())
    {
        const QString text = dataSizeToStr();
        painter->drawText(left(), top() + headerHeight(), width(),
            height() - headerHeight(), Qt::AlignCenter, text);
    }
    else
    {
        const QString strState = nodeStateToStr(stateInfo().state());
        painter->drawText(left(), top() + headerHeight(), width(),
            height() - headerHeight(), Qt::AlignCenter, strState);
    }
}

//==============================================================
// Вывод комментариев
//==============================================================
void SizeNode::drawComments(QPainter *painter) const
{
    Q_ASSERT(painter != nullptr);

    if (isCommentsVisible())
    {
        QString comments{};
        comments += QString{" <<< %1: \"%2\"\n"}.arg(tr("Name"), name());
        comments += QString{"     %1: %2\n"}.arg(tr("Unit"), sizeUnitToStr(unit_));
        comments += QString{"     %1: %2\n"}.arg(tr("Bypass"), boolToStr(isBypass_));
        comments += QString{"     %1: %2\n"}.arg(tr("Caching"), boolToStr(isCaching_));
        comments += QString{"     %1: \"%2\"\n"}.arg(tr("Comment"), comment());
#ifdef QT_DEBUG
        comments += "     -\n";
        comments += QString{"     %1: %2\n"}.arg("Id").arg(id());
#endif // QT_DEBUG

        const int commentsLeft = right();
        const int commentsTop = top() + (headerHeight() - charHeight()) / 2;
        const int commentsFlags = Qt::AlignLeft | Qt::AlignTop | Qt::TextDontClip;
        const QRect commentsRect{commentsLeft, commentsTop, 0, 0};
        painter->setPen(Colors::nodeText());
        painter->drawText(commentsRect, commentsFlags, comments);
    }
}

//==============================================================
// Перевод байтов в килобайты
//==============================================================
double SizeNode::bytesToKilobytes(int count)
{
    return count / 1024.0;
}

//==============================================================
// Перевод байтов в мегабайты
//==============================================================
double SizeNode::bytesToMegabytes(int count)
{
    return count / 1024.0 / 1024;
}

//==============================================================
// Получение размера данных в виде строки
//==============================================================
QString SizeNode::dataSizeToStr() const
{
    switch (unit_)
    {
        case SizeUnits::Byte:
        {
            return QString::number(dataSize()) + " B";
        }
        case SizeUnits::Kilobyte:
        {
            return QString::number(bytesToKilobytes(dataSize()), 'f', 3) + " KB";
        }
        case SizeUnits::Megabyte:
        {
            return QString::number(bytesToMegabytes(dataSize()), 'f', 3) + " MB";
        }
        default:
        {
            return QString{};
        }
    }
}

//==============================================================
// Создание входного пина
//==============================================================
void SizeNode::createInputPin()
{
    inputPin_ = ShPtrInputPin::create(this, 0);
}

//==============================================================
// Создание выходного пина
//==============================================================
void SizeNode::createOutputPin()
{
    outputPin_ = ShPtrOutputPin::create(this, 0);
}

//==============================================================
// Получение признака подключения входного пина
//==============================================================
bool SizeNode::isConnectedInputPin() const
{
    return inputPin_->isConnected();
}

//==============================================================
// Получение размера входные данных
//==============================================================
int SizeNode::inputDataSize() const
{
    return isConnectedInputPin() ? inputPin_->dataSize() : 0;
}

//==============================================================
// Чтение единицы измерения из XML
//==============================================================
SizeUnits SizeNode::readUnitFromXml(const QDomElement &elem) const
{
    Q_ASSERT(!elem.isNull());

    return SizeUnits::Byte;
}

//==============================================================
// Запись единицы измерения в XML
//==============================================================
void SizeNode::writeUnitToXml(QDomDocument &doc, QDomElement &elem) const
{
    Q_ASSERT(!doc.isNull());
    Q_ASSERT(!elem.isNull());

    QDomElement elemUnit = doc.createElement("unit");
    const QString strUnit = sizeUnitToStr(unit_);
    writeValueToXml(doc, elemUnit, strUnit);
    elem.appendChild(elemUnit);
}

//==============================================================
// Обновление состояния узла
//==============================================================
void SizeNode::updateStateInfo()
{
    const NodeStateInfo oldStateInfo = stateInfo_;

    if (!isConnectedInputPin())
    {
        const QString msg = "No connection to input pin";
        stateInfo_ = NodeStateInfo{NodeStates::Error, msg};
    }
    else if (inputDataSize() == 0)
    {
        const QString msg = "Not data";
        stateInfo_ = NodeStateInfo{NodeStates::Warning, msg};
    }
    else
    {
        stateInfo_ = NodeStateInfo{NodeStates::Success, QString{}};
    }

    if (stateInfo_ != oldStateInfo)
    {
        emit sigChangedState(stateInfo_);
    }
}
