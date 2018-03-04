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
#include <QMenuBar>
#include <QMenu>
#include <QAction>

#include <QDir>
#include <QUrl>
#include <QtMultimedia>
#include <QtMultimediaWidgets>

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
    Buttom **buttomList;
    QHBoxLayout *buttomLauout;
    QVBoxLayout *mainLayout;
    QWidget *window;
    QMenuBar *highTopMenu;

    QString ChooseWord[2];
    bool go_next;
    bool runAudio;
    QSqlDatabase db;
    QSqlQuery query;

    bool nextRound();
private slots:
    void slotButton();
    void ColorTrueAncwer();
    void AudioPlay();
};

#endif // MAINWINDOW_H
