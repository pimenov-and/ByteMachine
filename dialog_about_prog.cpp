////////////////////////////////////////////////////////////////
// ByteMachine
// Диалоговое окно "О программе"
////////////////////////////////////////////////////////////////
#include "dialog_about_prog.h"
#include "ui_dialog_about_prog.h"

//==============================================================
// Конструктор с параметром
//==============================================================
DialogAboutProg::DialogAboutProg(QWidget *parent) : QDialog{parent},
    ui_{new Ui::DialogAboutProg{}}
{
    ui_->setupUi(this);

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setFixedSize(sizeHint());

    const QString version = QString{"%1 %2 %3 %4"}.
        arg("Version", APP_VERSION, "from", APP_BUILD_DATE);
    ui_->labelVersion_->setText(version);
}

//==============================================================
// Деструктор
//==============================================================
DialogAboutProg::~DialogAboutProg()
{
    delete ui_;
}
