////////////////////////////////////////////////////////////////
// ByteMachine
// Стандартные цвета
////////////////////////////////////////////////////////////////
#ifndef STANDART_COLORS_H
#define STANDART_COLORS_H

//==============================================================
#include <QColor>

//==============================================================
//  Стандартные цвета
//==============================================================
class StandartColors
{
    Q_DISABLE_COPY_MOVE(StandartColors)
public:
    // Конструктор по умолчанию
    StandartColors() = delete;

    //----------------------------------------------------------
    // Основные цвета
    //----------------------------------------------------------
    // Получение белого цвета
    [[nodiscard]]
    constexpr static QColor white() noexcept { return {255, 255, 255}; }
    // Получение черного цвета
    [[nodiscard]]
    constexpr static QColor black() noexcept { return {0, 0, 0}; }
    // Получение красного цвета
    [[nodiscard]]
    constexpr static QColor red() noexcept { return {255, 0, 0}; }
    // Получение зелёного цвета
    [[nodiscard]]
    constexpr static QColor green() noexcept { return {0, 128, 0}; }
    // Получение синего цвета
    [[nodiscard]]
    constexpr static QColor blue() noexcept { return {0, 0, 255}; }
    // Получение серого цвета
    [[nodiscard]]
    constexpr static QColor gray() noexcept { return {128, 128, 128}; }
    // Получение жёлтого цвета
    [[nodiscard]]
    constexpr static QColor yellow() noexcept { return {255, 255, 0}; }
    // Получение цвета Navy
    [[nodiscard]]
    constexpr static QColor navy() noexcept { return {0, 0, 128}; }
    // Получение цвета Brown
    [[nodiscard]]
    constexpr static QColor brown() noexcept { return {165, 42, 42}; }
    // Получение цвета Lime
    [[nodiscard]]
    constexpr static QColor lime() noexcept { return {0, 255, 0}; }
    // Получение цвета Aqua
    [[nodiscard]]
    constexpr static QColor aqua() noexcept { return {0, 255, 255}; }
    // Получение цвета Teal
    [[nodiscard]]
    constexpr static QColor teal() noexcept { return {0, 255, 255}; }
    // Получение цвета Maroon
    [[nodiscard]]
    constexpr static QColor maroon() noexcept { return {128, 0, 0}; }
    // Получение цвета Olive
    [[nodiscard]]
    constexpr static QColor olive() noexcept { return {128, 128, 0}; }
    // Получение прозрачного цвета
    [[nodiscard]]
    constexpr static QColor transparent() noexcept { return {0, 0, 0, 0}; }

    //----------------------------------------------------------
    // Красные тона
    //----------------------------------------------------------
    // Получение цвета IndianRed
    [[nodiscard]]
    constexpr static QColor indianRed() noexcept { return {205, 92, 92}; }
    // Получение цвета LightCoral
    [[nodiscard]]
    constexpr static QColor lightCoral() noexcept { return {240, 128, 128}; }
    // Получение цвета Salmon
    [[nodiscard]]
    constexpr static QColor salmon() noexcept { return {250, 128, 114}; }
    // Получение цвета DarkSalmon
    [[nodiscard]]
    constexpr static QColor darkSalmon() noexcept { return {233, 150, 122}; }
    // Получение цвета LightSalmon
    [[nodiscard]]
    constexpr static QColor lightSalmon() noexcept { return {255, 160, 122}; }
    // Получение цвета Crimson
    [[nodiscard]]
    constexpr static QColor crimson() noexcept { return {220, 20, 60}; }
    // Получение цвета FireBrick
    [[nodiscard]]
    constexpr static QColor fireBrick() noexcept { return {178, 34, 34}; }
    // Получение цвета DarkRed
    [[nodiscard]]
    constexpr static QColor darkBrick() noexcept { return {139, 0, 0}; }

    //----------------------------------------------------------
    // Розовые тона
    //----------------------------------------------------------
    // Получение цвета Pink
    [[nodiscard]]
    constexpr static QColor pink() noexcept { return {255, 192, 203}; }
    // Получение цвета LightPink
    [[nodiscard]]
    constexpr static QColor lightPink() noexcept { return {255, 182, 193}; }
    // Получение цвета HotPink
    [[nodiscard]]
    constexpr static QColor hotPink() noexcept { return {255, 105, 180}; }
    // Получение цвета DeepPink
    [[nodiscard]]
    constexpr static QColor deepPink() noexcept { return {255, 20, 147}; }
    // Получение цвета MediumVioletRed
    [[nodiscard]]
    constexpr static QColor mediumVioletRed() noexcept { return {199, 21, 133}; }
    // Получение цвета PaleVioletRed
    [[nodiscard]]
    constexpr static QColor paleVioletRed() noexcept { return {219, 112, 147}; }

