#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QtSql>
#include <QWidget>
class Buttom : public QPushButton
{
   Q_OBJECT
public:
    explicit Buttom(QPushButton *parent = 0);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QLabel *label;
    Buttom *buttom_1;
    Buttom *buttom_2;
    Buttom *buttom_3;
    Buttom *buttom_4;
    QHBoxLayout *buttomLauout;
    QVBoxLayout *mainLayout;
    QWidget *window;

    QString ChooseWord[2];
    bool go_next;
    QSqlDatabase db;
    QSqlQuery query;

    void nextRound();
private slots:
    void slotButton();
};

#endif // MAINWINDOW_H
