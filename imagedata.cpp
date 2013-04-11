#include "imagedata.h"
#include <QColor>

ImageData::ImageData() {
    width_ = 28;
    height_ = 28;
}

ImageData::ImageData(int width, int height) {
    width_ = width;
    height_ = height;
}

void ImageData::Load(QImage image) {
    /// Очищаем вектор значений
    values_.clear();
    QImage scaled_image;
    /// Масштабирование к необходимому формату
    scaled_image = image.scaled(width_, height_, Qt::KeepAspectRatio);
    /// Заполнение вектора проходом по строкам массива
    for (int y = 0; y < height_; y++ ) {
        for (int x = 0; x < width_; x++) {
            values_.push_back((uint)qGray(scaled_image.pixel(x,y)));
        }
    }
}

/// Функция загрузки значений из массива
void ImageData::Load(int *array, int array_length) {
    values_.clear();
    for (int index = 0; index < array_length; ++index) {
        values_.push_back(*array);
        ++array;
    }
}

/// Функция получения картинки
QImage ImageData::getQImage() {
    QImage image(width_, height_, QImage::Format_ARGB32);
    int pixels = width_ * height_;
    if (image.byteCount() >= pixels * (int)sizeof(QRgb)) {
        QRgb *img_data = (QRgb *)image.bits();
        for (int i = 0; i < pixels; ++i) {
            int value = values_[i];
            img_data[i] = qRgb(value, value, value);
        }
    }
    return image;
}

/// Функция получения длины массива
int ImageData::GetLength() {
    return width_ * height_;
}




