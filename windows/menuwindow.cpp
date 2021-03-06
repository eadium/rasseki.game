#include "menuwindow.h"
#include "ui_menuwindow.h"
#include "loadwindow.h"

#include <QMessageBox>
#include "paths.h"
#include "style.h"
#include "russian.h"

MenuWindow::MenuWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenuWindow)
{
    ui->setupUi(this);
    Game = nullptr;

    //установка фона и размеров окна меню
    QImage bg_menu(img_menu.c_str());
    setFixedSize(bg_menu.width(), bg_menu.height());
    QBrush br;
    br.setTextureImage(bg_menu);
    QPalette plt = palette();
    plt.setBrush(QPalette::Background, br);
    setPalette(plt);

    //растягиваем изображение по размеру объекта
    QPixmap img(img_archer.c_str());
    int width = ui->logo->width();
    int height = ui->logo->height();
    ui->logo->setPixmap(img.scaled(width, height, Qt::KeepAspectRatio));

    //установка стилей
    this->setStyleSheet((css_widget + css_pushbutton + css_messagebox).c_str());
}

MenuWindow::~MenuWindow()
{
    delete ui;
    delete Game;
}

void MenuWindow::on_newGame_clicked()
{   //запуск окна игры
    hide();
    Game = new GameWindow(this);
    Game->show();
}

void MenuWindow::on_loadGame_clicked()
{   //запуск окна загрузки игры
    LoadWindow Load;
    Load.setModal(true);
    Load.exec();
}

void MenuWindow::on_exitGame_clicked()
{   //закрытие игры
    QMessageBox::StandardButton reply = QMessageBox::question(this, game_exit.c_str(), is_exit.c_str(), QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QApplication::quit();
    }
}
