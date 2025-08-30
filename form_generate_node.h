////////////////////////////////////////////////////////////////
// ByteMachine
// Виджет для настройки узла "Generate"
////////////////////////////////////////////////////////////////
#ifndef FORM_GENERATE_NODE_H
#define FORM_GENERATE_NODE_H

//==============================================================
#include <QWidget>
#include "ui_form_generate_node.h"
#include "prop_value.h"
#include "generate_types.h"

//==============================================================
namespace Ui
{
    class FormGenerateNode;
}
class GenerateNode;

//==============================================================
// Виджет для настройки узла "Generate"
//==============================================================
class FormGenerateNode : public QWidget
{
    Q_OBJECT
public:
    // Конструктор с параметром
    explicit FormGenerateNode(GenerateNode *node,
        QWidget *parent = nullptr);
    // Деструктор
    ~FormGenerateNode() override;
private slots:
    // Функция вызывается при изменении свойств узла
    void slotChangedNodeProp(PropValue value);
    // Функция вызывается при завершении редактирования имени
    void slotEditingFinishedName();
    // Функция вызывается при изменении типа генерации
    void slotChangedGenerateType(int index);
    // Сброс типа генерации
    void slotResetGenerateType();
    // Задание количества байтов
    void slotChangedByteCount(int count);
    // Сброс количества байтов
    void slotResetCount();
    // Задание заполняющего байта
    void slotChangedFilledByte(int value);
    // Сброс заполняющего байта
    void slotResetFilledByte();
    // Функция вызывается при изменении булевого значения
    void slotChangedBoolValue(int value);
    // Сброс булевого значения
    void slotResetBoolValue();
    // Функция вызывается при изменении целого значения
    void slotChangedIntValue(int value);
    // Сброс целочисленного значения
    void slotResetIntValue();
    // Функция вызывается при изменении дробного значения
    void slotChangedDoubleValue(double value);
    // Сброс дробного значения
    void slotResetDoubleValue();
    // Функция вызывается при изменении значения цвета
    void slotChangedColorValue(const QColor &color);
    // Функция вызывается при изменении строки
    void slotChangedStrValue();
    // Сброс строкового значения
    void slotResetStrValue();
    // Сброс значения цвета
    void slotResetColorValue();
    // Функция вызывается при завершении редактирования комментария
    void slotEditingFinishedComment();
    // Сброс комментария
    void slotResetComment();
private:
    // Задание узла
    void setNode(GenerateNode *node);
    // Задание соединений
    void setConnections();

    // Получение типа генерации
    GenerateTypes generateType() const;
    // Задание типа генерации
    void setGenerateType(GenerateTypes type);
    // Задание типа генерации Usual
    void setGenerateTypeUsual();
    // Задание типа генерации Random
    void setGenerateTypeRandom();
    // Задание типа генерации Bool
    void setGenerateTypeBool();
    // Задание типа генерации Int8
    void setGenerateTypeInt8();
    // Задание типа генерации UInt8
    void setGenerateTypeUInt8();
    // Задание типа генерации Int16
    void setGenerateTypeInt16();
    // Задание типа генерации UInt16
    void setGenerateTypeUInt16();
    // Задание типа генерации Int32
    void setGenerateTypeInt32();
    // Задание типа генерации UInt32
    void setGenerateTypeUInt32();
    // Задание типа генерации Int64
    void setGenerateTypeInt64();
    // Задание типа генерации UInt64
    void setGenerateTypeUInt64();
    // Задание типа генерации Float
    void setGenerateTypeFloat();
    // Задание типа генерации Double
    void setGenerateTypeDouble();
    // Задание типа генерации String
    void setGenerateTypeStr();
    // Задание типа генерации QColor
    void setGenerateTypeColor();

    // Интерфейс пользователя
    Ui::FormGenerateNode ui_{};
    // Узел
    GenerateNode *node_{nullptr};
};

//==============================================================
#endif // FORM_GENERATE_NODE_H
