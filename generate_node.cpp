////////////////////////////////////////////////////////////////
// ByteMachine
// Узел "Generate"
////////////////////////////////////////////////////////////////
#include "generate_node.h"
#include "node_name_manager.h"
#include "undo_change_object_prop_value.h"
#include "qt_helper.h"
#include "xml_helper.h"
#include "byte_convert.h"
#include "base_exception.h"
#include "colors.h"
#include <QPainter>
#include <QDomDocument>
#include <QDebug>

//==============================================================
using std::optional;

//==============================================================
using UsualData = QPair<int, quint8>;

//==============================================================
// Конструктор с параметром
//==============================================================
GenerateNode::GenerateNode(QUndoStack *undoStack, QObject *parent) :
    BaseNode{undoStack, parent}
{
    name_ = nodeNameManager()->addName("generate");
    Q_ASSERT(!name_.isEmpty());

    createOutputPin();
}

//==============================================================
// Деструктор
//==============================================================
GenerateNode::~GenerateNode()
{
}

//==============================================================
// Чтение из XML
//==============================================================
void GenerateNode::readFromXml(const QDomElement &elem)
{
    Q_ASSERT(!elem.isNull());

    const QString name = readNameFromXml(elem);
    const int left = readLeftFromXml(elem);
    const int top = readTopFromXml(elem);
    const int width = readWidthFromXml(elem);
    const int height = readHeightFromXml(elem);
    const GenerateTypes generateType = readGenerateTypeFromXml(elem);
    const QVariant value = readValueFromXml(elem);
    const QString comment = readCommentFromXml(elem);

    setName(name);
    setLeft(left);
    setTop(top);
    Q_UNUSED(width);
    Q_UNUSED(height);
    setGenerateType(generateType);
    Q_UNUSED(value);
    setComment(comment);
}

//==============================================================
// Запись в XML
//==============================================================
void GenerateNode::writeToXml(QDomDocument &doc, QDomElement &elem) const
{
    Q_ASSERT(!doc.isNull());
    Q_ASSERT(!elem.isNull());

    writeIdToXml(doc, elem);
    writeNameToXml(doc, elem);
    writeLeftToXml(doc, elem);
    writeTopToXml(doc, elem);
    writeWidthToXml(doc, elem);
    writeHeightToXml(doc, elem);
    writeGenerateTypeToXml(doc, elem);
    writeValueToXml(doc, elem);
    writeCommentToXml(doc, elem);
}

//==============================================================
// Функция вывода
//==============================================================
void GenerateNode::draw(QPainter *painter) const
{
    Q_ASSERT(painter != nullptr);

    drawSimpleBody(painter);
    drawOutputPins(painter);
    drawComments(painter);
}

//==============================================================
// Получение копии узла
//==============================================================
QSharedPointer<BaseNode> GenerateNode::clone() const
{
    const auto cloneNode = ShPtrGenerateNode::create(undoStack());
    cloneNode->setUndo(true);
    cloneNode->setName(name());
    cloneNode->setTopLeft(topLeft());
    cloneNode->setGenerateType(generateType());
    cloneNode->setByteCount(byteCount());
    cloneNode->setFilledByte(filledByte());
    cloneNode->setBoolValue(boolValue());
    cloneNode->setInt8Value(int8Value());
    cloneNode->setUInt8Value(uint8Value());
    cloneNode->setInt16Value(int16Value());
    cloneNode->setUInt16Value(uint16Value());
    cloneNode->setInt32Value(int32Value());
    cloneNode->setUInt32Value(uint32Value());
    cloneNode->setInt64Value(int64Value());
    cloneNode->setUInt64Value(uint64Value());
    cloneNode->setFloatValue(floatValue());
    cloneNode->setDoubleValue(doubleValue());
    cloneNode->setStrValue(strValue());
    cloneNode->setColorValue(colorValue());
    cloneNode->setComment(comment());
    cloneNode->setUndo(false);

    return cloneNode;
}

//==============================================================
// Получение текста подсказки
//==============================================================
QString GenerateNode::tooltipText() const
{
    QString text{};
    text += QString{"%1: \"%2\"\n"}.arg("Name", name());
    text += QString{"%1: %2\n"}.arg("Generate type", generateTypeToStr(generateType()));
    text += QString{"%1: %2\n"}.arg("Byte count").arg(byteCount());
    text += valueStrForTooltip();
    text += QString{"%1: \"%2\""}.arg("Comment", comment());

    return text;
}

//==============================================================
// Получение размера данных
//==============================================================
qint32 GenerateNode::dataSize() const
{
    if (stateInfo_.isError())
    {
        return 0;
    }

    return byteCountForGenerateType();
}

//==============================================================
// Получение байта данных
//==============================================================
quint8 GenerateNode::dataByte(qint32 index) const
{
    Q_ASSERT_X((index >= 0) && (index < dataSize()), "Check index",
               qPrintable(QString{"Index: %1, DataSize: %2"}.arg(index).arg(dataSize())));

    switch (generateType_)
    {
        case GenerateTypes::Usual:
        {
            return filledByte_;
        }
        case GenerateTypes::Random:
        {
            return randValue(index);
        }
        case GenerateTypes::Bool:
        {
            return static_cast<quint8>(boolValue_);
        }
        case GenerateTypes::Int8:
        {
            return static_cast<quint8>(int8Value_);
        }
        case GenerateTypes::UInt8:
        {
            return uint8Value_;
        }
        case GenerateTypes::Int16:
        {
            return valueToByteList(int16Value_).at(index);
        }
        case GenerateTypes::UInt16:
        {
            return valueToByteList(uint16Value_).at(index);
        }
        case GenerateTypes::Int32:
        {
            return valueToByteList(int32Value_).at(index);
        }
        case GenerateTypes::UInt32:
        {
            return valueToByteList(uint32Value_).at(index);
        }
        case GenerateTypes::Int64:
        {
            return valueToByteList(int64Value_).at(index);
        }
        case GenerateTypes::UInt64:
        {
            return valueToByteList(uint64Value_).at(index);
        }
        case GenerateTypes::Float:
        {
            return valueToByteList(floatValue_).at(index);
        }
        case GenerateTypes::Double:
        {
            return valueToByteList(doubleValue_).at(index);
        }
        case GenerateTypes::String:
        {
            return valueToByteList(strValue_).at(index);
        }
        case GenerateTypes::Color:
        {
            return valueToByteList(colorValue_).at(index);
        }
        default:
        {
            return 0;
        }
    }
}

