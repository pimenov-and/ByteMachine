////////////////////////////////////////////////////////////////
// ByteMachine
// Цвета
////////////////////////////////////////////////////////////////
#ifndef COLORS_H
#define COLORS_H

//==============================================================
#include "standart_colors.h"

//==============================================================
// Цвета
//==============================================================
class Colors
{
    Q_DISABLE_COPY_MOVE(Colors)
public:
    // Конструктор по умолчанию
    Colors() = delete;

    //----------------------------------------------------------
    // Цвета дизайнера
    //----------------------------------------------------------
    // Цвета фона дизайнера
    [[nodiscard]]
    constexpr static QColor designerBack() noexcept
        { return StandartColors::white(); }
    // Цвет сетки дизайнера
    [[nodiscard]]
    constexpr static QColor designerGrid() noexcept
        { return QColor{225, 225, 225}; }
    // Цвет рамки выделения
    [[nodiscard]]
    constexpr static QColor designerSelectArea() noexcept
        { return QColor{60, 60, 255}; }

    //----------------------------------------------------------
    // Цвета узлов
    //----------------------------------------------------------
    // Цвет границы узла
    [[nodiscard]]
    constexpr static QColor nodeBorder() noexcept
        { return {110, 110, 110}; }
    // Цвет фона пина для
    [[nodiscard]]
    constexpr static QColor nodePinBack() noexcept
        { return StandartColors::white(); }
    // Цвет фона подключенного пина
    [[nodiscard]]
    constexpr static QColor nodeConnectPinBack() noexcept
        { return {180, 180, 180}; }
    // Цвет фона узла
    [[nodiscard]]
    constexpr static QColor nodeBack() noexcept
        { return StandartColors::white(); }
    // Цвет текста узла
    [[nodiscard]]
    constexpr static QColor nodeText() noexcept
        { return {10, 10, 10}; }
    // Цвет границы выделенного узла
    [[nodiscard]]
    constexpr static QColor nodeSelectBorder() noexcept
        { return {60, 60, 255}; }
    // Цвет границы вторично выделенного узла
    [[nodiscard]]
    constexpr static QColor nodeSecondSelectBorder() noexcept
        { return {0, 156, 0}; }
    // Цвет рамки области состояния узла при предупреждении
    [[nodiscard]]
    constexpr static QColor nodeWarnStateAreaBorder() noexcept
        { return StandartColors::black(); }
    // Цвет фона области состояния узла при предупреждении
    [[nodiscard]]
    constexpr static QColor nodeWarnStateAreaBack() noexcept
        { return StandartColors::yellow(); }
    // Цвет рамки области состояния узла при ошибке
    [[nodiscard]]
    constexpr static QColor nodeErrStateAreaBorder() noexcept
        { return StandartColors::black(); }
    // Цвет фона области состояния узла при ошибке
    [[nodiscard]]
    constexpr static QColor nodeErrStateAreaBack() noexcept
        { return {255, 107, 107}; }

    //----------------------------------------------------------
    // Статус-бар
    //----------------------------------------------------------
    // Цвет фона области с именем бренда
    [[nodiscard]]
    constexpr static QColor statusBarVersionAreaBackColor() noexcept
        { return {0, 80, 152}; }
    // Цвет фона статус-бара
    [[nodiscard]]
    constexpr static QColor statusBarBackColor() noexcept
        { return {0, 122, 204}; }
    // Цвет текста статус-бара
    [[nodiscard]]
    constexpr static QColor statusBarTextColor() noexcept
        { return StandartColors::white(); }
};

//==============================================================
#endif // COLORS_H
