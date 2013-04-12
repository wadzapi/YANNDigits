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
    void LoadMSBFirst(unsigned char *array, int array_length);
    void LoadLSBFirst(unsigned char *array, int array_length);

    QImage getQImage();
    unsigned int Label();


private:
    std::vector<unsigned char> values_;
    int width_;
    int height_;
    //int label_;

};

#endif // IMAGEDATA_H
