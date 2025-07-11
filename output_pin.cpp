/////////////////////////////////////////////////////////////////////
// ByteMachine
// Выходной пин узла
/////////////////////////////////////////////////////////////////////
#include "output_pin.h"
#include "input_pin.h"
#include "base_node.h"
#include "base_exception.h"
#include <QDomDocument>
#include <QRect>

//===================================================================
// Конструктор с параметром
//===================================================================
OutputPin::OutputPin(BaseNode *parentNode, int index) :
    BasePin{parentNode, index}
{
}

//===================================================================
// Деструктор
//===================================================================
OutputPin::~OutputPin()
{
    /* for (InputPin *const inPin: qAsConst(inputPins_))
    {
        inPin->setOutputPin(nullptr, false);
    } */ // FIXME: возможно нужно удалять связи
}

//===================================================================
// Чтение из XML
//===================================================================
void OutputPin::readFromXml(const QDomElement &elem)
{
    inputPinConnections_.clear();

    const QDomElement elemPins = elem.firstChildElement("inputPins");
    if (elemPins.isNull())
    {
        throw BaseException{tr("Bad output pin")};
    }
    QDomElement elemPin = elemPins.firstChildElement("inputPin");
    while (!elemPin.isNull())
    {
        // Получение идентификатора узла для задания связи
        const QString strNodeId = elemPin.attribute("nodeId");
        if (strNodeId.isEmpty())
            throw BaseException{tr("Bad node id")};
        bool ok = false;
        const int nodeId = strNodeId.toInt(&ok);
        if (!ok)
        {
            throw BaseException{tr("Bad node id")};
        }

        // Получение индекса пина для задания связи
        const QString strIndex = elemPin.attribute("index");
        if (strIndex.isEmpty())
        {
            throw BaseException{tr("Bad pin index")};
        }
        const int index = strIndex.toInt(&ok);
        if (!ok)
        {
            throw BaseException{tr("Bad pin index")};
        }
        inputPinConnections_ << PinConnection{nodeId, index};

        elemPin = elemPin.nextSiblingElement("inputPin");
    }
}

//===================================================================
// Запись в XML
//===================================================================
void OutputPin::writeToXml(QDomDocument &doc, QDomElement &elem) const
{
    writeIndexToXml(doc, elem);
    writeInputPinsToXml(doc, elem);
}

//===================================================================
// Получение области пина
//===================================================================
QRect OutputPin::rect() const
{
    const BaseNode *const node = parentNode();
    const int index = node->indexOfOutputPin(this);
    Q_ASSERT(index != -1);

    return node->outputPinRect(index);
}

//===================================================================
// Получение представления в виде строки
//===================================================================
QString OutputPin::toStr() const
{
    return "OutputPin";
}

//===================================================================
// Получение входных пинов
//===================================================================
QVector<ShPtrInputPin> OutputPin::inputPins()
{
    return inputPins_;
}

//===================================================================
// Получение входных пинов (константный вариант)
//===================================================================
QVector<ShPtrConstInputPin> OutputPin::inputPins() const
{
    QVector<ShPtrConstInputPin> pins{};
    for (const ShPtrInputPin &pin: inputPins_)
    {
        pins << pin;
    }

    return pins;
}

//===================================================================
// Получение количества подключенных входных пинов
//===================================================================
int OutputPin::inputPinCount() const
{
    return inputPins_.count();
}

//===================================================================
// Получение признака подключения
//===================================================================
bool OutputPin::isConnected() const
{
    return !inputPins_.isEmpty();
}

//===================================================================
// Проверка наличия подключенного входного пина
//===================================================================
bool OutputPin::containsInputPin(const ShPtrConstInputPin &pin) const
{
    return containsInputPin(pin.get());
}

