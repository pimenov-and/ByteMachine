////////////////////////////////////////////////////////////////
// ByteMachine
// Вспомогательные функции Qt
////////////////////////////////////////////////////////////////
#include "qt_helper.h"
#include <QPainter>
#include <QFile>
#include <QTextStream>

//==============================================================
using std::optional;
using std::nullopt;

//==============================================================
// Сделать заглавную букву строки строчной
//==============================================================
QString capitalizeStr(const QString &str)
{
    if (str.isEmpty())
    {
        return QString{};
    }

    return str.front().toLower() + str.mid(1);
}

//==============================================================
// Конвертация bool в строку
//==============================================================
QString boolToStr(bool value)
{
    return value ? "True" : "False";
}

//==============================================================
// Проверка bool в виде строки
//==============================================================
bool checkBoolStr(const QString &str)
{
    return (str == "True") || (str == "False");
}

//==============================================================
// Получение bool из строки
//==============================================================
optional<bool> strToBool(const QString &str)
{
    if (checkBoolStr(str))
    {
        return str == "True";
    }
    else
    {
        return nullopt;
    }
}

//==============================================================
// Чтение текстового файла
//==============================================================
optional<QString> readFileAllLines(const QString &path)
{
    QFile file{path};
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return nullopt;
    }

    return QTextStream{&file}.readAll();
}

//==============================================================
// Получение размера строки
//==============================================================
QSize strSize(QPainter &painter, const QString &str)
{
    const QRect boundingRect =
        painter.boundingRect(QRect{}, Qt::AlignCenter, str);

    return QSize{boundingRect.width(), boundingRect.height()};
}

//==============================================================
// Проверка нажатия клавиши Alt
//==============================================================
bool isAltKey(Qt::KeyboardModifiers modifier)
{
    return (modifier & Qt::AltModifier) == Qt::AltModifier;
}

//==============================================================
// Проверка нажатия клавиши Control
//==============================================================
bool isCtrlKey(Qt::KeyboardModifiers modifier)
{
    return (modifier & Qt::ControlModifier) == Qt::ControlModifier;
}
