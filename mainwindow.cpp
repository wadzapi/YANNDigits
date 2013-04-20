#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imagedata.h"
#include "imgframe.h"
#include "mnistdataset.h"

#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QStringList>
#include <QTableWidgetItem>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ConfigureUI();
    ////
    ann_.ConstructANN();
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
    QObject::connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(AdjustTableRows(int)));
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
        LoadMnistImage();
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
        LoadMnistLabel();
    }
}

void MainWindow::Recognize() {
    ;
}

void MainWindow::NextMnist() {
    images_counter_.Next();
    LoadMnistImage();
    labels_counter_.Next();
    LoadMnistLabel();
}

void MainWindow::PrevMnist() {
    images_counter_.Prev();
    LoadMnistImage();
    labels_counter_.Prev();
    LoadMnistLabel();
}

void MainWindow::LoadMnistImage() {
    if (mnist_.IsImagesLoaded()) {
        QImage new_image = mnist_.GetImage(images_counter_.GetIndex())->GetQImage();
        ui->frame_2->SetImage(new_image);
        ui->label_2->setText(QString::number(images_counter_.GetValue()));
    }
}

void MainWindow::LoadMnistLabel() {
    if (mnist_.IsLabelsLoaded()) {
        QString label_string = QString::number(static_cast<int>(mnist_.GetLabel(labels_counter_.GetIndex())));
        this->ui->label_4->setText(QString(label_string));
        this->ui->label_15->setText(QString::number(labels_counter_.GetValue()));
    }
}

void MainWindow::AdjustTableRows(int numLayers) {
    QTableWidget *table = this->ui->tableWidget;
    table->clear();
    table->setRowCount(numLayers);
    QTableWidgetItem *item;
    for (int i = 0; i < numLayers; ++i) {
            item = new QTableWidgetItem();
            item->setText(QString("Слой %1").arg(i+1));
            item->setData(Qt::BackgroundColorRole, QColor("#c0c0c0"));
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            table->setItem(i, 0, item);
            item = new QTableWidgetItem();
            item->setText("20");
            table->setItem(i, 1, item);
    }
    this->update();
}
