////////////////////////////////////////////////////////////////
// ByteMachine
// Виджет для настройки узла "Generate"
////////////////////////////////////////////////////////////////
#include "form_generate_node.h"
#include "generate_node.h"
#include "byte_convert.h"
#include <limits>

//==============================================================
using std::numeric_limits;

//==============================================================
// Конструктор с параметром
//==============================================================
FormGenerateNode::FormGenerateNode(GenerateNode *node, QWidget *parent) :
    QWidget{parent}
{
    Q_ASSERT(node != nullptr);

    ui_.setupUi(this);

    setNode(node);
    setConnections();
}

//==============================================================
// Деструктор
//==============================================================
FormGenerateNode::~FormGenerateNode()
{
}

//==============================================================
// Функция вызывается при изменении свойств узла
//==============================================================
void FormGenerateNode::slotChangedNodeProp(PropValue value)
{
    // Имя
    if (value.name == "name")
    {
        const QString name = node_->name();
        ui_.lineEditName_->setText(name);
        ui_.lineEditName_->setToolTip(name);
    }
    // Тип генерации
    else if (value.name == "generateType")
    {
        const GenerateTypes type = node_->generateType();
        Q_ASSERT(!isUnknown(type));
        const int index = generateTypeToInt(type);
        Q_ASSERT(index != -1);
        ui_.comboBoxGenerateType_->setCurrentIndex(index);

        const bool isTypeChanged = node_->isGenerateTypeChanged();
        ui_.pushBtnResetGenerateType_->setEnabled(isTypeChanged);
    }
    // Количество генерируемых байтов
    else if (value.name == "byteCount")
    {
        const int count = node_->byteCount();
        ui_.spinBoxByteCount_->setValue(count);

        const bool isCountChanged = node_->isByteCountChanged();
        ui_.pushBtnResetByteCount_->setEnabled(isCountChanged);
    }
    // Заполняющий байт
    else if (value.name == "filledByte")
    {
        const quint8 filledByte = node_->filledByte();
        ui_.spinBoxFilledByte_->setValue(filledByte);

        const bool isFilledByte = node_->isFilledByteChanged();
        ui_.pushBtnResetFilledByte_->setEnabled(isFilledByte);
    }
    // Значение Bool
    else if (value.name == "boolValue")
    {
        const bool v = node_->boolValue();
        ui_.checkBoxBoolValue_->setChecked(v);

        const bool isValueChanged = node_->isBoolValueChanged();
        ui_.pushBtnResetBoolValue_->setEnabled(isValueChanged);
    }
    // Значение Int8
    else if (value.name == "int8Value")
    {
        const int v = static_cast<int>(node_->int8Value());
        ui_.spinBoxIntValue_->setValue(v);

        const bool isValueChanged = node_->isInt8ValueChanged();
        ui_.pushBtnResetIntValue_->setEnabled(isValueChanged);
    }
    // Значение UInt8
    else if (value.name == "uint8Value")
    {
        const int v = static_cast<int>(node_->uint8Value());
        ui_.spinBoxIntValue_->setValue(v);

        const bool isChanged = node_->isUInt8ValueChanged();
        ui_.pushBtnResetIntValue_->setEnabled(isChanged);
    }
    // Значение Int16
    else if (value.name == "int16Value")
    {
        const int v = static_cast<int>(node_->int16Value());
        ui_.spinBoxIntValue_->setValue(v);

        const bool isValueChanged = node_->isInt16ValueChanged();
        ui_.pushBtnResetIntValue_->setEnabled(isValueChanged);
    }
    // Значение UInt16
    else if (value.name == "uint16Value")
    {
        const int v = static_cast<int>(node_->uint16Value());
        ui_.spinBoxIntValue_->setValue(v);

        const bool isValueChanged = node_->isUInt16ValueChanged();
        ui_.pushBtnResetIntValue_->setEnabled(isValueChanged);
    }
    // Значение Int32
    else if (value.name == "int32Value")
    {
        const int v = node_->int32Value();
        ui_.spinBoxIntValue_->setValue(v);

        const bool isValueChanged = node_->isInt32ValueChanged();
        ui_.pushBtnResetIntValue_->setEnabled(isValueChanged);
    }
    // Значение UInt32
    else if (value.name == "uint32Value")
    {
        const int v = static_cast<int>(node_->uint32Value());
        ui_.spinBoxIntValue_->setValue(v);

        const bool isValueChanged = node_->isUInt32ValueChanged();
        ui_.pushBtnResetIntValue_->setEnabled(isValueChanged);
    }
    // Значение Int64
    else if (value.name == "int64Value")
    {
        const int v = static_cast<int>(node_->int64Value());
        ui_.spinBoxIntValue_->setValue(v);

        const bool isValueChanged = node_->isInt64ValueChanged();
        ui_.pushBtnResetIntValue_->setEnabled(isValueChanged);
    }
    // Значение UInt64
    else if (value.name == "uint64Value")
    {
        const int v = static_cast<int>(node_->uint64Value());
        ui_.spinBoxIntValue_->setValue(v);

        const bool isValueChanged = node_->isUInt64ValueChanged();
        ui_.pushBtnResetIntValue_->setEnabled(isValueChanged);
    }
    // Значение Float
    else if (value.name == "floatValue")
    {
        const double v = static_cast<double>(node_->floatValue());
        ui_.doubleSpinBoxDoubleValue_->setValue(v);

        const bool isValueChanged = node_->isFloatValueChanged();
        ui_.pushBtnResetDoubleValue_->setEnabled(isValueChanged);
    }
    // Значение Double
    else if (value.name == "doubleValue")
    {
        const double v = node_->doubleValue();
        ui_.doubleSpinBoxDoubleValue_->setValue(v);

        const bool isValueChanged = node_->isDoubleValueChanged();
        ui_.pushBtnResetDoubleValue_->setEnabled(isValueChanged);
    }
    // Значение строки
    else if (value.name == "strValue")
    {
        const QString v = node_->strValue();
        if (ui_.plainTextEditStrValue_->toPlainText() != v)
        {
            ui_.plainTextEditStrValue_->setPlainText(v);
        }

        const bool isValueChanged = node_->isStrValueChanged();
        ui_.pushBtnResetStrValue_->setEnabled(isValueChanged);

        // const int valueByteCount = getValueByteSize(v);
        // ui_.spinBoxByteCount_->setValue(valueByteCount);
    }
    // Значение цвета
    else if (value.name == "colorValue")
    {
        const QColor &color = node_->colorValue();
        ui_.widgetColorValue_->setColor(color);

        const bool isColorChanged = node_->isColorValueChanged();
        ui_.pushBtnResetColorValue_->setEnabled(isColorChanged);
    }
    // Комментарий
    else if (value.name == "comment")
    {
        const QString comment = node_->comment();
        ui_.lineEditComment_->setText(comment);
        ui_.lineEditComment_->setToolTip(comment);

        const bool isCommentChanged = node_->isCommentChanged();
        ui_.pushBtnResetComment_->setEnabled(isCommentChanged);
    }
}