    //----------------------------------------------------------
    // Оранжевые тона
    //----------------------------------------------------------
    // Получение цвета Coral
    [[nodiscard]]
    constexpr static QColor coral() noexcept { return {255, 127, 80}; }
    // Получение цвета Tomato
    [[nodiscard]]
    constexpr static QColor tomato() noexcept { return {255, 99, 71}; }
    // Получение цвета OrangeRed
    [[nodiscard]]
    constexpr static QColor orangeRed() noexcept { return {255, 69, 0}; }
    // Получение цвета DarkOrange
    [[nodiscard]]
    constexpr static QColor darkOrange() noexcept { return {255, 140, 0}; }
    // Получение цвета Orange
    [[nodiscard]]
    constexpr static QColor orange() noexcept { return {255, 165, 0}; }

    //----------------------------------------------------------
    // Жёлтые тона
    //----------------------------------------------------------
    // Получение цвета Gold
    [[nodiscard]]
    constexpr static QColor gold() noexcept { return {255, 215, 0}; }
    // Получение цвета LightYellow
    [[nodiscard]]
    constexpr static QColor lightYellow() noexcept { return {255, 255, 224}; }
    // Получение цвета LemonChiffon
    [[nodiscard]]
    constexpr static QColor lemonChiffon() noexcept { return {255, 250, 205}; }
    // Получение цвета LightGoldenrodYellow
    [[nodiscard]]
    constexpr static QColor lightGoldenrodYellow() noexcept { return {250, 250, 210}; }
    // Получение цвета PapayaWhip
    [[nodiscard]]
    constexpr static QColor papayaWhip() noexcept { return {255, 239, 213}; }
    // Получение цвета Moccasin
    [[nodiscard]]
    constexpr static QColor moccasin() noexcept { return {255, 228, 181}; }
    // Получение цвета PeachPuff
    [[nodiscard]]
    constexpr static QColor peachPuff() noexcept { return {255, 218, 185}; }
    // Получение цвета PaleGoldenrod
    [[nodiscard]]
    constexpr static QColor paleGoldenrod() noexcept { return {238, 232, 170}; }
    // Получение цвета Khaki
    [[nodiscard]]
    constexpr static QColor khaki() noexcept { return {240, 230, 140}; }
    // Получение цвета DarkKhaki
    [[nodiscard]]
    constexpr static QColor darkKhaki() noexcept { return {189, 183, 107}; }

    //----------------------------------------------------------
    // Фиолетовые тона
    //----------------------------------------------------------
    // Получение цвета Lavender
    [[nodiscard]]
    constexpr static QColor lavender() noexcept { return {230, 230, 250}; }
    // Получение цвета Thistle
    [[nodiscard]]
    constexpr static QColor thistle() noexcept { return {216, 191, 216}; }
    // Получение цвета Plum
    [[nodiscard]]
    constexpr static QColor plum() noexcept { return {221, 160, 221}; }
    // Получение цвета Violet
    [[nodiscard]]
    constexpr static QColor violet() noexcept { return {238, 130, 238}; }
    // Получение цвета Orchid
    [[nodiscard]]
    constexpr static QColor orchid() noexcept { return {218, 112, 214}; }
    // Получение цвета Fuchsia
    [[nodiscard]]
    constexpr static QColor fuchsia() noexcept { return {255, 0, 255}; }
    // Получение цвета Magenta
    [[nodiscard]]
    constexpr static QColor magenta() noexcept { return {255, 0, 255}; }
    // Получение цвета MediumOrchid
    [[nodiscard]]
    constexpr static QColor mediumOrchid() noexcept { return {186, 85, 211}; }
    // Получение цвета MediumPurple
    [[nodiscard]]
    constexpr static QColor mediumPurple() noexcept { return {147, 112, 219}; }
    // Получение цвета BlueViolet
    [[nodiscard]]
    constexpr static QColor blueViolet() noexcept { return {138, 43, 226}; }
    // Получение цвета DarkViolet
    [[nodiscard]]
    constexpr static QColor darkViolet() noexcept { return {148, 0, 211}; }
    // Получение цвета DarkOrchid
    [[nodiscard]]
    constexpr static QColor darkOrchid() noexcept { return {153, 50, 204}; }
    // Получение цвета DarkMagenta
    [[nodiscard]]
    constexpr static QColor darkMagenta() noexcept { return {139, 0, 139}; }
    // Получение цвета Purple
    [[nodiscard]]
    constexpr static QColor purple() noexcept { return {128, 0, 128}; }
    // Получение цвета Indigo
    [[nodiscard]]
    constexpr static QColor indigo() noexcept { return {75, 0, 130}; }
    // Получение цвета SlateBlue
    [[nodiscard]]
    constexpr static QColor slateBlue() noexcept { return {106, 90, 205}; }
    // Получение цвета DarkSlateBlue
    [[nodiscard]]
    constexpr static QColor darkSlateBlue() noexcept { return {72, 61, 139}; }

