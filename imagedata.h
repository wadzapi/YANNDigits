#ifndef IMAGEDATA_H
#define IMAGEDATA_H

#include <QImage>
#include <vector>

/** Класс для хранения и передачи информации об изображении
 */
class ImageData
{
public:
    ImageData();
    ImageData(int width, int height);
    int GetLength();
    void Load(QImage image);
    void Load(int *array, int array_length);
    QImage getQImage();
    unsigned int Label();


private:
    std::vector<uint> values_;
    unsigned int width_;
    unsigned int height_;
    unsigned int label_;

};

#endif // IMAGEDATA_H