//==============================================================
// Функция вызывается при завершении редактирования имени
//==============================================================
void FormGenerateNode::slotEditingFinishedName()
{
    const QString name = ui_.lineEditName_->text();
    node_->setName(name);
}

//==============================================================
// Функция вызывается при изменении типа генерации
//==============================================================
void FormGenerateNode::slotChangedGenerateType(int index)
{
    if (index == -1)
    {
        return;
    }

    const GenerateTypes type = intToGenerateType(index);
    Q_ASSERT(!isUnknown(type));
    node_->setGenerateType(type);
    switch (type)
    {
        case GenerateTypes::Usual:
        {
            setGenerateTypeUsual();
            break;
        }
        case GenerateTypes::Random:
        {
            setGenerateTypeRandom();
            break;
        }
        case GenerateTypes::Bool:
        {
            setGenerateTypeBool();
            break;
        }
        case GenerateTypes::Int8:
        {
            setGenerateTypeInt8();
            break;
        }
        case GenerateTypes::UInt8:
        {
            setGenerateTypeUInt8();
            break;
        }
        case GenerateTypes::Int16:
        {
            setGenerateTypeInt16();
            break;
        }
        case GenerateTypes::UInt16:
        {
            setGenerateTypeUInt16();
            break;
        }
        case GenerateTypes::Int32:
        {
            setGenerateTypeInt32();
            break;
        }
        case GenerateTypes::UInt32:
        {
            setGenerateTypeUInt32();
            break;
        }
        case GenerateTypes::Int64:
        {
            setGenerateTypeInt64();
            break;
        }
        case GenerateTypes::UInt64:
        {
            setGenerateTypeUInt64();
            break;
        }
        case GenerateTypes::Float:
        {
            setGenerateTypeFloat();
            break;
        }
        case GenerateTypes::Double:
        {
            setGenerateTypeDouble();
            break;
        }
        case GenerateTypes::String:
        {
            setGenerateTypeStr();
            break;
        }
        case GenerateTypes::Color:
        {
            setGenerateTypeColor();
            break;
        }
        default:
        {
            qDebug() << "Bad generate type";
            break;
        }
    }
    highlightByteCountWidget();
}

//==============================================================
// Сброс типа генерации
//==============================================================
void FormGenerateNode::slotResetGenerateType()
{
    node_->resetGenerateType();

    ui_.comboBoxGenerateType_->setFocus();
}

//==============================================================
// Задание количества байтов
//==============================================================
void FormGenerateNode::slotChangedByteCount(int count)
{
    node_->setByteCount(count);
    highlightByteCountWidget();
}

//==============================================================
// Сброс количества байтов
//==============================================================
void FormGenerateNode::slotResetCount()
{
    node_->resetByteCount();

    ui_.spinBoxByteCount_->setFocus();
}

//==============================================================
// Задание заполняющего байта
//==============================================================
void FormGenerateNode::slotChangedFilledByte(int value)
{
    node_->setFilledByte(value);
}

//==============================================================
// Сброс заполняющего байта
//==============================================================
void FormGenerateNode::slotResetFilledByte()
{
    node_->resetFilledByte();

    ui_.spinBoxFilledByte_->setFocus();
}

//==============================================================
// Функция вызывается при изменении целого значения
//==============================================================
void FormGenerateNode::slotChangedBoolValue(int value)
{
    Q_ASSERT(isBool(generateType()));

    node_->setBoolValue(static_cast<bool>(value));
}

//==============================================================
// Сброс целочисленного значения
//==============================================================
void FormGenerateNode::slotResetBoolValue()
{
    node_->resetBoolValue();

    ui_.checkBoxBoolValue_->setFocus();
}

//==============================================================
// Функция вызывается при изменении целого значения
//==============================================================
void FormGenerateNode::slotChangedIntValue(int value)
{
    const GenerateTypes type = generateType();
    switch (type)
    {
        case GenerateTypes::Int8:
        {
            const qint8 v = static_cast<qint8>(value);
            node_->setInt8Value(v);
            break;
        }
        case GenerateTypes::UInt8:
        {
            const quint8 v = static_cast<quint8>(value);
            node_->setUInt8Value(v);
            break;
        }
        case GenerateTypes::Int16:
        {
            const int v = static_cast<int>(value);
            node_->setInt16Value(v);
            break;
        }
        case GenerateTypes::UInt16:
        {
            const quint16 v = static_cast<quint16>(value);
            node_->setUInt16Value(v);
            break;
        }
        case GenerateTypes::Int32:
        {
            const qint32 v = static_cast<qint32>(value);
            node_->setInt32Value(v);
            break;
        }
        case GenerateTypes::UInt32:
        {
            const quint32 v = static_cast<quint32>(value);
            node_->setUInt32Value(v);
            break;
        }
        case GenerateTypes::Int64:
        {
            const qint64 v = static_cast<qint64>(value);
            node_->setInt64Value(v);
            break;
        }
        case GenerateTypes::UInt64:
        {
            const quint64 v = static_cast<quint64>(value);
            node_->setUInt64Value(v);
            break;
        }
        default:
        {
            qDebug() << "Bad integer generate type";
            break;
        }
    }
}