//==============================================================
// Получение блока данных
//==============================================================
QVector<quint8> GenerateNode::dataBlock(qint32 index, qint32 count) const
{
    Q_ASSERT_X(index >= 0, "Check index", qPrintable(QString::number(index)));
    Q_ASSERT_X(count >= 0, "Check count", qPrintable(QString::number(count)));
    Q_ASSERT_X(static_cast<qint64>(index) + count <= dataSize(), "Check index and count",
        qPrintable(QString{"Index: %1, Count: %2, DataSize: %3"}.arg(index).arg(count).arg(dataSize())));

    switch (generateType_)
    {
        case GenerateTypes::Usual:
        {
            return QVector<quint8>(count, filledByte_);
        }
        case GenerateTypes::Random:
        {
            QVector<quint8> block{};
            for (qint32 i = index, j = 0; j < count; ++i, ++j)
            {
                block << randValue(i);
            }
            return block;
        }
        case GenerateTypes::Bool:
        {
            const QVector<quint8> bl = valueToByteList(boolValue_);
            return bl.mid(index, count);
        }
        case GenerateTypes::Int8:
        {
            const QVector<quint8> bl = valueToByteList(int8Value_);
            return bl.mid(index, count);
        }
        case GenerateTypes::UInt8:
        {
            const QVector<quint8> bl = valueToByteList(uint8Value_);
            return bl.mid(index, count);
        }
        case GenerateTypes::Int16:
        {
            const QVector<quint8> bl = valueToByteList(int16Value_);
            return bl.mid(index, count);
        }
        case GenerateTypes::UInt16:
        {
            const QVector<quint8> bl = valueToByteList(uint16Value_);
            return bl.mid(index, count);
        }
        case GenerateTypes::Int32:
        {
            const QVector<quint8> bl = valueToByteList(int32Value_);
            return bl.mid(index, count);
        }
        case GenerateTypes::UInt32:
        {
            const QVector<quint8> bl = valueToByteList(uint32Value_);
            return bl.mid(index, count);
        }
        case GenerateTypes::Int64:
        {
            const QVector<quint8> bl = valueToByteList(int64Value_);
            return bl.mid(index, count);
        }
        case GenerateTypes::UInt64:
        {
            const QVector<quint8> bl = valueToByteList(uint64Value_);
            return bl.mid(index, count);
        }
        case GenerateTypes::Float:
        {
            const QVector<quint8> bl = valueToByteList(floatValue_);
            return bl.mid(index, count);
        }
        case GenerateTypes::Double:
        {
            const QVector<quint8> bl = valueToByteList(doubleValue_);
            return bl.mid(index, count);
        }
        case GenerateTypes::String:
        {
            const QVector<quint8> bl = valueToByteList(strValue_);
            return bl.mid(index, count);
        }
        case GenerateTypes::Color:
        {
            const QVector<quint8> bl = valueToByteList(colorValue_);
            return bl.mid(index, count);
        }
        default:
        {
            return QVector<quint8>{};
        }
    }
}

//==============================================================
// Функция вызывается при изменении данных
//==============================================================
void GenerateNode::dataChanged()
{
    // updateStateInfo();

    outputPin_->dataChanged();
}

//==============================================================
// Получение выходных пинов
//==============================================================
QVector<ShPtrOutputPin> GenerateNode::outputPins()
{
    return QVector<ShPtrOutputPin>{outputPin_};
}

//==============================================================
// Получение выходных пинов (константный вариант)
//==============================================================
QVector<ShPtrConstOutputPin> GenerateNode::outputPins() const
{
    return QVector<ShPtrConstOutputPin>{outputPin_};
}

//==============================================================
// Задание типа генерации
//==============================================================
void GenerateNode::setGenerateType(GenerateTypes type)
{
    Q_ASSERT(!isUnknown(type));

    if (generateType_ != type)
    {
        GenerateTypes oldGenerateType = generateType_;
        generateType_ = type;
        const PropValue value{"generateType", QVariant::fromValue(generateType_)};
        emit sigChangedProp(value);

        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
            const auto undoCmd = new UndoChangeObjectPropValue{this,
                "generateType", QVariant::fromValue(generateType_),
                QVariant::fromValue(oldGenerateType)};
            undoStack_->push(undoCmd);
        }
    }
}

//==============================================================
// Сброс типа генерации
//==============================================================
void GenerateNode::resetGenerateType()
{
    setGenerateType(GenerateTypes::Usual);
}

//==============================================================
// Задание количества байтов
//==============================================================
void GenerateNode::setByteCount(qint32 count)
{
    Q_ASSERT_X(count >= 0, "Check byte count",
        qPrintable(QString::number(count)));

    if (byteCount_ != count)
    {
        const qint32 oldByteCount = byteCount_;
        byteCount_ = count;
        const PropValue value{"byteCount", byteCount_};
        emit sigChangedProp(value);

        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
            const auto undoCmd = new UndoChangeObjectPropValue{this,
                "byteCount", byteCount_, oldByteCount};
            undoStack_->push(undoCmd);
        }
    }
}

//==============================================================
// Сброс количества байтов
//==============================================================
void GenerateNode::resetByteCount()
{
    setByteCount(0);
}

//==============================================================
// Задание байта для заполнения
//==============================================================
void GenerateNode::setFilledByte(quint8 byte)
{
    if (filledByte_ != byte)
    {
        const quint8 oldFilledByte = byte;
        filledByte_ = byte;
        const PropValue value{"filledByte", filledByte_};
        emit sigChangedProp(value);

        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
            const auto undoCmd = new UndoChangeObjectPropValue{this,
                "filledByte", filledByte_, oldFilledByte};
            undoStack_->push(undoCmd);
        }
    }
}

//==============================================================
// Сброс байта для заполнения
//==============================================================
void GenerateNode::resetFilledByte()
{
    setFilledByte(0);
}

//==============================================================
// Задание значения типа Bool
//==============================================================
void GenerateNode::setBoolValue(bool value)
{
    if (boolValue_ != value)
    {
        const bool oldBoolValue = boolValue_;
        boolValue_ = value;
        const PropValue value{"boolValue", boolValue_};
        emit sigChangedProp(value);

        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
            const auto undoCmd = new UndoChangeObjectPropValue{this,
                "boolValue", boolValue_, oldBoolValue};
            undoStack_->push(undoCmd);
        }
    }
}

//==============================================================
// Сброс значения типа Bool
//==============================================================
void GenerateNode::resetBoolValue()
{
    setBoolValue(false);
}

//==============================================================
// Задание значения типа Int8
//==============================================================
void GenerateNode::setInt8Value(qint8 value)
{
    if (int8Value_ != value)
    {
        const qint8 oldInt8Value = int8Value_;
        int8Value_ = value;
        const PropValue value{"int8Value", int8Value_};
        emit sigChangedProp(value);

        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
            const auto undoCmd = new UndoChangeObjectPropValue{this,
                "int8Value", int8Value_, oldInt8Value};
            undoStack_->push(undoCmd);
        }
    }
}

//==============================================================
// Сброс значения типа Int8
//==============================================================
void GenerateNode::resetInt8Value()
{
    setInt8Value(0);
}

//==============================================================
// Задание значения типа UInt8
//==============================================================
void GenerateNode::setUInt8Value(quint8 value)
{
    if (uint8Value_ != value)
    {
        const qint8 oldUInt8Value = uint8Value_;
        uint8Value_ = value;
        const PropValue value{"uint8Value", uint8Value_};
        emit sigChangedProp(value);

        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
            const auto undoCmd = new UndoChangeObjectPropValue{this,
                "uint8Value", uint8Value_, oldUInt8Value};
            undoStack_->push(undoCmd);
        }
    }
}

