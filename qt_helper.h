////////////////////////////////////////////////////////////////
// ByteMachine
// Вспомогательные функции Qt
////////////////////////////////////////////////////////////////
#ifndef QT_HELPER_H
#define QT_HELPER_H

//==============================================================
#include <QString>
#include <QSize>
#include <optional>

//==============================================================
class QPainter;

//==============================================================
// Прототипы функций
//==============================================================
// Получение размера строки
[[nodiscard]]
QSize strSize(QPainter &painter, const QString &str);
// Конвертация bool в строку
[[nodiscard]]
QString boolToStr(bool value);
// Получение bool из строки
[[nodiscard]]
std::optional<bool> strToBool(const QString &str);
// Проверка bool в виде строки
[[nodiscard]]
bool checkBoolStr(const QString &str);
// Чтение текстового файла
[[nodiscard]]
std::optional<QString> readFileAllLines(const QString &path);
// Сделать заглавную букву строки строчной
[[nodiscard]]
QString capitalizeStr(const QString &str);

// Проверка нажатия клавиши Alt
[[nodiscard]]
bool isAltKey(Qt::KeyboardModifiers modifier);
// Проверка нажатия клавиши Control
[[nodiscard]]
bool isCtrlKey(Qt::KeyboardModifiers modifier);

//==============================================================
#endif // QT_HELPER_H