//==============================================================
// Сброс целочисленного значения
//==============================================================
void FormGenerateNode::slotResetIntValue()
{
    switch (generateType())
    {
        case GenerateTypes::Int8:
        {
            node_->resetInt8Value();
            ui_.spinBoxIntValue_->setFocus();
            break;
        }
        case GenerateTypes::UInt8:
        {
            node_->resetUInt8Value();
            ui_.spinBoxIntValue_->setFocus();
            break;
        }
        case GenerateTypes::Int16:
        {
            node_->resetInt16Value();
            ui_.spinBoxIntValue_->setFocus();
            break;
        }
        case GenerateTypes::UInt16:
        {
            node_->resetUInt16Value();
            ui_.spinBoxIntValue_->setFocus();
            break;
        }
        case GenerateTypes::Int32:
        {
            node_->resetInt32Value();
            ui_.spinBoxIntValue_->setFocus();
            break;
        }
        case GenerateTypes::UInt32:
        {
            node_->resetUInt32Value();
            ui_.spinBoxIntValue_->setFocus();
            break;
        }
        case GenerateTypes::Int64:
        {
            node_->resetInt64Value();
            ui_.spinBoxIntValue_->setFocus();
            break;
        }
        case GenerateTypes::UInt64:
        {
            node_->resetUInt64Value();
            ui_.spinBoxIntValue_->setFocus();
            break;
        }
        default:
        {
            qDebug() << "Bad integer generate type";
            break;
        }
    }
}

//==============================================================
// Функция вызывается при изменении дробного значения
//==============================================================
void FormGenerateNode::slotChangedDoubleValue(double value)
{
    switch (generateType())
    {
        case GenerateTypes::Float:
        {
            const float v = static_cast<float>(value);
            node_->setFloatValue(v);
            break;
        }
        case GenerateTypes::Double:
        {
            node_->setDoubleValue(value);
            break;
        }
        default:
        {
            qDebug() << "Bad double generate type";
            break;
        }
    }
}

//==============================================================
// Сброс дробного значения
//==============================================================
void FormGenerateNode::slotResetDoubleValue()
{
    switch (generateType())
    {
        case GenerateTypes::Float:
        {
            node_->resetFloatValue();
            ui_.doubleSpinBoxDoubleValue_->setFocus();
            break;
        }
        case GenerateTypes::Double:
        {
            node_->resetDoubleValue();
            ui_.doubleSpinBoxDoubleValue_->setFocus();
            break;
        }
        default:
        {
            qDebug() << "Bad double generate type";
            break;
        }
    }
}

//==============================================================
// Функция вызывается при изменении значения цвета
//==============================================================
void FormGenerateNode::slotChangedColorValue(const QColor &color)
{
    node_->setColorValue(color);
}

//==============================================================
// Функция вызывается при изменении строки
//==============================================================
void FormGenerateNode::slotChangedStrValue()
{
    const QString str = ui_.plainTextEditStrValue_->toPlainText();
    node_->setStrValue(str);
}

//==============================================================
// Сброс строкового значения
//==============================================================
void FormGenerateNode::slotResetStrValue()
{
    node_->resetStrValue();

    ui_.plainTextEditStrValue_->setFocus();
}

//==============================================================
// Сброс значения цвета
//==============================================================
void FormGenerateNode::slotResetColorValue()
{
    node_->resetColorValue();

    ui_.widgetColorValue_->setFocus();
}

//==============================================================
// Функция вызывается при завершении редактирования комментария
//==============================================================
void FormGenerateNode::slotEditingFinishedComment()
{
    const QString comment = ui_.lineEditComment_->text();
    node_->setComment(comment);
}

//==============================================================
// Сброс комментария
//==============================================================
void FormGenerateNode::slotResetComment()
{
    node_->resetComment();

    ui_.lineEditComment_->setFocus();
}

//==============================================================
// Задание соединений
//==============================================================
void FormGenerateNode::setConnections()
{
    connect(node_, &BaseNode::sigChangedProp,
        this, &FormGenerateNode::slotChangedNodeProp);

    connect(ui_.lineEditName_, &QLineEdit::editingFinished,
        this, &FormGenerateNode::slotEditingFinishedName);

    connect(ui_.comboBoxGenerateType_, qOverload<int>(&QComboBox::currentIndexChanged),
        this, &FormGenerateNode::slotChangedGenerateType);
    connect(ui_.pushBtnResetGenerateType_, &QPushButton::clicked,
        this, &FormGenerateNode::slotResetGenerateType);

    connect(ui_.spinBoxByteCount_, qOverload<int>(&QSpinBox::valueChanged),
        this, &FormGenerateNode::slotChangedByteCount);
    connect(ui_.pushBtnResetByteCount_, &QPushButton::clicked,
        this, &FormGenerateNode::slotResetCount);

    connect(ui_.spinBoxFilledByte_, qOverload<int>(&QSpinBox::valueChanged),
        this, &FormGenerateNode::slotChangedFilledByte);
    connect(ui_.pushBtnResetFilledByte_, &QPushButton::clicked,
        this, &FormGenerateNode::slotResetFilledByte);

    connect(ui_.checkBoxBoolValue_, &QCheckBox::stateChanged,
        this, &FormGenerateNode::slotChangedBoolValue);
    connect(ui_.pushBtnResetBoolValue_, &QPushButton::clicked,
        this, &FormGenerateNode::slotResetBoolValue);

    connect(ui_.spinBoxIntValue_, qOverload<int>(&QSpinBox::valueChanged),
        this, &FormGenerateNode::slotChangedIntValue);
    connect(ui_.pushBtnResetIntValue_, &QPushButton::clicked,
        this, &FormGenerateNode::slotResetIntValue);

    connect(ui_.doubleSpinBoxDoubleValue_, qOverload<double>(&QDoubleSpinBox::valueChanged),
        this, &FormGenerateNode::slotChangedDoubleValue);
    connect(ui_.pushBtnResetDoubleValue_, &QPushButton::clicked,
        this, &FormGenerateNode::slotResetDoubleValue);

    connect(ui_.plainTextEditStrValue_, &QPlainTextEdit::textChanged,
        this, &FormGenerateNode::slotChangedStrValue);
    connect(ui_.pushBtnResetStrValue_, &QPushButton::clicked,
        this, &FormGenerateNode::slotResetStrValue);

    connect(ui_.widgetColorValue_, &FormAdvColor::sigColorChanged,
        this, &FormGenerateNode::slotChangedColorValue);
    connect(ui_.pushBtnResetColorValue_, &QPushButton::clicked,
        this, &FormGenerateNode::slotResetColorValue);

    connect(ui_.lineEditComment_, &QLineEdit::editingFinished,
        this, &FormGenerateNode::slotEditingFinishedComment);
    connect(ui_.pushBtnResetComment_, &QPushButton::clicked,
        this, &FormGenerateNode::slotResetComment);
}

