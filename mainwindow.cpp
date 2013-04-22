#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imgframe.h"


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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ConfigureUI() {
    this->ui->frame_3->is_editable_ = true;
    AdjustTableRows(ui->spinBox->value());
    QObject::connect(ui->pushButton, SIGNAL(clicked()), ui->frame_3, SLOT(ClearFrame()));
    QObject::connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(Recognize()));
    QObject::connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(MnistImagesOpen()));
    QObject::connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(MnistLabelsOpen()));
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit->setReadOnly(true);
    QObject::connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(PrevMnist()));
    QObject::connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(NextMnist()));
    QObject::connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(AdjustTableRows(int)));
    QObject::connect(ui->pushButton_10, SIGNAL(clicked()), this, SLOT(StartTraining()));
    QObject::connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(CreateANN()));
    QObject::connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(LoadANN()));
    QObject::connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(SaveANN()));
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

void MainWindow::AdjustTableRows(int num_layers) {
    if (num_layers > 2) {
        QTableWidget *table = this->ui->tableWidget;
        table->clear();
        table->setRowCount(num_layers);
        QTableWidgetItem *item;
        for (int i = 0; i < num_layers; ++i) {
            item = new QTableWidgetItem();
            item->setText(QString("Слой %1").arg(i+1));
            item->setData(Qt::BackgroundColorRole, QColor("#c0c0c0"));
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            table->setItem(i, 0, item);
            item = new QTableWidgetItem();
            item->setText("20");
            table->setItem(i, 1, item);
        }
        table->item(0, 1)->setText(QString::number(28*28));
        table->item(num_layers - 1, 1)->setText(QString::number(10));
        this->update();
    }
}

void MainWindow::CreateANN() {
    ///Чтение параметров из формы GUI
    unsigned int layers_num = ui->spinBox->value();
    unsigned int capacity[layers_num];
    capacity[0] = 28 * 28;
    capacity[layers_num - 1] = 10;
    for (unsigned int i = 1; i < layers_num - 1; ++i) {
       QString text =  ui->tableWidget->item(i, 1)->text();
       int value = text.toInt();
       if (value < 0)
           value *= -1;
       capacity[i] = value;
    }
    ann_.ConstructANN(layers_num, capacity);
}

void MainWindow::LoadANN() {
    QString file_name = QFileDialog::getOpenFileName(this,tr("Открыть файл нейронной сети..."), ".", "Файл нейронной сети");
    if (!ann_.Load(file_name.toStdString())) {
        //сообщение об ошибке
    }
}

void MainWindow::SaveANN() {
    QString file_name = QFileDialog::getSaveFileName(this, tr("Сохранить файл нейронной сети..."), ".", "Файл нейронной сети");
    ann_.Save(file_name.toStdString());
}

void MainWindow::StartTraining() {
    ///Задание параметров сети
    if (ann_.IsInit()) {
        float learn_rate = static_cast<float>(ui->doubleSpinBox->value());
        ann_.net.set_learning_rate(learn_rate);
        float momentum = static_cast<float>(ui->doubleSpinBox_2->value());
        ann_.net.set_learning_momentum(momentum);
        unsigned int max_epochs = ui->spinBox_2->value();
        unsigned int epochs_span = ui->spinBox_3->value();
        float desired_error = static_cast<float>(ui->doubleSpinBox_3->value());
        ann_.SetTrainingData(&mnist_);
        ann_.Train(max_epochs, epochs_span, desired_error);
    }
}