//==============================================================
// Сброс значения типа UInt8
//==============================================================
void GenerateNode::resetUInt8Value()
{
    setUInt8Value(0);
}

//==============================================================
// Задание значения типа Int16
//==============================================================
void GenerateNode::setInt16Value(qint16 value)
{
    if (int16Value_ != value)
    {
        const qint16 oldInt16Value = int16Value_;
        int16Value_ = value;
        const PropValue value{"int16Value", int16Value_};
        emit sigChangedProp(value);

        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
            const auto undoCmd = new UndoChangeObjectPropValue{this,
                "uint8Value", int16Value_, oldInt16Value};
            undoStack_->push(undoCmd);
        }
    }
}

//==============================================================
// Сброс значения типа Int16
//==============================================================
void GenerateNode::resetInt16Value()
{
    setInt16Value(0);
}

//==============================================================
// Задание значения типа quint16
//==============================================================
void GenerateNode::setUInt16Value(quint16 value)
{
    if (uint16Value_ != value)
    {
        const quint16 oldUInt16Value = uint16Value_;
        uint16Value_ = value;
        const PropValue value{"uint16Value", uint16Value_};
        emit sigChangedProp(value);

        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
            const auto undoCmd = new UndoChangeObjectPropValue{this,
                "uint8Value", uint16Value_, oldUInt16Value};
            undoStack_->push(undoCmd);
        }
    }
}

//==============================================================
// Сброс значения типа quint16
//==============================================================
void GenerateNode::resetUInt16Value()
{
    setUInt16Value(0);
}

//==============================================================
// Задание значения типа qint32
//==============================================================
void GenerateNode::setInt32Value(qint32 value)
{
    if (int32Value_ != value)
    {
        const qint32 oldInt32Value = int32Value_;
        int32Value_ = value;
        const PropValue value{"int32Value", int32Value_};
        emit sigChangedProp(value);

        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
            const auto undoCmd = new UndoChangeObjectPropValue{this,
                "int32Value", int32Value_, oldInt32Value};
            undoStack_->push(undoCmd);
        }
    }
}

//==============================================================
// Сброс значения типа Int32
//==============================================================
void GenerateNode::resetInt32Value()
{
    setInt32Value(0);
}

//==============================================================
// Задание значения типа UInt32
//==============================================================
void GenerateNode::setUInt32Value(quint32 value)
{
    if (uint32Value_ != value)
    {
        const quint32 oldUInt32Value = uint32Value_;
        uint32Value_ = value;
        const PropValue value{"uint32Value", uint32Value_};
        emit sigChangedProp(value);

        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
            const auto undoCmd = new UndoChangeObjectPropValue{this,
                "uint32Value", uint32Value_, oldUInt32Value};
            undoStack_->push(undoCmd);
        }
    }
}

//==============================================================
// Сброс значения типа UInt32
//==============================================================
void GenerateNode::resetUInt32Value()
{
    setUInt32Value(0);
}

//==============================================================
// Задание значения типа Int64
//==============================================================
void GenerateNode::setInt64Value(const qint64 &value)
{
    if (int64Value_ != value)
    {
        const qint64 oldInt64Value = int64Value_;
        int64Value_ = value;
        const PropValue value{"int64Value", int64Value_};
        emit sigChangedProp(value);

        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
            const auto undoCmd = new UndoChangeObjectPropValue{this,
                "int64Value", int64Value_, oldInt64Value};
            undoStack_->push(undoCmd);
        }
    }
}

//==============================================================
// Сброс признака значения типа Int64
//==============================================================
void GenerateNode::resetInt64Value()
{
    setInt64Value(0);
}

//==============================================================
// Задание значения типа UInt64
//==============================================================
void GenerateNode::setUInt64Value(const quint64 &value)
{
    if (uint64Value_ != value)
    {
        const quint64 oldUInt64Value = uint64Value_;
        uint64Value_ = value;
        const PropValue value{"uint64Value", uint64Value_};
        emit sigChangedProp(value);

        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
            const auto undoCmd = new UndoChangeObjectPropValue{this,
                "uint64Value", uint64Value_, oldUInt64Value};
            undoStack_->push(undoCmd);
        }
    }
}

//==============================================================
// Сброс значения типа UInt64
//==============================================================
void GenerateNode::resetUInt64Value()
{
    setUInt64Value(0);
}

//==============================================================
// Задание значения типа Float
//==============================================================
void GenerateNode::setFloatValue(float value)
{
    if (!qFuzzyCompare(floatValue_, value))
    {
        const float oldFloatValue = floatValue_;
        floatValue_ = value;
        const PropValue value{"floatValue", floatValue_};
        emit sigChangedProp(value);

        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
            const auto undoCmd = new UndoChangeObjectPropValue{this,
                "floatValue", floatValue_, oldFloatValue};
            undoStack_->push(undoCmd);
        }
    }
}

//==============================================================
// Сброс значения типа Float
//==============================================================
void GenerateNode::resetFloatValue()
{
    setFloatValue(0);
}

//==============================================================
// Задание значения типа Double
//==============================================================
void GenerateNode::setDoubleValue(const double &value)
{
    if (!qFuzzyCompare(doubleValue_, value))
    {
        const float oldDoubleValue = floatValue_;
        doubleValue_ = value;
        const PropValue value{"doubleValue", doubleValue_};
        emit sigChangedProp(value);

        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
            const auto undoCmd = new UndoChangeObjectPropValue{this,
                "doubleValue", doubleValue_, oldDoubleValue};
            undoStack_->push(undoCmd);
        }
    }
}

//==============================================================
// Сброс значения типа double
//==============================================================
void GenerateNode::resetDoubleValue()
{
    setDoubleValue(0);
}

//==============================================================
// Задание значения типа String
//==============================================================
void GenerateNode::setStrValue(const QString &value)
{
    if (strValue_ != value)
    {
        const QString oldStrValue = strValue_;
        strValue_ = value;
        const PropValue value{"strValue", strValue_};
        emit sigChangedProp(value);

        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
            const auto undoCmd = new UndoChangeObjectPropValue{this,
                "strValue", strValue_, oldStrValue};
            undoStack_->push(undoCmd);
        }
    }
}

//==============================================================
// Сброс значения типа String
//==============================================================
void GenerateNode::resetStrValue()
{
    setStrValue(QString{});
}

//==============================================================
// Задание значения типа Color
//==============================================================
void GenerateNode::setColorValue(const QColor &value)
{
    if (colorValue_ != value)
    {
        const QColor oldColorValue = colorValue_;
        colorValue_ = value;
        const PropValue value{"colorValue", colorValue_};
        emit sigChangedProp(value);

        if (!isUndo_)
        {
            Q_ASSERT(undoStack_ != nullptr);
            const auto undoCmd = new UndoChangeObjectPropValue{this,
                "colorValue", colorValue_, oldColorValue};
            undoStack_->push(undoCmd);
        }
    }
}