//==============================================================
// Получение типа генерации
//==============================================================
GenerateTypes FormGenerateNode::generateType() const
{
    const int typeIndex = ui_.comboBoxGenerateType_->currentIndex();
    Q_ASSERT(typeIndex != -1);

    return intToGenerateType(typeIndex);
}

//==============================================================
// Задание типа генерации
//==============================================================
void FormGenerateNode::setGenerateType(GenerateTypes type)
{
    Q_ASSERT(!isUnknown(type));
    const int index = generateTypeToInt(type);
    ui_.comboBoxGenerateType_->setCurrentIndex(index);
}

//==============================================================
// Задание типа генерации Usual
//==============================================================
void FormGenerateNode::setGenerateTypeUsual()
{
    // Показ и настройка виджетов
    ui_.spinBoxByteCount_->blockSignals(false);
    ui_.spinBoxByteCount_->setEnabled(true);
    ui_.spinBoxByteCount_->setMinimum(0);
    ui_.spinBoxByteCount_->setMaximum(numeric_limits<qint32>::max());
    ui_.spinBoxByteCount_->setStyleSheet(QString{});
    const bool isByteCountChanged = node_->isByteCountChanged();
    ui_.pushBtnResetByteCount_->setEnabled(isByteCountChanged);
    ui_.labelFilledByte_->show();
    ui_.spinBoxFilledByte_->show();
    ui_.pushBtnResetFilledByte_->show();

    // Скрытие виджетов
    ui_.checkBoxBoolValue_->hide();
    ui_.pushBtnResetBoolValue_->hide();
    ui_.labelValue_->hide();
    ui_.spinBoxIntValue_->hide();
    ui_.pushBtnResetIntValue_->hide();
    ui_.doubleSpinBoxDoubleValue_->hide();
    ui_.pushBtnResetDoubleValue_->hide();
    ui_.labelColorValue_->hide();
    ui_.widgetColorValue_->hide();
    ui_.pushBtnResetColorValue_->hide();
    ui_.labelStrValue_->hide();
    ui_.plainTextEditStrValue_->hide();
    ui_.pushBtnResetStrValue_->hide();
}

//==============================================================
// Задание типа генерации Random
//==============================================================
void FormGenerateNode::setGenerateTypeRandom()
{
    // Показ и настройка виджетов
    ui_.spinBoxByteCount_->blockSignals(false);
    ui_.spinBoxByteCount_->setEnabled(true);
    ui_.spinBoxByteCount_->setMinimum(0);
    ui_.spinBoxByteCount_->setMaximum(numeric_limits<qint32>::max());
    ui_.spinBoxByteCount_->setStyleSheet(QString{});
    const bool isByteCountChanged = node_->isByteCountChanged();
    ui_.pushBtnResetByteCount_->setEnabled(isByteCountChanged);

    // Скрытие виджетов
    ui_.labelFilledByte_->hide();
    ui_.spinBoxFilledByte_->hide();
    ui_.pushBtnResetFilledByte_->hide();
    ui_.checkBoxBoolValue_->hide();
    ui_.pushBtnResetBoolValue_->hide();
    ui_.labelValue_->hide();
    ui_.spinBoxIntValue_->hide();
    ui_.pushBtnResetIntValue_->hide();
    ui_.doubleSpinBoxDoubleValue_->hide();
    ui_.pushBtnResetDoubleValue_->hide();
    ui_.labelColorValue_->hide();
    ui_.widgetColorValue_->hide();
    ui_.pushBtnResetColorValue_->hide();
    ui_.labelStrValue_->hide();
    ui_.plainTextEditStrValue_->hide();
    ui_.pushBtnResetStrValue_->hide();
}

//==============================================================
// Задание типа генерации Bool
//==============================================================
void FormGenerateNode::setGenerateTypeBool()
{
    // Показ и настройка виджетов
    ui_.checkBoxBoolValue_->show();
    const bool value = node_->boolValue();
    ui_.checkBoxBoolValue_->setChecked(value);
    ui_.pushBtnResetBoolValue_->setVisible(true);
    const bool isValueChanged = node_->isBoolValueChanged();
    ui_.pushBtnResetBoolValue_->setEnabled(isValueChanged);
    ui_.spinBoxByteCount_->blockSignals(true);
    ui_.spinBoxByteCount_->setEnabled(false);
    ui_.spinBoxByteCount_->setValue(sizeof(value));
    ui_.spinBoxByteCount_->setStyleSheet("color: palette(text);");
    ui_.pushBtnResetByteCount_->setEnabled(false);

    // Скрытие виджетов
    ui_.labelFilledByte_->hide();
    ui_.spinBoxFilledByte_->hide();
    ui_.pushBtnResetFilledByte_->hide();
    ui_.labelValue_->hide();
    ui_.spinBoxIntValue_->hide();
    ui_.pushBtnResetIntValue_->hide();
    ui_.doubleSpinBoxDoubleValue_->hide();
    ui_.pushBtnResetDoubleValue_->hide();
    ui_.labelColorValue_->hide();
    ui_.widgetColorValue_->hide();
    ui_.pushBtnResetColorValue_->hide();
    ui_.labelStrValue_->hide();
    ui_.plainTextEditStrValue_->hide();
    ui_.pushBtnResetStrValue_->hide();
}

