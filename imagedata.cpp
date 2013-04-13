#include "imagedata.h"
#include <QColor>
#include <cstring>

const int ImageData::kDefaultHeight = 28;
const int ImageData::kDefaultWidth = 28;

ImageData::ImageData(int width, int height) {
    width_ = width;
    height_ = height;
    data_ = new unsigned char[width_ * height_];
}

ImageData::ImageData() {
    width_ = kDefaultWidth;
    height_ = kDefaultWidth;
    data_ = new unsigned char[width_ * height_];
}

ImageData::ImageData(const ImageData &image_data) {
    if (this != &image_data) {
        width_ = image_data.width_;
        height_ = image_data.height_;
        data_ = new unsigned char[width_ * height_];
        this->Load(image_data.data_, width_* height_);
    }
}


unsigned char& ImageData::operator[](const int index) {
    return data_[index];
}

const ImageData& ImageData::operator =(const ImageData& image_data) {
    if (this == &image_data)
        return *this;
    delete[] data_;
    width_ = image_data.width_;
    height_ = image_data.height_;
    data_ = new unsigned char[width_ * height_];
    this->Load(image_data.data_, width_* height_);
    return *this;
}

ImageData::~ImageData() {
    delete[] data_;
}

bool ImageData::Load(QImage image) {
    QImage scaled_image;
    /// Масштабирование к необходимому формату
    scaled_image = image.scaled(width_, height_, Qt::IgnoreAspectRatio);
    /// Заполнение вектора проходом по строкам массива
    for (int y = 0; y < height_; y++ ) {
        for (int x = 0; x < width_; x++) {
            data_[y * width_ + x] = static_cast<unsigned char>(qGray(scaled_image.pixel(x,y)));
        }
    }
    return true;
}

/// Функция загрузки значений из массива
bool ImageData::Load(unsigned char *array, int array_length) {
    int length = width_ * height_;
    if (array_length > length) {
        return false;
    }
    memcpy(data_, array, length * sizeof(unsigned char));
    return true;
}

/// Функция получения картинки
QImage ImageData::getQImage() {
    QImage image(width_, height_, QImage::Format_ARGB32);
    int pixels = width_ * height_;
    if (image.byteCount() >= pixels * (int)sizeof(QRgb)) {
        QRgb *img_data = (QRgb *)image.bits();
        for (int i = 0; i < pixels; ++i) {
            int value = static_cast<int>(data_[i]);
            img_data[i] = qRgb(value, value, value);
        }
    }
    return image;
}

/// Функция получения длины массива
int ImageData::GetSize() {
    return width_ * height_;
}




