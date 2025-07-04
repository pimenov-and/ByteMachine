////////////////////////////////////////////////////////////////
// ByteMachine
// Узел "Generate"
////////////////////////////////////////////////////////////////
#ifndef GENERATE_NODE_H
#define GENERATE_NODE_H

//==============================================================
#include <QColor>
#include "base_node.h"
#include "generate_types.h"

//==============================================================
// Узел "Generate"
//==============================================================
class GenerateNode final : public BaseNode
{
    Q_OBJECT
    Q_PROPERTY(GenerateTypes generateType READ generateType WRITE setGenerateType RESET resetGenerateType)
public:
    // Конструктор с параметром
    explicit GenerateNode(QUndoStack *undoStack, QObject *parent = nullptr);
    // Деструктор
    ~GenerateNode() override;

    // Чтение из XML
    void readFromXml(const QDomElement &elem) override;
    // Запись в XML
    void writeToXml(QDomDocument &doc, QDomElement &elem) const override;

    // Получение типа узла
    NodeTypes type() const override { return NodeTypes::Generate; }
    // Функция вывода
    void draw(QPainter *painter) const override;
    // Получение копии узла
    QSharedPointer<BaseNode> clone() const override;
    // Получение текста подсказки
    QString tooltipText() const override;
    // Получение признака изменения размера
    bool isResizeble() const override { return false; }
    // Получение признака того, что узел поддерживает прокрутку
    bool isScrollable() const override { return false; }

    // Получение размера данных
    qint32 dataSize() const override;
    // Получение байта данных
    quint8 dataByte(qint32 index) const override;
    // Получение блока данных
    QVector<quint8> dataBlock(qint32 index, qint32 count) const override;
    // Функция вызывается при изменении данных
    void dataChanged() override;

    // Получение типа генерации
    [[nodiscard]]
    GenerateTypes generateType() const { return generateType_; }
    // Задание типа генерации
    void setGenerateType(GenerateTypes type);
    // Сброс типа генерации
    void resetGenerateType();
    // Получение признака изменения типа генерации
    [[nodiscard]]
    bool isGenerateTypeChanged() const { return !isUsual(generateType_); }
private slots:
private:
    // Создание выходного пина
    void createOutputPin();

    //----------------------------------------------------------
    // Чтение значений из XML
    //----------------------------------------------------------

    //----------------------------------------------------------
    // Генерируемые значения
    //----------------------------------------------------------
    // Тип генерации
    GenerateTypes generateType_ {GenerateTypes::Usual};
    // Значение типа Bool
    bool boolValue_{false};
    // Значение типа Int8
    qint8 int8Value_{0};
    // Значение типа UInt8
    quint8 uint8Value_{0};
    // Значение типа Int16
    qint16 int16Value_{0};
    // Значение типа UInt16
    quint16 uint16Value_{0};
    // Значение типа Int32
    qint32 int32Value_{0};
    // Значение типа UInt32
    quint32 uint32Value_{0};
    // Значение типа Int64
    qint64 int64Value_{0};
    // Значение типа UInt64
    quint64 uint64Value_{0};
    // Значение типа Float
    float floatValue_{0};
    // Значение типа Double
    double doubleValue_{0};
    // Значение тип String
    QString strValue_{};
    // Цвет
    QColor colorValue_{Qt::black};

    // Количество генерируемых байт
    qint32 byteCount_{0};
    // Байт для заполнения
    quint8 filledByte_{0};
};

//==============================================================
using ShPtrGenerateNode = QSharedPointer<GenerateNode>;
using ShPtrConstGenerateNode = QSharedPointer<const GenerateNode>;

//==============================================================
#endif // GENERATE_NODE_H