//==============================================================
// Задание типа генерации Int8
//==============================================================
void FormGenerateNode::setGenerateTypeInt8()
{
    // Показ и настройка виджетов
    ui_.labelValue_->show();
    ui_.spinBoxIntValue_->show();
    ui_.spinBoxIntValue_->setMinimum(numeric_limits<qint8>::min());
    ui_.spinBoxIntValue_->setMaximum(numeric_limits<qint8>::max());
    const qint8 value = node_->int8Value();
    ui_.spinBoxIntValue_->setValue(value);
    ui_.pushBtnResetIntValue_->show();
    const bool isValueChanged = node_->isInt8ValueChanged();
    ui_.pushBtnResetIntValue_->setEnabled(isValueChanged);
    ui_.spinBoxByteCount_->blockSignals(true);
    ui_.spinBoxByteCount_->setEnabled(false);
    ui_.spinBoxByteCount_->setValue(sizeof(value));
    ui_.spinBoxByteCount_->setStyleSheet("color: palette(text);");
    ui_.pushBtnResetByteCount_->setEnabled(false);

    // Скрытие виджетов
    ui_.labelFilledByte_->hide();
    ui_.spinBoxFilledByte_->hide();
    ui_.pushBtnResetFilledByte_->hide();
    ui_.checkBoxBoolValue_->hide();
    ui_.pushBtnResetBoolValue_->hide();
    ui_.doubleSpinBoxDoubleValue_->hide();
    ui_.pushBtnResetDoubleValue_->hide();
    ui_.labelColorValue_->hide();
    ui_.widgetColorValue_->hide();
    ui_.pushBtnResetColorValue_->hide();
    ui_.labelStrValue_->hide();
    ui_.plainTextEditStrValue_->hide();
    ui_.pushBtnResetStrValue_->hide();
}

//==============================================================
// Задание типа генерации UInt8
//==============================================================
void FormGenerateNode::setGenerateTypeUInt8()
{
    // Показ и настройка виджетов
    ui_.labelValue_->show();
    ui_.spinBoxIntValue_->show();
    ui_.spinBoxIntValue_->setMinimum(numeric_limits<quint8>::min());
    ui_.spinBoxIntValue_->setMaximum(numeric_limits<quint8>::max());
    ui_.spinBoxByteCount_->setStyleSheet("background-color: rgb(235, 235, 235);");
    const quint8 value = node_->uint8Value();
    ui_.spinBoxIntValue_->setValue(value);
    const bool isValueChanged = node_->isUInt8ValueChanged();
    ui_.pushBtnResetIntValue_->setEnabled(isValueChanged);
    ui_.spinBoxByteCount_->blockSignals(true);
    ui_.spinBoxByteCount_->setEnabled(false);
    ui_.spinBoxByteCount_->setValue(sizeof(value));
    ui_.spinBoxByteCount_->setStyleSheet("color: palette(text);");
    ui_.pushBtnResetByteCount_->setEnabled(false);

    // Скрытие виджетов
    ui_.labelFilledByte_->hide();
    ui_.spinBoxFilledByte_->hide();
    ui_.pushBtnResetFilledByte_->hide();
    ui_.checkBoxBoolValue_->hide();
    ui_.pushBtnResetBoolValue_->hide();
    ui_.doubleSpinBoxDoubleValue_->hide();
    ui_.pushBtnResetDoubleValue_->hide();
    ui_.labelColorValue_->hide();
    ui_.widgetColorValue_->hide();
    ui_.pushBtnResetColorValue_->hide();
    ui_.labelStrValue_->hide();
    ui_.plainTextEditStrValue_->hide();
    ui_.pushBtnResetStrValue_->hide();
}

//==============================================================
// Задание типа генерации Int16
//==============================================================
void FormGenerateNode::setGenerateTypeInt16()
{
    // Показ и настройка виджетов
    ui_.labelValue_->show();
    ui_.spinBoxIntValue_->show();
    ui_.spinBoxIntValue_->setMinimum(numeric_limits<qint16>::min());
    ui_.spinBoxIntValue_->setMaximum(numeric_limits<qint16>::max());
    ui_.spinBoxByteCount_->setStyleSheet("background-color: rgb(235, 235, 235);");
    const qint16 value = node_->int16Value();
    ui_.spinBoxIntValue_->setValue(value);
    const bool isValueChanged = node_->isInt16ValueChanged();
    ui_.pushBtnResetIntValue_->setEnabled(isValueChanged);
    ui_.spinBoxByteCount_->blockSignals(true);
    ui_.spinBoxByteCount_->setEnabled(false);
    ui_.spinBoxByteCount_->setValue(sizeof(value));
    ui_.spinBoxByteCount_->setStyleSheet("color: palette(text);");
    ui_.pushBtnResetByteCount_->setEnabled(false);

    // Скрытие виджетов
    ui_.labelFilledByte_->hide();
    ui_.spinBoxFilledByte_->hide();
    ui_.pushBtnResetFilledByte_->hide();
    ui_.checkBoxBoolValue_->hide();
    ui_.pushBtnResetBoolValue_->hide();
    ui_.doubleSpinBoxDoubleValue_->hide();
    ui_.pushBtnResetDoubleValue_->hide();
    ui_.labelColorValue_->hide();
    ui_.widgetColorValue_->hide();
    ui_.pushBtnResetColorValue_->hide();
    ui_.labelStrValue_->hide();
    ui_.plainTextEditStrValue_->hide();
    ui_.pushBtnResetStrValue_->hide();
}

