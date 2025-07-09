////////////////////////////////////////////////////////////////
// ByteMachine
// Базовый класс узла
////////////////////////////////////////////////////////////////
#ifndef BASE_NODE_H
#define BASE_NODE_H

//==============================================================
#include <QObject>
#include <QPoint>
#include <QSize>
#include <QRect>
#include <QSharedPointer>
#include "node_types.h"
#include "i_data.h"
#include "i_xml.h"
#include "i_to_str.h"
#include "prop_value.h"
#include "input_pin.h"
#include "output_pin.h"

//==============================================================
class QPainter;
class QUndoStack;

//==============================================================
// Базовый класс узла
//==============================================================
class BaseNode : public QObject, public IData, public IXml, public IToStr
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(int left READ left WRITE setLeft)
    Q_PROPERTY(int top READ top WRITE setTop)
    Q_PROPERTY(int width READ width WRITE setWidth)
    Q_PROPERTY(int height READ height WRITE setHeight)
    Q_PROPERTY(QPoint topLeft READ topLeft WRITE setTopLeft)
    Q_PROPERTY(QSize size READ size WRITE setSize)
    Q_PROPERTY(QString comment READ comment WRITE setComment RESET resetComment)
    Q_PROPERTY(bool isUndo READ isUndo WRITE setUndo RESET resetUndo)
