#ifndef LOGBOOK_H
#define LOGBOOK_H

#include <QWidget>

class LogBook : public QWidget
{
    Q_OBJECT
public:
    explicit LogBook(QWidget *parent = nullptr);

signals:

public slots:
    void printNewLine(QString newLine);
};

#endif // LOGBOOK_H