//==============================================================
// Задание типа генерации UInt16
//==============================================================
void FormGenerateNode::setGenerateTypeUInt16()
{
    // Показ и настройка виджетов
    ui_.labelValue_->show();
    ui_.spinBoxIntValue_->show();
    ui_.spinBoxIntValue_->setMinimum(numeric_limits<quint16>::min());
    ui_.spinBoxIntValue_->setMaximum(numeric_limits<quint16>::max());
    ui_.spinBoxByteCount_->setStyleSheet("background-color: rgb(235, 235, 235);");
    const quint16 value = node_->uint16Value();
    ui_.spinBoxIntValue_->setValue(value);
    const bool isValueChanged = node_->isUInt16ValueChanged();
    ui_.pushBtnResetIntValue_->setEnabled(isValueChanged);
    ui_.spinBoxByteCount_->blockSignals(true);
    ui_.spinBoxByteCount_->setEnabled(false);
    ui_.spinBoxByteCount_->setValue(sizeof(value));
    ui_.spinBoxByteCount_->setStyleSheet("color: palette(text);");
    ui_.pushBtnResetByteCount_->setEnabled(false);

    // Скрытие виджетов
    ui_.labelFilledByte_->hide();
    ui_.spinBoxFilledByte_->hide();
    ui_.pushBtnResetFilledByte_->hide();
    ui_.checkBoxBoolValue_->hide();
    ui_.pushBtnResetBoolValue_->hide();
    ui_.doubleSpinBoxDoubleValue_->hide();
    ui_.pushBtnResetDoubleValue_->hide();
    ui_.labelColorValue_->hide();
    ui_.widgetColorValue_->hide();
    ui_.pushBtnResetColorValue_->hide();
    ui_.labelStrValue_->hide();
    ui_.plainTextEditStrValue_->hide();
    ui_.pushBtnResetStrValue_->hide();
}

//==============================================================
// Задание типа генерации Int32
//==============================================================
void FormGenerateNode::setGenerateTypeInt32()
{
    // Показ и настройка виджетов
    ui_.labelValue_->show();
    ui_.spinBoxIntValue_->show();
    ui_.spinBoxIntValue_->setMinimum(numeric_limits<qint32>::min());
    ui_.spinBoxIntValue_->setMaximum(numeric_limits<qint32>::max());
    const qint32 value = node_->int32Value();
    ui_.spinBoxIntValue_->setValue(value);
    const bool isValueChanged = node_->isInt32ValueChanged();
    ui_.pushBtnResetIntValue_->setEnabled(isValueChanged);
    ui_.spinBoxByteCount_->blockSignals(true);
    ui_.spinBoxByteCount_->setEnabled(false);
    ui_.spinBoxByteCount_->setValue(sizeof(value));
    ui_.spinBoxByteCount_->setStyleSheet("color: palette(text);");
    ui_.pushBtnResetByteCount_->setEnabled(false);

    // Скрытие виджетов
    ui_.labelFilledByte_->hide();
    ui_.spinBoxFilledByte_->hide();
    ui_.pushBtnResetFilledByte_->hide();
    ui_.checkBoxBoolValue_->hide();
    ui_.pushBtnResetBoolValue_->hide();
    ui_.doubleSpinBoxDoubleValue_->hide();
    ui_.pushBtnResetDoubleValue_->hide();
    ui_.labelColorValue_->hide();
    ui_.widgetColorValue_->hide();
    ui_.pushBtnResetColorValue_->hide();
    ui_.labelStrValue_->hide();
    ui_.plainTextEditStrValue_->hide();
    ui_.pushBtnResetStrValue_->hide();
}

//==============================================================
// Задание типа генерации UInt32
//==============================================================
void FormGenerateNode::setGenerateTypeUInt32()
{
    // Показ и настройка виджетов
    ui_.labelValue_->show();
    ui_.spinBoxIntValue_->show();
    ui_.spinBoxIntValue_->setMinimum(0);
    ui_.spinBoxIntValue_->setMaximum(numeric_limits<qint32>::max());
    const quint32 value = node_->uint32Value();
    ui_.spinBoxIntValue_->setValue(value);
    const bool isValueChanged = node_->isUInt32ValueChanged();
    ui_.pushBtnResetIntValue_->setEnabled(isValueChanged);
    ui_.spinBoxByteCount_->blockSignals(true);
    ui_.spinBoxByteCount_->setEnabled(false);
    ui_.spinBoxByteCount_->setValue(sizeof(value));
    ui_.spinBoxByteCount_->setStyleSheet("color: palette(text);");
    ui_.pushBtnResetByteCount_->setEnabled(false);

    // Скрытие виджетов
    ui_.labelFilledByte_->hide();
    ui_.spinBoxFilledByte_->hide();
    ui_.pushBtnResetFilledByte_->hide();
    ui_.checkBoxBoolValue_->hide();
    ui_.pushBtnResetBoolValue_->hide();
    ui_.doubleSpinBoxDoubleValue_->hide();
    ui_.pushBtnResetDoubleValue_->hide();
    ui_.labelColorValue_->hide();
    ui_.widgetColorValue_->hide();
    ui_.pushBtnResetColorValue_->hide();
    ui_.labelStrValue_->hide();
    ui_.plainTextEditStrValue_->hide();
    ui_.pushBtnResetStrValue_->hide();
}

