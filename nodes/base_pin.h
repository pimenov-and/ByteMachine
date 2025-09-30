////////////////////////////////////////////////////////////////
// ByteMachine
// Базовый класс пина
////////////////////////////////////////////////////////////////
#ifndef BASE_PIN_H
#define BASE_PIN_H

//==============================================================
#include <QObject>
#include <QSharedPointer>
#include "i_data.h"
#include "i_xml.h"
#include "i_to_str.h"

//==============================================================
class BaseNode;

//==============================================================
// Базовый класс пина
//==============================================================
class BasePin : public QObject, public IData, public IXml, public IToStr
{
    Q_OBJECT
public:
    // Конструктор с параметрами
    BasePin(BaseNode *parentNode, int32_t index);

    // Получение признака подключения
    [[nodiscard]]
    virtual bool isConnected() const = 0;
    // Получение области пина
    [[nodiscard]]
    virtual QRect rect() const = 0;
    // Получение родительского узла
    [[nodiscard]]
    BaseNode* parentNode() const { return parentNode_; }
    // Индекс пина в узле
    [[nodiscard]]
    int32_t index() const { return index_; }
    // Получение ширины
    [[nodiscard]]
    static int32_t width() { return 20; }
    // Получение высоты
    [[nodiscard]]
    static int32_t height() { return 10; }
private:
    // Родительский узел
    BaseNode *parentNode_{nullptr};
    // Индекс пина в узле
    int32_t index_{0};
};

//==============================================================
using ShPtrBasePin = QSharedPointer<BasePin>;
using ShPtrConstBasePin = QSharedPointer<const BasePin>;

//==============================================================
#endif // BASE_PIN_H