    //----------------------------------------------------------
    // Коричневые тона
    //----------------------------------------------------------
    // Получение цвета Cornsilk
    [[nodiscard]]
    constexpr static QColor cornsilk() noexcept { return {255, 248, 220}; }
    // Получение цвета BlanchedAlmond
    [[nodiscard]]
    constexpr static QColor blanchedAlmond() noexcept { return {255, 235, 205}; }
    // Получение цвета Bisque
    [[nodiscard]]
    constexpr static QColor bisque() noexcept { return {255, 228, 196}; }
    // Получение цвета NavajoWhite
    [[nodiscard]]
    constexpr static QColor navajoWhite() noexcept { return {255, 222, 173}; }
    // Получение цвета Wheat
    [[nodiscard]]
    constexpr static QColor wheat() noexcept { return {245, 222, 179}; }
    // Получение цвета BurlyWood
    [[nodiscard]]
    constexpr static QColor burlyWood() noexcept { return {222, 184, 135}; }
    // Получение цвета Tan
    [[nodiscard]]
    constexpr static QColor tan() noexcept { return {210, 180, 140}; }
    // Получение цвета RosyBrown
    [[nodiscard]]
    constexpr static QColor rosyBrown() noexcept { return {188, 143, 143}; }
    // Получение цвета SandyBrown
    [[nodiscard]]
    constexpr static QColor sandyBrown() noexcept { return {244, 164, 96}; }
    // Получение цвета Goldenrod
    [[nodiscard]]
    constexpr static QColor goldenrod() noexcept { return {218, 165, 32}; }
    // Получение цвета DarkGoldenRod
    [[nodiscard]]
    constexpr static QColor darkGoldenRod() noexcept { return {184, 134, 11}; }
    // Получение цвета Peru
    [[nodiscard]]
    constexpr static QColor peru() noexcept { return {205, 133, 63}; }
    // Получение цвета Chocolate
    [[nodiscard]]
    constexpr static QColor chocolate() noexcept { return {210, 105, 30}; }
    // Получение цвета SaddleBrown
    [[nodiscard]]
    constexpr static QColor saddleBrown() noexcept { return {139, 69, 19}; }
    // Получение цвета Sienna
    [[nodiscard]]
    constexpr static QColor sienna() noexcept { return {160, 82, 45}; }

    //----------------------------------------------------------
    // Зелёные тона
    //----------------------------------------------------------
    // Получение цвета GreenYellow
    [[nodiscard]]
    constexpr static QColor greenYellow() noexcept { return {173, 255, 47}; }
    // Получение цвета Chartreuse
    [[nodiscard]]
    constexpr static QColor chartreuse() noexcept { return {127, 255, 0}; }
    // Получение цвета LawnGreen
    [[nodiscard]]
    constexpr static QColor lawnGreen() noexcept { return {124, 252, 0}; }
    // Получение цвета LimeGreen
    [[nodiscard]]
    constexpr static QColor limeGreen() noexcept { return {50, 205, 50}; }
    // Получение цвета PaleGreen
    [[nodiscard]]
    constexpr static QColor paleGreen() noexcept { return {152, 251, 152}; }
    // Получение цвета LightGreen
    [[nodiscard]]
    constexpr static QColor lightGreen() noexcept { return {144, 238, 144}; }
    // Получение цвета MediumSpringGreen
    [[nodiscard]]
    constexpr static QColor mediumSpringGreen() noexcept { return {0, 250, 154}; }
    // Получение цвета SpringGreen
    [[nodiscard]]
    constexpr static QColor springGreen() noexcept { return {0, 255, 127}; }
    // Получение цвета MediumSeaGreen
    [[nodiscard]]
    constexpr static QColor mediumSeaGreen() noexcept { return {60, 179, 113}; }
    // Получение цвета SeaGreen
    [[nodiscard]]
    constexpr static QColor seaGreen() noexcept { return {46, 139, 87}; }
    // Получение цвета ForestGreen
    [[nodiscard]]
    constexpr static QColor forestGreen() noexcept { return {34, 139, 34}; }
    // Получение цвета DarkGreen
    [[nodiscard]]
    constexpr static QColor darkGreen() noexcept { return {0, 100, 0}; }
    // Получение цвета YellowGreen
    [[nodiscard]]
    constexpr static QColor yellowGreen() noexcept { return {154, 205, 50}; }
    // Получение цвета OliveDrab
    [[nodiscard]]
    constexpr static QColor oliveDrab() noexcept { return {107, 142, 35}; }
    // Получение цвета DarkOliveGreen
    [[nodiscard]]
    constexpr static QColor darkOliveGreen() noexcept { return {85, 107, 47}; }
    // Получение цвета MediumAquamarine
    [[nodiscard]]
    constexpr static QColor mediumAquamarine() noexcept { return {102, 205, 170}; }
    // Получение цвета DarkSeaGreen
    [[nodiscard]]
    constexpr static QColor darkSeaGreen() noexcept { return {143, 188, 143}; }
    // Получение цвета LightSeaGreen
    [[nodiscard]]
    constexpr static QColor lightSeaGreen() noexcept { return {32, 178, 170}; }
    // Получение цвета DarkCyan
    [[nodiscard]]
    constexpr static QColor darkCyan() noexcept { return {0, 139, 139}; }

