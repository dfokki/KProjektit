#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    showResult();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_AskinHinta_valueChanged(double arg1)
{
    askinhinta = arg1;
    calculateSpending();
    showResult();
}

void MainWindow::on_Kappaletta_valueChanged(double arg1)
{
    kplAskissa = arg1;
    calculateSpending();
    showResult();
}

void MainWindow::on_Kulutus_valueChanged(double arg1)
{
    kplPäivässä = arg1;

    calculateSpending();
    showResult();
}

void MainWindow::on_Paiva_valueChanged(double arg1)
{
    ui->AskinHinta->setValue(arg1/ui->Kulutus->value()*ui->Kappaletta->value());
    ui->Vuosi->setValue(arg1*365);
    ui->Paiva->setValue(arg1);
}

void MainWindow::on_Vuosi_valueChanged(double arg1)
{
    ui->AskinHinta->setValue(arg1/365/ui->Kulutus->value()*ui->Kappaletta->value());
    ui->Vuosi->setValue(arg1);
    ui->Paiva->setValue(arg1 / 365);
}

double MainWindow::calculateSpending()
{
ui->pushButton_2->setStyleSheet("background-color: white");
    KulutusPerPäivä = ui->AskinHinta->value() / ui->Kappaletta->value() * ui->Kulutus->value();
    KulutusPerVuosi = KulutusPerPäivä * 365;

    return  KulutusPerPäivä;
}

void MainWindow::showResult()
{
    calculateSpending();
    ui->Vuosi->setValue(KulutusPerVuosi);
    ui->Paiva->setValue(KulutusPerPäivä);
}

void MainWindow::on_pushButton_2_clicked()
{
    showResult();
}

void MainWindow::on_pushButton_2_pressed()
{
    ui->pushButton_2->setStyleSheet("background-color: grey");
}

void MainWindow::on_pushButton_pressed()
{
    ui->pushButton->setStyleSheet("background-color: grey");
}
void MainWindow::on_pushButton_clicked()
{
    ui->pushButton->setStyleSheet("background-color: white");
}