//==============================================================
// Сброс значения типа Color
//==============================================================
void GenerateNode::resetColorValue()
{
    setColorValue(Qt::black);
}

//==============================================================
// Виртуальная функция получения имени свойства из графического
// интерфейса по его системному имени
//==============================================================
QString GenerateNode::getUiPropertyName(const QString &systemName)
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
        {"generateType", "Generate type"},
        {"byteCount", "Сount (B)"},
        {"filledByte", "Filled byte"},
        {"boolValue", "Value"},
        {"int8Value", "Value"},
        {"uint8Value", "Value"},
        {"int16Value", "Value"},
        {"uint16Value", "Value"},
        {"int32Value", "Value"},
        {"uint32Value", "Value"},
        {"int64Value", "Value"},
        {"uint64Value", "Value"},
        {"floatValue", "Value"},
        {"doubleValue", "Value"},
        {"strValue", "Value"},
        {"colorValue", "Value"}
    };

    return map.value(systemName, "Unknown property");
}

//==============================================================
// Функция вызывается при подключении выходного пина
//==============================================================
void GenerateNode::slotOutputPinConnectChanged(ConnectStates state,
    InputPin *pin)
{
    Q_ASSERT(!isUnknown(state));
    Q_ASSERT(pin != nullptr);
}

//==============================================================
// Создание выходного пина
//==============================================================
void GenerateNode::createOutputPin()
{
    outputPin_ = ShPtrOutputPin::create(this, 0);
    // connect(outputPin_.get(), &OutputPin::sigConnectChanged,
    //     this, &GenerateNode::slotOutputPinConnectChanged);
}

//==============================================================
// Получение количества данных по типу
//==============================================================
qint32 GenerateNode::byteCountForGenerateType() const
{
    switch (generateType_)
    {
        case GenerateTypes::Bool:
        case GenerateTypes::Int8:
        case GenerateTypes::UInt8:
        {
            return 1;
        }
        case GenerateTypes::Int16:
        case GenerateTypes::UInt16:
        {
            return 2;
        }
        case GenerateTypes::Int32:
        case GenerateTypes::UInt32:
        case GenerateTypes::Float:
        case GenerateTypes::Color:
        {
            return 4;
        }
        case GenerateTypes::Int64:
        case GenerateTypes::UInt64:
        case GenerateTypes::Double:
        {
            return 8;
        }
        case GenerateTypes::String:
        {
            return static_cast<qint32>(getValueByteSize(strValue_));
        }
        default:
        {
            return byteCount_;
        }
    }
}

//==============================================================
// Вывод комментариев
//==============================================================
void GenerateNode::drawComments(QPainter *painter) const
{
    Q_ASSERT(painter != nullptr);

    if (isCommentsVisible())
    {
        QString comments{};
        comments += QString{" <<< %1: \"%2\"\n"}.arg(tr("Name"), name());
        comments += QString{"     %1: %2\n"}.arg(tr("Generate type"), generateTypeToStr(generateType()));
        comments += QString{"     %1: %2\n"}.arg(tr("Count (B)")).arg(dataSize());
        comments += valueStrForComments();
        comments += QString{"     %1: \"%2\"\n"}.arg(tr("Comment"), comment());
#ifdef QT_DEBUG
        comments += "     -\n";
        comments += QString{"     %1: %2\n"}.arg("Id").arg(id());
#endif // QT_DEBUG

        const int commentsLeft = right();
        const int commentsTop = top() + (height() - charHeight()) / 2;
        const int commentsFlags = Qt::AlignLeft | Qt::AlignTop | Qt::TextDontClip;
        const QRect commentsRect{commentsLeft, commentsTop, 0, 0};
        painter->setPen(Colors::nodeText());
        painter->drawText(commentsRect, commentsFlags, comments);
    }
}

//==============================================================
// Получение строки со значением для комментария
//==============================================================
QString GenerateNode::valueStrForTooltip() const
{
    switch (generateType_)
    {
        case GenerateTypes::Usual:
        {
            return QString{"%1: 0x%2\n"}.arg(tr("Filled byte"),
                dataToHexStr(filledByte(), 2));
        }
        case GenerateTypes::Random:
        {
            return QString{};
        }
        case GenerateTypes::Bool:
        {
            return QString{"%1: %2\n"}.arg(tr("Value"), boolToStr(boolValue_));
        }
        case GenerateTypes::Int8:
        {
            return QString{"%1: %2\n"}.arg(tr("Value")).arg(int8Value_);
        }
        case GenerateTypes::UInt8:
        {
            return QString{"%1: %2\n"}.arg(tr("Value")).arg(uint8Value_);
        }
        case GenerateTypes::Int16:
        {
            return QString{"%1: %2\n"}.arg(tr("Value")).arg(int16Value_);
        }
        case GenerateTypes::UInt16:
        {
            return QString{"%1: %2\n"}.arg(tr("Value")).arg(uint16Value_);
        }
        case GenerateTypes::Int32:
        {
            return QString{"%1: %2\n"}.arg(tr("Value")).arg(int32Value_);
        }
        case GenerateTypes::UInt32:
        {
            return QString{"%1: %2\n"}.arg(tr("Value")).arg(uint32Value_);
        }
        case GenerateTypes::Int64:
        {
            return QString{"%1: %2\n"}.arg(tr("Value")).arg(int64Value_);
        }
        case GenerateTypes::UInt64:
        {
            return QString{"%1: %2\n"}.arg(tr("Value")).arg(uint64Value_);
        }
        case GenerateTypes::Float:
        {
            return QString{"%1: %2\n"}.arg(tr("Value")).
                arg(static_cast<double>(floatValue_), 0, 'f', 3);
        }
        case GenerateTypes::Double:
        {
            return QString{"%1: %2\n"}.arg(tr("Value")).
                arg(doubleValue_, 0, 'f', 3);
        }
        case GenerateTypes::String:
        {
            return QString{"%1: \"%2\"\n"}.arg(tr("Value"),
                strValue_.isEmpty() ? "" : "...");
        }
        case GenerateTypes::Color:
        {
            return QString{"%1: %2\n"}.arg(tr("Value"),
            colorValue_.name(QColor::HexArgb).toUpper());
        }
        default:
        {
            return QString{};
        }
    }
}

//==============================================================
// Получение случайного значения по индексу
//==============================================================
quint8 GenerateNode::randValue(qint32 index)
{
    return static_cast<quint8>(qHash(index));
}