//===================================================================
// Проверка наличия подключенного входного пина (2 вариант)
//===================================================================
bool OutputPin::containsInputPin(const InputPin *pin) const
{
    for (const ShPtrInputPin &inputPin: inputPins_)
    {
        if (inputPin == pin)
        {
            return true;
        }
    }

    return false;
}

//===================================================================
// Добавление подключенного входного пина
//===================================================================
void OutputPin::addInputPin(const ShPtrInputPin &pin)
{
    if (!containsInputPin(pin))
    {
        inputPins_ << pin;

        emit sigConnectChanged(ConnectStates::Connect, pin.get());
    }
}

//===================================================================
// Удаление входного пина
//===================================================================
void OutputPin::removeInputPin(const ShPtrConstInputPin &pin,
                               bool isRaiseSignal)
{
    if (containsInputPin(pin))
    {
        const ShPtrInputPin p = qSharedPointerConstCast<InputPin>(pin);

        if (isRaiseSignal)
        {
            emit sigConnectChanged(ConnectStates::Disconnect, p.get());
        }

        inputPins_.removeOne(p);
    }
}

//===================================================================
// Удаление входного пина ((сырые указатели))
//===================================================================
void OutputPin::removeInputPin(const InputPin *pin, bool isRaiseSignal)
{
    if (containsInputPin(pin))
    {
        InputPin *const p = const_cast<InputPin*>(pin);

        if (isRaiseSignal)
        {
            emit sigConnectChanged(ConnectStates::Disconnect, p);
        }

        int index = -1;
        for (int i = 0; i < inputPins_.count(); ++i)
        {
            if (inputPins_[i] == p)
            {
                index = i;
                break;
            }
        }
        Q_ASSERT(index != -1);
        inputPins_.removeAt(index);
    }
}

//===================================================================
// Получение размера данных
//===================================================================
qint32 OutputPin::dataSize() const
{
    return parentNode()->dataSize();
}

//===================================================================
// Получение байта данных
//===================================================================
quint8 OutputPin::dataByte(qint32 index) const
{
    Q_ASSERT_X((index >= 0) && (index < dataSize()), "Check index",
               qPrintable(QString("index: %1, dataSize: %2").arg(index).arg(dataSize())));

    return parentNode()->dataByte(index);
}

//===================================================================
// Получение блока данных
//===================================================================
QVector<quint8> OutputPin::dataBlock(qint32 index, qint32 count) const
{
    Q_ASSERT_X(index >= 0, "Check index", qPrintable(QString::number(index)));
    Q_ASSERT_X(count >= 0, "Check count", qPrintable(QString::number(count)));
    Q_ASSERT_X(static_cast<qint64>(index) + count <= dataSize(), "Check index and count",
               qPrintable(QString("index: %1, count: %2, dataSize: %3").arg(index).arg(count).arg(dataSize())));

    return parentNode()->dataBlock(index, count);
}

//===================================================================
// Функция вызывается при изменении данных родительского узла
//===================================================================
void OutputPin::dataChanged()
{
    for (ShPtrInputPin &pin: inputPins_)
    {
        pin->dataChanged();
    }
}

//===================================================================
// Запись индекса в XML
//===================================================================
void OutputPin::writeIndexToXml(QDomDocument &doc, QDomElement &elem) const
{
    Q_UNUSED(doc)

    elem.setAttribute("index", index());
}

//===================================================================
// Запись подключенных входных пинов
//===================================================================
void OutputPin::writeInputPinsToXml(QDomDocument &doc, QDomElement &elem) const
{
    QDomElement elemInputPins = doc.createElement("inputPins");
    for (const ShPtrInputPin &pin: inputPins_)
    {
        QDomElement elemInputPin = doc.createElement("inputPin");

        const int nodeId = pin->parentNode()->id();
        elemInputPin.setAttribute("nodeId", nodeId);

        const int index = pin->index();
        elemInputPin.setAttribute("index", index);

        elemInputPins.appendChild(elemInputPin);
    }
    elem.appendChild(elemInputPins);
}
