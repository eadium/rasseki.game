#include "journal.h"

#include "libAdapter.h"
#include "config.h"
#include "style.h"

Journal::Journal(QWidget *parent) : QTextEdit(parent)
{
    this->setStyleSheet(css_journal.c_str());
    timer = std::shared_ptr<QTimer>(new QTimer());   //инициализируем Таймер
    connect(timer.get(), SIGNAL(timeout()), this, SLOT(slotWrite()));    //подключаем cлот для отрисовки к таймеру
    timer->start(timer_delay);   //стартуем таймер
}

void Journal::slotWrite()
{
    Message post = Write();
    if (post.text != "") {
        // append((post.writer + ": " + post.text).c_str());
        append((post.text + '\n').c_str()); // no author ver.

    }
}