//==============================================================
// Задание типа генерации Int64
//==============================================================
void FormGenerateNode::setGenerateTypeInt64()
{
    // Показ и настройка виджетов
    ui_.labelValue_->show();
    ui_.spinBoxIntValue_->show();
    ui_.spinBoxIntValue_->setMinimum(numeric_limits<qint32>::min());
    ui_.spinBoxIntValue_->setMaximum(numeric_limits<qint32>::max());
    const qint64 value = node_->int64Value();
    ui_.spinBoxIntValue_->setValue(value);
    const bool isValueChanged = node_->isInt64ValueChanged();
    ui_.pushBtnResetIntValue_->setEnabled(isValueChanged);
    ui_.spinBoxByteCount_->blockSignals(true);
    ui_.spinBoxByteCount_->setEnabled(false);
    ui_.spinBoxByteCount_->setValue(sizeof(value));
    ui_.spinBoxByteCount_->setStyleSheet("color: palette(text);");
    ui_.pushBtnResetByteCount_->setEnabled(false);

    // Скрытие виджетов
    ui_.labelFilledByte_->hide();
    ui_.spinBoxFilledByte_->hide();
    ui_.pushBtnResetFilledByte_->hide();
    ui_.checkBoxBoolValue_->hide();
    ui_.pushBtnResetBoolValue_->hide();
    ui_.doubleSpinBoxDoubleValue_->hide();
    ui_.pushBtnResetDoubleValue_->hide();
    ui_.labelColorValue_->hide();
    ui_.widgetColorValue_->hide();
    ui_.pushBtnResetColorValue_->hide();
    ui_.labelStrValue_->hide();
    ui_.plainTextEditStrValue_->hide();
    ui_.pushBtnResetStrValue_->hide();
}

//==============================================================
// Задание типа генерации UInt64
//==============================================================
void FormGenerateNode::setGenerateTypeUInt64()
{
    // Показ и настройка виджетов
    ui_.labelValue_->show();
    ui_.spinBoxIntValue_->show();
    ui_.spinBoxIntValue_->setMinimum(0);
    ui_.spinBoxIntValue_->setMaximum(numeric_limits<qint32>::max());
    const quint64 value = node_->uint64Value();
    ui_.spinBoxIntValue_->setValue(value);
    ui_.pushBtnResetIntValue_->show();
    const bool isValueChanged = node_->isUInt64ValueChanged();
    ui_.pushBtnResetIntValue_->setEnabled(isValueChanged);
    ui_.spinBoxByteCount_->blockSignals(true);
    ui_.spinBoxByteCount_->setEnabled(false);
    ui_.spinBoxByteCount_->setValue(sizeof(value));
    ui_.spinBoxByteCount_->setStyleSheet("color: palette(text);");
    ui_.pushBtnResetByteCount_->setEnabled(false);

    // Скрытие виджетов
    ui_.labelFilledByte_->hide();
    ui_.spinBoxFilledByte_->hide();
    ui_.pushBtnResetFilledByte_->hide();
    ui_.checkBoxBoolValue_->hide();
    ui_.pushBtnResetBoolValue_->hide();
    ui_.doubleSpinBoxDoubleValue_->hide();
    ui_.pushBtnResetDoubleValue_->hide();
    ui_.labelColorValue_->hide();
    ui_.widgetColorValue_->hide();
    ui_.pushBtnResetColorValue_->hide();
    ui_.labelStrValue_->hide();
    ui_.plainTextEditStrValue_->hide();
    ui_.pushBtnResetStrValue_->hide();
}

//==============================================================
// Задание типа генерации Float
//==============================================================
void FormGenerateNode::setGenerateTypeFloat()
{
    // Показ и настройка виджетов
    ui_.labelValue_->show();
    ui_.doubleSpinBoxDoubleValue_->show();
    ui_.doubleSpinBoxDoubleValue_->setMinimum(numeric_limits<float>::lowest());
    ui_.doubleSpinBoxDoubleValue_->setMaximum(numeric_limits<float>::max());
    const float value = node_->floatValue();
    ui_.doubleSpinBoxDoubleValue_->setValue(value);
    ui_.pushBtnResetDoubleValue_->show();
    const bool isValueChanged = node_->isFloatValueChanged();
    ui_.pushBtnResetDoubleValue_->setEnabled(isValueChanged);
    ui_.spinBoxByteCount_->blockSignals(true);
    ui_.spinBoxByteCount_->setEnabled(false);
    ui_.spinBoxByteCount_->setValue(sizeof(value));
    ui_.spinBoxByteCount_->setStyleSheet("color: palette(text);");
    ui_.pushBtnResetByteCount_->setEnabled(false);

    // Скрытие виджетов
    ui_.labelFilledByte_->hide();
    ui_.spinBoxFilledByte_->hide();
    ui_.pushBtnResetFilledByte_->hide();
    ui_.checkBoxBoolValue_->hide();
    ui_.pushBtnResetBoolValue_->hide();
    ui_.spinBoxIntValue_->hide();
    ui_.pushBtnResetIntValue_->hide();
    ui_.labelColorValue_->hide();
    ui_.widgetColorValue_->hide();
    ui_.pushBtnResetColorValue_->hide();
    ui_.labelStrValue_->hide();
    ui_.plainTextEditStrValue_->hide();
    ui_.pushBtnResetStrValue_->hide();
}

//==============================================================
// Задание типа генерации Double
//==============================================================
void FormGenerateNode::setGenerateTypeDouble()
{
    // Показ и настройка виджетов
    ui_.labelValue_->show();
    ui_.doubleSpinBoxDoubleValue_->show();
    ui_.doubleSpinBoxDoubleValue_->setMinimum(numeric_limits<double>::lowest());
    ui_.doubleSpinBoxDoubleValue_->setMaximum(numeric_limits<double>::max());
    const double value = node_->doubleValue();
    ui_.doubleSpinBoxDoubleValue_->setValue(value);
    ui_.pushBtnResetDoubleValue_->show();
    const bool isValueChanged = node_->isDoubleValueChanged();
    ui_.pushBtnResetDoubleValue_->setEnabled(isValueChanged);
    ui_.spinBoxByteCount_->blockSignals(true);
    ui_.spinBoxByteCount_->setEnabled(false);
    ui_.spinBoxByteCount_->setValue(sizeof(value));
    ui_.spinBoxByteCount_->setStyleSheet("color: palette(text);");
    ui_.pushBtnResetByteCount_->setEnabled(false);

    // Скрытие виджетов
    ui_.labelFilledByte_->hide();
    ui_.spinBoxFilledByte_->hide();
    ui_.pushBtnResetFilledByte_->hide();
    ui_.checkBoxBoolValue_->hide();
    ui_.pushBtnResetBoolValue_->hide();
    ui_.spinBoxIntValue_->hide();
    ui_.pushBtnResetIntValue_->hide();
    ui_.labelColorValue_->hide();
    ui_.widgetColorValue_->hide();
    ui_.pushBtnResetColorValue_->hide();
    ui_.labelStrValue_->hide();
    ui_.plainTextEditStrValue_->hide();
    ui_.pushBtnResetStrValue_->hide();
}