    //----------------------------------------------------------
    // Синие тона
    //----------------------------------------------------------
    // Получение цвета Cyan
    [[nodiscard]]
    constexpr static QColor cyan() noexcept { return {0, 255, 255}; }
    // Получение цвета LightCyan
    [[nodiscard]]
    constexpr static QColor lightCyan() noexcept { return {224, 255, 255}; }
    // Получение цвета PaleTurquoise
    [[nodiscard]]
    constexpr static QColor paleTurquoise() noexcept { return {175, 238, 238}; }
    // Получение цвета Aquamarine
    [[nodiscard]]
    constexpr static QColor aquamarine() noexcept { return {127, 255, 212}; }
    // Получение цвета Turquoise
    [[nodiscard]]
    constexpr static QColor turquoise() noexcept { return {64, 224, 208}; }
    // Получение цвета MediumTurquoise
    [[nodiscard]]
    constexpr static QColor mediumTurquoise() noexcept { return {72, 209, 204}; }
    // Получение цвета DarkTurquoise
    [[nodiscard]]
    constexpr static QColor darkTurquoise() noexcept { return {0, 206, 209}; }
    // Получение цвета CadetBlue
    [[nodiscard]]
    constexpr static QColor cadetBlue() noexcept { return {95, 158, 160}; }
    // Получение цвета SteelBlue
    [[nodiscard]]
    constexpr static QColor steelBlue() noexcept { return {70, 130, 180}; }
    // Получение цвета LightSteelBlue
    [[nodiscard]]
    constexpr static QColor lightSteelBlue() noexcept { return {176, 196, 222}; }
    // Получение цвета PowderBlue
    [[nodiscard]]
    constexpr static QColor powderBlue() noexcept { return {176, 224, 230}; }
    // Получение цвета LightBlue
    [[nodiscard]]
    constexpr static QColor lightBlue() noexcept { return {173, 216, 230}; }
    // Получение цвета SkyBlue
    [[nodiscard]]
    constexpr static QColor skyBlue() noexcept { return {135, 206, 235}; }
    // Получение цвета LightSkyBlue
    [[nodiscard]]
    constexpr static QColor lightSkyBlue() noexcept { return {135, 206, 250}; }
    // Получение цвета DeepSkyBlue
    [[nodiscard]]
    constexpr static QColor deepSkyBlue() noexcept { return {0, 191, 255}; }
    // Получение цвета DodgerBlue
    [[nodiscard]]
    constexpr static QColor dodgerBlue() noexcept { return {30, 144, 255}; }
    // Получение цвета CornflowerBlue
    [[nodiscard]]
    constexpr static QColor cornflowerBlue() noexcept { return {100, 149, 237}; }
    // Получение цвета MediumSlateBlue
    [[nodiscard]]
    constexpr static QColor mediumSlateBlue() noexcept { return {123, 104, 238}; }
    // Получение цвета RoyalBlue
    [[nodiscard]]
    constexpr static QColor royalBlue() noexcept { return {65, 105, 225}; }
    // Получение цвета MediumBlue
    [[nodiscard]]
    constexpr static QColor mediumBlue() noexcept { return {0, 0, 205}; }
    // Получение цвета DarkBlue
    [[nodiscard]]
    constexpr static QColor darkBlue() noexcept { return QColor{0, 0, 139}; }
    // Получение цвета MidnightBlue
    [[nodiscard]]
    constexpr static QColor midnightBlue() noexcept { return {25, 25, 112}; }
};

//==============================================================
#endif // STANDART_COLORS_H
