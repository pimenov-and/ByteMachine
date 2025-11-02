////////////////////////////////////////////////////////////////
// ByteMachine
// Узел для показа размера данных
////////////////////////////////////////////////////////////////
#ifndef SIZE_NODE_H
#define SIZE_NODE_H

//==============================================================
#include "base_node.h"
#include "size_units.h"

//==============================================================
class QUndoStack;

//==============================================================
// Узел для показа размера данных
//==============================================================
class SizeNode final : public BaseNode
{
    Q_OBJECT
    Q_PROPERTY(SizeUnits unit READ unit WRITE setUnit RESET resetUnit)
    Q_PROPERTY(bool bypass READ isBypass WRITE setBypass RESET resetBypass)
public:
    // Конструктор с параметром
    explicit SizeNode(QUndoStack *undoStack, QObject *parent = nullptr);
    // Деструктор
    ~SizeNode();

    // Чтение из XML
    void readFromXml(const QDomElement &elem) override;
    // Запись в XML
    void writeToXml(QDomDocument &doc, QDomElement &elem) const override;

    // Получение входных пинов
    QVector<ShPtrInputPin> inputPins() override;
    // Получение входных пинов (2 вариант)
    QVector<ShPtrConstInputPin> inputPins() const override;
    // Получение выходных пинов
    QVector<ShPtrOutputPin> outputPins() override;
    // Получение выходных пинов (константный вариант)
    QVector<ShPtrConstOutputPin> outputPins() const override;

    // Получение типа узла
    NodeTypes type() const override { return NodeTypes::Size; }
    // Функция вывода
    void draw(QPainter *painter) const override;
    // Получение копии узла
    ShPtrBaseNode clone() const override;
    // Получение текста подсказки
    QString tooltipText() const override;
    // Получение признака изменения размера
    bool isResizeble() const override { return true; }
    // Получение признака того, что узел поддерживает прокрутку
    bool isScrollable() const override { return false; }

    // Получение размера данных
    std::size_t dataSize() const override;
    // Получение байта данных
    quint8 dataByte(std::size_t index) const override;
    // Получение блока данных
    ByteList dataBlock(std::size_t index, std::size_t count) const override;
    // Функция вызывается при изменении данных
    void dataChanged() override;

    // Получение размерности
    [[nodiscard]]
    SizeUnits unit() const { return unit_; }
    // Задание размерности
    void setUnit(SizeUnits unit);
    // Сброс размерности
    void resetUnit();
    // Получение признака изменения размерности
    [[nodiscard]]
    bool isUnitChanged() const { return unit_ != SizeUnits::Byte; }

    // Получение признака пропуска
    [[nodiscard]]
    bool isBypass() const { return isBypass_; }
    // Задание признака пропуска
    void setBypass(bool bypass);
    // Получение признака изменения пропуска
    [[nodiscard]]
    bool isBypassChanged() const { return isBypass_; }
    // Сброс признака пропуска
    void resetBypass();

    // Виртуальная функция получения имени свойства из графического
    // интерфейса по его системному имени
    QString getUiPropertyName(const QString &systemName) override;
private slots:
    // Функция вызывается при подключении входного пина
    void slotInputPinConnectChanged(ConnectStates state, OutputPin *pin);
    // Функция вызывается при подключении выходного пина
    void slotOutputPinConnectChanged(ConnectStates state, InputPin *pin);
private:
    // Вывод основы
    void drawBody(QPainter *painter) const;
    // Вывод комментариев
    void drawComments(QPainter *painter) const;

    // Перевод байтов в килобайты
    [[nodiscard]]
    static double bytesToKilobytes(qint32 count);
    // Перевод байтов в мегабайты
    [[nodiscard]]
    static double bytesToMegabytes(qint32 count);
    // Получение размера данных в виде строки
    [[nodiscard]]
    QString dataSizeToStr() const;

    // Создание входного пина
    void createInputPin();
    // Создание выходного пина
    void createOutputPin();
    // Получение признака подключения входного пина
    [[nodiscard]]
    bool isConnectedInputPin() const;
    // Получение размера входные данных
    [[nodiscard]]
    int inputDataSize() const;

    // Чтение единицы измерения из XML
    [[nodiscard]]
    SizeUnits readUnitFromXml(const QDomElement &elem) const;
    // Запись единицы измерения в XML
    void writeUnitToXml(QDomDocument &doc, QDomElement &elem) const;

    // Обновление состояния узла
    void updateStateInfo();

    // Входной пин
    ShPtrInputPin inputPin_{};
    // Выходной пин
    ShPtrOutputPin outputPin_{};
    // Единицы измерения
    SizeUnits unit_{SizeUnits::Byte};
    // Размеры символа
    static QSize charSize_;
};

//==============================================================
using ShPtrSizeNode = QSharedPointer<SizeNode>;
using ShPtrConstSizeNode = QSharedPointer<SizeNode>;

//==============================================================
#endif // SIZE_NODE_H
