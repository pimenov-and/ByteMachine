////////////////////////////////////////////////////////////////
// ByteMachine
// Диалоговое окно "О программе"
////////////////////////////////////////////////////////////////
#ifndef DIALOG_ABOUT_PROG_H
#define DIALOG_ABOUT_PROG_H

//==============================================================
#include <QDialog>

//==============================================================
namespace Ui
{
    class DialogAboutProg;
}

//==============================================================
// Диалоговое окно "О программе"
//==============================================================
class DialogAboutProg : public QDialog
{
    Q_OBJECT
public:
    // Конструктор с параметром
    explicit DialogAboutProg(QWidget *parent = nullptr);
    // Деструктор
    ~DialogAboutProg() override;
private:
    // Интерфейс пользователя
    Ui::DialogAboutProg *ui_{nullptr};
};

//==============================================================
#endif // DIALOG_ABOUT_PROG_H
