/////////////////////////////////////////////////////////////////////
// ByteMachine
// Входной пин
/////////////////////////////////////////////////////////////////////
#ifndef INPUT_PIN_H
#define INPUT_PIN_H

//===================================================================
#include "base_pin.h"
#include "connect_states.h"
#include "pin_connection.h"

//===================================================================
class BaseNode;
class OutputPin;

//===================================================================
// Входной пин
//===================================================================
class InputPin : public BasePin
{
    Q_OBJECT
public:
    // Конструктор с параметром
    explicit InputPin(BaseNode *parentNode, int index);
    // Деструктор
    ~InputPin() override;

    // Чтение из XML
    void readFromXml(const QDomElement &elem) override;
    // Запись в XML
    void writeToXml(QDomDocument &doc, QDomElement &elem) const override;

    // Получение признака подключения
    bool isConnected() const override;
    // Получение области пина
    QRect rect() const override;
    // Получение представления в виде строки
    QString toStr() const override;
    // Получение подключенного выходного пина
    QSharedPointer<OutputPin>& outputPin();
    // Получение подключенного выходного пина (константный вариант)
    QSharedPointer<const OutputPin> outputPin() const;
    // Задание подключенного выходного пина
    void setOutputPin(const QSharedPointer<OutputPin> &pin,
                      bool isRaiseSignal = true);
    // Корректировка соединений (используется при чтении
    // из XML для последующей корректировки связи)
    void correctConnections(QVector<QSharedPointer<BaseNode>> &nodes);

    // Получение размера данных
    qint32 dataSize() const override;
    // Получение байта данных
    quint8 dataByte(qint32 index) const override;
    // Получение блока данных
    QVector<quint8> dataBlock(qint32 index, qint32 count) const override;
    // Функция вызывается при изменении данных родительского узла
    void dataChanged() override;
signals:
    // Сигнал возникает при изменении подключения
    void sigConnectChanged(ConnectStates state, OutputPin *pin);
private:
    // Запись индекса в XML
    void writeIndexToXml(QDomDocument &, QDomElement &elem) const;
    // Запись подключенного выходного пина
    void writeOutputPinToXml(QDomDocument &doc, QDomElement &elem) const;

    // Подключенный выходной пин
    QSharedPointer<OutputPin> outputPin_{};
    // Подключение выходного пина (используется при чтении
    // из XML для последующей корректировки связи)
    PinConnection outputPinConnection_{};
};

//===================================================================
using ShPtrInputPin = QSharedPointer<InputPin>;
using ShPtrConstInputPin = QSharedPointer<const InputPin>;

//===================================================================
#endif // INPUT_PIN_H