//==============================================================
// Задание типа генерации String
//==============================================================
void FormGenerateNode::setGenerateTypeStr()
{
    // Показ и настройка виджетов
    ui_.labelStrValue_->show();
    ui_.plainTextEditStrValue_->show();
    const QString value = node_->strValue();
    ui_.plainTextEditStrValue_->setPlainText(value);
    ui_.pushBtnResetStrValue_->show();
    const bool isValueChanged = node_->isStrValueChanged();
    ui_.pushBtnResetStrValue_->setEnabled(isValueChanged);
    ui_.spinBoxByteCount_->blockSignals(true);
    ui_.spinBoxByteCount_->setEnabled(false);
    const int valueByteCount = getValueByteSize(value);
    ui_.spinBoxByteCount_->setValue(valueByteCount);
    // ui_.spinBoxByteCount_->setStyleSheet("color: palette(text);");
    ui_.pushBtnResetByteCount_->setEnabled(false);

    // Скрытие виджетов
    ui_.labelFilledByte_->hide();
    ui_.spinBoxFilledByte_->hide();
    ui_.pushBtnResetFilledByte_->hide();
    ui_.checkBoxBoolValue_->hide();
    ui_.pushBtnResetBoolValue_->hide();
    ui_.labelValue_->hide();
    ui_.spinBoxIntValue_->hide();
    ui_.pushBtnResetIntValue_->hide();
    ui_.doubleSpinBoxDoubleValue_->hide();
    ui_.pushBtnResetDoubleValue_->hide();
    ui_.labelColorValue_->hide();
    ui_.widgetColorValue_->hide();
    ui_.pushBtnResetColorValue_->hide();
}

//==============================================================
// Задание типа генерации Color
//==============================================================
void FormGenerateNode::setGenerateTypeColor()
{
    // Показ и настройка виджетов
    ui_.labelColorValue_->show();
    ui_.widgetColorValue_->show();
    const QColor value = node_->colorValue();
    ui_.widgetColorValue_->setColor(value);
    ui_.pushBtnResetColorValue_->show();
    const bool isValueChanged = node_->isColorValueChanged();
    ui_.pushBtnResetColorValue_->setEnabled(isValueChanged);
    ui_.spinBoxByteCount_->blockSignals(true);
    ui_.spinBoxByteCount_->setEnabled(false);
    ui_.spinBoxByteCount_->setValue(4);
    ui_.spinBoxByteCount_->setStyleSheet("color: palette(text);");
    ui_.pushBtnResetByteCount_->setEnabled(false);

    // Скрытие виджетов
    ui_.labelFilledByte_->hide();
    ui_.spinBoxFilledByte_->hide();
    ui_.pushBtnResetFilledByte_->hide();
    ui_.checkBoxBoolValue_->hide();
    ui_.pushBtnResetBoolValue_->hide();
    ui_.labelValue_->hide();
    ui_.spinBoxIntValue_->hide();
    ui_.pushBtnResetIntValue_->hide();
    ui_.doubleSpinBoxDoubleValue_->hide();
    ui_.pushBtnResetDoubleValue_->hide();
    ui_.labelStrValue_->hide();
    ui_.plainTextEditStrValue_->hide();
    ui_.pushBtnResetStrValue_->hide();
}

//==============================================================
// Подсветка виджета с количеством байт
//==============================================================
void FormGenerateNode::highlightByteCountWidget()
{
    if (ui_.spinBoxByteCount_->value() > 0)
    {
        ui_.spinBoxByteCount_->setStyleSheet("");
    }
    else
    {
        ui_.spinBoxByteCount_->setStyleSheet("background-color: rgb(255, 240, 168);");
    }
}

//==============================================================
// Задание узла
//==============================================================
void FormGenerateNode::setNode(GenerateNode *node)
{
    Q_ASSERT(node != nullptr);

    node_ = node;

    // Задание имени
    const QString name = node->name();
    ui_.lineEditName_->setText(name);
    ui_.lineEditName_->setToolTip(name);

    // Задание типа генерации
    const GenerateTypes type = node_->generateType();
    setGenerateType(type);
    const int typeIndex = generateTypeToInt(type);
    Q_ASSERT(typeIndex != -1);
    slotChangedGenerateType(typeIndex);
    const bool isTypeChanged = node_->isGenerateTypeChanged();
    ui_.pushBtnResetGenerateType_->setEnabled(isTypeChanged);

    // Задание количества байтов
    const int count = node_->byteCount();
    ui_.spinBoxByteCount_->setValue(count);
    // highlightByteCountWidget();

    // Задание заполняющего байта
    const quint8 filledByte = node_->filledByte();
    ui_.spinBoxFilledByte_->setValue(filledByte);
    const bool isFilledByteChanged = node_->isFilledByteChanged();
    ui_.pushBtnResetFilledByte_->setEnabled(isFilledByteChanged);

    // Задание комментария
    const QString comment = node->comment();
    ui_.lineEditComment_->setText(comment);
    ui_.lineEditComment_->setToolTip(comment);
    const bool isCommentChanged = node->isCommentChanged();
    ui_.pushBtnResetComment_->setEnabled(isCommentChanged);
}
