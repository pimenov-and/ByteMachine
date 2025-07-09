/////////////////////////////////////////////////////////////////////
// ByteMachine
// Входной пин
/////////////////////////////////////////////////////////////////////
#include "input_pin.h"
#include "output_pin.h"
#include "base_node.h"
#include "base_exception.h"
#include <QDomDocument>
#include <QRect>

//===================================================================
// Конструктор с параметрами
//===================================================================
InputPin::InputPin(BaseNode *parentNode, int index) :
    BasePin{parentNode, index}
{
}

//===================================================================
// Деструктор
//===================================================================
InputPin::~InputPin()
{
    /* if (outputPin_ != nullptr)
    {
        outputPin_->removeInputPin(this, false);
    } */
    // FIXME: возможно добавить удаление связи
}

//===================================================================
// Чтение из XML
//===================================================================
void InputPin::readFromXml(const QDomElement &elem)
{
    const QDomElement elemOutputPin = elem.firstChildElement("outputPin");
    if (elemOutputPin.isNull())
    {
        throw BaseException(tr("Bad input pin"));
    }

    const QString strNodeId = elemOutputPin.attribute("nodeId");
    bool ok = false;
    const int nodeId = strNodeId.toInt(&ok);
    if (!ok)
    {
        throw BaseException{tr("Bad node id")};
    }

    const QString strIndex = elemOutputPin.attribute("index");
    const int index = strIndex.toInt(&ok);
    if (!ok)
    {
        throw BaseException{tr("Bad pin index")};
    }

    outputPinConnection_.init(nodeId, index);
}

//===================================================================
// Запись в XML
//===================================================================
void InputPin::writeToXml(QDomDocument &doc, QDomElement &elem) const
{
    writeIndexToXml(doc, elem);
    writeOutputPinToXml(doc, elem);
}

//===================================================================
// Получение признака подключения
//==================================================================
bool InputPin::isConnected() const
{
    return outputPin_ != nullptr;
}

//===================================================================
// Получение области пина
//===================================================================
QRect InputPin::rect() const
{
    const BaseNode *const node = parentNode();
    const int index = node->indexOfInputPin(this);
    Q_ASSERT(index != -1);

    return node->inputPinRect(index);
}

//===================================================================
// Получение представления в виде строки
//===================================================================
QString InputPin::toStr() const
{
    return "InputPin";
}

//===================================================================
// Получение подключенного выходного пина
//===================================================================
ShPtrOutputPin& InputPin::outputPin()
{
    return outputPin_;
}

//===================================================================
// Получение подключенного выходного пина (константный вариант)
//===================================================================
ShPtrConstOutputPin InputPin::outputPin() const
{
    return outputPin_;
}

//===================================================================
// Задание подключенного выходного пина
//===================================================================
void InputPin::setOutputPin(const ShPtrOutputPin &pin, bool isRaiseSignal)
{
    if (outputPin_ != pin)
    {
        outputPin_ = pin;

        if (isRaiseSignal)
        {
            const ConnectStates state = (outputPin_ != nullptr)
                ? ConnectStates::Connect
                : ConnectStates::Disconnect;
            emit sigConnectChanged(state, outputPin_.get());
        }
    }
}

//===================================================================
// Корректировка соединений (используется при чтении из XML
// для последующей корректировки связи)
//===================================================================
void InputPin::correctConnections(QVector<ShPtrBaseNode> &nodes)
{
    Q_UNUSED(nodes);

    // FIXME: добавить тело функции коректировки соедининий пина
}

//===================================================================
// Получение размера данных
//===================================================================
qint32 InputPin::dataSize() const
{
    Q_ASSERT(outputPin_ != nullptr);

    return outputPin_->dataSize();
}

//===================================================================
// Получение байта данных
//===================================================================
quint8 InputPin::dataByte(qint32 index) const
{
    Q_ASSERT_X((index >= 0) && (index < dataSize()), "Check index",
               qPrintable(QString("index: %1, dataSize: %2").arg(index).arg(dataSize())));

    return outputPin_->dataByte(index);
}

//===================================================================
// Получение блока данных
//===================================================================
QVector<quint8> InputPin::dataBlock(qint32 index, qint32 count) const
{
    Q_ASSERT_X(index >= 0, "Check index", qPrintable(QString::number(index)));
    Q_ASSERT_X(count >= 0, "Check count", qPrintable(QString::number(count)));
    Q_ASSERT_X(static_cast<qint64>(index) + count <= dataSize(), "Check index and count",
               qPrintable(QString{"index: %1, count: %2, dataSize: %3"}.
                          arg(index).arg(count).arg(dataSize())));

    return outputPin_->dataBlock(index, count);
}

//===================================================================
// Функция вызывается при изменении данных родительского узла
//===================================================================
void InputPin::dataChanged()
{
    parentNode()->dataChanged();
}

//===================================================================
// Запись индекса в XML
//===================================================================
void InputPin::writeIndexToXml(QDomDocument&, QDomElement &elem) const
{
    elem.setAttribute("index", index());
}

//===================================================================
// Запись подключенного выходного пина
//===================================================================
void InputPin::writeOutputPinToXml(QDomDocument &doc,
                                   QDomElement &elem) const
{
    QDomElement elemOutputPin = doc.createElement("outputPin");

    const int nodeId = isConnected() ? outputPin_->parentNode()->id() : -1;
    elemOutputPin.setAttribute("nodeId", nodeId);

    const int index = isConnected() ? outputPin_->index() : -1;
    elemOutputPin.setAttribute("index", index);

    elem.appendChild(elemOutputPin);
}
