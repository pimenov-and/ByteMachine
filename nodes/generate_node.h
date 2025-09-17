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
    Q_PROPERTY(qint32 byteCount READ byteCount WRITE setByteCount RESET resetByteCount)
    Q_PROPERTY(qint32 filledByte READ filledByte WRITE setFilledByte RESET resetFilledByte)
    Q_PROPERTY(bool boolValue READ boolValue WRITE setBoolValue RESET resetBoolValue)
    Q_PROPERTY(qint8 int8Value READ int8Value WRITE setInt8Value RESET resetInt8Value)
    Q_PROPERTY(quint8 uint8Value READ uint8Value WRITE setUInt8Value RESET resetUInt8Value)
    Q_PROPERTY(qint16 int16Value READ int16Value WRITE setInt16Value RESET resetInt16Value)
    Q_PROPERTY(quint16 uint16Value READ uint16Value WRITE setUInt16Value RESET resetUInt16Value)
    Q_PROPERTY(qint32 int32Value READ int32Value WRITE setInt32Value RESET resetInt32Value)
    Q_PROPERTY(quint32 uint32Value READ uint32Value WRITE setUInt32Value RESET resetUInt32Value)
    Q_PROPERTY(qint64 int64Value READ int64Value WRITE setInt64Value RESET resetInt64Value)
    Q_PROPERTY(quint64 uint64Value READ uint64Value WRITE setUInt64Value RESET resetUInt64Value)
    Q_PROPERTY(float floatValue READ floatValue WRITE setFloatValue RESET resetFloatValue)
    Q_PROPERTY(double doubleValue READ doubleValue WRITE setDoubleValue RESET resetDoubleValue)
    Q_PROPERTY(QString strValue READ strValue WRITE setStrValue RESET resetStrValue)
    Q_PROPERTY(QColor colorValue READ colorValue WRITE setColorValue RESET resetColorValue)
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

    // Получение выходных пинов
    QVector<ShPtrOutputPin> outputPins() override;
    // Получение выходных пинов (константный вариант)
    QVector<ShPtrConstOutputPin> outputPins() const override;

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

    // Получение количества байтов
    [[nodiscard]]
    qint32 byteCount() const { return byteCount_; }
    // Задание количества байтов
    void setByteCount(qint32 count);
    // Сброс количества байтов
    void resetByteCount();
    // Получение признака изменения количества байтов
    [[nodiscard]]
    bool isByteCountChanged() const { return byteCount_ != 0; }

    // Получение байта для заполнения
    [[nodiscard]]
    quint8 filledByte() const { return filledByte_; }
    // Задание байта для заполнения
    void setFilledByte(quint8 byte);
    // Сброс байта для заполнения
    void resetFilledByte();
    // Функция для проверки изменения байта заполнения
    [[nodiscard]]
    bool isFilledByteChanged() const { return filledByte_ != 0; }

    // Получение значения типа Bool
    [[nodiscard]]
    bool boolValue() const { return boolValue_; }
    // Задание значения типа Bool
    void setBoolValue(bool value);
    // Сброс значения типа Bool
    void resetBoolValue();
    // Получение признака изменения типа Bool
    [[nodiscard]]
    bool isBoolValueChanged() const { return boolValue_; }

    // Получение значения типа Int8
    [[nodiscard]]
    qint8 int8Value() const { return int8Value_; }
    // Задание значения типа Int8
    void setInt8Value(qint8 value);
    // Сброс значения типа Int8
    void resetInt8Value();
    // Получение признака изменения значения типа Int8
    [[nodiscard]]
    bool isInt8ValueChanged() const { return int8Value_ != 0; }

    // Получение значения типа UInt8
    [[nodiscard]]
    quint8 uint8Value() const { return uint8Value_; }
    // Задание значения типа UInt8
    void setUInt8Value(quint8 value);
    // Сброс значения типа UInt8
    void resetUInt8Value();
    // Получение признака изменения типа UInt8
    [[nodiscard]]
    bool isUInt8ValueChanged() const { return uint8Value_ != 0; }

    // Получение значения типа Int16
    [[nodiscard]]
    qint16 int16Value() const { return int16Value_; }
    // Задание значения типа Int16
    void setInt16Value(qint16 value);
    // Сброс значения типа Int16
    void resetInt16Value();
    // Получение признака изменения значения типа Int16
    [[nodiscard]]
    bool isInt16ValueChanged() const { return int16Value_ != 0; }

    // Получение значения типа UInt16
    [[nodiscard]]
    quint16 uint16Value() const { return uint16Value_; }
    // Задание значения типа quint16
    void setUInt16Value(quint16 value);
    // Сброс значения типа quint16
    void resetUInt16Value();
    // Получение признака изменения значения quint16
    [[nodiscard]]
    bool isUInt16ValueChanged() const { return uint16Value_ != 0; }

    // Получение значения типа qint32
    [[nodiscard]]
    qint32 int32Value() const { return int32Value_; }
    // Задание значения типа qint32
    void setInt32Value(qint32 value);
    // Сброс значения типа Int32
    void resetInt32Value();
    // Получение признака изменения значения Int32
    [[nodiscard]]
    bool isInt32ValueChanged() const { return int32Value_ != 0; }

    // Получение значения типа UInt32
    [[nodiscard]]
    quint32 uint32Value() const { return uint32Value_; }
    // Задание значения типа UInt32
    void setUInt32Value(quint32 value);
    // Сброс значения типа UInt32
    void resetUInt32Value();
    // Получение признака изменения типа UInt32
    [[nodiscard]]
    bool isUInt32ValueChanged() const { return uint32Value_ != 0; }

    // Получение значения типа Int64
    [[nodiscard]]
    qint64 int64Value() const { return uint64Value_; }
    // Задание значения типа Int64
    void setInt64Value(const qint64 &value);
    // Сброс признака значения типа Int64
    void resetInt64Value();
    // Получение признака изменения значения типа Int64
    [[nodiscard]]
    bool isInt64ValueChanged() const { return int64Value_ != 0; }

    // Получение значения типа UInt64
    [[nodiscard]]
    quint64 uint64Value() const { return uint64Value_; }
    // Задание значения типа UInt64
    void setUInt64Value(const quint64 &value);
    // Сброс значения типа UInt64
    void resetUInt64Value();
    // Получение признака изменения значения типа UInt64
    [[nodiscard]]
    bool isUInt64ValueChanged() const { return uint64Value_ != 0; }

    // Получение значения типа Float
    [[nodiscard]]
    float floatValue() const { return floatValue_; }
    // Задание значения типа Float
    void setFloatValue(float value);
    // Сброс значения типа Float
    void resetFloatValue();
    // Получение признака изменения значения типа Float
    [[nodiscard]]
    bool isFloatValueChanged() const { return floatValue_ != 0; }

    // Получение значения типа Double
    [[nodiscard]]
    double doubleValue() const { return doubleValue_; }
    // Задание значения типа Double
    void setDoubleValue(const double &value);
    // Сброс значения типа double
    void resetDoubleValue();
    // Получение признака изменения значения типа Double
    [[nodiscard]]
    bool isDoubleValueChanged() const { return doubleValue_ != 0; }

    // Получение значения типа String
    [[nodiscard]]
    QString strValue() const { return strValue_; }
    // Задание значения типа String
    void setStrValue(const QString &value);
    // Сброс значения типа String
    void resetStrValue();
    // Получение признака изменения значения типа String
    [[nodiscard]]
    bool isStrValueChanged() const { return !strValue_.isEmpty(); }

    // Получение значения типа Color
    [[nodiscard]]
    QColor colorValue() const { return colorValue_; }
    // Задание значения типа Color
    void setColorValue(const QColor &value);
    // Сброс значения типа Color
    void resetColorValue();
    // Получение признака изменения значения типа Color
    [[nodiscard]]
    bool isColorValueChanged() const { return colorValue_ != Qt::black; }

    // Виртуальная функция получения имени свойства из графического
    // интерфейса по его системному имени
    QString getUiPropertyName(const QString &systemName) override;
