/////////////////////////////////////////////////////////////////////
// ByteMachine
// Выходной пин узла
/////////////////////////////////////////////////////////////////////
#ifndef OUTPUT_PIN_H
#define OUTPUT_PIN_H

//===================================================================
#include "base_pin.h"
#include "connect_states.h"
#include "pin_connection.h"

//===================================================================
class InputPin;

//===================================================================
// Выходной пин
//===================================================================
class OutputPin : public BasePin
{
    Q_OBJECT
public:
    // Конструктор с параметром
    explicit OutputPin(BaseNode *parentNode, int index);
    // Деструктор
    ~OutputPin() override;

    // Чтение из XML
    void readFromXml(const QDomElement &elem) override;
    // Запись в XML
    void writeToXml(QDomDocument &doc, QDomElement &elem) const override;

    // Получение области пина
    QRect rect() const override;
    // Получение представления в виде строки
    QString toStr() const override;
    // Получение входных пинов
    QVector<QSharedPointer<InputPin>> inputPins();
    // Получение входных пинов (константный вариант)
    QVector<QSharedPointer<const InputPin>> inputPins() const;
    // Получение количества подключенных входных пинов
    int inputPinCount() const;
    // Получение признака подключения
    bool isConnected() const override;
    // Проверка наличия подключенного входного пина
    bool containsInputPin(const QSharedPointer<const InputPin> &pin) const;
    // Проверка наличия подключенного входного пина (2 вариант)
    bool containsInputPin(const InputPin *pin) const;
    // Добавление входного пина
    void addInputPin(const QSharedPointer<InputPin> &pin);
    // Удаление входного пина
    void removeInputPin(const QSharedPointer<const InputPin> &pin,
                        bool isRaiseSignal = true);
    // Удаление входного пина (сырые указатели)
    void removeInputPin(const InputPin *pin, bool isRaiseSignal = true);

    // Получение размера данных
    qint32 dataSize() const override;
    // Получение байта данных
    quint8 dataByte(qint32 index) const override;
    // Получение блока данных
    QVector<quint8> dataBlock(qint32 index, qint32 count) const override;
    // Функция вызывается при изменении данных родительского узла
    void dataChanged() override;
signals:
    // Сигнал возникает при изменении состояния подключения
    void sigConnectChanged(ConnectStates state, InputPin *pin);
private:
    // Запись индекса в XML
    void writeIndexToXml(QDomDocument &doc, QDomElement &elem) const;
    // Запись подключенных входных пинов
    void writeInputPinsToXml(QDomDocument &doc, QDomElement &elem) const;

    // Подключенные входные пины
    QVector<QSharedPointer<InputPin>> inputPins_{};
    // Подключения входных пинов (используется при чтении
    // из XML для последующей корректировки связи)
    QVector<PinConnection> inputPinConnections_{};
};

//===================================================================
using ShPtrOutputPin = QSharedPointer<OutputPin>;
using ShPtrConstOutputPin = QSharedPointer<const OutputPin>;

//===================================================================
#endif // OUTPUT_PIN_H