//==============================================================
// Обновление состояния узла
//==============================================================
void GenerateNode::updateStateInfo()
{
    const NodeStateInfo oldStateInfo = stateInfo_;

    if (byteCount() == 0)
    {
        const QString msg = "The number of bytes generated is 0";
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

//==============================================================
// Получение строки со значением для комментария
//==============================================================
QString GenerateNode::valueStrForComments() const
{
    switch (generateType_)
    {
        case GenerateTypes::Usual:
        {
            return QString{"     %1: 0x%2\n"}.arg(tr("Filled byte"),
                dataToHexStr(filledByte(), 2));
        }
        case GenerateTypes::Random:
        {
            return QString{};
        }
        case GenerateTypes::Bool:
        {
            return QString{"     %1: %2\n"}.arg(tr("Value"),
                boolToStr(boolValue_));
        }
        case GenerateTypes::Int8:
        {
            return QString{"     %1: %2\n"}.arg(tr("Value")).
                arg(int8Value_);
        }
        case GenerateTypes::UInt8:
        {
            return QString{"     %1: %2\n"}.arg(tr("Value")).
                arg(uint8Value_);
        }
        case GenerateTypes::Int16:
        {
            return QString{"     %1: %2\n"}.arg(tr("Value")).
                arg(int16Value_);
        }
        case GenerateTypes::UInt16:
        {
            return QString{"     %1: %2\n"}.arg(tr("Value")).
                arg(uint16Value_);
        }
        case GenerateTypes::Int32:
        {
            return QString{"     %1: %2\n"}.arg(tr("Value")).
                arg(int32Value_);
        }
        case GenerateTypes::UInt32:
        {
            return QString{"     %1: %2\n"}.arg(tr("Value")).
                arg(uint32Value_);
        }
        case GenerateTypes::Int64:
        {
            return QString{"     %1: %2\n"}.arg(tr("Value")).
                arg(int64Value_);
        }
        case GenerateTypes::UInt64:
        {
            return QString{"     %1: %2\n"}.arg(tr("Value")).
                arg(uint64Value_);
        }
        case GenerateTypes::Float:
        {
            return QString{"     %1: %2\n"}.arg(tr("Value")).
                arg(static_cast<double>(floatValue_), 0, 'f', 3);
        }
        case GenerateTypes::Double:
        {
            return QString{"     %1: %2\n"}.arg(tr("Value")).
                arg(doubleValue_, 0, 'f', 3);
        }
        case GenerateTypes::String:
        {
            return QString{"     %1: \"%2\"\n"}.arg(tr("Value"),
                strValue_.isEmpty() ? "" : "...");
        }
        case GenerateTypes::Color:
        {
            return QString{"     %1: %2\n"}.arg(tr("Value"),
                colorValue_.name(QColor::HexArgb).toUpper());
        }
        default:
        {
            return QString{};
        }
    }
}

//==============================================================
// Чтение типа значения из XML
//==============================================================
GenerateTypes GenerateNode::readGenerateTypeFromXml(const QDomElement &elem) const
{
    Q_ASSERT(!elem.isNull());

    const QString propName = "generateType";

    // Получение узла
    const QDomElement elemGenerateType = elem.firstChildElement(propName);
    if (elemGenerateType.isNull())
    {
        const QString msg = QString{"Not find property \"%1\" of type %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения в виде строки
    const optional<QString> strGenerateType = ::readValueFromXml(elemGenerateType);
    if (!strGenerateType)
    {
        const QString msg = QString{"Not read property \"%1\" of type %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения
    const GenerateTypes generateType = strToGenerateType(strGenerateType.value());
    if (isUnknown(generateType))
    {
        const QString msg = QString{"Bad value of property \"%1\" of type %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    return generateType;
}

//==============================================================
// Чтение значения из XML в зависимости от текущего типа генерации
//==============================================================
QVariant GenerateNode::readValueFromXml(const QDomElement &elem) const
{
    Q_ASSERT(!elem.isNull());

    switch (generateType_)
    {
        case GenerateTypes::Usual:
        {
            const int count = readByteCountFromXml(elem);
            const quint8 filledByte = readFilledByteFromXml(elem);
            const UsualData value{count, filledByte};
            return QVariant::fromValue(value);
        }
        case GenerateTypes::Random:
        {
            const int value = readByteCountFromXml(elem);
            return QVariant{value};
        }
        case GenerateTypes::Bool:
        {
            const bool value = readBoolValueFromXml(elem);
            return QVariant{value};
        }
        case GenerateTypes::Int8:
        {
            const qint8 value = readInt8ValueFromXml(elem);
            return QVariant::fromValue(value);
        }
        case GenerateTypes::UInt8:
        {
            const quint8 value = readUInt8ValueFromXml(elem);
            return QVariant::fromValue(value);
        }
        case GenerateTypes::Int16:
        {
            const qint16 value = readInt16ValueFromXml(elem);
            return QVariant::fromValue(value);
        }
        case GenerateTypes::UInt16:
        {
            const quint16 value = readUInt16ValueFromXml(elem);
            return QVariant::fromValue(value);
        }
        case GenerateTypes::Int32:
        {
            const qint32 value = readInt32ValueFromXml(elem);
            return QVariant::fromValue(value);
        }
        case GenerateTypes::UInt32:
        {
            const quint32 value = readUInt32ValueFromXml(elem);
            return QVariant::fromValue(value);
        }
        case GenerateTypes::Int64:
        {
            const qint64 value = readInt64ValueFromXml(elem);
            return QVariant{value};
        }
        case GenerateTypes::UInt64:
        {
            const quint64 value = readUInt64ValueFromXml(elem);
            return QVariant{value};
        }
        case GenerateTypes::Float:
        {
            const float value = readFloatValueFromXml(elem);
            return QVariant{value};
        }
        case GenerateTypes::Double:
        {
            const double value = readDoubleValueFromXml(elem);
            return QVariant{value};
        }
        case GenerateTypes::String:
        {
            const QString value = readStrValueFromXml(elem);
            return QVariant{value};
        }
        case GenerateTypes::Color:
        {
            const QColor value = readColorValueFromXml(elem);
            return QVariant{value};
        }
        default:
        {
            qDebug() << "Not need read value from XML";
            return QVariant{};
        }
    }
}

//==============================================================
// Чтение количества генерируемых байтов из XML
//==============================================================
int GenerateNode::readByteCountFromXml(const QDomElement &elem) const
{
    Q_ASSERT(!elem.isNull());

    const QString propName = "byteCount";

    // Получение узла
    const QDomElement elemCount = elem.firstChildElement(propName);
    if (elemCount.isNull())
    {
        const QString msg = QString{"Not find property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения в виде строки
    const optional<QString> strCount = ::readValueFromXml(elemCount);
    if (!strCount)
    {
        const QString msg = QString{"Not read property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения
    bool ok = false;
    const int count = strCount.value().toInt(&ok);
    if (!ok || (count < 0))
    {
        const QString msg = QString{"Bad value of property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    return count;
}

//==============================================================
// Чтение байта для заполнения из XML
//==============================================================
quint8 GenerateNode::readFilledByteFromXml(const QDomElement &elem) const
{
    Q_ASSERT(!elem.isNull());

    const QString propName = "filledByte";

    // Получение узла
    const QDomElement elemFilledByte = elem.firstChildElement(propName);
    if (elemFilledByte.isNull())
    {
        const QString msg = QString{"Not find property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения в виде строки
    const optional<QString> strFilledByte = ::readValueFromXml(elemFilledByte);
    if (!strFilledByte)
    {
        const QString msg = QString{"Not read property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения
    bool ok = false;
    const quint8 filledByte = static_cast<quint8>(strFilledByte.value().toUShort(&ok));
    if (!ok)
    {
        const QString msg = QString{"Bad value of property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    return filledByte;
}

//==============================================================
// Чтение значения bool из XML
//==============================================================
bool GenerateNode::readBoolValueFromXml(const QDomElement &elem) const
{
    Q_ASSERT(!elem.isNull());

    const QString propName = "value";

    // Получение узла
    const QDomElement elemValue = elem.firstChildElement(propName);
    if (elemValue.isNull())
    {
        const QString msg = QString{"Not find property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения в виде строки
    const optional<QString> strValue = ::readValueFromXml(elemValue);
    if (!strValue)
    {
        const QString msg = QString{"Not read property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения
    const optional<bool> value = strToBool(strValue.value());
    if (!value)
    {
        const QString msg = QString{"Bad value of property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    return value.value();
}

//==============================================================
// Чтение значения qint8 из XML
//==============================================================
qint8 GenerateNode::readInt8ValueFromXml(const QDomElement &elem) const
{
    Q_ASSERT(!elem.isNull());

    const QString propName = "value";

    // Получение узла
    const QDomElement elemValue = elem.firstChildElement(propName);
    if (elemValue.isNull())
    {
        const QString msg = QString{"Not find property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения в виде строки
    const optional<QString> strValue = ::readValueFromXml(elemValue);
    if (!strValue)
    {
        const QString msg = QString{"Not read property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения
    bool ok = false;
    const qint8 value = static_cast<qint8>(strValue.value().toShort(&ok));
    if (!ok)
    {
        const QString msg = QString{"Bad value of property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    return value;
}

//==============================================================
// Чтение значения quint8 из XML
//==============================================================
quint8 GenerateNode::readUInt8ValueFromXml(const QDomElement &elem) const
{
    Q_ASSERT(!elem.isNull());

    const QString propName = "value";

    // Получение узла
    const QDomElement elemValue = elem.firstChildElement(propName);
    if (elemValue.isNull())
    {
        const QString msg = QString{"Not find property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения в виде строки
    const optional<QString> strValue = ::readValueFromXml(elemValue);
    if (!strValue)
    {
        const QString msg = QString{"Not read property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения
    bool ok = false;
    const quint8 value = static_cast<quint8>(strValue.value().toUShort(&ok));
    if (!ok)
    {
        const QString msg = QString{"Bad value of property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    return value;
}

//==============================================================
// Чтение значения qint16 из XML
//==============================================================
qint16 GenerateNode::readInt16ValueFromXml(const QDomElement &elem) const
{
    Q_ASSERT(!elem.isNull());

    const QString propName = "value";

    // Получение узла
    const QDomElement elemValue = elem.firstChildElement(propName);
    if (elemValue.isNull())
    {
        const QString msg = QString{"Not find property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения в виде строки
    const optional<QString> strValue = ::readValueFromXml(elemValue);
    if (!strValue)
    {
        const QString msg = QString{"Not read property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения
    bool ok = false;
    const qint16 value = strValue.value().toShort(&ok);
    if (!ok)
    {
        const QString msg = QString{"Bad value of property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    return value;
}

//==============================================================
// Чтение значения quint16 из XML
//==============================================================
quint16 GenerateNode::readUInt16ValueFromXml(const QDomElement &elem) const
{
    Q_ASSERT(!elem.isNull());

    const QString propName = "value";

    // Получение узла
    const QDomElement elemValue = elem.firstChildElement(propName);
    if (elemValue.isNull())
    {
        const QString msg = QString{"Not find property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения в виде строки
    const optional<QString> strValue = ::readValueFromXml(elemValue);
    if (!strValue)
    {
        const QString msg = QString{"Not read property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения
    bool ok = false;
    const quint16 value = strValue.value().toUShort(&ok);
    if (!ok)
    {
        const QString msg = QString{"Bad value of property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    return value;
}

//==============================================================
// Чтение значения qint32 из XML
//==============================================================
qint32 GenerateNode::readInt32ValueFromXml(const QDomElement &elem) const
{
    Q_ASSERT(!elem.isNull());

    const QString propName = "value";

    // Получение узла
    const QDomElement elemValue = elem.firstChildElement(propName);
    if (elemValue.isNull())
    {
        const QString msg = QString{"Not find property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения в виде строки
    const optional<QString> strValue = ::readValueFromXml(elemValue);
    if (!strValue)
    {
        const QString msg = tr("Not read property \"%1\" of node %2 with id %3").
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения
    bool ok = false;
    const qint32 value = strValue.value().toInt(&ok);
    if (!ok)
    {
        const QString msg = tr("Bad value of property \"%1\" of node %2 with id %3").
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    return value;
}

//==============================================================
// Чтение значения quint32 из XML
//==============================================================
quint32 GenerateNode::readUInt32ValueFromXml(const QDomElement &elem) const
{
    Q_ASSERT(!elem.isNull());

    const QString propName = "value";

    // Получение узла
    const QDomElement elemValue = elem.firstChildElement(propName);
    if (elemValue.isNull())
    {
        const QString msg = QString{"Not find property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения в виде строки
    const optional<QString> strValue = ::readValueFromXml(elemValue);
    if (!strValue)
    {
        const QString msg = QString{"Not read property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения
    bool ok = false;
    const quint32 value = strValue.value().toUInt(&ok);
    if (!ok)
    {
        const QString msg = QString{"Bad value of property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    return value;
}

//==============================================================
// Чтение значения qint64 из XML
//==============================================================
qint64 GenerateNode::readInt64ValueFromXml(const QDomElement &elem) const
{
    Q_ASSERT(!elem.isNull());

    const QString propName = "value";

    // Получение узла
    const QDomElement elemValue = elem.firstChildElement(propName);
    if (elemValue.isNull())
    {
        const QString msg = QString{"Not find property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения в виде строки
    const optional<QString> strValue = ::readValueFromXml(elemValue);
    if (!strValue)
    {
        const QString msg = QString{"Not read property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения
    bool ok = false;
    const qint64 value = strValue.value().toLongLong(&ok);
    if (!ok)
    {
        const QString msg = QString{"Bad value of property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    return value;
}

//==============================================================
// Чтение значения quint64 из XML
//==============================================================
quint64 GenerateNode::readUInt64ValueFromXml(const QDomElement &elem) const
{
    Q_ASSERT(!elem.isNull());

    const QString propName = "value";

    // Получение узла
    const QDomElement elemValue = elem.firstChildElement(propName);
    if (elemValue.isNull())
    {
        const QString msg = QString{"Not find property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения в виде строки
    const optional<QString> strValue = ::readValueFromXml(elemValue);
    if (!strValue)
    {
        const QString msg = QString{"Not read property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения
    bool ok = false;
    const quint64 value = strValue.value().toULongLong(&ok);
    if (!ok)
    {
        const QString msg = QString{"Not read property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    return value;
}

//==============================================================
// Чтение значения float из XML
//==============================================================
float GenerateNode::readFloatValueFromXml(const QDomElement &elem) const
{
    Q_ASSERT(!elem.isNull());

    const QString propName = "value";

    // Получение узла
    const QDomElement elemValue = elem.firstChildElement(propName);
    if (elemValue.isNull())
    {
        const QString msg = QString{"Not find property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения в виде строки
    const optional<QString> strValue = ::readValueFromXml(elemValue);
    if (!strValue)
    {
        const QString msg = QString{"Not read property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения
    bool ok = false;
    const float value = strValue.value().toFloat(&ok);
    if (!ok)
    {
        const QString msg = QString{"Not read property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    return value;
}

//==============================================================
// Чтение значения double из XML
//==============================================================
double GenerateNode::readDoubleValueFromXml(const QDomElement &elem) const
{
    Q_ASSERT(!elem.isNull());

    const QString propName = "value";

    // Получение узла
    const QDomElement elemValue = elem.firstChildElement(propName);
    if (elemValue.isNull())
    {
        const QString msg = QString{"Not find property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения в виде строки
    const optional<QString> strValue = ::readValueFromXml(elemValue);
    if (!strValue)
    {
        const QString msg = QString{"Not read property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    // Получение значения
    bool ok = false;
    const double value = strValue.value().toDouble(&ok);
    if (!ok)
    {
        const QString msg = QString{"Not read property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    return value;
}

//==============================================================
// Чтение значения QColor из XML
//==============================================================
QColor GenerateNode::readColorValueFromXml(const QDomElement &elem) const
{
    Q_ASSERT(!elem.isNull());

    const QString propName = "value";

    //  Получение узла
    const QDomElement elemValue = elem.firstChildElement(propName);
    if (elemValue.isNull())
    {
        const QString msg = QString{"Not find property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    //  Получение значения в виде строки
    bool ok = false;
    const optional<QString> strValue = ::readValueFromXml(elemValue);
    if (!ok)
    {
        const QString msg = tr("Not read property \"%1\" of node %2 with id %3").
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    //  Получение значения
    const QColor value{strValue.value()};
    if (!value.isValid())
    {
        const QString msg = tr("Not read property \"%1\" of node %2 with id %3").
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    return value;
}

//==============================================================
// Чтение значения QString из XML
//==============================================================
QString GenerateNode::readStrValueFromXml(const QDomElement &elem) const
{
    Q_ASSERT(!elem.isNull());

    const QString propName = "value";

    //  Получение узла
    const QDomElement elemValue = elem.firstChildElement(propName);
    if (elemValue.isNull())
    {
        const QString msg = QString{"Not find property \"%1\" of node %2 with id %3"}.
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    //  Получение значения в виде строки
    const optional<QString> strValue = ::readValueFromXml(elemValue);
    if (!strValue)
    {
        const QString msg = tr("Not read property \"%1\" of node %2 with id %3").
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    //  Получение значения
    const optional<QString> value = strFromXmlFormat(strValue.value());
    if (!value)
    {
        const QString msg = tr("Bad value of property \"%1\" of node %2 with id %3").
            arg(propName, strType()).arg(id());
        throw BaseException{msg};
    }

    return value.value();
}

//==============================================================
// Запись типа генерации в XML
//==============================================================
void GenerateNode::writeGenerateTypeToXml(QDomDocument &doc,
    QDomElement &elem) const
{
    Q_ASSERT(!doc.isNull());
    Q_ASSERT(!elem.isNull());

    QDomElement elemGenerateType = doc.createElement("generateType");
    const QString strGenerateType = generateTypeToStr(generateType());
    ::writeValueToXml(doc, elemGenerateType, strGenerateType);
    elem.appendChild(elemGenerateType);
}

//==============================================================
// Запись количества генерируемых байт в XML
//==============================================================
void GenerateNode::writeByteCountToXml(QDomDocument &doc,
    QDomElement &elem) const
{
    Q_ASSERT(!doc.isNull());
    Q_ASSERT(!elem.isNull());

    QDomElement elemCount = doc.createElement("byteCount");
    const QString strCount = QString::number(byteCount());
    ::writeValueToXml(doc, elemCount, strCount);
    elem.appendChild(elemCount);
}

//==============================================================
// Запись байта для заполнения в XML
//==============================================================
void GenerateNode::writeFilledByteToXml(QDomDocument &doc,
    QDomElement &elem) const
{
    Q_ASSERT(!doc.isNull());
    Q_ASSERT(!elem.isNull());

    QDomElement elemFilledByte = doc.createElement("filledByte");
    const QString strFilledByte = QString::number(filledByte());
    ::writeValueToXml(doc, elemFilledByte, strFilledByte);
    elem.appendChild(elemFilledByte);
}

//==============================================================
// Запись значения в записимости от типа генерации в XML
//==============================================================
void GenerateNode::writeValueToXml(QDomDocument &doc, QDomElement &elem) const
{
    Q_ASSERT(!doc.isNull());
    Q_ASSERT(!elem.isNull());

    switch (generateType_)
    {
        case GenerateTypes::Usual:
        {
            writeByteCountToXml(doc, elem);
            writeFilledByteToXml(doc, elem);
            break;
        }
        case GenerateTypes::Random:
        {
            writeByteCountToXml(doc, elem);
            break;
        }
        case GenerateTypes::Bool:
        {
            writeBoolValueToXml(doc, elem);
            break;
        }
        case GenerateTypes::Int8:
        {
            writeInt8ValueToXml(doc, elem);
            break;
        }
        case GenerateTypes::UInt8:
        {
            writeUInt8ValueToXml(doc, elem);
            break;
        }
        case GenerateTypes::Int16:
        {
            writeInt16ValueToXml(doc, elem);
            break;
        }
        case GenerateTypes::UInt16:
        {
            writeUInt16ValueToXml(doc, elem);
            break;
        }
        case GenerateTypes::Int32:
        {
            writeInt32ValueToXml(doc, elem);
            break;
        }
        case GenerateTypes::UInt32:
        {
            writeUInt32ValueToXml(doc, elem);
            break;
        }
        case GenerateTypes::Int64:
        {
            writeInt64ValueToXml(doc, elem);
            break;
        }
        case GenerateTypes::UInt64:
        {
            writeUInt64ValueToXml(doc, elem);
            break;
        }
        case GenerateTypes::Float:
        {
            writeFloatValueToXml(doc, elem);
            break;
        }
        case GenerateTypes::Double:
        {
            writeDoubleValueToXml(doc, elem);
            break;
        }
        case GenerateTypes::String:
        {
            writeStrValueToXml(doc, elem);
            break;
        }
        case GenerateTypes::Color:
        {
            writeColorValueToXml(doc, elem);
            break;
        }
        default:
        {
            qDebug() << "Unknown generate value type";
            break;
        }
    }
}

//==============================================================
// Запись значения bool в XML
//==============================================================
void GenerateNode::writeBoolValueToXml(QDomDocument &doc, QDomElement &elem) const
{
    Q_ASSERT(!doc.isNull());
    Q_ASSERT(!elem.isNull());

    QDomElement elemBoolValue = doc.createElement("value");
    const QString strBoolValue = boolToStr(boolValue_);
    ::writeValueToXml(doc, elemBoolValue, strBoolValue);
    elem.appendChild(elemBoolValue);
}

//==============================================================
// Запись значения qint8 в XML
//==============================================================
void GenerateNode::writeInt8ValueToXml(QDomDocument &doc, QDomElement &elem) const
{
    Q_ASSERT(!doc.isNull());
    Q_ASSERT(!elem.isNull());

    QDomElement elemI8Value = doc.createElement("value");
    const QString strI8Value = QString::number(int8Value_);
    ::writeValueToXml(doc, elemI8Value, strI8Value);
    elem.appendChild(elemI8Value);
}

//==============================================================
// Запись значения quint8 в XML
//==============================================================
void GenerateNode::writeUInt8ValueToXml(QDomDocument &doc, QDomElement &elem) const
{
    Q_ASSERT(!doc.isNull());
    Q_ASSERT(!elem.isNull());

    QDomElement elemUI8Value = doc.createElement("value");
    const QString strUI8Value = QString::number(uint8Value_);
    ::writeValueToXml(doc, elemUI8Value, strUI8Value);
    elem.appendChild(elemUI8Value);
}

//==============================================================
// Запись значения qint16 в XML
//==============================================================
void GenerateNode::writeInt16ValueToXml(QDomDocument &doc, QDomElement &elem) const
{
    Q_ASSERT(!doc.isNull());
    Q_ASSERT(!elem.isNull());

    QDomElement elemI16Value = doc.createElement("value");
    const QString strI16Value = QString::number(int16Value_);
    ::writeValueToXml(doc, elemI16Value, strI16Value);
    elem.appendChild(elemI16Value);
}

//==============================================================
// Запись значения quint16 в XML
//==============================================================
void GenerateNode::writeUInt16ValueToXml(QDomDocument &doc, QDomElement &elem) const
{
    Q_ASSERT(!doc.isNull());
    Q_ASSERT(!elem.isNull());

    QDomElement elemUI16Value = doc.createElement("value");
    const QString strUI16Value = QString::number(uint16Value_);
    ::writeValueToXml(doc, elemUI16Value, strUI16Value);
    elem.appendChild(elemUI16Value);
}

//==============================================================
// Запись значения qint32 в XML
//==============================================================
void GenerateNode::writeInt32ValueToXml(QDomDocument &doc, QDomElement &elem) const
{
    Q_ASSERT(!doc.isNull());
    Q_ASSERT(!elem.isNull());

    QDomElement elemI32Value = doc.createElement("value");
    const QString strI32Value = QString::number(int32Value_);
    ::writeValueToXml(doc, elemI32Value, strI32Value);
    elem.appendChild(elemI32Value);
}

//==============================================================
// Запись значения quint32 в XML
//==============================================================
void GenerateNode::writeUInt32ValueToXml(QDomDocument &doc, QDomElement &elem) const
{
    Q_ASSERT(!doc.isNull());
    Q_ASSERT(!elem.isNull());

    QDomElement elemUI32Value = doc.createElement("value");
    const QString strUI32Value = QString::number(uint32Value_);
    ::writeValueToXml(doc, elemUI32Value, strUI32Value);
    elem.appendChild(elemUI32Value);
}

//==============================================================
// Запись значения qint64 в XML
//==============================================================
void GenerateNode::writeInt64ValueToXml(QDomDocument &doc, QDomElement &elem) const
{
    Q_ASSERT(!doc.isNull());
    Q_ASSERT(!elem.isNull());

    QDomElement elemUI64Value = doc.createElement("value");
    const QString strUI64Value = QString::number(uint64Value_);
    ::writeValueToXml(doc, elemUI64Value, strUI64Value);
    elem.appendChild(elemUI64Value);
}

//==============================================================
// Запись значения quint64 в XML
//==============================================================
void GenerateNode::writeUInt64ValueToXml(QDomDocument &doc, QDomElement &elem) const
{
    Q_ASSERT(!doc.isNull());
    Q_ASSERT(!elem.isNull());

    QDomElement elemFloatValue = doc.createElement("value");
    const QString strFloatValue = QString::number(static_cast<double>(floatValue_));
    ::writeValueToXml(doc, elemFloatValue, strFloatValue);
    elem.appendChild(elemFloatValue);
}

//==============================================================
// Запись значения float в XML
//==============================================================
void GenerateNode::writeFloatValueToXml(QDomDocument &doc, QDomElement &elem) const
{
    Q_ASSERT(!doc.isNull());
    Q_ASSERT(!elem.isNull());

    QDomElement elemFloatValue = doc.createElement("value");
    const QString strFloatValue = QString::number(static_cast<double>(floatValue_));
    ::writeValueToXml(doc, elemFloatValue, strFloatValue);
    elem.appendChild(elemFloatValue);
}

//==============================================================
// Запись значения double в XML
//==============================================================
void GenerateNode::writeDoubleValueToXml(QDomDocument &doc, QDomElement &elem) const
{
    Q_ASSERT(!doc.isNull());
    Q_ASSERT(!elem.isNull());

    QDomElement elemDoubleValue = doc.createElement("value");
    const QString strDoubleValue = QString::number(doubleValue_);
    ::writeValueToXml(doc, elemDoubleValue, strDoubleValue);
    elem.appendChild(elemDoubleValue);
}

//==============================================================
// Запись значения QString в XML
//==============================================================
void GenerateNode::writeStrValueToXml(QDomDocument &doc, QDomElement &elem) const
{
    Q_ASSERT(!doc.isNull());
    Q_ASSERT(!elem.isNull());

    QDomElement elemStrValue = doc.createElement("value");
    const QString xmlStrValue = strToXmlFormat(strValue_);
    ::writeValueToXml(doc, elemStrValue, xmlStrValue);
    elem.appendChild(elemStrValue);
}

//==============================================================
// Запись значения QColor в XML
//==============================================================
void GenerateNode::writeColorValueToXml(QDomDocument &doc, QDomElement &elem) const
{
    Q_ASSERT(!doc.isNull());
    Q_ASSERT(!elem.isNull());

    QDomElement elemColorValue = doc.createElement("value");
    const QString strColorValue = colorValue_.name(QColor::HexArgb).toUpper();
    ::writeValueToXml(doc, elemColorValue, strColorValue);
    elem.appendChild(elemColorValue);
}

//==============================================================
// Представление байта в виде шестнадцатиричной строки
//==============================================================
QString GenerateNode::dataToHexStr(quint32 data, int fieldWidth)
{
    Q_ASSERT(fieldWidth > 0);

    return QString{"%1"}.arg(data, fieldWidth, 16, QChar('0')).toUpper();
}