private slots:
    // Функция вызывается при подключении выходного пина
    void slotOutputPinConnectChanged(ConnectStates state, InputPin *pin);
private:
    // Создание выходного пина
    void createOutputPin();
    // Получение количества данных по типу
    [[nodiscard]]
    qint32 byteCountForGenerateType() const;
    // Вывод комментариев
    void drawComments(QPainter *painter) const;
    // Получение строки со значением для текстовой подсказки
    [[nodiscard]]
    QString valueStrForTooltip() const;
    // Получение случайного значения по индексу
    [[nodiscard]]
    static quint8 randValue(qint32 index);
    // Обновление состояния узла
    void updateStateInfo();
    // Получение строки со значением для комментария
    [[nodiscard]]
    QString valueStrForComments() const;

    //----------------------------------------------------------
    // Чтение значений из XML
    //----------------------------------------------------------
    // Чтение типа значения из XML
    [[nodiscard]]
    GenerateTypes readGenerateTypeFromXml(const QDomElement &elem) const;
    // Чтение значения из XML в зависимости от текущего типа генерации
    [[nodiscard]]
    QVariant readValueFromXml(const QDomElement &elem) const;
    // Чтение количества генерируемых байтов из XML
    [[nodiscard]]
    int readByteCountFromXml(const QDomElement &elem) const;
    // Чтение байта для заполнения из XML
    [[nodiscard]]
    quint8 readFilledByteFromXml(const QDomElement &elem) const;
    // Чтение значения bool из XML
    [[nodiscard]]
    bool readBoolValueFromXml(const QDomElement &elem) const;
    // Чтение значения qint8 из XML
    [[nodiscard]]
    qint8 readInt8ValueFromXml(const QDomElement &elem) const;
    // Чтение значения quint8 из XML
    [[nodiscard]]
    quint8 readUInt8ValueFromXml(const QDomElement &elem) const;
    // Чтение значения qint16 из XML
    [[nodiscard]]
    qint16 readInt16ValueFromXml(const QDomElement &elem) const;
    // Чтение значения quint16 из XML
    [[nodiscard]]
    quint16 readUInt16ValueFromXml(const QDomElement &elem) const;
    // Чтение значения qint32 из XML
    [[nodiscard]]
    qint32 readInt32ValueFromXml(const QDomElement &elem) const;
    // Чтение значения quint32 из XML
    [[nodiscard]]
    quint32 readUInt32ValueFromXml(const QDomElement &elem) const;
    // Чтение значения qint64 из XML
    [[nodiscard]]
    qint64 readInt64ValueFromXml(const QDomElement &elem) const;
    // Чтение значения quint64 из XML
    [[nodiscard]]
    quint64 readUInt64ValueFromXml(const QDomElement &elem) const;
    // Чтение значения float из XML
    [[nodiscard]]
    float readFloatValueFromXml(const QDomElement &elem) const;
    // Чтение значения double из XML
    [[nodiscard]]
    double readDoubleValueFromXml(const QDomElement &elem) const;
    // Чтение значения QColor из XML
    [[nodiscard]]
    QColor readColorValueFromXml(const QDomElement &elem) const;
    // Чтение значения QString из XML
    [[nodiscard]]
    QString readStrValueFromXml(const QDomElement &elem) const;

    //----------------------------------------------------------
    // Запись значений в XML
    //----------------------------------------------------------
    // Запись типа генерации в XML
    void writeGenerateTypeToXml(QDomDocument &doc, QDomElement &elem) const;
    // Запись количества генерируемых байт в XML
    void writeByteCountToXml(QDomDocument &doc, QDomElement &elem) const;
    // Запись байта для заполнения в XML
    void writeFilledByteToXml(QDomDocument &doc, QDomElement &elem) const;
    // Запись значения в записимости от типа генерации в XML
    void writeValueToXml(QDomDocument &doc, QDomElement &elem) const;
    // Запись значения bool в XML
    void writeBoolValueToXml(QDomDocument &doc, QDomElement &elem) const;
    // Запись значения qint8 в XML
    void writeInt8ValueToXml(QDomDocument &doc, QDomElement &elem) const;
    // Запись значения quint8 в XML
    void writeUInt8ValueToXml(QDomDocument &doc, QDomElement &elem) const;
    // Запись значения qint16 в XML
    void writeInt16ValueToXml(QDomDocument &doc, QDomElement &elem) const;
    // Запись значения quint16 в XML
    void writeUInt16ValueToXml(QDomDocument &doc, QDomElement &elem) const;
    // Запись значения qint32 в XML
    void writeInt32ValueToXml(QDomDocument &doc, QDomElement &elem) const;
    // Запись значения quint32 в XML
    void writeUInt32ValueToXml(QDomDocument &doc, QDomElement &elem) const;
    // Запись значения qint64 в XML
    void writeInt64ValueToXml(QDomDocument &doc, QDomElement &elem) const;
    // Запись значения quint64 в XML
    void writeUInt64ValueToXml(QDomDocument &doc, QDomElement &elem) const;
    // Запись значения float в XML
    void writeFloatValueToXml(QDomDocument &doc, QDomElement &elem) const;
    // Запись значения double в XML
    void writeDoubleValueToXml(QDomDocument &doc, QDomElement &elem) const;
    // Запись значения QString в XML
    void writeStrValueToXml(QDomDocument &doc, QDomElement &elem) const;
    // Запись значения QColor в XML
    void writeColorValueToXml(QDomDocument &doc, QDomElement &elem) const;

    // Представление байта в виде шестнадцатиричной строки
    static QString dataToHexStr(quint32 data, int fieldWidth);

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
    // Выходной пин
    ShPtrOutputPin outputPin_{nullptr};
};

//==============================================================
using ShPtrGenerateNode = QSharedPointer<GenerateNode>;
using ShPtrConstGenerateNode = QSharedPointer<const GenerateNode>;

//==============================================================
#endif // GENERATE_NODE_H
