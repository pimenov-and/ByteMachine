////////////////////////////////////////////////////////////////
// ByteMachine
// Главное окно
////////////////////////////////////////////////////////////////
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

//==============================================================
#include <QMainWindow>

//==============================================================
QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

//==============================================================
// Главное окно
//==============================================================
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    // Конструктор с параметром
    MainWindow(QWidget *parent = nullptr);
    // Деструктор
    ~MainWindow() override;
private:
    // Интерфейс пользователя
    Ui::MainWindow *ui_{nullptr};
};

//==============================================================
#endif // MAIN_WINDOW_H
