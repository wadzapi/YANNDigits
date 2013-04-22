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
    void Load(QImage &image);
    void Load(unsigned char* array, int array_length);
    QImage GetQImage();
    unsigned char& operator[](const int index);
    const ImageData& operator=(const ImageData &image_data);
    float* GetFloatData(float min_val, float max_val) const;
    double* GetDoubleData(double min_val, double max_val) const;



private:
    static const int kMaxValue;
    static const int kMinValue;
    int width_;
    int height_;
    unsigned char* data_;
};

#endif // IMAGEDATA_H
