#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "trem.h"
#include <QSemaphore>
#include <QMutex>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void updateInterface(int,int,int);
    void updateSemStats(int, int, QVector<QSemaphore *> *semVector);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_verticalSlider2_valueChanged(int value);

    void on_verticalSlider1_valueChanged(int value);

    void on_verticalSlider3_valueChanged(int value);

    void on_verticalSlider4_valueChanged(int value);

    void on_verticalSlider5_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    //Cria os objetos TREM's
    Trem *trem1;
    Trem *trem2;
    Trem *trem3;
    Trem *trem4;
    Trem *trem5;

    //Cria os objetos QSemaphores
    QSemaphore *s1;
    QSemaphore *s2;
    QSemaphore *s3;
    QSemaphore *s4;
    QSemaphore *s5;
    QSemaphore *s6;
    QSemaphore *s7;
    QSemaphore *s134;
    QSemaphore *s457;
    QSemaphore *s256;
    QSemaphore *stop;

    QVector<QSemaphore*> sem;
};

#endif // MAINWINDOW_H
