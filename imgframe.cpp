#include "imgframe.h"

#include <QMouseEvent>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QPainter>


ImgFrame::ImgFrame(QWidget *parent) :
    QFrame(parent) {
    InitFrame();
}

void ImgFrame::InitFrame() {
    this->setMouseTracking(true);
    is_painting_ = false;
    is_erasing_ = false;
    is_editable_ = false;
    /// установка цветовой схемы по умолчанию
    background_color_ = QColor(Qt::black);
    pen_color_ = QColor(Qt::white);
    /// задание ширины линии по умолчанию
    pen_width_ = 6;
}

QImage ImgFrame::GetImage() const {
    return image_;
}

void ImgFrame::SetImage(const QImage &image) {
    /// Масштабирование картинки
    QImage scaled_image = image.scaled(image.size());
    /// Копируем содержимое
    QPainter painter(&image_);
    painter.drawImage(image_.rect(), scaled_image);
    update();
}

void ImgFrame::ClearFrame() {
    image_.fill(background_color_);
    update();
}

void ImgFrame::InitImage() {
    image_ = QImage(this->frameSize(), QImage::Format_ARGB32);
    image_.fill(background_color_);
    update();
}

void ImgFrame::SetPenColor(const QColor &color) {
    pen_color_ = color;
}

void ImgFrame::SetPenWidth(int width) {
    pen_width_ = width;
}

QSize ImgFrame::GetSize() const {
    return image_.size();
}

bool ImgFrame::SaveImage(const QString &file_name, const char *format) {
    return image_.save(file_name, format);
}

bool ImgFrame::OpenImage(const QString &file_name) {
    QImage opened_image;
    if (!opened_image.load(file_name))
        return false;
    SetImage(opened_image);
    return true;
}

void ImgFrame::PaintToImage() {
    if (is_editable_) {
        QPainter painter(&image_);
        painter.setRenderHint(QPainter::Antialiasing, true);
        if (is_painting_)
            painter.setPen(QPen(pen_color_, pen_width_, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        else if (is_erasing_)
            painter.setPen(QPen(background_color_, pen_width_, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        if (end_point_ == start_point_) {
            painter.drawPoint(end_point_);
        } else {
            painter.drawLine(start_point_, end_point_);
        }
    }
}

void ImgFrame::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
        is_painting_ = true;
    else if (event->button() == Qt::RightButton)
        is_erasing_ = true;
    start_point_ = event->pos();
    end_point_ = event->pos();
    PaintToImage();
    this->update();
}

void ImgFrame::mouseMoveEvent(QMouseEvent *event) {
    if (is_painting_ || is_erasing_) {
        start_point_ = end_point_;
        end_point_ = event->pos();
        PaintToImage();
        this->update();
    }
}

/// Обработчик на отпускание кнопки мыши
void ImgFrame::mouseReleaseEvent(QMouseEvent *) {
    is_painting_ = false;
    is_erasing_ = false;
}

/// Обработчик события изменения размера
void ImgFrame::resizeEvent(QResizeEvent *) {
    InitImage();
}

/// Обработчик события отрисовки
void ImgFrame::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.drawImage(event->rect(), image_);
}

/// Метод определения рамки картинки
QRect ImgFrame::GetBounds() const {
    QRect bounds;
    //Размеры картинки
    int imgW = image_.width();
    int imgH = image_.height();
    //Координаты области
    int minX = imgW;
    int minY = imgH;
    int maxX = 0;
    int maxY = 0;
    //найдем границы прямоугольной области в которой содержится рисунок цифры
    for (int x = 0; x < imgW; x++) {
        for (int y = 0; y < imgH; y++) {
            if (QColor(image_.pixel(x,y)) == pen_color_) {
                if (x < minX)
                    minX = x;
                else if (x > maxX)
                    maxX = x;
                if (y < minY)
                    minY = y;
                else if (y > maxY)
                    maxY = y;
            }
        }
    }
    if (minX > maxX || minY > maxY) {
        minX = 0;
        maxX = imgW;
        minY = 0;
        maxY = imgH;
    }
    bounds.setCoords(minX, minY, maxX, maxY);
    return bounds;
}

/// Метод получения картинки с обрезанными краями
QImage ImgFrame::GetCroppedImage() {
    QImage cropped_image;
    cropped_image = image_.copy(GetBounds());
    return cropped_image;
}

