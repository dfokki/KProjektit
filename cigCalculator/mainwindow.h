#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    double askinhinta = 6;
    double kplAskissa = 20;
    double kplPäivässä = 10;
    double KulutusPerVuosi = 0;
    double KulutusPerPäivä = 0;

    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private slots:
    void on_AskinHinta_valueChanged(double arg1);

    void on_Kappaletta_valueChanged(double arg1);

    void on_Kulutus_valueChanged(double arg1);

    void on_Paiva_valueChanged(double arg1);

    void on_Vuosi_valueChanged(double arg1);



    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

    void on_pushButton_2_pressed();

    void on_pushButton_pressed();

private:

    Ui::MainWindow *ui;

    void showResult();
    double calculateSpending();


};

#endif // MAINWINDOW_H
