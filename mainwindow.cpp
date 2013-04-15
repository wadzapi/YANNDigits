#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imagedata.h"
#include "imgframe.h"
#include "mnistdataset.h"

#include <QString>
#include <QFileDialog>
#include <QMessageBox>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ConfigureUI();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ConfigureUI() {
    this->ui->frame_3->is_editable_ = true;
    this->ui->lineEdit->
    connect(ui->pushButton, SIGNAL(clicked()), ui->frame_3, SLOT(ClearFrame()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(onRecognize()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(MnistImagesOpen()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(MnistLabelsOpen()));
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit->setReadOnly(true);
}

void MainWindow::MnistImagesOpen() {
    QString file_name = QFileDialog::getOpenFileName(this,tr("Открыть изображения MNIST..."), ".", "Файл изображений MNIST");
    ui->lineEdit->setText(file_name);
    if (!mnist_.LoadImages(file_name.toLatin1().constData())) {
        QMessageBox::warning(this, tr("Ошибка загрузки файла изображений MNIST"), tr("Произошла ошибка при загрузке файла с изображениями из набора MNIST. Попробуйте выбрать другой файл."), QMessageBox::Ok );
        ui->lineEdit->clear();
    }

}

void MainWindow::MnistLabelsOpen() {
    QString file_name = QFileDialog::getOpenFileName(this,tr("Открыть метки изображений MNIST..."), ".", "Файл меток MNIST");
    ui->lineEdit_2->setText(file_name);
    if (!mnist_.LoadLabels(file_name.toLatin1().constData())) {
        QMessageBox::warning(this, tr("Ошибка загрузки файла меток MNIST"), tr("Произошла ошибка при загрузке файла с метками изображений из набора MNIST. Попробуйте выбрать другой файл."), QMessageBox::Ok );
        ui->lineEdit->clear();
    }
}

void MainWindow::Recognize() {
    ;
    //MnistDataset data;
    //data.Load("train-images.idx3-ubyte", "train-labels.idx1-ubyte");
    //QImage test_image = data.Get(59999)->GetQImage();
    //this->ui->frame->SetImage(test_image);
}
