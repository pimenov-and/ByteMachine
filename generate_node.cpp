////////////////////////////////////////////////////////////////
// ByteMachine
// Узел "Generate"
////////////////////////////////////////////////////////////////
#include "generate_node.h"
#include "node_name_manager.h"
#include <QPainter>
#include <QDomDocument>
#include <QDebug>

//==============================================================
// Конструктор с параметром
//==============================================================
GenerateNode::GenerateNode(QUndoStack *undoStack, QObject *parent) :
    BaseNode{undoStack, parent}
{
    name_ = nodeNameManager()->addName("Generate");
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
}

//==============================================================
// Запись в XML
//==============================================================
void GenerateNode::writeToXml(QDomDocument &doc, QDomElement &elem) const
{
    Q_ASSERT(!doc.isNull());
    Q_ASSERT(!elem.isNull());
}

//==============================================================
// Функция вывода
//==============================================================
void GenerateNode::draw(QPainter *painter) const
{
    Q_ASSERT(painter != nullptr);
}

//==============================================================
// Получение копии узла
//==============================================================
QSharedPointer<BaseNode> GenerateNode::clone() const
{
    const auto cloneNode = ShPtrGenerateNode::create(undoStack());
    cloneNode->setGenerateType(generateType());

    return cloneNode;
}

//==============================================================
// Получение текста подсказки
//==============================================================
QString GenerateNode::tooltipText() const
{
    QString text{};
    text += QString{"%1: \"%2\"\n"}.arg(tr("Name"), name());
    text += QString{"%1: \"%2\""}.arg(tr("Comment"), comment());

    return text;
}

//==============================================================
// Получение размера данных
//==============================================================
qint32 GenerateNode::dataSize() const
{
    return 0;
}

//==============================================================
// Получение байта данных
//==============================================================
quint8 GenerateNode::dataByte(qint32 index) const
{
    Q_UNUSED(index);

    return 0;
}

//==============================================================
// Получение блока данных
//==============================================================
QVector<quint8> GenerateNode::dataBlock(qint32 index, qint32 count) const
{
    Q_UNUSED(index);
    Q_UNUSED(count);

    return QVector<quint8>{};
}

//==============================================================
// Функция вызывается при изменении данных
//==============================================================
void GenerateNode::dataChanged()
{
}

//==============================================================
// Задание типа генерации
//==============================================================
void GenerateNode::setGenerateType(GenerateTypes type)
{
    if (generateType_ != type)
    {
        generateType_ = type;
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
    Q_ASSERT_X(count >= 0, "Check byte count", qPrintable(QString::number(count)));
}

//==============================================================
// Сброс количества байтов
//==============================================================
void GenerateNode::resetByteCount()
{
    setByteCount(0);
}

//==============================================================
// Создание выходного пина
//==============================================================
void GenerateNode::createOutputPin()
{
}

//==============================================================
// Чтение типа значения из XML
//==============================================================
GenerateTypes GenerateNode::readGenerateTypeFromXml(const QDomElement &elem) const
{
    Q_UNUSED(elem);

    return GenerateTypes::Unknown;
}

//==============================================================
// Чтение значения из XML в зависимости от текущего типа генерации
//==============================================================
QVariant GenerateNode::readValueFromXml(const QDomElement &elem) const
{
    Q_UNUSED(elem);

    return QString{};
}

//==============================================================
// Запись типа генерации в XML
//==============================================================
void GenerateNode::writeGenerateTypeToXml(QDomDocument &doc, QDomElement &elem) const
{
    Q_UNUSED(doc);
    Q_UNUSED(elem);
}

//==============================================================
// Запись количества генерируемых байт в XML
//==============================================================
void GenerateNode::writeByteCountToXml(QDomDocument &doc, QDomElement &elem) const
{
    Q_UNUSED(doc);
    Q_UNUSED(elem);
}