public:
    // Конструктор с параметром
    explicit BaseNode(QUndoStack *undoStack = nullptr,
        QObject *parent = nullptr);
    // Деструктор
    ~BaseNode() override;

    // Получение идентификатора
    [[nodiscard]]
    int id() const { return id_; }
    // Получение имени
    [[nodiscard]]
    QString name() const { return name_; }
    // Задание имени
    void setName(const QString &name);
    // Получение комментария
    [[nodiscard]]
    QString comment() const { return comment_; }
    // Задание комментария
    void setComment(const QString &comment);
    // Сброс комментария
    void resetComment();
    // Получение признака изменения комментария
    [[nodiscard]]
    bool isCommentChanged() const { return !comment_.isEmpty(); }

    // Получение типа узла
    [[nodiscard]]
    virtual NodeTypes type() const = 0;
    // Получение типа узла в виде строки
    [[nodiscard]]
    QString strType() const { return nodeTypeToStr(type()); }
    // Получение представления в виде строки
    virtual QString toStr() const override;
    // Функция вывода
    virtual void draw(QPainter *painter) const = 0;
    // Получение копии узла
    [[nodiscard]]
    virtual QSharedPointer<BaseNode> clone() const = 0;
    // Получение текста подсказки
    [[nodiscard]]
    virtual QString tooltipText() const = 0;
    // Получение признака изменения размера
    [[nodiscard]]
    virtual bool isResizeble() const = 0;
    // Получение признака того, что узел поддерживает прокрутку
    [[nodiscard]]
    virtual bool isScrollable() const = 0;

    // Получение стека отмен
    [[nodiscard]]
    QUndoStack* undoStack() { return undoStack_; }
    // Получение стека отмен (константный вариант)
    [[nodiscard]]
    QUndoStack* undoStack() const { return undoStack_; }
    // Задание стека отмен
    void setUndoStack(QUndoStack *undoStack);

    // Получение признака режима отмены
    [[nodiscard]]
    bool isUndo() const { return isUndo_; }
    // Задание признака режима отмены
    void setUndo(bool isUndo);
    // Сброс признака режима отмены
    void resetUndo();
    // Получение признака изменения режима отмены
    [[nodiscard]]
    bool isUndoChanged() const { return isUndo_ == true; }

    //----------------------------------------------------------
    // Положение узла
    //----------------------------------------------------------
    // Получение смещения слева
    [[nodiscard]]
    qint32 left() const noexcept { return left_; }
    // Задание смещения слева
    void setLeft(qint32 left) noexcept;
    // Получение смещения сверху
    [[nodiscard]]
    qint32 top() const noexcept { return top_; }
    // Задание смещения сверху
    void setTop(qint32 top) noexcept;
    // Получение ширины узла
    [[nodiscard]]
    qint32 width() const noexcept { return width_; }
    // Задание ширины узла
    virtual void setWidth(qint32 width);
    // Получение высоты узла
    [[nodiscard]]
    qint32 height() const noexcept { return height_; }
    // Задание высоты узла
    virtual void setHeight(qint32 height);
    // Получение правой границы
    [[nodiscard]]
    qint32 right() const noexcept { return left() + width(); }
    // Получение нижней границы
    [[nodiscard]]
    qint32 bottom() const noexcept { return top_ + height_; }
    // Получение центра
    [[nodiscard]]
    QPoint center() const;
    // Получение левого верхнего угла
    [[nodiscard]]
    QPoint topLeft() const { return QPoint{left_, top_}; }
    // Задание левого верхнего угла
    void setTopLeft(const QPoint &topLeft);
    // Получение размера узла
    QSize size() const { return QSize{width_, height_}; }
    // Задание размера узла
    void setSize(const QSize &size);
    // Получение прямоугольника узла
    QRect rect() const { return QRect{topLeft(), size()}; }

    //----------------------------------------------------------
    // Интерфейс входных пинов
    //----------------------------------------------------------
    // Получение входных пинов
    virtual QVector<ShPtrInputPin> inputPins();
    // Получение входных пинов (константный вариант)
    virtual QVector<ShPtrConstInputPin> inputPins() const;
    // Получение областей входных пинов (константный вариант)
    virtual QVector<QRect> inputPinRects() const;
    // Получение количества входных пинов
    int inputPinCount() const { return inputPins().count(); }
    // Получение входного пина по индексу
    virtual ShPtrInputPin inputPin(int index);
    // Получение входного пина по индексу (константный вариант)
    virtual ShPtrConstInputPin inputPin(int index) const;
    // Получение области входного пина по индексу
    virtual QRect inputPinRect(int index) const;
    // Проверка наличия входного пина
    virtual bool containsInputPin(const ShPtrInputPin &pin) const;
    // Провека наличия выходного пина (константный вариант)
    virtual bool containsInputPin(const InputPin *pin) const;
    // Получение индекса входного пина
    virtual int indexOfInputPin(const ShPtrInputPin &pin) const;
    // Получение индекса входного пина (сырой указатель)
    virtual int indexOfInputPin(const InputPin *pin) const;

    //----------------------------------------------------------
    // Интерфейс выходных пинов
    //----------------------------------------------------------
    // Получение выходных пинов
    virtual QVector<ShPtrOutputPin> outputPins();
    // Получение выходных пинов (константный вариант)
    virtual QVector<ShPtrConstOutputPin> outputPins() const;
    // Получение областей выходных пинов
    virtual QVector<QRect> ouputPinRects() const;
    // Получение количества выходных пинов
    int outputPinCount() const { return outputPins().count(); }
    // Получение выходного пина по индексу
    virtual ShPtrOutputPin outputPin(int index);
    // Получение выходного пина по индексу (константный вариант)
    virtual ShPtrConstOutputPin outputPin(int index) const;
    // Получение области выходного пина по индексу
    virtual QRect outputPinRect(int index) const;
    // Проверка наличия выходного пина
    virtual bool containsOutputPin(const ShPtrOutputPin &pin) const;
    // Проверка наличия выходного пина (сырые указатели)
    virtual bool containsOutputPin(const OutputPin *pin) const;
    // Получение индекса выходного пина
    virtual int indexOfOutputPin(const ShPtrOutputPin &pin) const;
    // Получение индекса выходного пина (сырой указатель)
    virtual int indexOfOutputPin(const OutputPin *pin) const;
signals:
    // Сигнал возникает при изменении узла
    void sigChangedProp(PropValue value);
protected:
    // Рисование примитивной основы
    void drawSimpleBody(QPainter *painter) const;

    // Имя
    QString name_{};
    // Признак режима отмены
    bool isUndo_{false};
    // Стек отмен
    QUndoStack *undoStack_{nullptr};
private:
    // Идентификатор
    qint32 id_{0};
    // Смещение слева
    qint32 left_{20};
    // Смещение сверху
    qint32 top_{20};
    // Ширина
    qint32 width_{100};
    // Высота
    qint32 height_{40};
    // Выделение
    bool isSelected_{false};
    // Комментарий
    QString comment_{};

    // Максимальная ширина
    static const int maxWidth_{500};
    // Максимальная высота
    static const int maxHeight_{480};
    // Тип комментариев
    static bool isCommentsVisible_;
};

//==============================================================
using ShPtrBaseNode = QSharedPointer<BaseNode>;
using ShPtrConstBaseNode = QSharedPointer<const BaseNode>;

//==============================================================
// Прототипы функций
//==============================================================

//==============================================================
#endif // BASE_NODE_H
