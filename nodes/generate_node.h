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
    Q_PROPERTY(int32_t byteCount READ byteCount WRITE setByteCount RESET resetByteCount)
    Q_PROPERTY(int32_t filledByte READ filledByte WRITE setFilledByte RESET resetFilledByte)
    Q_PROPERTY(bool boolValue READ boolValue WRITE setBoolValue RESET resetBoolValue)
    Q_PROPERTY(int8_t int8Value READ int8Value WRITE setInt8Value RESET resetInt8Value)
    Q_PROPERTY(uint8_t uint8Value READ uint8Value WRITE setUInt8Value RESET resetUInt8Value)
    Q_PROPERTY(int16_t int16Value READ int16Value WRITE setInt16Value RESET resetInt16Value)
    Q_PROPERTY(uint16_t uint16Value READ uint16Value WRITE setUInt16Value RESET resetUInt16Value)
    Q_PROPERTY(int32_t int32Value READ int32Value WRITE setInt32Value RESET resetInt32Value)
    Q_PROPERTY(uint32_t uint32Value READ uint32Value WRITE setUInt32Value RESET resetUInt32Value)
    Q_PROPERTY(int64_t int64Value READ int64Value WRITE setInt64Value RESET resetInt64Value)
    Q_PROPERTY(uint64_t uint64Value READ uint64Value WRITE setUInt64Value RESET resetUInt64Value)
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
    std::size_t dataSize() const override;
    // Получение байта данных
    uint8_t dataByte(std::size_t index) const override;
    // Получение блока данных
    std::deque<uint8_t> dataBlock(std::size_t index,
        std::size_t count) const override;
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
    int32_t byteCount() const { return byteCount_; }
    // Задание количества байтов
    void setByteCount(int32_t count);
    // Сброс количества байтов
    void resetByteCount();
    // Получение признака изменения количества байтов
    [[nodiscard]]
    bool isByteCountChanged() const { return byteCount_ != 0; }

    // Получение байта для заполнения
    [[nodiscard]]
    uint8_t filledByte() const { return filledByte_; }
    // Задание байта для заполнения
    void setFilledByte(uint8_t byte);
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
    int8_t int8Value() const { return int8Value_; }
    // Задание значения типа Int8
    void setInt8Value(int8_t value);
    // Сброс значения типа Int8
    void resetInt8Value();
    // Получение признака изменения значения типа Int8
    [[nodiscard]]
    bool isInt8ValueChanged() const { return int8Value_ != 0; }

    // Получение значения типа UInt8
    [[nodiscard]]
    uint8_t uint8Value() const { return uint8Value_; }
    // Задание значения типа UInt8
    void setUInt8Value(uint8_t value);
    // Сброс значения типа UInt8
    void resetUInt8Value();
    // Получение признака изменения типа UInt8
    [[nodiscard]]
    bool isUInt8ValueChanged() const { return uint8Value_ != 0; }

    // Получение значения типа Int16
    [[nodiscard]]
    int16_t int16Value() const { return int16Value_; }
    // Задание значения типа Int16
    void setInt16Value(int16_t value);
    // Сброс значения типа Int16
    void resetInt16Value();
    // Получение признака изменения значения типа Int16
    [[nodiscard]]
    bool isInt16ValueChanged() const { return int16Value_ != 0; }

    // Получение значения типа UInt16
    [[nodiscard]]
    uint16_t uint16Value() const { return uint16Value_; }
    // Задание значения типа UInt16
    void setUInt16Value(uint16_t value);
    // Сброс значения типа UInt16
    void resetUInt16Value();
    // Получение признака изменения значения UInt16
    [[nodiscard]]
    bool isUInt16ValueChanged() const { return uint16Value_ != 0; }

    // Получение значения типа int32_t
    [[nodiscard]]
    int32_t int32Value() const { return int32Value_; }
    // Задание значения типа int32_t
    void setInt32Value(int32_t value);
    // Сброс значения типа Int32
    void resetInt32Value();
    // Получение признака изменения значения Int32
    [[nodiscard]]
    bool isInt32ValueChanged() const { return int32Value_ != 0; }

    // Получение значения типа UInt32
    [[nodiscard]]
    uint32_t uint32Value() const { return uint32Value_; }
    // Задание значения типа UInt32
    void setUInt32Value(uint32_t value);
    // Сброс значения типа UInt32
    void resetUInt32Value();
    // Получение признака изменения типа UInt32
    [[nodiscard]]
    bool isUInt32ValueChanged() const { return uint32Value_ != 0; }

    // Получение значения типа Int64
    [[nodiscard]]
    int64_t int64Value() const { return uint64Value_; }
    // Задание значения типа Int64
    void setInt64Value(const int64_t &value);
    // Сброс признака значения типа Int64
    void resetInt64Value();
    // Получение признака изменения значения типа Int64
    [[nodiscard]]
    bool isInt64ValueChanged() const { return int64Value_ != 0; }

    // Получение значения типа UInt64
    [[nodiscard]]
    uint64_t uint64Value() const { return uint64Value_; }
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
    int32_t byteCountForGenerateType() const;
    // Вывод комментариев
    void drawComments(QPainter *painter) const;
    // Получение строки со значением для текстовой подсказки
    [[nodiscard]]
    QString valueStrForTooltip() const;
    // Получение случайного значения по индексу
    [[nodiscard]]
    static uint8_t randValue(int32_t index);
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
    uint8_t readFilledByteFromXml(const QDomElement &elem) const;
    // Чтение значения bool из XML
    [[nodiscard]]
    bool readBoolValueFromXml(const QDomElement &elem) const;
    // Чтение значения int8_t из XML
    [[nodiscard]]
    int8_t readInt8ValueFromXml(const QDomElement &elem) const;
    // Чтение значения uint8_t из XML
    [[nodiscard]]
    uint8_t readUInt8ValueFromXml(const QDomElement &elem) const;
    // Чтение значения int16_t из XML
    [[nodiscard]]
    int16_t readInt16ValueFromXml(const QDomElement &elem) const;
    // Чтение значения UInt16 из XML
    [[nodiscard]]
    uint16_t readUInt16ValueFromXml(const QDomElement &elem) const;
    // Чтение значения int32_t из XML
    [[nodiscard]]
    int32_t readInt32ValueFromXml(const QDomElement &elem) const;
    // Чтение значения quint32 из XML
    [[nodiscard]]
    quint32 readUInt32ValueFromXml(const QDomElement &elem) const;
    // Чтение значения int64_t из XML
    [[nodiscard]]
    int64_t readInt64ValueFromXml(const QDomElement &elem) const;
    // Чтение значения uint64_t из XML
    [[nodiscard]]
    uint64_t readUInt64ValueFromXml(const QDomElement &elem) const;
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
    // Запись значения Int8 в XML
    void writeInt8ValueToXml(QDomDocument &doc, QDomElement &elem) const;
    // Запись значения UInt8 в XML
    void writeUInt8ValueToXml(QDomDocument &doc, QDomElement &elem) const;
    // Запись значения Int16 в XML
    void writeInt16ValueToXml(QDomDocument &doc, QDomElement &elem) const;
    // Запись значения UInt16 в XML
    void writeUInt16ValueToXml(QDomDocument &doc, QDomElement &elem) const;
    // Запись значения Int32 в XML
    void writeInt32ValueToXml(QDomDocument &doc, QDomElement &elem) const;
    // Запись значения UInt32 в XML
    void writeUInt32ValueToXml(QDomDocument &doc, QDomElement &elem) const;
    // Запись значения Int64 в XML
    void writeInt64ValueToXml(QDomDocument &doc, QDomElement &elem) const;
    // Запись значения UInt64 в XML
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
    int8_t int8Value_{0};
    // Значение типа UInt8
    uint8_t uint8Value_{0};
    // Значение типа Int16
    int16_t int16Value_{0};
    // Значение типа UInt16
    uint16_t uint16Value_{0};
    // Значение типа Int32
    int32_t int32Value_{0};
    // Значение типа UInt32
    uint32_t uint32Value_{0};
    // Значение типа Int64
    int64_t int64Value_{0};
    // Значение типа UInt64
    uint64_t uint64Value_{0};
    // Значение типа Float
    float floatValue_{0};
    // Значение типа Double
    double doubleValue_{0};
    // Значение тип String
    QString strValue_{};
    // Цвет
    QColor colorValue_{Qt::black};

    // Количество генерируемых байт
    int32_t byteCount_{0};
    // Байт для заполнения
    uint8_t filledByte_{0};
    // Выходной пин
    ShPtrOutputPin outputPin_{nullptr};
};

//==============================================================
using ShPtrGenerateNode = QSharedPointer<GenerateNode>;
using ShPtrConstGenerateNode = QSharedPointer<const GenerateNode>;

//==============================================================
#endif // GENERATE_NODE_H
