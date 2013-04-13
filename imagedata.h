#ifndef IMAGEDATA_H
#define IMAGEDATA_H

#include <QImage>

/** Класс для хранения и передачи информации об изображении
 */
class ImageData
{
public:
    ImageData();
    ImageData(int width, int height);
    ImageData(const ImageData& image_data);
    ~ImageData();
    int GetSize();
    bool Load(QImage image);
    bool Load(unsigned char* array, int array_length);
    QImage getQImage();
    unsigned char& operator[](const int index);
    const ImageData& operator=(const ImageData &image_data);



private:
    static const int kDefaultWidth;
    static const int kDefaultHeight;
    unsigned char* data_;
    int width_;
    int height_;
};

#endif // IMAGEDATA_H
