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
    QObject::connect(ui->pushButton, SIGNAL(clicked()), ui->frame_3, SLOT(ClearFrame()));
    QObject::connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(Recognize()));
    QObject::connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(MnistImagesOpen()));
    QObject::connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(MnistLabelsOpen()));
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit->setReadOnly(true);
    QObject::connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(PrevMnist()));
    QObject::connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(NextMnist()));
}

void MainWindow::MnistImagesOpen() {
    QString file_name = QFileDialog::getOpenFileName(this,tr("Открыть изображения MNIST..."), ".", "Файл изображений MNIST");
    ui->lineEdit->setText(file_name);
    if (!mnist_.LoadImages(file_name.toLatin1().constData())) {
        QMessageBox::warning(this, tr("Ошибка загрузки файла изображений MNIST"), tr("Произошла ошибка при загрузке файла с изображениями из набора MNIST. Попробуйте выбрать другой файл."), QMessageBox::Ok );
        ui->lineEdit->clear();
    } else {
        images_counter_.Init(1, mnist_.ImagesCount());
        images_counter_.SetLooped(true);
        ui->label_3->setText(QString::number(images_counter_.MaxValue()));
        LoadMnistImage(images_counter_.GetValue());
    }
}

void MainWindow::MnistLabelsOpen() {
    QString file_name = QFileDialog::getOpenFileName(this,tr("Открыть метки изображений MNIST..."), ".", "Файл меток MNIST");
    ui->lineEdit_2->setText(file_name);
    if (!mnist_.LoadLabels(file_name.toLatin1().constData())) {
        QMessageBox::warning(this, tr("Ошибка загрузки файла меток MNIST"), tr("Произошла ошибка при загрузке файла с метками изображений из набора MNIST. Попробуйте выбрать другой файл."), QMessageBox::Ok );
        ui->lineEdit->clear();
    } else {
        labels_counter_.Init(1, mnist_.LabelsCount());
        labels_counter_.SetLooped(true);
        ui->label_17->setText(QString::number(labels_counter_.MaxValue()));
        LoadMnistLabel(labels_counter_.GetValue());
    }
}

void MainWindow::Recognize() {
    ;

}

void MainWindow::NextMnist() {
    images_counter_.Next();
    LoadMnistImage(images_counter_.GetValue());
    labels_counter_.Next();
    LoadMnistLabel(labels_counter_.GetValue());
}

void MainWindow::PrevMnist() {
    images_counter_.Prev();
    LoadMnistImage(images_counter_.GetValue());
    labels_counter_.Prev();
    LoadMnistLabel(labels_counter_.GetValue());
}

void MainWindow::LoadMnistImage(unsigned int index) {
    if (mnist_.IsImagesLoaded()) {
        QImage new_image = mnist_.GetImage(index)->GetQImage();
        this->ui->frame_2->SetImage(new_image);
        this->ui->label_2->setText(QString::number(index));
    }
}

void MainWindow::LoadMnistLabel(unsigned int index) {
    if (mnist_.IsLabelsLoaded()) {
        QChar label_char = QChar::fromLatin1(mnist_.GetLabel(index));
        this->ui->label_4->setText(QString(label_char));
        this->ui->label_15->setText(QString::number(index));
    }
}
